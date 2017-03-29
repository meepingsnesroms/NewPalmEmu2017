/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/01 16:08:37 $
 * $Revision: 1.50.2.1 $
 */

#ifndef _MSL_MATH_H
#define _MSL_MATH_H

#include <ansi_parms.h>

#if !_MSL_USING_MW_C_HEADERS
	#error You must have the non-MSL C header file access path before the MSL access path
#else

#include <cmath>

#if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE) && defined(_MSL_CMATH_DEFINED_MATH_ITEMS)
	#if !(__m56800E__ || __m56800__ )
	using std::acos;
	using std::acosf;
	using std::acosh;
	using std::acoshf;
	using std::acoshl;
	using std::acosl;
	using std::asin;
	using std::asinf;
	using std::asinh;
	using std::asinhf;
	using std::asinhl;
	using std::asinl;
	using std::atan;
	using std::atan2;
	using std::atan2f;
	using std::atan2l;
	using std::atanf;
	using std::atanh;
	using std::atanhf;
	using std::atanhl;
	using std::atanl;
	#endif  /* !(__m56800E__ || __m56800__ ) */
	using std::cbrt;
	using std::cbrtf;
	using std::cbrtl;
	#if !(__m56800E__ || __m56800__ )
	using std::ceil;
	using std::ceilf;
	using std::ceill;
	using std::copysign;
	using std::copysignf;
	using std::copysignl;
	using std::cos;
	using std::cosf;
	using std::cosh;
	using std::coshf;
	using std::coshl;
	using std::cosl;
	#endif /*  !(__m56800E__ || __m56800__ ) */

#if _MSL_C99											/*- mm 030521 -*/

	using std::erf;
	using std::erfc;
	using std::erfcf;
	using std::erfcl;
	using std::erff;
	using std::erfl;

#endif /* _MSL_C99 */									/*- mm 030521 -*/

	using std::exp;
	#if !(__m56800E__ || __m56800__ )
	using std::exp2;
	using std::exp2f;
	using std::exp2l;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::expf;
	using std::expl;
	#if !(__m56800E__ || __m56800__ )
	using std::expm1;
	using std::expm1f;
	using std::expm1l;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::fabs;
	using std::fabsf;
	using std::fabsl;
	#if !(__m56800E__ || __m56800__ )

#if _MSL_C99											/*- mm 030521 -*/
	using std::fdim;
	using std::fdimf;
	using std::fdiml;
	using std::floor;
	using std::floorf;
	using std::floorl;
