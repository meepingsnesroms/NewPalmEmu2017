/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief N-Tree abstract iterator template
 *
 * $Id: XFuNTreeAbstractIterator.h,v 1.5 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.5 $
 */

#ifndef XFUNTREEABSTRACTITERATOR_H_INCLUDED
#define XFUNTREEABSTRACTITERATOR_H_INCLUDED

template<class T> class XFuNTree;
template<class T> class XFuNTreeNode;


template<class T> class XFuNTreeAbstractIterator
{
public:
    
    //! Checks if the nodes pointed by two iterators are inequal.
    /*! \return 1 if inequal, 0 otherwise.
     */
    INT operator!=(const XFuNTreeAbstractIterator &aRef) const;
    
    //! Checks if the nodes pointed by two iterators are equal.
    /*! \return 1 if equal, 0 otherwise.
     */
    INT operator==(const XFuNTreeAbstractIterator &aRef) const;

    //! Returns the amount of allocated child nodes.
    /*! \return Amount of allocated child nodes, 0 if node is not valid
     */
    UINT32 size() const;

    //! Returns information about the validity of the node.
    /*! \return 1 if the node is valid, 0 otherwise.
     */
    INT isValid() const;
    
    //! Returns information about the validity of the Nth child node.
    /*!
     * \param aIndex Index of child node.
     * \return 1 if the node is valid, 0 otherwise.
     */
    INT isValid(const UINT32 aIndex) const;
    
    //! Checks whether the node is a leaf node.
    /*! \return 1 if the node is a leaf node, 0 otherwise
     */
    INT isLeaf() const;
    
    //! Sets the internal data of a node.
    /*! \return 1 if the addition succeeded, 0 if an error occured
     */
    INT setData(T aNewData);
    
    //! Returns the internal data of a node.
    /*!
     * \return Internal data of a node
     */
    T getData() const;

protected:
    
    //! Number of child nodes in each node.
    UINT32 mChildNodes;

    //! Current node.
    XFuNTreeNode<T> *mNode;

    //! Creates an empty iterator.
    XFuNTreeAbstractIterator();
    //! Creates an iterator pointing to a node.
    XFuNTreeAbstractIterator(XFuNTreeNode<T> *aNode, const UINT32 aChildNodes);

    friend class XFuNTree<T>;
};


template<class T> 
INT XFuNTreeAbstractIterator<T>::operator!=(const XFuNTreeAbstractIterator &aRef) const
{
    if (mNode != aRef.mNode)
        return 1;
    else
        return 0;
}


template<class T> 
INT XFuNTreeAbstractIterator<T>::operator==(const XFuNTreeAbstractIterator &aRef) const
{
    if (mNode == aRef.mNode)
        return 1;
    else
        return 0;
}


template<class T> UINT32 XFuNTreeAbstractIterator<T>::size() const
{
    if (mNode != NULL)
        return mNode->size();
    else
        return 0;
}


template<class T> INT XFuNTreeAbstractIterator<T>::isValid() const
{
    if (mNode != NULL)
        return 1;
    else
        return 0;
}


template<class T> 
INT XFuNTreeAbstractIterator<T>::isValid(const UINT32 aIndex) const
{
    if (mNode != NULL)
        return mNode->isValid(aIndex);
    else
        return 0;
}


template<class T> INT XFuNTreeAbstractIterator<T>::isLeaf() const
{
    if (mNode != NULL)
        return mNode->isLeaf();
    else
        return 0;
}


template<class T> INT XFuNTreeAbstractIterator<T>::setData(T aNewData)
{
    if (mNode != NULL)
    {
        mNode->setData(aNewData);
        return 1;
    }
    else
        return 0;
}


template<class T> T XFuNTreeAbstractIterator<T>::getData() const
{
    return mNode->getData();
}


template<class T> XFuNTreeAbstractIterator<T>::XFuNTreeAbstractIterator()
{
    mNode = NULL;
    mChildNodes = 0;
}


template<class T> XFuNTreeAbstractIterator<T>::XFuNTreeAbstractIterator(XFuNTreeNode<T> *aNode, 
                                                      const UINT32 aChildNodes)
{
    mNode = aNode;
    mChildNodes = aChildNodes;
}


#endif // !XFUNTREEABSTRACTITERATOR_H_INCLUDED

