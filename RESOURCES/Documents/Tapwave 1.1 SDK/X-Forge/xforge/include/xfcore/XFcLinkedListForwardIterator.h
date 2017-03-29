/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedListForwardIterator.h,v 1.8 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.8 $
 */

#ifndef XFCLINKEDLISTFORWARDITERATOR_H_INCLUDED
#define XFCLINKEDLISTFORWARDITERATOR_H_INCLUDED

#include <xfcore/XFcLinkedListAbstractIterator.h>

template<class T> class XFcLinkedList;
template<class T> class XFcLinkedListNode;


//! Linked list forward iterator template.
template<class T> class XFcLinkedListForwardIterator :
    public XFcLinkedListAbstractIterator<T>
{

public:

    //! Advances to the next node, pre-operation.
    /*! \return reference to next node.
     */
    XFcLinkedListForwardIterator<T> & operator ++ ();

    //! Advances to the next node, post-operation.
    /*! \return next node.
     */
    XFcLinkedListForwardIterator<T> operator ++ (int);

    //! Creates an empty iterator.
    XFcLinkedListForwardIterator();

    //! Creates an iterator pointing to a node.
    XFcLinkedListForwardIterator(XFcLinkedListNode<T> *aNode);
};


template<class T>
XFcLinkedListForwardIterator<T> & XFcLinkedListForwardIterator<T>::operator ++ ()
{
    if (mNode != NULL) mNode = mNode->getNext();

    return *this;
}


template<class T>
XFcLinkedListForwardIterator<T> XFcLinkedListForwardIterator<T>::operator ++ (int)
{
    XFcLinkedListForwardIterator<T> newIt = XFcLinkedListForwardIterator<T>(*this);

    if (mNode != NULL) mNode = mNode->getNext();

    return newIt;
}


template<class T> XFcLinkedListForwardIterator<T>::XFcLinkedListForwardIterator()/* :
    XFcLinkedListAbstractIterator<T>()*/
{
    mNode = NULL;
}


template<class T>
XFcLinkedListForwardIterator<T>::XFcLinkedListForwardIterator(XFcLinkedListNode<T> *aNode)/* :
    XFcLinkedListAbstractIterator<T>(aNode)*/
{
    mNode = aNode;
}


#endif // !XFCLINKEDLISTFORWARDITERATOR_H_INCLUDED

