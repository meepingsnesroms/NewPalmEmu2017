/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWJPG_H___
#define __TWJPG_H___

#include <TwGfx.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Constants
 */
#define twJPGLibType		sysFileTLibrary
#define twJPGLibCreator		'twJ6'
#define twJPGLibName		"IJG JPEG Library"

/*
 * Error codes
 */
#define twJpgErrorLibraryOpen           (0 + twJpgErrorBase)
#define twJpgErrorNullPointer           (1 + twJpgErrorBase)
#define twJpgErrorBadObjectVersion      (2 + twJpgErrorBase)
#define twJpgErrorLibraryClosed         (3 + twJpgErrorBase)
#define twJpgErrorBadImage              (4 + twJpgErrorBase)

#define twJpgErrorInvalidHandle         (10 + twJpgErrorBase)
#define twJpgErrorInvalidPixelFormat    (11 + twJpgErrorBase)
#define twJpgErrorInvalidSize           (12 + twJpgErrorBase)

#define twJpgErrorDecodeAborted         (20 + twJpgErrorBase)

/*
 * Supported decode pixel formats
 */
#define twJpgPixelFormatRGB565          1       /* RGB, 2 bytes per pixel, little endian */
#define twJpgPixelFormatRGB565_LE       1       /* RGB, 2 bytes per pixel, little endian */
#define twJpgPixelFormatRGB565_BE       2       /* RGB, 2 bytes per pixel, big endian */
#define twJpgPixelFormatRGB888          3       /* RGB, 3 bytes per pixel */

/*
 * Jpeg specified color spaces
 */
#define twJpgColorSpaceUnknown          0
#define twJpgColorSpaceGrayscale        1
#define twJpgColorSpaceRGB              2
#define twJpgColorSpaceYCbCr            3
#define twJpgColorSpaceYUV              3
#define twJpgColorSpaceCMYK             4
#define twJpgColorSpaceYCCK             5

/***********************************************************************/

/*
 * Structures
 */
typedef struct TwJpgImageType* TwJpgImageHandle;

/* This declaration is for C */
typedef struct TwJpgImageType TwJpgImageType;

typedef struct TwJpgImageInfoType {
    Int32 size;                         /* caller MUST set this to sizeof(TwJpgImageInfoType) */

    Int32 width, height;                /* image dimensions */
    Int32 colorspace;                   /* colorspace */
    Int32 components;                   /* # of color components (RGB==3, for example) */

    // TODO: add "standard" markers
} TwJpgImageInfoType;

/*
 * Image reader callback. This is used by the jpg functions to read
 * data for a given image. The return value is a count of the number
 * of bytes read. Zero indicates an EOF, positive values indicate the
 * amount returned. Negative values indicates an error. aHandle is a
 * data value provided to the callback for the usage of the callback
 * implementation.
 */
typedef Int32 (*TwJpgImageReader)(void* aHandle,
                                  void* aBuffer,
                                  UInt32 aAmount);

/*
 * This predicate is invoked during the decode process to see if the
 * decoder should abort the current decode. The predicate should
 * return a non-zero value if the decode should be aborted, zero
 * otherwise.
 */
typedef Int32 (*TwJpgAbortCheck)(void* aHandle);

/***********************************************************************/

/*
 * Open an image returning a new instance of TwJpgImageType. Associate
 * aReader and aHandle with the image. These are used to read the
 * actual encoded image data. This library reads jpeg files encoded in
 * the standard jpeg file format (JFIF).
 */
Err TwJpgOpenImage(TwJpgImageHandle* aResult,
                   TwJpgImageReader aReader,
                   void* aHandle)
	TAL_TRAP(trapTwJpgOpenImage);

/*
 * Set the abort check callback for this image.
 */
Err TwJpgSetAbortCheck(TwJpgImageHandle aImage,
                       TwJpgAbortCheck aChecker,
                       void* aHandle)
	TAL_TRAP(trapTwJpgSetAbortCheck);

/*
 * Get the abort check callback for this image.
 */
Err TwJpgGetAbortCheck(TwJpgImageHandle aImage,
                       TwJpgAbortCheck* aCheckerResult,
                       void** aHandleResult)
	TAL_TRAP(trapTwJpgGetAbortCheck);

/*
 * Close an open image and release all the memory resources associated
 * with the image.
 */
Err TwJpgCloseImage(TwJpgImageHandle aImage)
	TAL_TRAP(trapTwJpgCloseImage);

/*
 * Read in enough of the image header to acquire information about the
 * image.
 */
Err TwJpgGetImageInfo(TwJpgImageHandle aImage,
                      TwJpgImageInfoType* aInfoResult)
	TAL_TRAP(trapTwJpgGetImageInfo);

