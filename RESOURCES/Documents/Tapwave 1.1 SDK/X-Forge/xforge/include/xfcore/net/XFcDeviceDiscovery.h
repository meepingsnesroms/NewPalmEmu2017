/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Device discovery interface
 *
 * $Id: XFcDeviceDiscovery.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCDEVICEDISCOVERY_H_INCLUDED
#define XFCDEVICEDISCOVERY_H_INCLUDED


#include <xfcore/XFcLinkedList.h>

class XFcHostEntry;


//! Interface for device discovery.
class XFcDeviceDiscovery
{
protected:

    XFcDeviceDiscovery() {}

public:

    virtual ~XFcDeviceDiscovery() {}
    
    //! Device discovery is called when device list is received.
    /*!
     * \param aHostEntry hostentry list.
     */
    virtual void deviceDiscovery(const XFcLinkedList<XFcHostEntry *> & /*aHostEntry*/) = 0;

    //! Device discovery is called when device list is received.
    /*!
     * \param aAdvertiser advertiser list.
     */
    virtual void deviceDiscovery(const XFcLinkedList<XFcAdvertiser *> & /*aAdvertiser*/) = 0;

};


#endif // !XFCDEVICEDISCOVERY_H_INCLUDED

