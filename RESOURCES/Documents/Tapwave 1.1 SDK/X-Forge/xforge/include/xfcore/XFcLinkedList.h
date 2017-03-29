/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcLinkedList.h,v 1.15 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.15 $
 */

#ifndef XFCLINKEDLIST_H_INCLUDED
#define XFCLINKEDLIST_H_INCLUDED

#include <xfcore/XFcLinkedListNode.h>
#include <xfcore/XFcLinkedListAbstractIterator.h>
#include <xfcore/XFcLinkedListForwardIterator.h>
#include <xfcore/XFcLinkedListReverseIterator.h>
#include <xfcore/XFcLinkedListBidirectionalIterator.h>


//! Bidirectional linked list template class.
/*!
 * Example:
 * \code
 * // Create the list
 * XFcLinkedList<UINT32> *list = new XFcLinkedList<UINT32>();
 * list->addLast(1);
 * list->addLast(2);
 * list->addLast(3);
 * list->addLast(4);
 * list->removeIndex(2);
 * // The list now contains items {1, 2, 4}
 * delete list;
 * \endcode
 */
template<class T> class XFcLinkedList
{

public:

    //! Abstract iterator type.
    typedef XFcLinkedListAbstractIterator<T> iterator;
    //! Forward iterator type.
    typedef XFcLinkedListForwardIterator<T> forwardIterator;
    //! Reverse iterator type.
    typedef XFcLinkedListReverseIterator<T> reverseIterator;
    //! Bidirectional iterator type.
    typedef XFcLinkedListBidirectionalIterator<T> bidirectionalIterator;

    //! Returns a forward iterator pointing to the beginning of list.
    forwardIterator forwardBegin() const;

    //! Returns a forward iterator pointing to the end of list.
    forwardIterator forwardEnd() const;

    //! Returns a reverse iterator pointing to the beginning of list.
    reverseIterator reverseBegin() const;

    //! Returns a reverse iterator pointing to the end of list.
    reverseIterator reverseEnd() const;

    //! Returns a bidirectional iterator pointing to the beginning of list.
    bidirectionalIterator bidirectionalBegin() const;

    //! Returns a bidirectional iterator pointing to the end of list.
    bidirectionalIterator bidirectionalEnd() const;


    //! Returns the amount of nodes in the list.
    /*! \note Complexity of this method is O(1).
     */
    UINT32 size() const;


    //! Returns the value of the first node.
    /*! \note Complexity of this method is O(1).
     */
    T getFirst() const;

    //! Returns the value of the last node.
    /*! \note Complexity of this method is O(1).
     */
    T getLast() const;

    //! Adds a new node by index.
    /*! If the list is empty, the node will be added as the first node in the list.
     * \note \note Complexity of this method is O(n).
     * \param aIndex index where the node should be added.
     * \param aNewData value to put in the new node.
     * \return 1 if the addition is successful, 0 otherwise.
     */
    INT add(const UINT32 aIndex, const T aNewData);

    //! Adds a new node to the beginning of list.
    /*! \note Complexity of this method is O(1).
     * \param aNewData value to put in the new node.
     */
    INT addFirst(const T aNewData);

    //! Adds a new node to the end of list.
    /*! If the list is empty, the node will be added as the first node in the list.
     * \note Complexity of this method is O(1).
     * \param aNewData value to put in the new node.
     * \return 1 if the addition is successful, 0 otherwise.
     */
    INT addLast(const T aNewData);

    //! Adds a new node before the node pointed to by an iterator.
    /*! If the list is empty, the node will be added as the first node in the list.
     *  If the iterator is not valid, the operation fails.
     * \note Complexity of this method is O(1).
     * \param aIterator iterator to add the new node before.
     * \param aNewData value to put in the new node.
     * \return 1 if the addition is successful, 0 otherwise.
     */
    INT addBefore(const iterator &aIterator, const T aNewData);

    //! Adds a new node after the node pointed to by an iterator.
    /*! If the list is empty, the node will be added as the first node in the list.
     *  If the iterator is not valid, the operation fails.
     * \note Complexity of this method is O(1).
     * \param aIterator iterator to add the new node after.
     * \param aNewData value to put in the new node.
     * \return 1 if the addition is successful, 0 otherwise.
     */
    INT addAfter(const iterator &aIterator, const T aNewData);


    //! Removes a node by index.
    /*! If the given index is smaller than 0, or bigger than the amount of
     *  nodes in the list, the node will not be removed.
     * \note Complexity of this method is O(n).
     * \param aIndex index of the node to be removed.
     * \return 1 if the removal is successful, 0 otherwise.
     */
    INT removeIndex(const UINT32 aIndex);

    //! Removes a node by value.
    /*! \note Complexity of this method is O(n).
     * \param aData value of the node to be removed.
     * \return 1 if the removal is successful, 0 otherwise.
     */
    INT remove(const T aData);

    //! Removes a node pointed to by an iterator.
    /*! \note Complexity of this method is O(1).
     * \param aIterator iterator to remove the node from.
     * \param aMethod use 0 to make iterator point to the previous node after
     *                removal. Use 1 (default) to make iterator point to the
     *                next node after removal.
     * \return 1 if the removal is successful, 0 otherwise.
     */
    INT remove(iterator &aIterator, const UINT aMethod = 1);

    //! Creates an empty list.
    XFcLinkedList();

    //! Creates an empty list with a number of preallocated nodes.
    /*! \param aPreAlloc number of nodes to preallocate.
     */
    XFcLinkedList(const UINT32 aPreAlloc);

    //! Destructor.
    ~XFcLinkedList();

protected:

    //! Number of nodes in list.
    UINT32 mNodes;

    //! Number of preallocated nodes.
    UINT32 mPreAlloc;

    //! Number of empty preallocated nodes.
    UINT32 mEmptyNodes;


    //! Pointer to the first node in list.
    XFcLinkedListNode<T> *mHead;

    //! Pointer to the last node in list.
    XFcLinkedListNode<T> *mTail;

    //! Pointer to the empty node list, used for faster allocation.
    XFcLinkedListNode<T> *mEmpty;


    //! Preallocates nodes to the empty nodes list.
    void preAlloc();


    //! Puts an empty node into the empty nodes list.
    /*! \param aNode node to add to the list.
     */
    void putEmptyNode(XFcLinkedListNode<T> *aNode);

    //! Returns and removes the first node from the empty nodes list.
    /*! \return empty node.
     */
    XFcLinkedListNode<T> * getEmptyNode();

    //! Removes a node from the list.
    /*! \param aNode pointer to the node to be removed.
     */
    void removeNode(XFcLinkedListNode<T> *aNode);

};


