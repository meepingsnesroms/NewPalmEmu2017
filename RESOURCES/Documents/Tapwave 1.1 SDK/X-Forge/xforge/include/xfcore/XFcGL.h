/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief X-Forge Graphics Library.
 * 
 * $Id: XFcGL.h,v 1.21 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.21 $
 */

#ifndef XFC_CORE_XFCGL_H_INCLUDED
#define XFC_CORE_XFCGL_H_INCLUDED


#include <xfcore/XFcGLTexture.h>
#include <xfcore/XFcGLEnums.h>
#include <xfcore/XFcGLDeviceInfo.h>


class XFcGLVertexBuffer;
class XFcGLTriangleInfoBuffer;
class XFcGLDeviceInfo;


//! Vertex type for the custom primitive callback mechanism.
/*!
 * \sa XFcGL
 * \sa XFcGLCustomRenderCallback
 */
class XFcGLCustomVertex
{
public:
    REAL mSX;
    REAL mSY;
    REAL mSZ;
    REAL mRHW;
    UINT32 mDiffuseColor;
};


//! Callback interface for the custom primitive type mechanism.
/*!
 * \sa XFcGL
 * \sa XFcGLCustomVertex 
 */
class XFcGLCustomRenderCallback
{
public:
    virtual void customRender(XFcGLCustomVertex &aVertex,
                              INT32 aCustomData) = 0;
};


//! Max. number of lights supported.
/*! \note change requires core recompile.
 */
#define XFC_MAX_NUMBER_OF_LIGHTS 8


//! Defines GL viewport.
/*!
 * \sa XFcGL
 */
class XFcGLViewport 
{
public:
    INT32 mXScreenOffset;   //!< Horizontal offset on screen of this viewport.
    INT32 mYScreenOffset;   //!< Vertical offset on screen of this viewport.
    INT32 mAreaWidth;       //!< Viewport area width.
    INT32 mAreaHeight;      //!< Viewport area height.
    REAL  mMinZ;            //!< Minimum z value.
    REAL  mMaxZ;            //!< Maximum z value.
};


//! Defines a light source.
/*! You also have to define material in order to get any sensible use
 *  out of light sources.
 *  \sa XFcGL
 *  \sa XFcGLMaterial
 */
class XFcGLLight 
{
public:
    //! Light type.
    /*! \sa XFCGLLIGHTTYPES
     */
    INT32 mType;
    //! Diffuse color of light.
    REAL mDiffuseR;
    //! Diffuse color of light.
    REAL mDiffuseG;
    //! Diffuse color of light.
    REAL mDiffuseB;
    //! Specular color of light. Ignored currently.
    REAL mSpecularR;
    //! Specular color of light. Ignored currently.
    REAL mSpecularG;
    //! Specular color of light. Ignored currently.
    REAL mSpecularB;
    //! Ambient color of light. Ignored currently.
    REAL mAmbientR;
    //! Ambient color of light. Ignored currently.
    REAL mAmbientG;
    //! Ambient color of light. Ignored currently.
    REAL mAmbientB;
    //! Position of the light in world space.
    XFcVector3 mPosition;
    //! Direction of the light in world space. Ignored for point lights.
    XFcVector3 mDirection;
    //! Light does not evaluate further than this.
    REAL mRange;
    //! Constant attenuation.
    REAL mAttenuateConstant;
    //! Linear attenuation.
    REAL mAttenuateLinear;
    //! Squared attenuation.
    REAL mAttenuateSquared;
    //! Hotspot angle for spotlight cone.
    REAL mHotspotAngle;
    //! Falloff angle for spotlight cone.
    REAL mFalloffAngle;
};


//! Defines a material.
/*!
 * \sa XFcGL
 * \sa XFcGLLight
 */
class XFcGLMaterial 
{
public:
    //! Material diffuse color.
    UINT32 mDiffuseColor;
    //! Material specular color.
    UINT32 mSpecularColor;
    //! Material ambient color.
    UINT32 mAmbientColor;
    //! Material emissive (self illuminating) color.
    UINT32 mEmissiveColor;
    //! Glossiness value. Ignored currently.
    REAL mSpecularExponent;
};


