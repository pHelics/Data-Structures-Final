/* ***       Author:  David Jordan
     *  Last Update:  February 27, 2014
     *        Class:  CSI-281-01
     *     Filename:  dynamicArray.h
     *
     *  Description:
     *      This is the template dynamic array definition.
	 *      
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/


#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

using namespace std;


template <class T>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(int initialCapacity);
	~DynamicArray();

	void add(T data);
	int size();
	
	T operator[](int index);

private:
	T* mArray;
	int mCapacity;
	int mSize;
};


/*     Post: The array is allocated with the default capacity
 *  Purpose: To instantiate the list with a default initial capacity
 *****************************************************************************/
template <class T>
DynamicArray<T>::DynamicArray()
{
	mCapacity = 10;
	mSize     = 0;
	mArray    = new T[mCapacity];
}



/*      Pre: The given initial capacity is a positive integer
 *     Post: The array is allocated with the given capacity
 *  Purpose: To instantiate the list with an initial capacity
 *****************************************************************************/
template <class T>
DynamicArray<T>::DynamicArray(int initialCapacity)
{
	mCapacity = initialCapacity;
	mSize     = 0;
	mArray    = new T[mCapacity];
}


/*  Post: The memory used to store the data is freed
 *****************************************************************************/
template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete [] mArray;
}


/*      Pre:  The list is instantiated
 *     Post:  The data is added to the end of the list
 *  Purpose:  To add an element to the list
 *****************************************************************************/
template <class T>
void DynamicArray<T>::add(T data)
{
	if (mSize >= mCapacity)
	{
		mCapacity += 10;
		T* newArray = new T[mCapacity];
		for (int i = 0; i < mSize; i++)
			newArray[i] = mArray[i];
		delete [] mArray;
		mArray = newArray;
	}
	mArray[mSize] = data;
	mSize++;
}


/*      Pre:  The list is instantiated
 *     Post:  The number of elements is returned
 *  Purpose:  To get the current number of elements stored in the array
 *****************************************************************************/
template <class T>
int DynamicArray<T>::size()
{
	return mSize;
}


/*      Pre:  The list is instantiated and the index is valid
 *     Post:  The data at the given index is returned
 *  Purpose:  To get data from the list at a specific index
 *****************************************************************************/
template <class T>
 T DynamicArray<T>::operator[](int index)
{
	return mArray[index];
}


#endif



