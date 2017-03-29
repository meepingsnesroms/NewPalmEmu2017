/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcAsyncCallBack.h,v 1.6 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.6 $
 */

#ifndef XFCASYNCALLBACK_H_INCLUDED
#define XFCASYNCALLBACK_H_INCLUDED


//! XFcAsyncCallBack is asyncronous callback interface for asyncronous sockets. 
/*!
 * Callbacks are handled with three pure virtual functions. These functions
 * do not give any error status. Error or fail status is given with function call.
 */ 
class XFCDLLEXPORT XFcAsyncCallBack
{
protected:

    //! Constructor.
    XFCIMPORT XFcAsyncCallBack();

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcAsyncCallBack();

    //! Socket action is ready.
    XFCIMPORT virtual void actionReady(INT32 aStatus = 0) = 0;
    //! Socket action failed.
    XFCIMPORT virtual void actionFailed(INT32 aStatus = 0) = 0;
    //! Socket action canceled.
    XFCIMPORT virtual void actionCancel(INT32 aStatus = 0) = 0;
    //! Socket has received some data.
    XFCIMPORT virtual void actionReceive(const CHAR8 *aBuffer, INT32 aBufferSize) = 0;
    //! Socket is ready to send more data
    XFCIMPORT virtual void actionSend(INT32 aStatus = 0) = 0;
    
    
};


#endif // !XFCASYNCALLBACK_H_INCLUDED

