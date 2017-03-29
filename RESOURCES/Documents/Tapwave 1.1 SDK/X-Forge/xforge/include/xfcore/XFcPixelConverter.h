/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Pixel format conversion functions/macros
 * 
 * $Id: XFcPixelConverter.h,v 1.24 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.24 $
 */

#ifndef XFC_CORE_XFCPIXELCONVERTER_H_INCLUDED
#define XFC_CORE_XFCPIXELCONVERTER_H_INCLUDED


// To build full eight bits from a 5-bit value, shift up by
// three and down by two and add together
// original:     00011111
// shifted up:   11111000
// shifted down: 00000111
// result:       11111111

//! Converts from 16bit 5:6:5 to 32bit x:8:8:8 format.
#define XFCPC_565_TO_X888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07e0) << 5) | (((srccolor) & 0x0600) >> 1) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3))

//! Converts from 16bit 5:6:5 to 16bit 1:5:5:5 format.
#define XFCPC_565_TO_1555(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0) >> 1) | (((srccolor) & 0xf800) >> 1) | 0x8000)

//! Converts from 16bit 5:6:5 to 32bit 8:8:8:8 format.
#define XFCPC_565_TO_8888(srccolor)  ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07e0) << 5) | (((srccolor) & 0x0600) >> 1) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | 0xff000000)
// ((((srccolor) & 0x001f)<<3) | (((srccolor) & 0x07e0)<<5) | (((srccolor) & 0xf800)<<8) | 0xff000000)

//! Converts from 16bit 5:6:5 to 32bit x:6:x:5:x:5 format.
#define XFCPC_565_TO_X6X5X5(srccolor) ((((srccolor) & 0x07e0) << 16) | (((srccolor) & 0xf81f)))

//! Converts from 16bit 5:6:5 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_565_TO_1X5X5X5(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0) << 15) | (((srccolor) & 0xf800) >> 1) | 0x80000000)

//! Converts from 16bit 5:6:5 to 16bit 5:5:x:5 format.
#define XFCPC_565_TO_55X5(srccolor) (srccolor & 0xffdf)

//! Converts from 16bit 5:6:5 to 16bit 5:5:1:5 format.
#define XFCPC_565_TO_5515(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0)) | (((srccolor) & 0xf800)) | 0x20)

//! Converts from 16bit 5:6:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_565_TO_PREMUL8888(srccolor)  ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07e0) << 5) | (((srccolor) & 0x0600) >> 1) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | 0xff000000)



//! Converts from 32bit x:8:8:8 to 16bit 5:6:5 format.
#define XFCPC_X888_TO_565(srccolor) ((((srccolor) & 0x0000f8) >> 3) | (((srccolor) & 0x00fc00) >> 5) | (((srccolor) & 0xf80000) >> 8))

//! Converts from 32bit x:8:8:8 to 16bit 1:5:5:5 format.
#define XFCPC_X888_TO_1555(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) >> 6) | (((srccolor) & 0x00f80000) >> 9) | 0x8000)

//! Converts from 32bit x:8:8:8 to 32bit 8:8:8:8 format.
#define XFCPC_X888_TO_8888(srccolor) (((srccolor) | 0xff000000))

//! Converts from 32bit x:8:8:8 to 32bit x:6:x:5:x:5 format.
#define XFCPC_X888_TO_X6X5X5(srccolor) ((((srccolor) & 0x0000f8) >> 3) | (((srccolor) & 0x00fc00) << 11) | (((srccolor) & 0xf80000) >> 8))

//! Converts from 32bit 8:8:8:8 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_X888_TO_1X5X5X5(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) << 10) | (((srccolor) & 0x00f80000) >> 9) | ((0x80000000)))

//! Converts from 32bit x:8:8:8 to 16bit 5:5:x:5 format.
#define XFCPC_X888_TO_55X5(srccolor) ((((srccolor) & 0x0000f8) >> 3) | (((srccolor) & 0x00f800) >> 5) | (((srccolor) & 0xf80000) >> 8))

//! Converts from 32bit x:8:8:8 to 16bit 5:5:1:5 format.
#define XFCPC_X888_TO_5515(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) >> 5) | (((srccolor) & 0x00f80000) >> 8) | 0x20)

//! Converts from 32bit x:8:8:8 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_X888_TO_PREMUL8888(srccolor) (((srccolor) | 0xff000000))



//! Converts from 16bit 1:5:5:5 to 16bit 5:6:5 format.
#define XFCPC_1555_TO_565(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x03e0) << 1) | (((srccolor) & 0x0200) >> 4) | (((srccolor) & 0x7c00) << 1))

//! Converts from 16bit 1:5:5:5 to 32bit x:8:8:8 format.
#define XFCPC_1555_TO_X888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x03e0) << 6) | (((srccolor) & 0x0380) << 1) | (((srccolor) & 0x7c00) << 9) | (((srccolor) & 0x7000) << 4))
// ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x03e0) << 6) | (((srccolor) & 0x7c00) << 9))

