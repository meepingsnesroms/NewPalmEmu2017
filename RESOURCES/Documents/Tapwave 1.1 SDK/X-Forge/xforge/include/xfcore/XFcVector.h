/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Vector math header file
 * 
 * $Id: XFcVector.h,v 1.26.2.1 2004/01/09 13:35:14 kkallio Exp $
 * $Date: 2004/01/09 13:35:14 $
 * $Revision: 1.26.2.1 $
 */

#ifndef XFC_MATH_VECTOR_H_INCLUDED
#define XFC_MATH_VECTOR_H_INCLUDED


#include <xfcore/XFcFixed.h>

#ifdef XFC_USE_INTELGPP
#include <external/internal/gpp.h>
#endif


// disable warning C4514: unreferenced inline function has been removed
#ifdef _WIN32
#pragma warning ( disable : 4514 )
#endif


//! 4-Dimensional vector container.
/*!
 * \sa XFcMath
 */
class XFcVector4 
{
public:
    REAL x, y, z, w;

    XFcVector4() {}
    XFcVector4(REAL aX, REAL aY, REAL aZ, REAL aW) : x(aX), y(aY), z(aZ), w(aW) {}
};


//! 3-Dimensional vector.
/*! Typical vector operators implemented.
 * \sa XFcMath
 */
class XFcVector3 
{
public:

    //! The vector components.
    REAL x, y, z;

    //! Empty constructor.
    XFcVector3() {}
    //! Creation from 3 REALs.
    XFcVector3(REAL aX, REAL aY, REAL aZ) : x(aX), y(aY), z(aZ) {}

    //! Adds components of another vector to this vector.
    /*! \param aVec vector to be added to this vector.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator+=(const XFcVector3 &aVec);

    //! Adds components of another vector to this vector.
    /*! \param aVec vector to be added to this vector.
     * \return a new result vector.
     */
    inline XFcVector3 operator+(const XFcVector3 &aVec) const;

    //! Subtracts components of another vector from this vector.
    /*! \param aVec vector to be subtracted from this vector.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator-=(const XFcVector3 &aVec);

    //! Subtracts components of another vector from this vector.
    /*! \param aVec vector to be subtracted from this vector.
     * \return a new result vector.
     */
    inline XFcVector3 operator-(const XFcVector3 &aVec) const;

    //! Adds an integer value to each component of this vector.
    /*! \param aArg integer value for the addition.
     * \return a new result vector.
     */
    inline XFcVector3 operator+(const INT32 aArg) const;

    //! Subtracts an integer value from each component of this vector.
    /*! \param aArg integer value for the subtraction.
     * \return a new result vector.
     */
    inline XFcVector3 operator-(const INT32 aArg) const;

    //! Multiplies components of this vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator*=(const INT32 aArg);

    //! Multiplies components of this vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     * \return a new result vector.
     */
    inline XFcVector3 operator*(const INT32 aArg) const;

    //! Multiplies components of a vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     *  \param aVec vector to be multiplied.
     * \return a new result vector.
     */
    friend XFcVector3 operator*(const INT32 aArg, const XFcVector3 &aVec);

    //! Divides components of this vector with an integer value.
    /*! \param aArg integer value for the division.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator/=(const INT32 aArg);

    //! Divides components of this vector with an integer value.
    /*! \param aArg integer value for the division.
     * \return a new result vector.
     */
    inline XFcVector3 operator/(const INT32 aArg) const;

    //! Divides components of a vector with an integer value.
    /*! \param aArg integer value for the division.
     *  \param aVec vector to be divided.
     * \return a new result vector.
     */
    friend XFcVector3 operator/(const INT32 aArg, const XFcVector3 &aVec);

    //! Adds a REAL value to each component of this vector.
    /*! \param aArg value for the addition.
     * \return a new result vector.
     */
    inline XFcVector3 operator+(const REAL &aArg) const; 

