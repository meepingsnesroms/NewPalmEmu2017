/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedListBidirectionalIterator.h,v 1.8 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.8 $
 */

#ifndef XFCLINKEDLISTBIDIRECTIONALITERATOR_H_INCLUDED
#define XFCLINKEDLISTBIDIRECTIONALITERATOR_H_INCLUDED

#include <xfcore/XFcLinkedListAbstractIterator.h>
#include <xfcore/XFcLinkedListBidirectionalIterator.h>
#include <xfcore/XFcLinkedListBidirectionalIterator.h>

template<class T> class XFcLinkedList;
template<class T> class XFcLinkedListNode;


//! Linked list bidirectional iterator template.
template<class T> class XFcLinkedListBidirectionalIterator :
    public XFcLinkedListAbstractIterator<T>
{

public:

    //! Advances to the next node, pre-operation.
    /*! \return reference to next node.
     */
    XFcLinkedListBidirectionalIterator<T> & operator ++ ();

    //! Advances to the next node, post-operation.
    /*! \return next node.
     */
    XFcLinkedListBidirectionalIterator<T> operator ++ (int);

    //! Backs up to the previous node, pre-operation.
    /*! \return reference to previous node.
     */
    XFcLinkedListBidirectionalIterator<T> & operator -- ();

    //! Backs up to the previous node, post-operation.
    /*! \return previous node.
     */
    XFcLinkedListBidirectionalIterator<T> operator -- (int);


    //! Creates an empty iterator.
    XFcLinkedListBidirectionalIterator();

    //! Creates an iterator pointing to a node.
    XFcLinkedListBidirectionalIterator(XFcLinkedListNode<T> *aNode);
};


template<class T>
XFcLinkedListBidirectionalIterator<T> & XFcLinkedListBidirectionalIterator<T>::operator ++ ()
{
    if ((mNode != NULL) && (mNode->getNext() != NULL))
        mNode = mNode->getNext();

    return *this;
}


template<class T>
XFcLinkedListBidirectionalIterator<T> XFcLinkedListBidirectionalIterator<T>::operator ++ (int)
{
    XFcLinkedListBidirectionalIterator<T> newIt = XFcLinkedListBidirectionalIterator<T>(*this);

    if ((mNode != NULL) && (mNode->getNext() != NULL))
        mNode = mNode->getNext();

    return newIt;
}


template<class T>
XFcLinkedListBidirectionalIterator<T> & XFcLinkedListBidirectionalIterator<T>::operator -- ()
{
    if ((mNode != NULL) && (mNode->getPrev() != NULL))
        mNode = mNode->getPrev();

    return *this;
}


template<class T>
XFcLinkedListBidirectionalIterator<T> XFcLinkedListBidirectionalIterator<T>::operator -- (int)
{
    XFcLinkedListBidirectionalIterator<T> newIt = XFcLinkedListBidirectionalIterator<T>(*this);

    if ((mNode != NULL) && (mNode->getPrev() != NULL))
        mNode = mNode->getPrev();

    return newIt;
}


template<class T> XFcLinkedListBidirectionalIterator<T>::XFcLinkedListBidirectionalIterator() :
    XFcLinkedListAbstractIterator<T>()
{
}


template<class T>
XFcLinkedListBidirectionalIterator<T>::XFcLinkedListBidirectionalIterator(XFcLinkedListNode<T> *aNode) :
    XFcLinkedListAbstractIterator<T>(aNode)
{
}


#endif // !XFCLINKEDLISTBIDIRECTIONALITERATOR_H_INCLUDED