//! Converts from 16bit 1:5:5:5 to 32bit 8:8:8:8 format.
#define XFCPC_1555_TO_8888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x03e0) << 6) | (((srccolor) & 0x0380) << 1) | (((srccolor) & 0x7c00) << 9) | (((srccolor) & 0x7000) << 4) | ((srccolor & 0x8000) ? 0xff000000 : 0))
// ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x03e0) << 6) |
// (((srccolor) & 0x7c00) << 9) | ((srccolor & 0x8000) ? 0xff000000 : 0))

//! Converts from 16bit 1:5:5:5 to 32bit x:5:x:6:x:5 format.
#define XFCPC_1555_TO_X6X5X5(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x000003e0) << 17) | (((srccolor) & 0x00000200) << 12) | (((srccolor) & 0x00007c00) << 1))

//! Converts from 16bit 1:5:5:5 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_1555_TO_1X5X5X5(srccolor) ((((srccolor) & 0x7c1f)) | (((srccolor) & 0x83e0) << 16))

//! Converts from 16bit 1:5:5:5 to 16bit 5:5:x:5 format.
#define XFCPC_1555_TO_55X5(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x7fe0) << 1))

//! Converts from 16bit 1:5:5:5 to 16bit 5:5:1:5 format.
#define XFCPC_1555_TO_5515(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x7fe0) << 1) | (((srccolor) & 0x8000) >> 10))

//! Converts from 16bit 1:5:5:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_1555_TO_PREMUL8888(srccolor) (((srccolor) & 0x8000) ? ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x03e0) << 6) | (((srccolor) & 0x0380) << 1) | (((srccolor) & 0x7c00) << 9) | (((srccolor) & 0x7000) << 4) | 0xff000000) : 0)



//! Converts from 32bit 8:8:8:8 to 32bit x:8:8:8 format.
#define XFCPC_8888_TO_X888(srccolor) (((srccolor) & 0x00ffffff))

//! Converts from 32bit 8:8:8:8 to 16bit 1:5:5:5 format.
#define XFCPC_8888_TO_1555(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) >> 6) | (((srccolor) & 0x00f80000) >> 9) | (((srccolor) & 0x80000000) >> 16))

//! Converts from 32bit 8:8:8:8 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_8888_TO_1X5X5X5(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) << 10) | (((srccolor) & 0x00f80000) >> 9) | (((srccolor) & 0x80000000)))

//! Converts from 32bit 8:8:8:8 to 16bit 5:5:1:5 format.
#define XFCPC_8888_TO_5515(srccolor) ((((srccolor) & 0x000000f8) >> 3) | (((srccolor) & 0x0000f800) >> 5) | (((srccolor) & 0x00f80000) >> 8) | (((srccolor) & 0x80000000) >> 26))

//! Converts from 32bit 8:8:8:8 to 32bit premultipled x:8:8:8 format.
/*
#define XFCPC_8888_TO_PREMUL8888(srccolor,resultcolor) { \
    UINT32 a = (srccolor) & 0xff000000; \
    UINT32 alpha = a >> 24;
    UINT32 r = (srccolor) & 0xff0000; \
    UINT32 g = (srccolor) & 0xff00; \
    UINT32 b = (srccolor) & 0xff; \
 \
    UINT32 i = alpha * r + (128 << 16); \
    r = (( i + ((i >> 8) & 0xffff0000) ) >> 8) & 0xff0000; \
 \
    i = alpha * g + (128 << 8); \
    g = (( i + ((i >> 8) & 0xffff00) ) >> 8) & 0xff00; \
 \
    i = alpha * b + 128; \
    b = ( i + (i >> 8) ) >> 8; \
\
    resultcolor = a | r | g | b; \
}
*/

#define XFCPC_8888_TO_PREMUL8888(srccolor,resultcolor) { \
    UINT32 __a = (srccolor) & 0xff000000; \
    UINT32 __alpha = __a >> 24; \
    UINT32 __rb = (srccolor) & 0x00ff00ff; \
    UINT32 __g = (srccolor) & 0x0000ff00; \
 \
    UINT32 __i = __alpha * __rb + ((128 << 16) + 128); \
    __rb = (( __i + ((__i >> 8) & 0x00ff00ff) ) >> 8) & 0x00ff00ff; \
 \
    __i = __alpha * __g + (128 << 8); \
    __g = (( __i + ((__i >> 8) & 0x0000ff00) ) >> 8) & 0x0000ff00; \
 \
    resultcolor = __a | __rb | __g; \
}



//! Converts from 32bit x:6:x:5:x:5 to 16bit 5:6:5 format.
#define XFCPC_X6X5X5_TO_565(srccolor) ((((srccolor) & 0x07e00000) >> 16) | (((srccolor) & 0x0000f81f)))

//! Converts from 32bit x:6:x:5:x:5 to 32bit x:8:8:8 format.
#define XFCPC_X6X5X5_TO_X888(srccolor) ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x0000001c) >> 2) | (((srccolor) & 0x07e00000) >> 11) | (((srccolor) & 0x06000000) >> 17) | (((srccolor) & 0x0000f800) << 8) | (((srccolor) & 0x0000e000) << 3))
// ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x07e00000) >> 11) | (((srccolor) & 0x0000f800) << 8))

