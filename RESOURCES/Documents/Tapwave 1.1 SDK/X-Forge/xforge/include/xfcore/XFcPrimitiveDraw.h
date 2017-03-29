/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveDraw class implements drawing of various high-level 2D primitives. 
 *
 * $Id: XFcPrimitiveDraw.h,v 1.21 2003/10/15 09:32:44 kkallio Exp $
 * $Date: 2003/10/15 09:32:44 $
 * $Revision: 1.21 $
 */

#ifndef XFC_CORE_XFCPRIMITIVEDRAW_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVEDRAW_H_INCLUDED

#define XFC_PRIMITIVE_DRAW_LEFT 1
#define XFC_PRIMITIVE_DRAW_RIGHT -1

class XFcPrimitiveDrawFiller;

//! Point struct used in XFcPrimitiveDrawPointSet.
struct XFcPrimitiveDrawPoint
{
    XFcVector2 mPos;
    XFcVector2 mScaledPos;
};


//! Line index struct used in XFcPrimitiveDrawLineSet.
struct XFcPrimitiveDrawLine
{
    INT32 mStart;
    INT32 mEnd;
};


//! Class for defining and handling shape edges in XFcPrimitiveDraw.
class XFcPrimitiveDrawEdge
{
public:

    REAL mXp;                           //!< Current X position.
    INT32 mXpi;                         //!< Current X position as integer.
    INT32 mYStart;                      //!< Starting Y of the line.
    INT32 mYEnd;                        //!< Ending Y of the line.
    XFcPrimitiveDrawEdge *mNextEdge;    //!< Pointer to the next edge
    XFcPrimitiveDrawEdge *mPrevEdge;    //!< Pointer to the previous edge

    INT32 mSpanStart;                   //!< Beginning of the span drawn with current edge.
    INT32 mSpanEnd;                     //!< End of the span drawn with the current edge.
    XFcPrimitiveDrawEdge *mNextSpan;    //!< Pointer to the next span
    XFcPrimitiveDrawEdge *mPrevSpan;    //!< Pointer to the previous span

    UINT8 mSpanAlpha;                   //!< Alpha for the area between this and next span.
    
    INT32 mEdgeType;                    //!< Used in non-xor drawing for detecting edge states.

    //! Advances the current scanline with one step.
    virtual void advanceScanline() = 0;

    //! Updates the span information of an edge.
    inline void updateSpan(INT32 aXp)
    {
        if (aXp < mSpanStart)
            mSpanStart = aXp;
        else if (aXp > mSpanEnd)
            mSpanEnd = aXp;
    }
    
    //! Returns the next edge after this.
    inline XFcPrimitiveDrawEdge *nextEdge() { return mNextEdge; }
    
    //! Returns the previous edge before this.
    inline XFcPrimitiveDrawEdge *prevEdge() { return mPrevEdge; }

    //! Removes this edge from the list.
    inline void removeEdge(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        if (mPrevEdge)
            mPrevEdge->mNextEdge = mNextEdge;
        else
            *mListBegin = mNextEdge;
    
        if (mNextEdge)
            mNextEdge->mPrevEdge = mPrevEdge;
        else
            *mListEnd = mPrevEdge;
    }

    //! Inserts a new edge after this.
    inline void insertAfterEdge(XFcPrimitiveDrawEdge **mListEnd, XFcPrimitiveDrawEdge *newNode)
    {
        newNode->mPrevEdge = this;
        newNode->mNextEdge = mNextEdge;
        if (mNextEdge)
            mNextEdge->mPrevEdge = newNode;
        else
            *mListEnd = newNode;
        mNextEdge = newNode;
    }

    //! Inserts a new edge before this.
    inline void insertBeforeEdge(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge *newNode)
    {
        newNode->mNextEdge = this;
        newNode->mPrevEdge = mPrevEdge;
        if (mPrevEdge)
            mPrevEdge->mNextEdge = newNode;
        else
            *mListBegin = newNode;
        mPrevEdge = newNode;
    }

