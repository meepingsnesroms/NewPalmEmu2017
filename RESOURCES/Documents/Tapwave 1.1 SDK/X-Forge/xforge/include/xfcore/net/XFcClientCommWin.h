/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Base for clients
 *
 * $Id: XFcClientCommWin.h,v 1.13 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.13 $
 */

#ifndef XFCCLIENTCOMMWIN_H_INCLUDED
#define XFCCLIENTCOMMWIN_H_INCLUDED

class XFcAddress;
class XFcObjectDataServant;
class XFcObjecDataQueue;
class XFcObjectDataPacket;
class XFcObjectPacketBase;
class XFcSingleDataPacket;
class XFcObjectDataFrame;


//! XFcClientCommWin is client communication window class. It's interface for communicate to other clients.
/*!
 * It's interface class for every clients used with network. On X-Forge network
 * all network network/bt users are clients. Server side ClientCommWin and client
 * side ClientCommWin are connected together. 
 */
class XFCDLLEXPORT XFcClientCommWin
{
private:

    //! Connection type, e.g. INET, IRDA, BLUETOOTH.
    INT32 mConnectionType;

    //! Connection time out.
    INT32 mConnectionTimeOut;
    
    //! Round trip time.
    UINT32 mRtt;

    //! Connection speed.
    INT32 mCommSpeed;

    //! Holds latest error.
    INT32 mLastError;

protected:

    //! Incoming data handler.
    XFcObjectDataServant *mObjectDataServant;

    //! Host address.
    XFcAddress *mAddress;

    //! Holds client id.
    INT32 mClientId;

    //! Initializes.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT initClientCommWin();

    //! Protected constructor.
    XFCIMPORT XFcClientCommWin();

public:

    //! Connection speed enumeration.
    enum XFCNET_CONNECTION_SPEED
    {
        //! 28.8 kbit/s.
        XFCNET_MODEM_28_8,
        //! 14.4 kbit/s.
        XFCNET_HSCD_14_4,
        //! 9 - 150 kbit/s.
        XFCNET_GPRS,
        //! 2 Mbit/s.
        XFCNET_WLAN_2MB,
        //! 11 Mbit/s.
        XFCNET_WLAN_11MB,
        //! Bluetooth.
        XFCNET_BLUETOOTH, 
    };
    
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcClientCommWin();

    //! Runtime initialize client.
    XFCIMPORT virtual void intializeClient();

    //! Runtime deinitialize client.
    XFCIMPORT virtual void deinitializeClient();

    //! Gets latest error of XFcClientCommWin.
    XFCIMPORT INT32 getLastError() const;
 
    //! Sets latest error.
    XFCIMPORT void setLastError(INT32 aError);

    //! Gets a packet frame.
    /*!
     * \param aSlot client id.
     * \return packet frame class.
     */
    XFCIMPORT virtual XFcObjectDataFrame * getPacketFrame(INT aSlot) = 0;

    //! Gets recent state frame.
    /*! 
     * \param aRecentId recent state id.
     * \return recent state frame.
     */
    XFCIMPORT virtual XFcObjectDataFrame * getRecentStateFrame(INT32 aRecentId) = 0;

    //! Removes recent state frame.
    /*!
     * \param aRecentId recent state id.
     */
    XFCIMPORT virtual void removeRecentStateFrame(INT32 aRecentId) = 0;
    
    //! Incoming data buffer.
    /*!
     * \param aRecvBuffer packet base that contains new data from network.
     * \return length of incoming data in bytes.
     */
    XFCIMPORT virtual INT32 incoming(XFcObjectPacketBase &aRecvBuffer) = 0;
    
    //! Outgoing data buffer.
    /*!
     * \param aSendBuffer packet base where sendable packet is created.
     * \return length of data in bytes.
     */
    XFCIMPORT virtual INT32 outgoing(XFcObjectPacketBase &aSendBuffer) = 0;
    
    //! Gets status of bandwidth.
    /*! 
     * \return 1 if we are able to send data, or 0 otherwise.
     */
    XFCIMPORT virtual INT bandwidthCheck() = 0;

    //! Gets client status.
    XFCIMPORT virtual INT isClientActive() = 0;

    //! Tests clients address against given address.
    XFCIMPORT virtual INT testAddress(const XFcAddress &aAddress) = 0;
    

    // Basic connection handling methods
    
    //! Sets host address.
    /*! 
     * \param aAddress host address.
     */ 
    XFCIMPORT virtual void setAddress(const XFcAddress &aAddress) = 0;

    //! Gets host address.
    /*!
     * \return host address set by setHostAddress().
     */
    XFCIMPORT const XFcAddress & getAddress() const;
        
    //! Sets connection timeout.
    /*!
     * \param aTime timeout.
     */
    XFCIMPORT void setConnectionTimeout(INT32 aTime);

    //! Gets connection timeout.
    /*! 
     * \return connection timeout value.
     */
    XFCIMPORT INT32 getConnectionTimeout() const;
    
    //! Sets connection type.
    /*!
     * \param aType connection type.
     */
    XFCIMPORT void setConnectionType(INT aType);

    //! Gets connection type.
    /*!
     * \return connection type.
     */
    XFCIMPORT INT getConnectionType() const;

    //! Set round trip time.
    /*!
     * \param aRttValue round trip time in milliseconds.
     */
    XFCIMPORT void setRtt(INT32 aRttValue);

    //! Gets round trip time.
    /*!
     * \return round trip time in milliseconds.
     */
    XFCIMPORT INT32 getRtt() const;
    

    //! Gets client id.
    XFCIMPORT INT32 getClientId() const;

    //! Sets client id.
    XFCIMPORT void setClientId(INT32 aId);

    //! Sets object data servant.
    /*!
     * \param aObjectDataServant object data servant.
     */
    XFCIMPORT void setObjectDataServant(XFcObjectDataServant *aObjectDataServant);

    //! Gets object data servant.
    /*!
     * \return object data servant.
     */
    XFCIMPORT XFcObjectDataServant * getObjectDataServant() const;

    //! Sets communication speed.
    XFCIMPORT void setCommSpeed(INT aType);

    //! Gets communication speed.
    XFCIMPORT INT getCommSpeed() const;
};


#endif // !XFCCLIENTCOMMWIN_H_INCLUDED


