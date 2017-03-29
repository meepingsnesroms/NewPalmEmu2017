/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcAddress base
 *
 * $Id: XFcAddress.h,v 1.9 2003/10/14 07:40:11 slehti Exp $
 * $Date: 2003/10/14 07:40:11 $
 * $Revision: 1.9 $
 */


#ifndef XFCADDRESS_H_INCLUDED
#define XFCADDRESS_H_INCLUDED


//! Base class for addresses. 
/*!
 * Holds type of address and length of address. 
 * Its purpose is to give common interface for setting and getting address. 
 */
class XFCDLLEXPORT XFcAddress
{
protected:

    //! Type of address, i.e. XFCNET_AFINET.
    INT32 mType;
    //! Length of address.
    INT32 mLen;

    //! Protected constructor.
    XFcAddress();

public:
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcAddress();

    //! Set type of network address.
    /*!
     * \param aType Sets type of address. i.e XFCNET_AFINET.
     */
    XFCIMPORT void setType(INT32 aType);

    //! Get type of network address.
    /*!
     * \return type of address.
     */
    XFCIMPORT INT32 getType() const;

    //! Set size of address.
    /*!
     * \param aLen Sets size of address.
     */
    XFCIMPORT void setAddressSize(INT32 aLen);

    //! Get size of address.
    /*!
     * \return size of address.
     */
    XFCIMPORT INT32 getAddressSize() const;

    //! Set pointer to the address.
    /*! 
     * \param aAddress platform specific address, i.e. struct sockaddr_in.
     * \param aLen length of platform specifig address.
     */
    XFCIMPORT virtual void setAddress(void *aAddress, INT32 aLen) = 0;

    //! Get pointer to the address.
    /*!
     * \return platform specific address. i.e. struct sockaddr_in.
     */
    XFCIMPORT virtual void * getAddress() const = 0;

    //!Get pointer to the address.
    /*!
     * \return platform specific address. i.e. struct sockaddr_in.
     */
    XFCIMPORT virtual void * getAddress() = 0;


    //! Test if address is same. Tests only address part of given address port is not tested.
    /*!
     * \param aAddress is address to test against.
     * \return 1 if it is else 0.
     */
    XFCIMPORT virtual INT isSame(const XFcAddress &aAddress) const = 0;
    
};


#endif // !XFCADDRESS_H_INCLUDED