    //! Subtracts a REAL value from each component of this vector.
    /*! \param aArg value for the subtraction.
     * \return a new result vector.
     */
    inline XFcVector3 operator-(const REAL &aArg) const; 

    //! Multiplies components of this vector with a REAL value.
    /*! \param aArg value for the multiplication.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator*=(const REAL &aArg);

    //! Multiplies components of this vector with a REAL value.
    /*! \param aArg value for the multiplication.
     * \return a new result vector.
     */
    inline XFcVector3 operator*(const REAL &aArg) const;

    //! Multiplies components of a vector with a REAL value.
    /*! \param aArg value for the multiplication.
     *  \param aVec vector to be multiplied.
     * \return a new result vector.
     */
    friend XFcVector3 operator*(const REAL &aArg, const XFcVector3 &aVec);

    //! Divides components of this vector with a REAL value.
    /*! \param aArg value for the division.
     * \return reference to this vector.
     */
    inline XFcVector3 & operator/=(const REAL &aArg);

    //! Divides components of this vector with a REAL value.
    /*! \param aArg integer value for the division.
     * \return a new result vector.
     */
    inline XFcVector3 operator/(const REAL &aArg) const;

    //! Divides components of a vector with a REAL value.
    /*! \param aArg value for the division.
     *  \param aVec vector to be divided.
     * \return a new result vector.
     */
    friend XFcVector3 operator/(const REAL &aArg, const XFcVector3 &aVec);

    //! Negates all components of this vector.
    /*! \return a new result vector.
     */
    inline XFcVector3 operator - () const { return XFcVector3(-x, -y, -z); }

    //! Returns dot product of this vector with an another vector.
    /*! \param aVec the other vector of the dot product.
     * \return dot product of the vectors.
     */
    inline REAL dotProduct(const XFcVector3 &aVec);

    //! Returns cross product of this vector with an another vector.
    /*! \param aVec the other vector of the cross product.
     * \return a new result vector which is the cross product of the vectors.
     */
    inline XFcVector3 crossProduct(const XFcVector3 &aVec);

    //! Returns length of this vector.
    /*! \sa lengthSq
     */
    inline REAL length();

    //! Returns squared length of this vector.
    /*! \note Calculating squared length is faster than calculating length.
     * \sa length
     */
    inline REAL lengthSq();

    //! Normalizes this vector.
    inline void normalize();

    //! Normalizes this vector. This is fast but has problems with large vectors.
    inline void normalizeFast();

    //! "Normalizes" this vector to length between 1 and 2. This can be used to make fixed point vector math safe.
    /*! \return the scale that the vector was multiplied with to get the pseudonormal length.
     */
    inline REAL pseudoNormalize();

};


XFcVector3 & XFcVector3::operator+=(const XFcVector3 &aVec)
{
    x += aVec.x;
    y += aVec.y;
    z += aVec.z;
    return *this;
}


inline XFcVector3 XFcVector3::operator+(const XFcVector3 &aVec) const
{
    return XFcVector3(x + aVec.x, y + aVec.y, z + aVec.z);
}


XFcVector3 & XFcVector3::operator-=(const XFcVector3 &aVec)
{
    x -= aVec.x;
    y -= aVec.y;
    z -= aVec.z;
    return *this;
}


inline XFcVector3 XFcVector3::operator-(const XFcVector3 &aVec) const
{
    return XFcVector3(x - aVec.x, y - aVec.y, z - aVec.z);
}


inline XFcVector3 XFcVector3::operator+(const INT32 aArg) const
{
    return XFcVector3(x + aArg, y + aArg, z + aArg);
}


inline XFcVector3 XFcVector3::operator-(const INT32 aArg) const
{
    return XFcVector3(x - aArg, y - aArg, z - aArg);
}


inline XFcVector3 & XFcVector3::operator*=(const INT32 aArg)
{
    x *= aArg;
    y *= aArg;
    z *= aArg;
    return *this;
}


inline XFcVector3 XFcVector3::operator*(const INT32 aArg) const
{
    return XFcVector3(x * aArg, y * aArg, z * aArg);
}


