/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFuStringKey.cpp is the implementation file for the
 * XFuStringKey class. For more information, see XFuStringKey.h.
 *
 * $Id: XFuStringKey.cpp,v 1.9 2003/09/29 13:47:35 jari Exp $
 * $Date: 2003/09/29 13:47:35 $
 * $Revision: 1.9 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuStringKey.h>


XFuStringKey::XFuStringKey()
{
    mKey = NULL;
    mHashCode = 0;
    mUsingData = 0;
}


XFuStringKey::XFuStringKey(const CHAR *aKey)
{
    init(aKey);
}


XFuStringKey::XFuStringKey(const XFuStringKey &aKey)
{
    init(aKey.mKey);
}


XFuStringKey & XFuStringKey::operator=(const XFuStringKey &aKey)
{
    init(aKey.mKey);
    return *this;
}


void XFuStringKey::init(const CHAR *aKey)
{
    mKey = NULL;
    mHashCode = 0;
    mUsingData = 0;

    if (aKey)
    {
        INT32 keyLen = XFcStringToolkit::getLength(aKey);
        if (keyLen < XFUSTRINGKEY_DATASIZE - 1)
            mUsingData = 1;
        if (mUsingData)
        {
            mKey = mData;
            INT a;
            for (a = 0; a < keyLen; ++a)
                mData[a] = aKey[a];
            mData[keyLen] = 0;
        }
        else
        {
            mKey = XFcStringToolkit::copy(aKey);
        }
        mHashCode = 0;
        INT32 pos;
        for (pos = 0; pos < keyLen; pos++)
            mHashCode = 7 * mHashCode + aKey[pos];
    }
    else
    {
        mKey = NULL;
    }
}


XFuStringKey::~XFuStringKey()
{
    if (!mUsingData)
        delete[] mKey;
}


UINT32 XFcHashtableHash<XFuStringKey>::operator() (const XFuStringKey key) const
{
    return key.mHashCode;
}


INT XFcHashtableEQ<XFuStringKey>::operator() (const XFuStringKey key1, const XFuStringKey key2) const
{
    return !XFcStringToolkit::compare(key1.mKey, key2.mKey);
}


