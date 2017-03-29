/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Communication handler base
 *
 * $Id: XFcCommunicationHandler.h,v 1.12 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.12 $
 */

#ifndef XFCCOMMUNICATIONHANDLER_H_INCLUDED
#define XFCCOMMUNICATIONHANDLER_H_INCLUDED

class XFcClientCommWin;
class XFcUnknownSender;
class XFcObjectPacketBase;
class XFcUnknownSender;
class XFcCommService;
class XFcClientLost;
class XFcAddress;


//! XFcCommunicationHandler is base for incoming and outgoing data flow.
/*!
 * It uses array of clients which are "connected" together. Data flow will 
 * allways go throught this object. It offers basic functionality to 
 * handle communication between two clients. It doesn't own any of clients, 
 * one have to delete all added clients before deleting this class. 
 */
class XFCDLLEXPORT XFcCommunicationHandler
{
private:
    //! Holds maximum client count.
    INT mMaxClientCount;

    //! Holds base number for client.
    INT mBaseNumber;

    //! Holds connection type, e.g. INET, IRDA, BLUETOOTH.
    INT32 mConnectionType;

    //! Holds communication handlers last error, argument is initialized to XFCNET_ERROR.
    INT32 mLastError;

protected:

    //! Initializes packet.
    XFCIMPORT INT baseInit();

    //! Protected constructor.
    XFCIMPORT XFcCommunicationHandler();

    //! Holds client array.
    XFcClientCommWin **mClientWinData;
    
    //! Holds unknown sender, senders address is not known.
    XFcUnknownSender *mUSender;
    
    //! Holds connection lost event interface.
    XFcClientLost *mClientLost;
    
    //! Connection speed.
    INT32 mConnectionSpeed;
    
public:

    //! Enumerated communication handlers internal errors.
    enum XFCNET_HANDLER_ERRORS
    {
        //! Communication handler has reached its maximum client count.
        /*! New clients can not be added. */
        XFCNET_MAX_CLIENT_COUNT_REACHED = 1000,
        //! Given index is out of range. Array underflow or overflow.
        XFCNET_INDEX_OUT_OF_RANGE,
        //! No client found with given id.
        XFCNET_INVALID_CLIENT_ID,
        //! There is more created clients than newly created array can handle.
        XFCNET_ARRAYSIZELEAK_ERROR,
        //! Handler was not able to alloc new array for clients. Old array stays.
        XFCNET_ARRAYSIZEMEMORY_ERROR,
        //! No error, return value when called setMaxClientCount().
        XFCNET_ARRAYSIZE_OK = 1, 
    };

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcCommunicationHandler();

    //! Sets client communication data.
    /*!
     * \param aClientWinData client communication data.
     */
    XFCIMPORT INT addClientCommWin(XFcClientCommWin *aClientWinData);

    //! Removes client count window.
    /*!
     * \param aClient client index.
     * \return client communication window if successful, or NULL otherwise.
     * \note If NULL is returned error value is set.
     */
    XFCIMPORT XFcClientCommWin * removeClientCommWin(INT32 aClient);

    //! Gets client count window.
    /*!
     * \param aClient client index.
     * \return client communication window if successful, or NULL otherwise.
     * \note If NULL is returned error value is set.
     */
    XFCIMPORT XFcClientCommWin * getClientCommWin(INT32 aClient);

    //! Sets handler for unknown packet sender.
    /*!
     * \param aHandler interface for handling unknown data sender.
     */
    XFCIMPORT void setUnknownSenderHandler(XFcUnknownSender *aHandler);

    //! Gets handle of unknown packet sender.
    XFCIMPORT XFcUnknownSender * getUnknownSenderHandler();

    //! Sets maximum client count.
    /*!
     * \param aClientCount new client count.
     * \return XFCNET_ARRAYSIZE_OK if new array creation is successful, or XFCNET_ERROR if unsuccessful.
     * \note If XFCNET_ERROR is returned error value is set and client table is not changed. 
     */
    XFCIMPORT INT setMaxClientCount(INT32 aClientCount);

    //! Gets client count.
    /*!
     * \return client count, number of clients added to mClientWinData.
     */
    XFCIMPORT INT32 getClientCount() const;

    //! Gets maximum client count.
    /*!
     * \return max client count, number of client can be added to mClientWinData.
     */  
    XFCIMPORT INT32 getMaxClientCount() const;

    //! Sets base number of client.
    XFCIMPORT void setClientBaseNumber(INT32 aBase);

    //! Gets base number of client.
    XFCIMPORT INT32 getClientBaseNumber() const;
    
    //! Sets client lost handler.
    /*!
     * \param aClientLost client lost handling interface.
     */
    XFCIMPORT void setClientLost(XFcClientLost *aClientLost);

    //! Sets client lost handler.
    /*!
     * \return client lost handling interface.
     */
    XFCIMPORT XFcClientLost * getClientLost() const;
    
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

    //! Sets handlers connection speed.
    /*! 
     * \param aSpeedType connection speed enumeration, see XFCNET_CONNECTION_SPEED.
     * \sa XFCNET_CONNECTION_SPEED
     */
    XFCIMPORT void setConnectionSpeed(INT aSpeedType);

    //! Tunes connection speed directly.
    /*! 
     * \param aSpeed new connection speed timerout.
     */
    XFCIMPORT void tuneConnectionSpeed(INT32 aSpeed);

    //! Gets current connection speed.
    /*!
     * \return connection speed.
     */
    XFCIMPORT INT32 getConnectionSpeed() const;
        
    //! Tests incoming packet sender address.
    /*!
     * \param aAddress test address against added clients.
     * \return client number, index to array.
     */
    XFCIMPORT INT32 testAddress(const XFcAddress &aAddress);

    //! Sets handlers last error.
    /*!
     * \param aError error value.
     */
    XFCIMPORT void setLastError(INT32 aError);
    
    //! Gets handlers last error.
    /*!
     * \return last error set by setLastError().
     */
    XFCIMPORT INT32 getLastError() const;

    //! Sets client last error.
    /*!
     * \param aClient client identifier.
     * \param aError error value.
     */ 
    XFCIMPORT void setClientLastError(INT32 aClient, INT32 aError);
    
    //! Gets clients last error.
    /*!
     * \param aClient client identifier.
     * \return XFCNET_INDEX_OUT_OF_RANGE if aClient underflows or overflows, or
     *         XFCNET_INVALID_CLIENT_ID if client is not found, or XFCNET_ERROR otherwise.
     */
    XFCIMPORT INT32 getClientLastError(INT32 aClient) const;
    
    //! Close the communication service.
    XFCIMPORT virtual void closeService() = 0;

    //! Sends data.
    XFCIMPORT virtual INT outgoing() = 0;
 
    //! Gets data.
    XFCIMPORT virtual INT incoming() = 0;

    //! Activity check.
    XFCIMPORT virtual void checkActivity() = 0;

    //! Handles data from unknown address.
    XFCIMPORT virtual void unknownSender(const XFcAddress *, XFcObjectPacketBase *) = 0;
    

};


#endif // !XFCCOMMUNICATIONHANDLER_H_INCLUDED

