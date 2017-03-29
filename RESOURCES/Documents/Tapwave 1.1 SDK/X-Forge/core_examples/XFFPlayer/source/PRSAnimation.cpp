/*! \file
 * PRSAnimation.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: PRSAnimation.cpp,v 1.4 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.4 $
 */

#include <xforge.h>
#include <xfutil/XFuDynamicArray.h>
#include "PRSAnimation.h"

PRSAnimation * PRSAnimation::create()
{
    PRSAnimation *p = new PRSAnimation();
    if(p)
    {
        p->mData = XFuDynamicArray<PRS>::create();
        if(!p->mData)
        {
            delete p;
            p = NULL;
        }
    }
    return p;
}

PRSAnimation::PRSAnimation() : mNextFrame(NULL), mData(NULL)
{ }

PRSAnimation::~PRSAnimation()
{
    delete mData;
}

void PRSAnimation::addFrame(PRS &aPRS)
{
    mData->put(aPRS);
}

void PRSAnimation::getNextFrame(XFcMatrix4 &aDest)
{
    // Just shove the next sample down the pipe
    
    PRS p = mData->get(mNextFrame);

    XFcMatrix4 rotation;
    XFcMath::matrixFromQuaternion(rotation, p.mRot);
    
    XFcMath::matrixIdentity(aDest);
    aDest.m[0][0] = p.mScale.x;
    aDest.m[1][1] = p.mScale.y;
    aDest.m[2][2] = p.mScale.z;
    
    aDest *= rotation;
    
    aDest.m[3][0] = p.mPos.x;
    aDest.m[3][1] = p.mPos.y;
    aDest.m[3][2] = p.mPos.z;
    
    mNextFrame++;
    if(mNextFrame >= mData->size())
        mNextFrame = 0;
}


