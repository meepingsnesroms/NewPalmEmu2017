/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XFcQuaternion math
 * 
 * $Id: XFcQuaternion.h,v 1.16 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.16 $
 */

#ifndef XFC_MATH_QUATERNION_H_INCLUDED
#define XFC_MATH_QUATERNION_H_INCLUDED

#include <xfcore/XFcVector.h>


//! Quaternion class.
/*!
 * Provides tools to store and manipulate rotation stored into a quaternion.
 * \sa XFcMath
 */
class XFcQuaternion 
{
public:

    REAL x;     //!< X-component of the rotation.
    REAL y;     //!< Y-component of the rotation.
    REAL z;     //!< Z-component of the rotation.
    REAL w;     //!< W-component of the rotation.

    //! Empty constructor.
    XFcQuaternion() {}

    //! Copy constructor.
    XFcQuaternion(const XFcQuaternion &aQuat)
    {
        x = aQuat.x;
        y = aQuat.y;
        z = aQuat.z;
        w = aQuat.w;
    }

    //! Construction from a vector.
    XFcQuaternion(const XFcVector3 &aVec)
    {
        x = aVec.x;
        y = aVec.y;
        z = aVec.z;
        w = 0;
    }

    //! Construction from 4 values.
    XFcQuaternion(const REAL aX, const REAL aY, const REAL aZ, const REAL aW) :
        x(aX), y(aY), z(aZ), w(aW) {}

    //! Adds components of another quaternion to this quaternion.
    /*! \param aQuat quaternion to be added to this quaternion.
     * \return reference to this quaternion.
     */
    inline XFcQuaternion & operator+=(const XFcQuaternion &aQuat);

    //! Creates a new quaternion which contains the result of this + another quaternion.
    /*! \param aQuat quaternion to be added to this quaternion.
     * \return A new quaternion containing the result.
     */
    inline XFcQuaternion operator+(const XFcQuaternion &aQuat) const;


    //! Substracts components of another quaternion from this quaternion.
    /*! \param aQuat quaternion to be substracted from this quaternion.
     * \return reference to this quaternion.
     */
    inline XFcQuaternion & operator-=(const XFcQuaternion &aQuat);

    //! Creates a new quaternion which contains the result of this - another quaternion.
    /*! \param aQuat quaternion to be substracted from this quaternion.
     * \return A new quaternion containing the result.
     */
    inline XFcQuaternion operator-(const XFcQuaternion &aQuat) const;


    //! Multiplies this quaternion by an INT32.
    inline XFcQuaternion operator*=(const INT32 aArg);
    //! Multiplies this quaternion by a FLOAT32.
    inline XFcQuaternion operator*=(const FLOAT32 aArg);

    //! Creates a new quaternion which contains the result of this * INT32.
    inline XFcQuaternion operator*(const INT32 aArg) const;
    //! Creates a new quaternion which contains the result of this * FLOAT32.
    inline XFcQuaternion operator*(const FLOAT32 aArg) const;
    //! Creates a new quaternion which contains the result of INT32 * this.
    friend XFcQuaternion operator*(const INT32 aArg, const XFcQuaternion &aQuat);
    //! Creates a new quaternion which contains the result of FLOAT32 * this.
    friend XFcQuaternion operator*(const FLOAT32 aArg, const XFcQuaternion &aQuat);

    //! Divides this quaternion by an INT32.
    inline XFcQuaternion operator/=(const INT32 aArg);
    //! Divides this quaternion by an FLOAT32.
    inline XFcQuaternion operator/=(const FLOAT32 aArg);

