/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XFcGL vertex buffer class
 * 
 * $Id: XFcGLVertexBuffer.h,v 1.12 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.12 $
 */

#ifndef XFC_CORE_XFCGLVERTEXBUFFER_H_INCLUDED
#define XFC_CORE_XFCGLVERTEXBUFFER_H_INCLUDED


#include <xfcore/XFcGL.h>
#include <xfcore/XFcGLEnums.h>


class XFcVBProcVertice;

//! Vertex buffer.
/*!
 * This is a wrapper for an array of vertices. The vertex format itself is
 * flexible - see XFcGLVertex, XFcGLLVertex and XFcGLTLVertex as examples of legal
 * vertex formats.
 * \sa XFcGLVertex
 * \sa XFcGLLVertex
 * \sa XFcGLTLVertex
 */
class XFCDLLEXPORT XFcGLVertexBuffer
{
    //! XFcGLCore needs access to offsets (and is the only class that needs it).
    friend class XFcGLCore;

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcGLVertexBuffer();

    //! Creates a XFcGLVertexBuffer object.
    /*!
     * \param aVertexFlags vertex flags, see XFCGLVERTEXFLAGS.
     * \param aSizeOfVertex size of one vertex structure, in bytes.
     * \param aNumberOfVertices number of vertices to allocate.
     * \return new vertex buffer, or NULL if unsuccessful.
     * \sa XFcGLVertex, XFcGLLVertex, XFcGLTLVertex
     */
    XFCIMPORT static XFcGLVertexBuffer * create(
        INT32 aVertexFlags, INT32 aSizeOfVertex, INT32 aNumberOfVertices);

    //! Returns creation flags.
    XFCIMPORT INT32 getFlags();
    //! Returns how many bytes each vertex takes in the buffer.
    XFCIMPORT INT32 getVertexStride();
    //! Returns the vertex count.
    XFCIMPORT INT32 getNumVertices();

    //! Locks vertex buffer.
    /*!
     * \param aLockFlags vertex buffer locking flags, see XFCGLVBLOCKFLAGS.
     * \return pointer to the vertex buffer data, or NULL if buffer cannot be locked.
     * \sa XFCGLVBLOCKFLAGS
     * \sa optimize
     */
    XFCIMPORT void * lock(INT32 aLockFlags);

    //! Unlocks the vertex buffer. Buffer must be unlocked in order to be used.
    XFCIMPORT INT32 unlock();

    //! Optimizes a vertex buffer. 
    /*! 
     * \note After optimization the vertex buffer can not be locked.
     */
    XFCIMPORT INT32 optimize();

protected:

    //! Protected constructor.
    XFcGLVertexBuffer();

    //! Initializes all variables to default values.
    void initVariables();

    //! Initializes all offsets.
    /*! \param aVertexFlags vertex buffer flags, see XFCGLVERTEXFLAGS.
     */
    INT32 initOffsets(INT32 aVertexFlags);

    //! Returns non-zero if the vertex buffer is valid.
    INT isValid();

    //! Returns flags suitable for processed vertices on buffer with given flags.
    INT32 createProcessedBufferFlags(INT32 aSrcVertexFlags);

    //! Vertex flags (from construction).
    INT32 mVertexFlags;
    //! Size of one vertex.
    INT32 mVertexStride;
    //! Number of vertices in buffer.
    INT32 mNumberOfVertices;
    //! Pointer to vertex data.
    void *mVertexData;
    //! Matrix state/lock counter that was used to calculate the following.
    INT32 mStateCount;

    // Pointer to processed vertices used to minimize recalculation
    //XFcVBProcVertice *mProcessedVertices;

    //! \internal Vertex positions.
    XFcVector3 *mPosition;
    //! \internal Diffuse colors.
    UINT32 *mDiffuseColor;
    //! \internal Texture coordinates.
    REAL *mUV;
    //! \internal Normals.
    XFcVector3 *mNormal;

    //! Non-zero if this vertex buffer is optimized.
    INT mIsOptimized;


    // Extra component offsets in a vertex:
    
    INT mRHWOffs;               //!< Offset to RHW component, or 0 if not supported by format.
    INT mNormalOffs;            //!< Offset to the normal, or 0 if not supported by format.
    INT mDiffuseColorOffs;      //!< Offset to the diffuse color, or 0 if not supported by format.
    INT mSpecularColorOffs;     //!< Offset to the specular color, or 0 if not supported by format.
    INT mTexture1Offs;          //!< Offset to texture 1 coordinates, or 0 if not supported by format.
    INT mTexture2Offs;          //!< Offset to texture 2 coordinates, or 0 if not supported by format.
    INT mTexture3Offs;          //!< Offset to texture 3 coordinates, or 0 if not supported by format.
    INT mTexture4Offs;          //!< Offset to texture 4 coordinates, or 0 if not supported by format.
    INT mClipInfoOffs;          //!< Offset to clip info, or 0 if not supported by format.
};


#endif // !XFC_CORE_XFCGLVERTEXBUFFER_H_INCLUDED

