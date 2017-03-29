/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief UDP opening and closing service
 *
 * $Id: XFcUdpEngine.h,v 1.11 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision $
 */

#ifndef XFCUDPENGINE_H_INCLUDED
#define XFCUDPENGINE_H_INCLUDED


class XFcUdpRecv;
class XFcInetHandler;
class XFcInetClientWin;
class XFcDgramSocket;
class XFcObjectPacketBase;
class XFcInetAddress;
class XFcAddress;


//! XFcUdpEngine is interface for UDP open and close engine.
class XFcUdpEngine
{
protected:
    //! Gets recv address.
    /*!
     * \param aCommHandler reference to udp manager.
     * \return pointer to address.
     */
    const XFcAddress * const getRecvAddress(XFcCommunicationHandler &aCommHandler) const;

    //! Changes udp engine.
    void changeUdpEngine(XFcCommunicationHandler &aCommHandler, XFcUdpEngine *aEngine);

    //! Protected constructor.
    XFcUdpEngine();

public:

    //! States that UDP engine can handle.
    enum XFCNET_UDP_CONNECTION
    {
        XFCNET_UDP_OPEN = -2,   //!< UDP socket is open.
        XFCNET_UDP_CLOSE = -3   //!< UDP socket is closed.
    };


    //! Virtual destructor, does nothing.
    virtual ~XFcUdpEngine();

    //! Opens UdpEngine.
    /*!
     * \param aCommHandler communication handler that holds client that are going to send or receive data.
     * \note If open fails state will change.
     */
    virtual void open(XFcCommunicationHandler &aCommHandler, INT32 aSendMtu, INT32 aRecvMtu) = 0;

    //! Closes UdpEngine. 
    /*!
     * \param aCommHandler communication handler.
     * \note Will release XFcUdpEngine resources.
     */
    virtual void close(XFcCommunicationHandler &aCommHandler) = 0;

    //! Sends data to given client.
    /*!
     * \param aClientCommWin client where data is going to send.
     * \return number of sent bytes if successful, or XFCNET_ERROR if unsuccessful.
     */
    virtual INT send(XFcClientCommWin *aClientCommWin) = 0;

    //! Receives data from udp port.
    /*!
     * \param aCommHandler communication handler base. It is used for client address resolving.
     * \param aBase pointer for received data packet.
     * \param aIndex client index to XFcCommunicationHandler array.
     * \return number of received bytes if successful, or XFCNET_ERROR if unsuccessful.
     */
    virtual INT recv(XFcCommunicationHandler &aCommHandler, XFcObjectPacketBase **aBase, INT32 &aIndex) = 0;

    //! Gets current XFcUdpEngine state.
    /*!
     * \return current engine state, check XFCNET_UDP_CONNECTION.
     */
    virtual INT getState() = 0;

};



//! XFcUdpOpenEngine UDP open state.
class XFcUdpOpenEngine : public XFcUdpEngine
{
private:

    //! Holds UDP socket.
    XFcDgramSocket *mSocket;

    //! Holds send data buffer.
    XFcObjectPacketBase *mBuffer;

    //! Holds incoming data.
    XFcObjectPacketBase *mIncomingBuffer;

    //! Holds incoming buffer len 1500 bytes.
    INT32 mIncomingLen;

    //! Holds incoming address.
    XFcInetAddress *mAddress;

    //! Receive data. This is running it's own thread.
    XFcUdpRecv *mRecv;

protected:

    //! Protected constructor.
    XFcUdpOpenEngine();

    //! Initializes XFcUdpOpenEngine.
    INT init(XFcCommunicationHandler &aCommHandler, INT32 aSendMtu, INT32 aRecvMtu);

public:

    //! Static constructor.
    static XFcUdpOpenEngine * create(XFcCommunicationHandler &aCommHandler, INT32 aSendMtu, INT32 aRecvMtu);
 
    //! Receives data.
    virtual INT recv(XFcCommunicationHandler &aCommHandler, XFcObjectPacketBase **, INT32 &);

    //! Opens engine.
    virtual void open(XFcCommunicationHandler &aCommHandler, INT32 aSendMtu, INT32 aRecvMtu);

    //! Closes engine.
    virtual void close(XFcCommunicationHandler &aCommHandler);

    //! Sends data.
    virtual INT send(XFcClientCommWin *);

    //! Returns state of engine.
    virtual INT getState();

    //! Virtual destructor.
    virtual ~XFcUdpOpenEngine();
};


//! XFcUdpOpenEngine UDP close state.
class XFcUdpCloseEngine : public XFcUdpEngine
{
protected:

    //! Protected constructor.
    XFcUdpCloseEngine();

    //! Inits XFcUdpCloseEngine.
    INT init();

public:

    //! Static constructor.
    static XFcUdpCloseEngine *create();

    //! Opens udp engine.
    virtual void open(XFcCommunicationHandler &aCommHandler, INT32 aSendMtu, INT32 aRecvMtu);

    //! Closes udpengine.
    virtual void close(XFcCommunicationHandler &aCommHandler);

    //! Sends data.
    virtual INT send(XFcClientCommWin *);

    //! Receives data.
    virtual INT recv(XFcCommunicationHandler &aCommHandler, XFcObjectPacketBase **, INT32 &);

    //! Returns state of engine.
    virtual INT getState();

    //! Virtual destructor.
    virtual ~XFcUdpCloseEngine();

};


#endif // !XFCUDPENGINE_H_INCLUDED

