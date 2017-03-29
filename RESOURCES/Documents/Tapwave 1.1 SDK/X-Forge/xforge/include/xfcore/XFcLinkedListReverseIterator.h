/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedListReverseIterator.h,v 1.7 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.7 $
 */

#ifndef XFCLINKEDLISTREVERSEITERATOR_H_INCLUDED
#define XFCLINKEDLISTREVERSEITERATOR_H_INCLUDED

#include <xfcore/XFcLinkedListAbstractIterator.h>

template<class T> class XFcLinkedList;
template<class T> class XFcLinkedListNode;


//! Linked list reverse iterator template.
template<class T> class XFcLinkedListReverseIterator :
    public XFcLinkedListAbstractIterator<T>
{

public:

    //! Backs up to the previous node, pre-operation.
    /*! \return reference to previous node.
     */
    XFcLinkedListReverseIterator<T> & operator -- ();

    //! Backs up to the previous node, post-operation.
    /*! \return previous node.
     */
    XFcLinkedListReverseIterator<T> operator -- (int);

    //! Creates an empty iterator.
    XFcLinkedListReverseIterator();

    //! Creates an iterator pointing to a node.
    XFcLinkedListReverseIterator(XFcLinkedListNode<T> *aNode);
};


template<class T>
XFcLinkedListReverseIterator<T> & XFcLinkedListReverseIterator<T>::operator -- ()
{
    if (mNode != NULL) mNode = mNode->getPrev();

    return *this;
}


template<class T>
XFcLinkedListReverseIterator<T> XFcLinkedListReverseIterator<T>::operator -- (int)
{
    XFcLinkedListReverseIterator<T> newIt = XFcLinkedListReverseIterator<T>(*this);

    if (mNode != NULL) mNode = mNode->getPrev();

    return newIt;
}


template<class T> XFcLinkedListReverseIterator<T>::XFcLinkedListReverseIterator() :
    XFcLinkedListAbstractIterator<T>()
{
}


template<class T>
XFcLinkedListReverseIterator<T>::XFcLinkedListReverseIterator(XFcLinkedListNode<T> *aNode) :
    XFcLinkedListAbstractIterator<T>(aNode)
{
}


#endif // !XFCLINKEDLISTREVERSEITERATOR_H_INCLUDED

