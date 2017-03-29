/*! \file-*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet host entry
 *
 * $Id: XFcInetHostEntry.h,v 1.8 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.8 $
 */

#ifndef XFCINETHOSTENTRY_H_INCLUDED
#define XFCINETHOSTENTRY_H_INCLUDED

#include <xfcore/net/socket/XFcHostEntry.h>

class XFcAddress;
class XFcName;


//! Holds inet address and host name.
class XFCDLLEXPORT XFcInetHostEntry : public XFcHostEntry
{
protected:

    //! Protected constructor.
    XFcInetHostEntry();

    //! Initializes XFcBtHostEntry.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT init();

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aAddress inet address.
     * \return 1 if successful, or 0 otherwise.
     */
    INT init(const XFcAddress &aAddress);

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aName host name.
     * \return 1 if successful, or 0 otherwise.
     */
    INT init(const XFcName &aName);

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aAddress inet address.
     * \param aName host name.
     * \return 1 if successful, or 0 otherwise.
     */
    INT init(const XFcAddress &aAddress, const XFcName &aName);

    //! Initializes XFcBtHostEntry.
    /*!
     * \param aHostEntry inet host entry.
     * \return 1 if successful, or 0 otherwise.
     */
    INT init(const XFcHostEntry &aHostEntry);

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcInetHostEntry();

    //! Static constructor.
     /*!
     * \return pointer to new object if succesful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHostEntry * create();

    //! Static constructor copying from existing address.
    /*!
     * \param aAddress inet address.
     * \return pointer to new object if succesful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHostEntry * create(const XFcAddress &aAddress);

    //! Static constructor copying from existing name.
    /*!
     * \param aName host name.
     * \return pointer to new object if succesful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHostEntry * create(const XFcName &aName);

    //! Static constructor copying frmo existing address and name.
    /*!
     * \param aAddress inet address.
     * \param aName host name.
     * \return pointer to new object if succesful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHostEntry * create(const XFcAddress &aAddress, const XFcName &aName);

    //! Static constructor copying from existing host entry.
    /*!
     * \param aHostentry inet host entry.
     * \return pointer to new object if succesful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetHostEntry * create(const XFcHostEntry &aHostEntry);

};


#endif // !XFCINETHOSTENTRY_H_INCLUDED

