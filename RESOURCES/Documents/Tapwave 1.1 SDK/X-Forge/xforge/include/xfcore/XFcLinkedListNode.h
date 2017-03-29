/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedListNode.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFCLINKEDLISTNODE_H_INCLUDED
#define XFCLINKEDLISTNODE_H_INCLUDED

template<class T> class XFcLinkedList;


//! Linked list node template.
template<class T> class XFcLinkedListNode
{
    friend class XFcLinkedList<T>;

public:
    //! Returns pointer to next node in list.
    XFcLinkedListNode<T> * getNext();

    //! Returns pointer to previous node in list.
    XFcLinkedListNode<T> * getPrev();


    //! Returns the value of the node.
    T getData() const;

    //! Sets the value of the node.
    /*! \param aNewData new value for the node.
     * \return default value of the data type.
     */
    T setData(const T aNewData);


    //! Creates an empty node.
    XFcLinkedListNode();

    //! Creates a node with value.
    /*! \param aNewData value for the new node.
     */
    XFcLinkedListNode(const T &aNewData);

protected:

    //! Value of the node.
    T mData;

    //! Link to next node.
    XFcLinkedListNode<T> *mNext;
    //! Link to previous node.
    XFcLinkedListNode<T> *mPrev;

};


template<class T> XFcLinkedListNode<T> * XFcLinkedListNode<T>::getNext()
{
    return mNext;
}


template<class T> XFcLinkedListNode<T> * XFcLinkedListNode<T>::getPrev()
{
    return mPrev;
}


template<class T> T XFcLinkedListNode<T>::getData() const
{
    return mData;
}


template<class T> T XFcLinkedListNode<T>::setData(const T aNewData)
{
    mData = aNewData;

    return T();
}


template<class T> XFcLinkedListNode<T>::XFcLinkedListNode()
{
//    mData = T();
    mNext = NULL;
    mPrev = NULL;
}


template<class T> XFcLinkedListNode<T>::XFcLinkedListNode(const T &aNewData)
{
    mData = aNewData;
    mNext = NULL;
    mPrev = NULL;
}


#endif // !XFCLINKEDLISTNODE_H_INCLUDED

