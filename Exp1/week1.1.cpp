#include <bits/stdc++.h>
using namespace std;

int n;
int SumValue = 0; //输出结果

template <class T>
void GetSumValue(T Array[], int Judge[], int start, int size, int &SumValue) //ArrayJudge为标记数组，start为当前集合位置，size为集合大小
{
    if (start == size)
    { //所有集合的0/1标记完成
        int result = 0;
        int j = 0; //标记原数组位置
        for (int i = 0; i < size; i++)
        {
            if (Judge[i] == 1)
            {
                result += (j + 1) * Array[i]; //计算集合价值
                j++;
            }
        }
        SumValue ^= result;
        //cout << "result " << result << " sumvalue " << SumValue << endl;
        return;
    }
    Judge[start] = 0; //start位置元素不存在，生成子集
    GetSumValue(Array, Judge, start + 1, size, SumValue);
    Judge[start] = 1; //start位置元素存在，生成子集
    GetSumValue(Array, Judge, start + 1, size, SumValue);
}

int main(void)
{
    cin >> n;
    int *ArrayNumber = new int[n + 1]; //输入数组
    int *ArrayJudge = new int[n + 1];  //判断选择元素
    for (int i = 0; i < n; i++)
    {
        cin >> ArrayNumber[i];
        ArrayJudge[i] = 0;
    }
    GetSumValue(ArrayNumber, ArrayJudge, 0, n, SumValue);
    cout << SumValue << endl;
    return 0;
}