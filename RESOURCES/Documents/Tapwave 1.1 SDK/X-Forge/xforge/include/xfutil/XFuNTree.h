/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-tree template
 * 
 * $Id: XFuNTree.h,v 1.9 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.9 $
 */

#ifndef XFUNTREE_H_INCLUDED
#define XFUNTREE_H_INCLUDED

#include <xfutil/XFuNTreeNode.h>
#include <xfutil/XFuNTreeAbstractIterator.h>
#include <xfutil/XFuNTreeRandomAccessIterator.h>
#include <xfutil/XFuNTreePreOrderIterator.h>
#include <xfutil/XFuNTreePostOrderIterator.h>


//! Generic N-tree template.
template<class T> class XFuNTree
{
public:
    
    typedef XFuNTreeAbstractIterator<T> iterator;
    typedef XFuNTreeRandomAccessIterator<T> randomAccessIterator;
    typedef XFuNTreePreOrderIterator<T> preOrderIterator;
    typedef XFuNTreePostOrderIterator<T> postOrderIterator;

    //! Returns a random iterator pointing to the root of the tree.
    /*! \return Random iterator pointing to the root of the tree
     */
    randomAccessIterator beginRandomAccess() const;
    
    //! Returns a pre-order iterator pointing to the first node in iteration.
    preOrderIterator beginPreOrder() const;
    
    //! Returns a post-order iterator pointing to the first node in iteration.
    /*! \return PostOrder iterator pointing to the first node in iteration
     */
    postOrderIterator beginPostOrder() const;
    
    //! Returns an iterator pointing to an empty node.
    iterator end() const;

    //! Returns the amount of nodes in the tree.
    /*! \return Amount of nodes in the tree.
     */
    UINT32 size() const;

    //! Adds a new child node to a certain node.
    /*!
     * If the tree is empty, the node will be added as the root.
     * If all child nodes are already reserved, the operation fails.
     * \param aIterator Iterator pointing to the node where the new node should be added as a child.
     * \param aNewData Internal data of the node.
     * \return A valid iterator if the addition succeeds, or an invalid iterator if an error occured.
     */
    iterator add(iterator aIterator, T aNewData);
    
    //! Adds a new child node to a certain node as the Nth child node.
    /*!
     * If the tree is empty, the node will be added as the root.
     * If the Nth node is already reserved, the operation fails.
     * \param aIterator Iterator pointing to the node where the new node should be added as a child.
     * \param aIndex Index to which child node should the new node be created as.
     * \param aNewData Internal data of the node.
     * \return A valid iterator if the addition succeeds, or an invalid iterator if an error occured.
     */
    iterator add(iterator aIterator, const UINT32 aIndex, T aNewData);
    
    //! Inserts new internal data to the Nth child node in a certain node.
    /*!
     * \param aIterator Iterator pointing to the parent node.
     * \param aIndex Index to which child node should the new internal data be inserted to.
     * \param aNewData Internal data of the node.
     * \return 1 if the insertion succeeds, 0 if an error occured.
     */
    INT insert(iterator aIterator, const UINT32 aIndex, T aNewData);
    
    //! Removes a node with the given internal data from the list.
    /*!
     * \param aData Internal data of the node which is to be removed.
     * \return 1 if the removal succeeds, 0 otherwise.
     */
    INT remove(const T aData);
    
    //! Removes a node pointed to by an iterator.
    /*!
     * \param aData Iterator pointing to a node.
     * \return 1 if the removal succeeds, 0 otherwise.
     */
    INT remove(iterator &aIterator);

    //! Creates an empty N-tree.
    /*!
     * \param aChildNodes amount of child nodes per each node.
     */
    XFuNTree(const UINT32 aChildNodes);
    //! Destructor.
    ~XFuNTree();

protected:
    
    //! Number of nodes in tree.
    UINT32 mNodes;

    //! Number of child nodes in each node.
    UINT32 mChildNodes;

    //! Pointer to root node in tree.
    XFuNTreeNode<T> *mRoot;

    //! Removes a node from the tree.
    /*! \param aNode Pointer to the node
     */
    void removeNode(XFuNTreeNode<T> *aNode);
};


