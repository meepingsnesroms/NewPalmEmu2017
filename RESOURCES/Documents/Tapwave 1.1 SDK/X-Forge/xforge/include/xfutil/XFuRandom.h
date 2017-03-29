/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief "Normal" random class
 *
 * $Id: XFuRandom.h,v 1.11 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.11 $
 */

#ifndef XFURANDOM_H_INCLUDED
#define XFURANDOM_H_INCLUDED


//! Pseudo random number generator class.
class XFuRandom
{
public:

    //! Static constructor.
    /*! Random generator is initialized using system timer as the random seed value.
     * \return new random number generator object if successful, or NULL if unsuccessful.
     */
    static XFuRandom * create();

    //! Static constructor.
    /*! \param aSeed seed value to be used for initializing the random number generator.
     * \return new random number generator object if successful, or NULL if unsuccessful.
     */
    static XFuRandom * create(UINT32 aSeed);

    //! Returns the next random number.
    UINT32 next();
    //! Re-seeds the random number generator.
    void seed(UINT32 aSeed);
    //! Destructor.
    ~XFuRandom();

private:

    //! Protected constructor.
    XFuRandom();

    UINT32 *mTable;
    UINT32 mTableIndex;
};


#endif // !XFURANDOM_H_INCLUDED

