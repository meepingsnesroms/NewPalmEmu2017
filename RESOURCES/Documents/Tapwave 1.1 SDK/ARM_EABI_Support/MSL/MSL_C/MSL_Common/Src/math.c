/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/08/06 02:07:11 $
 * $Revision: 1.33.2.4 $
 */

#ifndef _INSIDE_X87D_C_

#include <ansi_parms.h>

#undef	_MSL_USE_INLINE
#define	_MSL_USE_INLINE 1
#undef	_MSL_INLINE
#define	_MSL_INLINE _MSL_DO_NOT_INLINE

#endif	/*_INSIDE_X87D_C_*/

#include <math.h>
#include <float.h>
#include <fenv.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#if _MSL_C99

#ifndef FP_ILOGB0
	 #define FP_ILOGB0   INT_MIN 
#endif

#ifndef FP_ILOGBNAN
	 #define FP_ILOGBNAN INT_MAX 
#endif 

#if !__has_intrinsic(__builtin___count_leading_zero32)
unsigned int _MSL_MATH_CDECL __msl_generic_count_leading_zero32(_UINT32 x) _MSL_CANT_THROW
{
	static const unsigned char count_leading_zero_nibble[16] =
		{4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int shift = sizeof(unsigned int)*CHAR_BIT;
	unsigned int mask = 0xFU << (shift - 4U);
	unsigned int result = 0;
	unsigned int t;
	while (shift)
	{
		shift -= 4;
		t = count_leading_zero_nibble[(x & mask) >> shift];
		result += t;
		if (t != 4)
			break;
		mask >>= 4;
	}
	return result;
}
#endif /* !__has_intrinsic(__builtin___count_leading_zero32) */

#if !__has_intrinsic(__builtin___count_trailing_zero32)
unsigned int _MSL_MATH_CDECL __msl_generic_count_trailing_zero32(_UINT32 x) _MSL_CANT_THROW
{
	if (x != 0)
	{
		int result = 0;
		
#if _MSL_LITTLE_ENDIAN
		unsigned char* c = (unsigned char*)&x;
		while (*c == 0)
		{
			result += CHAR_BIT;
			++c;
		}
#else
		unsigned char* c = (unsigned char*)&x + (sizeof(x)-1);
		while (*c == 0)
		{
			result += CHAR_BIT;
			--c;
		}
#endif /* _MSL_LITTLE_ENDIAN */
		
		*c = ~*c;
		while (*c & 1)
		{
			*c >>= 1;
			++result;
		}
		
		return result;
	}
	
	return CHAR_BIT * sizeof(x);
}
#endif /* !__has_intrinsic(__builtin___count_trailing_zero32) */

#if !__has_intrinsic(__builtin___count_leading_zero64)
unsigned int _MSL_MATH_CDECL __msl_generic_count_leading_zero64(_UINT64 x) _MSL_CANT_THROW
{
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x |= (x >> 32);
	return(64 - __msl_count_bits64(x));
}
#endif /* !__has_intrinsic(__builtin___count_leading_zero64) */

#if !__has_intrinsic(__builtin___count_bits64)
unsigned int _MSL_MATH_CDECL __msl_generic_count_bits64(_UINT64 x) _MSL_CANT_THROW
{
	x -= (x >> 1) & 0x5555555555555555;
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
	x += x >> 8;
	x += x >> 16;
	x += x >> 32;
	return (_INT32)x & 0xFF;
}
#endif /* !__has_intrinsic(__builtin___count_bits64) */

#if !__has_intrinsic(__builtin_fma)
_MSL_IMP_EXP_C double _MSL_MATH_CDECL fma(double x, double y, double z) _MSL_CANT_THROW
{
	uint64_t p_hi, p_lo;
	int shift;
	unsigned int xp;
	uint32_t sx, sy, sz, sp, x_lo, y_lo, z_lo;
	int32_t ep;
	/* get most significant 32 bits */
	uint32_t x_hi = __UHI(x);
	uint32_t y_hi = __UHI(y);
	uint32_t z_hi = __UHI(z);
	/* extract exponent */
	int32_t ex = (int32_t)(x_hi & 0x7FF00000);
	int32_t ey = (int32_t)(y_hi & 0x7FF00000);
	int32_t ez = (int32_t)(z_hi & 0x7FF00000);
	/* test for cases we don't need extended precision */
	if (x == 0 || ex == 0x7FF00000 ||
	    y == 0 || ey == 0x7FF00000 ||
	    z == 0 || ez == 0x7FF00000)
		return x * y + z;
	/* all of x, y and z are now either FP_NORMAL or FP_SUBNORMAL
	   represent each x as:  sx = sign, ex = biased exponent, x_hi:x_lo 53 bit mantissa 
	   shift exponents down, they are still biased */
	ex >>= 20;
	ey >>= 20;
	ez >>= 20;
	/* extract sign bits */
	sx = x_hi & 0x80000000;
	sy = y_hi & 0x80000000;
	sz = z_hi & 0x80000000;
	/* mask off mantissas.  Explicitly store implicit leading bit.  And correct 0 exponent */
	x_hi &= 0x000FFFFF;
	if (ex == 0)
		ex = 1;
	else
		x_hi |= 0x00100000;
	y_hi &= 0x000FFFFF;
	if (ey == 0)
		ey = 1;
	else
		y_hi |= 0x00100000;
	z_hi &= 0x000FFFFF;
	if (ez == 0)
		ez = 1;
	else
		z_hi |= 0x00100000;
	/* extract least significant 32 bits */
	x_lo = __ULO(x);
	y_lo = __ULO(y);
	z_lo = __ULO(z);

	/* Perform p = x * y
	   p will be 118 bits stored in 2 uint64_t's, p_hi:p_lo (only 106 bits are actually generated)
	   compute least significant 32 bits of p_lo.  Use p_hi as an accumulator. */
	p_hi = (uint64_t)x_lo * y_lo;
	p_lo = p_hi & 0xFFFFFFFF;
	p_hi >>= 32;
	/* compute most significant 32 bits of p_lo. */
	p_hi += (uint64_t)x_hi * y_lo;
	p_hi += (uint64_t)x_lo * y_hi;
	p_lo |= p_hi << 32;
	p_hi >>= 32;
	/* compute remaining 42 bits */
	p_hi += (uint64_t)x_hi * y_hi;
	/* shift p_hi:p_lo left by 12 bits to "normalize" it */
	p_hi = (p_hi << 12) | (p_lo >> 52);
	p_lo <<= 12;
	/* compute exponent ep */
	ep = ex + ey - 0x3FF;
	/* compute sign sp */
	sp = sx ^ sy;

	/* Perform p + z */
	shift = ez - ep;
	/* -106 < shift < 55
	   if shift is too low, return p
	   if shift is too high, return z
	   otherwise do addition */
	if (shift >= 55)
		return z;  /* p is so small it cannot effect z */
	/* sticky guard bit for p */
	xp = 0;
	if (shift > -106)  /* if z is big enough so that it can effect p */
	{
		uint64_t q_hi, q_lo;
		unsigned int xq;
		/* put z into extended precision q_hi:q_lo */
		q_hi = (uint64_t)z_hi << 32;
		q_hi |= z_lo;
		q_lo = 0;
		/* sticky guard bit for q */
		xq = 0;
		/* make ez == ep */
		if (shift > 0)
		{
			/* shift p right by shift bits, and capture lost bits in xp
			   0 < shift < 55 */
			xp = (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_lo) != 0);
			p_lo = (p_hi << (64 - shift)) | (p_lo >> shift);
			p_hi >>= shift;
			ep = ez;
		}
		else if (shift < 0)
		{
			shift = -shift;
			/* shift q right by shift bits, and capture lost bits in xq
			   0 < shift < 106
			   q_lo is known to be 0 */
			if (shift < 64)
			{
				q_lo = q_hi << (64 - shift);
				q_hi >>= shift;
			}
			else
			{
				xq = (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (128-shift)) & q_hi) != 0);
				q_lo = q_hi >> (shift - 64);
				q_hi = 0;
			}
			ez = ep;
		}
		/* Now ez == ep */
		if (sp ^ sz)  /* subtract */
		{
			int low_sign = 0;
			int high_sign = 0;
			if (p_lo < q_lo)
				low_sign = -1;
			else if (p_lo > q_lo)
				low_sign = 1;
			if (p_hi < q_hi)
				high_sign = -1;
			else if (p_hi > q_hi)
				high_sign = 1;
			if (high_sign < 0 || (high_sign == 0 && low_sign < 0) || (high_sign == 0 && low_sign == 0 && xp < xq))
			{
				/* p = q - p */
				if (low_sign > 0)
					--q_hi;
				p_lo = q_lo - p_lo;
				p_hi = q_hi - p_hi;
				sp = sz;
			}
			else
			{
				/* p = p - q */
				if (low_sign < 0)
					--p_hi;
				p_lo -= q_lo;
				p_hi -= q_hi;
			}
		}
		else  /* addition */
		{
			/* p += q */
			unsigned int carry = 0;
			/* lo */
			if (q_lo > 0xFFFFFFFFFFFFFFFFULL - p_lo)
				carry = 1;
			p_lo += q_lo;
			/* hi */
			p_hi += q_hi + carry;
		}
		/* x bit */
		xp |= xq;
	}
	/* normalize p */
	shift = 0;
	if (p_hi != 0)
		shift = (int)__msl_count_leading_zero64(p_hi) - 11;
	else if (p_lo != 0)
		shift = 53 + (int)__msl_count_leading_zero64(p_lo);
	else  /* p == 0 */
	{
		__ULO(x) = 0;
		__UHI(x) = sp;
		return x;
	}
	if (shift > 0)
	{
		/* shift left by shift bits
		   0 < shift < 116 */
		if (shift < 64)
		{
			p_hi = (p_hi << shift) | (p_lo >> (64 - shift));
			p_lo <<= shift;
		}
		else
		{
			p_hi = p_lo << (shift - 64);
			p_lo = 0;
		}
		ep -= shift;
	}
	else if (shift < 0)
	{
		shift = -shift;
		/* shift right by shift bits
		   0 < shift < 11 */
		xp |= (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_lo) != 0);
		p_lo = (p_hi << (64 - shift)) | (p_lo >> shift);
		p_hi >>= shift;
		ep += shift;
	}
	if (ep < 1)  /* denormal or 0 */
	{
		/* shift right by 1 - ep */
		shift = 1 - ep;
		if (shift < 64)
		{
			xp |= (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_lo) != 0);
			p_lo = (p_hi << (64 - shift)) | (p_lo >> shift);
			p_hi >>= shift;
			ep = 0;
		}
		else  /* return 0 */
		{
			__ULO(x) = 0;
			__UHI(x) = sp;
			return x;
		}
	}
	if (ep >= 0x7FF)
	{
		/* return +/- inf */
		__ULO(x) = 0;
		__UHI(x) = sp | 0x7FF00000;
		return x;
	}
	/* put exponent and sign into p_hi */
	p_hi &= 0x000FFFFFFFFFFFFF;
	p_hi |= ((uint64_t)sp << 32) | ((uint64_t)ep << 52);
	/* round p to 53 bits */
	switch (FLT_ROUNDS)
	{
	case 1:  /* to nearest (round to even on tie) */
		if ((p_lo & 0x8000000000000000ULL) && ((p_hi & 1) || (p_lo & 0x7FFFFFFFFFFFFFFFULL) || xp))
			++p_hi;
		break;
	case 2:  /* towards inf */
		if ((p_lo || xp) && !sp)
			++p_hi;
		break;
	case 3:  /* towards -inf */
		if ((p_lo || xp) && sp)
			++p_hi;
		break;
	case 0:  /* towards 0 */
	default: /* indeterminant */
		break;
	}
	__ULO(x) = (uint32_t)p_hi;
	__UHI(x) = (uint32_t)(p_hi >> 32);
	return x;
}
#endif /* !__has_intrinsic(__builtin_fma) */
	
