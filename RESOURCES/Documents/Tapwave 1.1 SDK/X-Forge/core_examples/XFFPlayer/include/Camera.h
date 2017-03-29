/*! \file
 * Camera.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Camera.h,v 1.2 2003/07/01 11:31:35 mikko Exp $
 * $Date: 2003/07/01 11:31:35 $
 * $Revision: 1.2 $
 */
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Group.h"

//! Camera class, extends Group
class Camera : public Group
{
public:
    //! Static constructor.
    static Camera * create(GameGraph *aGameGraph, UINT32 aId);
    
    //! Virtual destructor.
    virtual ~Camera();

    //! Sets camera matrix
    virtual void setCamera();

    //! Field of view in radians
    REAL mFOV;
    //! Near clipping plane
    REAL mNear;
    //! Far clipping plane
    REAL mFar;

protected:
    //! Protected constructor.
    Camera(GameGraph *aGameGraph, UINT32 aId);
};



#endif // !CAMERA_H_INCLUDED
