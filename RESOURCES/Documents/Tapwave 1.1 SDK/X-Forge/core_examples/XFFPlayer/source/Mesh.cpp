/*! \file
* Mesh.cpp <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: Mesh.cpp,v 1.2 2003/09/04 12:26:31 toni Exp $
* $Date: 2003/09/04 12:26:31 $
* $Revision: 1.2 $
*/

#include <xforge.h>
#include <xfutil/XFuDynamicArray.h>
#include "Mesh.h"
#include "GameGraph.h"
#include "Buffers.h"
#include "Material.h"
#include "Texture.h"

Mesh * Mesh::create(GameGraph *aGameGraph, UINT32 aId)
{
    Mesh *g = new Mesh(aGameGraph, aId);
    if(g)
    {
        // Further initializations and memory allocations
        g->mType = NT_MESH;
        g->mChildren = XFuDynamicArray<Group *>::create();
        if(!g->mChildren)
        {
            delete g;
            g = NULL;
            return NULL;
        }
        g->mSubmeshes = XFuDynamicArray<Submesh *>::create();
        if(!g->mSubmeshes)
        {
            delete g;
            g = NULL;
            return NULL;
        }
    }
    return g;    
}

Mesh::Mesh(GameGraph *aGameGraph, UINT32 aId) : Group(aGameGraph, aId)
{
    mSubmeshes = NULL;
}

Mesh::~Mesh()
{
    if(mSubmeshes)
    {
        for(unsigned int i = 0; i < mSubmeshes->size(); i++)
        {
            delete mSubmeshes->get(i);
        }
        delete mSubmeshes;
        mSubmeshes = NULL;
    }
}

void Mesh::render()
{
    // Get the gl
    XFcGL *gl = mGameGraph->getGL();
    gl->setMatrix(XFCGLMAT_WORLD, mWorldTransformation);

    for(unsigned int i = 0; i < mSubmeshes->size(); i++)
    {
        Submesh *sm = mSubmeshes->get(i);
        Material *material = sm->mMaterial;
        // Apply the material settings
        gl->setStateI(XFCGLRS_SHADING, material->mShadingMode);
        gl->setStateI(XFCGLRS_ALPHABLEND, material->mAlphaBlend);
        gl->setStateI(XFCGLRS_SRCBLEND, material->mSourceBlend);
        gl->setStateI(XFCGLRS_TGTBLEND, material->mTargetBlend);
        gl->setStateI(XFCGLRS_PERSPECTIVECORRECTION, material->mPerspectiveCorrection);
        gl->setStateI(XFCGLRS_WIREFRAME, material->mWireframeMode);
        gl->setStateI(XFCGLRS_CULLING, material->mDoubleSided ? XFCGLCULL_NONE : XFCGLCULL_CW);
        gl->setStateF(XFCGLRS_POLYGONOFFSET, material->mPolygonOffset);
        
        if(sm->mTexture)
            gl->setTexture(sm->mTexture->getTex());
        else
            gl->setTexture(NULL);
        

        XFcGLVertexBuffer *vb = sm->mVertexBuffer ? sm->mVertexBuffer->getVB() : NULL;
        UINT16 *fl = sm->mFaceList ? sm->mFaceList->getIndices() : NULL;
        XFcGLTriangleInfoBuffer *tib = sm->mTriangleInfoBuffer ? sm->mTriangleInfoBuffer->getTIB() : NULL;

        // render the sub object
        if (sm->mFaceList)
        {
            gl->renderPrimitiveIndexed(vb, XFCGLPT_TRIANGLELIST, sm->mVertexOffset, fl, sm->mVertexCount, 0, vb->getNumVertices(), tib );
        }
        else
        {
            gl->renderPrimitive(vb, XFCGLPT_TRIANGLELIST, sm->mVertexOffset, sm->mVertexCount, 0, vb->getNumVertices(), tib);
        }
    }

    // Base class render
    Group::render();
}

void Mesh::initLoad()
{
    for(unsigned int i = 0; i < mSubmeshes->size(); i++)
        mSubmeshes->get(i)->initLoad(mGameGraph);

    // Base class initload
    Group::initLoad();
}

void Mesh::addSubmesh(Submesh *aSubmesh)
{
    mSubmeshes->put(aSubmesh);
}