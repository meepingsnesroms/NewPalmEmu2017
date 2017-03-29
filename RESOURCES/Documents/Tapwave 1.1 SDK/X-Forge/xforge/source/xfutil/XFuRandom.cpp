/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Mersenne Twister random generator
 *
 * Information about the algorithm can be found at:
 * http://www.math.keio.ac.jp/~matumoto/emt.html
 *
 * $Id: XFuRandom.cpp,v 1.8 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.8 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuRandom.h>


enum XFURANDOM_MERSENNE_PARAMETERS
{
    XFURMP_N = 351,
    XFURMP_M = 175,
    XFURMP_R = 19,
    XFURMP_LOMASK = 0x0007FFFF,
    XFURMP_HIMASK = 0xFFFFE000,
    XFURMP_A = 0xEABD75F5,
    XFURMP_U = 11,
    XFURMP_S = 7,
    XFURMP_T = 15,
    XFURMP_L = 17,
    XFURMP_B = 0x655E5280,
    XFURMP_C = 0xFFD58000
};


XFuRandom::~XFuRandom()
{
    delete[] mTable;
    mTable = NULL;
}


XFuRandom::XFuRandom() : mTable(NULL)
{
}


XFuRandom * XFuRandom::create()
{
    return create((UINT32)XFcCore::getTick());
}


XFuRandom * XFuRandom::create(UINT32 aSeed)
{
    XFuRandom *res = new XFuRandom;

    if (res == NULL)
        return NULL;

    res->mTable = new UINT32[XFURMP_N];
    if (res->mTable == NULL)
    {
        delete res;
        return NULL;
    }

    res->seed(aSeed);

    return res;
}


UINT32 XFuRandom::next()
{
    UINT32 value;

    if (mTableIndex >= XFURMP_N)
    {
        UINT32 i, j;
        for (i = 0, j = XFURMP_M; i < XFURMP_N - 1; ++i)
        {
            value = (mTable[i] & XFURMP_HIMASK) | (mTable[i + 1] & XFURMP_LOMASK);
            mTable[i] = mTable[j] ^ (value >> 1) ^ (-(INT32)(value & 1) & XFURMP_A);
            ++j;
            if (j >= XFURMP_N)
                j = 0;
        }

        value = (mTable[XFURMP_N - 1] & XFURMP_HIMASK) | (mTable[0] & XFURMP_LOMASK);
        mTable[XFURMP_N - 1] = mTable[XFURMP_M - 1] ^ (value >> 1) ^ (-(INT32)(value & 1) & XFURMP_A);
        mTableIndex = 0;
    }

    value = mTable[mTableIndex];
    ++mTableIndex;

    value ^= (value >> XFURMP_U);
    value ^= (value << XFURMP_S) & XFURMP_B;
    value ^= (value << XFURMP_T) & XFURMP_C;
    value ^= (value >> XFURMP_L);

    return value;
}


void XFuRandom::seed(UINT32 aSeed)
{
    UINT32 s = aSeed;
    for (mTableIndex = 0; mTableIndex < XFURMP_N; ++mTableIndex)
    {
        s = (s * 29943829) - 1;
        mTable[mTableIndex] = s;
    }
}