inline XFcVector3 operator*(const INT32 aArg, const XFcVector3 &aVec)
{
    return aVec * aArg;
}


inline XFcVector3 & XFcVector3::operator/=(const INT32 aArg)
{
    x /= aArg;
    y /= aArg;
    z /= aArg;
    return *this;
}


inline XFcVector3 XFcVector3::operator/(const INT32 aArg) const
{
    return XFcVector3(x / aArg, y / aArg, z / aArg);
}


inline XFcVector3 operator/(const INT32 aArg, const XFcVector3 &aVec)
{
    return aVec / aArg;
}


inline XFcVector3 XFcVector3::operator+(const REAL &aArg) const
{
    return XFcVector3(x + aArg, y + aArg, z + aArg);
}


inline XFcVector3 XFcVector3::operator-(const REAL &aArg) const
{
    return XFcVector3(x - aArg, y - aArg, z - aArg);
}


inline XFcVector3 & XFcVector3::operator*=(const REAL &aArg)
{
    x *= aArg;
    y *= aArg;
    z *= aArg;
    return *this;
}


inline XFcVector3 XFcVector3::operator*(const REAL &aArg) const
{
    return XFcVector3(x * aArg, y * aArg, z * aArg);
}


inline XFcVector3 operator*(const REAL &aArg, const XFcVector3 &aVec)
{
    return aVec * aArg;
}


inline XFcVector3 & XFcVector3::operator/=(const REAL &aArg)
{
    x /= aArg;
    y /= aArg;
    z /= aArg;
    return *this;
}


inline XFcVector3 XFcVector3::operator/(const REAL &aArg) const
{
    return XFcVector3(x / aArg, y / aArg, z / aArg);
}


inline XFcVector3 operator/(const REAL &aArg, const XFcVector3 &aVec)
{
    return aVec / aArg;
}


inline REAL XFcVector3::dotProduct(const XFcVector3 &aVec)
{
#ifdef XFC_USE_INTELGPP
    XFcFixed res;
    gppVec3DDot_16_32s((GPP_VEC3D *)this, (GPP_VEC3D *)&aVec, (I32 *)&res.mValue);
    return res;
#else
    return x * aVec.x + y * aVec.y + z * aVec.z;
#endif
}


inline XFcVector3 XFcVector3::crossProduct(const XFcVector3 &aVec)
{
#ifdef XFC_USE_INTELGPP
    XFcVector3 res;
    gppVec3DCross_16_32s((GPP_VEC3D *)this, (GPP_VEC3D *)&aVec, (GPP_VEC3D *)&res);
    return res;
#else
    REAL a, b, c;
    a = y * aVec.z - z * aVec.y;
    b = -(x * aVec.z - z * aVec.x);
    c = x * aVec.y - y * aVec.x;
    /*float a,b,c;
      a = (float)y * (float)aVec.z - (float)z * (float)aVec.y;
      b = -((float)x * (float)aVec.z - (float)z * (float)aVec.x);
      c = (float)x * (float)aVec.y - (float)y * (float)aVec.x;*/
    return XFcVector3(REAL(a), REAL(b), REAL(c));
#endif
}


inline REAL XFcVector3::length()
{
#ifdef XFC_USE_INTELGPP
    XFcFixed res;
    gppVec3DLength_16_32s((GPP_VEC3D *)this, (U32 *)&res.mValue);
    return res;
#else
    //return (REAL)sqrt(lengthSq());
    XFcVector3 tmp = *this;
    tmp.normalize();
    return dotProduct(tmp);
#endif
}


inline REAL XFcVector3::lengthSq()
{
#ifdef XFC_USE_INTELGPP
    XFcFixed res;
    gppVec3DLengthSq_16_32s((GPP_VEC3D *)this, (U32 *)&res.mValue);
    return res;
#else
    //float temp = (float)(x) * (float)(x) + (float)(y) * (float)(y) + (float)(z) * (float)(z);
    REAL temp = x * x + y * y + z * z;
    return REAL(temp);
#endif
}


