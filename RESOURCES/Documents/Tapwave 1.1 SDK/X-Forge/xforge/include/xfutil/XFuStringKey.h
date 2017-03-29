/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFuStringKey.h is the header file for the XFuStringKey class,
 * which is a null terminated string key for use with hashtables.
 *
 * $Id: XFuStringKey.h,v 1.11 2003/09/29 13:49:02 jari Exp $
 * $Date: 2003/09/29 13:49:02 $
 * $Revision: 1.11 $
 */

#ifndef XFUSTRINGKEY_H_INCLUDED
#define XFUSTRINGKEY_H_INCLUDED

#include <xfcore/XFcHashtable.h>


#define XFUSTRINGKEY_DATASIZE   64


class XFuStringKey
{

public:

    //! Default constructor.
    XFuStringKey();

    //! Constructor.
    XFuStringKey(const CHAR *aKey);

    //! Copy constructor.
    XFuStringKey(const XFuStringKey &aKey);

    //! Overloaded assignment operator.
    XFuStringKey & operator=(const XFuStringKey &aKey);

    //! Destructor.
    virtual ~XFuStringKey();

    //! Initializer.
    void init(const CHAR *aKey);

    //! Key value.
    CHAR *mKey;

    //! Hash code.
    UINT32 mHashCode;

protected:

    CHAR mData[XFUSTRINGKEY_DATASIZE];
    UINT8 mUsingData;

};


/*
//! Hashcode function for XFuStringKey.
UINT32 XFcHashtableHash<XFuStringKey>::operator() (const XFuStringKey key) const;

//! Equality check for XFuStringKey.
INT XFcHashtableEQ<XFuStringKey>::operator() (const XFuStringKey key1, const XFuStringKey key2) const;
*/


#endif // !XFUSTRINGKEY_H_INCLUDED

