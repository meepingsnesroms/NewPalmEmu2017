/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet handler
 *
 * $Id: XFcInetHandler.h,v 1.16 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.16 $
 */

#ifndef XFCINETHANDLER_H_ICLUDED
#define XFCINETHANDLER_H_ICLUDED


#include <xfcore/net/XFcCommunicationHandler.h>
#include <xfcore/net/XFcCommunicationConstants.h>
#include <xfcore/net/XFcClientInetCommWinPriHelp.h>
#include <xfcore/XFcPriorityList.h>

class XFcObjectPacketBase;
class XFcInetAddress;
class XFcClientLost;
class XFcUdpEngine;
class XFcInetClientWin;
class XFcAddress;


//! XFcInetHandler responsipility is handle data flow throught UDP socket.
/*!
 * It directs data throught UDP socket. Its try not to choke current
 * UDP socket with data.
 */
class XFCDLLEXPORT XFcInetHandler : public XFcCommunicationHandler
{
private:

    //! Holds priority help for priorized object.
    XFcClientInetCommWinPriHelp mPriorityHelp;

    //! Holds bandwidth priority list.
    XFcPriorityList<XFcClientCommWin *> mBandwidthPriority;

    // Holds when we are able to send next packet.
    UINT32 mNextPacketTime;

    // Holds previous packet was sent.
    UINT32 mPrevPacketTime;

    //! Holds accept data from address.
    XFcInetAddress *mAcceptAddress;

    //! Holds maximum mtu for sendable packet.   
    INT32 mSendMtu;
    //! Holds maximum mtu for received packet.
    INT32 mRecvMtu;

    //! Holds state for open/close socket.
    XFcUdpEngine *mUdpEng;
    friend class XFcUdpEngine;

protected:

    //! Changes udp state.
    XFCIMPORT void changeUdpEngine(XFcUdpEngine *aNewEngine);

    //! Counts next packet time.
    XFCIMPORT void countNextPacketTime(INT aPacketSize);

    //! Initializes.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    XFCIMPORT INT init(UINT16 aListenPort, INT32 aSendMtu, INT32 aRecvMtu);

    //! Protected constructor.
    XFCIMPORT XFcInetHandler();

public:

    //! Static constructor.
    /*
     * \param aListenPort port number that is used to UDP communication.
     * \return new object if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHandler *create(UINT16 aListenPort,
                                            INT32 aSendMtu = XFCNET_MAXBUFFERSIZE,
                                            INT32 aRecvMtu = XFCNET_LISTENBUFFERSIZE);

    //! Static constructor.
    XFCIMPORT static XFcInetHandler *create(INT32 aSendMtu = XFCNET_MAXBUFFERSIZE,
                                            INT32 aRecvMtu = XFCNET_LISTENBUFFERSIZE);

    //! Opens communication service.
    XFCIMPORT void openService();

    //! Closes service, inherited from XFcCommunicationHandler.
    XFCIMPORT virtual void closeService();

    //! Verifies incoming packet sender address.
    /*!
     * \param address of incoming data.
     * \return client number.
     */
    XFCIMPORT INT32 verifySender(XFcAddress *aAddress) const;

    //! Handles incoming data. Inherited from XFcCommunicationHandler.
    /*!
     * \return size of received bytes.
     */
    XFCIMPORT virtual INT32 incoming();

    //! Handles outgoing data. Inherited from XFcCommunicationHandler.
    /*!
     * \return size of sent packet.
     */
    XFCIMPORT virtual INT32 outgoing();

    //! Sets UDP packet port.
    /*
     * \param packet port.
     */
    XFCIMPORT void setPort(UINT16 aPort);

    //! Handles unknown sender packet.
    XFCIMPORT virtual void unknownSender(const XFcAddress *aAddress, XFcObjectPacketBase *aPacket);

    //! Checks client activity.
    XFCIMPORT virtual void checkActivity();

    //! Destructor.
    XFCIMPORT virtual ~XFcInetHandler();

};


#endif // !XFCINETHANDLER_H_ICLUDED

