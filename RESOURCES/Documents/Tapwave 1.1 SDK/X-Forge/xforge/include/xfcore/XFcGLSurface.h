/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcGL surface class.
 *
 * $Id: XFcGLSurface.h,v 1.16 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.16 $
 */

#ifndef XFC_CORE_XFCGLSURFACE_H_INCLUDED
#define XFC_CORE_XFCGLSURFACE_H_INCLUDED

#include <xfcore/XFcRectangle.h>


class XFcGLCoreSurface;


//! Texture/sprite surface class.
/*! The XFcGLSurface is the main building block of all 2D graphics
 *  in X-Forge. Graphics surfaces can be locked for direct memory
 *  access, and they can be blitted to other surfaces in different ways.
 *  Surfaces can be created for direct 2d graphics use, or you can acquire
 *  surfaces from XFcTexture objects, or you can ask the XFcGL object for
 *  the back buffer with the getSecondary() call.
 * \sa XFcGLTexture
 * \sa XFcGL
 */
class XFCDLLEXPORT XFcGLSurface
{
    friend class XFcGLCoreSurface;

public:

    //! Creates a surface with dimensions and format.
    /*!
     * The default dimensions are 256 by 256. The default format is
     * chosen so as to be compatible with the target device. Currently
     * the default format is always 16-bit 55X5 format.
     * \param aWidth surface width.
     * \param aHeight surface height.
     * \param aFormat surface format, see XFCGFXFORMAT.
     * \sa XFCGFXFORMAT
     */
    XFCIMPORT static XFcGLSurface * create(INT32 aWidth = 256,
                                           INT32 aHeight = 256,
                                           INT32 aFormat = XFCGF_DEFAULT);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcGLSurface();
    
    //! Locks the surface with specific mode.
    /*!
     * Non-preferred modes will be converted on the fly, which is slow.
     * \par
     * If you wish to fill the whole surface you may get some speed gains
     * by using the XFCGFX_DISCARDCONTENTS flag. Not using this flag may cause
     * the system to convert between graphics formats on lock and unlock.
     * \par
     * If you only wish to read from the surface, use the XFCGFX_DISCARDCHANGES
     * flag. Not doing so may cause loss of data (if locked format has less
     * data than the native format).
     * \note While the framebuffer is locked, you should not call any graphics
     *       library functions.
     * \param aBuffer returned pointer to the surface.
     * \param aFlags surface lock flags, see XFCGFXFLAGS.
     * \param aMode graphics format, see XFCGFXFORMAT. Use XFCGF_DEFAULT to
     *              lock surface in its own native format.
     * \return Surface pitch in bytes.
     * \sa XFCGFXFORMAT
     * \sa XFCGFXFLAGS
     */
    XFCIMPORT virtual INT32 lock(void **aBuffer, INT32 aMode = XFCGF_DEFAULT,
                                 INT32 aFlags = XFCGFX_DISCARDCONTENTS);

    //! Unlocks the framebuffer.
    /*! If the surface was locked in a non-native format and the locking did
     *  not specify the GFX_DISCARDCHANGES flag, the unlock will convert the
     *  temporary buffer into the surface's native format.
     *  \sa lock
     */
    XFCIMPORT virtual void unlock();

    //! Returns the current color key.
    /*!
     * \sa setColorKey
     */
    XFCIMPORT INT32 getColorKey();

    //! Sets the color key (in 8:8:8:8 ARGB format).
    /*! Color keying is a method of masking parts of a 2D surface to
     *  be fully transparent.
     * \param aColorKey new color key in 8:8:8:8 ARGB format.
     * \note You have to enable color keying with the enableColorKey() call as well.
     * \note The color keying affects the 2D pipeline only. To make a color transparent
     *       in the 3D pipeline, you have to specify the color key at creation time.
     * \sa XFcGLTextureFromFile
     * \sa getColorKey
     * \sa enableColorKey
     */
    XFCIMPORT void setColorKey(INT32 aColorKey);

    //! Enables or disables color keying.
    /*!
     * \param aFlag 1 to enable color keying, 0 to disable.
     * \sa setColorKey
     */
    XFCIMPORT void enableColorKey(INT aFlag);