inline void XFcVector3::normalizeFast()
{
#ifdef XFC_USE_INTELGPP
    gppVec3DNormalize_16_32s((GPP_VEC3D *)this);
#else
    REAL lenSq = lengthSq();
    if (lenSq > REALi(0))
    {
        lenSq = REALi(1) / XFcMath::sqrtFast(lenSq);
        *this *= lenSq;
    }
#endif
}


inline void XFcVector3::normalize()
{
#ifdef XFC_USE_INTELGPP
    gppVec3DNormalize_16_32s((GPP_VEC3D *)this);
#else
#ifdef XFC_USE_FLOAT
    REAL len = length();
    if (len != REALi(0))
        *this /= len;
#else
    pseudoNormalize();

    // The MSB of the largest component is at XFCFIXED_SHIFT, so the
    // diff will reach zero at the XFCFIXED_SHIFT'th iteration. However,
    // the length square may be one even before that, so the loop will
    // also terminate when that happens.
    INT32 rounds = 0;
    XFcFixed diffX = x, diffY = y, diffZ = z;
    while (rounds < XFCFIXED_SHIFT)
    {
        XFcFixed tmp = x*x + y*y + z*z;

        //halve the diff
        diffX.mValue >>= 1;
        diffY.mValue >>= 1;
        diffZ.mValue >>= 1;

        if (tmp.mValue > (1 << XFCFIXED_SHIFT))
        {
            // value is larger than one, so subtract the diff
            x.mValue -= diffX.mValue;
            y.mValue -= diffY.mValue;
            z.mValue -= diffZ.mValue;
        }
        else if (tmp.mValue < (1 << XFCFIXED_SHIFT))
        {
            // value is larger than one, so add the diff
            x.mValue += diffX.mValue;
            y.mValue += diffY.mValue;
            z.mValue += diffZ.mValue;
        }
        else
            rounds = XFCFIXED_SHIFT;

        rounds++;
    }
#endif
#endif
/*
    float length = (float)sqrt(float(x) * float(x) +
                               float(y) * float(y) +
                               float(z) * float(z));
    if (length != 0)
    {
        *this /= length;
    }
*/
}


inline REAL XFcVector3::pseudoNormalize()
{
#ifdef XFC_USE_FLOAT
    REAL len = length();
    if (len != REALi(0))
    {
        REAL scale = REALf(1) / len;
        *this *= scale;
        return scale;
    }
    return REALf(1);
#else
    INT32 bits;
    if (x.mValue < 0)
        bits = -x.mValue;
    else
        bits = x.mValue;

    if (y.mValue < 0)
        bits |= -y.mValue;
    else
        bits |= y.mValue;

    if (z.mValue < 0)
        bits |= -z.mValue;
    else
        bits |= z.mValue;

    // get the position of most significant bit
    INT32 pos = 0;
    INT32 mask = 0xffff0000;
    if (bits & mask)
        pos += 16;

    mask = 0xff00 << pos;
    if (bits & mask)
        pos += 8;

    mask = 0xf0 << pos;
    if (bits & mask)
        pos += 4;

    mask = 0xc << pos;
    if (bits & mask)
        pos += 2;

    mask = 0x2 << pos;
    if (bits & mask)
        pos += 1;

    // shift values so that longest component is between 1 and 2
    REAL scale;
    if (pos < XFCFIXED_SHIFT)
    {
        INT32 shift = XFCFIXED_SHIFT - pos;
        x.mValue = x.mValue << shift;
        y.mValue = y.mValue << shift;
        z.mValue = z.mValue << shift;
        scale.mValue = (1 << XFCFIXED_SHIFT) << shift;
    }
    else
    {
        INT32 shift = pos - XFCFIXED_SHIFT;
        x.mValue = x.mValue >> shift;
        y.mValue = y.mValue >> shift;
        z.mValue = z.mValue >> shift;
        scale.mValue = (1 << XFCFIXED_SHIFT) >> shift;
    }
    return scale;
#endif
}


