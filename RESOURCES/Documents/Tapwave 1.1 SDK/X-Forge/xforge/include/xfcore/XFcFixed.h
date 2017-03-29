/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Fixed point class
 * 
 * $Id: XFcFixed.h,v 1.30 2003/10/06 12:50:06 jari Exp $
 * $Date: 2003/10/06 12:50:06 $
 * $Revision: 1.30 $
 */

#ifndef XFC_CORE_FIXED_H_INCLUDED
#define XFC_CORE_FIXED_H_INCLUDED

#define HUGE_FLOAT (3.402823466e+38F)

#ifdef XFC_USE_INTELGPP
#include <external/internal/gpp.h>
#endif

#if !defined(XFC_PLATFORM_EPOC) && defined(XFC_USE_ARMASM)
#include <xfcore/XFcAsmFixedDiv.h>
#endif

// Disable VC warning C4514: unreferenced inline function has been removed.
#ifdef _WIN32
#pragma warning ( disable : 4514 )
#endif

// If you change these you must also change it on the assembly versions as well!
//! Fixed point position.
static const INT XFCFIXED_SHIFT = 16;
//! Fixed point lower part bitmask.
static const INT32 XFCFIXED_MASK = ((1 << XFCFIXED_SHIFT) - 1);
//! Fixed point scale.
static const FLOAT32 XFCFIXED_SCALE = 65536.0f;