//! Converts from 32bit x:6:x:5:x:5 to 16bit 1:5:5:5 format.
#define XFCPC_X6X5X5_TO_1555(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x07c00000) >> 17) | (((srccolor) & 0x0000f800) >> 1) | 0x8000)

//! Converts from 32bit x:6:x:5:x:5 to 32bit 8:8:8:8 format.
#define XFCPC_X6X5X5_TO_8888(srccolor) ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x07e00000) >> 11) | (((srccolor) & 0x0000f800) << 8) | 0xff000000)

//! Converts from 32bit x:6:x:5:x:5 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_X6X5X5_TO_1X5X5X5(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x07e00000) >> 1) | (((srccolor) & 0x00007c00) >> 1) | 0x8000)

//! Converts from 32bit x:6:x:5:x:5 to 16bit 5:5:x:5 format.
#define XFCPC_X6X5X5_TO_55X5(srccolor) ((((srccolor) & 0x07c00000) >> 16) | (((srccolor) & 0x0000f81f)))

//! Converts from 32bit x:6:x:5:x:5 to 16bit 1:5:5:5 format.
#define XFCPC_X6X5X5_TO_5515(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x07c00000) >> 16) | (((srccolor) & 0x0000f800)) | 0x20)

//! Converts from 32bit x:6:x:5:x:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_X6X5X5_TO_PREMUL8888(srccolor) ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x07e00000) >> 11) | (((srccolor) & 0x0000f800) << 8) | 0xff000000)



//! Converts from 32bit 1:x:5:x:5:x:5 to 16bit 5:6:5 format.
#define XFCPC_1X5X5X5_TO_565(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x03e00000) >> 15) | (((srccolor) & 0x02000000) >> 21) | (((srccolor) & 0x00007c00) << 1))

//! Converts from 32bit 1:x:5:x:5:x:5 to 32bit x:8:8:8 format.
#define XFCPC_1X5X5X5_TO_X888(srccolor) ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x0000001c) >> 2) | (((srccolor) & 0x03e00000) >> 10) | (((srccolor) & 0x03800000) >> 15) | (((srccolor) & 0x00007c00) << 9) | (((srccolor) & 0x00007000) << 4))
// ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x03e00000) >> 10) | (((srccolor) & 0x00007c00) << 1))

//! Converts from 32bit 1:x:5:x:5:x:5 to 16bit 1:5:5:5 format.
#define XFCPC_1X5X5X5_TO_1555(srccolor) ((((srccolor) & 0x00007c1f)) | (((srccolor) & 0x83e00000) >> 16))

//! Converts from 32bit 1:x:5:x:5:x:5 to 32bit 8:8:8:8 format.
#define XFCPC_1X5X5X5_TO_8888(srccolor) ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x0000001c) >> 2) | (((srccolor) & 0x03e00000) >> 10) | (((srccolor) & 0x03800000) >> 15) | (((srccolor) & 0x00007c00) << 9) | (((srccolor) & 0x00007000) << 4) | (((srccolor) & 0x80000000) ? 0xff000000 : 0))
// ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x03e00000) >> 10) |
// (((srccolor) & 0x00007C00) << 1) | (((srccolor) & 0x80000000) ? 0xff000000 : 0))

//! Converts from 32bit 1:x:5:x:5:x:5 to 32bit x:6:x:5:x:5 format.
#define XFCPC_1X5X5X5_TO_X6X5X5(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x03e00000) << 1) | (((srccolor) & 0x02000000) >> 4) | (((srccolor) & 0x00007c00) << 1))

//! Converts from 32bit 1:x:5:x:5:x:5 to 16bit 5:5:x:5 format.
#define XFCPC_1X5X5X5_TO_55X5(srccolor) ((((srccolor) & 0x0000001f)) | (((srccolor) & 0x03e00000) >> 15) | (((srccolor) & 0x00007c00) << 1))

//! Converts from 16bit 1:x:5:x:5:x:5 to 32bit 5:5:1:5 format.
#define XFCPC_1X5X5X5_TO_5515(srccolor) ((((srccolor) & 0x07c00000) >> 16) | (((srccolor) & 0xf81f)) | (((srccolor) & 0x80000000) >> 26));

//! Converts from 32bit 1:x:5:x:5:x:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_1X5X5X5_TO_PREMUL8888(srccolor) (((srccolor) & 0x80000000) ? ((((srccolor) & 0x0000001f) << 3) | (((srccolor) & 0x0000001c) >> 2) | (((srccolor) & 0x03e00000) >> 10) | (((srccolor) & 0x03800000) >> 15) | (((srccolor) & 0x00007c00) << 9) | (((srccolor) & 0x00007000) << 4) | 0xff000000) : 0)



//! Converts from 16bit 5:5:x:5 to 16bit 5:6:5 format.
#define XFCPC_55X5_TO_565(srccolor) (srccolor | (((srccolor) & 0x0400) >> 5))