    //! Draws an image onto this surface to top-left corner.
    /*!
     * \param aImage image to draw.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage);

    //! Draws an image onto this surface to a given position.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY);

    //! Draws an image, scaling to given width and keeping aspect ratio.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY,
                             INT32 aWidth);

    //! Draws an image, scaling to given width and height.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY,
                             INT32 aWidth, INT32 aHeight);

    //! Draws an image onto this surface to top-left corner.
    /*!
     * \param aImage image to draw.
     * \param aSrcRect source rectangle.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             const XFcRectangle &aSrcRect);

    //! Draws an image onto this surface to a given position.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY,
                             const XFcRectangle &aSrcRect);

    //! Draws an image, scaling to given width and keeping aspect ratio.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY,
                             const XFcRectangle &aSrcRect,
                             INT32 aWidth);

    //! Draws an image, scaling to given width and height.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     */
    XFCIMPORT void drawImage(XFcGLSurface *aImage,
                             INT32 aX, INT32 aY,
                             const XFcRectangle &aSrcRect,
                             INT32 aWidth, INT32 aHeight);


    //! Draws an image onto this surface to top-left corner, using blending.
    /*!
     * \param aImage image to draw.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image onto this surface to a given position, using blending.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image, scaling to given width and keeping aspect ratio, using blending.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  INT32 aWidth,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image, scaling to given width and height, using blending.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  INT32 aWidth, INT32 aHeight,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image onto this surface to top-left corner, using blending.
    /*!
     * \param aImage image to draw.
     * \param aSrcRect source rectangle.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  const XFcRectangle &aSrcRect,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image onto this surface to a given position, using blending.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  const XFcRectangle &aSrcRect,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image, scaling to given width and keeping aspect ratio, using blending.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  const XFcRectangle &aSrcRect,
                                  INT32 aWidth,
                                  INT32 aBlendType, INT32 aBlendValue);

    //! Draws an image, scaling to given width and height, using blending.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \sa XFCBLENDMODE_2D
     */
    XFCIMPORT void drawImageBlend(XFcGLSurface *aImage,
                                  INT32 aX, INT32 aY,
                                  const XFcRectangle &aSrcRect,
                                  INT32 aWidth, INT32 aHeight,
                                  INT32 aBlendType, INT32 aBlendValue);


    //! Draws a 2D transformed image onto this surface to a given position.
    /*!
     * \param aImage image to draw.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to a given position.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and keeping aspect ratio.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      INT32 aWidth,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and height.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      INT32 aWidth, INT32 aHeight,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to top-left corner.
    /*!
     * \param aImage image to draw.
     * \param aSrcRect source rectangle.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      const XFcRectangle &aSrcRect,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to a given position.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      const XFcRectangle &aSrcRect,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and keeping aspect ratio.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      const XFcRectangle &aSrcRect,
                                      INT32 aWidth,
                                      UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and height.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransform(XFcGLSurface *aImage,
                                      INT32 aX, INT32 aY,
                                      const XFcRectangle &aSrcRect,
                                      INT32 aWidth, INT32 aHeight,
                                      UINT32 aFlags);


    //! Draws a 2D transformed image onto this surface to top-left corner, using blending.
    /*!
     * \param aImage image to draw.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to a given position, using blending.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and keeping aspect ratio, using blending.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           INT32 aWidth,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and height, using blending.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           INT32 aWidth, INT32 aHeight,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to top-left corner, using blending.
    /*!
     * \param aImage image to draw.
     * \param aSrcRect source rectangle.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           const XFcRectangle &aSrcRect,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image onto this surface to a given position, using blending.
    /*!
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           const XFcRectangle &aSrcRect,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws a 2D transformed image, scaling to given width and keeping aspect ratio, using blending.
    /*!
     * Height is calculated based on the original image size, keeping the aspect ratio.
     * \note Coordinates are in pixels. 
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           const XFcRectangle &aSrcRect,
                                           INT32 aWidth,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);

    //! Draws an image, scaling to given width and height, using blending.
    /*!
     * The image is stretched to fit the aWidth and aHeight parameters.
     * \note Coordinates are in pixels.
     * \param aImage image to draw.
     * \param aX top-left X-coordinate to start drawing from.
     * \param aY top-left Y-coordinate to start drawing from.
     * \param aSrcRect source rectangle.
     * \param aWidth width of the scaled image.
     * \param aHeight height of the scaled image.
     * \param aBlendType blending type, see XFCBLENDMODE_2D.
     * \param aBlendValue blend value in range from 0 to 0xff.
     * \param aFlags transformation flags, see XFCSURFACETRANSFORM_2D.
     * \sa XFCBLENDMODE_2D
     * \sa XFCSURFACETRANSFORM_2D
     */
    XFCIMPORT void drawImageTransformBlend(XFcGLSurface *aImage,
                                           INT32 aX, INT32 aY,
                                           const XFcRectangle &aSrcRect,
                                           INT32 aWidth, INT32 aHeight,
                                           INT32 aBlendType, INT32 aBlendValue,
                                           UINT32 aFlags);



