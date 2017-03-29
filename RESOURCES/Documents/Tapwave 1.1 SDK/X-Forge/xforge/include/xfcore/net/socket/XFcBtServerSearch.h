/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth XForge server search.
 *
 * $Id: XFcBtServerSearch.h,v 1.7 2003/09/17 11:09:57 slehti Exp $
 * $Date: 2003/09/17 11:09:57 $
 * $Revision: 1.7 $
 */

#ifndef XFCBTSERVERSEARCH_H_INCLUDED
#define XFCBTSERVERSEARCH_H_INCLUDED

#include <xfcore/XFcLinkedList.h>

class XFcAdvertiser;
class XFcDeviceDiscovery;
class XFcBtUUID;


class XFcBtServerSearch
{
private:

    //! Holds device discovery callback pointer.
    XFcDeviceDiscovery *mDeviceDiscovery;

    //! Holds server search pointer.
    void *mService;
    
protected:

    //! Protected constructor.
    XFcBtServerSearch();

    //! Initializes XFcBtServerSearch.
    INT init();
    
public:

    //! Virtual destructor.
    virtual ~XFcBtServerSearch();

    //! Static constructor.
    /*! Constructs a server search object.
     */
    XFCIMPORT static XFcBtServerSearch *create();

    //! Inquiry servers.
    /*!
     * \return if success return value is 0 else -1.
     */
    XFCIMPORT INT inquiry(XFcDeviceDiscovery *aDeviceDiscovery, const XFcBtUUID &aUuid);

    //! Cancel server inquiry.
    XFCIMPORT void cancelInquiry();

    //! Callback for inquiry result.
    XFCIMPORT void inquiryResult(XFcLinkedList<XFcAdvertiser *> &aAdvertiser);
};


#endif // !XFCBTSERVERSEARCH_H_INCLUDED

