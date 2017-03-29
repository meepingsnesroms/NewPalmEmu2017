/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Client lost interface
 *
 * $Id: XFcClientLost.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */

#ifndef XFCCLIENTLOST_H_INCLUDED
#define XFCCLIENTLOST_H_INCLUDED


//! XFcClientLost is event interface for client lost event.
/*!
 * Client lost is used if RFCOMM connection is lost or inet client 
 * does not receive any data in set time.
 */
class XFCDLLEXPORT XFcClientLost  
{
public:

    //! Connection lost handler.
    /*!
     * \param aClient client number.
     */
    XFCIMPORT virtual void clientLost(INT32 aClient) = 0;

    //! Constructor.
    XFCIMPORT XFcClientLost();

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcClientLost();

};


#endif // !XFCCLIENTLOST_H_INCLUDED

