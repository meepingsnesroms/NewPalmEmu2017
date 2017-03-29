/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/14 21:34:26 $
 * $Revision: 1.16 $
 */

// complex.cpp

#include <complex>

#if !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)

#endif // !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)

// hh  971220 fixed MOD_INCLUDE
// mf  980130 merged in division algorithm
// hh  980408 wrapped in #ifndef _No_Floating_Point
// hh  990120 changed name of MSIPL flags
// hh  991230 Fixed up _MSL_CX_LIMITED_RANGE version s*= and /= to work when this == &rhs
// blc 011211 Added _MSL_NO_MATH_LIB check
// hh  020226 No longer support compilers that don't support member templates
