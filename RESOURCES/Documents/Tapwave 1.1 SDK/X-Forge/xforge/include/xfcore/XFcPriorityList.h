/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Priority Linked list template.
 * 
 * $Id: XFcPriorityList.h,v 1.10 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.10 $
 */

#ifndef XFCPRIORITYLIST_H_INCLUDED
#define XFCPRIORITYLIST_H_INCLUDED

#include <xfcore/XFcLinkedList.h>
#include <xfcore/XFcPriorityHelp.h>


//! Defines a priority-sorted list.
template<class T> 
class XFcPriorityList : public XFcLinkedList<T>
{

public:

    //! Constructor.
    XFcPriorityList(XFcPriorityHelp *aPriorityHelp);

    //! Constructor.
    XFcPriorityList();

    //! Destructor.
    virtual ~XFcPriorityList();

    //! Sets the priority helper.
    void setPriorityHelp(XFcPriorityHelp *aPriorityHelp);

    //! Adds first by priority.
    INT addPriorityFirst(T aNewData);

    //! Adds last by priority.
    /*! If list holds already object with same priority
     *  the new element is added before the older element. 
     */
    INT addPriorityLast(T aNewData);

    //! Decreases all priorities.
    void decreasePriorities();

    //! Increases priorities.
    void increasePriorities();

    //! Removes first.
    INT removeFirst();

    //! Removes last.
    INT removeLast();

private:

    //! Priority help.
    /*! \internal
     */
    XFcPriorityHelp *mPriorityHelp;

};


template<class T>
XFcPriorityList<T>::XFcPriorityList() : mPriorityHelp(NULL)
{
}


template<class T>
XFcPriorityList<T>::XFcPriorityList(XFcPriorityHelp *aPriorityHelp) : mPriorityHelp(aPriorityHelp)
{
}


template<class T>
XFcPriorityList<T>::~XFcPriorityList()
{
}


template<class T>
void XFcPriorityList<T>::setPriorityHelp(XFcPriorityHelp *aPriorityHelp)
{
    mPriorityHelp = aPriorityHelp;
}


template <class T>
INT XFcPriorityList<T>::addPriorityFirst(T aNewData)
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
INT XFcPriorityList<T>::addPriorityLast(T aNewData)
{
    INT i = 0;

    XFcLinkedList<T>::forwardIterator it;
    T temp;

    for (it = forwardBegin(); it != forwardEnd(); it++)
    {
        temp = it.getData();
        INT32 out = 0;
        // +1 is higher and -1 lower 0 is same
        if ((out = mPriorityHelp->priorityCheck(temp, aNewData)) < 0 /*|| out == 0*/)
            break;
        i ++;
    }

    return add(i, aNewData);
}


template<class T>
void XFcPriorityList<T>::decreasePriorities()
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
void XFcPriorityList<T>::increasePriorities()
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
INT XFcPriorityList<T>::removeFirst()
{
    return removeIndex(0);
}


template<class T>
INT XFcPriorityList<T>::removeLast()
{
    return removeIndex(size());
}


#endif // !XFCPRIORITYLIST_H_INCLUDED

