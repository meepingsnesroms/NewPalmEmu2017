/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Used to pass application preferences to the core in xfcAppPrefs() call.
 * 
 * $Id: XFcAppPrefs.h,v 1.20 2003/08/18 11:48:18 jari Exp $
 * $Date: 2003/08/18 11:48:18 $
 * $Revision: 1.20 $
 */

#ifndef XFC_CORE_XFCAPPPREFS_H_INCLUDED
#define XFC_CORE_XFCAPPPREFS_H_INCLUDED



//! Used to pass application preferences to the core in xfcAppPrefs() call.
/*! Please note that the xfcAppPrefs() call may be invoked more than once in the
 *  application startup.
 */
class XFcAppPrefs
{

public:

    //! Total memory (in bytes). [Required]
    INT32 mTotalMemoryLimit;
    
    //! Max. memory resources may take (in bytes). [Required]
    INT32 mResourceMemoryLimit;

    //! Preferred screen width. Only affects the desktop windows.
    INT32 mPreferredWidth;

    //! Preferred screen height. Only affects the desktop windows.
    INT32 mPreferredHeight;

    //! Pointer to a string to be shown as title bar, if applicable.
    const CHAR *mTitleString;
    
    //! Application unique identifier. [Required for Symbian applications.]
    INT32 mUID;
    
    //! Minimum amount of extra free memory in bytes in the system after memory pool allocation.
    /*!
     * If the operating system (or other applications) can't get enough memory under
     * some Symbian platforms (at least), random applications will start crashing.
     * If the core cannot detect at least this much extra memory after the pool has been
     * allocated, the application will exit with an 'out of memory' error, just like if
     * there was not enough memory for the memory pool. (128KB recommended under Symbian)
     */
    INT32 mMinimumExtraMemory;

    //! Pointer to a string shown if memory pool allocation failed.
    /*!
     * If this parameter is NULL, the default error message will be rather technical,
     * and might not be useful for most end-users.
     */
    const CHAR *mOutOfMemoryErrorString;
};


#endif // !XFC_CORE_XFCAPPPREFS_H_INCLUDED

