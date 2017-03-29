/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/11 19:54:49 $
 * $Revision: 1.27 $
 */

/*
 *	Routines
 *	--------
 *		__wcstoul
 *
 *	Implementation
 *	--------------
 *			
 *		The string scanner is implemented as an extended Finite State Machine.
 *		A state diagram for it can be found in an accompanying TeachText
 *		document, 'wcstoul syntax' (too bad pictures can't be imbedded in
 *		document, 'strtod syntax' (too bad pictures can't be imbedded in
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
 *			Skip leading spaces. Process optional sign. Once a non-space is seen,
 *			trasition to next state.
 *			
 *		check_for_zero
 *			
 *			If 'base' is zero, then the base is either octal if there is a leading
 *			'0', hexadecimal if there is a leading '0X', or decimal if there is no
 *			leading zero at all. Also, if 'base' is 16, the leading '0X' may be
 *			optionally preset.
 *			
 *			If 'base' is zero or 16, check for a leading zero. If there one,
 *			transition to the next state. Otherwise, skip to state 'need_digit' to
 *			look for at least one digit (here a 'digit' is any alphanumeric; which
 *			'digits' are actually valid depends on the determined number base).
 *			
 *		leading_zero
 *			
 *			Having seen a leading zero, look for a subsequent 'X' (or 'x'). If
 *			present, the base is 16: transition to state 'need_digit' to look for
 *			at least one digit. If 'base' is zero, then the base must be 8.
 *			Transition to the state 'digit_loop' to scan the rest of the number.
 *			
 *		need_digit
 *		digit_loop
 *			
 *			The actions of these two states are identical. However, 'digit_loop'
 *			is a final state, whereas 'need_digit' is not (i.e., if scanning
 *			terminates in 'need_digit', the scan is invalid.
 *			
 *			If 'base' is still zero at this point, then the base must be 10.
 *			
 *			Loop on valid digits for the established base in this state,
 *			accumulating the corresponding numerical value. Keep on the lookout
 *			for overflow.
 *			
 *		finished
 *		failure
 *			
 *			These states are forced upon seeing the end of the numeric string in
 *			the combined need_digit/digit_loop state to signal whether the
 *			termination was valid or not.
 */

#pragma ANSI_strict off  /*- vss 990729 -*/
 
#include <ansi_parms.h> 
 
#if _MSL_WIDE_CHAR	/*- mm 980204 -*/

#if _MSL_C99																	/*- mm 030304 -*/

#pragma ANSI_strict reset

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <wchar.h>
#include <wctype.h>

enum scan_states {
	start           = 0x01,
	check_for_zero	= 0x02,
	leading_zero    = 0x04,
	need_digit      = 0x08,
	digit_loop      = 0x10,
	finished        = 0x20,
	failure         = 0x40
};

#define final_state(scan_state)	(scan_state & (finished | failure))

#define success(scan_state) (scan_state & (leading_zero | digit_loop | finished))

#define fetch()		(count++, (*wReadProc)(wReadProcArg, 0, __GetAwChar)) /*- mm 990311 -*/
#define unfetch(c)	(*wReadProc)(wReadProcArg, c, __UngetAwChar)		 /*- mm 990311 -*/