#if !__has_intrinsic(__builtin_fmaf)
_MSL_IMP_EXP_C float _MSL_MATH_CDECL fmaf(float x, float y, float z) _MSL_CANT_THROW
{
	uint64_t p_i;
	int shift;
	unsigned int xp;
	uint32_t sx, sy, sz, sp;
	int32_t ep;
	/* get as unsigned integral */
	uint32_t x_i = *(uint32_t*)&x;
	uint32_t y_i = *(uint32_t*)&y;
	uint32_t z_i = *(uint32_t*)&z;
	/* extract exponent */
	int32_t ex = (int32_t)(x_i & 0x7F800000);
	int32_t ey = (int32_t)(y_i & 0x7F800000);
	int32_t ez = (int32_t)(z_i & 0x7F800000);
	/* test for cases we don't need extended precision */
	if (x == 0 || ex == 0x7F800000 ||
	    y == 0 || ey == 0x7F800000 ||
	    z == 0 || ez == 0x7F800000)
		return x * y + z;
	/* all of x, y and z are now either FP_NORMAL or FP_SUBNORMAL
	   represent each x as:  sx = sign, ex = biased exponent, x_i 24 bit mantissa 
	   shift exponents down, they are still biased */
	ex >>= 23;
	ey >>= 23;
	ez >>= 23;
	/* extract sign bits */
	sx = x_i & 0x80000000;
	sy = y_i & 0x80000000;
	sz = z_i & 0x80000000;
	/* mask off mantissas.  Explicitly store implicit leading bit.  And correct 0 exponent */
	x_i &= 0x007FFFFF;
	if (ex == 0)
		ex = 1;
	else
		x_i |= 0x00800000;
	y_i &= 0x007FFFFF;
	if (ey == 0)
		ey = 1;
	else
		y_i |= 0x00800000;
	z_i &= 0x007FFFFF;
	if (ez == 0)
		ez = 1;
	else
		z_i |= 0x00800000;

	/* Perform p = x * y
	   p will be 57 bits stored in a uint64_t, p_i (only 48 bits are actually generated) */
	p_i = (uint64_t)x_i * y_i;
	/* shift p_i left by 9 bits to "normalize" it */
	p_i <<= 9;
	/* compute exponent ep */
	ep = ex + ey - 0x7F;
	/* compute sign sp */
	sp = sx ^ sy;

	/* Perform p + z */
	shift = ez - ep;
	/* -48 < shift < 26
	   if shift is too low, return p
	   if shift is too high, return z
	   otherwise do addition */
	if (shift >= 26)
		return z;  /* p is so small it cannot effect z */
	/* sticky guard bit for p */
	xp = 0;
	if (shift > -48)  /* if z is big enough so that it can effect p */
	{
		/* put z into extended precision q_i */
		uint64_t q_i = (uint64_t)z_i << 32;
		/* sticky guard bit for q */
		unsigned int xq = 0;
		/* make ez == ep */
		if (shift > 0)
		{
			/* shift p right by shift bits, and capture lost bits in xp
			   0 < shift < 26 */
			xp = (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_i) != 0);
			p_i >>= shift;
			ep = ez;
		}
		else if (shift < 0)
		{
			shift = -shift;
			/* shift q right by shift bits, and capture lost bits in xq
			   0 < shift < 48 */
			xq = (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & q_i) != 0);
			q_i >>= shift;
			ez = ep;
		}
		/* Now ez == ep */
		if (sp ^ sz)  /* subtract */
		{
			if (p_i < q_i || p_i == q_i && xp < xq)
			{
				/* p = q - p */
				p_i = q_i - p_i;
				sp = sz;
			}
			else
			{
				/* p = p - q */
				p_i -= q_i;
			}
		}
		else  /* addition */
		{
			/* p += q */
			p_i += q_i;
		}
		/* x bit */
		xp |= xq;
	}
	/* normalize p */
	shift = 0;
	if (p_i != 0)
		shift = (int)__msl_count_leading_zero64(p_i) - 8;
	else  /* p == 0 */
	{
		*(uint32_t*)&x = sp;
		return x;
	}
	if (shift > 0)
	{
		/* shift left by shift bits
		   0 < shift < 55 */
		p_i <<= shift;
		ep -= shift;
	}
	else if (shift < 0)
	{
		shift = -shift;
		/* shift right by shift bits
		   0 < shift < 8 */
		xp |= (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_i) != 0);
		p_i >>= shift;
		ep += shift;
	}
	if (ep < 1)  /* denormal or 0 */
	{
		/* shift right by 1 - ep */
		shift = 1 - ep;
		if (shift < 64)
		{
			xp |= (unsigned int)(((0xFFFFFFFFFFFFFFFFULL >> (64-shift)) & p_i) != 0);
			p_i >>= shift;
			ep = 0;
		}
		else  /* return 0 */
		{
			*(uint32_t*)&x = sp;
			return x;
		}
	}
	if (ep >= 0xFF)
	{
		/* return +/- inf */
		*(uint32_t*)&x = sp | 0x7F800000;
		return x;
	}
	/* put exponent and sign into p_i */
	p_i &= 0x007FFFFFFFFFFFFF;
	p_i |= ((uint64_t)sp << 32) | ((uint64_t)ep << 55);
	/* round p to 24 bits */
	switch (FLT_ROUNDS)
	{
	case 1:  /* to nearest (round to even on tie) */
		if ((p_i & 0x0000000080000000) && ((p_i & 0x0000000100000000) || (p_i & 0x000000007FFFFFFF) || xp))
			p_i += 0x0000000100000000;
		break;
	case 2:  /* towards inf */
		if (((p_i & 0x00000000FFFFFFFF) || xp) && !sp)
			p_i += 0x0000000100000000;
		break;
	case 3:  /* towards -inf */
		if (((p_i & 0x00000000FFFFFFFF) || xp) && sp)
			p_i += 0x0000000100000000;
		break;
	case 0:  /* towards 0 */
	default: /* indeterminant */
		break;
	}
	*(uint32_t*)&x = (uint32_t)(p_i >> 32);
	return x;
}
#endif /* !__has_intrinsic(__builtin_fmaf) */

