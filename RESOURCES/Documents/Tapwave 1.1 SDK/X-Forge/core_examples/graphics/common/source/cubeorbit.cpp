/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief Code to set up rendering environment to animate the cube.
 * 
 * $Id: cubeorbit.cpp,v 1.3 2003/01/16 14:36:36 jetro Exp $
 * $Date: 2003/01/16 14:36:36 $
 * $Revision: 1.3 $
 */

#include <xforge.h>


void xfCubeOrbit(XFcGL *aGL)
{
    XFcMatrix4 matrixWorld;             // Object relation to world space.
    XFcMatrix4 matrixLookAt;            // World relation to camera space.
    XFcMatrix4 matrixProjection;        // Camera projection matrix.
    
    XFcVector3 cubePos;                 // Cube position in world space.
    XFcVector3 camDist;                 // Camera distance from world origin.
    XFcMatrix4 camRotation;             // Camera's position rotating matrix.
    
    XFcVector3 aPos;                    // Camera's position in world space.
    XFcVector3 aAt;                     // Camera's point of view.
    XFcVector3 aUp;                     // Direction of up.
    
    
    // Animation speed.
    INT32 t = (XFcCore::getTick() / 10);
    
    // Define viewport:
    // For 240x320, objects in X=0..239, Y=0..319, Z=1..1000 will be drawn.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = 1;
    vp.mMaxZ = 1000;
    
    // Set viewport.
    aGL->setViewport(vp);
    
    // Clear framebuffer to black.
    aGL->clear();
    
    // World matrix: Object relation to World space.
    
    // Move cube in elliptic track in y-plane. Note: uses floats.
    cubePos.x = 7 * cos(t / 100.0f);
    cubePos.y = 0;
    cubePos.z = 15 * sin(t / 100.0f);
    
    // Translate World matrix to cube position.
    matrixWorld = XFcMath::matrixTranslation(matrixWorld, cubePos);
    
    // Rotate cube around its origin by every axis.
    matrixWorld = XFcMath::matrixRotateX(matrixWorld, 2.0f * t / 100);
    matrixWorld = XFcMath::matrixRotateY(matrixWorld, 1.5f * t / 100);
    matrixWorld = XFcMath::matrixRotateZ(matrixWorld, 1.0f * t / 100);
    
    // (Matrix initialization is done by Translation or Rotation-functions and
    // cumulative calculations after that by Translate or Rotate-functions.)
    
    
    // LookAt matrix: World space relation to Camera space.
    
    // Rotate camera around Y-axis (camRotation matrix is created when
    // using Rotation-function. Rotate-function needs the matrix to be initialized).
    camRotation = XFcMath::matrixRotationY(camRotation, 2 * 3.14159265f * t / 1000);
    
    // Set camera to be at y-plane Y=100, and distance from Y-axis to 400.
    camDist.x = 0;
    camDist.y = 0;
    camDist.z = 30;
    
    // Transform camera Rotation matrix and distance vector to camera's position aPos.
    XFcMath::matrixTransform(camRotation, camDist, aPos);
    
    // Camera will look at origin at every time.
    aAt.x = 0; 
    aAt.y = 0; 
    aAt.z = 0;
    
    // Positive Y-axis points to up.
    aUp.x = 0; 
    aUp.y = 1; 
    aUp.z = 0;
    
    // Calculate LookAt matrix and inverse it for use.
    XFcMath::matrixLookAt(matrixLookAt, aPos, aAt, aUp);
    matrixLookAt = XFcMath::matrixInverseFast(matrixLookAt);
    
    // Projection matrix: Camera Projection space.
    
    // Picture height 320, width 240, Field of view = 90 degrees = pi/2
    // Nearest z-coordinate to render is 1 and farest 1000.
    XFcMath::matrixToProjection(matrixProjection,
                                XFcCore::getDeviceHeight(),
                                XFcCore::getDeviceWidth(),
                                3.14159265f / 2, 1, 1000);
    
    // Set Object->World-matrix.
    aGL->setMatrix(XFCGLMAT_WORLD, matrixWorld);        
    // Set World->Camera-matrix.
    aGL->setMatrix(XFCGLMAT_VIEW, matrixLookAt);        
    // Set Projection matrix.
    aGL->setMatrix(XFCGLMAT_PROJECTION, matrixProjection);      
}