//! 2-Dimensional vector.
/*! Typical vector operators implemented.
 * \sa XFcVector3
 */
class XFcVector2 
{
public:
    REAL x, y;

    XFcVector2() {}
    XFcVector2(REAL aX, REAL aY) : x(aX), y(aY) {}

    //! Adds components of another vector to this vector.
    /*! \param aVec vector to be added to this vector.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator+=(const XFcVector2 &aVec);

    //! Adds components of another vector to this vector.
    /*! \param aVec vector to be added to this vector.
     * \return a new result vector.
     */
    inline XFcVector2 operator+(const XFcVector2 &aVec) const;

    //! Subtracts components of another vector from this vector.
    /*! \param aVec vector to be subtracted from this vector.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator-=(const XFcVector2 &aVec);

    //! Subtracts components of another vector from this vector.
    /*! \param aVec vector to be subtracted from this vector.
     * \return a new result vector.
     */
    inline XFcVector2 operator-(const XFcVector2 &aVec) const;

    //! Adds an integer value to each component of this vector.
    /*! \param aArg integer value for the addition.
     * \return a new result vector.
     */
    inline XFcVector2 operator+(const INT32 aArg) const;

    //! Subtracts an integer value from each component of this vector.
    /*! \param aArg integer value for the subtraction.
     * \return a new result vector.
     */
    inline XFcVector2 operator-(const INT32 aArg) const;

    //! Multiplies components of this vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator*=(const INT32 aArg);

    //! Multiplies components of this vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     * \return a new result vector.
     */
    inline XFcVector2 operator*(const INT32 aArg) const;

    //! Multiplies components of a vector with an integer value.
    /*! \param aArg integer value for the multiplication.
     *  \param aVec vector to be multiplied.
     * \return a new result vector.
     */
    friend XFcVector2 operator*(const INT32 aArg, const XFcVector2 &aVec);

    //! Divides components of this vector with an integer value.
    /*! \param aArg integer value for the division.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator/=(const INT32 aArg);

    //! Divides components of this vector with an integer value.
    /*! \param aArg integer value for the division.
     * \return a new result vector.
     */
    inline XFcVector2 operator/(const INT32 aArg) const;

    //! Divides components of a vector with an integer value.
    /*! \param aArg integer value for the division.
     *  \param aVec vector to be divided.
     * \return a new result vector.
     */
    friend XFcVector2 operator/(const INT32 aArg, const XFcVector2 &aVec);

    //! Adds a REAL value to each component of this vector.
    /*! \param aArg value for the addition.
     * \return a new result vector.
     */
    inline XFcVector2 operator+(const REAL &aArg) const; 

    //! Subtracts a REAL value from each component of this vector.
    /*! \param aArg value for the subtraction.
     * \return a new result vector.
     */
    inline XFcVector2 operator-(const REAL &aArg) const; 

    //! Multiplies components of this vector with a REAL value.
    /*! \param aArg value for the multiplication.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator*=(const REAL &aArg);

    //! Multiplies components of this vector with a REAL value.
    /*! \param aArg value for the multiplication.
     * \return a new result vector.
     */
    inline XFcVector2 operator*(const REAL &aArg) const;

    //! Multiplies components of a vector with a REAL value.
    /*! \param aArg value for the multiplication.
     *  \param aVec vector to be multiplied.
     * \return a new result vector.
     */
    friend XFcVector2 operator*(const REAL &aArg, const XFcVector2 &aVec);

    //! Divides components of this vector with a REAL value.
    /*! \param aArg value for the division.
     * \return reference to this vector.
     */
    inline XFcVector2 & operator/=(const REAL &aArg);

    //! Divides components of this vector with a REAL value.
    /*! \param aArg integer value for the division.
     * \return a new result vector.
     */
    inline XFcVector2 operator/(const REAL &aArg) const;

