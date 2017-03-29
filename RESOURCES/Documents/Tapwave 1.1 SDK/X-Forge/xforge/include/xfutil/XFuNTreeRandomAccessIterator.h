/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-Tree iterator template
 *
 * $Id: XFuNTreeRandomAccessIterator.h,v 1.6 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.6 $
 */

#ifndef XFUNTREERANDOMACCESSITERATOR_H_INCLUDED
#define XFUNTREERANDOMACCESSITERATOR_H_INCLUDED

#include <xfutil/XFuNTreeAbstractIterator.h>

template<class T> class XFuNTree;
template<class T> class XFuNTreeNode;


template<class T> class XFuNTreeRandomAccessIterator : 
public XFuNTreeAbstractIterator<T>
{
public:
    //! Advances to the Nth child node.
    /*!
     * \return Reference to Nth child node.
     */
    XFuNTreeRandomAccessIterator<T> & advance(const UINT32 aChildIndex);
    //! Backs up to parent node.
    /*!
     * \return Reference to parent node.
     */
    XFuNTreeRandomAccessIterator<T> & backup();

    //! Returns an iterator pointing to the Nth child node.
    /*!
     * \return Iterator pointing to the Nth child node if possible, otherwise default iterator.
     */
    XFuNTreeRandomAccessIterator<T> getChild(const UINT32 aIndex) const;

    //! Creates an empty iterator.
    XFuNTreeRandomAccessIterator();
    //! Creates an iterator pointing to a node.
    XFuNTreeRandomAccessIterator(XFuNTreeNode<T> *aNode, 
                                 const UINT32 aChildNodes);
    //! Clones an iterator.
    XFuNTreeRandomAccessIterator(const XFuNTreeAbstractIterator<T> &aClone);
};


template<class T>
XFuNTreeRandomAccessIterator<T> & 
XFuNTreeRandomAccessIterator<T>::advance(const UINT32 aChildIndex)
{
    if (mNode != NULL)
        mNode = mNode->getChild(aChildIndex);

    return *this;
}


template<class T> 
XFuNTreeRandomAccessIterator<T> & XFuNTreeRandomAccessIterator<T>::backup()
{
    if (mNode != NULL)
        mNode = mParent;

    return *this;
}


template<class T> XFuNTreeRandomAccessIterator<T> 
XFuNTreeRandomAccessIterator<T>::getChild(const UINT32 aIndex) const
{
    if (mNode != NULL)
        return XFuNTreeRandomAccessIterator<T>(mNode->getChild(aIndex), mChildNodes);
    else
        return XFuNTreeRandomAccessIterator<T>();
}


template<class T> 
XFuNTreeRandomAccessIterator<T>::XFuNTreeRandomAccessIterator()
{
    mNode = NULL;
}


template<class T> 
XFuNTreeRandomAccessIterator<T>::XFuNTreeRandomAccessIterator(
    XFuNTreeNode<T> *aNode, 
    const UINT32 aChildNodes)
{
    if (aNode != NULL)
    {
        mNode = aNode;
        mChildNodes = aChildNodes;
    }
}


template<class T> 
XFuNTreeRandomAccessIterator<T>::XFuNTreeRandomAccessIterator(
    const XFuNTreeAbstractIterator<T> &aClone) : XFuNTreeAbstractIterator<T>(aClone)
{
}


#endif // !XFUNTREERANDOMACCESSITERATOR_H_INCLUDED

