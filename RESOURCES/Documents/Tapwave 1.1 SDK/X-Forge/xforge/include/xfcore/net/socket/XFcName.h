/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Host name base
 *
 * $Id: XFcName.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCNAME_H_INCLUDED
#define XFCNAME_H_INCLUDED


//! Holds bluetooth device or inet name.
class XFCDLLEXPORT XFcName
{
public:

    //! Constructor.
    XFCIMPORT XFcName();

    //! Destructor.

    XFCIMPORT ~XFcName();

    //! Name of device.
    XFCIMPORT CHAR8 mName[0x40];

    //! Length of the name.
    XFCIMPORT INT mLen;

};


#endif // !XFCNAME_H_INCLUDED

