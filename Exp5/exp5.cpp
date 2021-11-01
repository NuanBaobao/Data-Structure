//
// Created by zjh15 on 2021/10/18.
//
#include <iostream>
using namespace std;

template<class T>
struct matrixTerm  //创建节点，里面包含矩阵中一个元素的  行，列，数值
{
    int r; // 元素索引
    int c;
    T v; // 元素值
};

template<class T>
class sparseMatrix
{
private:
    int rows; // 矩阵中的行数
    int cols; // 矩阵中的列数
    int listsize; // 非0项个数
    matrixTerm<T>* terms; // 非零项terms
public:
    sparseMatrix() { listsize = 0; rows = 0; cols = 0; } // 构造函数
    void set(int m, int n, int t); // 重置矩阵，根据输入元素建立terms
    void setTerm(int m, int n, int t); // 根据输入三元组建立terms
    void output();  // 数据矩阵元素
    int multiply(sparseMatrix<T>& q); // 稀疏矩阵乘法
    int add(sparseMatrix<T>& q); // 稀疏矩阵加法
    void transpose(); // 稀疏矩阵转置
};

template<class T>
void sparseMatrix<T>::set(int m, int n, int t) //m,n分别是行数和列数
{// 重置矩阵，根据输入元素建立terms
    // 新矩阵的信息
    rows = m;
    cols = n;
    T value;
    listsize = 0; // 初始化新矩阵非0元素个数为0
    if (t != 0) delete[] terms; // 释放原矩阵空间
    terms = new matrixTerm<T>[m * n + 1];
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> value;
            if (value != 0)
            {// 遍历输入元素，当其不为0时加入terms
                listsize++;
                terms[listsize].r = i;
                terms[listsize].c = j;
                terms[listsize].v = value;
            }
        }
    }
}

template<class T>
void sparseMatrix<T>::setTerm(int m, int n, int t)
{// 根据输入三元组建立terms
    rows = m;
    cols = n;
    listsize = t;
    terms = new matrixTerm<T>[t + 1];
    for (int i = 1; i <= listsize; i++)
        cin >> terms[i].r >> terms[i].c >> terms[i].v;
}

template<class T>
void sparseMatrix<T>::output()
{// 稀疏矩阵输出
    int step = 1;
    cout << rows << ' ' << cols << endl; // 输出矩阵行列数
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            if (step <= listsize && terms[step].r == i && terms[step].c == j)
            {// 遍历矩阵元素，当其索引信息在terms中时输出，否则输出0
                cout << terms[step].v << ' '; step++;
            }
            else cout << 0 << ' ';
        }
        cout << endl;
    }
}

