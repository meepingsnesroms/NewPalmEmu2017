/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-Tree post-order iterator template
 *
 * $Id: XFuNTreePostOrderIterator.h,v 1.7 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.7 $
 */

#ifndef XFUNTREEPOSTORDERITERATOR_H_INCLUDED
#define XFUNTREEPOSTORDERITERATOR_H_INCLUDED

#include <xfutil/XFuNTreeAbstractIterator.h>
#include <xfutil/XFuDynamicArray.h>

template<class T> class XFuNTree;
template<class T> class XFuNTreeNode;


template<class T> class XFuNTreePostOrderIterator : public XFuNTreeAbstractIterator<T>
{
public:
    
    //! Assignment operator overload.
    void operator=(const XFuNTreePostOrderIterator &aClone);

    //! Advances to the next node, pre-operation.
    /*!
     * \return Reference to next node.
     */
    XFuNTreePostOrderIterator<T> & operator++();
    
    //! Advances to the next node, post-operation.
    /*!
     * \return Next node.
     */
    XFuNTreePostOrderIterator<T> operator++(int);

    //! Creates an empty iterator.
    XFuNTreePostOrderIterator();
    //! Creates an iterator pointing to a node.
    XFuNTreePostOrderIterator(XFuNTreeNode<T> *aNode, const UINT32 aNodes, 
        const UINT32 aChildNodes);
    //! Clones an iterator.
    XFuNTreePostOrderIterator(const XFuNTreePostOrderIterator<T> &aClone);

    //! Destructor.
    ~XFuNTreePostOrderIterator();
    
protected:
    
    //! Number of nodes in tree.
    UINT32 mNodes;

    //! Stack used for saving pointers to nodes.
    XFuDynamicArray<XFuNTreeNode<T> *> *mNodeStack;
    //! Stack used for saving information on visitation of node.
    XFuDynamicArray<INT> *mBoolStack;
};


template<class T>
void XFuNTreePostOrderIterator<T>::operator=(
    const XFuNTreePostOrderIterator &aClone)
{
    mNode = aClone.mNode;
    mNodes = aClone.mNodes;
    mChildNodes = aClone.mChildNodes;

    if ((aClone.mNodeStack != NULL) && (aClone.mBoolStack != NULL))
    {
        if (mNodeStack == NULL)
            mNodeStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(
                aClone.mNodeStack->maxSize());

        if (mBoolStack == NULL)
            mBoolStack = XFuDynamicArray<INT>::create(
                aClone.mBoolStack->maxSize());

        if ((mNodeStack == NULL) || (mBoolStack == NULL))
        {
            mNode = NULL;
            mNodes = 0;
            mChildNodes = 0;
            return;
        }

        UINT32 i, lastElement;
        XFuNTreeNode<T> *temp = NULL;
        INT boolTemp;

        lastElement = aClone.mNodeStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            temp = aClone.mNodeStack->get(i);
            mNodeStack->put(i, temp);
        }

        lastElement = aClone.mBoolStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            boolTemp = aClone.mBoolStack->get(i);
            mBoolStack->put(i, boolTemp);
        }
    }
    else
    {
        if (mNodeStack != NULL)
        {
            delete mNodeStack;
            mNodeStack = NULL;
        }

        if (mBoolStack != NULL)
        {
            delete mBoolStack;
            mBoolStack = NULL;
        }
    }
}


