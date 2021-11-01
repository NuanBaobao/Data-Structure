#include <iostream>
#include "chainWithIterator.h"

using namespace std;

int main()
{
    // 创建单链表
    chain<int> myChain1;
    chain<int> myChain2;
    chain<int> myChain3;

    int n, m, temp;
    cin >> n >> m;

    // 建立单链表
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        myChain1.insert(i, temp);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> temp;
        myChain2.insert(i, temp);
    }
    // 链表一冒泡排序后输出异或和
    myChain1.bubbleSort();
    myChain1.output_xor();

    // 链表二冒泡排序后输出异或和
    myChain2.bubbleSort();
    myChain2.output_xor();

    // 链表合并排序输出异或和
    myChain3.combine(myChain1, myChain2);
    myChain3.output_xor();

    return 0;
}
