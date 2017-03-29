/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief CPU info
 * 
 * $Id: XFcCPUInfo.h,v 1.8 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.8 $
 */

#ifndef XFC_CORE_XFCCPUINFO_H_INCLUDED
#define XFC_CORE_XFCCPUINFO_H_INCLUDED


#if (defined(__arm__) || defined(ARM) || defined(_ARM) || defined(__MARM__) || defined(__ARM4__)) && defined(XFC_USE_ARMASM) && defined(XFC_PLATFORM_WINCE)
extern "C" UINT32 xfcAsmIdRegisterRead();
#endif


//! Known CPU info types.
enum XFCCPUINFO_CPU
{
    XFCCPUINFO_UNDEFINED = 0,   //!< No CPU information available.
    XFCCPUINFO_ARM = 1,         //!< ARM CPU specific information can be requested.
};


class XFcCPUInfoARM;


class XFcCPUInfo
{

public:

    //! Static constructor.
    /*! \return New XFcCPUInfo object if creation was successful, or NULL if creation was unsuccessful.
     */
    static XFcCPUInfo * create();

    //! Destructor.
    ~XFcCPUInfo();

    //! Returns type of available CPU information.
    /*! \return One value from XFCCPUINFO_CPU enumeration. XFCCPUINFO_UNDEFINED if no CPU information is available.
     * \sa XFCCPUINFO_CPU
     */
    INT8 getValidField();

    //! Returns ARM CPU specific information.
    /*! \note Use only if getValidField() returns XFCCPUINFO_ARM.
     */ 
    XFcCPUInfoARM * getARMInfo();

protected:

    //! Determines the type of CPU information.
    /*! \sa XFCCPUINFO_CPU
     */
    INT8 mValidField;

    //! CPU information for ARM CPUs if mValidField equals XFCCPUINFO_ARM.
    XFcCPUInfoARM *mCPUInfoARM;

    //! Protected constructor.
    XFcCPUInfo();

};


#endif // !XFC_CORE_XFCCPUINFO_H_INCLUDED

