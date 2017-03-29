/*! \file
 * Mesh.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Mesh.h,v 1.3 2003/07/04 14:16:00 lars Exp $
 * $Date: 2003/07/04 14:16:00 $
 * $Revision: 1.3 $
 */

#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

class Node;
class VertexBuffer;
class FaceList;
class TriangleInfoBuffer;
class Material;
class Plane;


//! Submesh struct.
struct Submesh
{
    // Ids to content nodes.
    UINT32 mVertexBufferId;
    UINT32 mFaceListId;
    UINT32 mTriangleInfoBufferId;
    UINT32 mMaterialId;
    UINT32 mTextureId;

    // Resolved in initLoad()

    FaceList *mFaceList;
    VertexBuffer *mVertexBuffer;
    TriangleInfoBuffer *mTriangleInfoBuffer;

    UINT32 mVertexOffset;
    UINT32 mVertexCount;

    Submesh() : mVertexBufferId(0xffffffff), mFaceListId(0xffffffff),
                mTriangleInfoBufferId(0xffffffff), mMaterialId(0xffffffff),
                mTextureId(0xffffffff), mVertexBuffer(NULL), mFaceList(NULL),
                mTriangleInfoBuffer(NULL), mVertexOffset(0), mVertexCount(0)
    { }

    //! Resolve node dependencies.
    void initLoad(Plane *aPlane);
};


//! Mesh class.
class Mesh : public Node
{
public:
    //! Static constructor.
    static Mesh * create(Plane *aPlane, UINT32 aId);
    
    //! Virtual destructor.
    virtual ~Mesh();

    //! Render the mesh.
    virtual void render();
    
    //! Adds a submesh to this mesh, transfers ownership.
    void addSubmesh(Submesh *aSubmesh);

    //! Initialize all submeshes after loading completed.
    virtual void initLoad();

protected:
    //! Protected constructor.
    Mesh(Plane *aPlane, UINT32 aId);

    //! Array of submeshes.
    XFuDynamicArray<Submesh *> *mSubmeshes;
};

#endif // !MESH_H_INCLUDED