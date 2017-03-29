/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcHashtableIterator.h,v 1.16 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.16 $
 */

#ifndef XFCHASHTABLEITERATOR_H_INCLUDED
#define XFCHASHTABLEITERATOR_H_INCLUDED

#include <xfcore/XFcHashtableNode.h>

template<class Key, class Value> class XFcHashtable;

//! Hashtable iterator template.
template<class Key, class Value> class XFcHashtableIterator
{
public:
    //! Advances to the next node, pre-operation.
    /*! \return reference to next node.
     */
    XFcHashtableIterator<Key, Value> & operator ++ ();

    //! Advances to the next node, post-operation.
    /*! \return next node.
     */
    XFcHashtableIterator<Key, Value> operator ++ (int);

    //! Inequality check.
    /*! Tests if two nodes are inequal.
     * \param aRef iterator to test this iterator against.
     * \return 1 if inequal, 0 otherwise.
     */
    INT operator != (const XFcHashtableIterator<Key, Value> &aRef) const;

    //! Equality check.
    /*! Tests if two nodes are equal.
     * \param aRef iterator to test this iterator against.
     * \return 1 if equal, 0 otherwise.
     */
    INT operator == (const XFcHashtableIterator<Key, Value> &aRef) const;


    //! Returns information about the validity of the node.
    /*! \return 1 if the node is valid, 0 otherwise.
     */
    INT isValid() const;

    //! Returns the key from this key-value pair.
    Key getKey() const;

    //! Returns the value from this key-value pair.
    Value getValue() const;

    //! Sets the value of this key-value pair.
    /*! \param aValue new value to set.
     */
    Value setValue(const Value aValue);


    //! Makes this iterator a copy of another iterator.
    /*! \param aClone iterator to copy state from.
     * \return reference to this iterator.
     */
    XFcHashtableIterator & operator= (const XFcHashtableIterator &aClone);

    //! Creates an empty iterator.
    XFcHashtableIterator();

    // Clones an iterator.
    //XFcHashtableIterator(const XFcHashtableIterator<Key, Value> &aClone);

private:
    //! Index of the current bucket.
    INT32 mBucketIndex;
    //! Forward iterator for the current bucket.
    typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator mIterator;
    //! Current hashtable.
    XFcHashtable<Key, Value> *mHashtable;

#ifdef XFC_COMPILER_ADS
    //! Creates an iterator pointing to a certain node.
    typedef typename XFcLinkedList<XFcHashtableNode<Key, Value>*>::forwardIterator myHashtableForwardIterator;
    XFcHashtableIterator(XFcHashtable<Key, Value> * aHashtable, myHashtableForwardIterator aIterator);
#else
    //! Creates an iterator pointing to a certain node.
    XFcHashtableIterator(XFcHashtable<Key, Value> * aHashtable,
                         typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator aIterator);
#endif

    friend class XFcHashtable<Key, Value>;
    
};


template<class Key, class Value>
XFcHashtableIterator<Key, Value> &
XFcHashtableIterator<Key, Value>::operator ++ ()
{
    if (mIterator.isValid())
        mIterator++;

    if (!mIterator.isValid())
    {
        while (++mBucketIndex < mHashtable->mBuckets)
        {
            if ((mHashtable->mTable[mBucketIndex] != NULL) &&
                (mHashtable->mTable[mBucketIndex]->size()))
            {
                mIterator = mHashtable->mTable[mBucketIndex]->forwardBegin();
                return *this;
            }
        }
    }

    return *this;
}


template<class Key, class Value>
XFcHashtableIterator<Key, Value>
XFcHashtableIterator<Key, Value>::operator ++ (int)
{
    XFcHashtableIterator<Key, Value> newIt = XFcHashtableIterator<Key, Value>(*this);

    if (mIterator.isValid())
        mIterator++;

    if (!mIterator.isValid())
    {
        while (++mBucketIndex < mHashtable->mBuckets)
        {
            if ((mHashtable->mTable[mBucketIndex] != NULL) &&
                (mHashtable->mTable[mBucketIndex]->size()))
            {
                mIterator = mHashtable->mTable[mBucketIndex]->forwardBegin();
                return *this;
            }
        }
    }
/*    
    else
    {
        while (++mBucketIndex < mHashtable->mBuckets)
        {
            if (mHashtable->mTable[mBucketIndex] != NULL)
            {
                mIterator = mHashtable->mTable[mBucketIndex]->forwardBegin();
                break;
            }
        }
    }
*/

    return newIt;
}


template<class Key, class Value>
INT XFcHashtableIterator<Key, Value>::operator != (
    const XFcHashtableIterator &aRef) const
{
    if (mIterator != aRef.mIterator)
        return 1;
    else
        return 0;
}


template<class Key, class Value>
INT XFcHashtableIterator<Key, Value>::operator == (
    const XFcHashtableIterator &aRef) const
{
    if (mIterator == aRef.mIterator)
        return 1;
    else
        return 0;
}


template<class Key, class Value>
INT XFcHashtableIterator<Key, Value>::isValid() const
{
    return mIterator.isValid();
}


template<class Key, class Value>
Key XFcHashtableIterator<Key, Value>::getKey() const
{
    if (mIterator.isValid())
        return (mIterator.getData())->getKey();
    else
        return Key();
}


template<class Key, class Value>
Value XFcHashtableIterator<Key, Value>::getValue() const
{
    if (mIterator.isValid())
        return (mIterator.getData())->getValue();
    else
        return Value();
}


template<class Key, class Value>
Value XFcHashtableIterator<Key, Value>::setValue(const Value aValue)
{
    if (mIterator.isValid())
        return (mIterator.getData())->setValue(aValue);
    else
        return Value();
}


template<class Key, class Value>
XFcHashtableIterator<Key, Value>::XFcHashtableIterator()
{
    mBucketIndex = -1;
    mHashtable = NULL;
    mIterator = typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator(NULL);
}


template<class Key, class Value>
#ifdef XFC_COMPILER_ADS
XFcHashtableIterator<Key, Value>::XFcHashtableIterator(
    XFcHashtable<Key, Value> *aHashtable, myHashtableForwardIterator aIterator)
#else
XFcHashtableIterator<Key, Value>::XFcHashtableIterator(
    XFcHashtable<Key, Value> *aHashtable,
    typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator aIterator)
#endif    
{
    mHashtable = aHashtable;
    mIterator = aIterator;
    
    if (mIterator.isValid())
        mBucketIndex = (mIterator.getData())->getBucketIndex();
    else
        mBucketIndex = -1;
}


template<class Key, class Value> XFcHashtableIterator<Key, Value> & 
    XFcHashtableIterator<Key, Value>::operator= (const XFcHashtableIterator<Key, Value> &aClone)
{
    mBucketIndex = aClone.mBucketIndex;
    mIterator = aClone.mIterator;
    mHashtable = aClone.mHashtable;

    return *this;
}

// Clones an iterator.
/*
template<class Key, class Value>
XFcHashtableIterator<Key, Value>::XFcHashtableIterator(
    const XFcHashtableIterator<Key, Value> &aClone)
{
    mBucketIndex = aClone.mBucketIndex;
    mIterator = aClone.mIterator;
    mHashtable = aClone.mHashtable;
}
*/


#endif // !XFCHASHTABLEITERATOR_H_INCLUDED

