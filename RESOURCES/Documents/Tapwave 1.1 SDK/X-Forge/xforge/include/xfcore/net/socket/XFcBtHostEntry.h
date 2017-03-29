/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth host entry
 *
 * $Id: XFcBtHostEntry.h,v 1.6 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.6 $
 */

#ifndef XFCBTHOSTENTRY_H_INCLUDED
#define XFCBTHOSTENTRY_H_INCLUDED

#include <xfcore/net/socket/XFcHostEntry.h>

class XFcAddress;
class XFcName;


//! Used to create bluetooth host entry.
/*!
 * Host entry holds address and name data. 
 */
class XFCDLLEXPORT XFcBtHostEntry : public XFcHostEntry
{
protected:

    //! Protected constructor.
    XFcBtHostEntry();

    //! Initializes XFcBtHostEntry.
    INT init();

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aAddress bluetooth address.
     */
    INT init(const XFcAddress &aAddress);

    //! Initializes XFcBtHostEntry.
    /*! 
     * \param aName device name.
     */
    INT init(const XFcName &aName);

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aAddress bluetooth address.
     * \param aName device name.
     */
    INT init(const XFcAddress &aAddress, const XFcName &aName);

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aHostEntry devices host entry.
     */
    INT init(const XFcHostEntry &aHostEntry);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtHostEntry();

    //! Creates XFcBtHostEntry object.
    XFCIMPORT static XFcBtHostEntry * create();

    //! Creates XFcBtHostEntry object.
    /*!
     * \param aAddress bluetooth address.
     */
    XFCIMPORT static XFcBtHostEntry * create(const XFcAddress &aAddress);

    //! Creates XFcBtHostEntry object.
    /*!
     * \param aName device name.
     */
    XFCIMPORT static XFcBtHostEntry * create(const XFcName &aName);

    //! Creates XFcBtHostEntry object.
    /*!
     * \param aAddress bluetooth address.
     * \param aName device name.
     */
    XFCIMPORT static XFcBtHostEntry * create(const XFcAddress &aAddress, const XFcName &aName);

    //! Creates XFcBtHostEntry object.
    /*!
     * \param aHostEntry bluetooth host address.
     */
    XFCIMPORT static XFcBtHostEntry * create(const XFcHostEntry &aHostEntry);

};


#endif // !XFCBTHOSTENTRY_H_INCLUDED