template<class T> void XFcLinkedList<T>::preAlloc()
{
    UINT32 i;

    for (i = 0; i < mPreAlloc; ++i)
    {
        XFcLinkedListNode<T> *newNode = new XFcLinkedListNode<T>();

        if (mEmpty == NULL)
        {
            newNode->mPrev = NULL;
            newNode->mNext = NULL;
            mEmpty = newNode;
        }
        else
        {
            newNode->mPrev = NULL;
            newNode->mNext = mEmpty;
            mEmpty->mPrev = newNode;
            mEmpty = newNode;
        }
    }

    mEmptyNodes = mPreAlloc;
}


template<class T>
void XFcLinkedList<T>::putEmptyNode(XFcLinkedListNode<T> *aNode)
{
    if (mEmpty == NULL)
    {
        aNode->mPrev = NULL;
        aNode->mNext = NULL;
        mEmpty = aNode;
    }
    else
    {
        aNode->mPrev = NULL;
        aNode->mNext = mEmpty;
        mEmpty->mPrev = aNode;
        mEmpty = aNode;
    }

    mEmptyNodes++;
}


template<class T> XFcLinkedListNode<T> * XFcLinkedList<T>::getEmptyNode()
{
    XFcLinkedListNode<T> *emptyNode = NULL;

    if (!(mPreAlloc) || (mEmpty == NULL))
    {
        emptyNode = new XFcLinkedListNode<T>();
    }
    else
    {
        emptyNode = mEmpty;

        if (emptyNode->mNext == NULL)
        {
            mEmpty = NULL;
        }
        else
        {
            emptyNode->mNext->mPrev = NULL;
            mEmpty = emptyNode->mNext;
        }

        mEmptyNodes--;
    }

    return emptyNode;
}


