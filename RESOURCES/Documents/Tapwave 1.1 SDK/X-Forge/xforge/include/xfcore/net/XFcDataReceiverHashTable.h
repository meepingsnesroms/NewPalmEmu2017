/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Data receiver hash table.
 *
 * $Id: XFcDataReceiverHashTable.h,v 1.14 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.14 $
 */

#ifndef XFCDATARECEIVERHASHTABLE_H_INCLUDED
#define XFCDATARECEIVERHASHTABLE_H_INCLUDED

#include <xfcore/net/XFcDataReceiver.h>
#include <xfcore/XFcHashtable.h>


//! XFcDataReceiverHashTable is hash table for data receivers.
class XFcDataReceiverHashTable  
{

private:

    //! Network controller hash table.
    XFcHashtable<UINT32, XFcDataReceiver *> mHashtable;

protected:

    //! Constructor.
    XFcDataReceiverHashTable();

    //! Initialize hash table.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT initReceiverHashtable();

public:

    //! Creates XFcDataReceiverHashTable.
    /*!
     * \return XFcDataReceiverHashTable if successful, or NULL otherwise.
     */
    static XFcDataReceiverHashTable * create();


    //! Adds group.
    /*!
     * \param aId key id.
     * \param aReceiver receiver.
     * \return 1 if successful, or 0 otherwise.
     */
    INT addReceiver(UINT32 aId, XFcDataReceiver *aReceiver);


    //! Removes group.
    /*!
     * \param aId key id.
     * \return pointer to XFcNetDataReceiver.
     */
    XFcDataReceiver * removeReceiver(UINT32 aId);


    //! Gets receiver.
    /*!
     * \param aId key.
     * \return pointer to XFcNetDataReceiver.
     */
    XFcDataReceiver * getReceiver(UINT32 aId);


    //! Uses network controller by id.
    /*!
     * \param aId controller id.
     * \param aData data buffer.
     * \param aLen buffer len.
     */
    INT callReceiver(INT32 aClientId, UINT32 aId, const CHAR8 *aData, INT32 aLen);


    //! Virtual destructor.
    virtual ~XFcDataReceiverHashTable();

};


#endif // !XFCDATARECEIVERHASHTABLE_H_INCLUDED

