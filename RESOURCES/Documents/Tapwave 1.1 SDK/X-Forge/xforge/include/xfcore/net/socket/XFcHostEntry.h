/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Host entry base
 *
 * $Id: XFcHostEntry.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCHOSTENTRY_H_INCLUDED
#define XFCHOSTENTRY_H_INCLUDED


#include <xfcore/net/socket/XFcName.h>

class XFcAddress;


//! Holds device name and device address information.
/*!
 * Used for device host entry information.
 * \note No alias support included.
 */
class XFCDLLEXPORT XFcHostEntry
{
protected:

    //! Holds name of the host.
    XFcName mName;
    
    //! Holds address of the host.
    XFcAddress *mAddress;

    //! Protected constructor.
    /*! \note Ensures abstract use of the class, as there is no public static constructor.
     */
    XFcHostEntry();

    //! Initializes mAddress with given address.
    void init(XFcAddress *aAddress);

public:
    
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcHostEntry();

    //! Gets host address.
    /*!
     * \return device address.
     */
    XFCIMPORT virtual const XFcAddress * const getAddress() const;
    
    //! Gets host address.
    /*!
     * \return device address.
     */
    XFCIMPORT virtual XFcAddress * getAddress();

    //! Gets host name.
    /*!
     * \return device name.
     */
    XFCIMPORT virtual const XFcName * const getName() const;

    //! Gets host name.
    /*!
     * \return device name.
     */
    XFCIMPORT virtual XFcName * const getName();

    //! Sets address.
    /*!
     * \param device address.
     */
    XFCIMPORT virtual void setAddress(const XFcAddress &aAddress);

    //! Sets name.
    /*!
     * \param device name.
     */
    XFCIMPORT virtual void setName(const XFcName &aName);

};


#endif // !XFCHOSTENTRY_H_INCLUDED

