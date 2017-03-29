/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Fast memory allocator template.
 *
 * $Id: XFcFastAllocator.h,v 1.12 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.12 $
 */

#ifndef XFC_UTIL_XFCFASTALLOCATOR_H_INCLUDED
#define XFC_UTIL_XFCFASTALLOCATOR_H_INCLUDED

#include <xfcore/XFcLinkedList.h>


//! Fast memory allocation template.
/*! Provides a reasonably fast way to allocate objects dynamically.
 */
template<class T, INT aGranularity> class XFcFastAllocator
{

public:

    //! Constructor.
    XFcFastAllocator();
    //! Destructor.
    ~XFcFastAllocator();
    //! Resets the allocator (this will not free any memory).
    void reset();
    //! Frees all allocated memory.
    void freeMemory();
    //! Allocates new object.
    T * alloc();
    //! Returns the pointer to newest object.
    T * getCurrent();

protected:

    INT mCurrentItem;
    typename XFcLinkedList<T *>::forwardIterator mIterator;
    XFcLinkedList<T *> mList;    //!< Linked list of arrays.

};


template<class T, INT aGranularity>
XFcFastAllocator<T, aGranularity>::XFcFastAllocator()
{
    reset();
}


template<class T, INT aGranularity>
XFcFastAllocator<T, aGranularity>::~XFcFastAllocator()
{
    freeMemory();
}


template<class T, INT aGranularity>
void XFcFastAllocator<T, aGranularity>::reset()
{
    mCurrentItem = -1;
    mIterator = mList.forwardBegin();
}


template<class T, INT aGranularity>
void XFcFastAllocator<T, aGranularity>::freeMemory()
{
    typename XFcLinkedList<T *>::forwardIterator iter;
    for (iter = mList.forwardBegin(); iter != mList.forwardEnd(); ++iter)
    {
        delete[] iter.getData();
    }
}


template<class T, INT aGranularity>
T * XFcFastAllocator<T, aGranularity>::alloc()
{
    T *res = NULL;
    if (mCurrentItem == -1)
    {
        T *object = NULL;
        if (mIterator == mList.forwardEnd())
        {
            // need to allocate new array.
            T *array = new T[aGranularity];
            mList.addLast(array);
            mIterator = mList.forwardBegin();
            object = mIterator.getData();
        }
        else
            object = mIterator.getData();
        mCurrentItem = 0;
        res = &object[mCurrentItem];
    }
    else
    {
        mCurrentItem++;
        if (mCurrentItem == aGranularity)
        {
            mCurrentItem = -1;
            typename XFcLinkedList<T *>::forwardIterator last(mIterator);
            mIterator++;
            if (mIterator == mList.forwardEnd())
            {
                T *array = new T[aGranularity];
                mList.addLast(array);
                mIterator = ++last;
                T *object = mList.getLast();
                mCurrentItem = 0;
                res = &object[mCurrentItem];
            }
            else
            {
                T *object = mIterator.getData();
                mCurrentItem = 0;
                res = &object[mCurrentItem];
            }
        }
        else
        {
            T *object = mIterator.getData();
            res = &object[mCurrentItem];
        }
    }
    return res;
}


template<class T, INT aGranularity>
T * XFcFastAllocator<T, aGranularity>::getCurrent()
{
    T *object = mIterator.getData();
    return &object[mCurrentItem];
}


#endif // !XFC_UTIL_XFCFASTALLOCATOR_H_INCLUDED

