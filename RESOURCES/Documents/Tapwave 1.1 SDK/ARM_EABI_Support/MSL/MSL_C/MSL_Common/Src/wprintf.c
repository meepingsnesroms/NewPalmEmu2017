/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/11 19:51:01 $
 * $Revision: 1.37 $
 */

/*
 *	Routines
 *	--------
 *		wprintf				
 *		fwprintf			
 *		swprintf			
 *	
 *		vwprintf			
 *		vswprintf			
 *		vfwprintf			
 */

#pragma ANSI_strict off  							/*- vss 990729 -*/

#include <ansi_parms.h>

#if _MSL_WIDE_CHAR								/*- mm 980204 -*/

#if _MSL_C99									/*- mm 030304 -*/

#pragma ANSI_strict reset

#include <ansi_parms.h>  
#include <errno.h>
#include <stddef.h>      

#include <ansi_fp.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>									/*- mm 011130 -*/
#include <lconv.h>									/*- mm 011130 -*/
#include <critical_regions.h>						/*- mm 001018 -*/


#define conversion_buff_size	512
#define conversion_max			509
#define bad_conversion			0xFFFF

enum justification_options {
	left_justification,
	right_justification,
	zero_fill
};

enum sign_options {
	only_minus,
	sign_always,
	space_holder
};

enum argument_options {
	normal_argument,
	char_argument,
	short_argument,
	long_argument,
#if _MSL_LONGLONG         				/*- mm 961219 -*/
	long_long_argument,                 				/*- mm 961219 -*/
#endif                                  				/*- mm 961219 -*/
	long_double_argument,
	wchar_argument										/*- mm 990322 -*/

};

#define MAX_SIG_DIG 32                 					/*- mm 970609 -*/

typedef struct {
	unsigned char	justification_options;
	unsigned char 	sign_options;
	unsigned char 	precision_specified;
	unsigned char	alternate_form;
	unsigned char 	argument_options;
	wchar_t			conversion_char;					/*- mm 990701 -*/
	int				field_width;
	int				precision;
} print_format;



static const wchar_t * parse_format(const wchar_t * format_string, va_list * arg, print_format * format)
{
	print_format		f;
	const wchar_t *	s = format_string;
	wchar_t				c;
	int					flag_found;
	
	f.justification_options	= right_justification;
	f.sign_options			= only_minus;
	f.precision_specified   = 0;
	f.alternate_form		= 0;
	f.argument_options		= normal_argument;
	f.field_width			= 0;
	f.precision				= 0;
	
	if ((c = *++s) == L'%')
	{
		f.conversion_char = c;
		*format = f;
		return((const wchar_t *) s + 1);
	}
	
	for (;;)
	{
		flag_found = 1;
		
		switch (c)
		{
			case L'-':
				
				f.justification_options = left_justification;
				
				break;
			
			case L'+':
				
				f.sign_options = sign_always;
				
				break;
			
			case L' ':
				
				if (f.sign_options != sign_always)
					f.sign_options = space_holder;
					
				break;
			
			case L'#':
				
				f.alternate_form = 1;
				
				break;
			
			case L'0':
				
				if (f.justification_options != left_justification)
					f.justification_options = zero_fill;
				
				break;
			
			default:
				
				flag_found = 0;
		}
		
		if (flag_found)
			c = *++s;
		else
			break;
	}
	
	if (c == L'*')
	{
		if ((f.field_width = va_arg(*arg, int)) < 0)
		{
			f.justification_options = left_justification;
			f.field_width           = -f.field_width;
		}
		
		c = *++s;
	}
	else
		while (iswdigit(c))
		{
			f.field_width = (f.field_width * 10) + (c - L'0');
			c = *++s;
		}
	
	if (f.field_width > conversion_max)
	{
		f.conversion_char = bad_conversion;
		*format = f;
		return((const wchar_t *) s + 1);
	}
	
	if (c == L'.')
	{
		f.precision_specified = 1;
		
		if ((c = *++s) == L'*')
		{
			if ((f.precision = va_arg(*arg, int)) < 0)
				f.precision_specified = 0;
			
			c = *++s;
		}
		else
			while (iswdigit(c))
			{
				f.precision = (f.precision * 10) + (c - L'0');
				c = *++s;
			}
	}
	
	flag_found = 1;
	
	switch (c)
	{
		case L'h':
			
			f.argument_options = short_argument;
			if (s [1] == L'h')								/*- mm 990630 -*/
			{												/*- mm 990630 -*/
				f.argument_options = char_argument;			/*- mm 990630 -*/
				c = *++s; /* move past second h */			/*- mm 990630 -*/
			}												/*- mm 990630 -*/
			
			break;
		
		case L'l':
			
			f.argument_options = long_argument;
#if _MSL_LONGLONG										/*- mm 990701 -*/
			if (s [1] == 'l')										/*- mm 990701 -*/
			{														/*- mm 990701 -*/
				f.argument_options = long_long_argument;			/*- mm 990701 -*/
				c = *++s; /* move past second l */					/*- mm 990701 -*/
			}														/*- mm 990701 -*/
#endif																/*- mm 990701 -*/
			break;
		
		case L'L':
			
			f.argument_options = long_double_argument;
			
			break;
		
		default:
			
			flag_found = 0;
	}
	
	if (flag_found)
		c = *++s;
	
	f.conversion_char = c;
	
	switch (c)
	{
		case L'd':
		case L'i':
		case L'u':
		case L'o':
		case L'x':
		case L'X':
			
			if (f.argument_options == long_double_argument)
			{
#if _MSL_LONGLONG                          /*- mm 961219 -*/
				f.argument_options = long_long_argument; /*- mm 961219 -*/
#else                                                    /*- mm 961220 -*/
				f.conversion_char = bad_conversion;      /*- mm 961219 -*/
				break;                                   /*- mm 961219 -*/
#endif                                                   /*- mm 961219 -*/
			}
		
			if (!f.precision_specified)
				f.precision = 1;
			else if (f.justification_options == zero_fill)
				f.justification_options = right_justification;
			
			break;

		case L'f':
		case L'F':										/*- mm 990430 -*/
			if (f.argument_options == short_argument
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif
			)  /*  defacto standard %lf is a double */
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			
			break;
		
		case L'g':
		case L'G':
			
			if (!f.precision)
				f.precision = 1;
		
		case L'e':
		case L'E':
			
			if (f.argument_options == short_argument 
#if _MSL_LONGLONG
				|| f.argument_options == long_long_argument
#endif
				|| f.argument_options == char_argument)        /*- mm 990208 -*/
			{
				f.conversion_char = bad_conversion;
				break;
			}
			
			if (!f.precision_specified)
				f.precision = 6;
			
			break;
		
		case L'p':
			
			f.argument_options = long_argument;
			f.alternate_form   = 1;
			f.conversion_char  = L'x';
			f.precision        = 8;
			
			break;
			
		case L'c':
#if _MSL_WIDE_CHAR				
			if (f.argument_options == long_argument)			/*- mm 990322 -*/
				f.argument_options = wchar_argument;			/*- mm 990322 -*/
			else												/*- mm 990322 -*/
#endif															/*- mm 990322 -*/
			
			if (f.precision_specified || f.argument_options != normal_argument)
				f.conversion_char = bad_conversion;
			
			break;
			
		case L's':
			
#if _MSL_WIDE_CHAR				
			if (f.argument_options == long_argument)			/*- mm 990322 -*/
				f.argument_options = wchar_argument;			/*- mm 990322 -*/
			else												/*- mm 990322 -*/
#endif															/*- mm 990322 -*/
			if (f.argument_options != normal_argument)			/*- mm 990322 -*/

				f.conversion_char = bad_conversion;
			
			break;
			
		case L'n':
			
			if (f.argument_options == long_double_argument)
#if _MSL_LONGLONG                             /*- mm 961219 -*/
				f.argument_options = long_long_argument;    /*- mm 961219 -*/
#else                                                       /*- mm 961220 -*/
				f.conversion_char = bad_conversion;         /*- mm 961219 -*/
#endif                                                      /*- mm 961219 -*/
			
			break;
			
		default:
			
			f.conversion_char = bad_conversion;
			
			break;
	}
	
	*format = f;
	
	return((const wchar_t *) s + 1);
}


