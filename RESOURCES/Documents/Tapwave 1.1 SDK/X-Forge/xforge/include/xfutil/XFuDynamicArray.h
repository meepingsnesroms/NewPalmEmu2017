/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Dynamic array template
 * 
 * $Id: XFuDynamicArray.h,v 1.10 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.10 $
 */

#ifndef XFUDYNAMICARRAY_H_INCLUDED
#define XFUDYNAMICARRAY_H_INCLUDED


//! Default size increment for the element pointer array.
#define XFUDYNAMICARRAY_DEFAULT_SIZE_INCREMENT 10


//! Dynamic array template.
/*! 
 * Simple usage example to store UINT32's:<br>
 *
 * \code
 * // Create the array
 * XFuDynamicArray<UINT32> *store = XFuDynamicArray<UINT32>::create();
 * // put 3 values to the end of the array
 * store->put(1);
 * store->put(3);
 * store->put(4);
 * // Insert value in the second position of the array
 * store->put(1, 2);
 * // store now contains { 1, 2, 3, 4 }
 * UINT32 value = store->get(3);
 * // value is now 4
 * delete store;
 * \endcode
 */
template<class T> class XFuDynamicArray
{
protected:
    //! The number of elements in the array.
    UINT32 mElementCount;
    //! Array of elements stored by the dynamic array.
    T *mElements;

    //! Size increment.
    UINT32 mSizeIncrement;

    //! The size of the element array.
    UINT32 mArraySize;

    //! Resizes the element array.
    void setArraySize(const UINT32 aSize);

    //! Protected constructor.
    XFuDynamicArray();

public:
    //! Returns the size increment.
    UINT32 getSizeIncrement() const;
    //! Sets the size increment.
    void setSizeIncrement(const UINT32 aSizeIncrement);
    //! Returns the number of elements stored in the array.
    UINT32 size() const;
    //! Returns the size of the array.
    UINT32 maxSize() const;
    //! Checks whether the array has any elements.
    INT isEmpty() const;

    //! Returns an element at the specified position in the array.
    T get(const UINT32 aPos) const;
    //! Returns the last element from the array.
    T get() const;
    //! Adds an element to the end of the array.
    void put(T aElement);
    //! Inserts an element to the array at the specified position.
    void put(const UINT32 aPos, T aElement);
    //! Removes an element from the array and returns the removed element.
    T removeIndex(const UINT32 aPos);
    //! Removes an element from the array.
    T remove(T aElement);
    //! Removes the last element from the array and returns the removed element.
    T remove();
    //! Clears the array, but does not free its internal storage.
    void clear();

    //! Static constructor.
    static XFuDynamicArray * create(const UINT32 aSize = XFUDYNAMICARRAY_DEFAULT_SIZE_INCREMENT);
    //! Destructor.
    ~XFuDynamicArray();
};


template<class T> void XFuDynamicArray<T>::setArraySize(const UINT32 aSize)
{
    mElements = (T *)realloc(mElements, aSize * sizeof(T));
    mArraySize = aSize;
}


template<class T> XFuDynamicArray<T>::XFuDynamicArray()
{
    mElements = NULL;
    mElementCount = 0;
    mArraySize = 0;
}


template<class T> UINT32 XFuDynamicArray<T>::getSizeIncrement() const
{
    return mSizeIncrement;
}


template<class T> 
void XFuDynamicArray<T>::setSizeIncrement(const UINT32 aSizeIncrement)
{
    mSizeIncrement = aSizeIncrement;
}


template<class T> UINT32 XFuDynamicArray<T>::size() const
{
    return mElementCount;
}


template<class T> UINT32 XFuDynamicArray<T>::maxSize() const
{
    return mArraySize;
}


template<class T> INT XFuDynamicArray<T>::isEmpty() const
{
    if (mElementCount > 0)
        return 0;
    else
        return 1;
}


template<class T> T XFuDynamicArray<T>::get(const UINT32 aPos) const
{
    if (aPos >= mElementCount)
        return T();
    else
        return mElements[aPos];
}


template<class T> T XFuDynamicArray<T>::get() const
{
    if (mElementCount == 0)
        return T();
    else
        return mElements[mElementCount - 1];
}


template<class T> void XFuDynamicArray<T>::put(T aElement)
{
    put(mElementCount, aElement);
}


template<class T> void XFuDynamicArray<T>::put(const UINT32 aPos, T aElement)
{
    if (aPos > mElementCount) return;

    if (mElementCount >= mArraySize) 
        setArraySize(mArraySize + mSizeIncrement);

    if (aPos < mElementCount)
    {
        UINT32 i;
        for (i = mElementCount; i > aPos; --i)
        {
            mElements[i] = mElements[i - 1];
        }
    }

    mElements[aPos] = aElement;

    mElementCount++;
}


template<class T> T XFuDynamicArray<T>::removeIndex(const UINT32 aPos)
{
    if (aPos >= mElementCount) return T();

    T element = mElements[aPos];

    UINT32 i, lastElement;
    lastElement = mElementCount - 1;
    for (i = aPos; i < lastElement; ++i)
    {
        mElements[i] = mElements[i + 1];
    }

    mElementCount--;

    return element;
}


template<class T> T XFuDynamicArray<T>::remove()
{
    return removeIndex(mElementCount - 1);
}


template<class T> T XFuDynamicArray<T>::remove(T aElement)
{
    UINT32 i;
    for (i = 0; i < mElementCount; ++i)
    {
        if (mElements[i] == aElement) return removeIndex(i);
    }

    return T();
}


template<class T> void XFuDynamicArray<T>::clear()
{
    mElementCount = 0;
}


template<class T> 
XFuDynamicArray<T> * XFuDynamicArray<T>::create(const UINT32 aSize)
{
    XFuDynamicArray<T> *xfuda = new XFuDynamicArray<T>();
    if (xfuda == NULL) return NULL;
    xfuda->mElements = (T *)malloc(aSize * sizeof(T));
    xfuda->mElementCount = 0;
    xfuda->mArraySize = aSize;
    xfuda->mSizeIncrement = XFUDYNAMICARRAY_DEFAULT_SIZE_INCREMENT;

    return xfuda;
}


template<class T> XFuDynamicArray<T>::~XFuDynamicArray()
{
    if (mElements != NULL) 
    {
        free(mElements);
        mElements = NULL;
    }
}


#endif // !XFUDYNAMICARRAY_H_INCLUDED

