//
// Created by zjh15 on 2021/10/26.
//
#include <iostream>
#include <sstream>

using namespace std;

template<class T>
class arrayQueue
{
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() {delete [] queue;}
    bool empty() const {return theFront == theBack;}
    int size() const
    {return (theBack - theFront + arrayLength) % arrayLength;}
    T front()
    {// 返回队头元素
        if (theFront == theBack)
            return NULL;
        return queue[(theFront + 1) % arrayLength];
    }
    T back()
    {// 返回队尾元素
        if (theFront == theBack)
            return NULL;
        return queue[theBack];
    }
    void pop()
    {// 弹出队头元素
        if (theFront == theBack)
            return;
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();  // 析构 T
    }
    void push(const T& theElement);
private:
    int theFront;       // 队头元素的前一个位置
    int theBack;        // 队尾元素位置
    int arrayLength;    // 队列容量
    T *queue;           // 队列数组
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{// 构造函数
    if (initialCapacity < 1)
    {// 队列容量出错
        cout << "Initial capacity = " << initialCapacity << " Must be > 0";
        return;
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{// 添加元素到队尾

    // 队列满时增加队列容量
    if ((theBack + 1) % arrayLength == theFront)
    {// 2倍的容量
        T* newQueue = new T[2 * arrayLength];

        // 复制元素到新队列
        int start = (theFront + 1) % arrayLength;
        if (start < 2)
            // 没有环
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        {  // 队列出现环
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        // 切换到新队列并设置 Front 和 Back
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;   // 原队列大小 arrayLength - 1
        arrayLength *= 2;
        queue = newQueue;
    }

    // 将元素插到队尾
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

int main(void)
{
    int n;
    cin >> n;
    arrayQueue<int> q(n);
    // 建立队列
    for(int i = 1;i <= n;i++)
        q.push(i);
    while(q.size() >= 2)
    {// 当队列元素个数>=2时不断弹出队头前两个元素，将第二个元素插入队尾
        q.pop();
        int theElement = q.front(); // 记录队头元素
        q.pop();
        q.push(theElement);
    }
    cout << q.back() << endl;

    return 0;
}