//! Converts from 16bit 5:5:x:5 to 32bit x:8:8:8 format.
#define XFCPC_55X5_TO_X888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | ((srccolor) & 0x0700) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3))

//! Converts from 16bit 5:5:x:5 to 16bit 1:5:5:5 format.
#define XFCPC_55X5_TO_1555(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0) >> 1) | (((srccolor) & 0xf800) >> 1) | 0x8000)

//! Converts from 16bit 5:5:x:5 to 32bit 8:8:8:8 format.
#define XFCPC_55X5_TO_8888(srccolor)  ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | ((srccolor) & 0x0700) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | 0xff000000)

//! Converts from 16bit 5:5:x:5 to 32bit x:6:x:5:x:5 format.
#define XFCPC_55X5_TO_X6X5X5(srccolor) ((((srccolor) & 0x07c0) << 16) | (((srccolor) & 0x0400) << 11) | (((srccolor) & 0xf81f)))

//! Converts from 16bit 5:5:x:5 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_55X5_TO_1X5X5X5(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0) << 15) | (((srccolor) & 0xf800) >> 1) | 0x80000000)

//! Converts from 16bit 5:5:x:5 to 16bit 5:5:1:5 format.
#define XFCPC_55X5_TO_5515(srccolor) (srccolor | 0x20)

//! Converts from 16bit 5:5:x:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_55X5_TO_PREMUL8888(srccolor)  ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | ((srccolor) & 0x0700) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | 0xff000000)



//! Converts from 16bit 5:5:1:5 to 16bit 5:6:5 format.
#define XFCPC_5515_TO_565(srccolor) (((srccolor) &  0xffdf) | (((srccolor) & 0x400) >> 5))
// #define XFCPC_5515_TO_565(srccolor) ((((srccolor) & 0x001f)) | (((srccolor) & 0x07c0) << 1) | (((srccolor) & 0x0400) >> 5) | (((srccolor) & 0xf800)))

//! Converts from 16bit 5:5:1:5 to 32bit x:8:8:8 format.
#define XFCPC_5515_TO_X888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | (((srccolor) & 0x0700)) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3))

//! Converts from 16bit 5:5:1:5 to 16bit 1:5:5:5 format.
#define XFCPC_5515_TO_1555(srccolor) (((srccolor) &  0x001f) | (((srccolor) & 0x20) << 10) | (((srccolor) & 0xffc0) >> 1))

//! Converts from 16bit 5:5:1:5 to 32bit 8:8:8:8 format.
#define XFCPC_5515_TO_8888(srccolor) ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | (((srccolor) & 0x0700)) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | ((srccolor & 0x20) ? 0xff000000 : 0))

//! Converts from 16bit 5:5:1:5 to 32bit x:5:x:6:x:5 format.
#define XFCPC_5515_TO_X6X5X5(srccolor) ((((srccolor) & 0x0000f81f)) | (((srccolor) & 0x000007c0) << 16) | (((srccolor) & 0x00000400) << 11))

//! Converts from 16bit 1:5:5:5 to 32bit 1:x:5:x:5:x:5 format.
#define XFCPC_5515_TO_1X5X5X5(srccolor) ((((srccolor) & 0x07c0) << 16) | (((srccolor) & 0xf81f)) | (((srccolor) & 0x0020) << 26));

//! Converts from 16bit 5:5:1:5 to 16bit 5:5:x:5 format.
#define XFCPC_5515_TO_55X5(srccolor) (srccolor & 0xffdf)

//! Converts from 16bit 5:5:1:5 to 32bit premultiplied 8:8:8:8 format.
#define XFCPC_5515_TO_PREMUL8888(srccolor) (((srccolor) & 0x20) ? ((((srccolor) & 0x001f) << 3) | (((srccolor) & 0x001c) >> 2) | (((srccolor) & 0x07c0) << 5) | (((srccolor) & 0x0700)) | (((srccolor) & 0xf800) << 8) | (((srccolor) & 0xe000) << 3) | 0xff000000) : 0)



//! Converts from 32bit premultiplied 8:8:8:8 to 32bit 8:8:8:8 format.
/*! Conversions to other formats can be either done using XFCPC_8888_TO_* or XFCPC_X888_TO_*
 *  macros, or first converting to 8:8:8:8 format with this and then to correct target format.
 */
#define XFCPC_PREMUL8888_TO_8888(srccolor,resultcolor) { \
    UINT32 __a = srccolor & 0xff000000; \
 \
    if (__a == 0) \
        resultcolor = 0x00ffffff; \
    else if (__a == 0xff000000) \
        resultcolor = srccolor; \
    else \
    { \
        XFcFixed __invAlpha; \
        __invAlpha.mValue = 0xff0000; \
        __invAlpha = __invAlpha / (INT32)(__a >> 24); \
 \
        XFcFixed __r,__g,__b; \
        __r.mValue = (srccolor) & 0x00ff0000; \
        __g.mValue = ((srccolor) & 0x0000ff00) << 8; \
        __b.mValue = ((srccolor) & 0x000000ff) << 16; \
 \
        __r *= __invAlpha; \
        __g *= __invAlpha; \
        __b *= __invAlpha; \
 \
        resultcolor = __a | (__r.mValue & 0x00ff0000) | ((__g.mValue & 0x00ff0000) >> 8) | ((__b.mValue & 0x00ff0000) >> 16);\
    } \
 \
}

