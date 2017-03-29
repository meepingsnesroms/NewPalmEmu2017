/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/04/03 18:37:32 $
 * $Revision: 1.10 $
 */

/*
 *	ansi_fp.c
 *	
 *	Routines
 *	--------
 *		These are routines similar to those from MathLib needed by non-Mac systems.
 *		Note that we assume 8-byte doubles here.
 *
 *			__num2dec -	same as num2dec, except that we don't support the FIXEDDECIMAL
 *						style result (all conversions are handled in printf using the
 *						FLOATDECIMAL output)
 *
 *			__dec2num -	same as dec2num
 */

#ifndef _No_Floating_Point

#include <ansi_fp.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>

#if __dest_os == __m56800_os 
#pragma optimize_for_size on

double copysign(double x, double y)
{
	__HI(x) = (__HI(x)&0x7fffffff)|(__HI(y)&0x80000000);
        return x;
}

#endif	

/*
	_ENCODE_NAN

	Set if you want __dec2num to be able to encode information into a nan
*/

/*
	Set _DOUBLE_BITS to either 64 to support IEEE 64 bit double
	Set _DOUBLE_BITS to either 32 to support IEEE 32 bit double
*/

/*
	Comment out _TEST once ansi_fp.c passes the tests in ansi_fp_test.c

#define _TEST
*/

#ifndef _DOUBLE_BITS

#if DBL_MANT_DIG == 53      /* 64 bit */

	#define _DOUBLE_BITS 64

#elif DBL_MANT_DIG == 24   /* 32 bit */

	#define _DOUBLE_BITS 32

#else

	#error unsupported sizeof double

#endif

#endif

/*
	There is an internal format and external format for the decimal structure.
	The external format is output from num2dec, and input for dec2num.
	The internal format is used everywhere else.
	The external format uses ASCII for the digits, and the decimal point
	is to the right of the least significant digit.
	The internal format uses numerical values for the digits ('\0' is 0)
	and the decimal point is to the right of the most significant digit.
*/

#if _DOUBLE_BITS == 64
	typedef unsigned long long d_int;
#elif _DOUBLE_BITS == 32
	typedef unsigned long d_int;
#else
	#error unsupported sizeof double
#endif

#ifdef _TEST

static
void __test_preconditions()
{
	char c1[sizeof(double)*CHAR_BIT == _DOUBLE_BITS];
	char c2[sizeof(double) == sizeof(d_int)];
	char c3[sizeof(unsigned long)*CHAR_BIT == 32];
	c1;
	c2;
	c3;
}

#endif

/*
	Count number of consequtive low order 0 bits in unsigned long
*/

#ifdef __POWERPC__

#ifndef _TEST
static
inline
#endif
int __count_trailing_zerol(unsigned long x)
{
	return 32 - __cntlzw(~x & (x-1));
}

#else  /* !__POWERPC__ */

#if __option(optimize_for_size)

#ifndef _TEST
static
#endif
int __count_trailing_zerol(unsigned long x)
{
	int result = 0;
	x = ~x;
	while (x & 1)
	{
		x >>= 1;
		++result;
	}
	return result;
}

#else  /* !__option(optimize_for_size) */

#ifndef _TEST
static
#endif
int __count_trailing_zerol(unsigned long x)
{
	if (x != 0)
	{
		int result = 0;
	#if __option(little_endian)
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
	#endif
		*c = (unsigned char)~*c;
		while (*c & 1)
		{
			*c >>= 1;
			++result;
		}
		return result;
	}
	return CHAR_BIT*sizeof(x);
}

#endif  /* __option(optimize_for_size) */

#endif  /* __POWERPC__ */

/*
	Count number of consequtive low order 0 bits in double
*/
#ifndef _TEST
static
inline
#endif
int __count_trailing_zero(double x)
{
	unsigned long* l = (unsigned long*)&x;
#if _DOUBLE_BITS == 64
#if __option(little_endian)
	return (l[0] != 0) ?
		__count_trailing_zerol(l[0]) :
		(int)(sizeof(unsigned long) * CHAR_BIT + __count_trailing_zerol(l[1] | 0x00100000));
#else
	return (l[1] != 0) ?
		__count_trailing_zerol(l[1]) :
		(int)(sizeof(unsigned long) * CHAR_BIT + __count_trailing_zerol(l[0] | 0x00100000));
#endif
#elif _DOUBLE_BITS == 32
	return __count_trailing_zerol(l[0] | 0x00800000);
#else
	#error  __count_trailing_zero unsupported
#endif
}

