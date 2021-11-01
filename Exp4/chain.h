// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented

#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "chainNode.h"
#include "myExceptions.h"

using namespace std;

template <class T>
class chain : public linearList<T>
{
public:
   // constructor, copy constructor and destructor
   chain(int initialCapacity = 10);
   chain(const chain<T> &);
   ~chain();

   // ADT methods
   void insert(int theIndex, const T &theElement); //插入链表元素
   void erase(const T &theElement);                //删除链表元素
   void indexOf(const T &theElement) const;        //获得元素索引
   void output_xor();                              //输出元素异或和
   void reverse();                                 //反转链表
   //other
   void output(ostream &out) const;
   bool empty() const { return listSize == 0; }
   int size() const { return listSize; }
   T &get(int theIndex) const;

protected:
   void checkIndex(int theIndex) const;
   // throw illegalIndex if theIndex invalid
   chainNode<T> *firstNode; // pointer to first node in chain
   int listSize;            // number of elements in list
};

template <class T>
chain<T>::chain(int initialCapacity)
{ // Constructor.
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
{ // Copy constructor.
   listSize = theList.listSize;

   if (listSize == 0)
   { // theList is empty
      firstNode = NULL;
      return;
   }

   // non-empty list
   chainNode<T> *sourceNode = theList.firstNode;
   // node in theList to copy from
   firstNode = new chainNode<T>(sourceNode->element);
   // copy first element of theList
   sourceNode = sourceNode->next;
   chainNode<T> *targetNode = firstNode;
   // current last node in *this
   while (sourceNode != NULL)
   { // copy remaining elements
      targetNode->next = new chainNode<T>(sourceNode->element);
      targetNode = targetNode->next;
      sourceNode = sourceNode->next;
   }
   targetNode->next = NULL; // end the chain
}

template <class T>
chain<T>::~chain()
{ // Chain destructor. Delete all nodes in chain.
   while (firstNode != NULL)
   { // delete firstNode
      chainNode<T> *nextNode = firstNode->next;
      delete firstNode;
      firstNode = nextNode;
   }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const
{ // Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }
}

template <class T>
T &chain<T>::get(int theIndex) const
{  // Return element whose index is theIndex.
   // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // move to desired node
   chainNode<T> *currentNode = firstNode;
   for (int i = 0; i < theIndex; i++)
      currentNode = currentNode->next;

   return currentNode->element;
}

template <class T>
void chain<T>::indexOf(const T &theElement) const
{  // Return index of first occurrence of theElement.
   // Return -1 if theElement not in list.

   // search the chain for theElement
   chainNode<T> *currentNode = firstNode;
   int index = 0; // index of currentNode
   while (currentNode != NULL &&
          currentNode->element != theElement)
   {
      // move to next node
      currentNode = currentNode->next;
      index++;
   }

   // make sure we found matching element
   if (currentNode == NULL)
      cout << -1 << endl;
   else
      cout << index << endl;
}

template <class T>
void chain<T>::erase(const T &theElement)
{
   // locate node with element to delete
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
            delete deleteNode;          // remove deleteNode from chain
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
   { // invalid index
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

      // insert after p
      p->next = new chainNode<T>(theElement, p->next);
   }
   listSize++;
}

template <class T>
void chain<T>::reverse()
{
   chainNode<T> *pre = firstNode;
   firstNode = firstNode->next;
   pre->next = NULL;
   chainNode<T> *aft = firstNode->next;
   for (int i = 0; i < listSize - 3; i++)
   {
      firstNode->next = pre;
      pre = firstNode;
      firstNode = aft;
      aft = aft->next;
   }
   firstNode->next = pre;
   aft->next = firstNode;
   firstNode = aft;
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
void chain<T>::output(ostream &out) const
{ // Put the list into the stream out.
   for (chainNode<T> *currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
      out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
   x.output(out);
   return out;
}

#endif
