/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Matrix math
 * 
 * $Id: XFcMatrix.h,v 1.14 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.14 $
 */

#ifndef XFC_MATH_MATRIX_H_INCLUDED
#define XFC_MATH_MATRIX_H_INCLUDED


#include <xfcore/XFcVector.h>

#ifdef XFC_USE_INTELGPP
#include <external/internal/gpp.h>
#endif


// disable warning C4514: unreferenced inline function has been removed
#ifdef _WIN32
#pragma warning ( disable : 4514 )
#endif

class XFcMatrix3;


//! 4 by 4 matrix.
/*!
 * \sa XFcMath
 */
class XFcMatrix4 
{
public:
    //! The contents of the 4x4 matrix in row-major order.
    REAL m[4][4];

    //! Empty constructor.
    XFcMatrix4() {}
    
    //! Copy-constructor.
    XFcMatrix4(const XFcMatrix4 &aMatrix)
    {
        memcpy(m, aMatrix.m, sizeof(REAL) * 4 * 4);
    }

    //! Creation from an array of REALs.
    XFcMatrix4(const REAL aMatrix[4][4])
    {
        memcpy(m, aMatrix, sizeof(REAL) * 4 * 4);
    }

    //! Creation from a 3x3 matrix.
    XFcMatrix4(const XFcMatrix3 &aMatrix);
    //! Creation from an orientation matrix and a position vector.
    XFcMatrix4(const XFcMatrix3 &aMatrix, const XFcVector3 &aVector);

    //! Multiplies this matrix with an another matrix.
    inline XFcMatrix4 & operator*=(const XFcMatrix4 &aMatrix);
    //! Multiplies this matrix with a REAL.
    inline XFcMatrix4 & operator*=(const REAL &aArg);
    //! Multiplies this matrix with an int.
    inline XFcMatrix4 & operator*=(int aArg);
    //! Multiplies this matrix with a float.
    inline XFcMatrix4 & operator*=(float aArg);

    //! Creates a new matrix which contains the result of matrix * matrix operation.
    inline XFcMatrix4 operator*(const XFcMatrix4 &aMatrix) const;
    //! Creates a new matrix which contains the result of this * REAL.
    inline XFcMatrix4 operator*(const REAL &aArg) const;
    //! Creates a new matrix which contains the result of this * int.
    inline XFcMatrix4 operator*(int aArg) const;
    //! Creates a new matrix which contains the result of this * float.
    inline XFcMatrix4 operator*(float aArg) const;
};


//! 3 by 3 matrix.
/*!
 * \sa XFcMath
 */
class XFcMatrix3 
{
public:
    //! The contents of the matrix in row-major order.
    REAL m[3][3];

    //! Empty constructor.
    XFcMatrix3() {}

    //! Copy-constructor.
    XFcMatrix3(const XFcMatrix3 &aMatrix)
    {
        memcpy(m, aMatrix.m, sizeof(REAL) * 3 * 3);
    }

    //! Creation from an array of REALs.
    XFcMatrix3(const REAL aMatrix[3][3])
    {
        memcpy(m, aMatrix, sizeof(REAL) * 3 * 3);
    }

    //! Creation from a 4x4 matrix.
    XFcMatrix3(const XFcMatrix4 &aMatrix)
    {
        INT i, j;
        for (i = 0; i < 3; ++i)
        {
            for (j = 0; j < 3; ++j)
            {
                m[i][j] = aMatrix.m[i][j];
            }
        }
    }

    //! Multiplies this matrix with an another matrix.
    inline XFcMatrix3 & operator*=(const XFcMatrix3 &aMatrix);
    //! Multiplies this matrix with a REAL.
    inline XFcMatrix3 & operator*=(const REAL &aArg);
    //! Multiplies this matrix with an int.
    inline XFcMatrix3 & operator*=(int aArg);
    //! Multiplies this matrix with a float.
    inline XFcMatrix3 & operator*=(float aArg);

    //! Creates a new matrix which contains the result of matrix * matrix operation.
    inline XFcMatrix3 operator*(const XFcMatrix3 &aMatrix) const;
    //! Creates a new matrix which contains the result of this * REAL.
    inline XFcMatrix3 operator*(const REAL &aArg) const;
    //! Creates a new matrix which contains the result of this * int.
    inline XFcMatrix3 operator*(int aArg) const;
    //! Creates a new matrix which contains the result of this * float.
    inline XFcMatrix3 operator*(float aArg) const;
};