    //! Adds this edge to the beginning of the list.
    inline void addHeadEdge(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        mPrevEdge = NULL;
        mNextEdge = *mListBegin;
        if (*mListBegin)
            (*mListBegin)->mPrevEdge = this;
        else
            *mListEnd = this;
        *mListBegin = this;
    }

    //! Adds this edge to the end of the list.
    inline void addTailEdge(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        mPrevEdge = *mListEnd;
        mNextEdge = NULL;
        if (*mListEnd)
            (*mListEnd)->mNextEdge = this;
        else
            *mListBegin = this;
        *mListEnd = this;
    }

    //! Returns the next Span after this.
    inline XFcPrimitiveDrawEdge *nextSpan() { return mNextSpan; }

    //! Returns the previous Span before this.
    inline XFcPrimitiveDrawEdge *prevSpan() { return mPrevSpan; }

    //! Removes this Span from the list.
    inline void removeSpan(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        if (mPrevSpan)
            mPrevSpan->mNextSpan = mNextSpan;
        else
            *mListBegin = mNextSpan;

        if (mNextSpan)
            mNextSpan->mPrevSpan = mPrevSpan;
        else
            *mListEnd = mPrevSpan;
    }

    //! Inserts a new Span after this.
    inline void insertAfterSpan(XFcPrimitiveDrawEdge **mListEnd, XFcPrimitiveDrawEdge *newNode)
    {
        newNode->mPrevSpan = this;
        newNode->mNextSpan = mNextSpan;
        if (mNextSpan)
            mNextSpan->mPrevSpan = newNode;
        else
            *mListEnd = newNode;
        mNextSpan = newNode;
    }

    //! Inserts a new Span before this.
    inline void insertBeforeSpan(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge *newNode)
    {
        newNode->mNextSpan = this;
        newNode->mPrevSpan = mPrevSpan;
        if (mPrevSpan)
            mPrevSpan->mNextSpan = newNode;
        else
            *mListBegin = newNode;
        mPrevSpan = newNode;
    }

    //! Adds this Span to the beginning of the list.
    inline void addHeadSpan(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        mPrevSpan = NULL;
        mNextSpan = *mListBegin;
        if (*mListBegin)
            (*mListBegin)->mPrevSpan = this;
        else
            *mListEnd = this;
        *mListBegin = this;
    }

    //! Adds this Span to the end of the list.
    inline void addTailSpan(XFcPrimitiveDrawEdge **mListBegin, XFcPrimitiveDrawEdge **mListEnd)
    {
        mPrevSpan = *mListEnd;
        mNextSpan = NULL;
        if (*mListEnd)
            (*mListEnd)->mNextSpan = this;
        else
            *mListBegin = this;
        *mListEnd = this;
    }
};


//! XFcPrimitiveDrawLineEdge implements a straight line edge.
class XFcPrimitiveDrawLineEdge : public XFcPrimitiveDrawEdge
{
public:

    REAL mGradient;                 //!< Line gradient.

    //! Advances the current scanline with one step.
    virtual void advanceScanline() { mXp += mGradient; mXpi = (INT32) mXp; }
};


//! XFcPrimitiveDrawIndexedEdge implements an edge with x offset index table.
/*! This can be used for instance for drawing circles and ellipses.
 */
class XFcPrimitiveDrawIndexedEdge : public XFcPrimitiveDrawEdge
{
public:

    REAL *mIndexTable;              //!< Table of indicies.
    REAL mXMultiplier;              //!< Horizontal scale.
    REAL mXOffset;                  //!< Offset in horizontal direction.
    INT32 mIndex;

    //! Advances the current scanline with one step.
    virtual void advanceScanline()
    {
        mXp = mIndexTable[++mIndex] * mXMultiplier + mXOffset;
        mXpi = (INT32) mXp;
    }
};


//! Defines a indexed primitive.
/*! Indexed primitives are drawing primitives that are defined by an array
 *  of horizontal coordinates. They can be used for drawing various arbitary
 *  shapes, a circle for instance consists of two indexed primitives, one defining
 *  the right edge and other the left edge.
 */
class XFCDLLEXPORT XFcPrimitiveDrawIndexedPrimitive
{
public:

    //! Creates XFcPrimitiveDrawIndexedPrimitive with given table size.
    XFCIMPORT static XFcPrimitiveDrawIndexedPrimitive *create(INT32 aIndexTableSize);

    //! Creates XFcPrimitiveDrawIndexedPrimitive from an array of indexes.
    /*! \param aIndexTable Pointer to indicies.
     *  \param aIndexTableSize Amount of indicies.
     *  \param aXPosition Horizontal position of the primitive.
     *  \param aYPosition Vertical position of the primitive.
     *  \param aXScale Horizontal scale of the primitive
     *  \param aEdgeType Type of the edge. (XFC_PRIMITIVE_LEFT or XFC_PRIMITVE_RIGHT)
     */
    XFCIMPORT static XFcPrimitiveDrawIndexedPrimitive *create(REAL *aIndexTable, INT32 aIndexTableSize,
                                                              INT32 aXPosition, INT32 aYPosition,
                                                              REAL aXScale, INT32 aEdgeType);

    //! Creates XFcPrimitiveDrawIndexedPrimitive that defines the right half of a circle.
    /*! \param aXPos X position of the center of the circle.
     *  \param aYPos Y position of the center of the circle.
     *  \param aRadius Radius of the circle.
     *  \param aXScale Horizontal scale of the circle.
     *  \param aXSkewStep Horizontal skew step per scanline of the circle.
     *  \param aEdgeType Type of the edge. (XFC_PRIMITIVE_LEFT or XFC_PRIMITVE_RIGHT)
     *  \param aYMin Minimum Y coordinate of the rendering area.
     *  \param aYMax Maximum Y coordinate of the rendering area.
     */
    XFCIMPORT static XFcPrimitiveDrawIndexedPrimitive *createHalfCircle(INT32 aXPos, INT32 aYPos,
                                                                        INT32 aRadius, REAL aXScale, REAL aXSkewStep,
                                                                        INT32 aEdgeType, INT32 aYMin, INT32 aYMax);

    //! Destructor.
    XFCIMPORT ~XFcPrimitiveDrawIndexedPrimitive();

    REAL *mIndexTable;              //!< Table of indicies.
    REAL mXScale;                   //!< Horizontal scale.
    REAL mXPosition;                //!< X position.
    REAL mYPosition;                //!< Y position.
    INT32 mIndexCount;              //!< Count of indicies.
    INT mTableIsClone;              //!< Flag that is set if the table is not owned by the primitive.
    INT32 mEdgeType;                //!< Type of the edge (on/off).

protected:

    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDrawIndexedPrimitive();

};


//! Defines a set of XFcPrimitiveDrawPoints.
/*! XFcPrimitiveDrawPointSet is a set of points, that can be used for defining
 *  lines with XFcPrimitiveDrawLineSet.
 */
class XFCDLLEXPORT XFcPrimitiveDrawPointSet
{
public:

    //! Creates a point set with aMaxPointCount maximum amount of points .
    XFCIMPORT static XFcPrimitiveDrawPointSet *create(INT32 aMaxPointCount);

    //! Destructor.
    XFCIMPORT ~XFcPrimitiveDrawPointSet();

    //! Returns the amount of points in the point set.
    XFCIMPORT INT32 getPointCount();

    //! Adds a point to the point set.
    XFCIMPORT void addPoint(XFcVector2 &aPos);

    //! Returns a pointer to a point at aPointIndex.
    XFCIMPORT XFcPrimitiveDrawPoint * getPoint(INT32 aPointIndex);

    //! Clears the point set.
    XFCIMPORT void clear();

    //! Calculates the mScaledPos value for all points in the point set.
    /*! This is used for scaling the point coordinates in antialiased rendering.
     */
    XFCIMPORT void calculateScaledValues(REAL aScale);

    //! Calculates the mScaledPos value for all points in the point set using a matrix.
    /*! This is used for scaling the point coordinates in antialiased rendering.
     */
    XFCIMPORT void calculateScaledValues(XFcMatrix3 &aTransformation);

protected:

    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDrawPointSet();

    XFcPrimitiveDrawPoint *mPoints; //!< Array of points.
    INT32 mPointCount;              //!< Count of points.
    INT32 mMaxPoints;               //!< Maximum amount of points.
};


