/*! \file
 * Sprite.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Sprite.h,v 1.3 2003/07/04 14:16:00 lars Exp $
 * $Date: 2003/07/04 14:16:00 $
 * $Revision: 1.3 $
 */

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

//! Sprite types used.
enum SP_SPRITE_TYPE 
{
    SP_SPRITE_NA = 0, //!< Undefined
    SP_SPRITE_HOOP,   //!< Hoop sprite
    SP_SPRITE_BONUS,  //!< Bonus sprite
};


//! Basic sprite class. Not very general though.
class Sprite
{
public:
    //! Constructor.
    Sprite() : mTexture(NULL), mEnabled(1), mType(SP_SPRITE_NA) {};

    //! Set pointer to texture for this sprite.
    void setTexture(XFcGLTexture *aTexture) { mTexture = aTexture; }

    //! Get pointer to texture used by this sprite.
    XFcGLTexture *getTexture() { return mTexture; }

    //! Get the type of this sprite.
    SP_SPRITE_TYPE getType() { return mType; }

    //! Returns 1 if sprite is enabled, 0 if not.
    INT isEnabled() { return mEnabled; }

    //! Disable this sprite.
    void disable() { mEnabled = 0; }

    //! Set sprite location.
    void setLocation(REAL aX, REAL aY, REAL aZ) { mX = aX; mY = aY; mZ = aZ; }

    //! Functions for returning sprite location.
    virtual REAL getX() { return mX; }
    virtual REAL getY() { return mY; }
    virtual REAL getZ() { return mZ; }

protected:
    //! Enabled/disabled flag.
    INT mEnabled;

    //! Type of sprite: currently only SRRITE_HOOP and SPRITE_BONUS used.
    SP_SPRITE_TYPE mType;
    
    //! Sprite location.
    REAL mX, mY, mZ;

    //! Pointer to texture.
    XFcGLTexture *mTexture;
};

#endif // !SPRITE_H_INCLUDED