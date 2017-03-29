/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth address
 *
 * $Id: XFcBtAddress.h,v 1.9 2003/10/14 07:40:11 slehti Exp $
 * $Date: 2003/10/14 07:40:11 $
 * $Revision: 1.9 $
 */

#ifndef XFCBTADDRESS_H_INCLUDED
#define XFCBTADDRESS_H_INCLUDED

#include <xfcore/net/socket/XFcSocketConstants.h>
#include <xfcore/net/socket/XFcAddress.h>


//! Holds platform specific bluetooth address. 
/*!
 * Its purpose is to hold bt information that is needed
 * to make connection between two bt devices. 
 */
class XFCDLLEXPORT XFcBtAddress : public XFcAddress
{
protected:

    //! Holds platform specific address type.
    void *mAddress;

    //! Protected constructor.
    XFcBtAddress();

    //! Initializes the bluetooth address.
    INT init();
    
    //! Initializes the bluetooth address from an existing address.
    INT init(const XFcAddress &aAddress);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtAddress();

    //! Creates XFcBtAddress.
    XFCIMPORT static XFcBtAddress * create();

    //! Creates XFcBtAddress by copying from existing one.
    /*!
     * \param aAddress address to copy from.
     */
    XFCIMPORT static XFcBtAddress * create(const XFcAddress &aAddress);

    //! Sets the port (channel).
    /*!
     * \param aPort is used channel.
     */
    XFCIMPORT void setPort(UINT16 aPort);
   
    //! Gets port.
    /*!
     * \return port.
     */
    XFCIMPORT UINT16 getPort() const;
    
    //! Gets 48 bit address in a string with format "de:ad:be:ef:ba:be".
    /*!
     * \param aAddress pointer to a string where the address will be written.
     * \param aLen maximum length of the address string, will be overwritten
     *             with the actual length of the address string.
     */
    XFCIMPORT void getAddrStr(CHAR8 *aAddress, INT &aLen);

    //! Sets address string. Given string can be in "de:ad:be:ef:ba:be" or "0x000000" format. 
    /*!
     * if address is given as "0x" format prefix "0x" is required.
     * \param aAddress address as a string to be parsed from.
     * \param aLen length of the address string.
     */
    XFCIMPORT void setAddrStr(const CHAR8 *aAddress, INT aLen);

    //! Sets 48 bit address. Syntax is 0x0000, 0x00000000.
    /*!
      * \param aAddrHi upper 16-bit part of the 48 bit address.
      * \param aAddrLo lower 32-bit part of the 48 bit address.
      */
    XFCIMPORT void setAddr(UINT32 aAddrHi, UINT32 aAddrLo);

    //! Inherited from parent class.
    XFCIMPORT virtual void setAddress(void *aAddress, INT32 aLen);
    //! Inherited from parent class.
    XFCIMPORT virtual void * getAddress() const;
    //! Inherited from parent class.
    XFCIMPORT virtual void * getAddress();

    //! Test if address is same. Tests only address part of given address port is not tested.
    /*!
     * \param aAddress is address to test against.
     * \return 1 if it is else 0.
     */
    XFCIMPORT virtual INT isSame(const XFcAddress &aAddress) const;
    
};


#endif // !XFCBTADDRESS_H_INCLUDED

