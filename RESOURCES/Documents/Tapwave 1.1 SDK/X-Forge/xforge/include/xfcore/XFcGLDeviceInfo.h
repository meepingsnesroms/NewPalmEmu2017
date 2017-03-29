/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief X-Forge Graphics Library device info.
 * 
 * $Id: XFcGLDeviceInfo.h,v 1.11 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.11 $
 */

#ifndef XFC_CORE_XFCGLDEVICEINFO_H_INCLUDED
#define XFC_CORE_XFCGLDEVICEINFO_H_INCLUDED


//! Device info features flags. 
/*!
 * \sa XFcGLDeviceInfo
 */
enum XFCGLDIFEATUREFLAGS
{
    //! Secondary buffer can be accessed.
    XFCGLDI_SECONDARY_ACCESS   = 0x00000001,
    //! Support for depth buffer.
    XFCGLDI_ZBUFFER            = 0x00000002,
    //! This is a full-screen anti-aliased device.
    XFCGLDI_FSAA               = 0x00000004,
    //! Support for flat-shaded polygons.
    XFCGLDI_FLAT               = 0x00000008,
    //! Support for gouraud-shaded polygons.
    XFCGLDI_GOURAUD            = 0x00000010,
    //! Support for linear texture mapping.
    XFCGLDI_LINEARTEXTURE      = 0x00000020,
    //! Support for perspective correct texture mapping.
    XFCGLDI_PERSPECTIVETEXTURE = 0x00000040,
    //! Support for gouraud-shaded texture mapping.
    XFCGLDI_GOURAUDTEXTURE     = 0x00000080,
    //! Support for 1-bit alpha texture format.
    XFCGLDI_TEXTURE1555        = 0x00000100,
    //! Support for gouraud-shaded 1-bit alpha texture.
    XFCGLDI_GOURAUDTEXTURE1555 = 0x00000200,
    //! Support for wireframe.
    XFCGLDI_WIREFRAME          = 0x00000400,
    //! Support for anti-aliased wireframe.
    XFCGLDI_AAWIREFRAME        = 0x00000800,
    //! Support for setrendertarget.
    XFCGLDI_SETRENDERTARGET    = 0x00001000
};


//! Device info blending support flags. 
/*!
 * \sa XFcGLDeviceInfo
 */
enum XFCGLDIBLENDFLAGS
{
    //! Support for ONE, ZERO blend mode.
    XFCGLDI_BLENDNONE          = 0x00000001,
    //! Support for SRCALPHA, INVSRCALPHA blend mode.
    XFCGLDI_BLENDALPHA         = 0x00000002,
    //! Support for ZERO, SRCCOLOR blend mode.
    XFCGLDI_BLENDMUL           = 0x00000004,
    //! Support for ONE, ONE blend mode.
    XFCGLDI_BLENDADD           = 0x00000008,
    //! Support for ZERO, INVSRCCOLOR blend mode.
    XFCGLDI_BLENDINVMUL        = 0x00000010
};


//! Information on a display device installed on system.
class XFcGLDeviceInfo
{
public:
     //! Link to the next device, or NULL if this was last.
    XFcGLDeviceInfo *mNext;
    //! Unique id for this device.
    UINT32 mDeviceId;
    //! Width of screen on this device.
    /*! \note May be different than physical screen due to memory
     *        limitations or FSAA.
     */
    UINT32 mDeviceWidth;
    //! Height of screen on this device.
    /*! \note May be different than physical screen due to memory
     *        limitations or FSAA.
     */
    UINT32 mDeviceHeight;
    //! Device's pixel format.
    UINT32 mDevicePixelFormat;

    //! Bit flags on supported features.
    /*! \sa XFCGLDIFEATUREFLAGS
     */    
    UINT32 mRenderFeatures;
    //! Bit flags on supported blending modes.
    /*! \sa XFCGLDIBLENDFLAGS
     */
    UINT32 mBlendModes;
    //! Bit flags on which features are faster than reference.
    /*! \sa XFCGLDIFEATUREFLAGS
     */    
    UINT32 mAcceleratedFeatures;
    //! Bit flags on which blend modes are faster than reference.
    /*! \sa XFCGLDIBLENDFLAGS
     */
    UINT32 mAcceleratedBlendModes;

    //! Preferability score for this device.
    /*! \li 0 = reference driver
     *  \li > 0 = accelerated
     *  \li < 0 = FSAA devices etc.
     */
    INT32 mPreferabilityScore;

    //! Printable name for this device.
    const CHAR *mPrintableName;
};


#endif // !XFC_CORE_XFCGLDEVICEINFO_H_INCLUDED

