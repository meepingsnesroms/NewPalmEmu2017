/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcObjectDataPriorityHelp.h,v 1.6 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.6 $
 */

#ifndef XFCOBJECTDATAPRIORITYHELP_H_INCLUDED
#define XFCOBJECTDATAPRIORITYHELP_H_INCLUDED

#include <xfcore/XFcPriorityHelp.h>


//! XFcObjectDataPriorityHelp handles priority of XFcObjectDataFrame, it's helpper class.
class XFcObjectDataPriorityHelp : public XFcPriorityHelp
{
public:
    
    //! Constructor.
    XFcObjectDataPriorityHelp();

    //! Virtual destructor.
    virtual ~XFcObjectDataPriorityHelp();

    //! Increases priority.
    /*!
     * \param aData object data frame (XFcObjectDataFrame).
     */
    void increase(void *aData);
    
    //! Decreases priority.
    /*!
     * \param aData object data frame (XFcObjectDataFrame).
     */
    void decrease(void *aData);

    //! Tests priority.
    /*!
     * \param aData1 first object data frame (XFcObjectDataFrame).
     * \param aData2 second object data frame (XFcObjectDataFrame).
     * \return 0 if priorities are the same, -1 if first params priority value is higher, and 1 otherwise.
     */
    INT32 priorityCheck(const void *aData1, const void *aData2) const;

};


#endif // !XFCOBJECTDATAPRIORITYHELP_H_INCLUDED

