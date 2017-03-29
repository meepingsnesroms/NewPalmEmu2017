/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Hardware identification class.
 * 
 * $Id: XFcHardwareId.h,v 1.5 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.5 $
 */

#ifndef XFC_CORE_XFCHARDWAREID_H_INCLUDED
#define XFC_CORE_XFCHARDWAREID_H_INCLUDED


//! Hardware identification flags; used by the XFcHardwareId class functions.
enum XFCHARDWAREIDFLAGS
{
    XFCHI_ANYID    = 1, //!< "Any" id.
    XFCHI_USERID   = 2, //!< User ID (such as SIM card).
    XFCHI_MEDIAID  = 4, //!< Media ID (such as CF card).
    XFCHI_DEVICEID = 8  //!< Device ID (such as IMEI code on a phone).
};


//! Static methods to uniquely identify the host device.
/*!
 * The XFcHardwareId class relies on the underlaying operating system
 * for its functionality. All platforms do not support all kinds of ids,
 * and ids may look different in different platforms. All ids are converted
 * to character strings for convenience.
 */
class XFCDLLEXPORT XFcHardwareId
{

public:

    //! Queries the available ids on this platform.
    /*!
     * \return combined value of available ids' flags, see XFCHARDWAREIDFLAGS.
     * \sa XFCHARDWAREIDFLAGS
     */
    XFCIMPORT static UINT32 queryAvailableIds();
    
    //! Returns device identification string.
    /*!
     * \param aIdType id type to request, see XFCHARDWAREIDFLAGS.
     * \return string containing a new copy of the requested id, or NULL if the request failed.
     *         Application should delete[] the returned string when it is not needed anymore.
     * \note On desktop windows platform you can create 'xfchi_userid.txt', 
     *       'xfchi_mediaid.txt' and 'xfchi_deviceid.txt' to override the contents of the ids.
     * \sa XFCHARDWAREIDFLAGS
     */
    XFCIMPORT static CHAR * readId(UINT32 aIdType);
};


#endif // !XFC_CORE_XFCXFCHARDWAREID_H_INCLUDED

