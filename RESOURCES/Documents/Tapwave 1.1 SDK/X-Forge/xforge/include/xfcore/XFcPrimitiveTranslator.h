/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveTranslator class translates drawing commands for XFcPrimitiveDraw.
 *
 * $Id: XFcPrimitiveTranslator.h,v 1.1.2.1 2003/10/23 11:59:56 kkallio Exp $
 * $Date: 2003/10/23 11:59:56 $
 * $Revision: 1.1.2.1 $
 */

#ifndef XFC_CORE_XFCPRIMITIVETRANSLATOR_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVETRANSLATOR_H_INCLUDED

#define XFC_PRIMITIVETRANSLATOR_DEFAULT_CURVE_SMOOTHNESS REALi(5)
#define XFC_PRIMITIVETRANSLATOR_DEFAULT_STROKE_WIDTH REALi(1)
#define XFC_PRIMITIVETRANSLATOR_DEFAULT_MITER_LIMIT REALi(4);

enum XFcPrimitiveTranslatorPaintMode {
    XFC_PRIMITIVETRANSLATOR_NONE = 0,
    XFC_PRIMITIVETRANSLATOR_COLOR,
    XFC_PRIMITIVETRANSLATOR_GRADIENT,
    XFC_PRIMITIVETRANSLATOR_IMAGE,
    XFC_PRIMITIVETRANSLATOR_PATTERN
};

enum XFcPrimitiveTranslatorFillRule {
    XFC_PRIMITIVETRANSLATOR_EVENODD_FILL = 0,
    XFC_PRIMITIVETRANSLATOR_NONZERO_FILL
};

enum XFcPrimitiveTranslatorLineCap {
    XFC_PRIMITIVETRANSLATOR_BUTT_CAP = 0,
    XFC_PRIMITIVETRANSLATOR_ROUND_CAP,
    XFC_PRIMITIVETRANSLATOR_SQUARE_CAP
};

enum XFcPrimitiveTranslatorLineJoin {
    XFC_PRIMITIVETRANSLATOR_MITER_JOIN = 0,
    XFC_PRIMITIVETRANSLATOR_ROUND_JOIN,
    XFC_PRIMITIVETRANSLATOR_BEVEL_JOIN
};

enum XFcPrimitiveTranslatorRenderFlags {
    XFC_PRIMITIVETRANSLATOR_NEW_SUBPATH = 1
};

enum XFcPrimitiveTranslatorLineFlags {
    XFC_PRIMITIVETRANSLATOR_START_CAP = 1,
    XFC_PRIMITIVETRANSLATOR_END_CAP = 2,
};

enum XFcPrimitiveTranslatorInvalidationFlags {
    XFC_PRIMITIVETRANSLATOR_INVALIDATED_ROUNDINGCIRCLE = 1,
    XFC_PRIMITIVETRANSLATOR_INVALIDATED_PERCEIVED_VALUES = 2
};

enum XFcPrimitiveTranslatorEllipticArcFlags {
    XFC_PRIMITIVETRANSLATOR_LARGE_ARC_FLAG = 1,
    XFC_PRIMITIVETRANSLATOR_SWEEP_FLAG = 2
};

class XFcPrimitiveTranslatorLengths;
class XFcPrimitiveTranslatorFlags;
class XFcPrimitiveDraw;
class XFcPrimitiveDrawFiller;
class XFcPrimitiveDrawGradientFiller;
class XFcPrimitiveDrawImageFiller;
class XFcPrimitiveDrawPatternFiller;
class XFcPrimitiveDrawPointSet;
class XFcPrimitiveDrawLineSet;
class XFcPrimitiveDrawIndexedPrimitive;
class XFcPrimitiveDrawIndexedPrimitiveSet;

//! XFcPrimitiveTranslator class translates drawing commands for XFcPrimitiveDraw.
class XFCDLLEXPORT XFcPrimitiveTranslator
{
public:

    //! Static constructor.
    XFCIMPORT static XFcPrimitiveTranslator * create();

