/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcGLSurfaceToolkit class implements various methods for modifying and processing surfaces.
 *
 * $Id: XFcGLSurfaceToolkit.h,v 1.6 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.6 $
 */

#ifndef XFC_CORE_XFCGLSURFACETOOLKIT_H_INCLUDED
#define XFC_CORE_XFCGLSURFACETOOLKIT_H_INCLUDED

enum XFC_DITHER_MODE
{
    XFC_DITHER_NONE = 0,
    XFC_DITHER_RANDOM,
    XFC_DITHER_ORDERED,
    XFC_DITHER_DIFFUSION
};

//! Surface toolkit. Contains various static functions for manipulating surfaces.
class XFCDLLEXPORT XFcGLSurfaceToolkit
{
public:
    //! Resamples a surface to new size, takes scale for x and y as parameters.
    /*!
     * \param aSurface the surface to resample.
     * \param aXScale the amount of scale in horizontal direction.
     * \param aYScale the amount of scale in vertical direction.
     */
    XFCIMPORT static XFcGLSurface * resampleSurface(XFcGLSurface *aSurface, REAL aXScale, REAL aYScale);

    //! Resamples a surface to new size, takes width and height as parameters.
    /*!
     * \param aSurface the surface to resample.
     * \param aWidth the new width.
     * \param aHeight the new height.
     */
    XFCIMPORT static XFcGLSurface * resampleSurface(XFcGLSurface *aSurface, INT32 aWidth, INT32 aHeight);

    //! Skews a surface in horizontal and/or vertical direction.
    /*!
     * The amount of skew in horizontal and vertical direction is defined as a difference
     * between two rows or columns of pixels. To calculate this value from a skewing angle,
     * use XFcMath::tan(angle). The method performs first the horizontal skew, then the
     * vertical skew.
     * \param aSurface the surface to skew.
     * \param aXSkew the amount of skew in horizontal direction.
     * \param aYSkew the amount of skew in vertical direction.
     */
    XFCIMPORT static XFcGLSurface * skewSurface(XFcGLSurface *aSurface, REAL aXSkew, REAL aYSkew);

    //! Rotates a surface by an angle.
    /*!
     * \param aSurface the surface to rotate.
     * \param aAngle the amount of rotation in radians in clockwise direction.
     */
    XFCIMPORT static XFcGLSurface * rotateSurface(XFcGLSurface *aSurface, REAL aRotation);

    //! Transforms a surface with an affine transformation matrix.
    /*!
     *  The transformation is performed so that the size of the translated image is
     *  defined by the new extents that result from the translation. In addition, a
     *  2D vector aTranslationResult is assigned a value that defines the translation
     *  in whole pixels. The transformation matrix aTransformation should be an affine
     *  matrix.
     *  /param aSurface the surface to transform.
     *  /param aMatrix the transformation matrix.
     *  /param aTranslationResult the integer part of the translation result.
     */
    XFCIMPORT static XFcGLSurface * transformSurface(XFcGLSurface *aSurface, XFcMatrix3 &aTransform, XFcVector2 &aTranslationResult);

    //! Dithers a surface.
    /*!
     * The surface will be dithered using method defined by aDitherMode. Valid modes are
     * XFC_DITHER_NONE, XFC_DITHER_RANDOM, XFC_DITHER_ORDERED and XFC_DITHER_DIFFUSION.
     * The aRanges variable defines a color in 32-bit ARGB format, where each color
     * component defines a range of values to which the component will be posterized. For
     * instance value 0x010f0f0f will convert the alpha to 1-bit value and each color
     * component to a 4-bit value.
     * \param aSurface the surface to dither.
     * \param aRanges a colour value in 32-bit ARBG format that defines the colour ranges.
     * \param aDitherMode the dithering method to use.
     */
    XFCIMPORT static void ditherSurface(XFcGLSurface *aSurface, UINT32 aRanges, INT32 aDitherMode);
};

#endif // !XFC_CORE_XFCGLSURFACETOOLKIT_H_INCLUDED