    //! Creates a new quaternion which contains the result of this / INT32.
    inline XFcQuaternion operator/(const INT32 aArg) const;
    //! Creates a new quaternion which contains the result of this / FLOAT32.
    inline XFcQuaternion operator/(const FLOAT32 aArg) const;
    //! Creates a new quaternion which contains the result of INT32 / this.
    friend XFcQuaternion operator/(const INT32 aArg, const XFcQuaternion &aQuat);
    //! Creates a new quaternion which contains the result of FLOAT32 / this.
    friend XFcQuaternion operator/(const FLOAT32 aArg, const XFcQuaternion &aQuat);

#ifndef XFC_NO_REAL_OPERATORS
    inline XFcQuaternion operator*=(const REAL &aArg);
    inline XFcQuaternion operator*(const REAL &aArg) const;
    friend XFcQuaternion operator*(const REAL &aArg, const XFcQuaternion &aQuat);
    inline XFcQuaternion operator/=(const REAL &aArg);
    inline XFcQuaternion operator/(const REAL &aArg) const;
    friend XFcQuaternion operator/(const REAL &aArg, const XFcQuaternion &aQuat);
#endif

    //! Multiplication with another quaternion.
    inline XFcQuaternion operator*(const XFcQuaternion &aQuat) const;
    //! Multiplication with another quaternion.
    inline XFcQuaternion & operator*=(const XFcQuaternion &aQuat);
    //! Division with another quaternion.
    inline XFcQuaternion operator/(const XFcQuaternion &aQuat) const;
    //! Division with another quaternion.
    inline XFcQuaternion & operator/=(const XFcQuaternion &aQuat);

    //! Calculates the normal of the quaterion (x^2+y^2+z^2+w^2).
    inline REAL normal();
    //! Calculates the length of the quaternion.
    inline REAL length();

    //! Normalizes a quaternion to unit length.
    /*! \note Matrix conversion requires unit quaternions.
     */
    inline void normalize();

    //! Conjugates the quaternion (negates x,y,z).
    inline void conjugate();

    //! Inverses the quaternion (q^-1 = q^* / N(q)).
    inline void inverse();
};