//! Defines a set of XFcPrimitiveDrawLines.
/*! XFcPrimitiveDrawLineSet is a set of lines defined with indicies. Each
 *  line has a start index and end index that refer to points in
 *  XFcPrimitiveDrawPointSet.
 */
class XFCDLLEXPORT XFcPrimitiveDrawLineSet
{
public:

    //! Creates a line index set with aMaxIndexCount maximum amount of lines .
    XFCIMPORT static XFcPrimitiveDrawLineSet *create(INT32 aMaxLineCount);

    //! Destructor.
    XFCIMPORT ~XFcPrimitiveDrawLineSet();

    //! Returns the amount of line indicies.
    XFCIMPORT INT32 getLineCount();

    //! Adds a line to the set.
    XFCIMPORT void addLine(INT32 aStart, INT32 aEnd);

    //! Returns a pointer to a line index at aLineIndex.
    XFCIMPORT XFcPrimitiveDrawLine * getLine(INT32 aLineIndex);

    //! Clears the line index set.
    XFCIMPORT void clear();

protected:

    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDrawLineSet();

    XFcPrimitiveDrawLine *mLines;   //!< Array of lines.
    INT32 mLineCount;               //!< Count of lines.
    INT32 mMaxLines;                //!< Maximum amount of lines.
};


//! Defines a set of indexed primitives.
class XFCDLLEXPORT XFcPrimitiveDrawIndexedPrimitiveSet
{
public:

    //! Creates an indexed set with aMaxPrimitiveCount maximum amount of primitives.
    XFCIMPORT static XFcPrimitiveDrawIndexedPrimitiveSet *create(INT32 aMaxPrimitiveCount);

    //! Destructor.
    XFCIMPORT ~XFcPrimitiveDrawIndexedPrimitiveSet();

    //! Returns the amount of primitives.
    XFCIMPORT INT32 getPrimitiveCount();

    //! Adds a primitive.
    XFCIMPORT void addPrimitive(XFcPrimitiveDrawIndexedPrimitive *aPrimitive);

    //! Returns a pointer to a primitive at aPrimitiveIndex.
    XFCIMPORT XFcPrimitiveDrawIndexedPrimitive * getPrimitive(INT32 aPrimitiveIndex);

    //! Clears the primitive index set.
    XFCIMPORT void clear();

protected:

    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDrawIndexedPrimitiveSet();

    XFcPrimitiveDrawIndexedPrimitive **mPrimitives; //!< Array of primitive pointers.
    INT32 mPrimitiveCount;                          //!< Count of primitives.
    INT32 mMaxPrimitives;                           //!< Maximum amount of primitives.
};


//! Defines a set of XFcPrimitiveDrawEdges.
class XFCDLLEXPORT XFcPrimitiveDrawEdgeSet
{
public:

    //! Creates a set of XFcPrimitiveDrawEdges.
    /*! /param aMaxLineEdgeCount Maximum count of line edges in the set.
     *  /param aMaxIndexedEdgeCount Maximum count of indexed edges in the set.
     */
    XFCIMPORT static XFcPrimitiveDrawEdgeSet *create(INT32 aMaxLineEdgeCount, INT32 aMaxIndexedEdgeCount);

    //! Destructor.
    XFCIMPORT ~XFcPrimitiveDrawEdgeSet();

    //! Returns the count of line edges.
    XFCIMPORT INT32 getLineEdgeCount();

    //! Returns the count of indexed edges.
    XFCIMPORT INT32 getIndexedEdgeCount();

    //! Adds a line edge to the edge set.
    /*! /param aYStart Vertical start position of the line edge.
     *  /param aYEnd Vertical end position of the line edge.
     *  /param aXp Horizontal start position of the line edge.
     *  /param aXpi Horizontal start position of the line edge as integer.
     *  /param aGradient Gradient of the line.
     *  /param aEdgeType Type of the edge (XFC_PRIMITIVE_DRAW_LEFT or XFC_PRIMITIVE_DRAW_RIGHT).
     */
    XFCIMPORT void addLineEdge(INT32 aYStart, INT32 aYEnd, REAL aXp, INT32 aXpi, REAL aGradient, INT32 aEdgeType);