#if defined(XFC_PLATFORM_EPOC)
#if defined(XFC_USE_ARMASM)
XFCIMPORT extern INT32 xfcFixedMul16x16(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedMul10x22(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedDiv16x16(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedDiv11x21(INT32 a, INT32 b);
#else
INT32 xfcFixedMul16x16(INT32 a, INT32 b);
INT32 xfcFixedMul10x22(INT32 a, INT32 b);
INT32 xfcFixedDiv16x16(INT32 a, INT32 b);
INT32 xfcFixedDiv11x21(INT32 a, INT32 b);
#endif
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Macros for fixed point multiplication & fixed point division.
//////////////////////////////////////////////////////////////////////////
// Since compiler inline depth seems (in some cases, at least) to be 1,
// we'll have to make div's and mul's as macros to make sure things
// inline correctly.

#if defined(XFC_PLATFORM_EPOC)

#define XFC_FIXEDMUL(a, b, c) c = xfcFixedMul16x16((a), (b));
#define XFC_FIXEDDIV(a, b, c) c = xfcFixedDiv16x16((a), (b));

#elif defined(XFC_USE_INTELGPP)

#define XFC_FIXEDMUL(a, b, c) gppMul_16_32s((I32)(a), (I32)(b), (I32 *)&(c));
#define XFC_FIXEDDIV(a, b, c) gppDiv_16_32s((I32)(a), (I32)(b), (I32 *)&(c));

#else

#define XFC_FIXEDMUL(a, b, c) { INT64 res = (INT64)(a) * (INT64)(b); c = (INT32)(res >> XFCFIXED_SHIFT); }
#define XFC_FIXEDDIV(a, b, c) { INT64 res = (INT64)(a) << XFCFIXED_SHIFT; res = res / (INT64)(b); c = (INT32)(res); }

#endif


//! Fixed math class, designed to work like a native type.
/*! Internally, the XFcFixed class uses 16.16 bit fixed point notation.
 *  Functionally it acts like a floating point value, and in most cases
 *  it is fully interchangeable with a float. Care has been taken to
 *  ensure proper inlining whenever neccessary, and expensive operations
 *  have assembler-optimized versions under ARM platforms.
 *  \note You should never store a XFcFixed value on disk, as the internal
 *        precision as well as byte order may differ from platform to platform.
 *        Convert to FLOAT32 and store that instead.
 */
class XFcFixed
{
public:
    INT32 mValue;

    // Constructors
    
    XFcFixed() {}
    XFcFixed(int aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(INT8 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(UINT8 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(INT16 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(UINT16 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(INT32 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(UINT32 aArg) { mValue = aArg << XFCFIXED_SHIFT; }
    XFcFixed(FLOAT32 aArg) {
        // mValue = INT32(aArg * XFCFIXED_SCALE);
        UINT32 tmp = *((UINT32 *)&aArg);
        INT32 exponent = ((tmp >> 23) & 0xff);
        if (exponent == 0)
            mValue = 0;
        else
        {
            UINT32 fraction = (tmp & ((1 << 23) - 1)) | (1 << 23);
            exponent = exponent - 127 - 23 + XFCFIXED_SHIFT;
            if (exponent < 0)
            {
                if (exponent <= -32)
                    mValue = 0;
                else
                    mValue = fraction >> -exponent;
            }
            else
            {
                if (exponent >= 32)
                    mValue = 0;
                else
                    mValue = fraction << exponent;
            }
            if (tmp & (1 << 31))
                mValue = -mValue;
        }
    }
    XFcFixed(FLOAT64 aArg) { mValue = INT32(aArg * XFCFIXED_SCALE); }
#ifndef XFC_CAN_DO_DIRECT_CAST
    // Used only if can't do static_cast
    XFcFixed(INT32 aArg, UINT32 /*aUnused*/) : mValue(aArg) {}
#endif
    /* This is needed with gcc-2.95.2 but is currently commented out since we
     * have moved to gcc-2.95.3, leave it here for now.
     */
    //XFcFixed(const XFcFixed &aSrc) { mValue = aSrc.getValue(); }

    // Cast operators.
    
    // From XFcFixed to type x.
    inline operator int() { return mValue >> XFCFIXED_SHIFT; }
    inline operator INT8() { return INT8(mValue >> XFCFIXED_SHIFT); }
    inline operator UINT8() { return UINT8(mValue >> XFCFIXED_SHIFT); }
    inline operator INT16() { return INT16(mValue >> XFCFIXED_SHIFT); }
    inline operator UINT16() { return UINT16(mValue >> XFCFIXED_SHIFT); }
    inline operator INT32() { return mValue >> XFCFIXED_SHIFT; }
    inline operator UINT32() { return mValue >> XFCFIXED_SHIFT; }
    //inline operator INT64() { return (INT64)(mValue >> XFCFIXED_SHIFT); }
    //inline operator UINT64() { return (UINT64)(mValue >> XFCFIXED_SHIFT); }
    inline operator FLOAT32() { return mValue / XFCFIXED_SCALE; }
    inline operator FLOAT64() { return mValue / XFCFIXED_SCALE; }

    // From type x to XFcFixed.
    inline XFcFixed operator()(int aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(INT8 aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(UINT8 aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(INT32 aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(UINT32 aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(FLOAT32 aArg) { return XFcFixed(aArg); }
    inline XFcFixed operator()(FLOAT64 aArg) { return XFcFixed(aArg); }

    // Arithmetic operators.
    
    /* This is needed with gcc-2.95.2 but is currently commented out since we
     * have moved to gcc-2.95.3, leave it here for now.
     */
    /*        
    XFcFixed & operator=(const XFcFixed &aRHS)
    {
        if (this != &aRHS)
            mValue = aRHS.getValue();
        return *this;
    }
    */

    inline XFcFixed & operator+=(const XFcFixed &aArg)
    {
        mValue += aArg.mValue;
        return *this;
    }
    
    inline XFcFixed & operator+=(int aArg)
    {
        mValue += aArg << XFCFIXED_SHIFT;
        return *this;
    }
    
    inline XFcFixed & operator+=(INT32 aArg)
    {
        mValue += aArg << XFCFIXED_SHIFT;
        return *this;
    }
    
    inline XFcFixed & operator+=(FLOAT32 aArg)
    {
        mValue += (INT32)(aArg * XFCFIXED_SCALE);
        return *this;
    }
    
    inline XFcFixed & operator+=(FLOAT64 aArg)
    {
        mValue += (INT32)(aArg * XFCFIXED_SCALE);
        return *this;
    }

    inline XFcFixed & operator-=(const XFcFixed &aArg)
    {
        mValue -= aArg.mValue;
        return *this;
    }
    
    inline XFcFixed & operator-=(int aArg)
    {
        mValue -= aArg << XFCFIXED_SHIFT;
        return *this;
    }
    
    inline XFcFixed & operator-=(INT32 aArg)
    {
        mValue -= aArg << XFCFIXED_SHIFT;
        return *this;
    }
    
    inline XFcFixed & operator-=(FLOAT32 aArg)
    {
        mValue -= (INT32)(aArg * XFCFIXED_SCALE);
        return *this;
    }
    
    inline XFcFixed & operator-=(FLOAT64 aArg)
    {
        mValue -= (INT32)(aArg * XFCFIXED_SCALE);
        return *this;
    }

    inline friend XFcFixed operator+(const XFcFixed &aFixed1, const XFcFixed &aFixed2);
    inline friend XFcFixed operator+(const XFcFixed &aFixed, int aArg);
    inline friend XFcFixed operator+(const XFcFixed &aFixed, INT32 aArg);
    inline friend XFcFixed operator+(const XFcFixed &aFixed, FLOAT32 aArg);
    inline friend XFcFixed operator+(const XFcFixed &aFixed, FLOAT64 aArg);
    inline friend XFcFixed operator+(int aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator+(INT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator+(FLOAT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator+(FLOAT64 aInt, const XFcFixed &aFixed);

    inline friend XFcFixed operator-(const XFcFixed &aFixed1, const XFcFixed &aFixed2);
    inline friend XFcFixed operator-(const XFcFixed &aFixed, int aArg);
    inline friend XFcFixed operator-(const XFcFixed &aFixed, INT32 aArg);
    inline friend XFcFixed operator-(const XFcFixed &aFixed, FLOAT32 aArg);
    inline friend XFcFixed operator-(const XFcFixed &aFixed, FLOAT64 aArg);
    inline friend XFcFixed operator-(int aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator-(INT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator-(FLOAT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator-(FLOAT64 aInt, const XFcFixed &aFixed);

#if defined(XFC_PLATFORM_EPOC) || defined(XFC_PLATFORM_LINUX)
    XFCIMPORT friend XFcFixed xfcFixedMul(const INT32 &a, const INT32 &b);
    XFCIMPORT friend XFcFixed xfcFixedDiv(const INT32 &a, const INT32 &b);
#endif

    inline XFcFixed & operator*=(const XFcFixed &aArg)
    {
        XFC_FIXEDMUL(mValue, aArg.mValue, mValue);
        return *this;
    }
    
    inline XFcFixed & operator*=(int aArg)
    {
        mValue *= aArg;
        return *this;
    }
    
    inline XFcFixed & operator*=(INT32 aArg)
    {
        mValue *= aArg;
        return *this;
    }
    
    inline XFcFixed & operator*=(FLOAT32 aArg)
    {
        XFC_FIXEDMUL(mValue, (INT32)(aArg * XFCFIXED_SCALE), mValue);
        return *this;
    }
    
    inline XFcFixed & operator*=(FLOAT64 aArg)
    {
        XFC_FIXEDMUL(mValue, (INT32)(aArg * XFCFIXED_SCALE), mValue);
        return *this;
    }

    inline XFcFixed operator*(const XFcFixed &aArg) const
    {
        XFcFixed temp;
        XFC_FIXEDMUL(mValue, aArg.mValue, temp.mValue);
        return temp;
    }

    inline XFcFixed operator*(int aArg) const
    {
        XFcFixed temp;
        temp.mValue = mValue * aArg;
        return temp;
    }
    
    inline XFcFixed operator*(INT32 aArg) const
    {
        XFcFixed temp;
        temp.mValue = mValue * aArg;
        return temp;
    }
    
    inline XFcFixed operator*(FLOAT32 aArg) const
    {
        XFcFixed temp;
        XFC_FIXEDMUL(mValue, (INT32)(aArg * XFCFIXED_SCALE), temp.mValue);
        return temp;
    }
    
    inline XFcFixed operator*(FLOAT64 aArg) const
    {
        XFcFixed temp;
        XFC_FIXEDMUL(mValue, (INT32)(aArg * XFCFIXED_SCALE), temp.mValue);
        return temp;
    }
    
    inline friend XFcFixed operator*(int aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator*(INT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator*(FLOAT32 aFloat, const XFcFixed &aFixed);
    inline friend XFcFixed operator*(FLOAT64 aDouble, const XFcFixed &aFixed);

    inline XFcFixed & operator/=(const XFcFixed &aArg)
    {
        XFC_FIXEDDIV(mValue, aArg.mValue, mValue);
        return *this;
    }
    
    inline XFcFixed & operator/=(int aArg)
    {
        mValue /= aArg;
        return *this;
    }
    
    inline XFcFixed & operator/=(INT32 aArg)
    {
        mValue /= aArg;
        return *this;
    }
    
    inline XFcFixed & operator/=(FLOAT32 aArg)
    {
        XFC_FIXEDDIV(mValue, (INT32)(aArg * XFCFIXED_SCALE), mValue);
        return *this;
    }
    
    inline XFcFixed & operator/=(FLOAT64 aArg)
    {
        XFC_FIXEDDIV(mValue, (INT32)(aArg * XFCFIXED_SCALE), mValue);
        return *this;
    }
    
    inline friend XFcFixed operator/(const XFcFixed &aArg1, const XFcFixed &aArg2);
    
    inline XFcFixed operator/(int aArg) const
    {
        XFcFixed temp;
        temp.mValue = mValue / aArg;
        return temp;
    }
    
    inline XFcFixed operator/(INT32 aArg) const
    {
        XFcFixed temp;
        temp.mValue = mValue / aArg;
        return temp;
    }
    
    inline XFcFixed operator/(FLOAT32 aArg) const
    {
        XFcFixed temp;
        XFC_FIXEDDIV(mValue, (INT32)(aArg * XFCFIXED_SCALE), temp.mValue);
        return temp;
    }
    
    inline XFcFixed operator/(FLOAT64 aArg) const
    {
        XFcFixed temp;
        XFC_FIXEDDIV(mValue, (INT32)(aArg * XFCFIXED_SCALE), temp.mValue);
        return temp;
    }
    
    inline friend XFcFixed operator/(int aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator/(INT32 aInt, const XFcFixed &aFixed);
    inline friend XFcFixed operator/(FLOAT32 aFloat, const XFcFixed &aFixed);
    inline friend XFcFixed operator/(FLOAT64 aDouble, const XFcFixed &aFixed);

    // Comparison
    
    inline INT32 operator==(const XFcFixed &aArg) const
    {
        return mValue == aArg.mValue;
    }
    
    inline INT32 operator==(int aArg) const
    {
        return mValue == (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator==(INT32 aArg) const
    {
        return mValue == (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator==(FLOAT32 aArg) const
    {
        return *this == (REAL)aArg;
    }
    
    inline INT32 operator==(FLOAT64 aArg) const
    {
        return *this == (REAL)aArg;
    }
    
    inline friend INT32 operator==(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator==(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator==(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator==(FLOAT64 aArg, const XFcFixed &aFixed);

    inline INT32 operator!=(const XFcFixed &aArg) const
    {
        return mValue != aArg.mValue;
    }
    
    inline INT32 operator!=(int aArg) const
    {
        return mValue != (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator!=(INT32 aArg) const
    {
        return mValue != (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator!=(FLOAT32 aArg) const
    {
        return *this != (REAL)aArg;
    }
    
    inline INT32 operator!=(FLOAT64 aArg) const
    {
        return *this != (REAL)aArg;
    }
    
    inline friend INT32 operator!=(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator!=(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator!=(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator!=(FLOAT64 aArg, const XFcFixed &aFixed);

    inline INT32 operator>(const XFcFixed &aArg) const
    {
        return mValue > aArg.mValue;
    }
    
    inline INT32 operator>(int aArg) const
    {
        return mValue > (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator>(INT32 aArg) const
    {
        return mValue > (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator>(FLOAT32 aArg) const
    {
        return *this > (REAL)aArg;
    }
    
    inline INT32 operator>(FLOAT64 aArg) const
    {
        return *this > (REAL)aArg;
    }
    
    inline friend INT32 operator>(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>(FLOAT64 aArg, const XFcFixed &aFixed);

    inline INT32 operator<(const XFcFixed &aArg) const
    {
        return mValue < aArg.mValue;
    }
    
    inline INT32 operator<(int aArg) const
    {
        return mValue < (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator<(INT32 aArg) const
    {
        return mValue < (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator<(FLOAT32 aArg) const
    {
        return *this < (REAL)aArg;
    }
    
    inline INT32 operator<(FLOAT64 aArg) const
    {
        return *this < (REAL)aArg;
    }
    
    inline friend INT32 operator<(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<(FLOAT64 aArg, const XFcFixed &aFixed);

    inline INT32 operator>=(const XFcFixed &aArg) const
    {
        return mValue >= aArg.mValue;
    }
    
    inline INT32 operator>=(int aArg) const
    {
        return mValue >= (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator>=(INT32 aArg) const
    {
        return mValue >= (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator>=(FLOAT32 aArg) const
    {
        return *this >= (REAL)aArg;
    }
    
    inline INT32 operator>=(FLOAT64 aArg) const
    {
        return *this >= (REAL)aArg;
    }
    
    inline friend INT32 operator>=(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>=(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>=(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator>=(FLOAT64 aArg, const XFcFixed &aFixed);

    inline INT32 operator<=(const XFcFixed &aArg) const
    {
        return mValue <= aArg.mValue;
    }
    
    inline INT32 operator<=(int aArg) const
    {
        return mValue <= (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator<=(INT32 aArg) const
    {
        return mValue <= (aArg << XFCFIXED_SHIFT);
    }
    
    inline INT32 operator<=(FLOAT32 aArg) const
    {
        return *this <= (REAL)aArg;
    }
    
    inline INT32 operator<=(FLOAT64 aArg) const
    {
        return *this <= (REAL)aArg;
    }
    
    inline friend INT32 operator<=(int aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<=(INT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<=(FLOAT32 aArg, const XFcFixed &aFixed);
    inline friend INT32 operator<=(FLOAT64 aArg, const XFcFixed &aFixed);
    
    inline void trunc()
    {
        mValue &= ~XFCFIXED_MASK;
    }
    
    inline void frac()
    {
        mValue &= XFCFIXED_MASK;
    }

    // Negate
    XFcFixed operator - () const
    {
        XFcFixed temp;
        temp.mValue = -mValue;
        return temp;
    }

    void setValue(INT32 aValue)
    {
        mValue = aValue;
    }
    
    INT32 getValue() const
    {
        return mValue;
    }
};


inline XFcFixed operator+(const XFcFixed &aFixed1, const XFcFixed &aFixed2)
{
    XFcFixed temp;
    temp.mValue = aFixed1.mValue + aFixed2.mValue;
    return temp;
}


inline XFcFixed operator+(const XFcFixed &aFixed, int aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (aArg << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator+(const XFcFixed &aFixed, INT32 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (aArg << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator+(const XFcFixed &aFixed, FLOAT32 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (INT32)(aArg * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator+(const XFcFixed &aFixed, FLOAT64 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (INT32)(aArg * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator+(int aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (aInt << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator+(INT32 aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (aInt << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator+(FLOAT32 aFLOAT32, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (INT32)(aFLOAT32 * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator+(FLOAT64 aFLOAT64, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue + (INT32)(aFLOAT64 * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator-(const XFcFixed &aFixed1, const XFcFixed &aFixed2)
{
    XFcFixed temp;
    temp.mValue = aFixed1.mValue - aFixed2.mValue;
    return temp;
}


inline XFcFixed operator-(const XFcFixed &aFixed, int aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue - (aArg << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator-(const XFcFixed &aFixed, INT32 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue - (aArg << XFCFIXED_SHIFT);
    return temp;
}


inline XFcFixed operator-(const XFcFixed &aFixed, FLOAT32 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue - (INT32)(aArg * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator-(const XFcFixed &aFixed, FLOAT64 aArg)
{
    XFcFixed temp;
    temp.mValue = aFixed.mValue - (INT32)(aArg * XFCFIXED_SCALE);
    return temp;
}


inline XFcFixed operator-(INT32 aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = (aInt << XFCFIXED_SHIFT) - aFixed.mValue;
    return temp;
}


inline XFcFixed operator-(int aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = (aInt << XFCFIXED_SHIFT) - aFixed.mValue;
    return temp;
}


inline XFcFixed operator-(FLOAT32 aFLOAT32, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = (INT32)(aFLOAT32 * XFCFIXED_SCALE) - aFixed.mValue;
    return temp;
}


inline XFcFixed operator-(FLOAT64 aFLOAT64, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = (INT32)(aFLOAT64 * XFCFIXED_SCALE) - aFixed.mValue;
    return temp;
}


inline XFcFixed operator*(int aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aInt * aFixed.mValue;
    return temp;
}


inline XFcFixed operator*(INT32 aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    temp.mValue = aInt * aFixed.mValue;
    return temp;
}


inline XFcFixed operator*(FLOAT32 aFLOAT32, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDMUL(aFixed.mValue, (INT32)(aFLOAT32 * XFCFIXED_SCALE), temp.mValue);
    return temp;
}


inline XFcFixed operator*(FLOAT64 aFLOAT64, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDMUL(aFixed.mValue, (INT32)(aFLOAT64 * XFCFIXED_SCALE), temp.mValue);
    return temp;
}


inline XFcFixed operator/(const XFcFixed &aArg1, const XFcFixed &aArg2)
{
    XFcFixed temp;
    XFC_FIXEDDIV(aArg1.mValue, aArg2.mValue, temp.mValue);
    return temp;
}


inline XFcFixed operator/(int aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDDIV(aInt << XFCFIXED_SHIFT, aFixed.mValue, temp.mValue);
    return temp;
}


inline XFcFixed operator/(INT32 aInt, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDDIV(aInt << XFCFIXED_SHIFT, aFixed.mValue, temp.mValue);
    return temp;
}


inline XFcFixed operator/(FLOAT32 aFLOAT32, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDDIV((INT32)(aFLOAT32 * XFCFIXED_SCALE), aFixed.mValue, temp.mValue);
    return temp;
}


inline XFcFixed operator/(FLOAT64 aFLOAT64, const XFcFixed &aFixed)
{
    XFcFixed temp;
    XFC_FIXEDDIV((INT32)(aFLOAT64 * XFCFIXED_SCALE), aFixed.mValue, temp.mValue);
    return temp;
}


inline INT32 operator==(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) == aFixed.mValue;
}


inline INT32 operator==(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) == aFixed.mValue;
}


inline INT32 operator==(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) == aFixed.mValue;
}


inline INT32 operator==(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) == aFixed.mValue;
}


inline INT32 operator!=(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) != aFixed.mValue;
}


inline INT32 operator!=(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) != aFixed.mValue;
}


inline INT32 operator!=(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) != aFixed.mValue;
}


inline INT32 operator!=(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) != aFixed.mValue;
}


inline INT32 operator>(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) > aFixed.mValue;
}


inline INT32 operator>(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) > aFixed.mValue;
}


inline INT32 operator>(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) > aFixed.mValue;
}


inline INT32 operator>(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) > aFixed.mValue;
}


inline INT32 operator<(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) < aFixed.mValue;
}


inline INT32 operator<(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) < aFixed.mValue;
}


inline INT32 operator<(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) < aFixed.mValue;
}


inline INT32 operator<(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) < aFixed.mValue;
}


inline INT32 operator>=(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) >= aFixed.mValue;
}


inline INT32 operator>=(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) >= aFixed.mValue;
}


inline INT32 operator>=(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) >= aFixed.mValue;
}


inline INT32 operator>=(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) >= aFixed.mValue;
}


inline INT32 operator<=(int aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) <= aFixed.mValue;
}


inline INT32 operator<=(INT32 aArg, const XFcFixed &aFixed)
{
    return (aArg << XFCFIXED_SHIFT) <= aFixed.mValue;
}


inline INT32 operator<=(FLOAT32 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) <= aFixed.mValue;
}


inline INT32 operator<=(FLOAT64 aArg, const XFcFixed &aFixed)
{
    return (INT32)(aArg * XFCFIXED_SCALE) <= aFixed.mValue;
}






#if defined(XFC_PLATFORM_EPOC)


#if defined(XFC_USE_ARMASM) && (defined(__MARM__) || defined(__ARM4__))


XFCIMPORT extern INT32 xfcFixedMul16x16(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedMul10x22(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedDiv16x16(INT32 a, INT32 b);
XFCIMPORT extern INT32 xfcFixedDiv11x21(INT32 a, INT32 b);

/*
inline INT32 FixedDiv21(INT32 a, INT32 b)
{
    return xfcFixedDiv11x21(a, b);
}
*/


#else // or if no ARMASM


inline INT32 xfcFixedMul16x16(INT32 a, INT32 b)
{
    INT64 res = (INT64)(int)a * (int)b;
    return (res >> 16).Low();
}

inline INT32 xfcFixedMul10x22(INT32 a, INT32 b)
{
    INT64 res = (INT64)(int)a * (int)b;
    return (res >> 22).Low();
}

inline INT32 xfcFixedDiv16x16(INT32 a, INT32 b)
{
    INT64 res = (INT64)((int)a) << 16;
    res = res / (int)b;
    return res.Low();
}

inline INT32 xfcFixedDiv11x21(INT32 a, INT32 b)
{
    INT64 res = (INT64)((int)a) << 21;
    res = res / (int)b;
    return (res).Low();
}


#endif

#if defined(XFC_PLATFORM_EPOC)

inline INT32 xfcFixedDiv10x22(INT32 a, INT32 b)
{
    INT64 res = (INT64)((int)a) << 22;
    res = res / (int)b;
    return res.Low();
}

#endif


#else // or not epoc


#if defined(XFC_USE_ARMASM) && (defined(XFC_PLATFORM_WINCE) || (defined(XFC_PLATFORM_LINUX) && defined(__arm__)))

inline INT32 xfcFixedDiv16x16(INT32 a, INT32 b)
{
    return xfcAsmFixedDiv16x16(a, b);
}

inline INT32 xfcFixedDiv10x22(INT32 a, INT32 b)
{
    return xfcAsmFixedDiv10x22(a, b);
}

inline INT32 xfcFixedDiv11x21(INT32 a, INT32 b)
{
    return xfcAsmFixedDiv11x21(a, b);
}

#else // or no ARMASM with WinCE or Linux

inline INT32 xfcFixedDiv16x16(INT32 a, INT32 b)
{
    INT64 res = (INT64)(a) << 16;
    res = res / b;
    return (INT32)(res);
}

inline INT32 xfcFixedDiv10x22(INT32 a, INT32 b)
{
    INT64 res = (INT64)(a) << 22;
    res = res / b;
    return (INT32)(res);
}

inline INT32 xfcFixedDiv11x21(INT32 a, INT32 b)
{
    INT64 res = (INT64)(a) << 21;
    res = res / b;
    return (INT32)(res);
}

#endif // no ARMASM with WinCE or Linux

/*
#if defined(XFC_USE_INTELGPP)

inline INT32 xfcFixedMul16x16(INT32 a, INT32 b)
{
    INT32 v;
    gppMul_16_32s((I32)a, (I32)b, (I32 *)&v);
    return v;
}
*/

inline INT32 xfcFixedMul16x16(INT32 a, INT32 b)

{
    INT64 res = (INT64)(a) * b;
    return (INT32)(res >> 16);
}


#if defined(XFC_USE_INTELGPP)

inline INT32 xfcFixedMul10x22(INT32 a, INT32 b)
{
    INT32 v;
    gppMul_n_32s((I32)a, (I32)b, (I32 *)&v, 22);
    return v;
}

#else

inline INT32 xfcFixedMul10x22(INT32 a, INT32 b)
{
    INT64 res = (INT64)(a) * b;
    return (INT32)(res >> 22);
}

#endif

#endif // not epoc


#if defined(XFC_USE_FLOAT)

// If we're using floats, don't do any conversion:
#define REALf(a) ((FLOAT32)(a))
#define REALi(a) ((FLOAT32)(a))

#define XFCREALTOFIXED16X16(a) (INT32)(a * 65536.0f)

#else // or no XFC_USE_FLOAT

// If we're NOT using floats, do the conversion:

#ifndef XFC_CAN_DO_DIRECT_CAST

#define REALf(a) (XFcFixed(((INT32)((a) * XFCFIXED_SCALE)), 0))
#define REALi(a) (XFcFixed(((INT32)((a) << XFCFIXED_SHIFT)), 0))

#else

#define REALf(a) (static_cast<XFcFixed>(((INT32)((a) * XFCFIXED_SCALE))))
#define REALi(a) (static_cast<XFcFixed>(((INT32)((a) << XFCFIXED_SHIFT))))

#endif

#define XFCREALTOFIXED16X16(a) ((a).mValue << (16 - XFCFIXED_SHIFT))

inline XFcFixed abs(XFcFixed aArg)
{
    return (aArg < 0) ? -aArg : aArg;
}

#endif // no XFC_USE_FLOAT

// Undefine the div/mul macros
#undef XFC_FIXEDMUL
#undef XFC_FIXEDDIV


#endif // !XFC_CORE_FIXED_H_INCLUDED

