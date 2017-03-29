/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XFcGL enumerations.
 * 
 * $Id: XFcGLEnums.h,v 1.23 2003/08/14 09:12:56 jouni Exp $
 * $Date: 2003/08/14 09:12:56 $
 * $Revision: 1.23 $
 */

#ifndef XFC_CORE_XFCGLENUMS_H_INCLUDED
#define XFC_CORE_XFCGLENUMS_H_INCLUDED


//! XFcGL error codes.
enum XFCGLERRORS
{
    XFCGLERR_OK = 0,             //!< No error.
    XFCGLERR_FAILED = -1,        //!< General failure.
    XFCGLERR_UNSUPPORTED = -2,   //!< Unsupported function.
    XFCGLERR_BADPARAMS = -3,     //!< Bad parameters or bad combination of them.
    XFCGLERR_OUTOFMEMORY = -4,   //!< Out of memory error.
    XFCGLERR_INVALIDBUFFER = -5, //!< Invalid buffer.
    XFCGLERR_INTERNALERROR = -6, //!< Internal error.
    XFCGLERR_NOTREADY = -7       //!< Hardware was not ready.
};


//! XFcGL light types.
enum XFCGLLIGHTTYPES
{
    XFCGLL_POINTLIGHT = 1,      //!< Point-, or omni light.
    XFCGLL_DIRECTIONAL,         //!< Directional light.
    XFCGLL_SPOT                 //!< Spotlight. Not supported currently.
};


//! XFcGL vertex buffer vertex type flags.
enum XFCGLVERTEXFLAGS
{
    //! Vertex x, y, z info; always available (3x REAL).
    XFCGLVF_XYZ = 1,
    //! Contains rhw component (1x REAL).
    /*! \note also means that xyz values are in screen space.
     */
    XFCGLVF_RHW = 2,
    //! Contains nx, ny, nz normal info (3x REAL).
    XFCGLVF_NORMAL = 4,
    //! Contains diffuse color component (1x UINT32).
    XFCGLVF_DIFFUSECOLOR = 8,
    //! Contains specular color component (ignored) (1x UINT32).
    XFCGLVF_SPECULARCOLOR = 16,
    //! Contains texture UV coordinates (2x REAL).
    XFCGLVF_TEXTURE1 = 32,
    //! Contains texture UV coordinates (2x REAL) (for multitexturing).
    XFCGLVF_TEXTURE2 = 64,
    //! Contains texture UV coordinates (2x REAL) (for multitexturing).
    XFCGLVF_TEXTURE3 = 128,
    //! Contains texture UV coordinates (2x REAL) (for multitexturing).
    XFCGLVF_TEXTURE4 = 256,
    //! Contains clipping information (.x UINT32; 6b needed, 26b padding).
    XFCGLVF_CLIPINFO = 512,
    //! Contains transform information.
    XFCGLVF_TRANSFORMINFO = 1024,
    //! Internal.
    XFCGLVF_LOCKED = 65536
};


//! XFcGL vertex buffer locking modes.
enum XFCGLVBLOCKFLAGS
{
    XFCGLVBLOCK_READ = 1,        //!< Lock an array for read only access.
    XFCGLVBLOCK_MODIFY = 2       //!< Lock an array for modification.
};


//! XFcGL internal: vertex clipping and transformation state flags.
enum XFCGLVERTEXTRANSFORMFLAGS
{
    XFCGLVTF_TRANSFORMED = 1,    //!< Transformation information.
    XFCGLVTF_PROJECTED = 2,      //!< Projection information.
    XFCGLVTF_CLIPNEAR = 4,       //!< Needs near clipping.
    XFCGLVTF_CLIPFAR = 8,        //!< Needs far clipping.
    XFCGLVTF_CLIPTOP = 16,       //!< Needs top clipping.
    XFCGLVTF_CLIPBOTTOM = 32,    //!< Needs bottom clipping.
    XFCGLVTF_CLIPLEFT = 64,      //!< Needs left clipping.
    XFCGLVTF_CLIPRIGHT = 128     //!< Needs right clipping.
};


//! XFcGL primitive types.
/*! <pre>
 *  Triangle list.
 *  Every 3 vertices make a new triangle:
 *
 *  1.        4.     
 *  |  .      |  .   
 *  |    .    |    . 
 *  2-----3   5-----6
 *
 *
 *  Triangle strip.
 *  Every vertex after the 2 initial ones create a new triangle:
 *
 *  2.----4.    6 
 *  |  .  |  .    
 *  |    .|    .  
 *  1-----3-----5 
 *
 *
 *  Triangle fan.
 *  Same as above, except that first vertex is used in every triangle:
 *
 *  3.----4----.5 
 *  |  .  |  .    
 *  |    .|.      
 *  2-----1     6 
 *  </pre>
 */
