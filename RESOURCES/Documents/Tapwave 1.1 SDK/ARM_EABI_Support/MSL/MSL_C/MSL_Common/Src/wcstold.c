/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/11 19:55:37 $
 * $Revision: 1.37 $
 */

/*
 *	Routines
 *	--------
 *		wcstold
 *		wcstod
 *		wcstof
 *
 *	Implementation
 *	--------------
 *			
 *		The string scanner is implemented as an extended Finite State Machine.
 *		A state diagram for it can be found in an accompanying TeachText
 *		document, 'wcstod syntax' (too bad pictures can't be imbedded in
 *		comments) in the "MSL Technical Notes" directory. A textual description
 *      of it follows.
 *			
 *		The state transition loop dispatches to the appropriate code for the
 *		current state, while simultaneously watching for terminating
 *		conditions (field width exhausted, EOF encountered, final state
 *		reached).
 *			
 *		start
 *			
 *			Skip leading spaces. Once a non-space is seen, process sign (if any)
 *			and trasition to next state.
 *			
 *		sig_start
 *			
 *			Look for either a digit or a decimal point. If it is a digit zero,
 *			treat it specially.
 *			
 *		leading_sig_zeroes
 *			
 *			Leading zero digits are discarded, as they add nothing to the result.
 *			
 *		int_digit_loop
 *			
 *			Process digits from the integer part of the significand. We accept
 *			only so many significant digits (DBL_DIG), but the ones we discard
 *			have to be accounted for in the exponent.
 *			
 *			If a decimal point is seen, proceed to process a fractional part (if
 *			one is present).
 *			
 *		frac_start
 *			
 *			Having seen a leading decimal point, we must see at least one digit.
 *			If the field width expires before the transition from this state to
 *			the next, we fail.
 *			
 *		frac_digit_loop
 *			
 *			Process digits from the fractional part of the significand. We accept
 *			only so many significant digits (DBL_DIG), but the ones we discard
 *			have to be accounted for in the exponent.
 *		sig_end
 *			
 *			If an 'E' (or 'e') follows we go after an exponent; otherwise we're
 *			done.
 *			
 *		exp_start
 *			
 *			Process the sign (if any).
 *			
 *		leading_exp_digit
 *			
 *			Check the leading exponent digit. If it is a digit zero, treat it
 *			specially.
 *			
 *		leading_exp_zeroes
 *			
 *			Leading zero digits are discarded, as they add nothing to the result.
 *			
 *		exp_digit_loop
 *			
 *			Process digits from the exponent. We watch for short int overflow,
 *			even though the maximum exponent is probably considerably less than
 *			this. The latter will be checked during the actual decimal to binary
 *			conversion.
 *			
 *		finished
 *			
 *			Successful exit.
 *			
 *		failure
 *			
 *			Invalid input exit.
 *
 *		The end product is just the parsed input and its conversion to a
 *		'decimal' record � la SANE and MathLib. '__dec2num' is used for conversion
 *		to binary. For other systems that don't provide decimal to binary
 *		conversion in this or a similar way, a routine will be provided.
 */

#pragma ANSI_strict off  /*- vss 990729 -*/

#include <ansi_parms.h> 

#if !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)

#if _MSL_WIDE_CHAR	/*- mm 980204 -*/

#if _MSL_C99 											/*- mm 030304 -*/

#pragma ANSI_strict reset

#include <ansi_fp.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <lconv.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <msl_thread_local_data.h>

enum scan_states {
	start				= 0x0001,
	sig_start			= 0x0002,
	leading_sig_zeroes	= 0x0004,
	int_digit_loop		= 0x0008,
	frac_start			= 0x0010,
	frac_digit_loop		= 0x0020,
	sig_end				= 0x0040,
	exp_start			= 0x0080,
	leading_exp_digit	= 0x0100,
	leading_exp_zeroes	= 0x0200,
	exp_digit_loop		= 0x0400,
	finished			= 0x0800,
	failure				= 0x1000
};

#define MAX_SIG_DIG 20               /*- mm 970609 -*/

#define final_state(scan_state)	(scan_state & (finished | failure))

#define success(scan_state) (scan_state & (	leading_sig_zeroes	|			\
										int_digit_loop			|			\
										frac_digit_loop			|			\
										leading_exp_zeroes		|			\
										exp_digit_loop			|			\
										finished		))

#define fetch()		(count++, (*wReadProc)(wReadProcArg, 0, __GetAwChar)) /*- mm 990311 -*/
#define unfetch(c)	(*wReadProc)(wReadProcArg, c, __UngetAwChar)		  /*- mm 990311 -*/

