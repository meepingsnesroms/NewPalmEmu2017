/*!
 * \file
 * X-Forge <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcRectangle.
 * 
 * $Id: XFcRectangle.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFC_CORE_XFCRECTANGLE_H_INCLUDED
#define XFC_CORE_XFCRECTANGLE_H_INCLUDED


//! Defines a rectangle.
class XFCDLLEXPORT XFcRectangle
{
public:

    INT32 mX;           //!< X-origin.
    INT32 mY;           //!< Y-origin.
    INT32 mWidth;       //!< Width.
    INT32 mHeight;      //!< Height.

    //! Default constructor.
    XFCIMPORT XFcRectangle();

    //! Constructor that takes the rectangle dimensions as parameters.
    XFCIMPORT XFcRectangle(INT32 aX, INT32 aY, INT32 aWidth, INT32 aHeight);
};


#endif // !XFC_CORE_XFCRECTANGLE_H_INCLUDED

