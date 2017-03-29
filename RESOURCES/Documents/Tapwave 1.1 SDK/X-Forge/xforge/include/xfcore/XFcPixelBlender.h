/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Pixel blending functions/macros
 * 
 * $Id: XFcPixelBlender.h,v 1.5 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.5 $
 */

#ifndef XFC_CORE_XFCPIXELBLENDER_H_INCLUDED
#define XFC_CORE_XFCPIXELBLENDER_H_INCLUDED

typedef UINT32 (*xfcBlendingFunction)(UINT32, UINT32, UINT32);
typedef void (*xfcBufferBlendingFunction)(void *, void *, UINT32, INT32);


//! Utility for pixel blending.
/*! Blending for X888 (XFCGF_X8R8G8B8) and Premul8888 (XFCGF_PREMULA8R8G8B8)
 *  formats is supported.
 */
class XFCDLLEXPORT XFcPixelBlender
{
public:
    //! Blends together two pixels, both in 55X5 format, no blending
    XFCIMPORT static UINT32 blendNone55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using alpha blending
    XFCIMPORT static UINT32 blendAlpha55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using fast alpha blending
    XFCIMPORT static UINT32 blendAlphaFast55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using additive blending
    XFCIMPORT static UINT32 blendAdd55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using fast additive blending
    XFCIMPORT static UINT32 blendAddFast55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using multiplicative blending
    XFCIMPORT static UINT32 blendMul55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using fast multiplicative blending
    XFCIMPORT static UINT32 blendMulFast55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using inverse multiplicative blending
    XFCIMPORT static UINT32 blendInvmul55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, both in 55X5 format, using fast inverse multiplicative blending
    XFCIMPORT static UINT32 blendInvmulFast55X5(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);