template<class T>
void sparseMatrix<T>::transpose()
{// 稀疏矩阵的转置
    matrixTerm<T>* b = new matrixTerm<T>[listsize + 1]; // 新建转置矩阵terms
    int* colSize = new int[cols + 1]; // 记录矩阵每一列的非0元素个数
    int* rowNext = new int[cols + 1]; // 记录矩阵当前列首个非0元素的索引

    for (int i = 1; i <= cols; i++) // 初始化
        colSize[i] = 0;
        for (int i = 1; i <= listsize; i++)
        colSize[terms[i].c]++;

    // 寻找b中每一行的起始点
    rowNext[1] = 1;
    for (int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    // 实现从*this到b的转置复制
    for (int i = 1; i <= listsize; i++)
    {
        int j = rowNext[terms[i].c]++;
        b[j].r = terms[i].c;
        b[j].c = terms[i].r;
        b[j].v = terms[i].v;
    }
    // 释放原数组空间
    delete[] terms;
    delete[] colSize;
    delete[] rowNext;
    terms = b;
    int t = cols;
    cols = rows;
    rows = t;
}

template<class T>
int sparseMatrix<T>::multiply(sparseMatrix<T>& q)
{//实现稀疏矩阵的乘法，*this = *this * q,若二者不能相乘，*this= q
    if (cols != q.rows)
    { // 如果两个矩阵不匹配
        delete[] terms;
        terms = q.terms; // 将 terms 指向 q 中的 terms
        listsize = q.listsize;
        rows = q.rows;
        cols = q.cols;
        return -1;
    }
    else
    {// 如果两个矩阵能相乘
        matrixTerm<T>* result = new matrixTerm<T>[rows * q.cols + 1]; // 储存结果
        int number = 0; // 目前没有结果
        //统计this------------------------------------------------------------------------------------
        int* irowsize = new int[rows + 1]; // 统计每一行有几个非0元素
        int* irowtop = new int[rows + 1]; // 统计每一行的非0元素在terms数组中的索引

        for (int i = 1; i <= rows; i++) // 初始化为0
            irowsize[i] = 0;
        for (int i = 1; i <= listsize; i++)
            irowsize[terms[i].r]++;

        // 寻找*this中每一行的起始点
        irowtop[1] = 1;
        for (int i = 2; i <= rows; i++)
            irowtop[i] = irowtop[i - 1] + irowsize[i - 1];
        //统计矩阵q--------------------------------------------------------------------------------------
        q.transpose();//转置矩阵q,便于后续处理
        //转置后的矩阵q的相关信息
        int* qrowsize = new int[q.rows + 1];//统计每一行有几个非0元素
        int* qrowtop = new int[q.rows + 1];//统计每一行的非0元素在terms数组中的索引

        for (int i = 1; i <= q.rows; i++)
            qrowsize[i] = 0;//初始化为0
        for (int i = 1; i <= q.listsize; i++)
            qrowsize[q.terms[i].r]++;

        qrowtop[1] = 1;
        for (int i = 2; i <= q.rows; i++)
            qrowtop[i] = qrowtop[i - 1] + qrowsize[i - 1];
        //乘法算法-----------------------------------------------------------------------------------------
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= q.rows; j++)
            {
                int temp = 0;//储存结果矩阵某（i，j）的数值
                int flagi = irowtop[i];   int flagq = qrowtop[j]; // 记录矩阵*this当前行与q中当前列非0元素索引

                while (flagi < irowtop[i] + irowsize[i] && flagq < qrowtop[j] + qrowsize[j])
                {// 保证只在当前行与当前列进行
                    if (terms[flagi].c == q.terms[flagq].c)
                    {// 若当前行与当前列对应位置元素值不为0，则相乘结果对[i,j]处值有影响
                        temp += terms[flagi].v * q.terms[flagq].v;
                        flagi++;
                        flagq++;
                    }
                    else if (terms[flagi].c < q.terms[flagq].c) {
                        // 如果当前行不为0元素小于当前列不为0元素值，则寻找当前行下一个非0元素
                        flagi++;
                    }
                    else flagq++;
                }
                if (temp != 0)
                {// 若当前最终乘积不为0，则加入terms
                    number++;
                    result[number].r = i;
                    result[number].c = j;
                    result[number].v = temp;
                }
            }
        }
        delete[] terms;
        terms = result;
        listsize = number;
        cols = q.rows;
        return 0;
    }
}
template<class T>
int sparseMatrix<T>::add(sparseMatrix<T>& q)
{// 稀疏矩阵的加法，*this = *this + q,若二者不能相加，则*this = q
    if (rows != q.rows || cols != q.cols)
    {// 稀疏矩阵不能相加
        delete[] terms;
        terms = q.terms;
        listsize = q.listsize;
        rows = q.rows;
        cols = q.cols;
        return -1;
    }
    else
    {// 矩阵加法
        matrixTerm<T>* data = new matrixTerm<T>[listsize + q.listsize + 1];
        int i = 1, j = 1; int t = 0;
        while (i != (listsize + 1) && j != (q.listsize + 1))
        {// 矩阵*this与q中对应位置未遍历完，记录在terms中的索引
            int aindex = (terms[i].r - 1) * cols + terms[i].c - 1;
            int qindex = (q.terms[j].r - 1) * cols + q.terms[j].c - 1;

            if (aindex < qindex)
            {// q项在后
                t++;
                data[t].r = terms[i].r;
                data[t].c = terms[i].c;
                data[t].v = terms[i].v;
                i++;
            }
            else if (aindex == qindex)
            {// 两项在同一个位置
                if (terms[i].v + q.terms[j].v != 0)
                {// 仅当相加后不为0时加入data
                    t++;
                    data[t].r = terms[i].r;
                    data[t].c = terms[i].c;
                    data[t].v = terms[i].v + q.terms[j].v;
                }
                i++;
                j++;
            }
            else if (aindex > qindex)
            {// a项在后
                t++;
                data[t].r = q.terms[j].r;
                data[t].c = q.terms[j].c;
                data[t].v = q.terms[j].v;
                j++;
            }
        }
        for (; i <= listsize; i++)
        {// 复制*this剩余项
            t++;
            data[t].r = terms[i].r;
            data[t].c = terms[i].c;
            data[t].v = terms[i].v;
        }
        for (; j <= q.listsize; j++)
        {// 复制q剩余项
            t++;
            data[t].r = q.terms[j].r;
            data[t].c = q.terms[j].c;
            data[t].v = q.terms[j].v;
        }
        delete[] terms;
        terms = data;
        listsize = t;
    }
    return 0;
}

int main()
{
    int w; //w 为执行操作数
    cin >> w;
    int step = 0;
    int size;
    int theRow, theCol;
    sparseMatrix<int> mode1;
    for (int i = 1; i <= w; i++)
    {
        int m;
        cin >> m;
        switch (m)
        {
            case 1: // 矩阵重置
            {cin >> theRow >> theCol;
                mode1.set(theRow, theCol, step);
                step++;
                break; }
            case 2: // 矩阵乘法
            {cin >> theRow >> theCol;
                cin >> size;
                sparseMatrix<int> mode2;
                mode2.setTerm(theRow, theCol, size);
                int t = mode1.multiply(mode2);
                if (t == -1) { cout << t << endl; }
                break; }
            case 3: // 矩阵加法
            {cin >> theRow >> theCol;
                cin >> size;
                sparseMatrix<int> mode2;
                mode2.setTerm(theRow, theCol, size);
                int t = mode1.add(mode2);
                if (t == -1) cout << t << endl;
                break; }
            case 4: // 输出矩阵元素
            {mode1.output(); break; }
            case 5: // 矩阵转置
            {mode1.transpose(); break; }
        }
    }
}