inline XFcMatrix4 & XFcMatrix4::operator*=(const XFcMatrix4 &aMatrix) 
{
    *this = *this * aMatrix;
    return *this;
}


#ifndef XFC_NO_REAL_OPERATORS

inline XFcMatrix4 & XFcMatrix4::operator*=(const REAL &aArg)
{
    *this = *this * aArg;
    return *this;
}

inline XFcMatrix4 & XFcMatrix4::operator*=(const float aArg)
{
    *this = *this * aArg;
    return *this;
}

#endif


inline XFcMatrix4 & XFcMatrix4::operator*=(const int aArg)
{
    *this = *this * aArg;
    return *this;
}


inline XFcMatrix4 XFcMatrix4::operator*(const XFcMatrix4 &aMatrix) const
{
#ifdef XFC_USE_INTELGPP
    XFcMatrix4 res;
    gppMatrix4X4Mul_16_32s(*(GPP_MATRIX4X4 *)&this->m, *(GPP_MATRIX4X4 *)&aMatrix.m, *(GPP_MATRIX4X4 *)&res.m);
    return res;
#else
    XFcMatrix4 res;
    
    INT i, j;
    for (j = 0; j < 4; ++j)
        for (i = 0; i < 4; ++i)
            res.m[i][j] =
                m[i][0] * aMatrix.m[0][j] +
                m[i][1] * aMatrix.m[1][j] +
                m[i][2] * aMatrix.m[2][j] +
                m[i][3] * aMatrix.m[3][j];
    
    return res;
#endif
}


inline XFcMatrix4 XFcMatrix4::operator*(const REAL &aArg) const
{
    XFcMatrix4 result;
    INT i, j;

    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            result.m[i][j] = m[i][j] * aArg;

    return result;
}


inline XFcMatrix4 XFcMatrix4::operator*(int aArg) const
{
    return *this * (REAL)aArg;
}


inline XFcMatrix4 XFcMatrix4::operator*(float aArg) const
{
    return *this * (REAL)aArg;
}


inline XFcMatrix4::XFcMatrix4(const XFcMatrix3 &aMatrix)
{
    INT i, j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            m[i][j] = aMatrix.m[i][j];
        }
        m[i][3] = 0;
    }
    for (j = 0; j < 3; ++j)
        m[3][j] = 0;
    m[3][3] = 1;
}


inline XFcMatrix4::XFcMatrix4(const XFcMatrix3 &aMatrix, const XFcVector3 &aVector)
{
    INT i, j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            m[i][j] = aMatrix.m[i][j];
        }
        m[i][3] = 0;
    }
    m[3][0] = aVector.x;
    m[3][1] = aVector.y;
    m[3][2] = aVector.z;
    m[3][3] = 1;
}


inline XFcMatrix3 & XFcMatrix3::operator*=(const XFcMatrix3 &aMatrix) 
{
    *this = *this * aMatrix;
    return *this;
}


#ifndef XFC_NO_REAL_OPERATORS

inline XFcMatrix3 & XFcMatrix3::operator*=(const REAL &aArg)
{
    *this = *this * aArg;
    return *this;
}

inline XFcMatrix3 & XFcMatrix3::operator*=(const float aArg)
{
    *this = *this * aArg;
    return *this;
}

#endif


inline XFcMatrix3 & XFcMatrix3::operator*=(const int aArg)
{
    *this = *this * aArg;
    return *this;
}


inline XFcMatrix3 XFcMatrix3::operator*(const XFcMatrix3 &aMatrix) const
{
    XFcMatrix3 res;
    
    INT i, j;
    for (j = 0; j < 3; ++j)
        for (i = 0; i < 3; ++i)
            res.m[i][j] =
                m[i][0] * aMatrix.m[0][j] +
                m[i][1] * aMatrix.m[1][j] +
                m[i][2] * aMatrix.m[2][j];
    
    return res;
}


inline XFcMatrix3 XFcMatrix3::operator*(const REAL &aArg) const
{
    XFcMatrix3 result;
    INT i, j;

    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            result.m[i][j] = m[i][j] * aArg;

    return result;
}


inline XFcMatrix3 XFcMatrix3::operator*(int aArg) const
{
    return *this * (REAL)aArg;
}


inline XFcMatrix3 XFcMatrix3::operator*(float aArg) const
{
    return *this * (REAL)aArg;
}


#endif // !XFC_MATH_MATRIX_H_INCLUDED