static wchar_t * long2str(long num, wchar_t * buff, print_format format)
{
	unsigned long unsigned_num, base;
	wchar_t *				p;
	int						n, digits;
	int						minus = 0;
	
	unsigned_num = num;
	minus        =   0;
	
	p = buff;
	
	*--p = 0;
	
	digits = 0;
	
	if (!num && !format.precision && !(format.alternate_form && format.conversion_char == L'o'))
		return(p);
	
	switch (format.conversion_char)
	{
		case L'd':
		case L'i':
			
			base =  10;
	
			if (num < 0)
			{
				unsigned_num = -unsigned_num;
				minus        = 1;
			}
			
			break;
			
		case L'o':
			
			base =   8;
			
			format.sign_options = only_minus;
						
			break;
			
		case L'u':
			
			base =  10;
			
			format.sign_options = only_minus;
			
			break;
			
		case L'x':
		case L'X':
			
			base =  16;
			
			format.sign_options = only_minus;
			
			break;
	}
	
	do
	{
		n = unsigned_num % base;
		
		unsigned_num /= base;
		
		if (n < 10)
			n += L'0';
		else
		{
			n -= 10;
			
			if (format.conversion_char == L'x')
				n += L'a';
			else
				n += L'A';
		}
		
		*--p = n;
		
		++digits;
	}
	while (unsigned_num != 0);
	
	if (base == 8 && format.alternate_form && *p != L'0')
	{
		*--p = L'0';
		++digits;
	}
	
	if (format.justification_options == zero_fill)
	{
		format.precision = format.field_width;
		
		if (minus || format.sign_options != only_minus)
			--format.precision;
		
		if (base == 16 && format.alternate_form)
			format.precision -= 2;
	}
	
	if (buff - p + format.precision > conversion_max)
		return(NULL);
	
	while (digits < format.precision)
	{
		*--p = L'0';
		++digits;
	}
	
	if (base == 16 && format.alternate_form)
	{
		*--p = format.conversion_char;
		*--p = L'0';
	}
	
	if (minus)
		*--p = L'-';
	else if (format.sign_options == sign_always)
		*--p = L'+';
	else if (format.sign_options == space_holder)
		*--p = L' ';
	
	return(p);
}