    //! Divides components of a vector with a REAL value.
    /*! \param aArg value for the division.
     *  \param aVec vector to be divided.
     * \return a new result vector.
     */
    friend XFcVector2 operator/(const REAL &aArg, const XFcVector2 &aVec);

    //! Negates all components of this vector.
    /*! \return a new result vector.
     */
    inline XFcVector2 operator - () const { return XFcVector2(-x, -y); }

    //! Returns dot product of this vector with an another vector.
    /*! \param aVec the other vector of the dot product.
     * \return dot product of the vectors.
     */
    inline REAL dotProduct(const XFcVector2 &aVec);

    //! Returns length of this vector.
    /*! \sa lengthSq
     */
    inline REAL length();

    //! Returns squared length of this vector.
    /*! \note Calculating squared length is faster than calculating length.
     * \sa length
     */
    inline REAL lengthSq();

    //! Normalizes this vector.
    inline void normalize();

    //! Normalizes this vector. This is fast but has problems with large vectors.
    inline void normalizeFast();

    //! "Normalizes" this vector to length between 1 and 2. This can be used to make fixed point vector math safe.
    /*! \return the scale that the vector was multiplied with to get the pseudonormal length.
     */
    inline REAL pseudoNormalize();
};


XFcVector2 & XFcVector2::operator+=(const XFcVector2 &aVec)
{
    x += aVec.x;
    y += aVec.y;
    return *this;
}


inline XFcVector2 XFcVector2::operator+(const XFcVector2 &aVec) const
{
    return XFcVector2(x + aVec.x, y + aVec.y);
}


XFcVector2 & XFcVector2::operator-=(const XFcVector2 &aVec)
{
    x -= aVec.x;
    y -= aVec.y;
    return *this;
}


inline XFcVector2 XFcVector2::operator-(const XFcVector2 &aVec) const
{
    return XFcVector2(x - aVec.x, y - aVec.y);
}


inline XFcVector2 XFcVector2::operator+(const INT32 aArg) const
{
    return XFcVector2(x + aArg, y + aArg);
}


inline XFcVector2 XFcVector2::operator-(const INT32 aArg) const
{
    return XFcVector2(x - aArg, y - aArg);
}


inline XFcVector2 & XFcVector2::operator*=(const INT32 aArg)
{
    x *= aArg;
    y *= aArg;
    return *this;
}


inline XFcVector2 XFcVector2::operator*(const INT32 aArg) const
{
    return XFcVector2(x * aArg, y * aArg);
}


inline XFcVector2 operator*(const INT32 aArg, const XFcVector2 &aVec)
{
    return aVec * aArg;
}


inline XFcVector2 & XFcVector2::operator/=(const INT32 aArg)
{
    x /= aArg;
    y /= aArg;
    return *this;
}


inline XFcVector2 XFcVector2::operator/(const INT32 aArg) const
{
    return XFcVector2(x / aArg, y / aArg);
}


inline XFcVector2 operator/(const INT32 aArg, const XFcVector2 &aVec)
{
    return aVec / aArg;
}


inline XFcVector2 XFcVector2::operator+(const REAL &aArg) const
{
    return XFcVector2(x + aArg, y + aArg);
}


inline XFcVector2 XFcVector2::operator-(const REAL &aArg) const
{
    return XFcVector2(x - aArg, y - aArg);
}


inline XFcVector2 & XFcVector2::operator*=(const REAL &aArg)
{
    x *= aArg;
    y *= aArg;
    return *this;
}


inline XFcVector2 XFcVector2::operator*(const REAL &aArg) const
{
    return XFcVector2(x * aArg, y * aArg);
}


inline XFcVector2 operator*(const REAL &aArg, const XFcVector2 &aVec)
{
    return aVec * aArg;
}


inline XFcVector2 & XFcVector2::operator/=(const REAL &aArg)
{
    x /= aArg;
    y /= aArg;
    return *this;
}


