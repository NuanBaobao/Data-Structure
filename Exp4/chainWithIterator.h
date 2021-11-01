#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include <string>
#include "chainNode.h"
#include "myExceptions.h"

using namespace std;

template <class T>
class chain
{
public:
    // 构造函数、复制构造函数和析构函数
    chain(int initialCapacity = 10);
    chain(const chain<T> &);
    ~chain();

    // ADT 方法
    void insert(int theIndex, const T &theElement);   //插入链表元素
    void erase(const T &theElement);                  //删除链表元素
    void indexOf(const T &theElement) const;          //获得元素索引
    void output_xor();                                //输出元素异或和
    void reverse();                                   //反转链表
    void combine(chain<T> &chain1, chain<T> &chain2); // 有序链表合并
    void bubbleSort();                                // 链表插入排序
    //other
    void output(ostream &out) const;
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const;

    // 列表开始和结束的迭代器
    class iterator;
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(NULL); }

    // 链的迭代器
    class iterator
    {
    public:
        // C++ 需要的 typedef 用于前向迭代器
        typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // 构造函数
        iterator(chainNode<T> *theNode = NULL)
        {
            node = theNode;
        }

        // 取消引用运算符
        T &operator*() const { return node->element; }
        T *operator->() const { return &node->element; }

        // 增量
        iterator &operator++() // 前增量
        {
            node = node->next;
            return *this;
        }
        iterator operator++(int) // 后增量
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        // 等号测试
        bool operator!=(const iterator right) const
        {
            return node != right.node;
        }
        bool operator==(const iterator right) const
        {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    }; // 迭代器类结束

protected:
    void checkIndex(int theIndex) const;
    // 如果索引无效，则抛出非法索引
    chainNode<T> *firstNode; // 列表中的元素数
    int listSize;            // 列表中的元素数
};

