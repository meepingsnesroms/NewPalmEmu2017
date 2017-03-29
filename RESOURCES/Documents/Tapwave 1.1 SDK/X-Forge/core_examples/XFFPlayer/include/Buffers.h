/*! \file
 * Buffers.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Buffers.h,v 1.1 2003/05/20 11:40:46 mikko Exp $
 * $Date: 2003/05/20 11:40:46 $
 * $Revision: 1.1 $
 */

#ifndef BUFFERS_H_INCLUDED
#define BUFFERS_H_INCLUDED

class GameGraph;
class XFcGLVertexBuffer;

#include "Node.h"

// Different buffers for geometry data

//! Vertex buffer class, just a node wrapper for XFcGLVertexBuffer
class VertexBuffer : public Node
{
public:
    //! Constructor.
    VertexBuffer(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId), mVB(NULL)
    {
        mType = NT_VERTEXBUFFER;
    }
    
    //! Virtual destructor.
    virtual ~VertexBuffer()
    {
        delete mVB;
        mVB = NULL;
    }
    
    XFcGLVertexBuffer *getVB() { return mVB; }
    void setVB(XFcGLVertexBuffer *aVB) { mVB = aVB; }
    
protected:
    XFcGLVertexBuffer *mVB;
    
};

//! Face list class, just a buffer actually
class FaceList : public Node
{
public:
    //! Constructor.
    FaceList(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId), mIndices(NULL), mCount(0)
    {
        mType = NT_FACELIST;
    }
    
    //! Virtual destructor.
    virtual ~FaceList()
    {
        delete mIndices;
        mIndices = NULL;
    }
    
    // Sets indices, transfers ownership
    void setIndices(UINT16 *aIndices, UINT32 aCount) { mIndices = aIndices; mCount = aCount; };
    UINT32 getIndexCount() { return mCount; }
    UINT16 *getIndices() { return mIndices; }

protected:
    UINT16 *mIndices;
    UINT32 mCount;  
};

//! TriangleInfo buffer class, just a node wrapper for XFcGLTriangleInfoBuffer
class TriangleInfoBuffer : public Node
{
public:
    //! Constructor.
    TriangleInfoBuffer(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId), mTIB(NULL)
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