enum XFCGLPRIMITIVETYPES
{
    //! 3 vertices = 1 triangle.
    XFCGLPT_TRIANGLELIST = 1,
    //! 3 vertices = first triangle, every following vertex = new triangle.
    XFCGLPT_TRIANGLESTRIP,
    //! 3 vertices = first triangle, every following vertex = new triangle.
    XFCGLPT_TRIANGLEFAN,
    //! 1 vertex = 1 custom primitive.
    XFCGLPT_CUSTOM
};


//! XFcGL matrix id's.
enum XFCGLMATRIXID
{
    XFCGLMAT_WORLD = 1,      //!< Object -> world space.
    XFCGLMAT_VIEW = 2,       //!< World -> camera space.
    XFCGLMAT_PROJECTION = 3  //!< Camera -> projection space.
};


//! XFcGL render states - used in setrenderstate.
/*! 
 * \sa XFcGL
 */
enum XFCGLRENDERSTATES
{
    //! Perform clipping. Values 0 and 1. Defaults to 1.
    XFCGLRS_CLIPPING,
    //! Perform lighting. Values 0 and 1. Defaults to 0.
    XFCGLRS_LIGHTING,
    //! Shading mode; see XFCGLSHADINGMODES. Defaults to XFCGLSHADE_FLAT.
    /*!
     * \sa XFCGLSHADINGMODES
     */
    XFCGLRS_SHADING, 
    //! Culling mode; see XFCGLCULLINGMODES. Defaults to XFCGLCULL_CW.
    /*!
     * \sa XFCGLCULLINGMODES
     */
    XFCGLRS_CULLING,
    //! Alpha blending. Values 0 and 1. Defaults to 0.
    XFCGLRS_ALPHABLEND,
    //! Source blend. Only certain combinations of src/tgtblend are valid. Defaults to XFCBLEND_ONE. 
    /*!
     * \sa XFCGLBLENDMODES
     * \sa XFCGLLEGALBLENDMODES
     */
    XFCGLRS_SRCBLEND, 
    //! Target blend. Only certain combinations of src/tgtblend are valid. Defaults to XFCBLEND_ZERO.
    /*! 
     * \sa XFCGLBLENDMODES
     * \sa XFCGLLEGALBLENDMODES
     */
    XFCGLRS_TGTBLEND,
    //! Sorting mode. See XFCGLSORTINGMODES. Defaults to XFCGLSORT_DESCENDING.
    /*!
     * \sa XFCGLSORTINGMODES
     */
    XFCGLRS_SORTING,
    //! Perspective correction. Values 0 and 1. Defaults to 0.
    XFCGLRS_PERSPECTIVECORRECTION,
    //! Orthogonal projection. Values 0 and 1. Defaults to 0.
    XFCGLRS_ORTHOGONALPROJECTION,
    //! Wireframe mode. Values 0 and 1. Mainly meant for debugging. Defaults to 0.
    XFCGLRS_WIREFRAME,
    //! Takes 0RGB dword color. Defaults to 0.
    XFCGLRS_AMBIENTLIGHT,
    //! Polygon offset, a REAL. Only affects sorting. Defaults to 0.
    /*!
     * Typically used to fight sorting problems.
     */
    XFCGLRS_POLYGONOFFSET,
    //! Depth testing. Only supported by devices that list it in their capabilities.
    /*!
     * Legal values 0 and 1. Defaults to 0. Default rasterizer has no depth buffering.
     */
    XFCGLRS_DEPTHTEST,
    //! Depth testing function. See XFCGLDEPTHFUNCMODES. Defaults to LESSEQUAL.
    XFCGLRS_DEPTHFUNC,
    //! Decides whether z-buffer should be written to or not. Defaults to 1.
    /*!
     * Legal values 0 and 1. If depth testing is on but depth writing is off,
     * everything happens as usual, except that the z-buffer is not updated.
     */
    XFCGLRS_DEPTHWRITE,
    XFCGLRS_PERSPECTIVEDISABLEDISTANCE
};


//! XFcGL depth buffer depth function modes.
enum XFCGLDEPTHFUNCMODES
{
    XFCGLDF_LESSEQUAL,
    XFCGLDF_LESS,
    XFCGLDF_NEVER,
    XFCGLDF_NOTEQUAL,
    XFCGLDF_EQUAL,
    XFCGLDF_GREATEREQUAL,
    XFCGLDF_GREATER,
    XFCGLDF_ALWAYS
};


//! XFcGL sorting modes.
/*! Unlike hardware-based rendering architectures, we must support sorting, as our 
 *  primary target in the near future is pure software rendering, using painter's 
 *  algorithm.
 */
enum XFCGLSORTINGMODES
{
    //! No sorting; default.
    XFCGLSORT_NONE = 1,
    //! Sort in descending order.
    XFCGLSORT_DESCENDING = 8,
    //! Sort in ascending (reverse) order.
    XFCGLSORT_ASCENDING = 16
};