template <class T>
chain<T>::chain(int initialCapacity)
{ // 构造函数
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theList)
{ // 复制构造函数
    listSize = theList.listSize;

    if (listSize == 0)
    { // 空列表
        firstNode = NULL;
        return;
    }

    // 非空列表
    chainNode<T> *sourceNode = theList.firstNode;
    // 要从中复制的列表中的节点
    firstNode = new chainNode<T>(sourceNode->element);
    // 复制列表的第一个元素
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;
    // *this 中的当前最后一个节点
    while (sourceNode != NULL)
    { // 复制剩余元素
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; // 结束链表
}

template <class T>
chain<T>::~chain()
{ // 析构函数，删除链中的所有节点。
    chainNode<T> *nextNode;
    while (firstNode != NULL)
    { // 删除第一个节点
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const
{ // 验证 theIndex 是否介于 0 和 listSize - 1 之间。
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T &chain<T>::get(int theIndex) const
{ // 返回索引为 theIndex 的元素。
    // 如果没有这样的元素，则抛出非法索引异常。
    checkIndex(theIndex);

    // 移动到所需节点
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;

    return currentNode->element;
}

template <class T>
void chain<T>::indexOf(const T &theElement) const
{ // 返回元素第一次出现的索引,如果元素不在列表中，则返回 -1。
    // 在链表中寻找元素theElement
    chainNode<T> *currentNode = firstNode;
    int index = 0; // 当前节点索引
    while (currentNode != NULL &&
           currentNode->element != theElement)
    {
        // 移向下一个节点
        currentNode = currentNode->next;
        index++;
    }

    // 确定找到匹配元素
    if (currentNode == NULL)
        cout << -1 << endl;
    else
        cout << index << endl;
}

template <class T>
void chain<T>::erase(const T &theElement)
{
    // 找到theElement所在节点删除
    chainNode<T> *deleteNode;
    if (firstNode->element == theElement)
    { //删除链表首节点
        deleteNode = firstNode;
        //删除首节点
        firstNode = firstNode->next;
        delete deleteNode;
        listSize--;
        return;
    }
    else
    { // 使用p找到要删除元素的前驱
        chainNode<T> *p = firstNode;
        for (; p->next != NULL; p = p->next)
        {
            if (p->next->element == theElement)
            {
                deleteNode = p->next;
                p->next = deleteNode->next; //删除deleteNode指向节点
                delete deleteNode;          // 去除 deleteNode
                listSize--;
                return;
            }
        }
    }
    cout << -1 << endl;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{ //在索引theIndex处插入元素theElement
    if (theIndex < 0 || theIndex > listSize)
    { // 无效索引
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
        // 在链表首节点插入
        firstNode = new chainNode<T>(theElement, firstNode); // 定义节点其值为theElement
    else
    { // 寻找新元素的前驱
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) // 找到索引指向的元素的前驱
            p = p->next;

        // 在p后插入
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template <class T>
void chain<T>::reverse()
{   //逆置链表
    // 链表为空或链表只有一个节点
    if(firstNode == NULL || firstNode->next == NULL)
        return;
    // currentNode为工作指针
    chainNode<T> *currentNode = firstNode;
    // tempNode指向当前节点上一个节点
    chainNode<T> *tempNode = NULL;

    while(currentNode != NULL)
    {
        //nextNode指向当前节点的后一个节点
        chainNode<T> *nextNode = currentNode->next;
        // 记录当前节点的下一个节点
        currentNode->next = tempNode;
        // 指针后移
        tempNode = currentNode;
        currentNode = nextNode;
    }
    firstNode = tempNode;
}

template <class T>
void chain<T>::output_xor()
{ // 输出异或和
    long long sum_xor = 0;

    chainNode<T> *currentNode = firstNode;

    for (int i = 0; i < listSize; i++)
    {
        sum_xor += (i ^ currentNode->element); //计算异或和
        currentNode = currentNode->next;       //工作指针后移
    }
    cout << sum_xor << endl;
}

template <class T>
void chain<T>::combine(chain<T> &chain1, chain<T> &chain2)
{   //使用迭代器实现两个有序链表的合并
    int i = 0;
    chain::iterator iter1 = chain1.begin(), iter2 = chain2.begin();
    // 未遍历到链表尾节点
    while (iter1 != NULL && iter2 != NULL)
    {
        if (*iter1 < *iter2)
        {   // 链表1的值小于链表2，插入链表1的值并将链表1指针后移
            insert(i++, *iter1);
            iter1++;
        }
        else if (*iter1 > *iter2)
        {  // 链表2的值小于链表1，插入链表2的值并将链表2指针后移
            insert(i++, *iter2);
            iter2++;
        }
        else
        {   // 链表2的值等于链表1，插入链表1、2的值并将链表指针后移
            insert(i++, *iter1);
            insert(i++, *iter2);
            iter1++;
            iter2++;
        }
    }
    if (iter1 != NULL)
    {   // 链表2的元素已遍历完，将链表1的元素全部复制
        while (iter1 != NULL)
        {
            insert(i++, *iter1);
            iter1++;
        }
    }
    if (iter2 != NULL)
    {   // 链表1的元素已遍历完，将链表2的元素全部复制
        while (iter2 != NULL)
        {
            insert(i++, *iter2);
            iter2++;
        }
    }
}

template <class T>
void chain<T>::bubbleSort()
{   // 单链表的冒泡排序
    if(firstNode == NULL || firstNode->next == NULL)
    {
        // 链表为空或者只有一个元素
        return;
    }
    chainNode<T> *currentNode = firstNode;
    for(int i = 0;i < this->listSize;i++)
    {   // 需要进行(n-1)次遍历,控制次数
        while(currentNode->next != NULL)
        {
            if(currentNode->element > currentNode->next->element)
            {
                // 若当前元素值大于下一节点，则交换
                T temp = currentNode->element;
                currentNode->element = currentNode->next->element;
                currentNode->next->element = temp;
            }
            // 工作指针后移
            currentNode = currentNode->next;
        }
        // 每次遍历完工作指针移到链表头
        currentNode = firstNode;
    }
}

template <class T>
void chain<T>::output(ostream &out) const
{ // 将链表放到输出流
    for (chainNode<T> *currentNode = firstNode;
         currentNode != NULL;
         currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// 重载 <<
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}

#endif
