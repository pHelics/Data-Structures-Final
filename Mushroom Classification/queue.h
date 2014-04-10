/* ***       Author:  Wei Kian Chen
     *  Last Update:  January 21, 2014
     *        Class:  CSI-281
     *     Filename:  queue.h
     *
     *  Description:
     *      This is the template queue definition.
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template <class T>
class Queue {
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
      Queue();
      ~Queue();

      int  getCount();

      void clear();
      T    dequeue();
      void display();
      void enqueue(T data);
      bool isEmpty();
      bool isExist(T searchKey);
};


template <class T>
Queue<T>::Queue()
{
   mHead  = NULL;
   mTail  = NULL;
   mCount = 0;
}


template <class T>
Queue<T>::~Queue()
{
   while (!isEmpty())
      dequeue();
}


template <class T>
int Queue<T>::getCount()
{
   return mCount;
}


template <class T>
void Queue<T>::clear()
{
   while (!isEmpty())
      dequeue();
}


/*      Pre:  The queue is initialized
 *     Post:  The first node in the queue is removed, and its content is
 *            returned.  If the queue is empty return the default value
 *            for the given data type
 *  Purpose:  To remove the first node in the queue
 *************************************************************************/
template <class T>
T Queue<T>::dequeue()
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


template <class T>
void Queue<T>::display()
{
   Node<T> *tmp;

   if (isEmpty())
      cout << "Empty Queue\n";
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



/*      Pre:  The queue is initialized
 *     Post:  The new node is added at the end of the queue.  Duplication
 *            is allowed
 *  Purpose:  To add a new node at the end of the queue
 *************************************************************************/
template <class T>
void Queue<T>::enqueue(T data)
{
	if (mHead == NULL)
	{
		mHead = new Node<T>(data);
		mTail = mHead;
	}
	else
	{
		mTail->mNext = new Node<T>(data);
		mTail = mTail->mNext;
	}
	mCount++;
}


template <class T>
bool Queue<T>::isEmpty()
{
   return mCount == 0;
}



/*      Pre:  The queue is initialized and searchKey is available
 *     Post:  The function retuns true if the searchKey exists in the queue;
 *            otherwise return false
 *  Purpose:  To determine if a given value exists in the queue or not
 *************************************************************************/
template <class T>
bool Queue<T>::isExist(T searchKey)
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


#endif