//! Converts from 32bit premultiplied 8:8:8:8 to 32bit 8:8:8:8 format, using an inversion table instead of division.
/*! Inversion table should be a table of 256 XFcFixed's, defined as division between
 *  255 and n (ranging from 0 to 255).
 */
#define XFCPC_PREMUL8888_TO_8888_TABLELOOKUP(srccolor,resultcolor,invtable) { \
    UINT32 __a = srccolor & 0xff000000; \
 \
    if (__a == 0) \
        resultcolor = 0x00ffffff; \
    else if (__a == 0xff000000) \
        resultcolor = srccolor; \
    else \
    { \
        XFcFixed __invAlpha; \
        __invAlpha = invtable[(INT32)(__a >> 24)]; \
 \
        XFcFixed __r,__g,__b; \
        __r.mValue = (srccolor) & 0x00ff0000; \
        __g.mValue = ((srccolor) & 0x0000ff00) << 8; \
        __b.mValue = ((srccolor) & 0x000000ff) << 16; \
 \
        __r *= __invAlpha; \
        __g *= __invAlpha; \
        __b *= __invAlpha; \
 \
        resultcolor = __a | (__r.mValue & 0x00ff0000) | ((__g.mValue & 0x00ff0000) >> 8) | ((__b.mValue & 0x00ff0000) >> 16);\
    } \
 \
}


//! Utility for pixel format conversions.
/*! Due to the obvious overhead this is mostly for convenience class,
 *  and not meant for heavy realtime use.
 * \note Pixel format conversions tend to cause loss of information, especially for the alpha values.
 * \par
 * Pixel format explanation:
 * \code
 *        565 - 16bit r:g:b format
 *       55X5 - 16bit r:g:x:b format
 *       X888 - 32bit x:r:g:b format (alpha ignored)
 *     X6X5X5 - 32bit 565565 bit format that's handy for fast 16bit image manipulation (XGXRXB)
 * \endcode
 * \code
 *       8888 - 32bit a:r:g:b format
 *       1555 - 16bit a:r:g:b format
 *       5515 - 16bit r:g:a:b format
 *    1X5X5X5 - 32bit 1556555 bit format, same as above, but with alpha on topmost bit (AXGXRXB)
 * Premul8888 - 32bit a:r:g:b format, color values are premultiplied with alpha
 * \endcode
 * See the XFCGFXFORMAT enumeration for graphics format constants.
 * \sa XFCGFXFORMAT
 */
 
typedef UINT32 (*xfcPixelConversionFunction)(UINT32);
typedef void (*xfcPixelBufferConversionFunction)(void *, void *, INT32);
 
class XFCDLLEXPORT XFcPixelConverter
{
public:
    // Pixel conversion functions

    //! Converts a pixel from 565 to X888 format.
    XFCIMPORT static UINT32 convert565ToX888(UINT32);
    //! Converts a pixel from 565 to 1555 format.
    XFCIMPORT static UINT32 convert565To1555(UINT32);
    //! Converts a pixel from 565 to 8888 format.
    XFCIMPORT static UINT32 convert565To8888(UINT32);
    //! Converts a pixel from 565 to X6X5X5 format.
    XFCIMPORT static UINT32 convert565ToX6X5X5(UINT32);
    //! Converts a pixel from 565 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convert565To1X5X5X5(UINT32);
    //! Converts a pixel from 565 to 55X5 format.
    XFCIMPORT static UINT32 convert565To55X5(UINT32);
    //! Converts a pixel from 565 to 5515 format.
    XFCIMPORT static UINT32 convert565To5515(UINT32);
    //! Converts a pixel from 565 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convert565ToPremul8888(UINT32);

    //! Converts a pixel from X888 to 565 format.
    XFCIMPORT static UINT32 convertX888To565(UINT32);
    //! Converts a pixel from X888 to 1555 format.
    XFCIMPORT static UINT32 convertX888To1555(UINT32);
    //! Converts a pixel from X888 to 8888 format.
    XFCIMPORT static UINT32 convertX888To8888(UINT32);
    //! Converts a pixel from X888 to X6X5X5 format.
    XFCIMPORT static UINT32 convertX888ToX6X5X5(UINT32);
    //! Converts a pixel from X888 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convertX888To1X5X5X5(UINT32);
    //! Converts a pixel from X888 to 55X5 format.
    XFCIMPORT static UINT32 convertX888To55X5(UINT32);
    //! Converts a pixel from X888 to 5515 format.
    XFCIMPORT static UINT32 convertX888To5515(UINT32);
    //! Converts a pixel from X888 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convertX888ToPremul8888(UINT32);

