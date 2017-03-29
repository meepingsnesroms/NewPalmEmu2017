///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// Compressed File Library 3 makecfl util
// Copyright (c) 2001-2002 Jari Komppa and Fathammer Ltd
//
//
///////////////////////////////////////////////
// License
///////////////////////////////////////////////
// 
//     This software is provided 'as-is', without any express or implied
//     warranty.    In no event will the authors be held liable for any damages
//     arising from the use of this software.
// 
//     Permission is granted to anyone to use this software for any purpose,
//     including commercial applications, and to alter it and redistribute it
//     freely, subject to the following restrictions:
// 
//     1. The origin of this software must not be misrepresented; you must not
//        claim that you wrote the original software. If you use this software
//        in a product, an acknowledgment in the product documentation would be
//        appreciated but is not required.
//     2. Altered source versions must be plainly marked as such, and must not be
//        misrepresented as being the original software.
//     3. This notice may not be removed or altered from any source distribution.
// 
// (eg. same as ZLIB license)
// 
//
///////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenwad.h"

tokenwad::tokenwad() 
{ 
    mData = NULL; 
    mCount = 0; 
}

tokenwad::~tokenwad() 
{ 
    for (int i=0;i<mCount;i++) 
        delete[] mData[i]; 
    delete[] mData; 
}

void tokenwad::tokenize(const char *aBuf, const char *aSeparators) 
{
    if (mData != NULL) 
    {
        for (int i = 0; i < mCount; i++)             
            delete[] mData[i]; 
        delete[] mData;
    }
    if (aBuf == NULL) return;

    int sepcount = 0;
    while (aSeparators[sepcount] != 0) sepcount++;

    // pass 1: mCount tokens
    
    mCount = 1;
    int i = 0;
    while (aBuf[i] != 0) 
    {      
        for (int j = 0; j < sepcount; j++)
            if (aBuf[i] == aSeparators[j]) 
                mCount++;
            i++;
    }
    int *offsets = new int[mCount + 1];
    int *lengths = new int[mCount + 1];
    
    // TODO: add out of memory check
    
    mCount = 0;
    offsets[0] = 0;
    i = 0;

    // pass 2: mCount token sizes and offsets
    
    while (aBuf[i] != 0) 
    {      
        for (int j = 0; j < sepcount; j++)
            if (aBuf[i] == aSeparators[j]) 
                offsets[++mCount] = i + 1;
            i++;
    }
    offsets[++mCount] = i + 1;

    // pass 3: trim
    
    for (i = 0; i < mCount; i++) 
    {
        // ltrim
        while (aBuf[offsets[i]] == 32 || aBuf[offsets[i]] == 9) 
            offsets[i]++;
        // rtrim
        lengths[i] = offsets[i + 1] - (offsets[i] + 1);
        while (lengths[i] > 0 && 
              (aBuf[offsets[i] + lengths[i] - 1] == 32 || 
               aBuf[offsets[i] + lengths[i] - 1] == 9)) 
            lengths[i]--;
    }

    // pass 4: allocate

    mData = new char*[mCount];
    // TODO: add out of memory check

    for (i=0;i<mCount;i++) 
    {
        mData[i] = new char[lengths[i] + 1];
        // TODO: add out of memory check
        mData[i][lengths[i]] = 0;
    }

    // pass 5: copy tokens
    
    for (i = 0; i < mCount; i++)
        for (int j = offsets[i], c = 0; j < offsets[i] + lengths[i]; j++, c++)
            mData[i][c] = aBuf[j];
        delete[] offsets;
        delete[] lengths;
}


int tokenwad::tokens() 
{ 
    return mCount; 
}

const char * tokenwad::token(int aIdx) 
{ 
    if (aIdx >= mCount || aIdx < 0) return NULL;
    return (const char*)mData[aIdx]; 
}

char * tokenwad::tokendup(int aIdx) 
{ 
    if (aIdx >= mCount || aIdx < 0) return NULL;
    return strdup(mData[aIdx]); 
}  

int tokenwad::tokenEquals(int aIdx, const char *aString)
{
    if (aIdx > mCount) return 0;
    char *s1 = (char*)token(aIdx), *s2=(char*)aString;
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    if (!*s1 && !*s2) return 1;
    return 0;
}

int tokenwad::tokenEqualsNocase(int aIdx, const char *aString)
{
    if (aIdx > mCount) return 0;
    char *s1 = (char*)token(aIdx), *s2 = (char*)aString;
    while (*s1 && *s2 && toupper(*s1) == toupper(*s2)) 
    {
        s1++;
        s2++;
    }
    if (!*s1 && !*s2) return 1;
    return 0;
}
