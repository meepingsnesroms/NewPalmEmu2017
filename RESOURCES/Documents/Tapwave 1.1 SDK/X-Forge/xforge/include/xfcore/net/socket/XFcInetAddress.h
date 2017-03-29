/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet address
 *
 * $Id: XFcInetAddress.h,v 1.10 2003/10/14 07:40:11 slehti Exp $
 * $Date: 2003/10/14 07:40:11 $
 * $Revision: 1.10 $
 */

#ifndef XFCINETADDRESS_H_INCLUDED
#define XFCINETADDRESS_H_INCLUDED

#include <xfcore/net/socket/XFcAddress.h>


//! Macro for creating an ip address.
#define XFCNET_IPADDR(a, b, c, d) (UINT32)(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))


//! Inet address.
/*!
 * Used to hold all necessary information that is needed to create an inet socket connection.
 */
class XFCDLLEXPORT XFcInetAddress : public XFcAddress
{
protected:

    //! Inet address.
    void *mAddress;

    //! Protected constructor.
    XFcInetAddress();

    //! Initializes object.
    INT init();

    //! Copy initializer.
    INT init(const XFcAddress &aAddress);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcInetAddress();

    //! Static constructor.
    XFCIMPORT static XFcInetAddress * create();

    //! Static copy constructor.
    XFCIMPORT static XFcInetAddress * create(const XFcAddress &aAddress);

    //! Sets port.
    /*!
     * \param aPort port number, e.g. 20.
     * \note Network byte ordering is done by XFcInetAddress.
     */
    XFCIMPORT void setPort(UINT16 aPort);

    //! Gets port.
    /*!
     * \return port number, e.g. 20.
     */
    XFCIMPORT UINT16 getPort() const;

    //! Returns address to given string.
    /*!
     * \param aAddress pointer to buffer where address is returned.
     * \param aLen length of buffer, length set to returned buffer size.
     */
    XFCIMPORT void getHost(CHAR8 *aAddress, INT32 &aLen) const;

    //! Gets remote host name.
    /*!
     * \param aRemote remote address as string, e.g. "127.0.0.1". String must be null terminated.
     */
    XFCIMPORT void setHost(const CHAR8 *aRemote);

    //! Sets remote host address by ip in network byte order.
    /*!
     * \param aRemote host ip given in network byte order.
     */
    XFCIMPORT void setHost(UINT32 aRemote);

    //! Inherited from XFcAddress.
    XFCIMPORT virtual void setAddress(void *aAddress, INT32 aLen);

    //! Inherited from XFcAddress.
    XFCIMPORT virtual void * getAddress() const;

     //! Inherited from XFcAddress.
    XFCIMPORT virtual void * getAddress();
    

    //! Returns an inet address from a given string, e.g. "127.0.0.1".
    XFCIMPORT static UINT32 inetAddress(const CHAR8 *cp);
   

    //! Tests addresses for equality.
    /*!
     * \param aAddrf first inet address to test.
     * \param aAddrs second inet address to test.
     * \return 1 if address objects are identical, or 0 otherwise.
     */
    XFCIMPORT static INT isSame(const XFcInetAddress &aAddrf,
                                const XFcInetAddress &aAddrs);

    
    //! Test if address is same. Tests only address part of given address port is not tested.
    /*!
     * \param aAddress is address to test against.
     * \return 1 if it is else 0.
     */
    XFCIMPORT virtual INT isSame(const XFcAddress &aAddress) const;

    
};


#endif // !XFCINETADDRESS_H_INCLUDED