    //! Adds an indexed edge to the edge set.
    /*! /param aYStart Vertical start position of the indexed edge.
     *  /param aYEnd Vertical end position of the indexed edge.
     *  /param aIndexTable Pointer to the index table.
     *  /param aXMultiplier Mutliplier for the indicies in horizontal direction.
     *  /param aXOffset Horizontal offset for the indicies.
     *  /param aEdgeType Type of the edge (XFC_PRIMITIVE_DRAW_LEFT or XFC_PRIMITIVE_DRAW_RIGHT).
     *  /param aStartIndex Starting index in the index table for the edge.
     */
    XFCIMPORT void addIndexedEdge(INT32 aYStart, INT32 aYEnd, REAL *aIndexTable, REAL aXMultiplier,
                                  REAL aXOffset, INT32 aEdgeType, INT32 aStartIndex);

    //! Returns a pointer to the line edge at aLineEdge position.
    XFCIMPORT XFcPrimitiveDrawLineEdge * getLineEdge(INT32 aLineEdge);

    //! Returns a pointer to the indexed edge at aIndexedEdge position.
    XFCIMPORT XFcPrimitiveDrawIndexedEdge * getIndexedEdge(INT32 aIndexedEdge);

    //! Clears the edge set.
    XFCIMPORT void clear();

    //! Converts lines described by aPoints and aLines to line edges in the set.
    XFCIMPORT void calculateLineInfo(INT32 aYClipMin, INT32 aYClipMax, XFcPrimitiveDrawPointSet *aPoints,
                                     XFcPrimitiveDrawLineSet *aLines);

    //! Converts indexed primitives described by aPrimitives to primitive edges in the set.
    XFCIMPORT void calculateIndexedEdgeInfo(INT32 aYClipMin, INT32 aYClipMax,
                                            XFcPrimitiveDrawIndexedPrimitiveSet *aPrimitives);

    //! Returns the minimum Y value of entries in the set.
    XFCIMPORT INT32 getMinY();

    //! Returns the maximum Y value of entries in the set.
    XFCIMPORT INT32 getMaxY();

protected:

    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDrawEdgeSet();

    XFcPrimitiveDrawLineEdge *mLineEdges;       //!< Pointer to line edges.
    INT32 mLineEdgeCount;                       //!< Count of line edges.
    INT32 mMaxLineEdges;                        //!< Maximum amount of line edges.

    XFcPrimitiveDrawIndexedEdge *mIndexedEdges; //!< Pointer to indexed edges.
    INT32 mIndexedEdgeCount;                    //!< Count of indexed edges.
    INT32 mMaxIndexedEdges;                     //!< Maximum amount of indexed edges.

    INT32 mMinY;                                //!< Minimum Y value of the entries in the set.
    INT32 mMaxY;                                //!< Maximum Y value of the entries in the set.
};

class XFcPrimitiveDraw;

typedef void (XFcPrimitiveDraw::*xfcPrimitiveBlitFunction)(UINT8 *,INT32);

//! XFcPrimitiveDraw is a class that handles drawing of 2D vector graphic primitives.
/*! 2D vector graphic primitives can be polygons (defined with XFcPrimitiveDrawLineSet
 *  and XFcPrimitiveDrawPointSet) or indexed edge sets (that can be used for describing
 *  circles for instance). Primitives are added to an instance of XFDcPrimitiveDraw,
 *  after which render() (or some variant of it) is called. Rendering can be performed
 *  with XOR-fill (where crossing lines toggle fill on/off - this is the default) or with
 *  constant fill (where edge direction defines if fill is toggled off or not). Rendering
 *  can be done also with or without antialiasing.
 */
class XFCDLLEXPORT XFcPrimitiveDraw
{
public:

    //! Static constructor.
    XFCIMPORT static XFcPrimitiveDraw * create(INT32 aWidth, INT32 aHeight, INT32 aMaxLineCount,
                                               INT32 aMaxIndexedEdgeCount);

    //! Destructor.
    XFCIMPORT virtual ~XFcPrimitiveDraw();