// Examples of legal vertex flags & related vertex formats.

//! Flag definitions for the XFcGLVertex type.
/*! \sa XFcGLVertex */
#define XFCGL_VERTEX (XFCGLVF_XYZ | XFCGLVF_NORMAL | XFCGLVF_TEXTURE1)
//! Flag definitions for the XFcGLLVertex type.
/*! \sa XFcGLLVertex */
#define XFCGL_LVERTEX (XFCGLVF_XYZ | XFCGLVF_DIFFUSECOLOR | XFCGLVF_TEXTURE1)
//! Flag definitions for the XFcGLTLVertex type.
/*! \sa XFcGLTLVertex */
#define XFCGL_TLVERTEX (XFCGLVF_XYZ | XFCGLVF_RHW | XFCGLVF_DIFFUSECOLOR | XFCGLVF_TEXTURE1)


//! An example for legal vertex format.
/*! Use XFCGL_VERTEX as vertex format flags.
 * XFCGL_VERTEX is defined as (XFCGLVF_XYZ | XFCGLVF_NORMAL | XFCGLVF_TEXTURE1).
 * \sa XFCGL_VERTEX
 */
class XFcGLVertex
{
public:
    REAL mX;
    REAL mY;
    REAL mZ;
    REAL mNX;
    REAL mNY;
    REAL mNZ;
    REAL mU;
    REAL mV;
};


//! An example for legal vertex format.
/*! Use XFCGL_LVERTEX as vertex format flags.
 * XFCGL_LVERTEX is defined as
 * (XFCGLVF_XYZ | XFCGLVF_DIFFUSECOLOR | XFCGLVF_TEXTURE1).
 * \sa XFCGL_LVERTEX
 */
class XFcGLLVertex
{
public:
    REAL mX;
    REAL mY;
    REAL mZ;
    UINT32 mDiffuseColor;
    REAL mU;
    REAL mV;    
};


//! An example for legal vertex format.
/*! Use XFCGL_TLVERTEX as vertex format flags.
 * XFCGL_TLVERTEX is defined as
 * (XFCGLVF_XYZ | XFCGLVF_RHW | XFCGLVF_DIFFUSECOLOR | XFCGLVF_TEXTURE1)
 * \sa XFCGL_TLVERTEX
 */
class XFcGLTLVertex
{
public:
    REAL mX;
    REAL mY;
    REAL mZ;
    REAL mRHW;
    UINT32 mDiffuseColor;
    REAL mU;
    REAL mV;    
};


//! X-Forge Core Graphics Library.
/*!
 * \note XFcGL functions return values of XFCGLERRORS enum.
 * \sa XFCGLERRORS
 */
class XFCDLLEXPORT XFcGL
{
public:
    //! Returns the device info for the currently active device.
    XFCIMPORT static const XFcGLDeviceInfo * const getCurrentDeviceInfo();
    
    //! Returns linked list of currently available devices.
    XFCIMPORT static const XFcGLDeviceInfo * const getDeviceInfo();

    XFCIMPORT static XFcGL * create(UINT32 aDeviceId = XFCGLC_DEFAULT, 
                                    UINT32 aFlags = XFCGLC_DEFAULT);

    //! Re-creates device without destroying the XFcGL object.
    /*! \note Resets all states.
     */
    XFCIMPORT INT recreate(UINT32 aDeviceId = XFCGLC_DEFAULT, 
                           UINT32 aFlags = XFCGLC_DEFAULT);

    //! Constructor.
    XFCIMPORT XFcGL();
    //! Destructor.
    XFCIMPORT ~XFcGL();
    
    //! Begins rendering block.
    /*! Everything that is supposed to be sorted should be between
     *  calls to beginRender() and endRender().
     */
    XFCIMPORT INT32 beginRender();
    
