/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWGFXUTILS_H__
#define __TWGFXUTILS_H__

#include "Tapwave.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Draw a PalmOS bitmap into a surface. Directly analagous to
 * TwGfxDrawBitmap except that the kind of bitmap is a PalmOS bitmap
 *
 * Errors:
 *      see TwGfxDrawBitmap
 */
Err
TwGfxDrawPalmBitmap(TwGfxSurfaceType* aDestSurface,
                    const TwGfxPointType* aDestPoint,
                    BitmapType* aBitmap)
    TAL_TRAP(trapTwGfxDrawPalmBitmap);

/*
 * Take a PalmOS 4-bpp (68K!) bitmap and use it as an alpha mask
 * blending the passed or current foreground color into the current draw
 * window at the specified offset.  Clipping is respected.
 * If colorP is NULL, current fore color is used
 * If twBlendMaskErase is set in flags, area is erased to current background
 * If twBlendMaskWaitForVBlank is set in flags, drawing is done at vblank
 * If twBlendMaskRotate*, will rotate the mask by 90 degree increments
 * If twBlendMaskMirror*, will mirror the mask as requested
 *
 * Errors:
 *      probably
 */
#define twBlendMaskNormal           0x00000000
#define twBlendMaskWaitForVBlank    0x00000001
#define twBlendMaskErase            0x00000002

#define twBlendMaskRotateShift      4
#define twBlendMaskRotateMask       (twGfxRotateCW270 << twBlendMaskRotateShift)
#define twBlendMaskRotate0          (twGfxRotateNone << twBlendMaskRotateShift)
#define twBlendMaskRotate90         (twGfxRotateCW90 << twBlendMaskRotateShift)
#define twBlendMaskRotate180        (twGfxRotateCW180 << twBlendMaskRotateShift)
#define twBlendMaskRotate270        (twGfxRotateCW270 << twBlendMaskRotateShift)

#define twBlendMaskMirrorShift      8
#define twBlendMaskMirrorMask       (twGfxMirrorBoth << twBlendMaskMirrorShift)
#define twBlendMaskMirrorNone       (twGfxMirrorNone << twBlendMaskMirrorShift)
#define twBlendMaskMirrorHorizontal (twGfxMirrorHorizontal << twBlendMaskMirrorShift)
#define twBlendMaskMirrorVertical   (twGfxMirrorVertical << twBlendMaskMirrorShift)
#define twBlendMaskMirrorBoth       (twGfxMirrorBoth << twBlendMaskMirrorShift)


Err
TwBlendMask(BitmapType *maskP, Coord x, Coord y, const RGBColorType *colorP, UInt32 flags)
    TAL_TRAP(trapTwBlendMask);

Err
TwTintBitmap(BitmapType *bmpP, const RGBColorType *colorP, UInt32 flags)
    TAL_TRAP(trapTwTintBitmap);

/*
 * Convert a bitmap pointer (68k or arm native) into it's arm native
 * equivalent.
 *
 * *aAllocatedResult will be set to true if an allocation was done (Note: free *aBitmapResult
 * *using MemPtrFree if *aAllocatedResult is set).
 */
Err
TwConvert68KBitmapToNative(void* aBitmap68KP, BitmapType** aBitmapResult, Boolean* aAllocatedResult)
    TAL_TRAP(trapTwConvert68KBitmapToNative);

#ifdef __cplusplus
}
#endif

#endif /* __TWGFXUTILS_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