    //! Sets the color for the rendering (doesn't contain alpha).
    /*! The color is used in all render calls after this. This overrides the filler setting
     *  when called.
     *  The color is in X8R8G8B8 format
     */
    XFCIMPORT void setColor(UINT32 aColor);

    //! Sets the opacity for the rendering.
    /*! This is used as the opacity for both color and custom fillers.
     */
    XFCIMPORT void setOpacity(UINT8 aOpacity);

    //! Sets the filler for rendering.
    /*! The filler is used in all render calls after this. This overrides the color
     *  setting when called. Filler can be also set to NULL, after which the current color
     *  is used.
     */
    XFCIMPORT void setFiller(XFcPrimitiveDrawFiller *aFiller);

    //! Sets the clipping rectangle for rendering.
    /*! Note that for antialiased rendering, the clipping rectangle should be multiplied with 8.
     * The clipping rectangle is inclusive, aClipMaxX and aClipMaxY are the last coordinates that are
     * still inside the rect.
     */
    XFCIMPORT void setClippingRect(INT32 aClipMinX, INT32 aClipMinY, INT32 aClipMaxX, INT32 aClipMaxY);

    //! Adds a polygon for rendering.
    /*! If polygon is to be rendered with render anti-aliasing, the coordinates should be multiplied with 8.
     */
    XFCIMPORT void addPolygon(XFcPrimitiveDrawPointSet *aPointSet, XFcPrimitiveDrawLineSet *aLineSet);

    //! Adds an indexed edge set (e.g. a circle) for rendering.
    /*! If the edge set is to be rendered with anti-aliasing, the coordinates should be multiplied with 8.
     */
    XFCIMPORT void addIndexedSet(XFcPrimitiveDrawIndexedPrimitiveSet *aIndexedSet);

    //! Renders the edges to the surface with antialiasing using even-odd fillrule.
    XFCIMPORT void renderEvenOddAA(UINT8 *aData, INT32 aWidth, INT32 aHeight, INT32 aPitch, INT32 aBufferFormat);

    //! Renders the edges to the surface with antialiasing using non-zero fillrule.
    XFCIMPORT void renderNonZeroAA(UINT8 *aData, INT32 aWidth, INT32 aHeight, INT32 aPitch, INT32 aBufferFormat);

    //! Renders the edges to the surface without antialiasing using even-odd fillrule.
    XFCIMPORT void renderEvenOdd(UINT8 *aData, INT32 aWidth, INT32 aHeight, INT32 aPitch, INT32 aBufferFormat);

    //! Renders the edges to the surface without antialiasing using non-zero fillrule.
    XFCIMPORT void renderNonZero(UINT8 *aData, INT32 aWidth, INT32 aHeight, INT32 aPitch, INT32 aBufferFormat);

protected:
    //! Protected constructor.
    XFCIMPORT XFcPrimitiveDraw();

    //! Reallocates the tables for new size requirements of the primitivedraw.
    XFCIMPORT INT resize(INT32 aWidth, INT32 aHeight);

    //! Init the bit counter that is used for calculating coverages from bit masks.
    XFCIMPORT void initBitCounter();

    //! Clears the high-resolution 1-bit representation of the scanline.
    XFCIMPORT void clearHiResSpan();

    //! Clears the actual color data of the scanline.
    XFCIMPORT void clearLoResSpan();

    //! Clears scanlines in scanline table.
    XFCIMPORT void clearScanlines();

    //! Adds edges from member edge set to scanline table.
    XFCIMPORT void addScanlines(INT32 aClipTop, INT32 aClipBot);

    //! Inserts edge to AET (active edge table).
    XFCIMPORT void insertToAET(XFcPrimitiveDrawEdge *aEdge, XFcPrimitiveDrawEdge *aAETEdge);

    //! Insets span to span table.
    XFCIMPORT void insertToSpan(XFcPrimitiveDrawEdge *aEdge, INT32 aMinX, INT32 aMaxX, XFcPrimitiveDrawEdge *aSpanEdge);

    //! Processes the scanline table at given Y position and add to AET and span list.
    XFCIMPORT void scanlineToAETandSpanlist(INT32 aYPos, INT32 aMinX, INT32 aMaxX);