    //! Blends together two pixels in Premul8888 format, no blending
    XFCIMPORT static UINT32 blendNonePremul8888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels in Premul8888 format, using alpha blending
    XFCIMPORT static UINT32 blendAlphaPremul8888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels in Premul8888 format, using additive blending
    XFCIMPORT static UINT32 blendAddPremul8888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels in Premul8888 format, using multiplicative blending
    XFCIMPORT static UINT32 blendMulPremul8888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels in Premul8888 format, using inverse multiplicative blending
    XFCIMPORT static UINT32 blendInvmulPremul8888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);

    //! Blends together two pixels, source in Premul8888 format, target in X888 format, no blending
    XFCIMPORT static UINT32 blendNoneX888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, source in Premul8888 format, target in X888 format, using alpha blending
    XFCIMPORT static UINT32 blendAlphaX888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, source in Premul8888 format, target in X888 format, using additive blending
    XFCIMPORT static UINT32 blendAddX888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, source in Premul8888 format, target in X888 format, using multiplicative blending
    XFCIMPORT static UINT32 blendMulX888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);
    //! Blends together two pixels, source in Premul8888 format, target in X888 format, using inverse multiplicative blending
    XFCIMPORT static UINT32 blendInvmulX888(UINT32 aSource, UINT32 aTarget, UINT32 aBlendValue);


    //! Blends together two buffers, both in 55X5 format, no blending
    XFCIMPORT static void blendBufferNone55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using alpha blending
    XFCIMPORT static void blendBufferAlpha55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using fast alpha blending
    XFCIMPORT static void blendBufferAlphaFast55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using additive blending
    XFCIMPORT static void blendBufferAdd55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using fast additive blending
    XFCIMPORT static void blendBufferAddFast55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using multiplicative blending
    XFCIMPORT static void blendBufferMul55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using fast multiplicative blending
    XFCIMPORT static void blendBufferMulFast55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using inverse multiplicative blending
    XFCIMPORT static void blendBufferInvmul55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, both in 55X5 format, using fast inverse multiplicative blending
    XFCIMPORT static void blendBufferInvmulFast55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);

    //! Blends together two buffers in Premul8888 format, no blending
    XFCIMPORT static void blendBufferNonePremul8888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers in Premul8888 format, using alpha blending
    XFCIMPORT static void blendBufferAlphaPremul8888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers in Premul8888 format, using additive blending
    XFCIMPORT static void blendBufferAddPremul8888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers in Premul8888 format, using multiplicative blending
    XFCIMPORT static void blendBufferMulPremul8888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers in Premul8888 format, using inverse multiplicative blending
    XFCIMPORT static void blendBufferInvmulPremul8888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);

    //! Blends together two buffers, source in Premul8888 format, target in X888 format, no blending
    XFCIMPORT static void blendBufferNoneX888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, source in Premul8888 format, target in X888 format, using alpha blending
    XFCIMPORT static void blendBufferAlphaX888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, source in Premul8888 format, target in X888 format, using additive blending
    XFCIMPORT static void blendBufferAddX888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, source in Premul8888 format, target in X888 format, using multiplicative blending
    XFCIMPORT static void blendBufferMulX888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends together two buffers, source in Premul8888 format, target in X888 format, using inverse multiplicative blending
    XFCIMPORT static void blendBufferInvmulX888(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    
    
    //! Calculates the common blending formats that can be used to blend pixels of two formats together.
    XFCIMPORT static void getBlendingFormat(INT32 aSourceFormat, INT32 aTargetFormat,
                                            INT32 &aBlendingSourceFormat, INT32 &aBlendingTargetFormat);

    //! Returns the blending function that can blend aBlendingSourceFormat and aBlendingTargetFormat together.
    /*! aBlendingSourceFormat and aBlendingSourceFormats should be results from a call to
     *  getBlendingFormat so that it is guaranteed that a blending function for the formats
     *  exists. To get the correct blending value for the blending function, a call to
     *  getBlendingValue() has to be made.
     */
    XFCIMPORT static xfcBlendingFunction getBlendingFunction(INT32 aBlendingSourceFormat, INT32 aBlendingTargetFormat, INT32 aBlendMode);

    //! Returns the blendvalue for blending between aBlendingSourceFormat and aBlendingTargetFormat.
    /*! aBlendingSourceFormat and aBlendingSourceFormats should be results from a call to
     *  getBlendingFormat so that it is guaranteed that a blending function for the formats
     *  exists.
     */
    XFCIMPORT static INT32 getBlendValue(INT32 aBlendingSourceFormat, INT32 aBlendingTargetFormat, INT32 aBlendMode, INT32 aBlendValue);

    //! Returns the blending function that can blend aBlendingSourceFormat and aBlendingTargetFormat together.
    /*! aBlendingSourceFormat and aBlendingSourceFormats should be results from a call to
     *  getBlendingFormat so that it is guaranteed that a blending function for the formats
     *  exists. To get the correct blending value for the blending function, a call to
     *  getBlendingValue() has to be made.
     */
    XFCIMPORT static xfcBufferBlendingFunction getBufferBlendingFunction(INT32 aBlendingSourceFormat, INT32 aBlendingTargetFormat, INT32 aBlendMode);

    // These are custom blenders for faster blender access in various situations

    //! Blends a buffer of 16bit alpha (range 0-32) plus 16bit color with count aCount from source to target
    XFCIMPORT static void blendBufferAlphaXA55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a buffer of 16bit alpha (range 0-32) plus 16bit color with count aCount from source to target using additive blending
    XFCIMPORT static void blendBufferAddXA55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a buffer of 16bit alpha (range 0-32) plus 16bit color with count aCount from source to target using multiplicative blending
    XFCIMPORT static void blendBufferMulXA55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a buffer of 16bit alpha (range 0-32) plus 16bit color with count aCount from source to target using inverse multiplicative blending
    XFCIMPORT static void blendBufferInvmulXA55X5(void *aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);

    //! Blends a constant 16bit color to target buffer with count aCount
    XFCIMPORT static void blendColorToBufferAlpha55X5(UINT32 aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a constant 16bit color to target buffer with count aCount using additive blending
    XFCIMPORT static void blendColorToBufferAdd55X5(UINT32 aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a constant 16bit color to target buffer with count aCount using multiplicative blending
    XFCIMPORT static void blendColorToBufferMul55X5(UINT32 aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);
    //! Blends a constant 16bit color to target buffer with count aCount using multiplicative blending
    XFCIMPORT static void blendColorToBufferInvmul55X5(UINT32 aSource, void *aTarget, UINT32 aBlendValue, INT32 aCount);

};

#endif // !XFC_CORE_XFCPIXELBLENDER_H_INCLUDED

