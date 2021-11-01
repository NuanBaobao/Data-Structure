#include<iostream>
#include "chainWithIterator.h"

using namespace std;

int main()
{
   // test constructor
   int n,q,temp;
   cin >> n>> q;
   // 建立单链表
   chain<int>mychain;
   for(int i = 0;i < n;i++)
   {
       cin >> temp;
       mychain.insert(i,temp);
   }
   mychain.output(cout);

    int idx, val;
    for (int i = 0; i < q; i++)
    {
        int decision;
        cin >> decision;
        switch (decision)
        {
            case(1):
                cin >> idx >> val;
                // 插入元素
                mychain.insert(idx, val);
                // mychain.output(cout);
                break;
            case(2):
                cin >> val;
                // 删除元素
                mychain.erase(val);
                // mychain.output(cout);
                break;
            case(3):
                // 反转链表
                mychain.reverse();
                // mychain.output(cout);
                break;
            case(4):
                cin >> val;
                //查找元素索引
                mychain.indexOf(val);
                break;
            case(5):
                //输出异或和
                mychain.output_xor();
            default:
                break;
        }
    }
    return 0;
}
