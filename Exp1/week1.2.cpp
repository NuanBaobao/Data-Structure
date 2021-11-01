#include <bits/stdc++.h>
using namespace std;

int sumValue = 0;
template <class T>
void perm(T arr[], int start, int size, int &sumValue) // 计算每种排列的价值,size标志全排列个数，start标志当前选择位置
{
    if (start == size)
    { //全部遍历完成
        int per_value = 0;
        for (int i = 0; i < size; i++)
            per_value += (arr[i] ^ (i + 1));
        sumValue |= per_value;
    }
    else
    {
        for (int i = start; i < size; i++)
        {
            swap(arr[start], arr[i]);
            perm(arr, start + 1, size, sumValue);
            swap(arr[i], arr[start]);
        }
    }
}
int main()
{
    int n;
    cin >> n;

    int *arr = new int[n];

    for (int i = 0; i < n; i++) // 初始化
        cin >> arr[i];

    perm(arr, 0, n, sumValue);

    cout << sumValue << endl;
}