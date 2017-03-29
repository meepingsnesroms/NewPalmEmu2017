/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \todo Add complexity notes.
 *
 * $Id: XFcHashtable.h,v 1.23 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.23 $
 */

#ifndef XFCHASHTABLE_H_INCLUDED
#define XFCHASHTABLE_H_INCLUDED


#include <xfcore/XFcLinkedList.h>
#include <xfcore/XFcHashtableNode.h>
#include <xfcore/XFcHashtableIterator.h>


//! Represents hashing function in a template struct for hashtable.
template<class Key> struct XFcHashtableHash
{
    //! Hashing operator.
    XFCIMPORT UINT32 operator() (const Key aKey) const;
};


//! Equality check for hashtable in a template struct.
template<class Key> struct XFcHashtableEQ
{
    //! Equality check operator.
    XFCIMPORT INT operator() (const Key aKey1, const Key aKey2) const;
};


//! Hashtable template class.
/*! 
 * \sa XFuConfiguration
 */
template<class Key, class Value> class XFcHashtable
{
    friend class XFcHashtableIterator<Key, Value>;

public:

    //! Iterator type.
    typedef XFcHashtableIterator<Key, Value> iterator;

    //! Returns an iterator pointing to the first key.
    iterator begin();

    //! Returns an iterator pointing to the last key.
    iterator end();


    //! Returns the amount of elements.
    UINT32 size() const;


    //! Puts a new key-value pair in the hashtable.
    /*! \param aKey key for the new pair.
     *  \param aValue value for the new pair.
     * \return value of the new pair.
     */
    Value put(const Key aKey, const Value aValue);

    //! Gets the value for a key from the hashtable.
    /*! \param aKey key to get the value for.
     * \return value corresponding the requested key.
     */
    Value get(const Key aKey);

    //! Finds the key-value pair from the hashtable with a given key.
    /*! \param aKey key to get the pair by.
     * \return iterator pointing to the requested pair.
     */
    iterator find(const Key aKey);

    //! Removes a key-value pair from the hashtable.
    /*! \param aKey key of the pair to remove.
     * \return 1 if removal was successful, 0 otherwise.
     */
    INT remove(const Key aKey);

    //! Removes a key-value pair by iterator.
    /*! \param aIterator iterator pointing to the pair to be removed.
     * \return 1 if the removal was successful, 0 otherwise.
     */
    INT remove(iterator &aIterator);


    //! Creates an empty hashtable.
    XFcHashtable();

    //! Creates an empty hashtable with specified amount of buckets.
    /*! \param aBucketCount amount of buckets for the hashtable.
     */
    XFcHashtable(const INT32 aBucketCount);

    //! Destructor.
    ~XFcHashtable();

protected:

    //! Hasher function for the key type.
    XFcHashtableHash<Key> _hasher_function;
    //! Equality checking function for the key type.
    XFcHashtableEQ<Key> _equals_function;

    //! Number of keys/values in hashtable.
    UINT32 mElements;

    //! Number of buckets.
    INT32 mBuckets;

    //! Hashtable.
    XFcLinkedList<XFcHashtableNode<Key, Value> *> **mTable;

    //! Finds the first entry.
    typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator findFirst(); 

};


template<class Key, class Value>
typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator
XFcHashtable<Key, Value>::findFirst()
{
    if (mElements)
    {
        INT32 bucket = 0;

        // Find first non-null, non-empty bucket
        while ((mTable[bucket] == NULL) || (mTable[bucket]->size() == 0))
        {
            bucket++;
        }

        return mTable[bucket]->forwardBegin();
    }
    else
        return typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator(NULL);
}


template<class Key, class Value>
typename XFcHashtable<Key, Value>::iterator XFcHashtable<Key, Value>::begin()
{
    iterator i(this, findFirst());

    return i;
}


template<class Key, class Value>
typename XFcHashtable<Key, Value>::iterator XFcHashtable<Key, Value>::end()
{

    iterator i(this, 
        typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator(NULL));

    return i;
}


template<class Key, class Value> UINT32 XFcHashtable<Key, Value>::size() const
{
    return mElements;
}


template<class Key, class Value>
Value XFcHashtable<Key, Value>::put(const Key aKey, const Value aValue)
{
    UINT32 hashcode = _hasher_function(aKey);
    INT32 bucket = hashcode % mBuckets;

    // Linked list in bucket is empty
    if (mTable[bucket] == NULL)
    {
        mTable[bucket] = new XFcLinkedList<XFcHashtableNode<Key, Value> *>();

        XFcHashtableNode<Key, Value> *temp =
            new XFcHashtableNode<Key, Value>(aKey, aValue, bucket);

        mTable[bucket]->addLast(temp);
        mElements++;
    }
    else
    {
        XFcHashtableNode<Key, Value> *temp = NULL;

        typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator it;

        for (it = mTable[bucket]->forwardBegin(); it != mTable[bucket]->forwardEnd(); ++it)
        {
            temp = it.getData();

            if (_equals_function(aKey, temp->getKey()))
            {
                Value valTemp = temp->getValue();
                temp->setValue(aValue);

                return valTemp;
            }
        }

        temp = new XFcHashtableNode<Key, Value>(aKey, aValue, bucket);

        // Key wasn't found, create a new node
        mTable[bucket]->addLast(temp);
        mElements++;
    }

    return aValue;
}