    //! Destructor.
    XFCIMPORT virtual ~XFcPrimitiveTranslator();

    //! Sets the surface for rendering
    XFCIMPORT void setRenderTarget(XFcGLSurface *aRenderTarget);

    //! Returns the rendering surface
    XFCIMPORT XFcGLSurface *getRenderTarget();

    //! Sets the XFcPrimitiveDraw to be used for rendering
    XFCIMPORT void setRenderer(XFcPrimitiveDraw *aRenderer);

    //! Sets the clipping rectangle to be used for rendering
    XFCIMPORT void setClipRect(XFcRectangle *aClipRect);

    //! Sets the transformation matrix for transforming the primitives
    XFCIMPORT void setTransformation(XFcMatrix3 &aTransformation);

    //! Sets the smoothness for the curve approximation. 
    /*! Curves are converted to linesets for rendering. Curve smoothness
     *  defines the approximate length of one curve segment. The length is
     *  calculated from the length of the control path of the curve.
     */
    XFCIMPORT void setCurveSmoothLength(REAL aSmoothness);

    //! Sets the gradient filler to be used for filling.
    XFCIMPORT void setFillGradient(XFcPrimitiveDrawGradientFiller *aGradient);

    //! Sets the gradient filler to be used for stroking.
    XFCIMPORT void setStrokeGradient(XFcPrimitiveDrawGradientFiller *aGradient);

    //! Sets the image filler to be used for filling.
    XFCIMPORT void setFillImage(XFcPrimitiveDrawImageFiller *aImageFiller);

    //! Sets the image filler to be used for stroking.
    XFCIMPORT void setStrokeImage(XFcPrimitiveDrawImageFiller *aImageFiller);

    //! Sets the pattern filler to be used for filling.
    XFCIMPORT void setFillPattern(XFcPrimitiveDrawPatternFiller *aPattern);

    //! Sets the pattern filler to be used for stroking.
    XFCIMPORT void setStrokePattern(XFcPrimitiveDrawPatternFiller *aPattern);

    //! Sets the color to be used for filling. Color is in X8R8G8B8 format.
    XFCIMPORT void setFillColor(UINT32 aColor);

    //! Sets the color to be used for stroking. Color is in X8R8G8B8 format.
    XFCIMPORT void setStrokeColor(UINT32 aColor);

    //! Sets the filling off
    XFCIMPORT void setFillOff();

    //! Sets the stroking off
    XFCIMPORT void setStrokeOff();

    //! Sets the opacity for filling.
    XFCIMPORT void setFillOpacity(UINT8 aOpacity);

    //! Sets the opacity for stroking.
    XFCIMPORT void setStrokeOpacity(UINT8 aOpacity);

    //! Sets the fill rule for filling.
    XFCIMPORT void setFillRule(INT32 aFillRule);

    //! Sets the stroke width.
    XFCIMPORT void setStrokeWidth(REAL aWidth);

    //! Sets the line cap style.
    XFCIMPORT void setLineCap(INT32 aLineCap);

    //! Sets the line join style.
    XFCIMPORT void setLineJoin(INT32 aLineJoin);

    //! Sets the miter limit.
    XFCIMPORT void setMiterLimit(REAL aMiterLimit);

    //! Sets the dash array for dashing.
    XFCIMPORT void setDashArray(REAL *aDashArray, INT32 aLength);

    //! Sets the dash offset for dashing.
    XFCIMPORT void setDashOffset(REAL aDashOffset);

    //! Sets the antialiasing mode (TRUE / FALSE)
    XFCIMPORT void setAntialiasing(INT aState);

    //! Starts a path command.
    XFCIMPORT void beginPath();

    //! Ends a path command. The path will be rendered to the canvas.
    XFCIMPORT void endPath();

    //! Moves the pointer to an absolute position.
    XFCIMPORT void moveToAbsolute(XFcVector2 &aPos);

    //! Moves the pointer to an absolute position.
    inline void moveToAbsolute(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        moveToAbsolute(pos);
    }

