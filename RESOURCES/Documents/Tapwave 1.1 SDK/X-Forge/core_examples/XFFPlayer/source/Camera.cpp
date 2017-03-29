/*! \file
* Camera.cpp <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: Camera.cpp,v 1.2 2003/09/04 12:26:31 toni Exp $
* $Date: 2003/09/04 12:26:31 $
* $Revision: 1.2 $
*/

#include <xforge.h>
#include <xfutil/XFuDynamicArray.h>
#include "Camera.h"
#include "GameGraph.h"

Camera * Camera::create(GameGraph *aGameGraph, UINT32 aId)
{
    Camera *g = new Camera(aGameGraph, aId);
    if(g)
    {
        // Further initializations and memory allocations
        g->mType = NT_CAMERA;
        g->mChildren = XFuDynamicArray<Group *>::create();
        if(!g->mChildren)
        {
            delete g;
            g = NULL;
        }
    }
    return g;    
}

Camera::Camera(GameGraph *aGameGraph, UINT32 aId) : Group(aGameGraph, aId), mFOV(PI / 2), mNear(REALf(0.1)), mFar(REALi(1000))
{
    
}

Camera::~Camera()
{
    
}

//! Sets view and projection matrices
void Camera::setCamera()
{
    XFcGL *gl = mGameGraph->getGL();
    // Build the view matrix
    XFcMatrix4 view = mWorldTransformation;
    XFcMath::matrixInverseFast(view);
    gl->setMatrix(XFCGLMAT_VIEW, view);
    
    // Create a 4x4 matrix
    XFcMatrix4 projectionMatrix;
    
    // Get viewport information from GL device, used for aspect ratio in projection matrix
    XFcGLViewport viewport;
    gl->getViewport(viewport);
    
    // Create a projection matrix with aspect ratio from viewport
    XFcMath::matrixToProjection(projectionMatrix,
        viewport.mAreaHeight,
        viewport.mAreaWidth,
        mFOV,
        mNear,
        mFar);
    
    // Set projection transform to GL device
    gl->setMatrix(XFCGLMAT_PROJECTION, projectionMatrix);
}