template<class Key, class Value>
Value XFcHashtable<Key, Value>::get(const Key aKey)
{
    typename XFcHashtable<Key, Value>::iterator it = find(aKey);

    if (it.isValid())
        return it.getValue();
    else
        return Value();
}


template<class Key, class Value> 
typename XFcHashtable<Key, Value>::iterator 
XFcHashtable<Key, Value>::find(const Key aKey)
{
    UINT32 hashcode = _hasher_function(aKey);
    INT32 bucket = hashcode % mBuckets;

    if (mTable[bucket] != NULL)
    {
        XFcLinkedList<XFcHashtableNode<Key, Value> *> *list = mTable[bucket];
        typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator it;

        for (it = list->forwardBegin(); it != list->forwardEnd(); ++it)
        {
            if (_equals_function(aKey, it.getData()->getKey()))
            {
                return typename XFcHashtable<Key, Value>::iterator(this, it);
            }
        }
    }

    return this->end();
}


template<class Key, class Value>
INT XFcHashtable<Key, Value>::remove(const Key aKey)
{
    INT result = 0;
    XFcHashtableNode<Key, Value> *temp = NULL;

    UINT32 hashcode = _hasher_function(aKey);
    INT32 bucket = hashcode % mBuckets;

    typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator it;

    if (mTable[bucket] != NULL)
    {
        for (it = mTable[bucket]->forwardBegin(); it != mTable[bucket]->forwardEnd(); ++it)
        {
            temp = it.getData();

            if (_equals_function(aKey, temp->getKey()))
            {
                mTable[bucket]->remove(it, 1);

                delete temp;
                mElements--;

                result = 1;
                break;
            }
        }

        if (mTable[bucket]->size() == 0)
        {
            delete mTable[bucket];
            mTable[bucket] = NULL;
        }
    }

    return result;
}


template<class Key, class Value>
INT XFcHashtable<Key, Value>::remove(iterator &aIterator)
{
    XFcHashtableNode<Key, Value> *temp = NULL;

    if (aIterator.isValid())
    {
        iterator it = aIterator;
        ++aIterator;

        temp = it.mIterator.getData();

        UINT32 index = it.mBucketIndex;
        mTable[index]->remove(it.mIterator, 1);

        delete temp;
        mElements--;

        if (mTable[index]->size() == 0)
        {
            delete mTable[index];
            mTable[index] = NULL;
        }

        return 1;
    }
    else
        return 0;
}


template<class Key, class Value> XFcHashtable<Key, Value>::XFcHashtable()
{
    mElements = 0;
    mBuckets = 128;
    mTable = new XFcLinkedList<XFcHashtableNode<Key, Value> *> *[mBuckets];

    INT32 i;

    for (i = 0; i < mBuckets; i++)
    {
        mTable[i] = NULL;
    }
}


template<class Key, class Value>
XFcHashtable<Key, Value>::XFcHashtable(const INT32 aBucketCount)
{
    XFCASSERT(aBucketCount > 0);

    mElements = 0;
    mBuckets = aBucketCount;
    mTable = new XFcLinkedList<XFcHashtableNode<Key, Value> *> *[mBuckets];

    INT32 i;

    for (i = 0; i < mBuckets; i++)
    {
        mTable[i] = NULL;
    }
}


template<class Key, class Value> XFcHashtable<Key, Value>::~XFcHashtable()
{
    INT32 i;

    for (i = 0; i < mBuckets; ++i)
    {
        if (mTable[i] != NULL)
        {
            typename XFcLinkedList<XFcHashtableNode<Key, Value> *>::forwardIterator it;
            XFcHashtableNode<Key, Value> *temp = NULL;

            for (it = mTable[i]->forwardBegin(); it != mTable[i]->forwardEnd(); ++it)
            {
                temp = it.getData();
                delete temp;                
            }

            if (mTable[i] != NULL) 
            {
                delete mTable[i];
                mTable[i] = NULL;
            }
        }
    }

    delete[] mTable;
}


/*
//! Hashcode function for generic objects.
template<class Key> UINT32 Hash<Key>::operator() (const Key &key) const
{
    UINT32 hashcode = 0;

    UINT32 len = sizeof(Key);
    const CHAR8 *p = reinterpret_cast<const CHAR8 *>(&key);

    while (len--)
    {
        hashcode = (hashcode << 1) ^ *p++;
    }

    return hashcode;
}


//! Equality check for generic objects.
template<class Key>
INT EQ<Key>::operator() (const Key &key1, const Key &key2) const
{ 
    UINT32 hashcode = 0;

    UINT32 len = sizeof(Key);
    const CHAR8 *p1 = reinterpret_cast<const CHAR8 *>(&key1);
    const CHAR8 *p2 = reinterpret_cast<const CHAR8 *>(&key2);

    while (*p1++ == *p2++) {
        len--;
    }

    if (len < 0)
        return 1;
    else
        return 0;
}
*/


#endif // !XFCHASHTABLE_H_INCLUDED

