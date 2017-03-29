/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveShapes class contains static function for defining simple graphic shapes.
 *
 * $Id: XFcPrimitiveShapes.h,v 1.1 2003/10/15 12:31:33 kkallio Exp $
 * $Date: 2003/10/15 12:31:33 $
 * $Revision: 1.1 $
 */

#ifndef XFC_CORE_XFCPRIMITIVESHAPES_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVESHAPES_H_INCLUDED

class XFcPrimitiveShapes
{
public:
    //! Draws a rectangle with the translator.
    /*! \param aTranslator to draw the shape.
     *  \param aX x position of the upper left corner.
     *  \param aY y position of the upper left corner.
     *  \param aWidth width of the rectangle.
     *  \param aHeight height of the rectangle.
     *  \param aRx width of the rounding circle in the corners.
     *  \param aRy height of the rounding circle in the corners.
     */
    static void rectangle(XFcPrimitiveTranslator *aTranslator, REAL aX, REAL aY,
                          REAL aWidth, REAL aHeight, REAL aRx = REALi(0), REAL aRy = REALi(0));

    //! Draws a circle with the translator.
    /*! \param aTranslator to draw the shape.
     *  \param aX x position of the center of the circle.
     *  \param aY y position of the center of the circle.
     *  \param aRadius radius of the circle.
     */
    static void circle(XFcPrimitiveTranslator *aTranslator, REAL aX, REAL aY, REAL aRadius);

    //! Draws an ellipse with the translator.
    /*! \param aTranslator to draw the shape.
     *  \param aX x position of the center of the ellipse.
     *  \param aY y position of the center of the ellipse.
     *  \param aRx horizontal radius of the ellipse.
     *  \param aRy vertical radius of the ellipse.
     */
    static void ellipse(XFcPrimitiveTranslator *aTranslator, REAL aX, REAL aY, REAL aRx, REAL aRy);

    //! Draws a line with the translator.
    /*! \param aTranslator to draw the shape.
     *  \param aX1 x position of the start of the line.
     *  \param aY1 y position of the start of the line.
     *  \param aX2 x position of the end of the line.
     *  \param aY2 y position of the end of the line.
     */
    static void line(XFcPrimitiveTranslator *aTranslator, REAL aX1, REAL aY1, REAL aX2, REAL aY2);

    //! Draws a polyline with the translator
    /*! \param aTranslator to draw the shape.
     *  \param aCoordinates an array of coordinates that define the polyline. Order is x1,y1,x2,y2,x3,y3 etc.
     *  \param aCount amount of coordinate pairs in the array.
     */
    static void polyline(XFcPrimitiveTranslator *aTranslator, REAL *aCoordinates, INT32 aCount);

    //! Draws a polygon with the translator
    /*! \param aTranslator to draw the shape.
     *  \param aCoordinates an array of coordinates that define the polyline. Order is x1,y1,x2,y2,x3,y3 etc.
     *  \param aCount amount of coordinate pairs in the array.
     */
    static void polygon(XFcPrimitiveTranslator *aTranslator, REAL *aCoordinates, INT32 aCount);
};

#endif // !XFC_CORE_XFCPRIMITIVESHAPES_H_INCLUDED