#if _MSL_LONGLONG                          /*- mm 961219 -*/
static wchar_t * longlong2str(long long num, wchar_t * buff, print_format format)
{
	unsigned long long      unsigned_num, base;
	wchar_t *				    p;
	int						n, digits;
	int						minus = 0;
	
	unsigned_num = num;
	minus        =   0;
	
	p = buff;
	
	*--p = 0;
	
	digits = 0;
	
	if (!num && !format.precision && !(format.alternate_form && format.conversion_char == L'o'))
		return(p);
	
	switch (format.conversion_char)
	{
		case L'd':
		case L'i':
			
			base =  10;
	
			if (num < 0)
			{
				unsigned_num = -unsigned_num;
				minus        = 1;
			}
			
			break;
			
		case L'o':
			
			base =   8;
			
			format.sign_options = only_minus;
						
			break;
			
		case L'u':
			
			base =  10;
			
			format.sign_options = only_minus;
			
			break;
			
		case L'x':
		case L'X':
			
			base =  16;
			
			format.sign_options = only_minus;
			
			break;
	}
	
	do
	{
		n = unsigned_num % base;
		
		unsigned_num /= base;
		
		if (n < 10)
			n += L'0';
		else
		{
			n -= 10;
			
			if (format.conversion_char == L'x')
				n += L'a';
			else
				n += L'A';
		}
		
		*--p = n;
		
		++digits;
	}
	while (unsigned_num != 0);
	
	if (base == 8 && format.alternate_form && *p != L'0')
	{
		*--p = L'0';
		++digits;
	}
	
	if (format.justification_options == zero_fill)
	{
		format.precision = format.field_width;
		
		if (minus || format.sign_options != only_minus)
			--format.precision;
		
		if (base == 16 && format.alternate_form)
			format.precision -= 2;
	}
	
	if (buff - p + format.precision > conversion_max)
		return(NULL);
	
	while (digits < format.precision)
	{
		*--p = L'0';
		++digits;
	}
	
	if (base == 16 && format.alternate_form)
	{
		*--p = format.conversion_char;
		*--p = L'0';
	}
	
	if (minus)
		*--p = L'-';
	else if (format.sign_options == sign_always)
		*--p = L'+';
	else if (format.sign_options == space_holder)
		*--p = L' ';
	
	return(p);
}
#endif    /*_MSL_LONGLONG*/

static void round_decimal(decimal * dec, int new_length)
{
	char		c;
	char *	p;
	int			carry;
	
	if (new_length < 0)
	{
return_zero:
		/*dec->sgn         =  0 ; */									/*- mm 990906 -*/
		dec->exp         =  0;
		dec->sig.length  =  1;
		*dec->sig.text   = '0';
		return;
	}
	
	if (new_length >= dec->sig.length)
		return;
	
	p     = (char *) dec->sig.text + new_length + 1;
	c     = *--p - L'0';
	/*  -- added round to nearest or even mode; was: carry = (c >= 5);*/  /*- mm 970614 -*/
	if( c == 5 )                                                    	  /*- mm 970614 -*/
	{ char *q = &((char *)dec->sig.text)[dec->sig.length];           	  /*- mm 970614 -*/
	  while( --q > p && *q == '0' ) /* */;                           	  /*- mm 970614 -*/
	  carry = ( q == p ) ? p[-1] & 1 : 1;                            	  /*- mm 970614 -*/
	}                                                                	  /*- mm 970614 -*/
	else                                                            	  /*- mm 970614 -*/
	  carry = (c > 5);                                               	  /*- mm 970614 -*/
	
	while (new_length)
	{
		c = *--p - L'0' + carry;
		
		if ((carry = (c > 9)) != 0 || c == 0 )							  /*- mm 970614 -*/
			--new_length;
		else
		{
			*p = c + L'0';
			break;
		}
	}
	
	if (carry)
	{
		dec->exp        +=  1 ;
		dec->sig.length  =  1 ;
		*dec->sig.text   = '1';
		return;
	}
	else if (new_length == 0)
		goto return_zero;
	
	dec->sig.length = new_length;
}


#if !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)