unsigned long _MSL_CDECL __wcstoul(int			base, 
						int			max_width,
						wint_t (*wReadProc)(void *, wint_t, int), /*- mm 990311 -*/
						void * wReadProcArg,					/*- mm 990311 -*/
						int		* chars_scanned,
						int		* negative,
						int		* overflow)
{
	int				scan_state = start;
	int				count      = 0;
	unsigned long	value      = 0;
	unsigned long	value_max  = 0;
	wchar_t				c;
	
	*negative = *overflow = 0;
	
	if (base < 0 || base == 1 || base > 36 || max_width < 1)
		scan_state = failure;
	else
		c = fetch();
	
	if (base)
		value_max	= ULONG_MAX / base;
	
	while (count <= max_width && c != EOF && !final_state(scan_state)) {
		switch (scan_state)
		{
			case start:
			
				if (iswspace(c))
				{
					c = fetch();
					
					break;
				}
				
				if (c == L'+')
					c = fetch();
				else if (c == L'-')
				{
					c = fetch();
					
					*negative = 1;
				}
				
				scan_state = check_for_zero;
				
				break;
			
			case check_for_zero:
				
				if (base == 0 || base == 16)
				{
					if (c == L'0')
					{
						scan_state = leading_zero;
						
						c = fetch();
						
						break;
					}
				}
				
				scan_state = need_digit;
				
				break;
			
			case leading_zero:
				
				if (c == L'X' || c == L'x')
				{
					base = 16;
					
					scan_state = need_digit;
					
					c = fetch();
					
					break;
				}
				
				if (base == 0)
					base = 8;
				
				scan_state = digit_loop;
				
				break;
			
			case need_digit:
			case digit_loop:
				
				if (base == 0)
					base = 10;
				
				if (!value_max)
					value_max	= ULONG_MAX / base;
				
				if (iswdigit(c))
				{
					if ((c -= L'0') >= base)
					{
						if (scan_state == digit_loop)
							scan_state = finished;
						else
							scan_state = failure;
						
						c += L'0';
						
						break;
					}
				}
				else if (!iswalpha(c) || (toupper(c) - L'A' + 10) >= base)
				{
					if (scan_state == digit_loop)
						scan_state = finished;
					else
						scan_state = failure;
					
					break;
				}
				else
					c = towupper(c) - L'A' + 10;
				
				if (value > value_max)
					*overflow = 1;
				
				value *= base;
				
				if (c > (ULONG_MAX - value))
					*overflow = 1;
				
				value += c;
				
				scan_state = digit_loop;	/* In case we entered in state need_digit */
				
				c = fetch();
				
				break;				
			
		}
	}
	
	if (!success(scan_state))
		count = value = 0;
	else
		count--;
	
	*chars_scanned = count;
	
	unfetch(c);
	
	return(value);
}


#if (_MSL_LONGLONG && _MSL_C99)      /*- mm 970110 -*/ /*- mm 030225 -*/
unsigned long long _MSL_CDECL __wcstoull(int		  base, 
								int		  max_width,
								wint_t (*wReadProc)(void *, wint_t, int), /*- mm 990311 -*/
								void * wReadProcArg,					/*- mm 990311 -*/
								int		* chars_scanned,
								int		* negative,
								int		* overflow)
{
	int				   scan_state = start;
	int				   count      = 0;
	unsigned long long value      = 0;
	unsigned long long value_max  = 0;
	unsigned long long ullmax     = ULLONG_MAX;      /*- mm 970102 -*/
	wchar_t				   c;
	
	*negative = *overflow = 0;
	
	if (base < 0 || base == 1 || base > 36 || max_width < 1)
		scan_state = failure;
	else
		c = fetch();
	
	if (base)
		value_max	= ullmax / base;                  /*- mm 970102 -*/
	
	while (count <= max_width && c != EOF && !final_state(scan_state)) {
		switch (scan_state)
		{
			case start:
			
				if (iswspace(c))
				{
					c = fetch();
					
					break;
				}
				
				if (c == L'+')
					c = fetch();
				else if (c == L'-')
				{
					c = fetch();
					
					*negative = 1;
				}
				
				scan_state = check_for_zero;
				
				break;
			
			case check_for_zero:
				
				if (base == 0 || base == 16)
				{
					if (c == L'0')
					{
						scan_state = leading_zero;
						
						c = fetch();
						
						break;
					}
				}
				
				scan_state = need_digit;
				
				break;
			
			case leading_zero:
				
				if (c == L'X' || c == L'x')
				{
					base = 16;
					
					scan_state = need_digit;
					
					c = fetch();
					
					break;
				}
				
				if (base == 0)
					base = 8;
				
				scan_state = digit_loop;
				
				break;
			
			case need_digit:
			case digit_loop:
				
				if (base == 0)
					base = 10;
				
				if (!value_max)
					value_max	= ullmax / base;             /*- mm 970102 -*/
				
				if (iswdigit(c))
				{
					if ((c -= L'0') >= base)
					{
						if (scan_state == digit_loop)
							scan_state = finished;
						else
							scan_state = failure;
						
						c += L'0';
						
						break;
					}
				}
				else if (!iswalpha(c) || (towupper(c) - L'A' + 10) >= base)
				{
					if (scan_state == digit_loop)
						scan_state = finished;
					else
						scan_state = failure;
					
					break;
				}
				else
					c = towupper(c) - L'A' + 10;
				
				if (value > value_max)
					*overflow = 1;
				
				value *= base;
				
				if (c > (ullmax - value))            /*- mm 970102 -*/
					*overflow = 1;
				
				value += c;
				
				scan_state = digit_loop;	/* In case we entered in state need_digit */
				
				c = fetch();
				
				break;				
			
		}
	}
	
	if (!success(scan_state))
		count = value = 0;
	else
		count--;
	
	*chars_scanned = count;
	
	unfetch(c);
	
	return(value);
}
#endif  /* _MSL_LONGLONG    */                               /*- mm 970110 -*/

