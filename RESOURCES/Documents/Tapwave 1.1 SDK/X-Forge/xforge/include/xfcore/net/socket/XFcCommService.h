/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Communication service base
 *
 * $Id: XFcCommService.h,v 1.11 2003/09/17 11:09:57 slehti Exp $
 * $Date: 2003/09/17 11:09:57 $
 * $Revision: 1.11 $
 */

#ifndef XFCCOMMSERVICE_H_INCLUDED
#define XFCCOMMSERVICE_H_INCLUDED

class XFcAdvertiser;
class XFcDeviceDiscovery;
class XFcUUID;


#include <xfcore/XFcLinkedList.h>


//! Base class for communication services. 
/*!
 * Communication service is used to advertice game server or inquiry adveticement from game server.
 */ 
class XFCDLLEXPORT XFcCommService
{

protected:

    //! Holds system specifig interface to services.
    void *mService;

    //! Initializes the XFcCommService.
    /*!
      * \return 1 if successful, or 0 otherwise.
      */
    INT init(void *aService, INT aType);

    //! Protected constructor.
    XFcCommService();
    
    //! Comm service type.
    INT mType;

public:

    // Commservice types
//     enum COMMSERVICE_TYPE
//     {
//         XFCNET_TYPE_INET, // inet
//         XFCNET_TYPE_BT, // bluetooth
//     };

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcCommService();

    //! Gets type of service.
    /*!
     * \return type of service, e.g. XFCNET_TYPE_INET.
     */
    XFCIMPORT INT getType() const;

    //! Device inquiry.
    /*!
     * \param aAdvertise advertise inquiry callback interface.
     * \param aDeviceDiscovery device discovery interface.
     * \return 1 if succesful, or XFCNET_ERROR if unsuccessful.
     */
    XFCIMPORT virtual INT inquiry(const XFcAdvertiser & /*aAdvertise*/,
                                  XFcDeviceDiscovery * /*aDeviceDiscovery*/,
                                  const XFcUUID *aUuid = NULL);

    //! Stops device inquiry.
    XFCIMPORT virtual void cancelInquiry();

    //! Inquiry result.
    /*!
     * \param advertice packet from adverticer.
     */
    XFCIMPORT virtual void inquiryResult(XFcLinkedList<XFcAdvertiser *> &aAdverticePacket);

    //! Starts to advertise service.
    /*!
     * \param aAdvertiser advertise base class.
     * \return 1 if advertise starts succesfully, or 0 otherwise.
     */
    XFCIMPORT virtual INT advertise(const XFcAdvertiser &aAdvertiser, const XFcUUID *aUuid = NULL);


    //! Supports special features for e.g. bt comm service.
    XFCIMPORT virtual INT updateAdvertise(const XFcAdvertiser &aAdvertiser);

    //! Stops advertise service.
    XFCIMPORT virtual void cancelAdvertise();

};


#endif // !XFCCOMMSERVICE_H_INCLUDED