    //! Ends rendering block.
    /*! Does actual rendering in software mode.
     *  Hardware implementations may render all the time.
     */
    XFCIMPORT INT32 endRender();
    
    //! Sets the currently active viewport.
    /*!
     * \param aViewport new viewport settings.
     */
    XFCIMPORT INT32 setViewport(XFcGLViewport &aViewport);
    
    //! Retrieves the currently active viewport.
    /*!
     * \param aViewport returned viewport settings.
     */
    XFCIMPORT INT32 getViewport(XFcGLViewport &aViewport);
    
    //! Processes vertices.
    /*!
     * This method can be used to make special effects that require the same
     * calculations as everything rendered. You do not need to call this for
     * normal rendering.
     * \note Source must not have RHW component, target must have it.
     * \param aSource source vertex buffer.
     * \param aTarget target vertex buffer.
     * \param aOffset offset in source buffer to start processing vertices from.
     * \param aCount number of vertices to process.
     */
    XFCIMPORT INT32 processVertices(XFcGLVertexBuffer &aSource,
                                    XFcGLVertexBuffer &aTarget,
                                    INT32 aOffset, INT32 aCount);
    
    //! Renders primitive(s). 
    /*!
     * Renders one or more triangles using current render states, matrices and
     * textures.
     *
     * \param aSource Source vertex buffer. See XFcGLVertexBuffer for details.
     * \param aPrimitiveType Primitive type, see XFCGLPRIMITIVETYPES.
     * \param aOffset Offset to the vertex buffer from which to start rendering.
     * \param aNumVertices Number of vertices to render (e.g. 3 for one triangle).
     * \param aFirstVertex Index to first vertex for rendering.
     * \param aLastVertex Index to last vertex for rendering.
     * \param aTriangleInfo Triangle info buffer.
     * \sa XFCGLPRIMITIVETYPES
     */
    XFCIMPORT INT32 renderPrimitive(XFcGLVertexBuffer *aSource,
                                    INT32 aPrimitiveType, INT32 aOffset,
                                    INT32 aNumVertices,
                                    INT32 aFirstVertex, INT32 aLastVertex,
                                    XFcGLTriangleInfoBuffer *aTriangleInfo);
    
    //! Renders primitive(s) using index list.
    /*!
     * Renders one or more triangles using current render states, matrices and
     * textures. Using this function instead of renderPrimitive() is often
     * cheaper as the system doesn't need to do all the transformations for
     * all vertices multiple times if several faces are using the same vertex.
     *
     * \param aSource Source vertex buffer. See XFcGLVertexBuffer for details.
     * \param aPrimitiveType Primitive type, see XFCGLPRIMITIVETYPES.
     * \param aOffset Offset to the vertex buffer from which to start rendering
     * \param aIndexArray Pointer to a list of indices to the vertex buffer.
     * \param aNumVertices Number of indices to render (e.g. 3 for one triangle).
     * \param aFirstVertex Index to first vertex for rendering.
     * \param aLastVertex Index to last vertex for rendering.
     * \param aTriangleInfo Triangle info buffer.
     * \sa XFCGLPRIMITIVETYPES
     */
    XFCIMPORT INT32 renderPrimitiveIndexed(XFcGLVertexBuffer *aSource,
                                           INT32 aPrimitiveType,
                                           INT32 aOffset, UINT16 *aIndexArray,
                                           INT32 aNumVertices,
                                           INT32 aFirstVertex,
                                           INT32 aLastVertex,
                                           XFcGLTriangleInfoBuffer *aTriangleInfo);
    
    //! Sets a light's data.
    /*!
     * \param aIndex index number of the light.
     * \param aLight new light data.
     * \sa XFcGLLight
     */
    XFCIMPORT INT32 setLight(INT32 aIndex, XFcGLLight &aLight);
    
    //! Gets specific light's data.
    /*!
     * \param aIndex index number of the light.
     * \param aLight returned light data.
     * \sa XFcGLLight
     */
    XFCIMPORT INT32 getLight(INT32 aIndex, XFcGLLight &aLight);
    