static wchar_t * float2str(long double num, wchar_t * wbuff, print_format format) /*- mm 980129 -*/
{
	decimal		dec;
	decform		form;
	wchar_t *	pw;																/*- mm 980129 -*/
	char *		p;																/*- mm 980129 -*/
	char        buff[conversion_buff_size];										/*- mm 980129 -*/
	char *		q;																/*- mm 980129 -*/
	int			n, digits, sign;												/*- mm 990904 -*/
	int			int_digits, frac_digits;
	int         radix_marker;													/*- mm 011130 -*/
	
	#if _MSL_C_LOCALE_ONLY	
		radix_marker = '.';
	#else
		radix_marker = 	* (unsigned char *) _MSL_LOCALDATA(__lconv).decimal_point;	/*- mm 011130 -*/
	#endif
	
	if (format.precision > conversion_max)							/* might as well punt asap */
		return(NULL);

/*
 *	Note: If you look at <ansi_fp.h> you'll see that __num2dec only supports double.
 *				If you look at <float.h> you'll see that long double == double. Ergo, the
 *				difference is moot *until* a truly long double type is supported.
 */
	
	form.style  = FLOATDECIMAL;
	form.digits = MAX_SIG_DIG;           										/*- mm 970609 -*/
	
	__num2dec(&form, num, &dec);
	
	p = (char *) dec.sig.text + dec.sig.length;	/* strip off trailing zeroes */ /*- mm 980129 -*/
	
	while (dec.sig.length > 1 && *--p == '0')									/*- mm 980129 -*/
	{
		--dec.sig.length;
		++dec.exp;
	}
	
	switch (*dec.sig.text)
	{
		case '0':																/*- mm 980129 -*/
			
			/* dec.sgn = 0;		*/ /* print correctly signed zero --mf 060298 */
			dec.exp = 0;					/* __num2dec doesn't guarantee */
											/* this for zeroes             */
			break;
			
		case 'I':																/*- mm 980129 -*/
			
			if (num < 0)                   										/*- mm 970213 -*/
			{                              										/*- mm 970213 -*/
				pw = wbuff - 5;             				/*- mm 970213 -*/	/*- mm 980129 -*/																/* special cases */
				if (iswupper(format.conversion_char))							/*- mm 990430 -*/
					wcscpy(pw, L"-INF");
				else
					wcscpy(pw, L"-inf");        			/*- mm 970213 -*/	/*- mm 980129 -*/
			}                              										/*- mm 970213 -*/
			else                           										/*- mm 970213 -*/
			{                              										/*- mm 970213 -*/
				pw = wbuff - 4;             				/*- mm 970213 -*/	/*- mm 980129 -*/																	/* special cases */
				if (iswupper(format.conversion_char))							/*- mm 990430 -*/
					wcscpy(pw, L"INF");
				else
					wcscpy(pw, L"inf");        				/*- mm 970213 -*/	/*- mm 980129 -*/
			}                              										/*- mm 970213 -*/
			
			return(pw);															/*- mm 980129 -*/
			
		case 'N':																/*- mm 980129 -*/
			
			pw = wbuff - 4;														/*- mm 980129 -*/
			
			wcscpy(pw, L"NaN");													/*- mm 980129 -*/
			
			return(pw);															/*- mm 980129 -*/
	}
	
	dec.exp += dec.sig.length - 1;				/* shift decimal point to */
												/* follow first digit	  */
	p = buff + conversion_buff_size;											/*- mm 980129 -*/
	
	*--p = 0;
	
	switch (format.conversion_char)
	{
		case L'g':
		case L'G':
			
			if (dec.sig.length > format.precision)
				round_decimal(&dec, format.precision);
			
			if (dec.exp < -4 || dec.exp >= format.precision)
			{
				if (format.alternate_form)
					--format.precision;
				else
					format.precision = dec.sig.length - 1;
				
				if (format.conversion_char == L'g')
					format.conversion_char = L'e';
				else
					format.conversion_char = L'E';
				
				goto e_format;
			}
			
			if (format.alternate_form)
				format.precision -= dec.exp + 1;
			else
				if ((format.precision = dec.sig.length - (dec.exp + 1)) < 0)
					format.precision = 0;
			
			goto f_format;
		
		case L'e':
		case L'E':
		e_format:
			
			if (dec.sig.length > format.precision + 1)
				round_decimal(&dec, format.precision + 1);
			
			n    = dec.exp;
			sign = '+';									/*- mm 980129 -*/
			
			if (n < 0)
			{
				n    = -n;
				sign = '-';								/*- mm 980129 -*/
			}
			
			for (digits = 0; n || digits < 2; ++digits)
			{
				*--p  = n % 10 + '0';					/*- mm 980129 -*/
				n    /= 10;
			}
			
			*--p = sign;
			*--p = format.conversion_char;
			
			if (buff - p + format.precision > conversion_max)
				return(NULL);
			
			if (dec.sig.length < format.precision + 1)
				for (n = format.precision + 1 - dec.sig.length + 1; --n;)
					*--p = '0';								/*- mm 980129 -*/
			
			for (n = dec.sig.length, q = (char *) dec.sig.text + dec.sig.length; --n;)
				*--p = *--q;
			
			if (format.precision || format.alternate_form)
				*--p = radix_marker;						/*- mm 011130 -*/
			
			*--p = *dec.sig.text;
			
			if (dec.sgn)
				*--p = '-';									/*- mm 980129 -*/
			else if (format.sign_options == sign_always)
				*--p = '+';									/*- mm 980129 -*/
			else if (format.sign_options == space_holder)
				*--p = ' ';									/*- mm 980129 -*/
			
			break;
		
		case L'f':
		case L'F':
		f_format:
			
			if ((frac_digits = -dec.exp + dec.sig.length - 1) < 0)
				frac_digits = 0;
			
			if (frac_digits > format.precision)
			{
				round_decimal(&dec, dec.sig.length - (frac_digits - format.precision));
				
				if ((frac_digits = -dec.exp + dec.sig.length - 1) < 0)
					frac_digits = 0;
			}
			
			if ((int_digits = dec.exp + 1) < 0)
				int_digits = 0;
			
			if (int_digits + frac_digits > conversion_max)
				return(NULL);
			
			q = (char *) dec.sig.text + dec.sig.length;		/*- mm 980129 -*/
			
			for (digits = 0; digits < (format.precision - frac_digits); ++digits)
				*--p = '0';									/*- mm 980129 -*/
			
			for (digits = 0; digits < frac_digits && digits < dec.sig.length; ++digits)
				*--p = *--q;
			
			for (; digits < frac_digits; ++digits)
				*--p = '0';									/*- mm 980129 -*/
			
			if (format.precision || format.alternate_form)
				*--p = radix_marker;							/*- mm 011130 -*/
			
			if (int_digits)
			{
				for (digits = 0; digits < int_digits - dec.sig.length; ++digits)
					*--p = '0';								/*- mm 980129 -*/
				
				for (; digits < int_digits; ++digits)
					*--p = *--q;
			}
			else
				*--p = '0';										/*- mm 980129 -*/
			
			if (dec.sgn)
				*--p = '-';										/*- mm 980129 -*/
			else if (format.sign_options == sign_always)
				*--p = '+';										/*- mm 980129 -*/
			else if (format.sign_options == space_holder)
				*--p = ' ';										/*- mm 980129 -*/
			
			break;
	}
	      /*  Convert number string to wchars */				/*- mm 980129 -*/
	pw = wbuff - strlen(p) - 1;									/*- mm 980129 -*/
	mbstowcs(pw, p, strlen(p));									/*- mm 990904 -*/
	
	return(pw);
}

