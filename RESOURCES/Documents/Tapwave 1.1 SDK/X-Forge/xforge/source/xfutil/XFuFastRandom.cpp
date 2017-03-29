/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Implementation of a 'fast' random class. 
 * 
 * \note This is the initial implementation of a 'fast' random (noise)
 * function. It is not meant to generate too good random numbers, and is
 * just meant as a 'noise' function (visual effects).
 *
 * $Id: XFuFastRandom.cpp,v 1.5 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.5 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuFastRandom.h>


XFuFastRandom::XFuFastRandom()
{
    seed(XFcCore::getTick());
}


XFuFastRandom::XFuFastRandom(UINT32 aSeed)
{
    seed(aSeed);
}


void XFuFastRandom::seed(UINT32 aSeed)
{
    UINT32 s = aSeed & 31;
    UINT32 t = aSeed ^ 0x14951C57;
    mSeed2 = (t >> s) + (t << (32 - s));
    s = (aSeed >> 5) & 31;
    t = aSeed ^ 0x6C691B25;
    mSeed1 = (t >> s) + (t << (32 - s));
}