XFcQuaternion & XFcQuaternion::operator+=(const XFcQuaternion &aQuat)
{
    x += aQuat.x;
    y += aQuat.y;
    z += aQuat.z;
    w += aQuat.w;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator+(const XFcQuaternion &aQuat) const
{
    return XFcQuaternion(x + aQuat.x, y + aQuat.y, z + aQuat.z, w + aQuat.w);
}


XFcQuaternion & XFcQuaternion::operator-=(const XFcQuaternion &aQuat)
{
    x -= aQuat.x;
    y -= aQuat.y;
    z -= aQuat.z;
    w -= aQuat.w;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator-(const XFcQuaternion &aQuat) const
{
    return XFcQuaternion(x - aQuat.x, y - aQuat.y, z - aQuat.z, w - aQuat.w);
}


inline XFcQuaternion XFcQuaternion::operator*=(const INT32 aArg)
{
    x *= aArg;
    y *= aArg;
    z *= aArg;
    w *= aArg;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator*=(const FLOAT32 aArg)
{
    x *= aArg;
    y *= aArg;
    z *= aArg;
    w *= aArg;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator/=(const INT32 aArg)
{
    x /= aArg;
    y /= aArg;
    z /= aArg;
    w /= aArg;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator/=(const FLOAT32 aArg)
{
    x /= aArg;
    y /= aArg;
    z /= aArg;
    w /= aArg;
    return *this;
}


#ifndef XFC_NO_REAL_OPERATORS

inline XFcQuaternion XFcQuaternion::operator*=(const REAL &aArg)
{
    x *= aArg;
    y *= aArg;
    z *= aArg;
    w *= aArg;
    return *this;
}

inline XFcQuaternion XFcQuaternion::operator*(const REAL &aArg) const
{
    return XFcQuaternion(x * aArg, y * aArg, z * aArg, w * aArg);
}

inline XFcQuaternion XFcQuaternion::operator/=(const REAL &aArg)
{
    x /= aArg;
    y /= aArg;
    z /= aArg;
    w /= aArg;
    return *this;
}

inline XFcQuaternion XFcQuaternion::operator/(const REAL &aArg) const
{
    return XFcQuaternion(x / aArg, y / aArg, z / aArg, w / aArg);
}

inline XFcQuaternion operator*(const REAL &aArg, const XFcQuaternion &aQuat)
{
    return aQuat * aArg;
}

#else // or no XFC_NO_REAL_OPERATORS

inline XFcQuaternion XFcQuaternion::operator/(const FLOAT32 aArg) const
{
    return XFcQuaternion(x / aArg, y / aArg, z / aArg, w / aArg);
}

#endif // no XFC_NO_REAL_OPERATORS


inline XFcQuaternion XFcQuaternion::operator*(const INT32 aArg) const
{
    return XFcQuaternion(x * aArg, y * aArg, z * aArg, w * aArg);
}

inline XFcQuaternion XFcQuaternion::operator*(const FLOAT32 aArg) const
{
    return XFcQuaternion(x * aArg, y * aArg, z * aArg, w * aArg);
}

inline XFcQuaternion operator*(const INT32 aArg, const XFcQuaternion &aQuat)
{
    return aQuat * aArg;
}

inline XFcQuaternion operator*(const FLOAT32 aArg, const XFcQuaternion &aQuat)
{
    return aQuat * aArg;
}

inline XFcQuaternion & XFcQuaternion::operator*=(const XFcQuaternion &aQuat) 
{
    *this = *this * aQuat;
    return *this;
}


//! \note XFcQuaternion multiplication is non-commutative, ie. q1*q2 != q2*q1.
inline XFcQuaternion XFcQuaternion::operator*(const XFcQuaternion &aQuat) const
{
    XFcQuaternion res;

    REAL A, B, C, D, E, F, G, H;

    A = (w + x) * (aQuat.w + aQuat.x);
    B = (z - y) * (aQuat.y - aQuat.z);
    C = (w - x) * (aQuat.y + aQuat.z); 
    D = (y + z) * (aQuat.w - aQuat.x);
    E = (x + z) * (aQuat.x + aQuat.y);
    F = (x - z) * (aQuat.x - aQuat.y);
    G = (w + y) * (aQuat.w - aQuat.z);
    H = (w - y) * (aQuat.w + aQuat.z);

    res.w = B + (-E - F + G + H) / 2;
    res.x = A - (E + F + G + H) / 2; 
    res.y = C + (E - F + G - H) / 2; 
    res.z = D + (E - F - G + H) / 2;

    return res;
}


inline XFcQuaternion & XFcQuaternion::operator/=(const XFcQuaternion &aQuat) 
{
    *this = *this / aQuat;
    return *this;
}


inline XFcQuaternion XFcQuaternion::operator/(const XFcQuaternion &aQuat) const
{
    XFcQuaternion tQuat = aQuat;
    tQuat.inverse();
    XFcQuaternion res = *this;
    res = res * tQuat;
    return res;
}


inline REAL XFcQuaternion::normal()
{
    return ((x * x) + (y * y) + (z * z) + (w * w));
}


inline REAL XFcQuaternion::length()
{
    REAL norm = normal();
#ifndef XFC_USE_FLOAT
    // detect overflow
    if (norm < 0)
        norm.mValue = 0x7fffffff;
#endif
    return XFcMath::sqrt(norm);
}


inline void XFcQuaternion::normalize()
{
    REAL len = length();

    XFCASSERT(len != REALi(0));
    *this /= len;
}


/*! Conjugate of a quaternion is defined in the same way as with complex
 * numbers.
 */
inline void XFcQuaternion::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}


inline void XFcQuaternion::inverse()
{
    // q^-1 = q^* / N(q)

    REAL norm = normal();

    // inverse of zero quaternion is undefined
    XFCASSERT(norm != 0);

    conjugate();

    *this = *this / norm;
}


#endif // !XFC_MATH_QUATERNION_H_INCLUDED

