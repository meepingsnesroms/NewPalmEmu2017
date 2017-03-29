/*! \file
 * PRSAnimation.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: PRSAnimation.h,v 1.3 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.3 $
 */
#ifndef PRSANIMATION_H_INCLUDED
#define PRSANIMATION_H_INCLUDED

template<class T> class XFuDynamicArray;

struct PRS
{
    XFcVector3 mPos;
    XFcQuaternion mRot;
    XFcVector3 mScale;

    PRS() : mPos(0,0,0), mRot(0,0,0,1), mScale(1,1,1)
    { }
    PRS(XFcVector3 aPos, XFcQuaternion aRot, XFcVector3 aScale) : mPos(aPos), mRot(aRot), mScale(aScale)
    { }
    PRS(const PRS &aPRS) : mPos(aPRS.mPos), mRot(aPRS.mRot), mScale(aPRS.mScale)
    { }
};

//! Simple PRS Animation container class
class PRSAnimation
{
public:
    //! Static creation
    static PRSAnimation * create();    
    
    //! Virtual destructor.
    virtual ~PRSAnimation();

    //! Calculates the matrix for the next frame of animation
    void getNextFrame(XFcMatrix4 &aDest);

    //! Appends frame to the animation data
    void addFrame(PRS &aPRS);
protected:
    //! Protected constructor.
    PRSAnimation();

    //! The next frame to be calculated
    UINT32 mNextFrame;

    XFuDynamicArray<PRS> *mData;

};



#endif // !PRSANIMATION_H_INCLUDED
