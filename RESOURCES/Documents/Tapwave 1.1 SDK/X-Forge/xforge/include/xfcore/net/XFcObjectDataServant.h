/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd        
 *
 * \brief Data dealer to data receivers
 *
 * $Id: XFcObjectDataServant.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */

#ifndef XFCOBJECTDATASERVANT_H_INCLUDED
#define XFCOBJECTDATASERVANT_H_INCLUDED


#include <xfcore/net/XFcDataReceiverHashTable.h>
#include <xfcore/net/XFcDataReceiver.h>


//! XFcObjectDataServant holds hash table of data receivers and share data to those.
/*!
 * Its purpose is to keep up hash table of data receivers. It does not 
 * own any added receiver so delete doesn not remove or release any of those.
 */
class XFcObjectDataServant
{
protected:

    //! Data receiver creator.
    XFcDataReceiver *mReceiver;

    //! Data receiver hash table.
    XFcDataReceiverHashTable *mReceiverHashTable;

    //! Initializes class.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT init();

    //! Protected constructor.
    XFcObjectDataServant();

public:

    //! Destructor.
    ~XFcObjectDataServant();

    //! Static constructor.
    /*!
     * \return new object if successful, or NULL if unsuccessful.
     */
    static XFcObjectDataServant *create();

    //! Sets data receiver.
    /*!
     * \param aReceiver data receiver.
     */
    void setDataReceiver(XFcDataReceiver *aReceiver);

    //! Adds data receiver to hash table.
    /*!
     * \param aReceiver data receiver.
     * \return 1 if successful, or 0 otherwise.
     */
    INT addDataReceiver(UINT32 aId, XFcDataReceiver *aReceiver);

    //! Gets data receiver.
    /*!
     * \param aId receiver id.
     * \return data receiver.
     */
    XFcDataReceiver * getDataReceiver(UINT32 aId);

    //! Removes data receiver.
    /*! 
     * \param aId receiver id.
     * \return data receiver.
     */
    XFcDataReceiver * removeDataReceiver(UINT32 aId);


    //! Incoming data.
    /*! 
     * \param aClientId is identidfier about client where data comes from.
     * \param aId object id.
     * \param aBlock data block.
     * \param aBlockLen data block length.
     */
    void incoming(INT32 aClientId, UINT32 aId, CHAR8 *aBlock, INT aBlockLen);

};


#endif // !XFCOBJECTDATASERVANT_H_INCLUDED

