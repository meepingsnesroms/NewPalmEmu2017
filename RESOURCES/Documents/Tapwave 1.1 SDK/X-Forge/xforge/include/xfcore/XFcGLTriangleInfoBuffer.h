/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XFcGL triangle info buffer class
 * 
 * $Id: XFcGLTriangleInfoBuffer.h,v 1.12 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.12 $
 */

#ifndef XFC_CORE_XFCGLTRIANGLEINFOBUFFER_H_INCLUDED
#define XFC_CORE_XFCGLTRIANGLEINFOBUFFER_H_INCLUDED

#include <xfcore/XFcVector.h>


//! Flags describing the contents of a triangle info buffer.
enum XFCGLTRIANGLEFLAGS
{
    //! Contains diffuse color component (1*UINT32).
    XFCGLTR_DIFFUSECOLOR = 1,
    //! Contains normal (3*REAL: x,y,z).
    XFCGLTR_NORMAL = 2,
    //! Contains texture coordinates (2*3*REAL: U0,U1,U2,V0,V1,V2).
    XFCGLTR_TEXTURE1 = 4,
    //! Contains texture coordinates (2*3*REAL: U0,U1,U2,V0,V1,V2).
    XFCGLTR_TEXTURE2 = 8,
    //! Contains texture coordinates (2*3*REAL: U0,U1,U2,V0,V1,V2).
    XFCGLTR_TEXTURE3 = 16,
    //! Contains texture coordinates (2*3*REAL: U0,U1,U2,V0,V1,V2).
    XFCGLTR_TEXTURE4 = 32
};


//! Triangle info buffer object.
/*!
 * Triangle info buffers are used to optimize meshes so that duplicate vertices
 * are not needed where, for example, each triangle has its own texture coordinates.
 * \code
 * // An example of legal triangleinfo data:
 * #define XFCGLTRIANGLEINFO (XFCGLTR_DIFFUSECOLOR | XFCGLTR_NORMAL | XFCGLTR_TEXTURE1)
 * 
 * // The data in the buffer must be in a specific order:
 * // - Diffuse color
 * // - Normal vector
 * // - Texture coordinates
 * 
 * class XFcGLTriangleInfo
 * {
 * public:
 *     UINT32 mDiffuseColor;
 *     REAL mNX, mNY, mNZ;
 *     REAL mU[3], mV[3];
 * };
 * \endcode
 * \sa XFcGLTriangleInfo
 */
class XFCDLLEXPORT XFcGLTriangleInfoBuffer
{
    //! XFcGLCore needs access to offsets (and is the only class that needs it).
    friend class XFcGLCore;

public:
    
    //! Creates an XFcGLTriangleInfoBuffer.
    /*!
     * \param aTriangleFlags flags describing the triangle info buffer, see XFCGLTRIANGLEFLAGS.
     * \param aSizeOfTriangle size of one triangle information in bytes.
     * \param aNumberOfTriangles number of triangles in the buffer.
     * \return new triangle info buffer object, or NULL if unsuccessful.
     * \sa XFCGLTRIANGLEFLAGS
     */
    XFCIMPORT static XFcGLTriangleInfoBuffer * create(UINT32 aTriangleFlags,
                                                      INT aSizeOfTriangle,
                                                      INT aNumberOfTriangles);

    //! Destructor.
    XFCIMPORT ~XFcGLTriangleInfoBuffer();

    //! Locks the triangle info buffer.
    /*! \return pointer to the triangle info data.
     */
    XFCIMPORT void * lock();

    //! Unlocks the triangle info buffer.
    XFCIMPORT void unlock();

    //! Size of one triangle info unit in bytes.
    INT mInfoSize;
    //! Number of triangles specified (from construction).
    INT mNumTriangles;
    //! Flags (from construction).    
    UINT32 mInfoFlags;
    //! Diffuse color offset (-1 if not specified).
    INT mDiffuseColorOffs;
    //! Normal offset (-1 if not specified).
    INT mNormalOffs;
    //! Texture1 cordinate offset (-1 if not specified).
    INT mTexture1Offs;

protected:

    //! The actual data.
    UINT8 *mTriangleInfoData;

    //! Calculates the offsets into the data buffer.
    void initOffsets(UINT32 aTriangleFlags);

};


// An example of legal triangleinfo data:
#define XFCGLTRIANGLEINFO (XFCGLTR_DIFFUSECOLOR | XFCGLTR_NORMAL | XFCGLTR_TEXTURE1)

// The data in the buffer must be in a specific order:
// - Diffuse color
// - Normal vector
// - Texture coordinates

//! Example of a legal triangle info data.
/*! Format matches to flags specified in XFCGLTRIANGLEINFO.
 * \sa XFCGLTRIANGLEINFO
 */
class XFcGLTriangleInfo
{
public:
    UINT32 mDiffuseColor[3];    //!< Diffuse color.
    REAL mNX;                   //!< X-component of normal vector.
    REAL mNY;                   //!< X-component of normal vector.
    REAL mNZ;                   //!< X-component of normal vector.
    REAL mU[3];                 //!< U-components of the texture coordinates.
    REAL mV[3];                 //!< V-components of the texture coordinates.
};


#endif // !XFC_CORE_XFCGLTRIANGLEINFOBUFFER_H_INCLUDED

