/*! \file
 * ParticleSystem.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: ParticleSystem.h,v 1.2 2003/07/01 11:31:35 mikko Exp $
 * $Date: 2003/07/01 11:31:35 $
 * $Revision: 1.2 $
 */

#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include "Group.h"
class XFuParticleSystem;

//! Particle system class, basically just a wrapper over XFuParticleSystem
class ParticleSystem : public Group
{
public:
    //! Static constructor.
    static ParticleSystem * create(GameGraph *aGameGraph, UINT32 aId);
    
    //! Virtual destructor.
    virtual ~ParticleSystem();

    XFuParticleSystem *getPS() { return mParticleSystem; }
    void setPS(XFuParticleSystem *aPS) { mParticleSystem = aPS; }

    virtual void render();

protected:
    //! Protected constructor.
    ParticleSystem(GameGraph *aGameGraph, UINT32 aId);

    XFuParticleSystem *mParticleSystem;
};



#endif // !PARTICLESYSTEM_H_INCLUDED