long double _MSL_CDECL __wcstold(	int			max_width,
						wint_t (*wReadProc)(void *, wint_t, int), 	/*- mm 990311 -*/
						void * wReadProcArg,						/*- mm 990311 -*/
						int		* chars_scanned,
						int		* overflow)
{
	int			scan_state		= start;
	int			count			= 0;
	int         spaces          = 0;     /*- mm 970708 -*/
	wchar_t		c;
	decimal		d				= {0, 0, 0, {0, ""}};
	int			sig_negative	= 0;
	int			exp_negative	= 0;
	long		exp_value		= 0;
	int			exp_adjust		= 0;
	long double	result;
	wchar_t		radix_marker;														/*- mm 011130 -*/
	
	#if _MSL_C_LOCALE_ONLY
		radix_marker = '.';
	#else
		radix_marker = 	(wchar_t)(* (unsigned char *) _MSL_LOCALDATA(__lconv).decimal_point);			/*- mm 011130 -*/
	#endif
	*overflow = 0;
	
	c = fetch();
	
	while (count <= max_width && c != EOF && !final_state(scan_state)) 
	{

		switch (scan_state)
		{
			case start:
			
				if (iswspace(c))
				{
					c = fetch();
					count--;    /*- mani 970101 -*/
					spaces++;   /*- mani 970101 -*/
					
					break;
				}
				
				if (c == L'+')
					c = fetch();
				else if (c == L'-')
				{
					c = fetch();
					
					sig_negative = 1;
				}
				
				scan_state = sig_start;
				
				break;
			
			case sig_start:
				
				if (c == radix_marker)							/*- mm 011130 -*/
				{
					scan_state = frac_start;
					
					c = fetch();
					
					break;
				}
				
				if (!iswdigit(c))
				{
					scan_state = failure;
					
					break;
				}
				
				if (c == L'0')
				{
					scan_state = leading_sig_zeroes;
					
					c = fetch();
					
					break;
				}
				
				scan_state = int_digit_loop;
				
				break;
			
			case leading_sig_zeroes:
			
				if (c == L'0')
				{
					c = fetch();
					
					break;
				}
				
				scan_state = int_digit_loop;
				
				break;
			
			case int_digit_loop:
				
				if (!iswdigit(c))
				{
					if (c == radix_marker)						/*- mm 011130 -*/
					{
						scan_state = frac_digit_loop;
						
						c = fetch();
					}
					else
						scan_state = sig_end;
					
					break;
				}
				
				if (d.sig.length < MAX_SIG_DIG)          /*- mm 970609 -*/
					d.sig.text[d.sig.length++] = c;
				else
					exp_adjust++;
				
				c = fetch();
				
				break;
			
			case frac_start:
				
				if (!iswdigit(c))
				{
					scan_state = failure;
					
					break;
				}
				
				scan_state = frac_digit_loop;
				
				break;
			
			case frac_digit_loop:
				
				if (!iswdigit(c))
				{
					scan_state = sig_end;
					
					break;
				}
				
				if (d.sig.length < MAX_SIG_DIG)                /*- mm 970609 -*/
				{
					if ( c != L'0' || d.sig.length)				/* __dec2num doesn't like leading zeroes*/
						d.sig.text[d.sig.length++] = c;
					exp_adjust--;
				}
				
				c = fetch();
				
				break;
			
			case sig_end:
				
				if (c == L'E' || c == L'e')
				{
					scan_state = exp_start;
					
					c = fetch();
					
					break;
				}
				
				scan_state = finished;
				
				break;
			
			case exp_start:
				
				if (c == L'+')
					c = fetch();
				else if (c == L'-')
				{
					c = fetch();
					
					exp_negative = 1;
				}
				
				scan_state = leading_exp_digit;
				
				break;
			
			case leading_exp_digit:
				
				if (!iswdigit(c))
				{
					scan_state = failure;
					
					break;
				}
				
				if (c == L'0')
				{
					scan_state = leading_exp_zeroes;
					
					c = fetch();
					
					break;
				}
				
				scan_state = exp_digit_loop;
				
				break;
			
			case leading_exp_zeroes:
			
				if (c == L'0')
				{
					c = fetch();
					
					break;
				}
				
				scan_state = exp_digit_loop;
				
				break;
			
			case exp_digit_loop:
				
				if (!iswdigit(c))
				{
					scan_state = finished;
					
					break;
				}
				
				exp_value = exp_value*10 + (c - L'0');
				
				if (exp_value > SHRT_MAX)
					*overflow = 1;
				
				c = fetch();
				
				break;
		}
	}
	
	if (!success(scan_state))
	{
		count = 0;   /*- mf 092497 -*/
		*chars_scanned=0;
	}
	else
	{
		count--;
		*chars_scanned = count + spaces; /*- mani 970101 -*/
	}
	
	unfetch(c);
	
	if (exp_negative)
		exp_value = -exp_value;
	
	{
		int							n = d.sig.length;
		unsigned char * p = &d.sig.text[n];
		
		while (n-- && *--p == '0')
			exp_adjust++;
		
		d.sig.length = n + 1;
		
		if (d.sig.length == 0)
			d.sig.text[d.sig.length++] = '0';
	}
	
	exp_value += exp_adjust;
	
	if (exp_value < SHRT_MIN || exp_value > SHRT_MAX)
		*overflow = 1;
	
	if (*overflow)
		if (exp_negative)
			return(0.0);
		else
			return(sig_negative ? -HUGE_VAL : HUGE_VAL);
	
	d.exp = exp_value;
	
	result = __dec2num(&d);

/*
 *	Note: If you look at <ansi_fp.h> you'll see that __dec2num only supports double.
 *				If you look at <float.h> you'll see that long double == double. Ergo, the
 *				difference is moot *until* a truly long double type is supported.
 */
	
	if (result != 0.0 && result < LDBL_MIN)
	{
		*overflow = 1;
		result    = 0.0;
	}
	else if (result > LDBL_MAX)
	{
		*overflow = 1;
		result    = HUGE_VAL;
	} 
	
	if (sig_negative)
		result = -result;
	
	return(result);
}

