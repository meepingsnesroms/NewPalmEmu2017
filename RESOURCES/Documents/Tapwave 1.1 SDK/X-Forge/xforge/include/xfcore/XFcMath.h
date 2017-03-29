/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Math functions.
 * 
 * $Id: XFcMath.h,v 1.26 2003/08/29 13:41:52 kkallio Exp $
 * $Date: 2003/08/29 13:41:52 $
 * $Revision: 1.26 $
 */

#ifndef XFC_XFCMATH_H_INCLUDED
#define XFC_XFCMATH_H_INCLUDED

#ifndef PI
#define PI 3.1415926535897932384626433832795f
#endif

// Value of ln(2.0)
#define LN_2 0.69314718055994530941723212145818f

class XFcQuaternion;
class XFcMatrix3;
class XFcMatrix4;
class XFcVector2;
class XFcVector3;
class XFcVector4;


//! Static collection of math functions.
/*! Contains quaternion, matrix and vector functions as well as math
 *  primitives like sin, cos, etc.
 */
class XFCDLLEXPORT XFcMath
{
public:
    //! Creates a quaternion that rotates around X axis.
    XFCIMPORT static XFcQuaternion & quaternionRotationX(XFcQuaternion &aQuat,
                                                         REAL aAngle);
    //! Creates a quaternion that rotates around Y axis.
    XFCIMPORT static XFcQuaternion & quaternionRotationY(XFcQuaternion &aQuat,
                                                         REAL aAngle);
    //! Creates a quaternion that rotates around Z axis.
    XFCIMPORT static XFcQuaternion & quaternionRotationZ(XFcQuaternion &aQuat,
                                                         REAL aAngle);
    //! Creates a quaternion that rotates around X, Y and Z axes.
    XFCIMPORT static XFcQuaternion & quaternionRotationXYZ(XFcQuaternion &aQuat,
                                                           REAL aXAngle,
                                                           REAL aYAngle,
                                                           REAL aZAngle);
    //! Creates a quaternion that rotates around given vector.
    XFCIMPORT static XFcQuaternion & quaternionRotationVector(XFcQuaternion &aQuat,
                                                              XFcVector3 &aVector,
                                                              REAL aAngle);
    //! Rotates a quaternion around X axis.
    XFCIMPORT static XFcQuaternion & quaternionRotateX(XFcQuaternion &aQuat,
                                                       REAL aAngle);
    //! Rotates a quaternion around Y axis.
    XFCIMPORT static XFcQuaternion & quaternionRotateY(XFcQuaternion &aQuat,
                                                       REAL aAngle);
    //! Rotates a quaternion around Z axis.
    XFCIMPORT static XFcQuaternion & quaternionRotateZ(XFcQuaternion &aQuat,
                                                       REAL aAngle);
    //! Rotates a quaternion around X, Y and Z axes.
    XFCIMPORT static XFcQuaternion & quaternionRotateXYZ(XFcQuaternion &aQuat,
                                                         REAL aXAngle,
                                                         REAL aYAngle,
                                                         REAL aZAngle);
    //! Rotates a quaternion around given vector.
    XFCIMPORT static XFcQuaternion & quaternionRotateVector(XFcQuaternion &aQuat,
                                                            XFcVector3 &aVec,
                                                            REAL aAngle);
    //! Creates an identity quaternion.
    XFCIMPORT static XFcQuaternion & quaternionIdentity(XFcQuaternion &aQuat);
    //! Transform a vector by a quaternion.
    /*! This is generally slower than a transform with a matrix, 
     *  so matrices are better for big amounts of vectors.
     */
    XFCIMPORT static void quaternionTransform(XFcQuaternion &aQuat, XFcVector3 &aSrc,
                                              XFcVector3 &aDst);
    //! Creates a quaternion from a look-at vector definition.
    XFCIMPORT static void quaternionLookAt(XFcQuaternion &aQuat, XFcVector3 &aPos,
                                           XFcVector3 &aAt, XFcVector3 &aUp);
    //! Creates a quaternion from a matrix.
    XFCIMPORT static void quaternionFromMatrix(XFcQuaternion &aQuat,
                                               XFcMatrix4 &aMatrix);
    //! Creates a quaternion from a matrix.
    XFCIMPORT static void quaternionFromMatrix(XFcQuaternion &aQuat,
                                               XFcMatrix3 &aMatrix);
    //! Creates matrix from a quaternion.
    XFCIMPORT static void matrixFromQuaternion(XFcMatrix4 &aMatrix,
                                               XFcQuaternion &aQuat);
    //! Interpolates a quaternion using spherical linear interpolation.
    XFCIMPORT static void quaternionSlerp(XFcQuaternion &aFrom, XFcQuaternion &aTo,
                                          REAL aPos, XFcQuaternion &aResult);
    //! Creates an identity matrix.
    XFCIMPORT static XFcMatrix4 & matrixIdentity(XFcMatrix4 &aMatrix);
    //! Creates a matrix that rotates around X axis.
    XFCIMPORT static XFcMatrix4 & matrixRotationX(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Creates a matrix that rotates around Y axis.
    XFCIMPORT static XFcMatrix4 & matrixRotationY(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Creates a matrix that rotates around Z axis.
    XFCIMPORT static XFcMatrix4 & matrixRotationZ(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Creates a translation matrix.
    XFCIMPORT static XFcMatrix4 & matrixTranslation(XFcMatrix4 &aMatrix,
                                                    const XFcVector3 &aOffset);
    //! Creates a scaling matrix.
    XFCIMPORT static XFcMatrix4 & matrixScaling(XFcMatrix4 &aMatrix, REAL aScale);
    //! Rotates a matrix around X axis.
    XFCIMPORT static XFcMatrix4 & matrixRotateX(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Rotates a matrix around Y axis.
    XFCIMPORT static XFcMatrix4 & matrixRotateY(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Rotates a matrix around Z axis.
    XFCIMPORT static XFcMatrix4 & matrixRotateZ(XFcMatrix4 &aMatrix, REAL aAngle);
    //! Translates a matrix by offset.
    XFCIMPORT static XFcMatrix4 & matrixTranslate(XFcMatrix4 &aMatrix,
                                                  const XFcVector3 &aOffset);
    //! Scales a matrix by a value.
    XFCIMPORT static XFcMatrix4 & matrixScale(XFcMatrix4 &aMatrix, REAL aScale);
    //! Transforms a vector by a matrix.
    XFCIMPORT static void matrixTransform(const XFcMatrix4 &aMatrix,
                                          const XFcVector3 &aSrc,
                                          XFcVector3 &aDst);
    //! Transforms a vector by a matrix without translation information (affine transform).
    XFCIMPORT static void matrixTransformNormal(const XFcMatrix4 &aMatrix,
                                                const XFcVector3 &aSrc,
                                                XFcVector3 &aDst);
    //! Transposes a matrix.
    XFCIMPORT static XFcMatrix4 & matrixTranspose(XFcMatrix4 &aMatrix);
    //! Inverses a matrix.
    XFCIMPORT static XFcMatrix4 & matrixInverse(XFcMatrix4 &aMatrix);
    //! Inverses a matrix. Handles only affine 3D transformation matricies.
    XFCIMPORT static XFcMatrix4 & matrixInverseAffine(XFcMatrix4 &aMatrix);
    //! Inverses a matrix. Handles only 3D matricies with rotation and translation.
    XFCIMPORT static XFcMatrix4 & matrixInverseFast(XFcMatrix4 &aMatrix);
    //! Normalizes a matrix.
    XFCIMPORT static void matrixNormalize(XFcMatrix4 &aMatrix);
    //! Creates a look-at matrix.
    XFCIMPORT static void matrixLookAt(XFcMatrix4 &aMatrix, const XFcVector3 &aPos,
                                       const XFcVector3 &aAt, const XFcVector3 &aUp);
    //! Creates a projection matrix.
    XFCIMPORT static void matrixToProjection(XFcMatrix4 &aMatrix, REAL aHeight,
                                             REAL aWidth, REAL aFov,
                                             REAL aZNear, REAL aZFar);

    //! Creates an off-center projection matrix. Left, right, bottom and top are in screen coordinates.
    XFCIMPORT static void matrixToProjectionOffCenter(XFcMatrix4 &aMatrix, REAL aHeight, REAL aWidth,
                                                      REAL aFov, REAL aZNear, REAL aZFar, REAL aLeft, REAL aRight,
                                                      REAL aTop, REAL aBottom);
    //! Creates an off-center projection matrix. Left, right, bottom and top are in cameraspace coordinates.
    XFCIMPORT static void matrixToProjectionOffCenter(XFcMatrix4 &aMatrix, REAL aLeft, REAL aRight,
                                                      REAL aBottom, REAL aTop, REAL aNear, REAL aFar);
    
    //! Projects a vector by a matrix.
    XFCIMPORT static void matrixProject(XFcMatrix4 &aMatrix, const XFcVector4 &aSrc,
                                       XFcVector4 &aDst);
    //! Creates an identity matrix.
    XFCIMPORT static XFcMatrix3 & matrixIdentity(XFcMatrix3 &aMatrix);
    //! Creates a matrix that rotates around X axis.
    XFCIMPORT static XFcMatrix3 & matrixRotationX(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Creates a matrix that rotates around Y axis.
    XFCIMPORT static XFcMatrix3 & matrixRotationY(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Creates a matrix that rotates around Z axis.
    XFCIMPORT static XFcMatrix3 & matrixRotationZ(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Creates a scaling matrix.
    XFCIMPORT static XFcMatrix3 & matrixScaling(XFcMatrix3 &aMatrix, REAL aScale);
    //! Rotates a matrix around X axis.
    XFCIMPORT static XFcMatrix3 & matrixRotateX(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Rotates a matrix around Y axis.
    XFCIMPORT static XFcMatrix3 & matrixRotateY(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Rotates a matrix around Z axis.
    XFCIMPORT static XFcMatrix3 & matrixRotateZ(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Scales a matrix by value.
    XFCIMPORT static XFcMatrix3 & matrixScale(XFcMatrix3 &aMatrix, REAL aScale);
    //! Transforms a vector by matrix.
    XFCIMPORT static void matrixTransform(const XFcMatrix3 &aMatrix,
                                          const XFcVector3 &aSrc,
                                          XFcVector3 &aDst);
    //! Transposes a matrix.
    XFCIMPORT static XFcMatrix3 & matrixTranspose(XFcMatrix3 &aMatrix);
    //! Inverses a matrix.
    XFCIMPORT static XFcMatrix3 & matrixInverse(XFcMatrix3 &aMatrix);
    //! Inverses a matrix. Handles only affine 3D transformation matricies.
    XFCIMPORT static XFcMatrix3 & matrixInverseAffine(XFcMatrix3 &aMatrix);
    //! Inverses a matrix. Handles only 3D rotation matrix.
    XFCIMPORT static XFcMatrix3 & matrixInverseFast(XFcMatrix3 &aMatrix);
    //! Normalizes a matrix.
    XFCIMPORT static void matrixNormalize(XFcMatrix3 &aMatrix);
    //! Creates a matrix from quaternion.
    XFCIMPORT static void matrixFromQuaternion(XFcMatrix3 &aMatrix, XFcQuaternion &aQuat);

    // Matrix operations relating to 2D vectors.

    //! Creates a matrix that rotates around Z axis.
    XFCIMPORT static XFcMatrix3 & matrixRotation2D(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Rotates a matrix around Z axis.
    XFCIMPORT static XFcMatrix3 & matrixRotate2D(XFcMatrix3 &aMatrix, REAL aAngle);
    //! Creates a translation matrix.
    XFCIMPORT static XFcMatrix3 & matrixTranslation2D(XFcMatrix3 &aMatrix,
                                                      const XFcVector2 &aOffset);
    //! Creates a scaling matrix.
    XFCIMPORT static XFcMatrix3 & matrixScaling2D(XFcMatrix3 &aMatrix, REAL aScale);
    //! Translates a matrix by offset.
    XFCIMPORT static XFcMatrix3 & matrixTranslate2D(XFcMatrix3 &aMatrix,
                                                    const XFcVector2 &aOffset);
    //! Scales a matrix by a value.
    XFCIMPORT static XFcMatrix3 & matrixScale2D(XFcMatrix3 &aMatrix, REAL aScale);

    //! Transforms a vector by a matrix.
    XFCIMPORT static void matrixTransform2D(const XFcMatrix3 &aMatrix,
                                            const XFcVector2 &aSrc,
                                            XFcVector2 &aDst);
    //! Inverses a matrix. Handles only 2D affine transformation.
    XFCIMPORT static XFcMatrix3 & matrixInverseAffine2D(XFcMatrix3 &aMatrix);
    //! Inverses a matrix. Handles only 2D rotation and translation.
    XFCIMPORT static XFcMatrix3 & matrixInverseFast2D(XFcMatrix3 &aMatrix);

#if defined(XFC_USE_FLOAT)

    //! Removes any fractional part from the value.
    XFCIMPORT static FLOAT32 floor(FLOAT32 aArg);
    //! Rounds the value up to the next larger integer.
    XFCIMPORT static FLOAT32 ceil(FLOAT32 aArg);
    //! Calculates square of the value.
    XFCIMPORT static FLOAT32 sqr(FLOAT32 aArg);
    //! Calculates square root of the value.
    XFCIMPORT static FLOAT32 sqrt(FLOAT32 aArg);
    //! Calculates square root of the value, sacrificing accuracy for speed.
    XFCIMPORT static FLOAT32 sqrtFast(FLOAT32 value);
    //! Calculates sin of the value in radians.
    XFCIMPORT static FLOAT32 sin(FLOAT32 aArg);
    //! Calculates cos of the value in radians.
    XFCIMPORT static FLOAT32 cos(FLOAT32 aArg);
    //! Calculates cos of the value in radians.
    XFCIMPORT static FLOAT32 tan(FLOAT32 aArg);
    //! Calculates sin of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static FLOAT32 sinFast(FLOAT32 value);
    //! Calculates cos of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static FLOAT32 cosFast(FLOAT32 value);
    //! Calculates acos of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static FLOAT32 acosFast(FLOAT32 aArg);
    //! Returns the absolute value of the argument.
    XFCIMPORT static FLOAT32 abs(FLOAT32 aArg);
    //! Calculates the angle (in radians) of the X-axis and the point (x,y).
    XFCIMPORT static FLOAT32 atan2(FLOAT32 aY, FLOAT32 aX);
    //! Calculates the arcus tangent of argument.
    XFCIMPORT static FLOAT32 atan(FLOAT32 aArg);
    //! Calculates the arcus sin of argument.
    XFCIMPORT static FLOAT32 asin(FLOAT32 aArg);
    //! Calculates the arcus cos of argument.
    XFCIMPORT static FLOAT32 acos(FLOAT32 aArg);
    //! Calculates e raised to a power of the argument.
    XFCIMPORT static FLOAT32 exp(FLOAT32 aArg);
    //! Calculates the natural logarithm of the argument.
    XFCIMPORT static FLOAT32 log(FLOAT32 aArg);
    //! Calculates the natural logarithm of the argument, sacrificing accuracy for speed.
    XFCIMPORT static FLOAT32 logFast(FLOAT32 aArg);
    //! Calculates aBase raised to the power of aExponent
    XFCIMPORT static FLOAT32 pow(FLOAT32 aBase, FLOAT32 aExponent);

#else // or no XFC_USE_FLOAT

    //! Removes any fractional part from the value.
    XFCIMPORT static XFcFixed floor(XFcFixed aArg);
    //! Rounds the value up to the next larger integer.
    XFCIMPORT static XFcFixed ceil(XFcFixed aArg);
    //! Calculates square of the value.
    XFCIMPORT static XFcFixed sqr(XFcFixed aArg);
    //! Calculates square root of the value.
    XFCIMPORT static XFcFixed sqrt(XFcFixed aArg);
    //! Calculates square root of the value, sacrificing accuracy for speed.
    XFCIMPORT static XFcFixed sqrtFast(XFcFixed value);
    //! Calculates sin of the value in radians.
    XFCIMPORT static XFcFixed sin(XFcFixed aArg);
    //! Calculates cos of the value in radians.
    XFCIMPORT static XFcFixed cos(XFcFixed aArg);
    //! Calculates tan of the value in radians.
    XFCIMPORT static XFcFixed tan(XFcFixed aArg);
    //! Calculates sin of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static XFcFixed sinFast(XFcFixed value);
    //! Calculates cos of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static XFcFixed cosFast(XFcFixed value);
    //! Calculates acos of the value in radians, sacrificing accuracy for speed.
    XFCIMPORT static XFcFixed acosFast(XFcFixed aArg);
    //! Returns the absolute value of the argument.
    XFCIMPORT static XFcFixed abs(XFcFixed aArg);
    //! Calculates the angle (in radians) of the X-axis and the point (x,y).
    XFCIMPORT static XFcFixed atan2(XFcFixed aY, XFcFixed aX);
    //! Calculates the arcus tangent of argument.
    XFCIMPORT static XFcFixed atan(XFcFixed aArg);
    //! Calculates the arcus sin of argument.
    XFCIMPORT static XFcFixed asin(XFcFixed aArg);
    //! Calculates the arcus cos of argument.
    XFCIMPORT static XFcFixed acos(XFcFixed aArg);
    //! Calculates e raised to a power of the argument.
    XFCIMPORT static XFcFixed exp(XFcFixed aArg);
    //! Calculates the natural logarithm of the argument.
    XFCIMPORT static XFcFixed log(XFcFixed aArg);
    //! Calculates the natural logarithm of the argument, sacrificing accuracy for speed.
    XFCIMPORT static XFcFixed logFast(XFcFixed aArg);
    //! Calculates aBase raised to the power of aExponent
    XFCIMPORT static XFcFixed pow(XFcFixed aBase, XFcFixed aExponent);

#endif // no XFC_USE_FLOAT

};


#endif // !XFC_XFCMATH_H_INCLUDED