    //! Enables or disables a light.
    /*!
     * \note Lighting is very expensive operation; use as few active
     *       lights as possible.
     * \param aIndex index number of the light.
     * \param aState 1 to enable the light, or 0 to disable the light.
     */
    XFCIMPORT INT32 enableLight(INT32 aIndex, INT aState);
    
    //! Sets the currently active matrix.
    /*!
     * \param aMatrixId Matrix type, see XFCGLMATRIXID.
     * \param aMatrix new active matrix.
     * \sa XFCGLMATRIXID
     */
    XFCIMPORT INT32 setMatrix(INT32 aMatrixId, XFcMatrix4 &aMatrix);
    
    //! Gets the currently active matrix.
    /*!
     * \param aMatrixId Matrix type, see XFCGLMATRIXID.
     * \param aMatrix returned active matrix.
     * \sa XFCGLMATRIXID
     */
    XFCIMPORT INT32 getMatrix(INT32 aMatrixId, XFcMatrix4 &aMatrix);
    
    //! Sets the custom renderer callback.
    /*!
     * \param aCallBack pointer to the callback object.
     */
    XFCIMPORT INT32 setCustomCallback(XFcGLCustomRenderCallback *aCallback);
    
    //! Sets the custom renderer data.
    /*!
     * \param aData value that is passed to the custom render callback.
     */
    XFCIMPORT INT32 setCustomCallbackData(INT32 aData);
    
    //! Sets the value of a render state as an INT32.
    /*!
     * \param aStateId State type, see XFCGLRENDERSTATES.
     * \param aValue Render state value as an INT32.
     * \sa XFCGLRENDERSTATES
     * \sa setStateF
     *
     * \note Unfortunately, making an overloaded method accepting both INT32
     *       and REAL doesn't work, since compilers don't know whether to
     *       convert an enumeration to an integer or to a float.
     */
    XFCIMPORT INT32 setStateI(INT32 aStateId, INT32 aValue);
    
    //! Sets the value of a render state as a REAL.
    /*!
     * \param aStateId State type, see XFCGLRENDERSTATES.
     * \param aValue Render state value as a REAL.
     * \sa XFCGLRENDERSTATES
     * \sa setStateI
     *
     * \note Unfortunately, making an overloaded method accepting both INT32
     *       and REAL doesn't work, since compilers don't know whether to
     *       convert an enumeration to an integer or to a float.
     */
    XFCIMPORT INT32 setStateF(INT32 aStateId, REAL aValue);
    
    //! Returns a render state value as an INT32.
    /*!
     * \param aStateId State type, see XFCGLRENDERSTATES.
     * \param aValue INT32 to store the result.
     * \sa XFCGLRENDERSTATES
     * \sa getStateF
     *
     * \note Unfortunately, making an overloaded method accepting both INT32
     *       and REAL doesn't work, since compilers don't know whether to
     *       convert an enumeration to an integer or to a float.
     */
    XFCIMPORT INT32 getStateI(INT32 aStateId, INT32 &aValue);
    
    //! Returns a render state value as a REAL.
    /*!
     * \param aStateId State type, see XFCGLRENDERSTATES.
     * \param aValue REAL to store the result.
     * \sa XFCGLRENDERSTATES
     * \sa getStateI
     *
     * \note Unfortunately, making an overloaded method accepting both INT32
     *       and REAL doesn't work, since compilers don't know whether to
     *       convert an enumeration to an integer or to a float.
     */
    XFCIMPORT INT32 getStateF(INT32 aStateId, REAL &aValue);
    