#if !(_MSL_USES_SUN_MATH_LIB)
_MSL_IMP_EXP_C double _MSL_MATH_CDECL cbrt(double x) _MSL_CANT_THROW
{
	unsigned int sign;
	int exponent;
	double y;
/* 		if x is 0 or -0 return x 																	*/
	if (x == 0)
		return x;
/* 	if x is +/- inf or nan, return x, setting errors as appropriate									*/
	if (!isfinite(x))
	{
		if (math_errhandling)
		{
			if (isnan(x))
			{
				if (math_errhandling & MATH_ERRNO)
					errno = EDOM;
				if (math_errhandling & MATH_ERREXCEPT)
					feraiseexcept(FE_INVALID);
			}
			else
			{
				if (math_errhandling & MATH_ERRNO)
					errno = ERANGE;
				if (math_errhandling & MATH_ERREXCEPT)
					feraiseexcept(FE_OVERFLOW);
			}
		}
		return x;
	}

/* 	extract biased exponent (x is either normal or denormal											*/
	sign = __UHI(x) & 0x80000000;
	__UHI(x) ^= sign;
	exponent = (int)(__UHI(x) >> 20);
	if (exponent == 0)  /* if x is denormal															*/
	{
		/* normalize x by shifting left until the first 1 bit is in									*/
		/* position 11																				*/
		int c = __msl_count_leading_zero32(__UHI(x)) - 11;
		if (c == 21)
			c += __msl_count_leading_zero32(__ULO(x));
		if (c < 32)
		{
			__UHI(x) = (__UHI(x) << c) | (__ULO(x) >> (32 - c));
			__ULO(x) <<= c;
		}
		else
		{
			__UHI(x) = __ULO(x) << (c - 32);
			__ULO(x) = 0;
		}
		/* decrement exponent by the number of leading 0 bits in mantissa							*/
		exponent -= c - 1;
	}

	/* unbias exponent and normalize x to [0.5, 1)													*/
	exponent -= 1022;
	__UHI(x) &= 0x000FFFFF;
	__UHI(x) |= 0x3FE00000;
	/* make exponent evenly divisible by 3, normalizing x to [0.125, 1)								*/
	switch (exponent % 3)
	{
		case -2:
		case 1:
			exponent += 2;
			__UHI(x) -= 0x00200000;
			break;
		case -1:
		case 2:
			exponent += 1;
			__UHI(x) -= 0x00100000;
			break;
	}
	/* estimate first guess to cube root of x [0.125, 1) 											*/
	/* use polynomial derived from minimizing the error  from 0.125 to 1                        	*/
	y = (0.1950252994681516 + (8.93386164028292 +  (34.95109317740758 + 14.90468137136715 * x) * x) * x) /
	    (1.0                + (17.79274627019952 + (34.47634312279896 + 5.715646840256109 * x) * x) * x);
	/* perform newton iterations to improve the estimate											*/
	y = (2 * y + x / (y*y)) / 3;
	/* put result of final estimate back in x														*/
	x = (2 * y + x / (y*y)) / 3;
	/* x is now the cube root of [0.125, 1) -> [0.5, 1)												*/
	/* complete by taking the cube root of the exponent, and loading that							*/
	/* exponent into x																				*/
	exponent /= 3;
	exponent <<= 20;
	__UHI(x) += exponent;
	/* restore original sign of x																	*/
	__UHI(x) |= sign; 
	/*x = x * sign; */
	return x;
}
#endif /* _MSL_USES_SUN_MATH_LIB */