template<class T> void XFuNTree<T>::removeNode(XFuNTreeNode<T> *aNode)
{
    if (aNode != NULL)
    {
        UINT32 i;

        for (i = 0; i < mChildNodes; ++i)
        {
            if (aNode->mChildren[i] != NULL)
                removeNode(aNode->mChildren[i]);
        }

        if (aNode->mParent != NULL)
            aNode->mParent->mChildren[aNode->mIndexInParent] = NULL;

        mNodes--;

        delete aNode;
    }
}


template<class T> 
XFuNTree<T>::randomAccessIterator XFuNTree<T>::beginRandomAccess() const
{
    return randomAccessIterator(mRoot, mChildNodes);
}


template<class T> 
XFuNTree<T>::preOrderIterator XFuNTree<T>::beginPreOrder() const
{
    return preOrderIterator(mRoot, mNodes, mChildNodes);
}


template<class T> 
XFuNTree<T>::postOrderIterator XFuNTree<T>::beginPostOrder() const
{
    return postOrderIterator(mRoot, mNodes, mChildNodes);
}


template<class T> UINT32 XFuNTree<T>::size() const
{
    return mNodes;
}


template<class T> XFuNTree<T>::iterator XFuNTree<T>::add(iterator aIterator, 
                                                         const T aNewData)
{
    XFuNTreeNode<T> *node = aIterator.mNode;
    XFuNTreeNode<T> *temp = NULL;

    if ((!mNodes) && (node == NULL))
    {
        temp = new XFuNTreeNode<T>(mChildNodes, aNewData);

        mRoot = temp;
        mNodes++;

        return iterator(temp, mChildNodes);
    }
    else if (aIterator.isValid())
    {
        temp = new XFuNTreeNode<T>(mChildNodes, aNewData);

        UINT32 i;

        while (i < node->mChildNodes)
        {
            if (node->mChildren[i] == NULL)
            {
                temp->mParent = node;
                temp->mIndexInParent = i;
                node->mChildren[i] = temp;
                node->mAllocatedChildNodes++;

                mNodes++;
                break;
            }

            i++;
        }

        return iterator(temp, mChildNodes);
    }

    return iterator(NULL, 0);
}


template<class T> XFuNTree<T>::iterator XFuNTree<T>::add(iterator aIterator, 
                                                         const UINT32 aIndex, 
                                                         const T aNewData)
{
    if (aIterator.isValid())
    {
        XFuNTreeNode<T> *node = aIterator.mNode;
        XFuNTreeNode<T> *temp = NULL;

        if (node->mChildren[aIndex] == NULL)
        {
            temp = new XFuNTreeNode<T>(mChildNodes, aNewData);

            temp->mParent = node;
            temp->mIndexInParent = aIndex;
            node->mChildren[aIndex] = temp;
            node->mAllocatedChildNodes++;

            mNodes++;
        }

        return iterator(temp, mChildNodes);
    }

    return iterator(NULL, 0);
}


template<class T> INT XFuNTree<T>::insert(iterator aIterator, 
                                          const UINT32 aIndex, 
                                          const T aNewData)
{
    if (aIterator.isValid())
    {
        XFuNTreeNode<T> *node = aIterator.mNode;
        
        if (node != NULL)
        {
            if (node->mChildren[aIndex] != NULL)
            {
                node->mChildren[aIndex]->mData = aNewData;

                return 1;
            }
        }
    }

    return 0;
}


template<class T> INT XFuNTree<T>::remove(const T aData)
{
/*
    XFuLinkedListNode<T> *ptr = mHead;

    UINT32 i;
    for (i = 0; i < mNodes; ++i)
    {
        if (ptr != NULL)
        {
            if (ptr->mData == aData)
            {
                removeNode(ptr);
                return 1;
            }
        }

        ptr = ptr->mNext;
    }
*/
    return 0;
}


template<class T> INT XFuNTree<T>::remove(iterator &aIterator)
{
    if (aIterator.mNode != NULL)
    {
        XFuNTreeNode<T> *temp = aIterator.mNode;
        aIterator.backup();

        removeNode(temp);

        return 1;
    }
    else
        return 0;
}


template<class T> XFuNTree<T>::XFuNTree(const UINT32 aChildNodes)
{
    mNodes = 0;
    mRoot = NULL;
    mChildNodes = aChildNodes;
}


template<class T> XFuNTree<T>::~XFuNTree()
{
    if (mRoot != NULL)
        removeNode(mRoot);
}


#endif // !XFUNTREE_H_INCLUDED

