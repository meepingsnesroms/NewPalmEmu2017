/*! \file
 * Buffers.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Buffers.h,v 1.2 2003/07/02 06:54:38 lars Exp $
 * $Date: 2003/07/02 06:54:38 $
 * $Revision: 1.2 $
 */

#ifndef BUFFERS_H_INCLUDED
#define BUFFERS_H_INCLUDED

class Plane;
class XFcGLVertexBuffer;


// Different buffers for geometry data


//! Vertex buffer class, just a node wrapper for XFcGLVertexBuffer.
class VertexBuffer : public Node
{
public:
    //! Constructor.
    VertexBuffer(Plane *aPlane, UINT32 aId) : Node(aPlane, aId), mVB(NULL)
    {
        mType = NT_VERTEXBUFFER;
    }
    
    //! Virtual destructor.
    virtual ~VertexBuffer()
    {
        delete mVB;
        mVB = NULL;
    }
    
    //! Get pointer to XFcGLVertexBuffer.
    XFcGLVertexBuffer *getVB() { return mVB; }

    //! Set pointer to XFcGLVertexBuffer.
    void setVB(XFcGLVertexBuffer *aVB) { mVB = aVB; }
    
protected:
    XFcGLVertexBuffer *mVB;
};


//! Face list class, just a buffer actually.
class FaceList : public Node
{
public:
    //! Constructor.
    FaceList(Plane *aPlane, UINT32 aId) : Node(aPlane, aId), mIndices(NULL), mCount(0)
    {
        mType = NT_FACELIST;
    }
    
    //! Virtual destructor.
    virtual ~FaceList()
    {
        delete mIndices;
        mIndices = NULL;
    }
    
    //! Sets indices, transfers ownership.
    void setIndices(UINT16 *aIndices, UINT32 aCount) { mIndices = aIndices; mCount = aCount; };

    //! Get number of indices.
    UINT32 getIndexCount() { return mCount; }

    //! Get pointer to index array.    
    UINT16 *getIndices() { return mIndices; }

protected:
    UINT16 *mIndices;
    UINT32 mCount;  
};


//! TriangleInfo buffer class, just a node wrapper for XFcGLTriangleInfoBuffer.
class TriangleInfoBuffer : public Node
{
public:
    //! Constructor.
    TriangleInfoBuffer(Plane *aPlane, UINT32 aId) : Node(aPlane, aId), mTIB(NULL)
    {
        mType = NT_TRIANGLEINFOBUFFER;
    }
    
    //! Virtual destructor.
    virtual ~TriangleInfoBuffer()
    {
        delete mTIB;
        mTIB = NULL;
    }
    
    XFcGLTriangleInfoBuffer *getTIB() { return mTIB; }
    void setTIB(XFcGLTriangleInfoBuffer *aTIB) { mTIB = aTIB; }
    
protected:
    XFcGLTriangleInfoBuffer *mTIB;
};

#endif // !BUFFERS_H_INCLUDED