_MSL_IMP_EXP_C float _MSL_MATH_CDECL cbrtf(float x) _MSL_CANT_THROW
{
	double xd;
	unsigned int* ix;
	unsigned int sign;
	int exponent;
	if (x == 0)
		return x;
	ix = (unsigned int*)&x;
/* 	if x is +/- inf or nan, return x, setting errors as appropriate									*/
	if (!isfinite(x))
	{
		if (math_errhandling)
		{
			if (isnan(x))
			{
				if (math_errhandling & MATH_ERRNO)
					errno = EDOM;
				if (math_errhandling & MATH_ERREXCEPT)
					feraiseexcept(FE_INVALID);
			}
			else
			{
				if (math_errhandling & MATH_ERRNO)
					errno = ERANGE;
				if (math_errhandling & MATH_ERREXCEPT)
					feraiseexcept(FE_OVERFLOW);
			}
		}
		return x;
	}

	sign = *ix & 0x80000000;
	*ix ^= sign;
	exponent = (int)(*ix >> 23);
	if (exponent == 0)
	{
		int c = __msl_count_leading_zero32(*ix) - 8;
		*ix <<= c;
		exponent -= c - 1;
	}
	exponent -= 126;
	*ix &= 0x007FFFFF;
	*ix |= 0x3F000000;
	switch (exponent % 3)
	{
		case -2:
		case 1:
			exponent += 2;
			*ix -= 0x01000000;
			break;
		case -1:
		case 2:
			exponent += 1;
			*ix -= 0x00800000;
			break;
	}
	xd = x;
	x = (float)((0.164705865585441 + (13.2513868634597 + (115.1358553761178 +
	                         (181.9414139157457 + 41.95971194004274 * xd) * xd) * xd) * xd) /
	    (1.0               + (33.30169492280659 + (161.6940396106312 +
	                         (142.8167287366127 + 13.64061797885738 * xd) * xd) * xd) * xd));
	exponent /= 3;
	exponent <<= 23;
	*ix += exponent;
	*ix |= sign;
	return x;
}

