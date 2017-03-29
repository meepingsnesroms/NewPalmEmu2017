/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief	String tokenizer utility
 * 
 * $Id: XFuTokenizer.cpp,v 1.4 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.4 $
 */

#include <xfcore/XFcCore.h>
#include <string.h> // memcpy
#include <xfutil/XFuTokenizer.h>


//! Constructor
XFuTokenizer::XFuTokenizer() 
{ 
    mData = NULL; 
    mCount=0; 
}


//! Destructor
XFuTokenizer::~XFuTokenizer() 
{
    INT32 i;
    for (i = 0; i < mCount; i++) 
        delete[] mData[i]; 
    delete[] mData; 
}


//! Tokenizes the input string, using the characters in 'separators' as delimiters for tokens
void XFuTokenizer::tokenize(const CHAR * aBuffer, const CHAR * aSeparators)
{
    // if reusing this tokenizer, clean up old mess:
    if (mData != NULL) 
    {
        INT32 i;
        for (i = 0; i < mCount; i++) 
        {
            delete[] mData[i]; 
        }
        delete[] mData;
        mCount = 0;
        mData = NULL;
    }
    if (aBuffer == NULL) return;
    INT32 sepcount = 0;
    while (aSeparators[sepcount] != 0) sepcount++;

    // pass 1: mCount tokens

    mCount = 1;
    INT32 i = 0;
    while (aBuffer[i] != 0) 
    {
        INT32 j;
        for (j = 0; j < sepcount; j++)
        {
            if (aBuffer[i] == aSeparators[j]) 
                mCount++;
        }
        i++;
    }
    INT32 *offsets = new INT32[mCount + 1];
    if (offsets == NULL)
    {
        mCount=0;
        return;
    }
    INT32 *lengths = new INT32[mCount + 1];
    if (lengths == NULL)
    {
        delete[] offsets;
        mCount=0;
        return;
    }
    mCount=0;
    offsets[0]=0;
    i=0;

    // pass 2: mCount token sizes and offsets

    while (aBuffer[i] != 0) 
    {
        INT32 j;
        for (j=0;j<sepcount;j++)
        {
            if (aBuffer[i]==aSeparators[j]) 
                offsets[++mCount]=i+1;
        }
        i++;
    }
    offsets[++mCount] = i + 1;

    // pass 3: trim

    for (i = 0; i < mCount; i++) 
    {
        // ltrim
        while (aBuffer[offsets[i]] == 32 || aBuffer[offsets[i]] == 9) offsets[i]++;
        // rtrim
        lengths[i] = offsets[i + 1] - (offsets[i] + 1);
        while (lengths[i] > 0 && (aBuffer[offsets[i] + lengths[i] - 1] == 32 || aBuffer[offsets[i] + lengths[i] - 1] == 9)) lengths[i]--;
    }

    // pass 4: allocate

    mData = new CHAR*[mCount];
    if (mData == NULL)
    {
        delete[] offsets;
        delete[] lengths;
        mCount=0;
        return;
    }
    for (i = 0; i < mCount; i++) 
    {
        mData[i] = new CHAR[lengths[i] + 1];
        mData[i][lengths[i]] = 0;
    }
    
    // pass 5: copy tokens

    for (i = 0; i < mCount; i++)
    {
        INT32 j, c;
        for (j = offsets[i], c = 0; j < offsets[i] + lengths[i]; j++, c++)
        {
            mData[i][c] = aBuffer[j];
        }
    }
    delete[] offsets;
    delete[] lengths;
}


//! Tokenizes the input string, using the ',' and '=' characters as delimiters for tokens
void XFuTokenizer::tokenize(const CHAR * aBuffer)
{
    tokenize(aBuffer,"=,");
}


//! Case sensitive matching of a token and given string
INT XFuTokenizer::tokenEquals(INT32 aIdx, const CHAR * aCompareString)
{
    const CHAR *t1 = getToken(aIdx), *t2 = aCompareString;
    while (*t1 != 0 && *t2 != 0 && *t1 == *t2) 
    { 
        t1++; 
        t2++; 
    }
    if (*t1 == *t2) return 1;
    return 0;
}


//! Case insensitive matching of a token and given string
INT XFuTokenizer::tokenEqualsNocase(INT32 aIdx, const CHAR * aCompareString)
{
    const CHAR *t1 = getToken(aIdx), *t2 = aCompareString;
    while (*t1 != 0 && *t2 != 0 && upcase(*t1) == upcase(*t2)) 
    { 
        t1++; 
        t2++; 
    }
    if (*t1 == *t2) return 1;
    return 0;
}


//! Get the token count
INT32 XFuTokenizer::getTokenCount()
{ 
    return mCount; 
}


//! Get a pointer to a token (as zero-terminated string)
const CHAR * XFuTokenizer::getToken(INT32 aIdx)
{ 
    return (const CHAR*)mData[aIdx]; 
}


//! Get a duplicate of a token (as zero-terminated string)
CHAR * XFuTokenizer::duplicateToken(INT32 aIdx) 
{ 
    INT32 l=0;
    const CHAR * s=mData[aIdx];
    while (s[l]!=0) l++;
    CHAR * copy=new CHAR[l+1];
    copy[l]='\0';
    memcpy(copy,s,l*sizeof(CHAR));
    return copy;
}


//! upcase function
CHAR XFuTokenizer::upcase(CHAR i) 
{
    if (i>='a' && i<='z') return (CHAR)(i-('a'-'A'));
    return i;
}