unsigned long _MSL_CDECL wcstoul(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end, int base)
{
	unsigned long		value;
	int					count, negative, overflow;
	
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
	
	value = __wcstoul(base, INT_MAX, &__wStringRead, (void *)&wisc, &count, &negative, &overflow);
	
	if (end)
		*end = (wchar_t *) str + count;
	
	if (overflow)
	{
		value = ULONG_MAX;
		errno = ERANGE;
	} else if (negative)
		value = -value;
	
	return(value);
}


#if (_MSL_LONGLONG && _MSL_C99)                  /*- mm 970110 -*/ /*- mm 030225 -*/
unsigned long long _MSL_CDECL wcstoull(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end, int base)
{
	unsigned long long	value;
	int					count, negative, overflow;
	
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
	
	value = __wcstoull(base, INT_MAX, &__wStringRead, (void *)&wisc, &count, &negative, &overflow);
	
	if (end)
		*end = (wchar_t*) str + count;
	
	if (overflow)
	{
		value = ULLONG_MAX;                          /*- mm 970102 -*/
		errno = ERANGE;
	} else if (negative)
		value = -value;
	
	return(value);
}
#endif       /*_MSL_LONGLONG*/                /*- mm 970110 -*/

long _MSL_CDECL wcstol(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end, int base)
{
	unsigned long		uvalue;
	long						svalue;
	int							count, negative, overflow;
		
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
	
	uvalue = __wcstoul(base, INT_MAX, &__wStringRead, (void *)&wisc, &count, &negative, &overflow);
	
	if (end)
		*end = (wchar_t *) str + count;
	
	if (overflow || (!negative && uvalue > LONG_MAX) || (negative && uvalue > -LONG_MIN))
	{
		svalue = (negative ? -LONG_MIN : LONG_MAX);
		errno = ERANGE;
	} else
		svalue = (negative ? -uvalue : uvalue);
	
	return(svalue);
}

#if (_MSL_LONGLONG && _MSL_C99)						/*- mm 981023 -*/ /*- mm 030225 -*/
long long _MSL_CDECL wcstoll(const wchar_t * _MSL_RESTRICT str, wchar_t ** _MSL_RESTRICT end, int base)
{
	unsigned long long	uvalue;
	long long 			svalue;
	int			    	count, negative, overflow;
	
	__wInStrCtrl wisc;
	wisc.wNextChar         = (wchar_t *)str;
	wisc.wNullCharDetected = 0;
	
	uvalue = __wcstoull(base, INT_MAX, &__wStringRead, (void *)&wisc, &count, &negative, &overflow);
	
	if (end)
		*end = (wchar_t *) str + count;
	
	if (overflow || (!negative && uvalue > LLONG_MAX) ||               /*- mm 970102 -*/
	                            (negative && uvalue > -LLONG_MIN))     /*- mm 970102 -*/
	{
		svalue = (negative ? -LLONG_MIN : LLONG_MAX);               /*- mm 970102 -*/
		errno = ERANGE;
	} else
		svalue = (negative ? -uvalue : uvalue);
	
	return(svalue);
}
#endif      /*_MSL_LONGLONG*/           /*- mm 970110 -*/

int _MSL_CDECL watoi(const wchar_t * str)
{
	return(wcstol(str, NULL, 10));
}

long _MSL_CDECL watol(const wchar_t * str)
{
	return(wcstol(str, NULL, 10));
}

#endif /* _MSL_C99 */							/*- mm 030304 -*/
#endif /* #if _MSL_WIDE_CHAR */					/*- mm 981030 -*/

/* Change record:
 * JCM 980128 First code release.
 * BLC 980324 Fixed prototypes to match C9X standard in second parameter
 * mm  980720 Added support for inttypes.h
 * mm  981029 Added non longlong support for wcstoimax and wcstoumax
 * mm  981030 Added #if _MSL_WIDE_CHAR wrappers
 * mm  990325 Changes to separate input from file i/o
 * mm  990817 Deleted include of <string_io.h>
 * mm  000515 Deleted definitions of wcstoimax and wcstoumax, now covered in cinttabs.
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030225 Added wrappers for LLONG_MAX and LLONG_MIN
 * mm  030304 Added _MSL_C99 wrapper
 */