#if !(_MSL_USES_SUN_MATH_LIB)
int ilogb(double x)
{
	if (x == 0.0)
		return (FP_ILOGB0);
	if (isinf(x))
		return (INT_MAX);
	if (isnan(x))
		return (FP_ILOGBNAN);
	return ((int)logb(x));
}

int ilogbl(long double x)
{
	if (x == 0.0)
		return (FP_ILOGB0);
	if (isinf(x))
		return (INT_MAX);
	if (isnan(x))
		return (FP_ILOGBNAN);
	return ((int)logbl(x));
}
#endif /*!(_MSL_USES_SUN_MATH_LIB) */

#if __dest_os != __mac_os

/* This function is taken from "Handbook of Mathematical Functions"
   from US Department of Commerce                                  */
   
_MSL_IMP_EXP_C long double _MSL_MATH_CDECL erfl(long double x) _MSL_CANT_THROW
{
	long double div;
	long double argx;
	long double coefs[6] =
	{
		0.0705230784,
		0.0422820123,
		0.0092705272,
		0.0001520143,
		0.0002765672,
		0.0000430638
	};
	int index;
	
	argx = x;
	div  = 1;
	for (index = 0; index < 6; index++)
	{
		div += argx * coefs[index];
		argx *= x;
	}
	
	for (index = 0; index < 4; index++)
		div *= div;
		
	return(1.0 - 1.0 / div);
}