//! XFcGL shading modes.
enum XFCGLSHADINGMODES
{
    //! No shading.
    /*! Meaningful for textured surfaces only; non-textured are flat.
     */
    XFCGLSHADE_MATTE = 1,
    //! Flat shading; color taken from the first vertex of the triangle.
    XFCGLSHADE_FLAT = 2,
    //! Gouraud shading.
    XFCGLSHADE_GOURAUD = 4,
    //! Greyscale gouraud shading.
    XFCGLSHADE_GREYSCALE_GOURAUD = 8
};


//! XFcGL culling modes. You can pick cw/ccw, or use NONE.
enum XFCGLCULLINGMODES
{
    //! Cull clockwise triangles. Default.
    XFCGLCULL_CW = 4,
    //! Cull counterclockwise triangles. 
    XFCGLCULL_CCW = 8,
    //! Do not perform culling.
    XFCGLCULL_NONE = 16
};


//! XFcGL blending modes. 
/*!
 * Each blend must be set for source and destination blends. For instance:
 * \par
 * src=XFCBLEND_ONE and dst=XFCBLEND_ONE cause this to happen:
 * \code
 * A = sA * 1 + dA * 1
 * R = sR * 1 + dR * 1
 * G = sG * 1 + dG * 1
 * B = sB * 1 + dB * 1
 * \endcode
 * (i.e. additive blend)
 * \par
 * For more interesting effects such as cross fading alpha you might use:
 * \par
 * src=XFCBLEND_SRCALPHA and dst=XFCBLEND_INVSRCALPHA
 * \code
 * A = sA * sA + dA * (1-sA)
 * R = sR * sA + dR * (1-sA)
 * G = sG * sA + dG * (1-sA)
 * B = sB * sA + dB * (1-sA)
 * \endcode
 * \sa XFCGLLEGALBLENDMODES
 */
enum XFCGLBLENDMODES
{
    //! Blend as zero (0 0 0 0).
    XFCBLEND_ZERO = 1,
    //! Blend as one (1 1 1 1).
    XFCBLEND_ONE,
    //! Blend as source color (sA sR sG sB).
    XFCBLEND_SRCCOLOR,
    //! Blend as inverse source color (1-sA 1-sR 1-sG 1-sB).
    XFCBLEND_INVSRCCOLOR,
    //! Blend as source alpha (sA sA sA sA).
    XFCBLEND_SRCALPHA,
    //! Blend as inverse source alpha (1-sA 1-sA 1-sA 1-sA).
    XFCBLEND_INVSRCALPHA,
    //! Blend as destination alpha (dA dA dA dA).
    XFCBLEND_DESTALPHA,
    //! Blend as inverse destination alpha (1-dA 1-dA 1-dA 1-dA).
    XFCBLEND_INVDESTALPHA,
    //! Blend as destination color (dA dR dG dB).
    XFCBLEND_DESTCOLOR,
    //! Blend as inverse destination color (1-dA 1-dR 1-dG 1-dB).
    XFCBLEND_INVDESTCOLOR
};


//! XFcGL internally legal blend modes.
enum XFCGLLEGALBLENDMODES
{
    XFCGLBLEND_NONE,         //!< src = ONE,      tgt = ZERO
    XFCGLBLEND_ALPHA,        //!< src = SRCALPHA, tgt = INVSRCALPHA
    XFCGLBLEND_MUL,          //!< src = ZERO,     tgt = SRCCOLOR (NOT IMPLEMENTED)
    XFCGLBLEND_ADD,          //!< src = ONE,      tgt = ONE
    XFCGLBLEND_INVMUL,       //!< src = ZERO,     tgt = INVSRCCOLOR
    XFCGLBLEND_ILLEGAL       //!< Illegal blend mode specified.
};


//! XFcGL flags for creation and recreation.
enum XFCGLCREATEENUMS
{
    XFCGLC_DEFAULT = 0,         //!< Create preferred device (best speed-wise).
    XFCGLC_REFERENCE = 1,       //!< Create reference device (software rendering).
    XFCGLC_PORTRAIT = 0x01000000,     //!< Create device in portrait mode.
    XFCGLC_LANDSCAPE = 0x02000000,    //!< Create device in landscape mode.
    XFCGLC_ROTATE_0 = 0x04000000,     //!< Create device in 0 degree rotated mode.
    XFCGLC_ROTATE_180 = 0x08000000,   //!< Create device in 180 degree rotated mode.
    XFCGLC_NO_CONTROL_ROTATE = 0x10000000, //!< Don't rotate control events.
    XFCGLC_NO_POINTER_ROTATE = 0x20000000  //!< Don't rotate pointer events.
};


//! XFcGL surface flags.
enum XFCGLSURFACEFLAGS
{
    XFCGLSF_FRAMEBUFFER = 1, //!< Internal: surface is a framebuffer surface.
    XFCGLSF_VIDMEM = 2,      //!< Internal: surface is not in system memory.
    XFCGLSF_CANTLOCK = 4     //!< Internal: surface cannot be locked for direct access.
};


#endif // !XFC_CORE_XFCGLENUMS_H_INCLUDED