/*
	Scan decimal mantissa starting at pos.
	Return -1 if should round down
	Return  1 if should round up
	Round towards even for half way
*/
#ifndef _TEST
static
#endif
int __must_round(const decimal *d, int pos)
{
	unsigned char const *i = d->sig.text + pos;
	if (*i > 5)
		return 1;
	if (*i < 5)
		return -1;
	{    /* if there are any non-zeroes after the 5 round up */
	unsigned char const *e = d->sig.text + d->sig.length;
	for (++i; i < e; ++i)
		if (*i != 0)
			return 1;
	}
	/* exactly half, round to even */
	if (d->sig.text[pos-1] & 1)
		return 1;
	return -1;
}

/*
	Round decimal up, using the left most digits digits
*/
#ifndef _TEST
static
#endif
void __dorounddecup(decimal *d, int digits)
{
	unsigned char *b = d->sig.text;
	unsigned char *i = b + digits - 1;
	while (1)
	{
		if (*i < 9)
		{
			(*i)++;
			break;
		}
		if (i == b)
		{
			*i = 1;
			d->exp++;
			break;
		}
		*i-- = 0;
	}
}

/*
	Round decimal to specified digits according to value in decimal
*/
#ifndef _TEST
static
#endif
void __rounddec(decimal *d, int digits)
{
	if (digits <= 0 || digits >= d->sig.length)
		return;
	{
	int r = __must_round(d, digits);
	d->sig.length = (unsigned char)digits;
	if (r < 0)
		return;
	}
	__dorounddecup(d, digits);
}

/*
	Convert d_int to decimal
*/
#ifndef _TEST
static
#endif
void __ull2dec(decimal *result, d_int integer)
{
	/* assumes integer is > 0 */
	result->sgn = 0;
	result->sig.length = 0;
	for (; integer != 0; integer /= 10)
		result->sig.text[result->sig.length++] = (unsigned char)(integer % 10);
	{
	unsigned char* i = result->sig.text;
	unsigned char* j = result->sig.text + result->sig.length;
	for (; i < --j; ++i)
	{
		unsigned char t = *i;
		*i = *j;
		*j = t;
	}
	}
	result->exp = (short)(result->sig.length - 1);
}

/*
	result = x * y
*/
#ifndef _TEST
static
#endif
void __timesdec(decimal *result, const decimal *x, const decimal *y)
{
	/* Assume x and y are finite and positive */
	unsigned long accumulator = 0;
	unsigned char mantissa[2*SIGDIGLEN];
	int i = x->sig.length + y->sig.length - 1;
	unsigned char *ip = mantissa + i + 1;
	unsigned char *ep = ip;
	result->sgn = 0;
	for (; i > 0; --i)
	{
		int k = y->sig.length - 1;
		int j = i - k - 1;
		int l;
		int t;
		unsigned char const *jp, *kp;
		if (j < 0)
		{
			j = 0;
			k = i - 1;
		}
		jp = x->sig.text + j;
		kp = y->sig.text + k;
		l = k + 1;
		t = x->sig.length - j;
		if (l > t)
			l = t;
		for (; l > 0; --l, ++jp, --kp)
			accumulator += (unsigned long)(*jp) * *kp;
		*--ip = (unsigned char)(accumulator % 10);
		accumulator /= 10;
	}
	result->exp = (short)(x->exp + y->exp);
	if (accumulator > 0)
	{
		*--ip = (unsigned char)accumulator;
		result->exp++;
	}
	for (i = 0; i < SIGDIGLEN && ip < ep; ++i, ++ip)
		result->sig.text[i] = *ip;
	result->sig.length = (unsigned char)i;
	if (ip < ep && *ip >= 5)
	{
		if (*ip == 5)
		{
			unsigned char* jp = ip + 1;
			for (; jp < ep; ++jp)
				if (*jp != 0)
					goto round;
			/* exactly half way, round toward even */
			if ((*(ip - 1) & 1) == 0)
				return;
		}
	round:
		__dorounddecup(result, result->sig.length);
	}
}