    //! Moves the pointer relatively to the previous position.
    XFCIMPORT void moveToRelative(XFcVector2 &aPos);

    //! Moves the pointer relatively to the previous position.
    inline void moveToRelative(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        moveToRelative(pos);
    }

    //! Draws a line from previous position to a new position.
    XFCIMPORT void lineToAbsolute(XFcVector2 &aPos);

    //! Draws a line from previous position to a new position.
    inline void lineToAbsolute(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        lineToAbsolute(pos);
    }

    //! Draws a line in relation to the previous position.
    XFCIMPORT void lineToRelative(XFcVector2 &aPos);

    //! Draws a line in relation to the previous position.
    inline void lineToRelative(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        lineToRelative(pos);
    }

    //! Draws a horizontal line from the previous position to a new x position.
    XFCIMPORT void horizontalLineToAbsolute(REAL aX);

    //! Draws a horizontal line in relation to the previous position.
    XFCIMPORT void horizontalLineToRelative(REAL aX);

    //! Draws a vertical line from the previous position to a new y position.
    XFCIMPORT void verticalLineToAbsolute(REAL aY);

    //! Draws a vertical line in relation to the previous position.
    XFCIMPORT void verticalLineToRelative(REAL aY);

    //! Draws a cubic bezier curve from the previous position to a new position with two control points.
    XFCIMPORT void curveToAbsolute(XFcVector2 &aCP1, XFcVector2 &aCP2, XFcVector2 &aPos);

    //! Draws a cubic bezier curve from the previous position to a new position with two control points.
    inline void curveToAbsolute(REAL aXCP1, REAL aYCP1, REAL aXCP2, REAL aYCP2, REAL aX, REAL aY)
    {
        XFcVector2 cp1 = XFcVector2(aXCP1, aYCP1);
        XFcVector2 cp2 = XFcVector2(aXCP2, aYCP2);
        XFcVector2 pos = XFcVector2(aX, aY);
        curveToAbsolute(cp1,cp2,pos);
    }

    //! Draws a cubic bezier curve in relation to the previous position.
    XFCIMPORT void curveToRelative(XFcVector2 &aCP1, XFcVector2 &aCP2, XFcVector2 &aPos);

    //! Draws a cubic bezier curve in relation to the previous position.
    inline void curveToRelative(REAL aXCP1, REAL aYCP1, REAL aXCP2, REAL aYCP2, REAL aX, REAL aY)
    {
        XFcVector2 cp1 = XFcVector2(aXCP1, aYCP1);
        XFcVector2 cp2 = XFcVector2(aXCP2, aYCP2);
        XFcVector2 pos = XFcVector2(aX, aY);
        curveToRelative(cp1,cp2,pos);
    }

    //! Draws a cubic bezier curve from the previous position to a new position using a mirror of the previous control point and one new control point.
    XFCIMPORT void smoothCurveToAbsolute(XFcVector2 &aCP2, XFcVector2 &aPos);

    //! Draws a cubic bezier curve from the previous position to a new position using a mirror of the previous control point and one new control point.
    inline void smoothCurveToAbsolute(REAL aXCP2, REAL aYCP2, REAL aX, REAL aY)
    {
        XFcVector2 cp2 = XFcVector2(aXCP2, aYCP2);
        XFcVector2 pos = XFcVector2(aX, aY);
        smoothCurveToAbsolute(cp2,pos);
    }

    //! Draws a cubic bezier curve in relation to the previous position using a mirror of the previous control point and one new control point.
    XFCIMPORT void smoothCurveToRelative(XFcVector2 &aCP2, XFcVector2 &aPos);

    //! Draws a cubic bezier curve in relation to the previous position using a mirror of the previous control point and one new control point.
    inline void smoothCurveToRelative(REAL aXCP2, REAL aYCP2, REAL aX, REAL aY)
    {
        XFcVector2 cp2 = XFcVector2(aXCP2, aYCP2);
        XFcVector2 pos = XFcVector2(aX, aY);
        smoothCurveToRelative(cp2,pos);
    }