    //! Checks if a specific blend mode is supported.
    /*!
     * Since most blend mode combinations will not be supported
     * by all hardware, you can use this function to determine,
     * at runtime, if a blend mode is supported.
     * \par
     * Currently, the software renderer supports the following
     * blend mode combinations:
     * \li \code NONE   : src = ONE      tgt = ZERO        \endcode
     * \li \code ALPHA  : src = SRCALPHA tgt = INVSRCALPHA \endcode
     * \li \code MUL    : src = ZERO     tgt = SRCCOLOR    \endcode
     * \li \code ADD    : src = ONE      tgt = ONE         \endcode
     * \li \code INVMUL : src = ZERO     tgt = INVSRCCOLOR \endcode
     * \sa XFCGLLEGALBLENDMODES
     * \sa XFCGLBLENDMODES
     *
     * \param aSrcBlend Source blend mode, see XFCGLBLENDMOES.
     * \param aTgtBlend Target blend mode, see XFCGLBLENDMOES.
     */
    XFCIMPORT INT32 validateBlendMode(INT32 aSrcBlend, INT32 aTgtBlend);
    
    //! Sets the current active texture.
    /*!
     * \param aTexture new active texture, or NULL to disable texturing.
     */
    XFCIMPORT INT32 setTexture(XFcGLTexture *aTexture);

    //! Gets the current texture.
    /*!
     * \return a pointer to the currently active texture, or NULL if none.
     */
    XFCIMPORT XFcGLTexture * getTexture();
    
    //! Sets the current material.
    /*!
     * \param aMaterial new material data.
     */
    XFCIMPORT INT32 setMaterial(XFcGLMaterial &aMaterial);
    
    //! Gets the current material.
    /*!
     * \param aMaterial returned current material data.
     */
    XFCIMPORT INT32 getMaterial(XFcGLMaterial &aMaterial);

    //! Draws a 2D sprite using screen coordinates.
    /*!
     * Draws the sprite with polygons, so you can make transformations like
     * Z-rotation on them. If you don't need any transformations, blitting a
     * surface directly to the secondary buffer may be faster.
     *
     * \param aCenterX center X-coordinate.
     * \param aCenterY center Y-coordinate.
     * \param aZ Z-coordinate.
     * \param aWidth width.
     * \param aHeight height.
     * \param aU0 first U-coordinate to the texture rectangle.
     * \param aV0 first V-coordinate to the texture rectangle.
     * \param aU1 second U-coordinate to the texture rectangle.
     * \param aV1 second V-coordinate to the texture rectangle.
     * \param aTransformationMatrix transformation matrix, or NULL if not needed.
     * \param aColor diffuse color.
     *
     * \note Transformations around center point.
     * \sa drawSprite2d2
     */
    XFCIMPORT INT32 drawSprite2d(REAL aCenterX, REAL aCenterY, REAL aZ,
                                 REAL aWidth, REAL aHeight,
                                 REAL aU0, REAL aV0, REAL aU1, REAL aV1,
                                 XFcMatrix4 *aTransformationMatrix,
                                 UINT32 aColor = 0xffffff);
    
    //! Draws a 2D sprite using screen coordinates.
    /*!
     * Draws the sprite with polygons, so you can make transformations like
     * Z-rotation on them. If you don't need any transformations, blitting a
     * surface directly to the secondary buffer may be faster.
     *
     * \param aX0 X-coordinate.
     * \param aY0 Y-coordinate.
     * \param aZ Z-coordinate.
     * \param aWidth width.
     * \param aHeight height.
     * \param aU0 first U-coordinate to the texture rectangle.
     * \param aV0 first V-coordinate to the texture rectangle.
     * \param aU1 second U-coordinate to the texture rectangle.
     * \param aV1 second V-coordinate to the texture rectangle.
     * \param aTransformationMatrix transformation matrix, or NULL if not needed.
     * \param aColor diffuse color.
     *
     * \note Transformations around center point.
     * \note Unlike drawSprite2d, this method uses top-left sprite coordinates.
     * \sa drawSprite2d
     */
    XFCIMPORT INT32 drawSprite2d2(REAL aX0, REAL aY0, REAL aZ,
                                  REAL aWidth, REAL aHeight,
                                  REAL aU0, REAL aV0, REAL aU1, REAL aV1,
                                  XFcMatrix4 *aTransformationMatrix,
                                  UINT32 aColor = 0xffffffff);
    
