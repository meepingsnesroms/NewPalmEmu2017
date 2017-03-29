/*! \file
 * Mesh.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Mesh.h,v 1.3 2003/07/07 09:43:23 jari Exp $
 * $Date: 2003/07/07 09:43:23 $
 * $Revision: 1.3 $
 */
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Group.h"

class VertexBuffer;
class FaceList;
class TriangleInfoBuffer;
class Material;
class Texture;

//! Submesh struct
struct Submesh
{
    // Ids to content
    UINT32 mVertexBufferId;
    UINT32 mFaceListId;
    UINT32 mTriangleInfoBufferId;
    UINT32 mMaterialId;
    UINT32 mTextureId;

    // Resolved in initload()
    VertexBuffer * mVertexBuffer;
    FaceList * mFaceList;
    TriangleInfoBuffer * mTriangleInfoBuffer;
    Material * mMaterial;
    Texture * mTexture;

    UINT32 mVertexOffset;
    UINT32 mVertexCount;

    Submesh() : mVertexBufferId(0xffffffff), mFaceListId(0xffffffff),
                         mTriangleInfoBufferId(0xffffffff), mMaterialId(0xffffffff),
                         mTextureId(0xffffffff), mVertexBuffer(NULL), mFaceList(NULL),
                         mTriangleInfoBuffer(NULL), mMaterial(NULL), mTexture(NULL), mVertexOffset(0), mVertexCount(0)
    { }

    // resolve
    void initLoad(GameGraph *aGameGraph)
    {
        mVertexBuffer = (VertexBuffer *)aGameGraph->getNodeById(mVertexBufferId);
        mFaceList = (FaceList *)aGameGraph->getNodeById(mFaceListId);
        mTriangleInfoBuffer = (TriangleInfoBuffer *)aGameGraph->getNodeById(mTriangleInfoBufferId);
        mMaterial = (Material *)aGameGraph->getNodeById(mMaterialId);
        mTexture = (Texture *)aGameGraph->getNodeById(mTextureId);
    }
};


//! Mesh class
class Mesh : public Group
{
public:
    //! Static constructor.
    static Mesh * create(GameGraph *aGameGraph, UINT32 aId);
    
    //! Virtual destructor.
    virtual ~Mesh();

    //! Render the mesh and all it's children
    virtual void render();
    
    //! Adds a submesh to this mesh, transfers ownership.
    void addSubmesh(Submesh *aSubmesh);

    //! from Node::initLoad()
    virtual void initLoad();

protected:
    //! Protected constructor.
    Mesh(GameGraph *aGameGraph, UINT32 aId);

    XFuDynamicArray<Submesh *> *mSubmeshes;
    
};


#endif