    //! Draws a quadratic bezier curve from the previous position to a new position using one control point.
    XFCIMPORT void quadraticCurveToAbsolute(XFcVector2 &aCP, XFcVector2 &aPos);

    //! Draws a quadratic bezier curve from the previous position to a new position using one control point.
    inline void quadraticCurveToAbsolute(REAL aXCP, REAL aYCP, REAL aX, REAL aY)
    {
        XFcVector2 cp = XFcVector2(aXCP, aYCP);
        XFcVector2 pos = XFcVector2(aX, aY);
        quadraticCurveToAbsolute(cp,pos);
    }

    //! Draws a quadratic bezier curve in relation to the previous position using one control point.
    XFCIMPORT void quadraticCurveToRelative(XFcVector2 &aCP, XFcVector2 &aPos);

    //! Draws a quadratic bezier curve in relation to the previous position using one control point.
    inline void quadraticCurveToRelative(REAL aXCP, REAL aYCP, REAL aX, REAL aY)
    {
        XFcVector2 cp = XFcVector2(aXCP, aYCP);
        XFcVector2 pos = XFcVector2(aX, aY);
        quadraticCurveToRelative(cp,pos);
    }

    //! Draws a quadratic bezier curve from the previous position to a new position using a mirror of the previous control point.
    XFCIMPORT void smoothQuadraticCurveToAbsolute(XFcVector2 &aPos);

    //! Draws a quadratic bezier curve from the previous position to a new position using a mirror of the previous control point.
    inline void smoothQuadraticCurveToAbsolute(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        smoothQuadraticCurveToAbsolute(pos);
    }

    //! Draws a quadratic bezier curve in relation to the previous position using a mirror of the previous control point.
    XFCIMPORT void smoothQuadraticCurveToRelative(XFcVector2 &aPos);

    //! Draws a quadratic bezier curve in relation to the previous position using a mirror of the previous control point.
    inline void smoothQuadraticCurveToRelative(REAL aX, REAL aY)
    {
        XFcVector2 pos = XFcVector2(aX, aY);
        smoothQuadraticCurveToRelative(pos);
    }

    //! Draws an ellipical arc. See SVG 1.0 Specification for explanation.
    XFCIMPORT void ellipticalArcAbsolute(XFcVector2 &aRadii, REAL aRotation, UINT32 aFlags, XFcVector2 &aPos);

    //! Draws an ellipical arc. See SVG 1.0 Specification for explanation.
    inline void ellipticalArcAbsolute(REAL aRadiusX, REAL aRadiusY, REAL aRotation, UINT32 aFlags, REAL aX, REAL aY)
    {
        XFcVector2 radii = XFcVector2(aRadiusX, aRadiusY);
        XFcVector2 pos = XFcVector2(aX, aY);
        ellipticalArcAbsolute(radii,aRotation,aFlags,pos);
    }

    //! Draws an ellipical arc. See SVG 1.0 Specification for explanation.
    XFCIMPORT void ellipticalArcRelative(XFcVector2 &aRadii, REAL aRotation, UINT32 aFlags, XFcVector2 &aPos);

    //! Draws an ellipical arc. See SVG 1.0 Specification for explanation.
    inline void ellipticalArcRelative(REAL aRadiusX, REAL aRadiusY, REAL aRotation, UINT32 aFlags, REAL aX, REAL aY)
    {
        XFcVector2 radii = XFcVector2(aRadiusX, aRadiusY);
        XFcVector2 pos = XFcVector2(aX, aY);
        ellipticalArcRelative(radii,aRotation,aFlags,pos);
    }

    //! Closes the path with a straight line.
    XFCIMPORT void closePath();

