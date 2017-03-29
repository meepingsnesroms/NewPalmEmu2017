/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * $Id: XFcClientInetCommWinPriHelp.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCCLIENTINETCOMMWINPRIHELP_H_INCLUDED
#define XFCCLIENTINETCOMMWINPRIHELP_H_INCLUDED

#include <xfcore/XFcPriorityHelp.h>


//! XFcClientInetCommWinPriHelp is created for priority helpper to change inet clients priority.
/*!
 * Its task is to increase or decrease inet clients priorities if they are not able to send data. 
 */
class XFCDLLEXPORT XFcClientInetCommWinPriHelp : public XFcPriorityHelp
{

public:

    //! Constructor.
    XFcClientInetCommWinPriHelp();

    //! Virtual destructor.
    virtual ~XFcClientInetCommWinPriHelp();
    
    //! Increases priority.
    /*!
     * \param aData inet client window.
     */
    void increase(void *aData);

    //! Decreases priority.
    /*!
     * \param aData inet client window.
     */
    void decrease(void *aData);
    
    //! Tests priority.
    /*!
     * \param aData1 first inet client window.
     * \param aData2 second inet client window.
     * \return 0 if priorities are the same, -1 if first params priority value is higher, and 1 otherwise.
     */
    INT32 priorityCheck(const void *aData1, const void *aData2) const;

};


#endif // !XFECLIENTINETCOMMWINPRIHELP_H_INCLUDED