_MSL_IMP_EXP_C float _MSL_MATH_CDECL erff(float x) _MSL_CANT_THROW
{
	return((float)erfl(x));
}

#if !_MSL_USES_SUN_MATH_LIB
_MSL_IMP_EXP_C double _MSL_MATH_CDECL erf(double x) _MSL_CANT_THROW
{
	return((double)erfl(x));
}

_MSL_IMP_EXP_C double _MSL_MATH_CDECL erfc(double x) _MSL_CANT_THROW
{
	return((double)(1.0 - erfl(x)));
}
#endif

_MSL_IMP_EXP_C float _MSL_MATH_CDECL erfcf(float x) _MSL_CANT_THROW
{
	return((float)(1.0 - erfl(x)));
}

_MSL_IMP_EXP_C long double _MSL_MATH_CDECL erfcl(long double x) _MSL_CANT_THROW
{
	return((long double)(1.0 - erfl(x)));
}
	
#define _ln2  0.6931471805599453094172321

#if !(__dest_os ==__win32_os)
_MSL_IMP_EXP_C double _MSL_MATH_CDECL exp2(double x) _MSL_CANT_THROW
{
	return(exp(x * _ln2));
}
#endif

_MSL_IMP_EXP_C float _MSL_MATH_CDECL exp2f(float x) _MSL_CANT_THROW
{
	return(exp(x * _ln2));
}

_MSL_IMP_EXP_C long double _MSL_MATH_CDECL exp2l(long double x) _MSL_CANT_THROW
{
	return(exp(x * _ln2));
}

