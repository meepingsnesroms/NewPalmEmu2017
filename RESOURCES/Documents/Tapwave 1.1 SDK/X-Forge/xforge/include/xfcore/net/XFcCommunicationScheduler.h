/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XForge communication 
 *
 * $Id: XFcCommunicationScheduler.h,v 1.19 2003/09/17 13:07:37 slehti Exp $
 * $Date: 2003/09/17 13:07:37 $
 * $Revision: 1.19 $
 */

#ifndef XFCCOMMUNICATIONSCHEDULER_H_INCLUDED
#define XFCCOMMUNICATIONSCHEDULER_H_INCLUDED

#include <xfcore/XFcCommunication.h>

class XFcObjectDataServant;
class XFcCommunicationHandler;
class XFcClientCommWin;
class XFcDataReceiver;
class XFcObjectDataFrame;
class XFcDataReceiverHashTable;
class XFcDataReceiver;
class XFcCommService;
class XFcAdvertiser;
class XFcDeviceDiscovery;
class XFcHostResolver;

//class XFcBtServerSearch;

#define XFCNET_SUPPORTED_HANDLER_COUNT 2


//! XFcCommunicationScheduler is user interface to use Xforge communication.
/*!
 * XFcore communication uses client to receiver communication. All data is send
 * throught client that express physical receiver to data receiver. XFcCommunicationScheduler
 * can hold multiple data receiver which can receive data from multiple different clients.
 * Any data receiver is not connected to any certain client. Its doesn't own any data receiver
 * or client so it does not delete any on destructor.
 */
class XFCDLLEXPORT XFcCommunicationScheduler : public XFcCommunication
{
private:

    //! Holds object data servant, its used to share data all registered data receiver.
    XFcObjectDataServant *mObjectDataServant;


protected:

    struct XFCDLLEXPORT XFcSchedulerObject
    {
        XFcSchedulerObject() : mCommHandler(NULL){}

        //! Holds pointer to communication handler.
        XFcCommunicationHandler *mCommHandler;
    };


    //! Holds sceduler objects for bt and inet. First one is Bt and second is INET.
    XFcSchedulerObject mCommunication[XFCNET_SUPPORTED_HANDLER_COUNT];

    //! Gets scheduler object from list.
    XFcSchedulerObject * getSchedulerObjectByType(INT aType);

    const XFcSchedulerObject * getSchedulerObjectByType(INT aType) const;

    XFcSchedulerObject * getSchedulerObjectByClientId(INT32 aIndex);

    const XFcSchedulerObject * getSchedulerObjectByClientId(INT32 aIndex) const;


    //! Initializes class.
    /*!
     * \param aCommHandlerArraySize communication handler array size.
     * \return 1 if successful, or 0 otherwise.
     */
    INT init();

    //! Protected constructor.
    XFCIMPORT XFcCommunicationScheduler();

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcCommunicationScheduler();

    //! Static constructor.
    /*!
     * \param aCommHnalderArraySize communication handler array size.
     * \return new XFcCommunicationScheduler object if successful, or NULL if unsuccessful.
     */
    static XFcCommunicationScheduler * create();

    //! Runs scheduler.
    /*!
     * \note Not supported.
     */
    XFCIMPORT virtual INT runScheduler();

    //! Gets last runscheduler error.
    /*!
     * \return Error value.
     */
    XFCIMPORT INT getError() const;

    //! Adds client.
    /*!
     * \param aClient client data.
     * \return client id if successful, or XFCNET_CLIENTADD_ERROR if unsuccessful.
     */
    XFCIMPORT INT32 addClient(XFcClientCommWin *aClient);

    //! Gets round client round trip time.
    /*!
     * \param aClient client id.
     */
    XFCIMPORT INT32 getRoundTripTime(INT32 aClient) const;

    //! Removes client.
    /*!
     * \param aClient client id.
     * \return client.
     */
    XFCIMPORT XFcClientCommWin * removeClient(INT32 aClient);

    //! Gets client.
    /*!
     * \param aClient client id.
     * \return client.
     */
    XFCIMPORT XFcClientCommWin * getClient(INT32 aClient);

    //! Adds communication handler.
    /*!
     * \param aHandler communication handler.
     * \return handler id if successful, or XFENET_COMMHANDLERADD_ERROR otherwise.
     */
    XFCIMPORT INT addCommunicationHandler(XFcCommunicationHandler *aHandler);

    //! Gets communication handler.
    /*!
     * \param aHandler handler id.
     * \return handler if successful, or NULL otherwise.
     */
    XFCIMPORT XFcCommunicationHandler * getCommunicationHandler(INT32 aHandler);

    //! Removes communication handler.
    /*!
     * \param aHandler handler id.
     * \return handler if successful, or NULL otherwise.
     */
    XFCIMPORT XFcCommunicationHandler * removeCommunicationHandler(INT32 aHandler);

    //! Sets data receiver.
    /*!
     * \param aReceiver data receiver.
     */
    XFCIMPORT void setDataReceiver(XFcDataReceiver *aReceiver);

    //! Adds data receiver to hash table.
    /*!
     * \param aReceiver data receiver.
     * \return 1 if successful, or 0 if unsuccessful.
     */
    XFCIMPORT INT addDataReceiver(UINT32 aId, XFcDataReceiver *aReceiver);

    //! Gets data receiver.
    /*!
     * \param aId receiver id.
     * \return data receiver.
     */
    XFCIMPORT XFcDataReceiver *getDataReceiver(UINT32 aId);

    //! Removes data receiver.
    /*!
     * \param aId receiver id.
     * \return data receiver.
     */
    XFCIMPORT XFcDataReceiver *removeDataReceiver(UINT32 aId);

    //! Gets packet frame.
    /*!
     * \param aClient client id.
     * \param aSlot message identifier (XFENET_RECENTSTATE ...).
     * \return packet frame class.
     */
    XFCIMPORT XFcObjectDataFrame *getPacketFrame(INT32 aClient, INT aSlot);

    //! Gets recent state frame.
    /*!
     * \param aClient client id.
     * \param aRecentId recent state id.
     * \return recent state frame.
     */
    XFCIMPORT XFcObjectDataFrame *getRecentStateFrame(INT32 aClient, INT32 aRecentId);

    //! Removes recent state frame.
    /*!
     * \param aClient client id.
     * \param aRecentId recent state id.
     */
    XFCIMPORT void removeRecentStateFrame(INT32 aClient, INT32 aRecentId);

    //! Adds communication service.
    /*!
     * \param aType connection type, e.g. XFCNET_COMMUNICATIONTYPE_INET.
     * \param aCommService pointer to communication service.
     */
    XFCIMPORT void addCommunicationService(INT aType, XFcCommService *aCommService);

};


#endif // !XFCCOMMUNICATIONSCHEDULER_H_INCLUDED