/*
	The ASCII string is put into d's mantissa (after converting
	to numeric) and the exp is put into d's exponent.  If the string
	is too long to fit in the mantissa, rounding is performed.
*/
#ifndef _TEST
static
#endif
void __str2dec(decimal *d, const char* s, short exp)
{
	int i;
	d->exp = exp;
	d->sgn = 0;
	for (i = 0; i < SIGDIGLEN && *s != 0;)
		d->sig.text[i++] = (unsigned char)(*s++ - '0');
	d->sig.length = (unsigned char)i;
	if (*s != 0)
	{
		if (*s < 5)
			return;
		if (*s > 5)
			goto round;
		{
		const char* p = s + 1;
		for (; *p != 0; ++p)
			if (*p != '0')
				goto round;
		if ((d->sig.text[i-1] & 1) == 0)
			return;
		}
	round:
		__dorounddecup(d, d->sig.length);
	}
}

/*
	decimal = pow(2, exp)
*/
#ifndef _TEST
static
#endif
void __two_exp(decimal *result, long exp)
{
#if __dest_os == __m56800_os 
	switch ((int)exp)
#else
	switch (exp)
#endif
	{
#if !__option(optimize_for_size)
	case -64:
		__str2dec(result, "542101086242752217003726400434970855712890625", -20);
		return;
	case -53:
		__str2dec(result, "11102230246251565404236316680908203125", -16);
		return;
	case -32:
		__str2dec(result, "23283064365386962890625", -10);
		return;
	case -16:
		__str2dec(result, "152587890625", -5);
		return;
	case -8:
		__str2dec(result, "390625", -3);
		return;
	case -7:
		__str2dec(result, "78125", -3);
		return;
	case -6:
		__str2dec(result, "15625", -2);
		return;
	case -5:
		__str2dec(result, "3125", -2);
		return;
	case -4:
		__str2dec(result, "625", -2);
		return;
	case -3:
		__str2dec(result, "125", -1);
		return;
	case -2:
		__str2dec(result, "25", -1);
		return;
#endif  /* !__option(optimize_for_size) */
	case -1:
		__str2dec(result, "5", -1);
		return;
	case 0:
		__str2dec(result, "1", 0);
		return;
	case 1:
		__str2dec(result, "2", 0);
		return;
#if !__option(optimize_for_size)
	case 2:
		__str2dec(result, "4", 0);
		return;
	case 3:
		__str2dec(result, "8", 0);
		return;
	case 4:
		__str2dec(result, "16", 1);
		return;
	case 5:
		__str2dec(result, "32", 1);
		return;
	case 6:
		__str2dec(result, "64", 1);
		return;
	case 7:
		__str2dec(result, "128", 2);
		return;
	case 8:
		__str2dec(result, "256", 2);
		return;
#endif  /* !__option(optimize_for_size) */
	}
	{
	decimal x2, temp;
	__two_exp(&x2, ((long)((0x80000000UL & exp) >> 31) + exp) >> 1); /*__two_exp(&x2, exp/2); */
	__timesdec(result, &x2, &x2);
	if (exp & 1)
	{
		temp = *result;
		if (exp > 0)
			__str2dec(&x2, "2", 0);
		else
			__str2dec(&x2, "5", -1);
		__timesdec(result, &temp, &x2);
	}
	}
}

#ifndef _TEST
static
#endif
int __equals_dec(const decimal *x, const decimal *y)
{
	/* Assume x and y are finite and non-negative */
	/* First check for x or y to be 0 */
	if (x->sig.text[0] == 0)
	{
		if (y->sig.text[0] == 0)
			return 1;
		return 0;
	}
	if (y->sig.text[0] == 0)
	{
		if (x->sig.text[0] == 0)
			return 1;
		return 0;
	}
	/* x and y are finite and positive */
	if (x->exp == y->exp)
	{
		int i;
		int l = x->sig.length;
		if (l > y->sig.length)
			l = y->sig.length;
		for (i = 0; i < l; ++i)
			if (x->sig.text[i] != y->sig.text[i])
				return 0;
		if (l == x->sig.length)
			x = y;
		for (; i < x->sig.length; ++i)
			if (x->sig.text[i] != 0)
				return 0;
		return 1;
	}
	return 0;
}

