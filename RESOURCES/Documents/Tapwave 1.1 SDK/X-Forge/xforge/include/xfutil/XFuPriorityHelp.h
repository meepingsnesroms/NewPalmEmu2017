/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Priority linked list help
 * 
 * $Id: XFuPriorityHelp.h,v 1.5 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.5 $
 */

#ifndef XFUPRIORITYHELP_H_INCLUDED
#define XFUPRIORITYHELP_H_INCLUDED


class XFuPriorityHelp
{
public:
    XFuPriorityHelp();
    virtual ~XFuPriorityHelp();

    virtual void increase(void *aData) = 0;
    virtual void decrease(void *aData) = 0;
    virtual INT32 priorityCheck(const void *aCompare1,
                                const void *aCompare2) const = 0;
};


#endif // !XFUPRIORITYHELP_H_INCLUDED

