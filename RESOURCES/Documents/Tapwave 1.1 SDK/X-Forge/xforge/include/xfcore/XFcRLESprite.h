/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcRLESprite.h is the header file for the XFcRLESprite class,
 * which implements drawing and construction of RLE sprites
 *
 * $Id: XFcRLESprite.h,v 1.17 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.17 $
 */

#ifndef XFC_CORE_XFCRLESPRITE_H_INCLUDED
#define XFC_CORE_XFCRLESPRITE_H_INCLUDED


//! Class for drawing and constructing RLE compressed sprites.
class XFCDLLEXPORT XFcRLESprite
{
public:

    //! Creates a RLE-compressed sprite from a surface. 
    /*! aBaseColor is the color that is compressed as transparent. aBaseMask
     *  defines which componets of the color are used in the comparison process,
     *  for instance aBaseMask 0xff000000 and aBaseColor 0 will compress (in
     *  ARGB color space) all those pixels whose alpha value is zero. To
     *  compress based on color (in RGB space), use aBaseMask 0xffffff and
     *  aBaseColor of any color you want to compress away. Also subsequent runs
     *  of the same color are compressed away, so simple images compress really
     *  well.
     * \param aSurface image to create the RLE-compressed form from.
     * \param aBaseMask mask applied to image pixels before comparing to the base color.
     * \param aBaseColor color to compress as transparent.
     * \return new RLE sprite object, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcRLESprite * create(XFcGLSurface *aSurface, UINT32 aBaseMask, UINT32 aBaseColor);

    //! Creates a RLE-compressed sprite from stored data.
    /*! This can be used for loading the XFcRLESprite from existing data.
     * \param aWidth width of the sprite.
     * \param aHeight height of the sprite.
     * \param aXOffset offset to the first column from the top left corner.
     * \param aYOffset offset to the first row from the top left corner.
     * \param aLineTable table of line start indices in the data.
     * \param aData pointer to the compressed data.
     * \param aDataLength length of the compressed data (size in UINT16's).
     */
    XFCIMPORT static XFcRLESprite * create(INT32 aWidth, INT32 aHeight, INT32 aXOffset, INT32 aYOffset, INT32 *aLineTable, UINT16 *aData, INT32 aDataLength);

    //! Destructor.
    XFCIMPORT ~XFcRLESprite();

    //! Blits the RLE sprite to a surface.
    /*!
     * \param aSurface destination surface to blit this RLE sprite.
     * \param aClipRect clipping rectangle to use.
     * \param aXPos top-left X-coordinate.
     * \param aYPos top-left Y-coordinate.
     * \param aBlendMode the blending mode to use.
     * \param aBlendValue the blending value for the blending mode.
     * \note Coordinates are in screen coordinates.
     */
    XFCEXPORT void blit(XFcGLSurface *aSurface, XFcRectangle *aClipRect, INT32 aXPos, INT32 aYPos, INT32 aBlendMode = XFCBLEND_NONE, INT32 aBlendValue = 255);

    //! Blits the RLE sprite to a surface using additive blending. aAlpha should be in the range of 0-32.
    /*!
     * \param aSurface destination surface to blit this RLE sprite.
     * \param aClipRect clipping rectangle to use.
     * \param aXPos top-left X-coordinate.
     * \param aYPos top-left Y-coordinate.
     * \param aAlpha alpha in range 0-32.
     * \note Coordinates are in screen coordinates.
     */
    XFCIMPORT void blitAdditive(XFcGLSurface *aSurface, XFcRectangle *aClipRect,
                                INT32 aXPos, INT32 aYPos, INT32 aAlpha = 32);

    //! Blits the RLE sprite to a surface using multiplicative blending.
    /*!
     * \param aSurface destination surface to blit this RLE sprite.
     * \param aClipRect clipping rectangle to use.
     * \param aXPos top-left X-coordinate.
     * \param aYPos top-left Y-coordinate.
     * \param aAlpha alpha in range 0-32.
     * \note Coordinates are in screen coordinates.
     */
    XFCIMPORT void blitMultiplicative(XFcGLSurface *aSurface, XFcRectangle *aClipRect,
                                      INT32 aXPos, INT32 aYPos, INT32 aAlpha = 32);