#ifndef _TEST
static
#endif
int __less_dec(const decimal *x, const decimal *y)
{
	/* Assume x and y are finite and non-negative */
	/* First check for x or y to be 0 */
	if (x->sig.text[0] == 0)
	{
		if (y->sig.text[0] != 0)
			return 1;
		return 0;
	}
	if (y->sig.text[0] == 0)
		return 0;
	/* x and y are finite and positive */
	if (x->exp == y->exp)
	{
		int i;
		int l = x->sig.length;
		if (l > y->sig.length)
			l = y->sig.length;
		for (i = 0; i < l; ++i)
		{
			if (x->sig.text[i] < y->sig.text[i])
				return 1;
			if (y->sig.text[i] < x->sig.text[i])
				return 0;
		}
		if (l == x->sig.length)
		{
			for (; i < y->sig.length; ++i)
				if (y->sig.text[i] != 0)
					return 1;
		}
		return 0;
	}
	return x->exp < y->exp;
}

#ifndef _TEST
static
#endif
void __minus_dec(decimal *z, const decimal *x, const decimal *y)
{
	/* Assume x and y are finite and non-negative */
	/* Also assume y < x */
	int zlen, dexp;
	unsigned char *ib, *i, *ie;
	unsigned char const *jb, *j, *jn;
	*z = *x;
	if (y->sig.text[0] == 0)
		return;
	zlen = z->sig.length;
	if (zlen < y->sig.length)
		zlen = y->sig.length;
	dexp = z->exp - y->exp;
	zlen += dexp;
	if (zlen > SIGDIGLEN)
		zlen = SIGDIGLEN;
	while (z->sig.length < zlen)
		z->sig.text[z->sig.length++] = 0;
	ib = z->sig.text;
	i = ib + zlen;
	if (y->sig.length + dexp < zlen)
		i = ib + (y->sig.length + dexp);
	jb = y->sig.text;
	j = jb + (i - ib - dexp);
	jn = j;
	while (i > ib && j > jb)
	{
		--i;
		--j;
		if (*i < *j)
		{
			unsigned char *k = i - 1;
			while (*k == 0)
				--k;
			while (k != i)
			{
				--*k;
				*++k += 10;
			}
		}
		*i -= *j;
	}
	/* round */
	if (jn - jb < y->sig.length)
	{
		int round_down = 0;
		if (*jn < 5)
			round_down = 1;
		else if (*jn == 5)
		{
			unsigned char const *je = y->sig.text + y->sig.length;
			for (j = jn+1; j < je; ++j)
				if (*j != 0)
					goto done;
			i = ib + (jn - jb) + dexp - 1;
			if (*i & 1)
				round_down = 1;
		}
		if (round_down)
		{
			if (*i < 1)
			{
				unsigned char *k = i - 1;
				while (*k == 0)
					--k;
				while (k != i)
				{
					--*k;
					*++k += 10;
				}
			}
			*i -= 1;
		}
	}
done:
	/* normalize */
	for (i = ib; *i == 0; ++i)
		{}
	if (i > ib)
	{
		unsigned char dl = (unsigned char)(i - ib);
		z->exp -= dl;
		ie = ib + z->sig.length;
		for (; i < ie; ++i, ++ib)
			*ib = *i;
		z->sig.length -= dl;
	}
	/* trim */
	ib = z->sig.text;
	for (i = ib + z->sig.length; i > ib; )
	{
		--i;
		if (*i != 0)
			break;
	}
	z->sig.length = (unsigned char)(i - ib + 1);
}

