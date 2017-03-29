/*! \file
* Mesh.cpp <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: Mesh.cpp,v 1.5 2003/07/07 11:53:46 lars Exp $
* $Date: 2003/07/07 11:53:46 $
* $Revision: 1.5 $
*/

#include <xforge.h>
#include <xfutil/XFuDynamicArray.h>
#include <xfcore/XFcMath.h>

#include "Node.h"
#include "Buffers.h"
#include "Mesh.h"
#include "Plane.h"


//! Static constructor.
Mesh * Mesh::create(Plane *aPlane, UINT32 aId)
{
    Mesh *g = new Mesh(aPlane, aId);
    if (g)
    {
        // Further initializations and memory allocations.
        g->mType = NT_MESH;

        g->mSubmeshes = XFuDynamicArray<Submesh *>::create();
        if (!g->mSubmeshes)
        {
            delete g;
            g = NULL;
        }
    }
    return g;    
}


Mesh::Mesh(Plane *aPlane, UINT32 aId) : Node(aPlane, aId)
{
    mSubmeshes = NULL;
}


Mesh::~Mesh()
{
    if (mSubmeshes)
    {
        UINT i;
        for (i = 0; i < mSubmeshes->size(); i++)
        {
            delete mSubmeshes->get(i);
        }
        delete mSubmeshes;
        mSubmeshes = NULL;
    }
}


//! Render all submeshes in this mesh...
void Mesh::render()
{
    // Get the GL.
    XFcGL *gl = mPlane->getGL();

    // Clockwise culling.
    gl->setStateI(XFCGLRS_CULLING, XFCGLCULL_CW);
    
    // Enable Gouraud shading.
    gl->setStateI(XFCGLRS_SHADING, XFCGLSHADE_GOURAUD); 

    // No textures.
    gl->setTexture(NULL);

    UINT i; 
    for (i = 0; i < mSubmeshes->size(); i++)
    {
        Submesh *sm = mSubmeshes->get(i);

        XFcGLVertexBuffer *vb = sm->mVertexBuffer ? sm->mVertexBuffer->getVB() : NULL;
        UINT16 *fl = sm->mFaceList ? sm->mFaceList->getIndices() : NULL;
        XFcGLTriangleInfoBuffer *tib = sm->mTriangleInfoBuffer ? sm->mTriangleInfoBuffer->getTIB() : NULL;

        // Render the sub object.
        if (sm->mFaceList)
        {
            gl->renderPrimitiveIndexed(vb, XFCGLPT_TRIANGLELIST, sm->mVertexOffset, 
                                       fl, sm->mVertexCount, 0, vb->getNumVertices(), tib);
        }
        else
        {
            gl->renderPrimitive(vb, XFCGLPT_TRIANGLELIST, sm->mVertexOffset, 
                                sm->mVertexCount, 0, vb->getNumVertices(), tib);
        }
    }

}


//! Initialize all submeshes.
void Mesh::initLoad()
{
    UINT i;
    for (i = 0; i < mSubmeshes->size(); i++)
    {
        Submesh *sm = mSubmeshes->get(i);
        sm->initLoad(mPlane);
    }
}


//! Add mesh to submesh list.
void Mesh::addSubmesh(Submesh *aSubmesh)
{
    mSubmeshes->put(aSubmesh);
}


//! Resolve node dependencies.
void Submesh::initLoad(Plane *aPlane)
{
    mVertexBuffer = (VertexBuffer *)aPlane->getNodeById(mVertexBufferId);
    mFaceList = (FaceList *)aPlane->getNodeById(mFaceListId);
    mTriangleInfoBuffer = (TriangleInfoBuffer *)aPlane->getNodeById(mTriangleInfoBufferId);
}
