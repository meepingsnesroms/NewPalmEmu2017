/*! \file
* ParticleSystem.cpp <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: ParticleSystem.cpp,v 1.3 2003/09/04 12:26:31 toni Exp $
* $Date: 2003/09/04 12:26:31 $
* $Revision: 1.3 $
*/

#include <xforge.h>
#include <xfutil/XFuParticleSystem.h>
#include <xfutil/XFuDynamicArray.h>
#include "ParticleSystem.h"

ParticleSystem *ParticleSystem::create(GameGraph *aGameGraph, UINT32 aId)
{
    ParticleSystem *g = new ParticleSystem(aGameGraph, aId);
    if(g)
    {
        // Further initializations and memory allocations
        g->mType = NT_PARTICLESYSTEM;
        g->mChildren = XFuDynamicArray<Group *>::create();
        if(!g->mChildren)
        {
            delete g;
            g = NULL;
            return NULL;
        }
    }
    return g;    
}

ParticleSystem::ParticleSystem(GameGraph *aGameGraph, UINT32 aId) : Group(aGameGraph, aId), mParticleSystem(NULL)
{
}

ParticleSystem::~ParticleSystem()
{
    delete mParticleSystem;
    mParticleSystem = NULL;
}

void ParticleSystem::render()
{
    XFcGL *gl = mGameGraph->getGL();
    gl->setMatrix(XFCGLMAT_WORLD, mWorldTransformation);
    
    // set z-offset
    REAL oldZOffset;
    gl->getStateF(XFCGLRS_POLYGONOFFSET, oldZOffset);
    gl->setStateF(XFCGLRS_POLYGONOFFSET, REALf(0));
    
    // force clipping on
    INT oldClippingState;
    gl->getStateI(XFCGLRS_CLIPPING, oldClippingState);
    gl->setStateI(XFCGLRS_CLIPPING, 1);
    
    // save shading mode
    INT32 savedShadingMode;
    gl->getStateI(XFCGLRS_SHADING, savedShadingMode);
    
    // force matte
    gl->setStateI(XFCGLRS_SHADING, XFCGLSHADE_MATTE);
    
    mParticleSystem->mViewScale = REALi(1);
    mParticleSystem->tick(mGameGraph->getTick());
    mParticleSystem->render(gl);
    
    gl->setTexture(NULL);
    
    // restore clipping state
    gl->setStateI(XFCGLRS_CLIPPING, oldClippingState);
    
    // restore z-offset
    gl->setStateF(XFCGLRS_POLYGONOFFSET, oldZOffset);
    
    // restore shading mode
    gl->setStateI(XFCGLRS_SHADING, savedShadingMode);
    
}