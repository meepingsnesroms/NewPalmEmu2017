/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Priority linked list help
 * 
 * $Id: XFcPriorityHelp.h,v 1.6 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.6 $
 */

#ifndef XFUPRIORITYHELP_H_INCLUDED
#define XFUPRIORITYHELP_H_INCLUDED



//! Helper class for priority-sorted list.
/*! \internal
 */
class XFCDLLEXPORT XFcPriorityHelp
{
public:
    XFcPriorityHelp();
    virtual ~XFcPriorityHelp();

    virtual void increase(void *aData) = 0;
    virtual void decrease(void *aData) = 0;
    virtual INT32 priorityCheck(const void *aCompare1,
                                const void *aCompare2) const = 0;
};


#endif // !XFUPRIORITYHELP_H_INCLUDED

