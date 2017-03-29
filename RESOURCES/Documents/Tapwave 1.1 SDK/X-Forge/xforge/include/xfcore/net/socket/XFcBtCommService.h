/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth advertiser and advertise inquiry
 *
 * $Id: XFcBtCommService.h,v 1.14 2003/10/02 11:43:01 slehti Exp $
 * $Date: 2003/10/02 11:43:01 $
 * $Revision: 1.14 $
 */

#ifndef XFCBTCOMMSERVICE_H_INCLUDED
#define XFCBTCOMMSERVICE_H_INCLUDED

#include <xfcore/net/socket/XFcCommService.h>
#include <xfcore/XFcLinkedList.h>

class XFcAddress;
class XFcHostEntry;
class XFcAdvertiser;
class XFcDeviceDiscovery;
class XFcUUID;


//! Used to inquiry and advertise bluetooth services.
class XFCDLLEXPORT XFcBtCommService : public XFcCommService
{
private:

    //! Holds device discovery interface pointer.
    XFcDeviceDiscovery *mDeviceDiscovery;

protected:
    
    //! Protected constructor.
    XFCIMPORT XFcBtCommService();
    
    //! Initializes the XFcBtCommService.
    /*!
      * \return INT is 1 if success else 0
      */
    XFCIMPORT INT init();

public:

    //! Static constructor.
    /*!
     * \return pointer to XFcBtCommService class if success else NULL
     */
    XFCIMPORT static XFcBtCommService * create();

    //! Starts the inquiry request for available bt services using SDP.
    XFCIMPORT virtual INT inquiry(const XFcAdvertiser &aAdvertise, XFcDeviceDiscovery *aDeviceDiscovery, const XFcUUID *aUuid);
    
    //! Cancels the inquiry request.
    XFCIMPORT virtual void cancelInquiry();
    
    //! Returns inquiry result.
    /*!
     * \param aAdvertisePacket list of host data received from bluetooth network. List is deleted after method call.
     */
    XFCIMPORT virtual void inquiryResult(XFcLinkedList<XFcAdvertiser *> &aAdvertisePacket);

    //! Starts to advertise service.
    /*!
     * \param aAdvertiser advertise base class.
     * \return 1 if advertise starts succesfully else 0.
     */
    XFCIMPORT virtual INT advertise(const XFcAdvertiser &aAdvertiser, const XFcUUID *aUuid);
    

    //! Updates advertiser state.
    XFCIMPORT virtual INT updateAdvertise(const XFcAdvertiser &aAdvertiser);

    //! Stops advertise service.
    XFCIMPORT virtual void cancelAdvertise();

    //! Returns first free port that can be used as server port.
    XFCIMPORT UINT16 getFirstFreeRFCOMMPort();
    
    //! Creates piconet.
    /*!
     * Creates bluetooth piconet. Needed if more than one simultanious connection is needed.
     * Use only with bluetooth master device.
     * \return 1 if success else XFCNET_ERROR.
     */
    XFCIMPORT INT createPiconet();

    //! Locks piconet.
    /*!
     * Locks the piconet. Other devices can not find this device nor connect to it.
     * The piconet must be created before this can be called.
     * Use only with bluetooth master device.
     * \return 1 if success else XFCNET_ERROR.
     */
    XFCIMPORT INT lockPiconet();

    //! Unlock piconet.
    /*!
     * Unlocks the bluetooth piconet.
     * Use only with bluetooth master device.
     */
    XFCIMPORT void unlockPiconet();

    //! Destroy piconet.
    /*!
     * Destroys created piconet.
     */
    XFCIMPORT void destroyPiconet();
    
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtCommService();

};


#endif // !XFCBTCOMMSERVICE_H_INCLUDED

