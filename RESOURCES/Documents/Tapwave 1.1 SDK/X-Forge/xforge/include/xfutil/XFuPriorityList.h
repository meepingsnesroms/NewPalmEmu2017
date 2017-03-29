/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Priority Linked list template
 * 
 * $Id: XFuPriorityList.h,v 1.8 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.8 $
 */

#ifndef XFUPRIORITYLIST_H_INCLUDED
#define XFUPRIORITYLIST_H_INCLUDED

#include <xfcore/XFcLinkedList.h>
#include <xfutil/XFuPriorityHelp.h>


template<class T> 
class XFuPriorityList : public XFcLinkedList<T>
{
private:
    XFuPriorityHelp *mPriorityHelp;

public:

    //! Constructor.
    XFuPriorityList(XFuPriorityHelp *aPriorityHelp);

    //! Constructor.
    XFuPriorityList();

    //! Virtual destructor.
    virtual ~XFuPriorityList();

    //! Sets priority helper.
    void setPriorityHelp(XFuPriorityHelp *aPriorityHelp);

    //! Add first by priority.
    INT addPriorityFirst(T aNewData);

    //! Add last by priority.
    INT addPriorityLast(T aNewData);

    //! Decreases all priorities.
    void decreasePriorities();

    //! Increases priorities.
    void increasePriorities();

    //! Removes first.
    INT removeFirst();

    //! Remove last.
    INT removeLast();
};


template<class T>
XFuPriorityList<T>::XFuPriorityList()
{
}


template<class T>
XFuPriorityList<T>::XFuPriorityList(
    XFuPriorityHelp *aPriorityHelp) : mPriorityHelp(aPriorityHelp)
{
}


template<class T>
XFuPriorityList<T>::~XFuPriorityList()
{
}


template<class T>
void XFuPriorityList<T>::setPriorityHelp(XFuPriorityHelp *aPriorityHelp)
{
    mPriorityHelp = aPriorityHelp;
}


template <class T>
INT XFuPriorityList<T>::addPriorityFirst(T aNewData)
{
    INT i = 0;

    XFcLinkedList<T>::forwardIterator it;
    T temp;

    for (it = forwardBegin(); it != forwardEnd(); it++)
    {
        temp = it.getValue();
        // +1 is higher and -1 lower 0 is same
        if (mPriorityHelp->priorityCheck(temp, aNewData) > 0)
            break;
        i ++;
    }

    return add(i, aNewData);
}


template <class T>
INT XFuPriorityList<T>::addPriorityLast(T aNewData)
{

    INT i = 0;

    XFcLinkedList<T>::forwardIterator it;
    T temp;

    for (it = forwardBegin(); it != forwardEnd(); it++)
    {
        temp = it.getData();
        // +1 is higher and -1 lower 0 is same
        if (mPriorityHelp->priorityCheck(temp, aNewData) < 0)
            break;
        i ++;
    }

    return add(i, aNewData);
}


template<class T>
void XFuPriorityList<T>::decreasePriorities()
{
    XFcLinkedList<T>::forwardIterator it;
    T temp;

    for (it = forwardBegin(); it != forwardEnd(); it++)
    {
        temp = it.getData();
        mPriorityHelp->decrease(temp);
    }
}


template<class T>
void XFuPriorityList<T>::increasePriorities()
{
    XFcLinkedList<T>::forwardIterator it;
    T temp;

    for (it = forwardBegin(); it != forwardEnd(); it++)
    {
        temp = it.getValue();
        mPriorityHelp->increase(temp);
    }
}


template<class T>
INT XFuPriorityList<T>::removeFirst()
{
    return removeIndex(0);
}


template<class T>
INT XFuPriorityList<T>::removeLast()
{
    return removeIndex(size());
}


#endif // !XFUPRIORITYLIST_H_INCLUDED

