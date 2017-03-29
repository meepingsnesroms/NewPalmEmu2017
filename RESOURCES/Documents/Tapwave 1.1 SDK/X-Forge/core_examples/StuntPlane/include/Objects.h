/*! \file
 * Objects.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Objects.h,v 1.3 2003/07/22 13:33:35 lars Exp $
 * $Date: 2003/07/22 13:33:35 $
 * $Revision: 1.3 $
 */

#ifndef HOOP_H_INCLUDED
#define HOOP_H_INCLUDED


//! Allowed plane orientations when passing through a hoop.
enum SP_HOOP_ORIENTATION 
{
    SP_HOOP_ANY = 0,
    SP_HOOP_MINUS,
    SP_HOOP_SLASH,
    SP_HOOP_BAR,
    SP_HOOP_BACKSLASH,
    SP_HOOP_PLUS,
    SP_HOOP_CROSS
};


//! Hoop object class used in the StuntPlane game.
class Hoop : public Sprite
{
public:
    //! Constructor.
    Hoop() : mHoleX(0), mHoleY(0) { mType = SP_SPRITE_HOOP; }

    //! Set allowed orientation.
    void setOrientation(SP_HOOP_ORIENTATION aOrientation) { mOrientation = aOrientation; }

    //! Get allowed orientation.
    SP_HOOP_ORIENTATION getOrientation() { return mOrientation; }

    //! Return coordinates of the center of the hole.
    virtual REAL getX() { return mX + mHoleX; }
    virtual REAL getY() { return mY + mHoleY; }

    //! Set hole (which you fly through) parameters.
    void setHoleParameters(REAL aX, REAL aY, REAL aDiam) 
    {
        mHoleX = aX; 
        mHoleY = aY;
        mHoleDiameter = aDiam;
    }

    //! Get diameter of the hole you fly through.
    REAL getHoleDiameter() { return mHoleDiameter; }

protected:
    //! Hole information.
    REAL mHoleX, mHoleY, mHoleDiameter;

    //! Allowed orientation.
    SP_HOOP_ORIENTATION mOrientation;
};


//! Bonus object class used in the StuntPlane game.
class Bonus : public Sprite
{
public:
    //! Constructor.
    Bonus() { mType = SP_SPRITE_BONUS; }

    //! Set bonus value.
    void setValue(int aValue) { mValue = aValue; }

    //! Get bonus value.
    INT getValue() { return mValue; }

protected:
    //! How many bonus points this object is worth.
    INT mValue;
};


//! Specifies wind magnitude, direction, rotation and gustfactor at a specific point on the level;
class WindParameter
{
public:
    void setParameters(REAL aZ, REAL aMagnitude, REAL aDirection, REAL aGustFactor)
    {
        mZ = aZ;
        mMagnitude = aMagnitude;
        mDirection = aDirection;
        mGustFactor = aGustFactor;
    }
    REAL getZ() { return mZ; }
    REAL getMagnitude() { return mMagnitude; }
    REAL getDirection() { return mDirection; }
    REAL getGustFactor() { return mGustFactor; }

protected:
    REAL mZ;

    REAL mMagnitude;
    REAL mDirection;

    REAL mGustFactor;
};

#endif // !OBJECTS_H_INCLUDED