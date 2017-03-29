/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcHashtableNode.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFCHASHTABLENODE_H_INCLUDED
#define XFCHASHTABLENODE_H_INCLUDED



//! Hashtable node template.
template<class Key, class Value> class XFcHashtableNode
{

public:

    //! Sets the key, value and bucket index of this node.
    void set(const Key aKey, const Value aValue, const INT32 aBucketIndex);

    //! Returns the key of this node.
    Key getKey() const;
    
    //! Returns the value of this node.
    Value getValue() const;
    
    //! Sets the value of this node.
    /*! \param aValue new value for the node.
     * \return previous value.
     */
    Value setValue(const Value aValue);

    //! Returns the bucket index of this node.
    INT32 getBucketIndex() const;

    //! Creates a node with specified key and value.
    /*! \param aKey key of the new node.
     *  \param aValue value of the new node.
     *  \param aBucketIndex bucket index of the new node.
     */
    XFcHashtableNode(const Key aKey, const Value aValue,
                    const INT32 aBucketIndex);

protected:

    //! Key of this node.
    Key mKey;
    //! Value of this node.
    Value mValue;
    //! Bucket index of this node.
    INT32 mBucketIndex;

};


template<class Key, class Value> 
void XFcHashtableNode<Key, Value>::set(const Key aKey, const Value aValue, 
                                      const INT32 aBucketIndex)
{
    mKey = aKey;
    mValue = aValue;
    mBucketIndex = aBucketIndex;
}


template<class Key, class Value>
Key XFcHashtableNode<Key, Value>::getKey() const
{
    return mKey;
}


template<class Key, class Value>
Value XFcHashtableNode<Key, Value>::getValue() const
{
    return mValue;
}


template<class Key, class Value>
Value XFcHashtableNode<Key, Value>::setValue(const Value aValue)
{
    Value temp = mValue;
    mValue = aValue;

    return temp;
}


template<class Key, class Value>
INT32 XFcHashtableNode<Key, Value>::getBucketIndex() const
{
    return mBucketIndex;
}


template<class Key, class Value>
XFcHashtableNode<Key, Value>::XFcHashtableNode(const Key aKey,
                                             const Value aValue, 
                                             const INT32 aBucketIndex)
{
    mKey = aKey;
    mValue = aValue;
    mBucketIndex = aBucketIndex;
}


#endif // !XFCHASHTABLENODE_H_INCLUDED