    //! Converts a pixel from 1555 to 565 format.
    XFCIMPORT static UINT32 convert1555To565(UINT32);
    //! Converts a pixel from 1555 to X888 format.
    XFCIMPORT static UINT32 convert1555ToX888(UINT32);
    //! Converts a pixel from 1555 to 8888 format.
    XFCIMPORT static UINT32 convert1555To8888(UINT32);
    //! Converts a pixel from 1555 to X6X5X5 format.
    XFCIMPORT static UINT32 convert1555ToX6X5X5(UINT32);
    //! Converts a pixel from 1555 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convert1555To1X5X5X5(UINT32);
    //! Converts a pixel from 1555 to 55X5 format.
    XFCIMPORT static UINT32 convert1555To55X5(UINT32);
    //! Converts a pixel from 1555 to 5515 format.
    XFCIMPORT static UINT32 convert1555To5515(UINT32);
    //! Converts a pixel from 1555 to premultipled 8888 format.
    XFCIMPORT static UINT32 convert1555ToPremul8888(UINT32);

    //! Converts a pixel from 8888 to X888 format.
    XFCIMPORT static UINT32 convert8888ToX888(UINT32);
    //! Converts a pixel from 8888 to 1555 format.
    XFCIMPORT static UINT32 convert8888To1555(UINT32);
    //! Converts a pixel from 8888 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convert8888To1X5X5X5(UINT32);
    //! Converts a pixel from 8888 to 5515 format.
    XFCIMPORT static UINT32 convert8888To5515(UINT32);
    //! Converts a pixel from 8888 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convert8888ToPremul8888(UINT32);

    //! Converts a pixel from X6X5X5 to 565 format.
    XFCIMPORT static UINT32 convertX6X5X5To565(UINT32);
    //! Converts a pixel from X6X5X5 to X888 format.
    XFCIMPORT static UINT32 convertX6X5X5ToX888(UINT32);
    //! Converts a pixel from X6X5X5 to 1555 format.
    XFCIMPORT static UINT32 convertX6X5X5To1555(UINT32);
    //! Converts a pixel from X6X5X5 to 8888 format.
    XFCIMPORT static UINT32 convertX6X5X5To8888(UINT32);
    //! Converts a pixel from X6X5X5 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convertX6X5X5To1X5X5X5(UINT32);
    //! Converts a pixel from X6X5X5 to 55X5 format.
    XFCIMPORT static UINT32 convertX6X5X5To55X5(UINT32);
    //! Converts a pixel from X6X5X5 to 5515 format.
    XFCIMPORT static UINT32 convertX6X5X5To5515(UINT32);
    //! Converts a pixel from X6X5X5 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convertX6X5X5ToPremul8888(UINT32);

    //! Converts a pixel from 1X5X5X5 to 565 format.
    XFCIMPORT static UINT32 convert1X5X5X5To565(UINT32);
    //! Converts a pixel from 1X5X5X5 to X888 format.
    XFCIMPORT static UINT32 convert1X5X5X5ToX888(UINT32);
    //! Converts a pixel from 1X5X5X5 to 1555 format.
    XFCIMPORT static UINT32 convert1X5X5X5To1555(UINT32);
    //! Converts a pixel from 1X5X5X5 to 8888 format.
    XFCIMPORT static UINT32 convert1X5X5X5To8888(UINT32);
    //! Converts a pixel from 1X5X5X5 to X6X5X5 format.
    XFCIMPORT static UINT32 convert1X5X5X5ToX6X5X5(UINT32);
    //! Converts a pixel from 1X5X5X5 to 55X5 format.
    XFCIMPORT static UINT32 convert1X5X5X5To55X5(UINT32);
    //! Converts a pixel from 1X5X5X5 to 5515 format.
    XFCIMPORT static UINT32 convert1X5X5X5To5515(UINT32);
    //! Converts a pixel from 1X5X5X5 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convert1X5X5X5ToPremul8888(UINT32);

    //! Converts a pixel from 55X5 to 565 format.
    XFCIMPORT static UINT32 convert55X5To565(UINT32);
    //! Converts a pixel from 55X5 to X888 format.
    XFCIMPORT static UINT32 convert55X5ToX888(UINT32);
    //! Converts a pixel from 55X5 to 1555 format.
    XFCIMPORT static UINT32 convert55X5To1555(UINT32);
    //! Converts a pixel from 55X5 to 8888 format.
    XFCIMPORT static UINT32 convert55X5To8888(UINT32);
    //! Converts a pixel from 55X5 to X6X5X5 format.
    XFCIMPORT static UINT32 convert55X5ToX6X5X5(UINT32);
    //! Converts a pixel from 55X5 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convert55X5To1X5X5X5(UINT32);
    //! Converts a pixel from 55X5 to 5515 format.
    XFCIMPORT static UINT32 convert55X5To5515(UINT32);
    //! Converts a pixel from 55X5 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convert55X5ToPremul8888(UINT32);

