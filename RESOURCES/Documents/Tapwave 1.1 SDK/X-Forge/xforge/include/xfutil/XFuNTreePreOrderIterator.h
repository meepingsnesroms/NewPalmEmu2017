/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-Tree pre-order iterator template
 *
 * $Id: XFuNTreePreOrderIterator.h,v 1.7 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.7 $
 */

#ifndef XFUNTREEPREORDERITERATOR_H_INCLUDED
#define XFUNTREEPREORDERITERATOR_H_INCLUDED

#include <xfutil/XFuNTreeAbstractIterator.h>
#include <xfutil/XFuDynamicArray.h>

template<class T> class XFuNTree;
template<class T> class XFuNTreeNode;


template<class T> class XFuNTreePreOrderIterator : public XFuNTreeAbstractIterator<T>
{

public:
    //! Assignment operator overload.
    void operator=(const XFuNTreePreOrderIterator &aClone);

    //! Advances to the next node, pre-operation.
    /*!
     * \return Reference to next node.
     */
    XFuNTreePreOrderIterator<T> & operator++();
    //! Advances to the next node, post-operation.
    /*!
     * \return Next node.
     */
    XFuNTreePreOrderIterator<T> operator++(int);

    //! Creates an empty iterator.
    XFuNTreePreOrderIterator();
    //! Creates an iterator pointing to a node.
    XFuNTreePreOrderIterator(XFuNTreeNode<T> *aNode, const UINT32 aNodes, 
                             const UINT32 aChildNodes);
    //! Clones an iterator.
    XFuNTreePreOrderIterator(const XFuNTreePreOrderIterator<T> &aClone);

    //! Destructor.
    ~XFuNTreePreOrderIterator();

protected:
    
    //! Number of nodes in tree.
    UINT32 mNodes;

    //! Stack used for saving pointers to unvisited nodes.
    XFuDynamicArray<XFuNTreeNode<T> *> *mStack;
};


template<class T>
void XFuNTreePreOrderIterator<T>::operator=(const XFuNTreePreOrderIterator &aClone)
{
    mNode = aClone.mNode;
    mNodes = aClone.mNodes;
    mChildNodes = aClone.mChildNodes;

    if (aClone.mStack != NULL)
    {
        if (mStack == NULL)
            mStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(
                aClone.mStack->maxSize());

        if (mStack == NULL)
        {
            mNode = NULL;
            mNodes = 0;
            mChildNodes = 0;
            return;
        }      

        UINT32 i, lastElement;
        XFuNTreeNode<T> *temp = NULL;

        lastElement = aClone.mStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            temp = aClone.mStack->get(i);
            mStack->put(i, temp);
        }
    }
    else
    {
        if (mStack != NULL)
        {
            delete mStack;
            mStack = NULL;
        }
    }
}


template<class T>
XFuNTreePreOrderIterator<T> & XFuNTreePreOrderIterator<T>::operator++()
{
    if (!mStack->isEmpty())
    {
        mNode = mStack->remove();

        INT32 i;
        for (i = (mChildNodes - 1); i >= 0; --i)
        {
            if (mNode->isValid(i))
                mStack->put(mNode->getChild(i));
        }
    }

    return *this;
}


template<class T>
XFuNTreePreOrderIterator<T> XFuNTreePreOrderIterator<T>::operator++(int)
{
    XFuNTreePreOrderIterator<T> newIt = XFuNTreePreOrderIterator<T>(*this);

/*
    if (mNode != NULL) mNode = mNode->mNext;

    return newIt;
*/
}


template<class T> XFuNTreePreOrderIterator<T>::XFuNTreePreOrderIterator()
{
    mNode = NULL;
    mNodes = 0;
    mStack = NULL;
}


template<class T> 
XFuNTreePreOrderIterator<T>::XFuNTreePreOrderIterator(XFuNTreeNode<T> *aNode,
                                                      const UINT32 aNodes,
                                                      const UINT32 aChildNodes)
{
    if (aNode != NULL)
    {
        mNode = aNode;
        mNodes = aNodes;
        mChildNodes = aChildNodes;

        mStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(aNodes);
        if (mStack == NULL)
        {
            mNode = NULL;
            mNodes = 0;
            mChildNodes = 0;
        }
        else
        {
            INT32 i;
            for (i = (mChildNodes - 1); i >= 0; --i)
            {
                if (mNode->isValid(i))
                    mStack->put(mNode->getChild(i));
            }
        }
    }
}


template<class T> 
XFuNTreePreOrderIterator<T>::XFuNTreePreOrderIterator(
    const XFuNTreePreOrderIterator<T> &aClone)
{
    mNode = aClone.mNode;

    if (aClone.mStack != NULL)
    {
        if (mStack == NULL)
        {
            mStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(
                aClone.mStack->maxSize());

            if (mStack == NULL)
            {
                mNode = NULL;
                mNodes = 0;
                mChildNodes = 0;
                return;
            }
        }

        UINT32 i, lastElement;
        XFuNTreeNode<T> *temp = NULL;

        lastElement = aClone.mStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            temp = aClone.mStack->get(i);
            mStack->put(i, temp);
        }
    }
    else
    {
        delete mStack;
        mStack = NULL;
    }
}


template<class T>
XFuNTreePreOrderIterator<T>::~XFuNTreePreOrderIterator()
{
    delete mStack;
}


#endif // !XFUNTREEPREORDERITERATOR_H_INCLUDED