#endif /* !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB) */

/*
	vfwprintf
	
	Description
	
	The vfwprintf function is equivalent to fwprintf, with
	the variable argument list replaced by arg, which shall have
	been initialized by the va_start macro (and possibly
	subsequent va_arg calls). The vfwprintf function does not
	invoke the va_end macro.
	
	Returns
	
	The vfwprintf function returns the number of wide
	characters transmitted, or a negative value if an output
	error occured.

*/


static int __wpformatter(void *(_MSL_CDECL *wWriteProc)(void *, const wchar_t *, size_t), void * WriteProcArg, 
													const wchar_t * format_str, va_list arg)	/*- mm 990325 -*/
{
	int				num_chars, chars_written, field_width;
	const wchar_t *	format_ptr;
	const wchar_t *	curr_format;
	print_format	format;
	long			long_num;
#if _MSL_LONGLONG          /*- mm 961219 -*/
	long long   	long_long_num;       /*- mm 961219 -*/
#endif                                   /*- mm 961219 -*/
#if !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)
	long double		long_double_num;
#endif
	wchar_t			buff[conversion_buff_size];
	wchar_t *		buff_ptr;
	wchar_t *		wstring_end;				/*- mm 990323 -*/
	char *			cstring_end;				/*- mm 990323 -*/
	wchar_t         fill_char = L' ';       	/*- mm 960722 -*/
	char * 			strptr;
	
	format_ptr    = format_str;
	chars_written = 0;
	
	while (*format_ptr)
	{
		if (!(curr_format = wcschr(format_ptr, L'%')))
		{
			num_chars      = wcslen(format_ptr);
			chars_written += num_chars;
			
			if (num_chars && !(*wWriteProc)(WriteProcArg, format_ptr, num_chars))	/*- mm 990325 -*/
				return(-1);
				
			break;
		}
		
		num_chars      = curr_format - format_ptr;
		chars_written += num_chars;
		
		if (num_chars && !(*wWriteProc)(WriteProcArg, format_ptr, num_chars))	/*- mm 990325 -*/
			return(-1);
		
		format_ptr = curr_format;
		
		format_ptr = parse_format(format_ptr, (va_list *)&arg, &format); /*- scm 970709 -*/
		
		switch (format.conversion_char)
		{
			case L'd':
			case L'i':
				
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, long);
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif                                                                   /*- mm 961219 -*/
				else
					long_num = va_arg(arg, int);
				
				if (format.argument_options == short_argument)
					long_num = (short) long_num;
					
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
                if (format.argument_options == long_long_argument)       /*- mm 961219 -*/
				{														 /*- bb 971019 -*/
				   if (!(buff_ptr = longlong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				}														 /*- bb 971019 -*/
				else                                                     /*- mm 961219 -*/
#endif                                                                   /*- mm 961219 -*/
				if (!(buff_ptr = long2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;
				
			case L'o':
			case L'u':
			case L'x':
			case L'X':
				
				if (format.argument_options == long_argument)
					long_num = va_arg(arg, unsigned long);
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
	            else if (format.argument_options == long_long_argument)  /*- mm 961219 -*/
					long_long_num = va_arg(arg, long long);              /*- mm 961219 -*/
#endif                                                                   /*- mm 961219 -*/
				else
					long_num = va_arg(arg, unsigned int);
				
				if (format.argument_options == short_argument)
					long_num = (unsigned short) long_num;
					
#if _MSL_LONGLONG                                          /*- mm 961219 -*/
                if (format.argument_options == long_long_argument)       /*- mm 961219 -*/
                {														 /*- mf 971020 -*/
				   if (!(buff_ptr = longlong2str(long_long_num,          /*- mm 961219 -*/
				                   buff + conversion_buff_size, format)))/*- mm 961219 -*/
					   goto conversion_error;                            /*- mm 961219 -*/
				} 														 /*- mf 971020 -*/
				else                                                     /*- mm 961219 -*/
#endif                                                                   /*- mm 961219 -*/
				if (!(buff_ptr = long2str(long_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				
				break;

#if !defined(_No_Floating_Point) && !defined(_MSL_NO_MATH_LIB)

			case L'f':
			case L'F':
			case L'e':
			case L'E':
			case L'g':
			case L'G':
				
				if (format.argument_options == long_double_argument)
					long_double_num = va_arg(arg, long double);
				else
					long_double_num = va_arg(arg, double);
				
				if (!(buff_ptr = float2str(long_double_num, buff + conversion_buff_size, format)))
					goto conversion_error;
				
				num_chars = buff + conversion_buff_size - 1 - buff_ptr;
				break;
#endif

			case L's':
				if (format.argument_options == wchar_argument)			/*- mm 990322 -*/
				{
					buff_ptr = va_arg(arg, wchar_t *);
					if (buff_ptr == NULL)    /*- mm 970708 -*/
	  					buff_ptr = L"";      /*- mm 970708 -*/
					if (format.alternate_form)
					{
						num_chars = (unsigned char) *buff_ptr++;
						
						if (format.precision_specified && num_chars > format.precision)
							num_chars = format.precision;
					}
					else if (format.precision_specified)
					{
						num_chars = format.precision;
						
						if ((wstring_end = (wchar_t *) wmemchr(buff_ptr, 0, num_chars)) != 0)  /*- mm 990322 -*/
							num_chars = wstring_end - buff_ptr;
					}
					else
						num_chars = wcslen(buff_ptr);
				}
				else
				{
					
					strptr = va_arg(arg, char *);
					if (strptr == NULL)    /*- mm 970708 -*/
	  					strptr = "";       /*- mm 970708 -*/
					if (format.alternate_form)
					{
						num_chars = (unsigned char) *buff_ptr++;
						
						if (format.precision_specified && num_chars > format.precision)
							num_chars = format.precision;
					}
					else if (format.precision_specified)
					{
						num_chars = format.precision;
						
						if ((cstring_end = (char *) memchr(strptr, 0, num_chars)) != 0)  /*- mm 990322 -*/
							num_chars = cstring_end - strptr;
					}
					else
						num_chars = strlen(strptr);
	  				if ((num_chars = mbstowcs(buff, strptr, num_chars)) < 0)
						goto conversion_error;
	  				
	  				buff_ptr = &buff[0];
				}	
				break;
				
			case L'n':
				
				buff_ptr = va_arg(arg, wchar_t *);
				
				switch (format.argument_options)
				{
					case normal_argument:    * (int *)       buff_ptr = chars_written; break;
					case short_argument:     * (short *)     buff_ptr = chars_written; break;
					case long_argument:      * (long *)      buff_ptr = chars_written; break;
#if _MSL_LONGLONG                                          /*-mm 961219 -*/
					case long_long_argument: * (long long *) buff_ptr = chars_written; break;
#endif                                                                   /*-mm 961219 -*/
				}
				
				continue;
				
			case L'c':
				buff_ptr = buff;
				if (format.argument_options == wchar_argument)			/*- mm 990322 -*/
				{
				
					*buff_ptr = va_arg(arg, int);
					
					num_chars = 1;
				}
				else
				{
					char chint = va_arg(arg, int);
					num_chars = mbtowc(buff, &chint, 1);
				}
				
				break;
			
			case L'%':
				
				buff_ptr = buff;
				
				*buff_ptr = L'%';
				
				num_chars = 1;
				
				break;
				
			case bad_conversion:
			conversion_error:
			default:
				
				num_chars      = wcslen(curr_format);
				chars_written += num_chars;
				
				if (num_chars && !(*wWriteProc)(WriteProcArg, curr_format, num_chars))	/*- mm 990325 -*/
					return(-1);
				
				return(chars_written);
		}
		
		field_width = num_chars;
		
		if (format.justification_options != left_justification)
		{                                                                         		/*- mm 960722 -*/
			fill_char = (format.justification_options == zero_fill) ? L'0' : L' ';  	/*- mm 960722 -*/
			if (((*buff_ptr == L'+') || (*buff_ptr == L'-') || (*buff_ptr == L' ')) 
															&& (fill_char == L'0')) 	/*- mm 990905 -*/	
			{	                                                                  		/*- mm 970206 -*/
				if ((*wWriteProc)(WriteProcArg, buff_ptr, 1) == 0)                      /*- mm 990325 -*/
					return(-1);                                                   		/*- mm 970206 -*/
				++buff_ptr;                                                       		/*- mm 970206 -*/
				num_chars--;                                                      		/*- mm 970723 -*/
			}
			while (field_width < format.field_width)
			{
				if ((*wWriteProc)(WriteProcArg, &fill_char, 1) == 0)                       /*- mm 990325 -*/
					return(-1);
					
				++field_width;
			}
		}                                                                       		/*- mm 960722 -*/
		
		if (num_chars && !(*wWriteProc)(WriteProcArg, buff_ptr, num_chars))	/*- mm 990325 -*/
			return(-1);
		
		if (format.justification_options == left_justification)
			while (field_width < format.field_width)
			{
				wchar_t blank = L' ';
				if ((*wWriteProc)(WriteProcArg, &blank, 1) == 0)  				/*- mm 990311 -*/
					return(-1);
					
				++field_width;
			}
		
		chars_written += field_width;
	}
	
	return(chars_written);
}


void * _MSL_CDECL __wFileWrite(void *File, const wchar_t * Buffer, size_t NumChars) /*- cc 020108 -*/
{
	return (fwrite(Buffer, sizeof(wchar_t), NumChars, (FILE *)File) == NumChars ? File : 0);
}

void * _MSL_CDECL __wStringWrite(void * wosc, const wchar_t * Buffer, size_t NumChars) /*- cc 020108 -*/
{
	size_t wCharsToBeWritten;
	void * MemCpyResult;
	__wOutStrCtrl * wOscp = (__wOutStrCtrl*)wosc;
	
	wCharsToBeWritten = ((wOscp->CharsWritten + NumChars) <= wOscp->MaxCharCount) ? NumChars : 
															wOscp->MaxCharCount - wOscp->CharsWritten;
	MemCpyResult = (void *)wmemcpy(wOscp->wCharStr + wOscp->CharsWritten, Buffer, wCharsToBeWritten);
	wOscp->CharsWritten += wCharsToBeWritten;
	return(MemCpyResult);
}

/*
	wprintf

	Description
	
	The wprintf function writes output to the stdin, 
	under control of the wide string
	pointed to by format that specifies how subsequent arguments
	are converted for output. If there are insufficient
	arguments for the format, the behaviour is undefined. If the
	format is exhausted while arguments remain, the excess
	arguments are evaluated (as always) but are otherwise
	ignored. 
	
	Returns
	
	The wprintf function returns when the end of the
	format string is encountered.

*/

int _MSL_CDECL wprintf(const wchar_t * _MSL_RESTRICT format, ...)
{
	int result;																			/*- mm 001018 -*/
	
#if __PPC_EABI__  || __MIPS__   /* __dest_os == __mips_bare */                     
	va_list args;                            
	if (fwide(stdout, 1) <= 0)			
		return(-1);						
	va_start( args, format );                
  	__begin_critical_region(stdout_access);			/*- mm 001018 -*//*- mm 020627 -*/
  	result = __wpformatter(&__wFileWrite, (void *)stdout, format, args);				/*- mm 001018 -*/
#else                                        
	if (fwide(stdout, 1) <= 0)			
		return(-1);						
  	__begin_critical_region(stdout_access);					/*- mm 001024 -*//*- mm 020627 -*/
	result = __wpformatter(&__wFileWrite, (void *)stdout, format, __va_start(format));	/*- mm 001018 -*/
#endif                                       
  	__end_critical_region(stdout_access);				/*- mm 001018 -*//*- mm 020627 -*/			
    return(result);										/*- mm 001018 -*/
}


/*
	fwprintf
	
	Description
	
	The fwprintf function writes output to the stream
	pointed to by file, under control of the wide string
	pointed to by format that specifies how subsequent arguments
	are converted for output. If there are insufficient
	arguments for the format, the behaviour is undefined. If the
	format is exhausted while arguments remain, the excess
	arguments are evaluated (as always) but are otherwise
	ignored. 
	
	Returns
	
	The fwprint function returns when the end of the
	format string is encountered.

*/

int _MSL_CDECL fwprintf(FILE * _MSL_RESTRICT file, const wchar_t * _MSL_RESTRICT format, ...)
{
	int result;											/*- mm 001018 -*/
	int crtrgn;

	if (file == stdout)						/*- mm 020627 -*/
		crtrgn = stdout_access;				/*- mm 020627 -*/
	else if (file == stderr)				/*- mm 020627 -*/
		crtrgn = stderr_access;				/*- mm 020627 -*/
	else									/*- mm 020627 -*/
		crtrgn = files_access;				/*- mm 020627 -*/
#if __PPC_EABI__ || __MIPS__ /*  __dest_os == __mips_bare */                           
	va_list args;  
	                          
	if (fwide(file, 1) <= 0)			
		return(-1);						
	va_start( args, format );               
  	__begin_critical_region(crtrgn);		 /*- mm 001013 -*/			/*- mm 020627 -*/
	result = __wpformatter(&__wFileWrite, (void *)file, format, args); /*- mm 001018 -*/
#else                                        
	if (fwide(file, 1) <= 0)			
		return(-1);						
  	__begin_critical_region(crtrgn);		 /*- mm 001013 -*/			/*- mm 020627 -*/
	result = __wpformatter(&__wFileWrite, (void *)file, format, __va_start(format));/*- mm 001018 -*/
#endif                                       
  	__end_critical_region(crtrgn);				/*- mm 001018 -*/		/*- mm 020627 -*/		
    return(result);										/*- mm 001018 -*/
}


/*
	vwprintf
	
	Description
	
	The vwprintf function is equivalent to wprintf, except
	that the argument list is replaced by arg, which shall have
	been initialized by the va_start macro (and possibly
	subsequent va_arg calls). The vwprintf function does not
	invoke the va_end macro.
	
	
	Returns
	
	The vwprintf function returns the number of wide 
	characters transmitted, or a negative value if an output
	error occurred.
	
*/

int _MSL_CDECL vwprintf(const wchar_t * _MSL_RESTRICT format, va_list arg)
{
	int retval;															/*- mm 001018 -*/
	if (fwide(stdout, 1) <= 0)			
		return(-1);						
  __begin_critical_region(stdout_access);				/*- mm 001018 -*//*- mm 020627 -*/
	retval = __wpformatter(&__wFileWrite, (void *)stdout, format, arg);	/*- mm 001018 -*/
  	__end_critical_region(stdout_access);				/*- mm 001018 -*//*- mm 020627 -*/		
	return(retval);														/*- mm 001018 -*/
}

/*
	vfwprintf
	
	Description
	
	The vfwprintf function is equivalent to fwprintf, with
	the variable argument list replaced by arg, which shall have
	been initialized by the va_start macro (and possibly
	subsequent va_arg calls). The vfwprintf function does not
	invoke the va_end macro.
	
	Returns
	
	The vfwprintf function returns the number of wide
	characters transmitted, or a negative value if an output
	error occured.

*/


int _MSL_CDECL vfwprintf(FILE * _MSL_RESTRICT file, const wchar_t * _MSL_RESTRICT format, va_list arg)
{
	int retval;															/*- mm 001018 -*/
	int crtrgn;								/*- mm 020627 -*/
	if (file == stdout)						/*- mm 020627 -*/
		crtrgn = stdout_access;				/*- mm 020627 -*/
	else if (file == stderr)				/*- mm 020627 -*/
		crtrgn = stderr_access;				/*- mm 020627 -*/
	else									/*- mm 020627 -*/
		crtrgn = files_access;				/*- mm 020627 -*/
	if (fwide(file, 1) <= 0)			
		return(-1);						
  	__begin_critical_region(crtrgn);		 /*- mm 001018 -*/			/*- mm 020627 -*/
	retval = __wpformatter(&__wFileWrite, (void *)file, format, arg);	/*- mm 001018 -*/
  	__end_critical_region(crtrgn);			/*- mm 001018 -*/			/*- mm 020627 -*/
	return(retval);														/*- mm 001018 -*/
}


/*
	swprintf
	
	Description
	
	The swprintf function is equivalent to fwprintf, except
	that the argument s specifies an array of wide character
	into which the generated output is to be written, rather
	than written to a stream. No more that n wide characters are
	written, including a terminating null wide character, which
	is always added (unless n is zero)
	
	
	Returns
	
      [#3]  The  swprintf  function  returns  the  number  of wide
       characters  written  in  the   array,   not   counting   the
       terminating  null  wide character, or a negative value if an
       encoding error occurred or if n or more wide characters were
       requested to be written.
	
*/

int _MSL_CDECL swprintf(wchar_t * _MSL_RESTRICT s, size_t n, const wchar_t * _MSL_RESTRICT format, ...)
{
#if __PPC_EABI__    || __MIPS__   /* __dest_os == __mips_bare  */ 	/*- scm 970709 -*/
	va_list args;                        							/*- scm 970709 -*/
	va_start( args, format );            							/*- scm 970709 -*/
	return(vswprintf(s, n, format, args));   						/*- scm 970709 -*/
#else                                    							/*- scm 970709 -*/
	return(vswprintf(s, n, format, __va_start(format)));
#endif                                   							/*- scm 970709 -*/
}

/*
	vswprintf
	
	Description
	
	The vswprintf function is equivalent to swprintf with
	the variable argument list replaced by arg, which shall have
	been initialized by the va_start macro (and possibly
	subsequent va_arg calls). The vswprintf function does not
	invoke the va_end macro.
	
	
	Returns
	
	The vswprintf function returns the number of wide 
	characters written in the array, not counting the
	terminating null wide character, or a negative value if n or
	more wide characters were requested to be generated.
	
*/

int _MSL_CDECL vswprintf(wchar_t * _MSL_RESTRICT s, size_t n, const wchar_t * _MSL_RESTRICT format, va_list arg)
{
	int		count;
	__wOutStrCtrl wosc;
	
	wosc.wCharStr     = s;
	wosc.MaxCharCount = n;
	wosc.CharsWritten = 0;
	
	count = __wpformatter(&__wStringWrite, &wosc, format, arg);
	
	if (count >= 0)				/*- mm 990316 -*/
		if (count < n)			/*- mm 990316 -*/
			s[count] = 0;		/*- mm 990316 -*/
		else					/*- mm 990316 -*/
		{						/*- mm 990316 -*/
			s[n-1] = 0;			/*- mm 990316 -*/
			count  = -1;		/*- mm 990316 -*/
		}						/*- mm 990316 -*/
	
	return(count);
}

#endif /* _MSL_C99 */						/*- mm 030304 -*/

#endif /* #if _MSL_WIDE_CHAR*/				/*- mm 981020 -*/

/* Change record:
 * JCM 980121 First code release.
 * mm  980206 Added call to fwide()
 * mm  980930 Corrected size passed to __open_string_file to get proper buffer size.
 * mm  981020 Added #if _MSL_WIDE_CHAR wrappers
 * mm  990315 Change to make insertion of fill characters work correctly  IL9903_1178
 * mm  990316 Corrected position of null character in output and made return value match C9x IL9903-1264
 * mm  990322 Implemented %ls and %lc
 * mm  990630 Implemented %hh
 * mm  990701 Implemented %ll
 * mm  990817 Deleted include of <string_io.h>
 * mm  990904 Corrected translation from multibyte to wchar
 * mm  990905 Move blank where there is zero fill and a blank sign space holder IL9908-4231
 * mm  990906 Print correct sign for zero.Il9908-4232
 * mm  001018 Threadsafety changes for fwprintf, wprintf, vfwprintf, vwprintf
 * mm  001024 Inserted missing __begin_critical_region
 * mm  011130 Changes for implementation of locale
 * cc  011203 Added _MSL_CDECL for new name mangling
 * blc 011211 Added _MSL_NO_MATH_LIB macro check
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 * JWW 020405 Fixed an instance where sizeof(wchar_t) was incorrectly assumed to always be 2
 * JWW 020604 Added _MSL_LOCALDATA macro to make multithread code easier to read
 * mm  020627 Changes to prevent io on stdin, stdout, stderr and general files from interfering with each other
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * cc  021022 Added _MSL_C_LOCALE_ONLY around the radix_marker
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added _MSL_C99 wrapper
 */