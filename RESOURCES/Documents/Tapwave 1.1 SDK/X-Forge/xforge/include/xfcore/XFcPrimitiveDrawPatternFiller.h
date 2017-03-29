/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveDrawPatternFiller is a filler that loops a bitmap pattern with a transformation.
 *
 * $Id: XFcPrimitiveDrawPatternFiller.h,v 1.1 2003/10/15 09:32:45 kkallio Exp $
 * $Date: 2003/10/15 09:32:45 $
 * $Revision: 1.1 $
 */

#ifndef XFC_CORE_XFCPRIMITIVEDRAWPATTERNFILLER_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVEDRAWPATTERNFILLER_H_INCLUDED

enum XFcPrimitiveDrawPatternUpdateFlags
{
    XFC_PRIMITIVEDRAW_PATTERN_UPDATE_TRANSFORMATION = 1,
    XFC_PRIMITIVEDRAW_PATTERN_UPDATE_IMAGE = 2
};

//! Pattern filler using bitmap patterns.
class XFCDLLEXPORT XFcPrimitiveDrawPatternFiller : public XFcPrimitiveDrawFiller
{
public:
    //! Creates the pattern filler.
    static XFCIMPORT XFcPrimitiveDrawPatternFiller * create(XFcGLSurface *aSourceImage, XFcRectangle &aSourceRect);

    //! Virtual destructor.
    virtual XFCIMPORT ~XFcPrimitiveDrawPatternFiller();

    //! Sets the image to be used for filling and the rectangle from which the pattern is read.
    /*! Note that the image is not copied, so it shoudn't be modified or deleted until
     *  the fill operation is done. However, the image is cached for transformation, so
     *  if the source image is animated, setPattern has to be called for every animation
     *  frame, otherwise the result may not work.
     */
    virtual XFCIMPORT void setPattern(XFcGLSurface *aSourceImage,XFcRectangle &aSourceRect);

    //! Sets the pattern transformation for the pattern.
    virtual XFCIMPORT void setPatternTransformation(XFcMatrix3 &aTransformation);

    //! Sets the rendering transformation for the pattern.
    virtual XFCIMPORT void setTransformation(XFcMatrix3 &aTransformation);

    //! Initializes the filler for filling.
    /*! This should be called before calling fill() for the first filled span.
     */
    virtual XFCIMPORT void initFill();

    //! Deinitializes the filler after rendering.
    virtual XFCIMPORT void deinitFill();

    //! Fills aLength PREMULA8R8G8B8 pixels to a scanline.
    //! param aXStart the starting position on the scanline
    //! param aXEnd the ending position on the scanline
    //! param aY the y position of the scanline
    //! param aScanline the start of the scanline
    virtual XFCIMPORT void fill(INT32 aXStart, INT32 aXEnd, INT32 aY, UINT32 *aScanline);

protected:
    //! Protected constructor.
    XFcPrimitiveDrawPatternFiller();

    //! Updates the transformation matrix
    virtual void updateTransformation();

    //! Updates the pattern image from the source image.
    virtual void updatePatternImage();

    XFcGLSurface *mSourceImage;
    XFcGLSurface *mPatternImage;
    XFcRectangle mSourceRect;
    XFcMatrix3 mTransformation;
    XFcMatrix3 mPatternTransformation;
    XFcMatrix3 mGlobalTransformation;
    XFcMatrix3 mRenderTransformation;
    INT32 mRequiresUpdate;
    REAL mWidthScale;
    REAL mHeightScale;
    UINT32 *mPatternBuffer;
    INT32 mPatternPitch;
    INT32 mPatternWidth;
    INT32 mPatternHeight;
};

#endif // !XFC_CORE_XFCPRIMITIVEDRAWPATTERNFILLER_H_INCLUDED
