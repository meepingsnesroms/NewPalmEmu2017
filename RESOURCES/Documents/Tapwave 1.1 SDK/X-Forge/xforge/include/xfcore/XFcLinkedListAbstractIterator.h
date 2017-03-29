/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedListAbstractIterator.h,v 1.7 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.7 $
 */

#ifndef XFCLINKEDLISTABSTRACTITERATOR_H_INCLUDED
#define XFCLINKEDLISTABSTRACTITERATOR_H_INCLUDED

template<class T> class XFcLinkedList;
template<class T> class XFcLinkedListNode;


//! Linked list abstract iterator template.
template<class T> class XFcLinkedListAbstractIterator
{
    friend class XFcLinkedList<T>;

public:
    //! Checks for inequality.
    /*! Tests if two nodes are inequal.
     * \param aRef iterator to test this iterator's value against.
     * \return 1 if inequal, 0 otherwise.
     */
    INT operator != (const XFcLinkedListAbstractIterator &aRef) const;

    //! Checks for equality.
    /*! Tests if two nodes are equal.
     * \param aRef iterator to test this iterator's value against.
     * \return 1 if equal, 0 otherwise.
     */
    INT operator == (const XFcLinkedListAbstractIterator &aRef) const;


    //! Returns information about the validity of the node.
    /*! \return 1 if the node is not NULL, 0 otherwise.
     */
    INT isValid() const;

    //! Returns the value of a node.
    T getData() const;

    //! Sets the value of a node.
    /*! \param aNewData new value for the node.
     * \return Old value if the set was successful, or default value for the
     *         data type if an error occurred.
     */
    T setData(const T aNewData);

protected:

    //! Current node.
    XFcLinkedListNode<T> *mNode;

    //! Creates an empty iterator.
    XFcLinkedListAbstractIterator();

    //! Creates an iterator pointing to a node.
    XFcLinkedListAbstractIterator(XFcLinkedListNode<T> *aNode);

};


template<class T>
INT XFcLinkedListAbstractIterator<T>::operator != (
    const XFcLinkedListAbstractIterator &aRef) const
{
    if (mNode != aRef.mNode)
        return 1;
    else
        return 0;
}


template<class T>
INT XFcLinkedListAbstractIterator<T>::operator == (
    const XFcLinkedListAbstractIterator &aRef) const
{
    if (mNode == aRef.mNode)
        return 1;
    else
        return 0;
}


template<class T> INT XFcLinkedListAbstractIterator<T>::isValid() const
{
    if (mNode != NULL)
        return 1;
    else
        return 0;
}


template<class T> T XFcLinkedListAbstractIterator<T>::getData() const
{
    return mNode->getData();
}


template<class T> T XFcLinkedListAbstractIterator<T>::setData(T aNewData)
{
    if (mNode != NULL)
    {
        return mNode->setData(aNewData);
    }
    else
        return T();
}


template<class T> XFcLinkedListAbstractIterator<T>::XFcLinkedListAbstractIterator()
{
    mNode = NULL;
}


template<class T> 
XFcLinkedListAbstractIterator<T>::XFcLinkedListAbstractIterator(XFcLinkedListNode<T> *aNode)
{
    mNode = aNode;
}


#endif // !XFCLINKEDLISTABSTRACTITERATOR_H_INCLUDED