template<class T> void XFcLinkedList<T>::removeNode(XFcLinkedListNode<T> *aNode)
{
    if (aNode != NULL)
    {
        if (aNode == mHead)
        {
            mHead = aNode->mNext;
            if (mHead == NULL)
                mTail = NULL;
            else
                mHead->mPrev = NULL;
        }
        else if (aNode == mTail)
        {
            mTail = aNode->mPrev;
            mTail->mNext = NULL;
        }
        else
        {
            aNode->mPrev->mNext = aNode->mNext;
            aNode->mNext->mPrev = aNode->mPrev;
        }

        mNodes--;

        if (mPreAlloc)
            putEmptyNode(aNode);
        else
            delete aNode;
    }
}


template<class T> typename XFcLinkedList<T>::forwardIterator XFcLinkedList<T>::forwardBegin() const
{
    forwardIterator it(mHead);

    return it;
}


template<class T> typename XFcLinkedList<T>::forwardIterator XFcLinkedList<T>::forwardEnd() const
{
    forwardIterator it(NULL);

    return it;
}


template<class T> typename XFcLinkedList<T>::reverseIterator XFcLinkedList<T>::reverseBegin() const
{
    reverseIterator it(mTail);

    return it;
}


template<class T> typename XFcLinkedList<T>::reverseIterator XFcLinkedList<T>::reverseEnd() const
{
    reverseIterator it(NULL);

    return it;
}


template<class T> 
typename XFcLinkedList<T>::bidirectionalIterator XFcLinkedList<T>::bidirectionalBegin() const
{
    bidirectionalIterator it(mHead);

    return it;
}


template<class T> 
typename XFcLinkedList<T>::bidirectionalIterator XFcLinkedList<T>::bidirectionalEnd() const
{
    bidirectionalIterator it(mTail);

    return it;
}


template<class T> UINT32 XFcLinkedList<T>::size() const
{
    return mNodes;
}


template<class T> T XFcLinkedList<T>::getFirst() const
{
    return mHead->mData;
}


template<class T> T XFcLinkedList<T>::getLast() const
{
    return mTail->mData;
}


