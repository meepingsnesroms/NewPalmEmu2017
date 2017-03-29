/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveDrawImageFiller is a basic image filler that doesn't support tiling or transformations of the source image.
 *
 * $Id: XFcPrimitiveDrawImageFiller.h,v 1.1 2003/10/15 09:32:45 kkallio Exp $
 * $Date: 2003/10/15 09:32:45 $
 * $Revision: 1.1 $
 */

#ifndef XFC_CORE_XFCPRIMITIVEDRAWIMAGEFILLER_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVEDRAWIMAGEFILLER_H_INCLUDED

//! Basic image filler, doesn't support tiling or transformations of the source image
class XFCDLLEXPORT XFcPrimitiveDrawImageFiller : public XFcPrimitiveDrawFiller
{
public:
    //! Creates the image filler.
    static XFCIMPORT XFcPrimitiveDrawImageFiller * create(XFcGLSurface *aFillImage, INT32 aXOffset, INT32 aYOffset);

    //! Virtual destructor.
    virtual XFCIMPORT ~XFcPrimitiveDrawImageFiller();

    //! Sets the image to be used for filling.
    /*! Note that the image is not copied, so it shoudn't be modified or deleted until
     *  the fill operation is done.
     */
    virtual XFCIMPORT void setFillImage(XFcGLSurface *aFillImage);

    //! Sets the offset (in relation to the top left corner of the screen) where to draw the image.
    virtual XFCIMPORT void setFillOffset(INT32 aXOffset, INT32 aYOffset);

    //! Initializes the filler for rendering.
    /*! This should be called before calling fill() for the first filled span.
     */
    virtual XFCIMPORT void initFill();

    //! Deinitializes the filler after rendering.
    /*! This should be called after calling fill() for the last filled span.
     */
    virtual XFCIMPORT void deinitFill();

    //! Fills aLength PREMULA8R8G8B8 pixels to a scanline.
    //! param aXStart the starting position on the scanline
    //! param aXEnd the ending position on the scanline
    //! param aY the y position of the scanline
    //! param aScanline the start of the scanline
    virtual XFCIMPORT void fill(INT32 aXStart, INT32 aXEnd, INT32 aY, UINT32 *aScanline);

protected:
    //! Protected constructor.
    XFcPrimitiveDrawImageFiller();

    XFcGLSurface *mFillImage;
    UINT8 *mFillBuffer;
    INT32 mFillPitch;
    INT32 mXOffset;
    INT32 mYOffset;
    INT32 mFillWidth;
    INT32 mFillHeight;
    INT32 mFillFormat;
};

#endif // !XFC_CORE_XFCPRIMITIVEDRAWIMAGEFILLER_H_INCLUDED