    //! After the endpath command has been issued, it is possible to find a point on the edge of the path.
    /*! aPos is a value between 0 and 1, where 0 is the start of the path and 1 is the end of the path.
     *  The calculated edge position and direction (not normalized) are placed to aPosition and aDirection.
     */
    XFCIMPORT void getEdgeInfo(REAL aPos, XFcVector2 *aPosition, XFcVector2 *aDirection);

protected:
    //! Protected constructor.
    XFcPrimitiveTranslator();

    //! Calculates the stroke from mPoints and mLineIndicies to mEdgepoints, mEdgeJoins and mEdgeLineIndicies
    void calculateStroking();

    //! Calculates the filling for the path by closing all gaps.
    void calculateFilling();

    //! Calcultaes the edge length array from mPoints and mLineIndicies.
    void calculateEdgeLengths();

    //! Calculates the perceived values of stroke width, opacity, caps and joins for very thin lines.
    void calculatePerceivedValues();

    //! Creates a dashed line using dashArray. This is just the dashed outline,
    //! stroking is done separately.
    void createDash(XFcPrimitiveDrawPointSet *aPoints, XFcPrimitiveDrawLineSet *aLines,
                    XFcPrimitiveTranslatorLengths *aEdgeLengths, XFcPrimitiveTranslatorFlags *aLineFlags);

    //! Creates the circle to be used for rounded caps and joins
    void createRoundingCircle();

    //! Creates an array of XFcPrimitiveDrawIndexedPrimitives to be used for rounded caps and joins.
    void resetCircleArray(INT32 aArraySize);

    //! Deletes the circle array.
    void deleteCircleArray();

    //! Adds the rounding circle to the path being drawn.
    void addRoundingCircle(XFcVector2 &aPos);

    XFcRectangle *mClipRect;
    XFcGLSurface *mRenderTarget;
    XFcPrimitiveDraw *mRenderer;
    XFcMatrix3 mTransformation;
    REAL mCurveSmooth;
    INT32 mFillMode;
    INT32 mStrokeMode;
    UINT32 mFillColor;
    UINT32 mStrokeColor;
    UINT8 mFillOpacity;
    UINT8 mStrokeOpacity;
    INT32 mFillRule;
    REAL mStrokeWidth;
    INT32 mLineCap;
    INT32 mLineJoin;
    REAL mPerceivedStrokeWidth;
    UINT8 mPerceivedStrokeOpacity;
    INT32 mPerceivedLineJoin;
    INT32 mPerceivedLineCap;
    REAL mMiterLimit;
    REAL *mDashArray;
    INT32 mDashArrayLength;
    REAL mDashOffset;
    XFcPrimitiveDrawPointSet *mPoints;
    XFcPrimitiveDrawLineSet *mLineIndicies;
    XFcPrimitiveDrawIndexedPrimitiveSet *mEdgeJoins;
    XFcPrimitiveDrawPointSet *mEdgePoints;
    XFcPrimitiveDrawLineSet *mEdgeLineIndicies;
    UINT32 mProcessingInfoFlags;
    XFcVector2 mCurrentPoint;
    XFcVector2 mLastControlPoint;
    XFcVector2 mPathStart;
    INT32 mFirstPoint;
    INT32 mFirstLine;
    INT32 mLineCaps;
    XFcPrimitiveTranslatorLengths *mEdgeLengths;
    XFcPrimitiveTranslatorFlags *mLineFlags;
    XFcPrimitiveDrawIndexedPrimitive **mCircleArray;
    INT32 mCircleArrayLength;
    INT32 mCircleIndex;
    REAL mRoundingCircleSize;
    REAL mRoundingCircleYPos;
    XFcPrimitiveDrawIndexedPrimitive *mRoundingCircleLeft;
    XFcPrimitiveDrawIndexedPrimitive *mRoundingCircleRight;
    INT32 mInvalidationFlags;
    INT32 mInsertedLineCount;
    XFcPrimitiveDrawFiller *mFiller;
    XFcPrimitiveDrawFiller *mStrokeFiller;
    INT mAntialiasing;
};

#endif // !XFC_CORE_XFCPRIMITIVETRANSLATOR_H_INCLUDED