    //! Blits the RLE sprite to a surface using inverse multiplicative blending.
    /*!
     * \param aSurface destination surface to blit this RLE sprite.
     * \param aClipRect clipping rectangle to use.
     * \param aXPos top-left X-coordinate.
     * \param aYPos top-left Y-coordinate.
     * \param aAlpha alpha in range 0-32.
     * \note Coordinates are in screen coordinates.
     */
    XFCIMPORT void blitInverseMultiplicative(XFcGLSurface *aSurface, XFcRectangle *aClipRect,
                                             INT32 aXPos, INT32 aYPos, INT32 aAlpha = 32);

    //! Returns the width of actual image in this sprite.
    XFCIMPORT INT32 getWidth();
    //! Returns the height of actual image in this sprite.
    XFCIMPORT INT32 getHeight();
    //! Returns the offset to the first colmn from the top left corner.
    XFCIMPORT INT32 getXOffset();
    //! Returns the offset to the first row from the top left corner.
    XFCIMPORT INT32 getYOffset();
    //! Sets the offset to the first colmn from the top left corner.
    XFCIMPORT void setXOffset(INT32 aXOffset);
    //! Sets the offset to the first row from the top left corner.
    XFCIMPORT void setYOffset(INT32 aYOffset);
    //! Returns a pointer to the line table.
    XFCIMPORT INT32 *getLineTable();
    //! Returns a pointer to the compressed data.
    XFCIMPORT UINT16 *getData();
    //! Returns the length of the compressed data.
    XFCIMPORT INT32 getDataLength();

protected:

    //! Protected constructor.
    XFcRLESprite();

    //! Find the extents for RLE compression.
    /*! Areas outside these extents would be compressed away, so there's no point in storing them.
     */
    XFCIMPORT static void getExtents(XFcGLSurface *aSurface, XFcRectangle *aRectangle,
                                     UINT32 aBaseMask, UINT32 aBaseColor);

    //! Compresses a line from source to destination. 
    /*! Returns the amount of bytes in the compressed data.
     */
    XFCIMPORT static UINT32 compressLine(UINT8 *aSource, UINT16 *aDestination,
                                         UINT32 aBaseMask, UINT32 aBaseColor,
                                         UINT32 aLineLength, INT32 aFormat, INT32 aBpp);

    //! Reads an UINT32 color value from UINT8 * buffer.
    XFCIMPORT static UINT32 getSourceColor(UINT8 *aSource, INT32 aFormat, INT32 aBpp);

    //! Blits the RLE sprite to a surface, fast blitting for 55X5 format, no blending
    XFCIMPORT void blitFast55X5(XFcGLSurface *aSurface, XFcRectangle *aClipRect, INT32 aXPos, INT32 aYPos);

    //! Blits the RLE sprite to a surface, supports all formats.
    XFCIMPORT void blitGeneric(XFcGLSurface *aSurface, XFcRectangle *aClipRect,
                               INT32 aXPos, INT32 aYPos, INT32 aBlend, UINT32 aBlendValue);

    //! Inits the blitting of a RLESprite and calculates clipping extents
    XFCIMPORT INT initBlit(XFcRectangle *aClipRect, INT32 aYPos, INT32 aXPos,
                           INT32 &aXs, INT32 &aXe, INT32 &aXt, INT32 &aYs, INT32 &aYe, INT32 &aYt);

    INT32 mWidth;           //!< Width of the sprite.
    INT32 mHeight;          //!< Height of the sprite.
    INT32 mXOffset;         //!< Offset to the first column from the top left corner.
    INT32 mYOffset;         //!< Offset to the first row from the top left corner.
    INT32 *mLineTable;      //!< Table of line start indices in the data.
    UINT16 *mData;          //!< Compressed data.
    INT32 mDataLength;      //!< Length of the compressed data (size in UINT16's).
};


#endif // !XFC_CORE_XFCRLESPRITE_H_INCLUDED

