/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth link security
 *
 * $Id: XFcBtSecurity.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCBTSECURITY_H_INCLUDED
#define XFCBTSECURITY_H_INCLUDED

class XFcAddress;


//! Holds bluetooth security information for bluetooth link to other device.
class XFCDLLEXPORT XFcBtSecurity
{
private:

    //! Holds platform specific bt security manager.
    void *mSecurity;
    
protected:

    //! Protected constructor.
    XFcBtSecurity();

    //! Initializes security manager.
    INT init();

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtSecurity();
      
    //! Static constructor.
    XFCIMPORT static XFcBtSecurity * create();

    //! Sets security attributes for a given socket.
    /*!
     * \param aAddress sets security settings for this port.
     * \param aAuthent true of false values required.
     * \param aEnc true of false values required.
     * \param aAuthor true of false values required.
     * \return registered index for given socket if successful, or -1 otherwise.
     * \todo Support for multiple security settings
     * \note Only one security setting is currently supported (indices are not implemented yet).
     */
    XFCIMPORT INT32 registerSecurity(XFcAddress &aAddress, INT aAuthent, INT aEnc, INT aAuthor);

    //! Unregisters security settings.
    /*!
     * \param aIndex index to security settings.
     * \note Only one security setting is currently supported (indices are not implemented yet).
     */
    XFCIMPORT void unregisterSecurity(INT aIndex);

};


#endif // !XFCBTSECURITY_H_INCLUDED