    //! Draws a filled rectangle with single color (in 8:8:8:8 ARGB format).
    /*!
     * If the GL device supports it, and the target surface is the back buffer,
     * this call may be hardware accelerated.
     * \note Coordinates are in pixels.
     * \param aX top-left X-coordinate.
     * \param aY top-left Y-coordinate.
     * \param aWidth width in pixels.
     * \param aHeight height in pixels.
     * \param aColor color in 8:8:8:8 ARGB format.
     */
    XFCIMPORT void drawFilledRect(INT32 aX, INT32 aY,
                                  INT32 aWidth, INT32 aHeight,
                                  UINT32 aColor);

    //! Clears the surface.
    /*! Whole bitmap is initialized to aColor.
     *  \param aColor color in 8:8:8:8 ARGB format.
     */
    XFCIMPORT void clear(UINT32 aColor);

    //! Draws an anti-aliased line (with color in 8:8:8:8 ARGB format).
    /*! The line is drawn to this surface, with the given color, between
     *  the points aX1,aY1 and aX2,aY2.
     * \note Coordinates are in pixels.
     * \param aX1 the first point's X-coordinate.
     * \param aY1 the first point's Y-coordinate.
     * \param aX2 the second point's X-coordinate.
     * \param aY2 the second point's Y-coordinate.
     * \param aColor color in 8:8:8:8 ARGB format.
     */
    XFCIMPORT void drawAALine(XFcFixed aX1, XFcFixed aY1,
                              XFcFixed aX2, XFcFixed aY2,
                              UINT32 aColor);

    //! Draws a line (with color in 8:8:8:8 ARGB format).
    /*! The line is drawn to this surface, with the given color, between
     *  the points aX1,aY1 and aX2,aY2.
     * \note Coordinates are in pixels.
     * \param aX1 the first point's X-coordinate.
     * \param aY1 the first point's Y-coordinate.
     * \param aX2 the second point's X-coordinate.
     * \param aY2 the second point's Y-coordinate.
     * \param aColor color in 8:8:8:8 ARGB format.
     */
    XFCIMPORT void drawLine(XFcFixed aX1, XFcFixed aY1,
                            XFcFixed aX2, XFcFixed aY2,
                            UINT32 aColor);

    //! Returns the surface format.
    /*! \sa XFCGFXFORMAT
     */
    XFCIMPORT INT32 getFormat();
    
    //! Returns surface width in pixels.
    XFCIMPORT INT32 getWidth();
    
    //! Returns surface height in pixels.
    XFCIMPORT INT32 getHeight();

protected:

    //! Protected empty constructor.
    XFcGLSurface();

    //! Locks both surfaces for blitting.
    XFCIMPORT INT lockForBlit(XFcGLSurface *aImage);

    //! Unlocks both surfaces after blitting.
    XFCIMPORT void unlockForBlit(XFcGLSurface *aImage);

    //! Locks surface for drawing.
    XFCIMPORT INT lockForDraw();

    //! Unlocks surface after drawing.
    XFCIMPORT void unlockForDraw();

    //! Pointer to the actual surface data.
    void *mData;
};


#endif // !XFC_CORE_XFCGLSURFACE_H_INCLUDED

