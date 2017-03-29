/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Printer variant that uses RLE-sprites instead of normal ones.
 * 
 * $Id: XFuRLESpritePrinter.h,v 1.13 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.13 $
 */

#ifndef XFURLESPRITEPRINTER_H_INCLUDED
#define XFURLESPRITEPRINTER_H_INCLUDED

#include <xfutil/XFuPrinter.h>


//! XFuPrinter variant that uses RLE sprites instead of normal ones.
/*! 
 * \sa XFuPrinter
 */
class XFuRLESpritePrinter : public XFuPrinter
{
public:
    
    //! Creates XFuRLESpritePrinter from an image file.
    static XFuRLESpritePrinter * create(const CHAR *aFname);
    //! Creates XFuRLESpritePrinter from an image file.
    static XFuRLESpritePrinter * create(const CHAR *aFname, UINT32 aBaseMask, UINT32 aBaseColor);
    //! Creates XFuRLESpritePrinter from an image file using a scale.
    static XFuRLESpritePrinter * create(const CHAR *aFname, UINT32 aBaseMask, UINT32 aBaseColor,
                                        REAL aXScale, REAL aYScale);
    //! Prints a character string with the printer's font.
    /*! String is printed to a target surface with optional blending and clipping rectangle.
     */
    virtual void print(XFcGLSurface * aTarget, INT32 aX, INT32 aY, const CHAR *aText,
                       INT32 aBlendType = 0, INT32 aBlendValue = 0x7f, XFcRectangle *aClipRect = NULL);
    //! Calculates how big an area a string would take if printed.
    virtual void stringMetrics(const CHAR *aText, INT32 &aWidth, INT32 &aHeight);
    //! Returns the width of a single character.
    virtual INT32 getCharWidth(CHAR aChar);
    virtual ~XFuRLESpritePrinter();

protected:
    
    XFuRLESpritePrinter();
    
    XFcRLESprite **mLetterSprite;  
};


#endif // !XFURLESPRITEPRINTER_H_INCLUDED