#if !_MSL_USES_SUN_MATH_LIB
_MSL_IMP_EXP_C double _MSL_MATH_CDECL lgamma(double x) _MSL_CANT_THROW
{
	return((double)(logl(tgammal(x))));
}
#endif /* !_MSL_USES_SUN_MATH_LIB */

_MSL_IMP_EXP_C float _MSL_MATH_CDECL lgammaf(float x) _MSL_CANT_THROW
{
	return((float)(logl(tgammal(x))));
}
	
_MSL_IMP_EXP_C long double _MSL_MATH_CDECL lgammal(long double x) _MSL_CANT_THROW
{
	return(logl(tgammal(x)));
}

#if _MSL_USES_SUN_MATH_LIB
_MSL_IMP_EXP_C long long _MSL_MATH_CDECL llrint(double x) _MSL_CANT_THROW
{
	return ((long long)rint(x));
}
#endif /* _MSL_USES_SUN_MATH_LIB */


_MSL_IMP_EXP_C float _MSL_MATH_CDECL nanf(const char* str) _MSL_CANT_THROW
{
	char temparg[32] = "NAN(";
	strcat(temparg, str);
	strcat(temparg, ")");
	
	return(strtof(temparg, (char**)NULL));
}

_MSL_IMP_EXP_C long double _MSL_MATH_CDECL nanl(const char* str) _MSL_CANT_THROW
{
	char temparg[32] = "NAN(";
	strcat(temparg, str);
	strcat(temparg, ")");
	
	return(strtold(temparg, (char**)NULL));
}

#if !_MSL_USES_SUN_MATH_LIB
_MSL_IMP_EXP_C double _MSL_MATH_CDECL nextafter(double x, double y) _MSL_CANT_THROW
{
	return nexttoward(x, (long double)y);
}
#endif /* !_MSL_USES_SUN_MATH_LIB */

_MSL_IMP_EXP_C float _MSL_MATH_CDECL nextafterf(float x, float y) _MSL_CANT_THROW
{
	return nexttowardf(x, (long double)y);
}

_MSL_IMP_EXP_C double _MSL_MATH_CDECL nexttoward(double x, long double y) _MSL_CANT_THROW
{
	int increase;
	int positive;
	unsigned long* lx = (unsigned long*)&x;
	unsigned long* ly = (unsigned long*)&y;
#if _MSL_LITTLE_ENDIAN
	unsigned long x_exp = lx[1] & 0x7FF00000;
	if ((ly[1] & 0x7FF00000) == 0x7FF00000 && (ly[1] & 0x000FFFFF) | ly[0] ||
	    x == y)
		return (double)y;
	if (x_exp == 0x7FF00000 && lx[1] & 0x000FFFFF | lx[0])
		return x;
#else
	unsigned long x_exp = lx[0] & 0x7FF00000;
	if ((ly[0] & 0x7FF00000) == 0x7FF00000 && (ly[0] & 0x000FFFFF) | ly[1] ||
	    x == y)
		return (double)y;
	if (x_exp == 0x7FF00000 && lx[0] & 0x000FFFFF | lx[1])
		return x;
#endif /* _MSL_LITTLE_ENDIAN */
	increase = y > x;
	positive = x > 0;
	if (x_exp != 0x7FF00000 || increase != positive)
	{
		unsigned long long* llx = (unsigned long long*)&x;
		if (x == 0)
		{
			if (increase)
				*llx = 0x0000000000000001ULL;
			else
				*llx = 0x8000000000000001ULL;
		}
		else
		{
			if (increase == positive)
				++(*llx);
			else
				--(*llx);
		}
	#if _MSL_LITTLE_ENDIAN
		x_exp = lx[1] & 0x7FF00000;
	#else
		x_exp = lx[0] & 0x7FF00000;
	#endif /* _MSL_LITTLE_ENDIAN */
		if (x_exp == 0 && (math_errhandling & MATH_ERREXCEPT))
			feraiseexcept(FE_UNDERFLOW | FE_INEXACT);
		else if (x_exp == 0x7FF00000)
		{
			if (math_errhandling & MATH_ERRNO)
				errno = ERANGE;
			if (math_errhandling & MATH_ERREXCEPT)
				feraiseexcept(FE_OVERFLOW | FE_INEXACT);
		}
	}
	return x;
}