    //! Converts a pixel from 5515 to 565 format.
    XFCIMPORT static UINT32 convert5515To565(UINT32);
    //! Converts a pixel from 5515 to X888 format.
    XFCIMPORT static UINT32 convert5515ToX888(UINT32);
    //! Converts a pixel from 5515 to 1555 format.
    XFCIMPORT static UINT32 convert5515To1555(UINT32);
    //! Converts a pixel from 5515 to 8888 format.
    XFCIMPORT static UINT32 convert5515To8888(UINT32);
    //! Converts a pixel from 5515 to X6X5X5 format.
    XFCIMPORT static UINT32 convert5515ToX6X5X5(UINT32);
    //! Converts a pixel from 5515 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convert5515To1X5X5X5(UINT32);
    //! Converts a pixel from 5515 to 55X5 format.
    XFCIMPORT static UINT32 convert5515To55X5(UINT32);
    //! Converts a pixel from 5515 to premultiplied 8888 format.
    XFCIMPORT static UINT32 convert5515ToPremul8888(UINT32);

    //! Converts a pixel from premultiplied 8888 to 1555 format.
    XFCIMPORT static UINT32 convertPremul8888To1555(UINT32);
    //! Converts a pixel from premultiplied 8888 to 8888 format.
    XFCIMPORT static UINT32 convertPremul8888To8888(UINT32);
    //! Converts a pixel from premultiplied 8888 to 1X5X5X5 format.
    XFCIMPORT static UINT32 convertPremul8888To1X5X5X5(UINT32);
    //! Converts a pixel from premultiplied 8888 to 5515 format.
    XFCIMPORT static UINT32 convertPremul8888To5515(UINT32);

    //! Copies the pixel value.
    XFCIMPORT static UINT32 copyPixel(UINT32);

    // Buffer conversion functions. Only conversions to and from 55X5 and Premul8888 use
    // conversion macros internally, others used pixel conversion functions.
    
