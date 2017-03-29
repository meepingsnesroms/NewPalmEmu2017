/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd       
 *
 * \brief Device name look up base
 *
 * $Id: XFcHostResolver.h,v 1.8 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.8 $
 */


#ifndef XFCHOSTRESOLVER_H_INCLUDED
#define XFCHOSTRESOLVER_H_INCLUDED

class XFcAddress;
class XFcHostEntry;
class XFcName;


//! Host resolver is base class for device name resolution.
class XFCDLLEXPORT XFcHostResolver
{
protected:

    //! Holds resolver type (rtti).
    INT mType;

    //! Holds pointer to platform independent code.
    void *mResolver;

    //! Constructor.
    XFcHostResolver();

public:

    // Supported types of XFcHostResolver
//     enum XFCHOSTRESOLVER
//     {
//         //! Base type for host resolver
//         XFCNET_HOSTRESOLVE_,
//         //! Inet host resolver
//         XFCNET_HOSTRESOLVE_INET,
//         //! Bt host resolver
//         XFCNET_HOSTRESOLVE_BT, 
//     };

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcHostResolver();

    //! Gets resolver type.
    /*!
     * \return resolver type.
     */
    XFCIMPORT INT getType() const;

    //! Gets local address.
    /*!
     * \param aAddress address where local address is stored.
     * \return 1 if query was succesful, or 0 otherwise.
     */
    XFCIMPORT virtual INT localAddress(XFcAddress &aAddress);

    //! Gets local name.
    /*!
     * \param aName buffer where name is stored.
     * \return 1 if query was succesful, or 0 otherwise.
     */
    XFCIMPORT virtual INT localName(XFcName &aName);

    //! Gets remote name.
    /*!
     * \param aAddress remote address, required.
     * \param aHostEntry entry where host address and host name is stored.
     * \return 1 if query was succesful, or 0 otherwise.
     */
    XFCIMPORT virtual INT remoteName(const XFcAddress &aAddress, XFcHostEntry &aHostEntry);

    //! Gets remote address.
    /*!
     * \param aName remote name, required.
     * \param aHostEntry entry where host address and host name is stored.
     * \return 1 if query was succesful, or 0 otherwise.
     */
    XFCIMPORT virtual INT remoteAddress(const XFcName &aName, XFcHostEntry &aHostEntry);

};


#endif // !XFCHOSTRESOLVER_H_INCLUDED

