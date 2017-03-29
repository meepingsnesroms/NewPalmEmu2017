/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth device discovery
 *
 * $Id: XFcBtHostResolver.h,v 1.6 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.6 $
 */

#ifndef XFCBTHOSTRESOLVER_H_INCLUDED
#define XFCBTHOSTRESOLVER_H_INCLUDED

#include <xfcore/net/socket/XFcHostResolver.h>
#include <xfcore/XFcLinkedList.h>

class XFcDeviceDiscovery;
class XFcHostEntry;


//! Used to query bluetooth devices. 
/*!
 * Does the asynchronous bluetooth device query. User gives callback interface when device inquiry is started.
 * User is able to cancel query. List of devices are returned if query is succesful and any devices are found. 
 */
class XFCDLLEXPORT XFcBtHostResolver : public XFcHostResolver
{
private:

    //! Holds ptr to device discovery callback object.
    XFcDeviceDiscovery *mDeviceDiscovery;

protected:

    //! Protected constructor.
    XFcBtHostResolver();

    //! Initializes XFcBtHostResolver.
    INT init(INT aType);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtHostResolver();

    //! Static creator for XFcBtHostResolver.
    XFCIMPORT static XFcBtHostResolver * create();

    //! Starts the inquiry request, starts to seach BT devices .
    /*!
     * \param aDeviceDiscovery callback interface for inquiry.
     * \return 1 if query starts succesfully, or 0 if unsuccessful.
     */
    XFCIMPORT INT inquiry(XFcDeviceDiscovery *aDeviceDiscovery);

    //! Cancels the inquiry request.
    XFCIMPORT void cancelInquiry();

    //! Returns inquiry result.
    /*!
     * \param aHostEntry list of host data received from bluetooth network. List is deleted after method call.
     */
    XFCIMPORT void inquiryResult(XFcLinkedList<XFcHostEntry *> &aHostEntry);

};


#endif // !XFCBTHOSTRESOLVER_H_INCLUDED