/*
 * Decode the entire image into *aBufferResult. TwJpgDecodeImage will
 * allocate the memory and return it in *aBufferResult. The caller
 * must free it when done.
 *
 * The format of the buffer data is determined by the aPixelFormat
 * argument. Note that this is the only API that will provide RGB888
 * bits.
 *
 * This call will return twJpgErrorDecodeAborted if the abort checker
 * aborts the decode.
 *
 * Note that it is allowed by this API to decode an image multiple
 * times. It is the callers responsibility to rewind the reader state
 * to allow for this to actually work. If the caller does not rewind
 * the reader state then most likely the subsequent call will yield a
 * twJpgErrorBadImage error.
 */
Err TwJpgDecodeImage(TwJpgImageHandle aImage,
                     Int32 aPixelFormat,
                     void** aBufferResult)
	TAL_TRAP(trapTwJpgDecodeImage);

/*
 * Similar to TwJpgDecodeImage except that the image is scaled to
 * (aScaledWidth, aScaledHeight). The returned buffer is exactly the
 * right size to hold the scaled image in the given pixel format.  The
 * rowbytes for the returned data will be the image width times the
 * number of bytes per pixel (2 for the RGB565 formats).
 *
 * The only pixel format supported is the twJpgPixelFormatRGB565_LE
 * format.
 *
 * This call will return twJpgErrorDecodeAborted if the abort checker
 * aborts the decode.
 *
 * Note that it is allowed by this API to decode an image multiple
 * times. It is the callers responsibility to rewind the reader state
 * to allow for this to actually work. If the caller does not rewind
 * the reader state then most likely the subsequent call will yield a
 * twJpgErrorBadImage error.
 */
Err TwJpgDecodeAndScaleImage(TwJpgImageHandle aImage,
                             Int32 aScaledWidth,
                             Int32 aScaledHeight,
                             Boolean aAntiAlias,
                             void** aBufferResult)
	TAL_TRAP(trapTwJpgDecodeAndScaleImage);

/*
 * Same idea as TwJpgDecodeImage except that no intermediate storage
 * is used: the image is decoded directly to the provided
 * TwGfxSurface. The image will be scaled to fit the target surface.
 *
 * The pixel format is always twJpgPixelFormatRGB565_LE.
 *
 * This call will return twJpgErrorDecodeAborted if the abort checker
 * aborts the decode.
 *
 * Note that it is allowed by this API to decode an image multiple
 * times. It is the callers responsibility to rewind the reader state
 * to allow for this to actually work. If the caller does not rewind
 * the reader state then most likely the subsequent call will yield a
 * twJpgErrorBadImage error.
 */
Err TwJpgDecodeImageToSurface(TwJpgImageHandle aImage,
                              Boolean aAntiAlias,
                              TwGfxSurfaceHandle aDestSurface)
	TAL_TRAP(trapTwJpgDecodeImageToSurface);

/*
 * Decode an image and create a new surface to hold the scaled results.
 *
 * The pixel format is always twJpgPixelFormatRGB565_LE.
 *
 * This call will return twJpgErrorDecodeAborted if the abort checker
 * aborts the decode.
 *
 * Note that it is allowed by this API to decode an image multiple
 * times. It is the callers responsibility to rewind the reader state
 * to allow for this to actually work. If the caller does not rewind
 * the reader state then most likely the subsequent call will yield a
 * twJpgErrorBadImage error.
 */
Err TwJpgDecodeImageToNewSurface(TwJpgImageHandle aImage,
                                 Int32 aScaledWidth,
                                 Int32 aScaledHeight,
                                 Boolean aAntiAlias,
                                 TwGfxHandle aGfxLib,
                                 TwGfxSurfaceHandle* aSurfaceResult)
	TAL_TRAP(trapTwJpgDecodeImageToNewSurface);

/*
 * Utility routine to scale an image already decoded in memory. if
 * aAntiAlias is true then a different (slower) scaling algorithm will
 * be used that in theory will produce better (smoother) results.
 *
 * The only pixel format supported is the twJpgPixelFormatRGB565_LE
 * format.
 */
Err TwJpgScaleImageBuffer(void* aBufferIn,
                          Int32 aInWidth,
                          Int32 aInHeight,
                          Int32 aScaledWidth,
                          Int32 aScaledHeight,
                          Boolean aAntiAlias,
                          void** aBufferResult)
    TAL_TRAP(trapTwJpgScaleImageBuffer);

#ifdef __cplusplus
}
#endif

#endif /* __TWJPG_H___ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
