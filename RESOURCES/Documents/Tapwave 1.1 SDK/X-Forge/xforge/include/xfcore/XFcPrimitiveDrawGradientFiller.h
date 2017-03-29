/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveDrawGradientFiller defines a base class for gradient fillers.
 *
 * $Id: XFcPrimitiveDrawGradientFiller.h,v 1.1.2.2 2003/10/23 11:59:56 kkallio Exp $
 * $Date: 2003/10/23 11:59:56 $
 * $Revision: 1.1.2.2 $
 */

#ifndef XFC_CORE_XFCPRIMITIVEDRAWGRADIENTFILLER_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVEDRAWGRADIENTFILLER_H_INCLUDED

enum XFcPrimitiveDrawGradientSpreadMethods
{
    XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_PAD = 0,
    XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_REFLECT = 1,
    XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_REPEAT = 2
};

enum XFcPrimitiveDrawGradientUpdateFlags
{
    XFC_PRIMITIVEDRAW_GRADIENT_UPDATE_TRANSFORMATION = 1,
    XFC_PRIMITIVEDRAW_GRADIENT_UPDATE_GRADIENT_DATA = 2
};

#define XFC_PRIMITIVEDRAW_GRADIENT_STORAGE_INCREMENT 10
#define XFC_PRIMITIVEDRAW_GRADIENT_DATA_SIZE 256

class XFcPrimitiveDrawGradientStopNode;

//! A base class for defining gradient fillers.
class XFCDLLEXPORT XFcPrimitiveDrawGradientFiller : public XFcPrimitiveDrawFiller
{
public:
    //! Virtual destructor.
    virtual XFCIMPORT ~XFcPrimitiveDrawGradientFiller();

    //! Initializes the filler for filling.
    /*! This should be called before calling fill() for the first filled span.
     */
    virtual XFCIMPORT void initFill();

    //! Deinitializes the filler after rendering.
    /*! This should be called after calling fill() for the last filled span.
     */
    virtual XFCIMPORT void deinitFill() {};

    //! Adds a gradient stop to the gradient.
    virtual XFCIMPORT void addGradientStop(REAL aOffset, UINT32 aColor);

    //! Reset the gradient, clears the gradient stops.
    virtual XFCIMPORT void resetGradient();

    //! Sets the spread method for the gradient.
    /*! Possible values are XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_PAD,
     *  XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_REFLECT and 
     *  XFC_PRIMITIVEDRAW_GRADIENT_SPREAD_REPEAT
     */
    virtual XFCIMPORT void setSpreadMethod(INT32 aSpreadMethod);

    //! Sets the transformation for the gradient.
    /*! This is the transformation of the shape which is filled with
     *  the gradient.
     */
    virtual XFCIMPORT void setTransformation(XFcMatrix3 &aTransformation);

    //! Sets the gradient transformation for the gradient.
    /*! This is the transformation that is applied when transforming from gradient
     *  space to rendering space, and allows operations such as skewing the gradient.
     */
    virtual XFCIMPORT void setGradientTransformation(XFcMatrix3 &aGradientTransformation);

protected:
    //! Protected constuctor.
    XFcPrimitiveDrawGradientFiller();

    //! Inits the gradient, returns 0 if init fails. 
    virtual INT initGradient();

    //! Increases the size of the stop node storage list.
    virtual void increaseStopNodeStorage();

    //! Calculates the gradient data based on the stop nodes.
    virtual void calculateGradientData();

    //! Calculates the gradient transformation.
    virtual void calculateGradientTransformation();

    XFcPrimitiveDrawGradientStopNode *mFirstStopNode;
    XFcPrimitiveDrawGradientStopNode *mStopNodeStorage;
    UINT32 *mGradientData;
    XFcMatrix3 mGlobalTransformation;
    XFcMatrix3 mTransformation;
    XFcMatrix3 mGradientTransformation;
    INT32 mSpreadMethod;
    INT32 mRequiresUpdate;
};


//! Linear gradient filler.
class XFCDLLEXPORT XFcPrimitiveDrawLinearGradientFiller : public XFcPrimitiveDrawGradientFiller
{
public:
    //! Creates a linear gradient that ranges from point aStart to point aEnd.
    static XFCIMPORT XFcPrimitiveDrawLinearGradientFiller * create(XFcVector2 &aStart, XFcVector2 &aEnd);

    //! Virtual destructor
    virtual XFCIMPORT ~XFcPrimitiveDrawLinearGradientFiller();

    //! Sets the gradient vectors for the gradient
    virtual XFCIMPORT void setGradientBase(XFcVector2 &aStart, XFcVector2 &aEnd);

    //! Fills aLength PREMULA8R8G8B8 pixels to a scanline.
    //! param aXStart the starting position on the scanline
    //! param aXEnd the ending position on the scanline
    //! param aY the y position of the scanline
    //! param aScanline the start of the scanline
    virtual XFCIMPORT void fill(INT32 aXStart, INT32 aXEnd, INT32 aY, UINT32 *aScanline);

protected:
    //! Protected constructor.
    XFcPrimitiveDrawLinearGradientFiller();

    //! Calculates the gradient transformation.
    virtual void calculateGradientTransformation();

    //! The transformation matrix that is calculated so that a vector from aStart to aEnd maps from 0 to 1.
    XFcMatrix3 mBaseTransformation;
};


//! Radial gradient filler.
class XFCDLLEXPORT XFcPrimitiveDrawRadialGradientFiller : public XFcPrimitiveDrawGradientFiller
{
public:
    //! Creates a radial gradient that has its center in aCenter, focal point in aFocalPoint and radius of aRadius.
    static XFCIMPORT XFcPrimitiveDrawRadialGradientFiller * create(XFcVector2 &aCenter, XFcVector2 &aFocalPoint, REAL aRadius);

    //! Virtual destructor.
    virtual XFCIMPORT ~XFcPrimitiveDrawRadialGradientFiller();

    //! Sets the base values for the gradient.
    virtual XFCIMPORT void setGradientBase(XFcVector2 &aCenter, XFcVector2 &aFocalPoint, REAL aRadius);

    //! Fills aLength PREMULA8R8G8B8 pixels to a scanline.
    //! param aXStart the starting position on the scanline
    //! param aXEnd the ending position on the scanline
    //! param aY the y position of the scanline
    //! param aScanline the start of the scanline
    virtual XFCIMPORT void fill(INT32 aXStart, INT32 aXEnd, INT32 aY, UINT32 *aScanline);

protected:
    //! Protected constructor.
    XFcPrimitiveDrawRadialGradientFiller();

    XFcVector2 mCenter;
    XFcVector2 mFocalPoint;
    REAL mRadius;
};

#endif // !XFC_CORE_XFCPRIMITIVEDRAWGRADIENTFILLER_H_INCLUDED