    //! Draws a 3D sprite using world coordinates.
    /*! 
     * Usually used with a transformation matrix to be really useful. To make a
     * nailboard sprite, for instance, you'll need to create a transformation
     * matrix that makes sure that the sprite rotates towards the camera around
     * it's Y axis only.
     *
     * \param aCenterX center X-coordinate.
     * \param aCenterY center Y-coordinate.
     * \param aCenterZ center Z-coordinate.
     * \param aWidth width.
     * \param aHeight height.
     * \param aU0 first U-coordinate to the texture rectangle.
     * \param aV0 first V-coordinate to the texture rectangle.
     * \param aU1 second U-coordinate to the texture rectangle.
     * \param aV1 second V-coordinate to the texture rectangle.
     * \param aTransformationMatrix transformation matrix, or NULL if not needed.
     * \param aColor diffuse color.
     */
    XFCIMPORT INT32 drawSprite3d(REAL aCenterX, REAL aCenterY, REAL aCenterZ,
                                 REAL aWidth, REAL aHeight, REAL aU0, REAL aV0,
                                 REAL aU1, REAL aV1,
                                 XFcMatrix4 *aTransformationMatrix,
                                 UINT32 aColor = 0xffffffff);
    
    //! Draws a 3D billboard sprite using world coordinates.
    /*!
     * Draws a billboard sprite (i.e. the sprite always faces the camera).
     * 
     * \param aCenterX center X-coordinate.
     * \param aCenterY center Y-coordinate.
     * \param aCenterZ center Z-coordinate.
     * \param aWidth width.
     * \param aHeight height.
     * \param aU0 first U-coordinate to the texture rectangle.
     * \param aV0 first V-coordinate to the texture rectangle.
     * \param aU1 second U-coordinate to the texture rectangle.
     * \param aV1 second V-coordinate to the texture rectangle.
     * \param aTransformationMatrix transformation matrix, or NULL if not needed.
     * \param aColor diffuse color.
     */
    XFCIMPORT INT32 drawSprite3dBillboard(REAL aCenterX, REAL aCenterY,
                                          REAL aCenterZ,
                                          REAL aWidth, REAL aHeight,
                                          REAL aU0, REAL aV0,
                                          REAL aU1, REAL aV1,
                                          XFcMatrix4 *aTransformationMatrix,
                                          UINT32 aColor = 0xffffffff);

    //! Returns a pointer to the secondary buffer.
    /*!
     * Accessing the secondary buffer directly may cause stalls in the
     * rendering pipeline, and in worst case the system may need to convert
     * the framebuffer to the desired format and back on calls to lock/unlock.
     * Blitting surfaces to the secondary should be fast, however.
     */
    XFCIMPORT XFcGLSurface * getSecondary();

    //! Sets render target. Set to NULL for the framebuffer.
    /*!
     * \param aSurface new render target, or NULL for the framebuffer.
     * \note Not supported in all rendering devices.
     */
    XFCIMPORT INT setRenderTarget(XFcGLSurface *aSurface);

    //! Returns pointer to the active palette. (Unused)
    XFCIMPORT INT32 getPalette(UINT8 **aPalette, UINT8 **aInvPalette);

    //! Sets the active palette. (Unused)
    XFCIMPORT INT32 setPalette(UINT8 *aPalette, UINT8 *aInvPalette);

    //! Clears the framebuffer.
    /*!
     * \param aColor Color used for filling the framebuffer in X8R8G8B8 format.
     * \param aZBuffer Z-value used for filling possible z-buffer.
     * \param aFlags Reserved.
     */
    XFCIMPORT INT32 clear(INT32 aColor = 0, REAL aZBuffer = REALf(0),
                          INT32 aFlags = 0);
    
protected:    
    void *mUnknown;
};


#endif // !XFC_CORE_XFCGL_H_INCLUDED

