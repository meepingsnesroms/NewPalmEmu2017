/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Date/Time class.
 * 
 * $Id: XFcDateTime.h,v 1.7 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.7 $
 */

#ifndef XFC_CORE_XFCDATETIME_H_INCLUDED
#define XFC_CORE_XFCDATETIME_H_INCLUDED


//! Interface to the device's current date/time.
/*!
 * The XFcDateTime class relies on the underlaying operating system
 * for its functionality. If the operating system does not report
 * some information, that value is set to some sensible default value.
 */
class XFCDLLEXPORT XFcDateTime
{

public:

    //! Static constructor.
    /*! \note Sets object to the current date/time.
     */
    XFCIMPORT static XFcDateTime * create();

    //! Updates the contents of the object to current date/time.
    XFCIMPORT void update();

    UINT16 mYear;               //!< Year, in 4 (or more) decimal digits.
    UINT16 mMonth;              //!< Month, first month being 1.
    UINT16 mDay;                //!< Day, first day being 1.
    UINT16 mHour;               //!< Hour, 0 through 23, inclusive.
    UINT16 mMinute;             //!< Minute, 0 through 59, inclusive.
    UINT16 mSecond;             //!< Second, 0 through 59, inclusive.
    UINT16 mMillisecond;        //!< Millisecond, 0 through 999, inclusive.

protected:

    //! Protected constructor.
    XFCIMPORT XFcDateTime();
};


#endif // !XFC_CORE_XFCDATETIME_H_INCLUDED

