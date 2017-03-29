/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet host look up
 *
 * $Id: XFcInetHostResolver.h,v 1.7 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.7 $
 */

#ifndef XFCINETHOSTRESOLVER_H_INCLUDED
#define XFCINETHOSTRESOLVER_H_INCLUDED

#include <xfcore/net/socket/XFcHostResolver.h>

class XFcInetAddress;


//! Handles inet host resolution.
class XFCDLLEXPORT XFcInetHostResolver : public XFcHostResolver
{
protected:

    //! Protected constructor.
    XFcInetHostResolver();

    //! Initializes inet host resolver.
    /*!
     * \param aType host resolver type, see XFCHOSTRESOLVER.
     * \return 1 if initialization was successful, or 0 otherwise.
     */ 
    INT init(INT aType);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcInetHostResolver();

    //! Static constructor.
    XFCIMPORT static XFcInetHostResolver * create();

    //! Gets host by name or with ip.
    /*!
     * \param aString host name string or ip string, e.g. "127.0.0.1" or "www.fathammer.com".
     * \param aAddress address where resolved information is written.
     * \return 1 if query was successful, or 0 otherwise.
     */
    XFCIMPORT INT getHostByString(const CHAR8 *aString, XFcInetAddress &aAddress);

};


#endif // !XFCINETHOSTRESOLVER_H_INCLUDED