#ifndef _TEST
static
#endif
void __num2dec_internal(decimal *d, double x)
{
	char sgn = (char)(signbit(x) != 0);
	/* Special cases */
	if (x == 0.0)
	{
		d->sgn = sgn;
		d->exp = 0;
		d->sig.length = 1;
		d->sig.text[0] = 0;
		return;
	}
	if (!isfinite(x))
	{
		d->sgn = sgn;
		d->exp = 0;
		d->sig.length = 1;
		d->sig.text[0] = (unsigned char)(isnan(x) ? 'N' : 'I');
		return;
	}
	/* Convert x to decimal */
	if (sgn)
		x = -x;
	{
	int exp;
	double frac = frexp(x, &exp);
	long num_bits_extract = DBL_MANT_DIG - __count_trailing_zero(frac);
	decimal int_d, pow2_d;
	__two_exp(&pow2_d, exp-num_bits_extract);
	__ull2dec(&int_d, (d_int)ldexp(frac, (int)num_bits_extract));
	__timesdec(d, &int_d, &pow2_d);
	d->sgn = sgn;
	}
}

void __num2dec(const decform *f, double x, decimal *d)
{
	short digits = f->digits;
	int i;
	__num2dec_internal(d, x);
	if (d->sig.text[0] > 9)
		return;
	/* Convert to external format */
	if (digits > SIGDIGLEN)
		digits = SIGDIGLEN;
	/* round length to digits */
	__rounddec(d, digits);
	/* pad length with 0 to digits */
	while (d->sig.length < digits)
		d->sig.text[d->sig.length++] = 0;
	/* Move decimal point from the right of digit 1 to the right of the last digit */
	d->exp -= d->sig.length - 1;
	/* Convert to ASCII */
	for (i = 0; i < d->sig.length; ++i)
		d->sig.text[i] += '0';
}

