/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Frame rate counter class
 * 
 * $Id: XFuFPSCount.cpp,v 1.5 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.5 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuFPSCount.h>

XFuFPSCount::XFuFPSCount()
{
    mTicks = NULL;
    mTickCount = 0;
    mCurrentTick = 0;
}

XFuFPSCount::~XFuFPSCount()
{
    delete[] mTicks;
}


XFuFPSCount * XFuFPSCount::create(INT32 aFrameInterval)
{
    XFuFPSCount * t = new XFuFPSCount;
    
    if (t == NULL) 
        return NULL;
    
    // Minimum number of tick stamps is 2.
    if (aFrameInterval < 2) 
        aFrameInterval = 2;

    t->mTickCount = aFrameInterval;
    
    t->mTicks = new INT32[aFrameInterval];
    
    if (t->mTicks == NULL)
    {
        delete t;
        return NULL;
    }

    INT32 i;
    for (i = 0; i < aFrameInterval; i++)
        t->mTicks[i] = 0xffffff;

    return t;
}
    
void XFuFPSCount::tick()
{
    mCurrentTick++;
    if (mCurrentTick >= mTickCount)
        mCurrentTick = 0;
    mTicks[mCurrentTick] = XFcCore::getTick();
}

REAL XFuFPSCount::getFPS()
{
    INT32 v = (mCurrentTick + 1);
    if (v >= mTickCount) v = 0;
    INT32 delta = mTicks[mCurrentTick] - mTicks[v];
    if (mTickCount < 2)
        return 0;
    if (delta < 1)
        return 0; // actually, this should be 'infinite'
    return REALi(1000) / ((REAL)(delta) / (REAL)(mTickCount - 1));
}


