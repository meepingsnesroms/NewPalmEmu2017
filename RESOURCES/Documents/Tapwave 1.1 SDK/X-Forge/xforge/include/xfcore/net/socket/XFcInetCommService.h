/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet advertiser and advertise discovery
 *
 * $Id: XFcInetCommService.h,v 1.11 2003/09/17 11:14:15 slehti Exp $
 * $Date: 2003/09/17 11:14:15 $
 * $Revision: 1.11 $
 */

#ifndef XFCINETCOMMSERVICE_H_INCLUDED
#define XFCINETCOMMSERVICE_H_INCLUDED

#include <xfcore/net/socket/XFcCommService.h>


//! Used to inquiry and advertice game server/s.
/*!
 * Creates broadcast socket and is able to advertice server on lan network.
 * \todo implementation.
 */
class XFCDLLEXPORT XFcInetCommService : public XFcCommService
{
private:

    XFcDeviceDiscovery *mDiscovery;

protected:
    
    //! Protected constructor.
    XFcInetCommService();

    //! Initializes XFcInetCommService.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT init();

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcInetCommService();

    //! Static constructor.
    XFCIMPORT static XFcInetCommService * create();

    //! Server advertise query.
    /*!
     * \param aAdvertise advertise inquiry callback interface.
     * \param aDeviceDiscovery device discovery interface.
     * \return 1 if succesful, or XFCNET_ERROR if unsuccessful.
     */
    XFCIMPORT virtual INT inquiry(const XFcAdvertiser &aAdvertise, XFcDeviceDiscovery * /*aDeviceDiscovery*/, const XFcUUID *aUuid = NULL);


    XFCIMPORT virtual void inquiryResult(XFcLinkedList<XFcAdvertiser *> &aAdverticePacket);

    //! Stops device inquiry.
    XFCIMPORT virtual void cancelInquiry();

    //! Starts advertise service.
    /*!
     * \param aAdvertiser advertiser packet.
     * \return 1 if advertise starts succesfully, or 0 otherwise.
     */
    XFCIMPORT virtual INT advertise(const XFcAdvertiser &aAdvertiser, const XFcUUID *aUuid = NULL);

    XFCIMPORT virtual INT updateAdvertise(const XFcAdvertiser &aAdvertiser);
    
    //! Stops advertise service.
    XFCIMPORT virtual void cancelAdvertise();

};


#endif // !XFCINETCOMMSERVICE_H_INCLUDED

