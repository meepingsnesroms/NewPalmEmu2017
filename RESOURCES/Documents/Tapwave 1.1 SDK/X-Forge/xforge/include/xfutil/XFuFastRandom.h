/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Implementation of a "fast" random class. 
 * 
 * $Id: XFuFastRandom.h,v 1.9 2003/10/03 11:29:31 jetro Exp $
 * $Date: 2003/10/03 11:29:31 $
 * $Revision: 1.9 $
 */

#ifndef XFUFASTRANDOM_H_INCLUDED
#define XFUFASTRANDOM_H_INCLUDED


//! A "fast" pseudo random number generator class.
/*!
 * Please note that the output from this pseudorandom number generator
 * is pretty poor, but it is suitable when all you need is just some noise.
 */
class XFuFastRandom
{
public:
    
    //! Constructor.
    XFuFastRandom();
    
    //! Constructor with seed input.
    XFuFastRandom(UINT32 aSeed);
    
    //! Returns the next random number.
    inline UINT32 next()
    {
        INT32 v = (INT32)mSeed1;
        mSeed1 = ((v >> 13) + (v << (32 - 13)));  
        v = mSeed2 ^ 0x51549515;
        mSeed2 = mSeed1 ^ mSeed2;
        mSeed1 = v;
        return mSeed1;
    }
    
    //! Re-seeds the random number generator.
    void seed(UINT32 aSeed);
    
protected:

    UINT32 mSeed1;      //!< Internal random number generator data.
    UINT32 mSeed2;      //!< Internal random number generator data.
};


#endif // !XFUFASTRANDOM_H_INCLUDED