template<class T> INT XFcLinkedList<T>::add(const UINT32 aIndex, 
                                            const T aNewData)
{
    if (/*(aIndex >= 0) &&*/ (aIndex <= mNodes))
    {
        if (!mNodes)
        {
            return addFirst(aNewData);
        }
        else
        {
            XFcLinkedListNode<T> *newNode = getEmptyNode();

            if (newNode != NULL)
            {
                newNode->setData(aNewData);

                XFcLinkedListNode<T> *temp = mHead;

                UINT32 i;
                for (i = 0; i < aIndex; ++i)
                {
                    temp = temp->mNext;
                }

                if (temp == mHead)
                {
                    newNode->mNext = mHead;
                    newNode->mPrev = NULL;
                    mHead->mPrev = newNode;
                    mHead = newNode;
                }
                else if (temp == NULL)
                {
                    newNode->mNext = NULL;
                    newNode->mPrev = mTail;
                    mTail->mNext = newNode;
                    mTail = newNode;
                }
                else
                {
                    newNode->mNext = temp;
                    newNode->mPrev = temp->mPrev;
                    temp->mPrev->mNext = newNode;
                    temp->mPrev = newNode;
                }

                mNodes++;

                return 1;
            }
        }
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::addFirst(const T aNewData)
{
    XFcLinkedListNode<T> *newNode = getEmptyNode();

    if (newNode != NULL)
    {
        newNode->setData(aNewData);

        if (!mNodes)
        {
            newNode->mNext = NULL;
            newNode->mPrev = NULL;
            mHead = newNode;
            mTail = newNode;
        }
        else
        {
            newNode->mNext = mHead;
            newNode->mPrev = NULL;
            mHead->mPrev = newNode;
            mHead = newNode;
        }

        mNodes++;

        return 1;
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::addLast(const T aNewData)
{
    XFcLinkedListNode<T> *newNode = getEmptyNode();

    if (newNode != NULL)
    {
        newNode->setData(aNewData);

        if (!mNodes)
        {
            newNode->mNext = NULL;
            newNode->mPrev = NULL;
            mHead = newNode;
            mTail = newNode;
        }
        else
        {
            newNode->mNext = NULL;
            newNode->mPrev = mTail;
            mTail->mNext = newNode;
            mTail = newNode;
        }

        mNodes++;

        return 1;
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::addBefore(const iterator &aIterator, 
                                                  const T aNewData)
{
    if (!mNodes)
    {
        return addFirst(aNewData);
    }
    else if (aIterator.mNode != NULL)
    {
        XFcLinkedListNode<T> *newNode = getEmptyNode();

        if (newNode != NULL)
        {
            newNode->setData(aNewData);

            XFcLinkedListNode<T> *temp = aIterator.mNode;

            if (temp == mHead)
            {
                newNode->mNext = mHead;
                newNode->mPrev = NULL;
                mHead->mPrev = newNode;
                mHead = newNode;
            }
            else
            {
                newNode->mNext = temp;
                newNode->mPrev = temp->mPrev;
                temp->mPrev->mNext = newNode;
                temp->mPrev = newNode;
            }

            mNodes++;

            return 1;
        }
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::addAfter(const iterator &aIterator, 
                                                 const T aNewData)
{
    if (!mNodes)
    {
        return addFirst(aNewData);
    }
    else if (aIterator.mNode != NULL)
    {
        XFcLinkedListNode<T> *newNode = getEmptyNode();

        if (newNode != NULL)
        {
            newNode->setData(aNewData);

            XFcLinkedListNode<T> *temp = aIterator.mNode;

            if (temp == mTail)
            {
                newNode->mPrev = mTail;
                newNode->mNext = NULL;
                mTail->mNext = newNode;
                mTail = newNode;
            }
            else
            {
                newNode->mPrev = temp;
                newNode->mNext = temp->mNext;
                temp->mNext->mPrev = newNode;
                temp->mNext = newNode;
            }

            mNodes++;

            return 1;
        }
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::removeIndex(const UINT32 aIndex)
{
    if (/*(aIndex >= 0) && */(aIndex < mNodes))
    {
        XFcLinkedListNode<T> *temp = mHead;

        UINT32 i;
        for (i = 0; i < aIndex; ++i)
        {
            temp = temp->mNext;
        }

        removeNode(temp);

        return 1;
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::remove(const T aData)
{
    XFcLinkedListNode<T> *temp = mHead;

    UINT32 i;
    for (i = 0; i < mNodes; ++i)
    {
        if (temp != NULL)
        {
            if (temp->mData == aData)
            {
                removeNode(temp);
                return 1;
            }
        }

        temp = temp->mNext;
    }

    return 0;
}


template<class T> INT XFcLinkedList<T>::remove(iterator &aIterator, 
                                               const UINT aMethod)
{
    if (aIterator.mNode != NULL)
    {
        XFcLinkedListNode<T> *temp = aIterator.mNode;
        if (aMethod)
        {
            aIterator.mNode = aIterator.mNode->mNext;
        }
        else
        {
            aIterator.mNode = aIterator.mNode->mPrev;
        }

        removeNode(temp);

        return 1;
    }
    else
        return 0;
}


template<class T> XFcLinkedList<T>::XFcLinkedList()
{
    mNodes = 0;
    mEmptyNodes = 0;
    mPreAlloc = 0;
    mHead = NULL;
    mTail = NULL;
    mEmpty = NULL;
}


template<class T> XFcLinkedList<T>::XFcLinkedList(const UINT32 aPreAlloc)
{
    mNodes = 0;
    mEmptyNodes = 0;
    mPreAlloc = aPreAlloc;
    mHead = NULL;
    mTail = NULL;
    mEmpty = NULL;

    preAlloc();
}


template<class T> XFcLinkedList<T>::~XFcLinkedList()
{

    XFcLinkedListNode<T> *it;
    XFcLinkedListNode<T> *temp;
    UINT32 i;

    it = mHead;
    for (i = 0; i < mNodes; ++i)
    {
        temp = it->mNext;
        delete it;
        it = temp;
    }

    it = mEmpty;
    for (i = 0; i < mEmptyNodes; ++i)
    {
        temp = it->mNext;
        delete it;
        it = temp;
    }
}


#endif // !XFCLINKEDLIST_H_INCLUDED