double _MSL_CDECL wcstod(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end)
{
	long double	value, abs_value;
	int					count, overflow;
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
		
	value = __wcstold(INT_MAX, &__wStringRead, (void *)&wisc, &count, &overflow);
	
	if (end)
		*end = (wchar_t*) str + count;
	
	abs_value = fabs(value);
	
	if (overflow || (value != 0.0 && (abs_value < DBL_MIN || abs_value > DBL_MAX)))
		errno = ERANGE;
	
	return(value);
}

/*- mm 021112 -*/
long double _MSL_CDECL wcstold(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end)
{
	long double	value, abs_value;
	int					count, overflow;
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
		
	value = __wcstold(INT_MAX, &__wStringRead, (void *)&wisc, &count, &overflow);
	
	if (end)
		*end = (wchar_t*) str + count;
	
	abs_value = fabs(value);
	
	if (overflow || (value != 0.0 && (abs_value < DBL_MIN || abs_value > DBL_MAX)))
		errno = ERANGE;
	
	return(value);
}

float _MSL_CDECL wcstof(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end)
{
	long double	value, abs_value;
	int					count, overflow;
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
		
	value = __wcstold(INT_MAX, &__wStringRead, (void *)&wisc, &count, &overflow);
	
	if (end)
		*end = (wchar_t*) str + count;
	
	abs_value = fabs(value);
	
	if (overflow || (value != 0.0 && (abs_value < DBL_MIN || abs_value > DBL_MAX)))
		errno = ERANGE;
	
	return((float)value);
}
/*- mm 021112 -*/
/*
double _MSL_CDECL watof(const wchar_t * str)
{
	return(wcstod(str, NULL));
}*/
#endif  /* _MSL_C99 */					/*- mm 030304 -*/
#endif  /* _MSL_WIDE_CHAR*/				/*- mm 981020 -*/
#endif  /* !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB) */

/* Change record:
 * JFH 950622 First code release.
 * JFH 950727 Removed stray SysBreak(). Added code to make use of the remembered sign of
 *			  of the significand.
 * JFH 950929 Discovered __dec2num doesn't like leading zeroes except for zeroes, so numbers
 *			  like .01 would get interpreted as zero. Fixed by suppressing leading zeroes.
 * JFH 951114 Fixed bug in wcstod where value was checked against DBL_MIN and DBL_MAX instead
 *			  of the absolute value.
 * JFH 960425 Changed __wcstold to return -HUGE_VAL instead of HUGE_VAL on overflow if a
 *			  minus sign was previously detected.
 * mani970101 Fix a scanf bug dealing with white space. Things like
 *			  scanf("%5lx") weren't working properly when there was
 *			  white space.
 * mm  970609 Changed the max number of significant digits to MAX_SIG_DIG(==32) instead of DBL_DIG
 * mm  970708 Inserted Be changes
 * mf  970924 If there are no digits in the string then the value of &endp must remain unchanged
 *            In this case the variable chars_scanned of wcstold should be 0
 * JCM 980121 First wchar release.
 * mm  980206 Added cide to handle wide char unget properly and implementation of fwide.
 * blc 980324 Fixed prototypes to match latest C9X standard (wchar_t** as
 *            second parameter)
 * mm  981020 Added #if _MSL_WIDE_CHAR wrappers
 * mm  990315 Corrected encoding of dot for wide characters IL9903_1178
 * mm  990325 Changes to separate char input from file i/o
 * mm  990817 Deleted include of <string_io.h>
 * mm  010503 Added code for thread local storage for lconv
 * mm  010521 Added _MWMT wrappers
 * cc  010531 Added _GetThreadLocalData's flag
 * mm  011130 Changes for implementation of locale
 * cc  011203 Added _MSL_CDECL for new name mangling
 * blc 011211 Added _MSL_NO_MATH_LIB macro check
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 * JWW 020604 Added _MSL_LOCALDATA macro to make multithread code easier to read
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * cc  021022 Added _MSL_C_LOCALE_ONLY around the radix_marker
 * JWW 021031 Made thread local data available for Mach-O
 * mm  021112 Added wcstold() and wcstof().
 * cc  021119 Moved watof from the C lib to extras
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added _MSL_C99 wrapper
 */