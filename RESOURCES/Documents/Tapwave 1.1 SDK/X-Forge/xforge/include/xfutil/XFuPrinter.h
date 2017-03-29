/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Primitive bitmap font printer class. 
 * 
 * $Id: XFuPrinter.h,v 1.17 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.17 $
 */

#ifndef XFUPRINTER_H_INCLUDED
#define XFUPRINTER_H_INCLUDED


//! Primitive bitmap font printer class.
/*!
 * This class loads a single image file and creates as many XFcGLSurface objects as the
 * font has characters. The image file must have all of its characters in ASCII order starting
 * from character 33 (the exclamation mark, "!"). The image file must be as wide as a single 
 * character is high, i.e. for a 8x8 font with 20 characters and one character, the image 
 * dimensions would be 8x160.
 */
class XFuPrinter
{
public:
    //! Creates a XFuPrinter object from an image file.
    static XFuPrinter * create(const CHAR *aFname);
    //! Creates a XFuPrinter object from an image file, with choise of color key value.
    /*!
     * aAlphamask is the color key value.
     * \sa XFcGLSurface
     */
    static XFuPrinter * create(const CHAR *aFname, INT32 aAlphamask);
    //! Creates a XFuPrinter object from an image file, with choise of color key value and scale
    static XFuPrinter * create(const CHAR *aFname, INT32 aAlphamask, REAL aXScale, REAL aYScale);
    //! Prints a character string with the printer's font.
    /*! String is printed to a target surface with optional blending and clipping rectangle.
     */
    virtual void print(XFcGLSurface *aTarget, INT32 aX, INT32 aY, const CHAR *aText,
                       INT32 aBlendType = 0, INT32 aBlendValue = 0x7f, XFcRectangle *aClipRect = NULL);
    //! Prints a character string with the printer's font, using target rectangle and word wrapping.
    /*! If the string contains words that are wider than the rectangle, the words are printed on a new
     *  line (no inter-word chopping is performed). If the aTargetRect is NULL, the whole surface is used.
     *  \Note This function uses print() and stringmetrics() internally, so it will also work with rlespriteprinter.
     *  \sa print
     *  \return Pixel height of the total printing operation (ignores clipping)
     */
    INT32 print(XFcGLSurface *aTarget, XFcRectangle *aTargetRect, const CHAR *aText,
                INT32 aBlendType = 0, INT32 aBlendValue = 0x7f, XFcRectangle *aClipRect = NULL);

    //! Calculates how big an area a string would take if printed.
    virtual void stringMetrics(const CHAR *aText, INT32 &aWidth, INT32 &aHeight);
    //! Returns the width of a single character.
    virtual INT32 getCharWidth(CHAR aChar);
    //! Sets the width of a space.
    virtual void setSpaceWidth(INT32 aSpacing);
    //! Sets letter spacing (i.e. extra space between characters).
    virtual void setLetterSpacing(INT32 aSpacing);
    //! Returns the current letter spacing (i.e. extra space between characters).
    virtual INT32 getLetterSpacing();
    //! Sets line spacing (Y-coordinate offset from a row to the next row).
    virtual void setLineSpacing(INT32 aSpacing);
    //! Returns the current line spacing (Y-coordinate offset from a row to the next row).
    virtual INT32 getLineSpacing();
    //! Returns height of one printer line.
    virtual INT32 getLineHeight();
    //! Virtual destructor.
    virtual ~XFuPrinter();

protected:
    
    //! Protected constructor.
    XFuPrinter();
    
    INT32 mMaxletter;           //!< Maximum letter in the font.
    XFcGLSurface **mLetter;     //!< Array of XFcGLSurfaces.
    INT32 mLetterSpacing;       //!< Current letter spacing.
    INT32 mLineSpacing;         //!< Current line spacing.
    INT32 mLineHeight;          //!< Line height.
    INT32 mSpaceWidth;          //!< Width of space character.
};


#endif // !XFUPRINTER_H_INCLUDED

