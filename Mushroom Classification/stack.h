/* ***       Author:  Wei Kian Chen
     *  Last Update:  January 21, 2014
     *        Class:  CSI-281
     *     Filename:  stack.h
     *
     *  Description:
     *      This is the template stack definition.
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <class T>
class Stack {
   private:
       template <class T>
       struct Node
       {
          T       mData;
          Node<T> *mNext;

          /*      Pre:  None
           *     Post:  This object is initialized using default values
           *  Purpose:  To intialize date object
           *************************************************************************/
          Node()
          {
             mData = T();
             mNext = NULL;
          }


          /*      Pre:  None
           *     Post:  This object is initialized using specified data
           *  Purpose:  To intialize date object
           *************************************************************************/
          Node(T data)
          {
             mData = data;
             mNext = NULL;
          }
       };

      Node<T> *mHead, *mTail;
      int     mCount;

   public:
      Stack();
      ~Stack();

      int  getCount();

      void clear();
      void display();
      bool isEmpty();
      bool isExist(T searchKey);
      T    pop();
      void push(T data);
};


template <class T>
Stack<T>::Stack()
{
   mHead  = NULL;
   mTail  = NULL;
   mCount = 0;
}


template <class T>
Stack<T>::~Stack()
{
   while (!isEmpty())
      pop();
}


template <class T>
int Stack<T>::getCount()
{
   return mCount;
}


template <class T>
void Stack<T>::clear()
{
   while (!isEmpty())
      pop();
}


template <class T>
void Stack<T>::display()
{
   Node<T> *tmp;

   if (isEmpty())
      cout << "Empty Stack\n";
   else
   {
      tmp = mHead;

      while (tmp != NULL)
      {
         cout << tmp->mData << " ";
         tmp = tmp->mNext;
      }
      cout << endl;
   }
}


template <class T>
bool Stack<T>::isEmpty()
{
   return mCount == 0;
}


/*      Pre:  The stack is initialized and searchKey is available
 *     Post:  The function retuns true if the searchKey exists in the queue;
 *            otherwise return false
 *  Purpose:  To determine if a given value exists in the stack or not
 *************************************************************************/
template <class T>
bool Stack<T>::isExist(T searchKey)
{
	bool exists = false;
	if (mCount > 0)
	{
		if (mTail->mData == searchKey || mHead->mData == searchKey)
			exists = true;
		else
		{
			Node<T> *current = mHead;
			while (current->mNext != NULL && !exists)
			{
				if (current->mNext->mData == searchKey)
					exists = true;
				current = current->mNext;
			}
		}
	}
	return exists;
}


/*      Pre:  The stack is initialized
 *     Post:  The first node in the stack is removed, and its content is
 *            returned.  If the stack is empty return the default value
 *            for the given data type
 *  Purpose:  To remove the first node in the stack
 *************************************************************************/
template <class T>
T Stack<T>::pop()
{
	T data;
	if (mHead != NULL)
	{
		Node<T> *temp = mHead;
		mHead = temp->mNext;
		if (mHead == NULL)
			mTail = NULL;
		mCount--;
		data = temp->mData;
		delete temp;
	}
	else
		data = T();
	return data;
}


/*      Pre:  The stack is initialized
 *     Post:  The new node is added at the beginning of the stack.
 *            Duplication is allowed
 *  Purpose:  To add a new node at the beginning of the stack
 *************************************************************************/
template <class T>
void Stack<T>::push(T data)
{
	if (mHead == NULL)
	{
		mHead = new Node<T>(data);
		mTail = mHead;
	}
	else
	{
		Node<T> *temp = mHead;
		mHead = new Node<T>(data);
		mHead->mNext = temp;
	}
	mCount++;
}


#endif