    //! Processes the scanline table at given Y position and add to AET.
    XFCIMPORT void scanlineToAET(INT32 aYPos);

    //! Sorts the AET with bubble sort. 
    /*! The algorithm sounds inefficient, but is suitable, as AET is mostly sorted already.
     */
    XFCIMPORT void sortAET();

    //! Resets AET.
    XFCIMPORT void resetAET();

    //! Resets the span information in lines using AET.
    XFCIMPORT void spansFromAET(INT32 aMinX, INT32 aMaxX);

    //! Downscales the span coordinates by 8.
    XFCIMPORT void downScaleSpans();

    //! Compresses the spans for conversion & blitting.
    XFCIMPORT void compressSpans();

    //! Converts the span from high-res representation to low-res representation.
    XFCIMPORT void convertSpan();

    //! Returns the blit function used for the buffer format.
    XFCIMPORT xfcPrimitiveBlitFunction getBlitFunction(INT32 aBufferFormat);

    //! Blits the span to a buffer in 16 bit mode, no alpha.
    XFCIMPORT void blitSpan16(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 16 bit mode with alpha.
    XFCIMPORT void blitSpan16Alpha(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 16 bit mode using a filler.
    XFCIMPORT void blitSpan16Filled(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 32 bit XRGB mode with alpha.
    XFCIMPORT void blitSpan32Alpha(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 32 bit XRGB mode using a filler.
    XFCIMPORT void blitSpan32Filled(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 32 bit ARGB mode with alpha.
    XFCIMPORT void blitSpan32ARGBAlpha(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in 32 bit ARGB mode using a filler.
    XFCIMPORT void blitSpan32ARGBFilled(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in generic mode with alpha.
    XFCIMPORT void blitSpanGenericAlpha(UINT8 *aData, INT32 aBufferFormat);

    //! Blits the span to a buffer in generic mode using a filler.
    XFCIMPORT void blitSpanGenericFilled(UINT8 *aData, INT32 aBufferFormat);

    //! Fills the span to a temporary scanline buffer using current XFcPrimitiveDrawFiller
    XFCIMPORT void fillSpan(INT32 aY);

    UINT8 *mHiResSpan;                      //!< Pointer to the high res scanline.
    UINT8 *mLoResSpan;                      //!< Pointer to the low res scanline.
    UINT8 *mBitCounter;                     //!< Pointer to the bit counter table.
    UINT32 *mFillerSpan;                    //!< Pointer to the temporary filler scanline.

    XFcPrimitiveDrawEdge **mScanlineBegin;  //!< Table of pointers to first edges of scanlines.
    XFcPrimitiveDrawEdge **mScanlineEnd;    //!< Table of pointers to last edges of scanlines.

    XFcPrimitiveDrawEdge *mAETBegin;        //!< Pointer to the first edge in AET.
    XFcPrimitiveDrawEdge *mAETEnd;          //!< Pointer to the last edge in AET.

    XFcPrimitiveDrawEdge *mSpanBegin;       //!< Pointer to the first edge of current span.
    XFcPrimitiveDrawEdge *mSpanEnd;         //!< Pointer to the last edge of current span.

    UINT32 mColorTable[33];                 //!< Pre-computed color values in X6X5X5 format.

    INT32 mWidth;                           //!< Width of the maximum rendering area.
    INT32 mHeight;                          //!< Height of the maximum rendering ares.

    XFcPrimitiveDrawEdgeSet *mEdgeSet;      //!< Pointer to the edge set containing the primitives.
    XFcPrimitiveDrawFiller *mFiller;        //!< Pointer to a filler that is used for more complex fills.

    //! Clipping rectangle boundaries.
    INT32 mClipMinX;
    INT32 mClipMinY;
    INT32 mClipMaxX;
    INT32 mClipMaxY;

    //! Stored color and alpha values.
    UINT32 mColor32;
    UINT16 mColor16;
    UINT32 mAlpha32;
    UINT32 mAlpha16;

};


#endif // !XFC_CORE_XFCPRIMITIVEDRAW_H_INCLUDED