double __dec2num(const decimal *d)
{
	if (d->sig.length <= 0)
		return copysign(0.0, d->sgn == 0 ? 1.0 : -1.0);
	switch (d->sig.text[0])
	{
	case '0':
		return copysign(0.0, d->sgn == 0 ? 1.0 : -1.0);
	case 'I':
		return copysign((double)INFINITY, d->sgn == 0 ? 1.0 : -1.0);
	case 'N':
		{
		double result;
		d_int *ll = (d_int*)&result;
	#if _DOUBLE_BITS == 64
		*ll = 0x7FF0000000000000ULL;
		if (d->sgn)
			*ll |= 0x8000000000000000ULL;
	#ifndef _ENCODE_NAN
		*ll |= 0x0008000000000000ULL;
	#else
		if (d->sig.length == 1)
			*ll |= 0x0008000000000000ULL;
		else
		{
		#if __option(little_endian)
			unsigned char* p = (unsigned char*)&result + 6;
		#else
			unsigned char* p = (unsigned char*)&result + 1;
		#endif
			int placed_non_zero = 0;
			int low = 1;
			int i;
			int e = d->sig.length;
			if (e > 14)
				e = 14;
			for (i = 1; i < e; ++i)
			{
				unsigned char c = d->sig.text[i];
				if (isdigit(c))
					c -= '0';
				else
					c = (unsigned char)(tolower(c) - 'a' + 10);
				if (c != 0)
					placed_non_zero = 1;
				if (low)
				#if __option(little_endian)
					*p-- |= c;
				#else
					*p++ |= c;
				#endif
				else
					*p = (unsigned char)(c << 4);
				low = !low;
			}
			if (!placed_non_zero)
				*ll |= 0x0008000000000000;
		}
	#endif  /* _ENCODE_NAN */
	#elif _DOUBLE_BITS == 32
		*ll = 0x7F800000;
		if (d->sgn)
			*ll |= 0x80000000;
	#ifndef _ENCODE_NAN
		*ll |= 0x00400000;
	#else
		if (d->sig.length == 1)
			*ll |= 0x00400000;
		else
		{
		#if __option(little_endian)
			unsigned char* p = (unsigned char*)&result + 2;
		#else
			unsigned char* p = (unsigned char*)&result + 1;
		#endif
			int placed_non_zero = 0;
			int low = 0;
			int i;
			int e = d->sig.length;
			if (e > 7)
				e = 7;
			for (i = 1; i < e; ++i)
			{
				unsigned char c = d->sig.text[i];
				if (isdigit(c))
					c -= '0';
				else
					c = (unsigned char)(tolower(c) - 'a' + 10);
				if (c != 0)
					placed_non_zero = 1;
				if (low)
				#if __option(little_endian)
					*p-- |= c;
				#else
					*p++ |= c;
				#endif
				else
					*p |= (unsigned char)(c << 4);
				low = !low;
			}
			if (!placed_non_zero)
				*ll |= 0x00400000;
		}
	#endif  /* _ENCODE_NAN */
	#else
		#error __dec2num not supported
	#endif
		return result;
		}
	}
	{
	static double pow_10[8] = {1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
	/* Store *d in dec in internal format */
	decimal dec = *d;
	unsigned char *i = dec.sig.text;
	unsigned char *e = i + dec.sig.length;
	double first_guess;
	int exponent;
	for (; i < e; ++i)
		*i -= '0';
	dec.exp += dec.sig.length - 1;
	exponent = dec.exp;
	{ /* Check for numbers greater than the half-way point between DBL_MAX and INFINITY*/
	decimal max;
#if _DOUBLE_BITS == 64
	__str2dec(&max, "179769313486231580793728714053034151", 308);
#elif _DOUBLE_BITS == 32
	__str2dec(&max, "340282356779733661637539395458142568", 38);
#else
	#error __dec2num not supported
#endif
	if (__less_dec(&max, &dec))
		return copysign((double)INFINITY, d->sgn == 0 ? 1.0 : -1.0);
	}
	/* make first guess for the value of dec */
	i = dec.sig.text;
	first_guess = *i++;
	while (i < e)
	{
		unsigned long ival = 0;
		int j;
		double temp1, temp2;
		int ndig = (int)(e - i) % 8;
		if (ndig == 0)
			ndig = 8;
		for (j = 0; j < ndig; ++j, ++i)
			ival = ival * 10 + *i;
		temp1 = first_guess * pow_10[ndig-1];
		temp2 = temp1 + ival;
		if (ival != 0 && temp1 == temp2)
			break;
		first_guess = temp2;
		exponent -= ndig;
	}
	if (exponent < 0)
		first_guess /= pow(5.0, -exponent);
	else
		first_guess *= pow(5.0, exponent);
	first_guess = ldexp(first_guess, exponent);
	if (isinf(first_guess))
		first_guess = DBL_MAX; 
	{
	/* convert first guess back to dec form and see if you get the same result */
	decimal feedback1, feedback2, difflow, diffhigh;
	double next_guess;
	d_int *ull = (d_int*)&next_guess;
	int guessed_low = 0;
	__num2dec_internal(&feedback1, first_guess);
	if (__equals_dec(&feedback1, &dec))
		goto done;
	if (__less_dec(&feedback1, &dec))
		guessed_low = 1;
	next_guess = first_guess;
	while (1)
	{
		if (guessed_low)
		{
			++*ull;
			if (isinf(next_guess))
				goto done;
		}
		else
			--*ull;
		__num2dec_internal(&feedback2, next_guess);
		if (guessed_low && !__less_dec(&feedback2, &dec))
			break;
		else if (!guessed_low && !__less_dec(&dec, &feedback2))
		{
			difflow = feedback1;
			feedback1 = feedback2;
			feedback2 =  difflow;
			{
			double temp = first_guess;
			first_guess = next_guess;
			next_guess = temp;
			}
			break;
		}
		feedback1 = feedback2;
		first_guess = next_guess;
	}
	__minus_dec(&difflow, &dec, &feedback1);
	__minus_dec(&diffhigh, &feedback2, &dec);
	if (__equals_dec(&difflow, &diffhigh))
	{
		/* break tie with round to even */
		if (*(d_int*)&first_guess & 1)
			first_guess = next_guess;
	}
	else if (!__less_dec(&difflow, &diffhigh))
		first_guess = next_guess;
	}
done:
	if (dec.sgn)
		first_guess = -first_guess;
	return first_guess;
	}
}

#if __dest_os == __m56800_os 
#pragma optimize_for_size reset
#endif	


#endif /* ndef _No_Floating_Point */

/* Change record:
 * JFH 951019 First code release.
 * JFH 951207 Changed Inf and NaN from zero-divide expressions to bit-pattern
 *            references.  Be's SCO barfed on the expressions.
 * SCM 970715 Disabled when _No_Floating_Point defined.
 * hh  971206 fixed bug with __double_nan.
 * hh  010924 Rewrote.
 * hh  020402 Added 32 bit double
 * blc 021003 Fixed implicit conversion errors from Palm OS build
 */