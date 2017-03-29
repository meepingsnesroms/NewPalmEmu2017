/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-tree node template 
 * 
 * $Id: XFuNTreeNode.h,v 1.7 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.7 $
 */

#ifndef XFUNTREENODE_H_INCLUDED
#define XFUNTREENODE_H_INCLUDED

template<class T> class XFuNTree;


template<class T> class XFuNTreeNode
{
public:
    //! Returns the amount of allocated child nodes.
    /*!
     * \return Amount of allocated child nodes.
     */
    UINT32 size() const;

    //! Returns information about the validity of the Nth child node.
    /*!
     * \param aIndex Index of child node.
     * \return 1 if the node is not NULL, 0 otherwise.
     */
    INT isValid(const UINT32 aIndex) const;
    
    //! Checks whether the node is a leaf node.
    /*!
     * \return 1 if the node is a leaf node, 0 otherwise.
     */
    INT isLeaf() const;

    //! Returns pointer to Nth child node.
    /*!
     * \return Pointer to the Nth child node.
     */
    XFuNTreeNode<T> * getChild(const UINT32 aIndex);

    //! Sets the internal data of the node.
    /*!
     * \param aNewData Data to be set.
     */
    void setData(const T aNewData);
    
    //! Returns the internal data of the node.
    /*!
     * \return Internal data of the node.
     */
    T getData() const;

    //! Creates an empty node.
    XFuNTreeNode(const UINT32 aChildNodes);
    //! Creates a node with internal data.
    /*!
     * \param aNewData Data to be set.
     */
    XFuNTreeNode(const UINT32 aChildNodes, const T aNewData);

    //! Destructor.
    ~XFuNTreeNode();
    
protected:
    
    UINT32 mIndexInParent;

    UINT32 mChildNodes;
    UINT32 mAllocatedChildNodes;

    T mData;

    XFuNTreeNode<T> *mParent;
    XFuNTreeNode<T> **mChildren;

    friend class XFuNTree<T>;
};


template<class T> UINT32 XFuNTreeNode<T>::size() const
{
    return mAllocatedChildNodes;
}


template<class T> INT XFuNTreeNode<T>::isValid(const UINT32 aIndex) const
{
    if (mChildren[aIndex] != NULL)
        return 1;
    else
        return 0;
}


template<class T> INT XFuNTreeNode<T>::isLeaf() const
{
    UINT32 i;

    for (i = 0; i < mChildNodes; ++i)
    {
        if (mChildren[i] != NULL)
            return 0;
    }

    return 1;
}


template<class T> 
XFuNTreeNode<T> * XFuNTreeNode<T>::getChild(const UINT32 aIndex)
{
    if (aIndex < mChildNodes)
        return mChildren[aIndex];
    else
        return NULL;
}


template<class T> void XFuNTreeNode<T>::setData(const T aNewData)
{
    mData = aNewData;
}


template<class T> T XFuNTreeNode<T>::getData() const
{
    return mData;
}


template<class T> XFuNTreeNode<T>::XFuNTreeNode(const UINT32 aChildNodes)
{
    mParent = NULL;

    mChildNodes = aChildNodes;
    mChildren = new XFuNTreeNode<T> *[aChildNodes];
    mAllocatedChildNodes = 0;

    UINT32 i;
    for (i = 0; i < mChildNodes; ++i)
    {
        mChildren[i] = NULL;
    }
}


template<class T> XFuNTreeNode<T>::XFuNTreeNode(const UINT32 aChildNodes, 
                                                const T aNewData)
{
    mParent = NULL;

    mData = aNewData;
    mChildNodes = aChildNodes;
    mChildren = new XFuNTreeNode<T> *[aChildNodes];
    mAllocatedChildNodes = 0;

    UINT32 i;
    for (i = 0; i < mChildNodes; ++i)
    {
        mChildren[i] = NULL;
    }
}


template<class T> XFuNTreeNode<T>::~XFuNTreeNode()
{
    UINT32 i;
    for (i = 0; i < mChildNodes; ++i)
    {
        delete mChildren[i];
        mAllocatedChildNodes--;
    }

    delete[] mChildren;
}


#endif // !XFUNTREENODE_H_INCLUDED