inline XFcVector2 XFcVector2::operator/(const REAL &aArg) const
{
    return XFcVector2(x / aArg, y / aArg);
}


inline XFcVector2 operator/(const REAL &aArg, const XFcVector2 &aVec)
{
    return aVec / aArg;
}


inline REAL XFcVector2::dotProduct(const XFcVector2 &aVec)
{
    return x * aVec.x + y * aVec.y;
}


inline REAL XFcVector2::length()
{
    XFcVector2 tmp = *this;
    tmp.normalize();
    return dotProduct(tmp);
}


inline REAL XFcVector2::lengthSq()
{
    //float temp = (float)(x)*(float)(x) + (float)(y)*(float)(y) + (float)(z)*(float)(z);
    REAL temp = x * x + y * y;
    return REAL(temp);
}


inline void XFcVector2::normalizeFast()
{
    REAL lenSq = lengthSq();
    if (lenSq > REALi(0))
    {
        lenSq = REALi(1) / XFcMath::sqrtFast(lenSq);
        *this *= lenSq;
    }
}


inline void XFcVector2::normalize()
{
#ifdef XFC_USE_FLOAT
    REAL len = length();
    if (len != REALi(0))
        *this /= len;
#else
    pseudoNormalize();

    // The MSB of the largest component is at XFCFIXED_SHIFT, so the
    // diff will reach zero at the XFCFIXED_SHIFT'th iteration. However,
    // the length square may be one even before that, so the loop will
    // also terminate when that happens.
    INT32 rounds = 0;
    XFcFixed diffX = x, diffY = y;
    while (rounds < XFCFIXED_SHIFT)
    {
        XFcFixed tmp = x*x + y*y;

        //halve the diff
        diffX.mValue >>= 1;
        diffY.mValue >>= 1;

        if (tmp.mValue > (1 << XFCFIXED_SHIFT))
        {
            // value is larger than one, so subtract the diff
            x.mValue -= diffX.mValue;
            y.mValue -= diffY.mValue;
        }
        else if (tmp.mValue < (1 << XFCFIXED_SHIFT))
        {
            // value is larger than one, so add the diff
            x.mValue += diffX.mValue;
            y.mValue += diffY.mValue;
        }
        else
            rounds = XFCFIXED_SHIFT;

        rounds++;
    }
#endif
}


inline REAL XFcVector2::pseudoNormalize()
{
#ifdef XFC_USE_FLOAT
    REAL len = length();
    if (len != REALi(0))
    {
        REAL scale = REALf(1) / len;
        *this *= scale;
        return scale;
    }
    return REALf(1);
#else
    INT32 bits;
    if (x.mValue < 0)
        bits = -x.mValue;
    else
        bits = x.mValue;

    if (y.mValue < 0)
        bits |= -y.mValue;
    else
        bits |= y.mValue;

    // get the position of most significant bit
    INT32 pos = 0;
    INT32 mask = 0xffff0000;
    if (bits & mask)
        pos += 16;

    mask = 0xff00 << pos;
    if (bits & mask)
        pos += 8;

    mask = 0xf0 << pos;
    if (bits & mask)
        pos += 4;

    mask = 0xc << pos;
    if (bits & mask)
        pos += 2;

    mask = 0x2 << pos;
    if (bits & mask)
        pos += 1;

    // shift values so that longest component is between 1 and 2
    REAL scale;
    if (pos < XFCFIXED_SHIFT)
    {
        INT32 shift = XFCFIXED_SHIFT - pos;
        x.mValue = x.mValue << shift;
        y.mValue = y.mValue << shift;
        scale.mValue = (1 << XFCFIXED_SHIFT) << shift;
    }
    else
    {
        INT32 shift = pos - XFCFIXED_SHIFT;
        x.mValue = x.mValue >> shift;
        y.mValue = y.mValue >> shift;
        scale.mValue = (1 << XFCFIXED_SHIFT) >> shift;
    }
    return scale;
#endif
}

#endif // !XFC_MATH_VECTOR_H_INCLUDED