_MSL_IMP_EXP_C float _MSL_MATH_CDECL nexttowardf(float x, long double y) _MSL_CANT_THROW
{
	int increase;
	int positive;
	unsigned long* lx = (unsigned long*)&x;
	unsigned long* ly = (unsigned long*)&y;
	unsigned long x_exp = *lx & 0x7F800000;
#if _MSL_LITTLE_ENDIAN
	if ((ly[1] & 0x7FF00000) == 0x7FF00000 && (ly[1] & 0x000FFFFF) | ly[0] ||
	    x == y)
		return (float)y;
#else
	if ((ly[0] & 0x7FF00000) == 0x7FF00000 && (ly[0] & 0x000FFFFF) | ly[1] ||
	    x == y)
		return (float)y;
#endif /* _MSL_LITTLE_ENDIAN */
	if (x_exp == 0x7F800000 && *lx & 0x007FFFFF)
		return x;
	increase = y > x;
	positive = x > 0;
	if (x_exp != 0x7F800000 || increase != positive)
	{
		if (x == 0)
		{
			if (increase)
				*lx = 0x00000001UL;
			else
				*lx = 0x80000001UL;
		}
		else
		{
			if (increase == positive)
				++(*lx);
			else
				--(*lx);
		}
		x_exp = *lx & 0x7F800000;
		if (x_exp == 0 && (math_errhandling & MATH_ERREXCEPT))
			feraiseexcept(FE_UNDERFLOW | FE_INEXACT);
		else if (x_exp == 0x7F800000)
		{
			if (math_errhandling & MATH_ERRNO)
				errno = ERANGE;
			if (math_errhandling & MATH_ERREXCEPT)
				feraiseexcept(FE_OVERFLOW | FE_INEXACT);
		}
	}
	return x;
}

_MSL_IMP_EXP_C double _MSL_MATH_CDECL tgamma(double x) _MSL_CANT_THROW
{
	return((double)tgammal(x));
}

_MSL_IMP_EXP_C float _MSL_MATH_CDECL tgammaf(float x) _MSL_CANT_THROW
{
	return((float)tgammal(x));
}

/* This function is taken from "Handbook of Mathematical Functions"
   from US Department of Commerce                                  */
   
_MSL_IMP_EXP_C long double _MSL_MATH_CDECL tgammal(long double x) _MSL_CANT_THROW
{
	long double coefs[26] =
	{
		+1.0000000000000000,
		+0.5772156649915329,
		-0.6558780715202538,
		-0.0420026350340952,
		+0.1665386113822915,
		-0.0421977345555443,
		-0.0096219715278770,
		+0.0072189432466630,
		-0.0011651675918591,
		-0.0002152416741149,
		+0.0001280502823882,
		-0.0000201348547807,
		-0.0000012504934821,
		+0.0000011330272320,
		-0.0000002056338417,
		+0.0000000061160960,
		+0.0000000050020075,
		-0.0000000011812746,
		+0.0000000001043427,
		+0.0000000000077823,
		-0.0000000000036968,
		+0.0000000000005100,
		-0.0000000000000206,
		-0.0000000000000054,
		+0.0000000000000014,
		+0.0000000000000001
	};
	
	long double argx;
	long double div;
	int    index;
	
	div  = 0.0;
	argx = x;
	for (index = 0; index < 26; index++)
	{
		div += argx * coefs[index];
		argx *= x;
	}
	
	return(1.0/div);
}

#endif /* _MSL_C99 */									/*- mm 030520 -*/

#endif /* #if __dest_os == __mac_os */
	
/* Change record: 
 * cc  020124 Needed for __fpclassifyf and other _MSL_INLINE items
 * JWW 020212 Removed the unnecessary __cdecl stuff
 * JWW 020308 Use new _MSL_DO_NOT_INLINE macro for bringing inlined functions into the library
 * mm  021108 Added erf, nan and gamma functions
 * mm  021120 Added nexttowardl()
 * cc  021121 Removed redefined of nexttowardl.  It lives as an inline in math_XXX.h.
 * cc  021216 Added cbrt and family for Michael
 * cc  030110 Fixed so it can be added to mac os and not affect math lib
 * mm  030128 Revised cbrt() and cbrtf() based on Howard's version
 * cc  030221 Added _MSL_USES_SUN_MATH_LIB flag
 * mm  030520 Added C99 wrappers
 * JWW 030321 Added fma, fmaf, and assortied helper functions (thanks to Howard)
 * mm  030522 Added C99 wrappers
 * mm  030529 Added modf() and modff()
 * mm  030605 Added ilogb() and ilogbl()
 * ejs 030613 Standardize the __builtin_xxx types
 */