    //! Converts a buffer of pixels from 565 to X888 format.
    XFCIMPORT static void convertBuffer565ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to 1555 format.
    XFCIMPORT static void convertBuffer565To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to 8888 format.
    XFCIMPORT static void convertBuffer565To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to X6X5X5 format.
    XFCIMPORT static void convertBuffer565ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to 1X5X5X5 format.
    XFCIMPORT static void convertBuffer565To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to 55X5 format.
    XFCIMPORT static void convertBuffer565To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to 5515 format.
    XFCIMPORT static void convertBuffer565To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 565 to premultiplied 8888 format.
    XFCIMPORT static void convertBuffer565ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from X888 to 565 format.
    XFCIMPORT static void convertBufferX888To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to 1555 format.
    XFCIMPORT static void convertBufferX888To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to 8888 format.
    XFCIMPORT static void convertBufferX888To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to X6X5X5 format.
    XFCIMPORT static void convertBufferX888ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to 1X5X5X5 format.
    XFCIMPORT static void convertBufferX888To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to 55X5 format.
    XFCIMPORT static void convertBufferX888To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to 5515 format.
    XFCIMPORT static void convertBufferX888To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X888 to premultiplied 8888 format.
    XFCIMPORT static void convertBufferX888ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from 1555 to 565 format.
    XFCIMPORT static void convertBuffer1555To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to X888 format.
    XFCIMPORT static void convertBuffer1555ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to 8888 format.
    XFCIMPORT static void convertBuffer1555To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to X6X5X5 format.
    XFCIMPORT static void convertBuffer1555ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to 1X5X5X5 format.
    XFCIMPORT static void convertBuffer1555To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to 55X5 format.
    XFCIMPORT static void convertBuffer1555To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to 5515 format.
    XFCIMPORT static void convertBuffer1555To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1555 to premultipled 8888 format.
    XFCIMPORT static void convertBuffer1555ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from 8888 to X888 format.
    XFCIMPORT static void convertBuffer8888ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 8888 to 1555 format.
    XFCIMPORT static void convertBuffer8888To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 8888 to 1X5X5X5 format.
    XFCIMPORT static void convertBuffer8888To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 8888 to 5515 format.
    XFCIMPORT static void convertBuffer8888To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 8888 to premultiplied 8888 format.
    XFCIMPORT static void convertBuffer8888ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from X6X5X5 to 565 format.
    XFCIMPORT static void convertBufferX6X5X5To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to X888 format.
    XFCIMPORT static void convertBufferX6X5X5ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to 1555 format.
    XFCIMPORT static void convertBufferX6X5X5To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to 8888 format.
    XFCIMPORT static void convertBufferX6X5X5To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to 1X5X5X5 format.
    XFCIMPORT static void convertBufferX6X5X5To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to 55X5 format.
    XFCIMPORT static void convertBufferX6X5X5To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to 5515 format.
    XFCIMPORT static void convertBufferX6X5X5To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from X6X5X5 to premultiplied 8888 format.
    XFCIMPORT static void convertBufferX6X5X5ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from 1X5X5X5 to 565 format.
    XFCIMPORT static void convertBuffer1X5X5X5To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to X888 format.
    XFCIMPORT static void convertBuffer1X5X5X5ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to 1555 format.
    XFCIMPORT static void convertBuffer1X5X5X5To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to 8888 format.
    XFCIMPORT static void convertBuffer1X5X5X5To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to X6X5X5 format.
    XFCIMPORT static void convertBuffer1X5X5X5ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to 55X5 format.
    XFCIMPORT static void convertBuffer1X5X5X5To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to 5515 format.
    XFCIMPORT static void convertBuffer1X5X5X5To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 1X5X5X5 to premultiplied 8888 format.
    XFCIMPORT static void convertBuffer1X5X5X5ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from 55X5 to 565 format.
    XFCIMPORT static void convertBuffer55X5To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to X888 format.
    XFCIMPORT static void convertBuffer55X5ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to 1555 format.
    XFCIMPORT static void convertBuffer55X5To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to 8888 format.
    XFCIMPORT static void convertBuffer55X5To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to X6X5X5 format.
    XFCIMPORT static void convertBuffer55X5ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to 1X5X5X5 format.
    XFCIMPORT static void convertBuffer55X5To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to 5515 format.
    XFCIMPORT static void convertBuffer55X5To5515(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 55X5 to premultiplied 8888 format.
    XFCIMPORT static void convertBuffer55X5ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from 5515 to 565 format.
    XFCIMPORT static void convertBuffer5515To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to X888 format.
    XFCIMPORT static void convertBuffer5515ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to 1555 format.
    XFCIMPORT static void convertBuffer5515To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to 8888 format.
    XFCIMPORT static void convertBuffer5515To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to X6X5X5 format.
    XFCIMPORT static void convertBuffer5515ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to 1X5X5X5 format.
    XFCIMPORT static void convertBuffer5515To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to 55X5 format.
    XFCIMPORT static void convertBuffer5515To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from 5515 to premultiplied 8888 format.
    XFCIMPORT static void convertBuffer5515ToPremul8888(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a buffer of pixels from premultiplied 8888 to 565 format.
    XFCIMPORT static void convertBufferPremul8888To565(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to X888 format.
    XFCIMPORT static void convertBufferPremul8888ToX888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to 1555 format.
    XFCIMPORT static void convertBufferPremul8888To1555(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to 8888 format.
    XFCIMPORT static void convertBufferPremul8888To8888(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to X6X5X5 format.
    XFCIMPORT static void convertBufferPremul8888ToX6X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to 1X5X5X5 format.
    XFCIMPORT static void convertBufferPremul8888To1X5X5X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to 55X5 format.
    XFCIMPORT static void convertBufferPremul8888To55X5(void *aSource, void *aTarget, INT32 aCount);
    //! Converts a buffer of pixels from premultiplied 8888 to 5515 format.
    XFCIMPORT static void convertBufferPremul8888To5515(void *aSource, void *aTarget, INT32 aCount);

    //! Copies INT16 buffer to INT16 buffer
    XFCIMPORT static void copyBuffer16(void *aSource, void *aTarget, INT32 aCount);
    //! Copies INT32 buffer to INT32 buffer
    XFCIMPORT static void copyBuffer32(void *aSource, void *aTarget, INT32 aCount);

    //! Converts a single pixel between two specified pixel formats.
    /*!
     * \param aSource source pixel.
     * \param aSourceFormat source buffer pixel format, see XFCGFXFORMAT.
     * \param aTargetFormat target buffer pixel format, see XFCGFXFORMAT.
     * \return converted pixel in the requested target format.
     * \sa XFCGFXFORMAT
     * \note this is not meant to be fast. Please use the XFCPC_ macros from
     *       XFcPixelConverter.h to perform fast operations.
     */
    XFCIMPORT static UINT32 convert(UINT32 aSource, INT32 aSourceFormat, INT32 aTargetFormat);

    //! Converts a buffer of pixels between two specified pixel formats.
    /*!
     * \param aSource source buffer.
     * \param aTarget target buffer.
     * \param aCount number of pixels to convert.
     * \param aSourceFormat source buffer pixel format, see XFCGFXFORMAT.
     * \param aTargetFormat target buffer pixel format, see XFCGFXFORMAT.
     * \sa XFCGFXFORMAT
     */
    XFCIMPORT static void convertBuffer(void *aSource, void *aTarget, INT32 aCount,
                                        INT32 aSourceFormat, INT32 aTargetFormat);

    //! Returns a conversion function for single pixel conversion of source format to target format
    /*!
     * \param aSourceFormat source buffer pixel format, see XFCGFXFORMAT.
     * \param aTargetFormat target buffer pixel format, see XFCGFXFORMAT.
     */
    static xfcPixelConversionFunction getConversionFunction(INT32 aSourceFormat,INT32 aTargetFormat);
    //static UINT32 (*getConversionFunction(INT32 aSourceFormat,INT32 aTargetFormat))(UINT32);

    //! Returns a buffer conversion function for conversion of source format to target format
    /*!
     * \param aSourceFormat source buffer pixel format, see XFCGFXFORMAT.
     * \param aTargetFormat target buffer pixel format, see XFCGFXFORMAT.
     */
    static xfcPixelBufferConversionFunction getBufferConversionFunction(INT32 aSourceFormat,INT32 aTargetFormat);
    //static void (*getBufferConversionFunction(INT32 aSourceFormat,INT32 aTargetFormat))(void *, void *, INT32);
};


#endif // !XFC_CORE_XFCPIXELCONVERTER_H_INCLUDED