#endif  /* _MSL_C99 */ 									/*- mm 030521 -*/
	using std::fma;
	using std::fmaf;
	using std::fmal;
	using std::fmax;
	using std::fmaxf;
	using std::fmaxl;
	using std::fmin;
	using std::fminf;
	using std::fminl;
	using std::fmod;
	#endif  /* !(__m56800E__ || __m56800__ ) */
	using std::fmodf;
	#if !(__m56800E__ || __m56800__ )
	using std::fmodl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::frexp;
	using std::frexpf;
	using std::frexpl;
	#if !(__m56800E__ || __m56800__ )	
	using std::hypot;
	using std::hypotf;
	using std::hypotl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::ilogb;
	using std::ilogbf;
	using std::ilogbl;
	using std::ldexp;
	using std::ldexpf;
	using std::ldexpl;
	using std::lgamma;
	using std::lgammaf;
	using std::lgammal;
	#if _MSL_LONGLONG
	using std::llrint;
	using std::llrintf;
	using std::llrintl;
	#if !_MSL_USES_SUN_MATH_LIB	
	using std::llround;
	using std::llroundf;
	using std::llroundl;
	#endif /* !_MSL_USES_SUN_MATH_LIB */
	#endif /* _MSL_LONGLONG */
	using std::log;
	using std::log10;
	using std::log10f;
	using std::log10l;
	#if !(__m56800E__ || __m56800__ )
	using std::log1p;
	using std::log1pf;
	using std::log1pl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::log2;
	using std::log2f;
	using std::log2l;
	#if !(__m56800E__ || __m56800__ )
	using std::logb;
	using std::logbf;
	using std::logbl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::logf;
	using std::logl;
	#if !(__m56800E__ || __m56800__ || _MSL_USES_SUN_MATH_LIB)
	using std::lrint;
	using std::lrintf;
	using std::lrintl;
	using std::lround;
	using std::lroundf;
	using std::lroundl;
	#endif
	#if !(__m56800E__ || __m56800__ )
	using std::modf;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::modff;
	using std::modfl;
	using std::nan;
	using std::nanf;
	using std::nanl;
	#if !(__m56800E__ || __m56800__ || _MSL_USES_SUN_MATH_LIB)
	using std::nearbyint;
	using std::nearbyintf;
	using std::nearbyintl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::nextafter;
	using std::nextafterf;
	using std::nextafterl;
	using std::nexttoward;
	using std::nexttowardf;
	using std::nexttowardl;
	using std::pow;
	using std::powf;
	using std::powl;
	#if !(__m56800E__ || __m56800__ )
	using std::remainder;
	using std::remainderf;
	using std::remainderl;
	#if !_MSL_USES_SUN_MATH_LIB
	using std::remquo;
	using std::remquof;
	using std::remquol;
	#endif
	using std::rint;
	using std::rintf;
	using std::rintl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	#if !(_MSL_USES_SUN_MATH_LIB || __m56800E__)
	using std::round;
	using std::roundf;
	using std::roundl;
	using std::scalbln;
	using std::scalblnf;
	using std::scalblnl;
	#endif /* !(__PPCGEKKO__ || defined(__arm) || __m56800E__) */
	using std::scalbn;
	using std::scalbnf;
	using std::scalbnl;
	#if !(__m56800E__ || __m56800__ )
	using std::sin;
	using std::sinf;
	using std::sinh;
	using std::sinhf;
	using std::sinhl;
	using std::sinl;
	using std::sqrt;
	using std::sqrtf;
	using std::sqrtl;
	using std::tan;
	using std::tanf;
	using std::tanh;
	using std::tanhf;
	using std::tanhl;
	using std::tanl;
	#endif /* !(__m56800E__ || __m56800__ ) */
	using std::tgamma;
	using std::tgammaf;
	using std::tgammal;
	#if !(__m56800E__ || __m56800__ || _MSL_USES_SUN_MATH_LIB)
	using std::trunc;
	using std::truncf;
	using std::truncl;
	#endif /* !(__m56800E__ || __m56800__ ) || _MSL_USES_SUN_MATH_LIB)*/
	
	#if __dest_os != __mac_os_x
		using std::abs;
		
		using std::float_t;
		using std::double_t;
	#endif /* __dest_os != __mac_os_x */
#endif /* __cplusplus && _MSL_USING_NAMESPACE && _MSL_CMATH_DEFINED_MATH_ITEMS */

#endif /* _MSL_USING_MW_C_HEADERS */

#endif /* _MSL_MATH_H */

/* Change record: 
 * hh  971206 Created.
 * hh  991112 Fixed using bug.
 * hh  000804 Protected against <fp.h> being included first (on Mac)
 * hh  000925 Fixed up <fp.h> protection on 68K
 * JWW 001208 Added case for targeting Mach-O
 * JWW 011027 Use _MSL_USING_MW_C_HEADERS as generic header test instead of specific Mach-O test
 * JWW 011029 No longer test for Mac 68K
 * blc 011211 Added _MSL_NO_MATH_LIB check
 * ejs 020129 This file is generated from a script now.
 * ejs 020130 Added float_t and double_t to namespace std
 * JWW 020205 Fixed up <fp.h> protection for Mach-O MSL C
 * JWW 020422 Test for _MSL_CMATH_DEFINED_MATH_ITEMS instead of __FP__
 * cc  020819 Round and family not supported by sun math
 * cc  020910 DSP does not support full math lib
 * cc  021022 Added ilogb and cbrt to arm and gcn
 * mm  021108 Changed some wrappers for new math functions in math.c
 * cc  021216 Added cbrt and family for Michael
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * mm  030521 Added C99 wrappers
 */