template<class T>
XFuNTreePostOrderIterator<T> & XFuNTreePostOrderIterator<T>::operator++()
{
    if (!mNodeStack->isEmpty())
    {
        mNode = mNodeStack->remove();
        INT temp = mBoolStack->remove();

        if (!temp)
        {
            UINT32 i, j;

            while (!mNode->isLeaf())
            {
                mNodeStack->put(mNode);
                mBoolStack->put(1);

                for (j = 0; j < mChildNodes; ++j)
                {
                    if (mNode->isValid(j))
                    {
                        for (i = (mChildNodes - 1); i > j; --i)
                        {
                            if (mNode->isValid(i))
                            {
                                mNodeStack->put(mNode->getChild(i));
                                mBoolStack->put(0);
                            }
                        }

                        mNode = mNode->getChild(j);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        mNode = NULL;
    }

    return *this;
}


template<class T>
XFuNTreePostOrderIterator<T> XFuNTreePostOrderIterator<T>::operator++(int)
{
    XFuNTreePostOrderIterator<T> newIt = XFuNTreePostOrderIterator<T>(*this);

/*
    if (mNode != NULL) mNode = mNode->mNext;

    return newIt;
*/
}


template<class T> XFuNTreePostOrderIterator<T>::XFuNTreePostOrderIterator()
{
    mNode = NULL;
    mNodes = 0;
    mChildNodes = 0;
    mNodeStack = NULL;
    mBoolStack = NULL;
}


template<class T> 
XFuNTreePostOrderIterator<T>::XFuNTreePostOrderIterator(XFuNTreeNode<T> *aNode,
                                                        const UINT32 aNodes,
                                                        const UINT32 aChildNodes)
{
    if (aNode != NULL)
    {
        mNode = aNode;
        mNodes = aNodes;
        mChildNodes = aChildNodes;

        mNodeStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(aNodes);
        mBoolStack = XFuDynamicArray<INT>::create(aNodes);

        if ((mNodeStack == NULL) || (mBoolStack == NULL))
        {
            mNode = NULL;
            mNodes = 0;
            mChildNodes = 0;
        }
        else
        {
            UINT32 i, j;

            while (!mNode->isLeaf())
            {
                mNodeStack->put(mNode);
                mBoolStack->put(1);

                for (j = 0; j < mChildNodes; ++j)
                {
                    if (mNode->isValid(j))
                    {
                        for (i = (mChildNodes - 1); i > j; --i)
                        {
                            if (mNode->isValid(i))
                            {
                                mNodeStack->put(mNode->getChild(i));
                                mBoolStack->put(0);
                            }
                        }

                        mNode = mNode->getChild(j);
                        break;
                    }
                }
            }
        }
    }
}


template<class T> 
XFuNTreePostOrderIterator<T>::XFuNTreePostOrderIterator(
    const XFuNTreePostOrderIterator<T> &aClone)
{
    mNode = aClone.mNode;
    mNodes = aClone.mNodes;
    mChildNodes = aClone.mChildNodes;

    if ((aClone.mNodeStack != NULL) && (aClone.mBoolStack != NULL))
    {
        if (mNodeStack == NULL)
            mNodeStack = XFuDynamicArray<XFuNTreeNode<T> *>::create(
                aClone.mNodeStack->maxSize());

        if (mBoolStack == NULL)
            mBoolStack = XFuDynamicArray<INT>::create(
                aClone.mBoolStack->maxSize());

        if ((mNodeStack == NULL) || (mBoolStack == NULL))
        {
            mNode = NULL;
            mNodes = 0;
            mChildNodes = 0;
            return;
        }

        UINT32 i, lastElement;
        XFuNTreeNode<T> *temp = NULL;
        INT boolTemp = NULL;

        lastElement = aClone.mNodeStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            temp = aClone.mNodeStack->get(i);
            mNodeStack->put(i, temp);
        }

        lastElement = aClone.mBoolStack->size();
        for (i = 0; i < lastElement; ++i)
        {
            boolTemp = aClone.mBoolStack->get(i);
            mBoolStack->put(i, boolTemp);
        }
    }
    else
    {
        delete mNodeStack;
        delete mBoolStack;
        mNodeStack = NULL;
        mBoolStack = NULL;
    }
}


template<class T>
XFuNTreePostOrderIterator<T>::~XFuNTreePostOrderIterator()
{
    delete mNodeStack;
    delete mBoolStack;
}


#endif // !XFUNTREEPOSTORDERITERATOR_H_INCLUDED

