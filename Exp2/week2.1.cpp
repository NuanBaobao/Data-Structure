#include <bits/stdc++.h>
#define MAXSIZE 1000
using namespace std;

template <class T>
class SortFunction
{
public:
    SortFunction(){};
    ~SortFunction(){};
    //名次计算
    void rankArray(T a[], int n, int r[])
    {
        //给数组a中元素排序
        for (int i = 0; i < n; i++)
        { //初始化
            r[i] = 0;
        }
        //比较排序
        for (int i = 1; i < n; i++) //r记录名次
        {
            for (int j = 0; j < i; j++)
            {
                if (a[j] <= a[i])
                    r[i]++;
                else
                    r[j]++;
            }
        }
    }

    //名次排序
    void rearrange(T a[], int n, int r[])
    {
        //使用附加数组u将元素排序
        T *u = new T[n];
        //将数组a中的元素按r中的顺序移到u中
        for (int i = 0; i < n; i++)
        {
            u[r[i]] = a[i];
        }
        //将数组u中的元素移到a中
        for (int i = 0; i < n; i++)
            a[i] = u[i];
        delete[] u;
    }

    //按名次排序(原地重排)
    void rearrange2(T a[], int n, int r[])
    {
        //原地重排
        for (int i = 0; i < n; i++)
        {
            //把正确的元素移动到a[i]
            while (r[i] != i)
            {
                int t = r[i];
                swap(a[i], a[t]);
                swap(r[i], r[t]);
            }
        }
    }

    //寻找最大元组位置
    int indexOfMax(T a[], int n)
    {
        if (n < 0)
        {
            cout << "n must be > 0" << endl;
        }
        int indexOfMax = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[indexOfMax] < a[i])
            {
                indexOfMax = i;
            }
        }
        return indexOfMax;
    }

    //选择排序
    void selectionSort2(T a[], int n)
    {
        //给数组a排序
        for (int size = n; size > 1; size--)
        {
            int j = indexOfMax(a, size);
            swap(a[j], a[size - 1]);
        }
    }

    //及时终止的选择排序
    void selectionSort(T a[], int n)
    {
        bool sorted = false;
        for (int size = n; !sorted && (size > 1); size--)
        {
            int indexOfMax = 0;
            sorted = true;
            for (int i = 1; i < size; i++)
            {
                //找最大元素
                if (a[indexOfMax] <= a[i])
                    indexOfMax = i;
                else
                    sorted = false; //无序
            }
            swap(a[indexOfMax], a[size - 1]);
        }
    }

    //一次冒泡
    bool bubble(T a[], int n)
    {
        //把数组a中最大的元素移到右边
        bool swapped = false; //尚未发生交换
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        return swapped;
    }

    //及时终止的冒泡排序
    void bubbleSort(T a[], int n)
    {
        for (int i = n; i > 1 && bubble(a, i); i--)
            ;
    }

    //向有序数组中插入元素
    void insert(T a[], int n, const T &x)
    {
        int i;
        //数组a容量大于n
        for (i = n - 1; i >= 0 && x < a[i]; i--)
        {
            a[i + 1] = a[i];
        }
        a[i + 1] = x;
    }

    //插入排序
    void insertionSort(T a[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            T t = a[i];
            insert(a, i, t);
        }
    }
};

int main(void)
{
    int n;
    cin >> n;
    int *number = new int[MAXSIZE];
    for (int i = 0; i < n; i++)
        cin >> number[i];
    int r[MAXSIZE];
    SortFunction<int> sort;
    //sort.rearrange(number,n,r);
    //sort.selectionSort2(number, n);
    //sort.bubbleSort(number,n);
    sort.insertionSort(number, n);
    for (int i = 0; i < n; i++)
        cout << number[i] << " ";
    cout << endl;

    return 0;
}