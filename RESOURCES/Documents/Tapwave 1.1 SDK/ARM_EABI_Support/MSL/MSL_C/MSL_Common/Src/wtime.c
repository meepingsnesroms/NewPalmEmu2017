/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/11 19:50:18 $
 * $Revision: 1.37 $
 */

/*
 *	Routines
 *	--------
 *		wasctime	 
 *		wctime		 
 *		wcsftime	
 */

#pragma ANSI_strict off  			/*- vss 990729 -*/

#include <ansi_parms.h> 

#if _MSL_WIDE_CHAR				/*- mm 980204 -*/

#if _MSL_C99					/*- mm 030304 -*/

#pragma ANSI_strict reset

#include <arith.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <time_api.h>				/*- mm 021220 -*/
#include <wtime.h>					/*- mm 990809 -*/

#include <wchar.h>
#include <locale_api.h>							
#include <msl_thread_local_data.h>

#define seconds_per_minute	(60L)
#define seconds_per_hour	(60L * seconds_per_minute)
#define seconds_per_day		(24L * seconds_per_hour)

static const short month_to_days[2][13] =
	{
		{0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
		{0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
	};

static const char *day_name[]
	= {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

static const char *month_name[]
	= {"January", "February", "March",     "April",   "May",      "June",
		 "July",     "August",  "September", "October", "November", "December"};

/*
 *	leap_year - return nonzero if year is a leap year, zero otherwise (year 0 = 1900)
 */

static int leap_year(int year)
{
	return(__msl_mod(year, 4) == 0 && (__msl_mod(year, 100) != 0 || __msl_mod(year, 400) == 100));	/*- cc 010510 -*/
}

/*
 *	leap_days - return the number of leap days between 1900 (year 0)
 *							and the given year and month. year can be negative,
 *							month cannot.
 */

static int leap_days(int year, int mon)
{
	int		n;
	div_t	q;

	q = div(year, 4);
	/* 1 leap day every four years */

	n = q.quot;

	q = div(year, 100);						/* except at the turn of the century */

	n -= q.quot;

	if (year < 100)
	/* not counting the turn of the millenium */
	{
		q = __msl_div(year+899, 1000);	/*- cc 010510 -*/

		n += q.quot;
	}
	else
	{
		q = __msl_div(year-100, 1000);	/*- cc 010510 -*/

		n += q.quot + 1;
	}

	if (leap_year(year))
		if (year < 0)
		{
			if (mon > 1)
				++n;
		}
		else
			if (mon <= 1)
				--n;

	return(n);
}

/*
 *	adjust - force x to be a modulo y number, add overflow to z
 */


static int adjust(int * x, int y, int * z)
{
	div_t	q;

	q = __msl_div(*x, y);	/*- cc 010510 -*/

	*x = q.rem;

	return(__msl_add(z, q.quot));  /*- cc 010510 -*/
}

/*
 *	__time2tm - convert seconds since midnight, 1/1/1900 (or 1970 on Win32),
 *	to broken-down time
 */

#if (__dest_os == __win32_os || __dest_os == __wince_os)
static void __time2tm(time_t inTime, struct tm * tm)
#else
static void __time2tm(time_t time, struct tm * tm)
#endif
{
	unsigned long	years, months, days, seconds;
	int						is_leap_year;

	#if (__dest_os == __win32_os  || __dest_os == __wince_os)
		/* Since Win32 time_t is relative to 1970 rather than 1900.
		 * This must be of type unsigned long rather than a signed
		 * time_t to prevent overflow */
		unsigned long time = inTime + ((365 * 70UL) + 17) * 24 * 60 * 60;
	#endif

	if (!tm)
		return;

	#ifndef _No_Time_OS_Support							 /*- cc 011210 -*/
		tm->tm_isdst = __isdst();                        /*- mm 010421 -*/
	#endif												 /*- cc 011210 -*/

	days    = time / seconds_per_day;
	seconds = time % seconds_per_day;

	tm->tm_wday = (days + 1) % 7;
			/* January 1, 1900 was a Monday */

	years = 0;

	for (;;)
	{
		unsigned long	days_this_year = leap_year(years) ? 366 : 365;

		if (days < days_this_year)
			break;

		days  -= days_this_year;
		years += 1;
	}

	tm->tm_year = years;
	tm->tm_yday = days;

	months = 0;

	is_leap_year = leap_year(years);

	for (;;)
	{
		unsigned long days_thru_this_month = month_to_days[is_leap_year][months+1];

		if (days < days_thru_this_month)
		{
			days -= month_to_days[is_leap_year][months];
			break;
		}

		++months;
	}

	tm->tm_mon  = months;
	tm->tm_mday = days + 1;

	tm->tm_hour = seconds / seconds_per_hour;

	seconds %= seconds_per_hour;

	tm->tm_min = seconds / seconds_per_minute;
	tm->tm_sec = seconds % seconds_per_minute;
}

/*
 *	__tm2time - convert broken-down time to seconds since midnight,
 *	1/1/1900 (or 1970 on Win32). return zero if broken-down time can't be
 *	represented; otherwise, convert seconds back into broken-down time and
 *	return nonzero.
 *
 *	Note:	Each field in broken-down time is forced into the normal range
 *	for that field, with overflow being added to next field up
 *	through mday (day of month). mday is allowed to remain out of
 *	range. mon is forced into its normal range with overflow being
 *	added to year. year and mon are converted to days since 1/1/1900
 *	with mday and leap days between 1/1/1900 and year and mon added.
 *	If the result is negative, zero is returned. Otherwise, it is
 *	converted to seconds and added to hour, min and sec converted to
 *	seconds to yield the final result. Overflow checking is performed
 *	where needed and if overflow occurs, zero is returned; nonzero
 *	otherwise.
 */

static int __tm2time(struct tm * tm, time_t * time)
{
	long		days;
	time_t	seconds, day_secs;

	if (!tm || !time)
		return(0);


	/* I don't know why it isn't     */
	--tm->tm_mday;
	/* zero-based in the first place */

	if (!adjust(&tm->tm_sec,  60, &tm->tm_min))	goto no_exit;
			/* put sec  in range 0-59 */
	if (!adjust(&tm->tm_min,  60, &tm->tm_hour))	goto no_exit;
		/* put min  in range 0-59 */
	if (!adjust(&tm->tm_hour, 24, &tm->tm_mday))	goto no_exit;
		/* put hour in range 0-23 */

	if (!adjust(&tm->tm_mon,  12, &tm->tm_year))	goto no_exit;
		/* put mon  in range 0-11 */

	days = tm->tm_year;

	if (!__msl_lmul(&days, 365))								/*- cc 010510 -*/

		goto no_exit;		/* convert year to days */
	if (!__msl_ladd(&days, leap_days(tm->tm_year, tm->tm_mon)))	/*- cc 010510 -*/
		goto no_exit;		/* add leap days */
	if (!__msl_ladd(&days, month_to_days[0][tm->tm_mon]))		/*- cc 010510 -*/
		goto no_exit;		/* add days to month */
	if (!__msl_ladd(&days, tm->tm_mday))						/*- cc 010510 -*/
		goto no_exit;		/* add days in month */

	if (days < 0 || days > (ULONG_MAX / seconds_per_day))
				/* make sure we're in range */
		goto no_exit;

	day_secs = days * seconds_per_day;

		/* convert days to seconds */

	seconds = (tm->tm_hour * seconds_per_hour) 	 +
							/* convert HMS to seconds */
						(tm->tm_min  * seconds_per_minute) + tm->tm_sec;

	if (seconds > ULONG_MAX - day_secs)

		/* make sure there's room */
		goto no_exit;

	seconds += day_secs;

	#if (__dest_os == __win32_os || __dest_os == __wince_os)
		/* Make this number relative to 1970 rather than 1900 */
		seconds -= ((365 * 70UL) + 17) * 24 * 60 * 60;
	#endif

	*time = seconds;

	__time2tm(seconds, tm);

	return(1);

no_exit:

	return(0);
}

/*
 *	wasciitime - similar to wasctime, but requires a pointer to result
string as input
 */

static void wasciitime(struct tm tm, wchar_t * str)
{
	size_t n;
	
	if (mktime(&tm) == (time_t) -1)
	{
		n = wcslen(L"xxx xxx xx xx:xx:xx xxxx\n");
		swprintf(str, n, L"xxx xxx xx xx:xx:xx xxxx\n");
		return;
	}

		n = wcslen( L"%.3s %.3s%3d %.2d:%.2d:%.2d %d\n");
	swprintf(str, n, L"%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",

	day_name[tm.tm_wday],

	month_name[tm.tm_mon],

	tm.tm_mday,

	tm.tm_hour,

	tm.tm_min,

	tm.tm_sec,

	tm.tm_year + 1900);
}

/*
 *	clear_tm - sets a broken-down time to the equivalent of 1900/1/1 00:00:00
 */

static void clear_tm(struct tm * tm)
{
	tm->tm_sec   =  0;
	tm->tm_min   =  0;
	tm->tm_hour  =  0;
	tm->tm_mday  =  1;
	tm->tm_mon   =  0;
	tm->tm_year  =  0;
	tm->tm_wday  =  1;
	tm->tm_yday  =  0;
	tm->tm_isdst = -1;
}

/*
 *	ANSI Routines
 */

static int _MSL_CDECL wemit(wchar_t * str, size_t size, size_t * max_size, const wchar_t * format_str, ...)
{
#if __PPC_EABI__ || __MIPS__  /* __dest_os == __mips_bare */		/*- scm 970709 -*/
	va_list args;                            						/*- scm 970709 -*/	
	va_start( args, format_str );            						/*- scm 970709 -*/
#endif                                      						/*- scm 970709 -*/

	if (size > *max_size)
		return(0);

	*max_size -= size;

#if __PPC_EABI__ || __MIPS__  /* __dest_os == __mips_bare */					/*- scm 970709 */
	return(vswprintf(str, size+1,  format_str, args)); 		/*- scm 970709 -*/	/*- mm 990322 -*/
#else                                        
	return(vswprintf(str, size+1, format_str, __va_start(format_str)));			/*- mm 990322 -*/
#endif                                       
}

static int week_num(const struct tm * tm, int starting_day)
{
	int	days = tm->tm_yday;

	days -= __msl_mod(tm->tm_wday - starting_day, 7);	/*- cc 010510 -*/

	if (days < 0)
		return(0);

	return((days / 7) + 1);
}

/*- beginning mm 021220 -*/
size_t _MSL_CDECL wcsftime(wchar_t * _MSL_RESTRICT str, size_t max_size, const wchar_t * _MSL_RESTRICT format_str, 
																						const struct tm * _MSL_RESTRICT timeptr)
{
	struct tm tm;
	static const struct tm	default_tm = {0, 0, 0, 1, 0, 0, 1, 0, -1};
	size_t 					num_chars, chars_written, space_remaining;
	const wchar_t *			format_ptr;
	const wchar_t *			curr_format;
	int 					n, ISO8601Year, ISO8601WeekNo;
	char                 	temp_string[32];
	wchar_t					wtemp_string[32];
	struct __locale *    	current_locale_ptr;
	size_t                  char_cnt;
	const char *                  charptr;							

	current_locale_ptr = &_MSL_LOCALDATA(_current_locale);				
	
	if ((space_remaining = --max_size) <= 0)
		return(0);

	tm = default_tm;

	if (timeptr)
	{
		tm = *timeptr;

		if (mktime(&tm) == (time_t) -1)
			tm = default_tm;
	}

	format_ptr    = format_str;
	chars_written = 0;

	while (*format_ptr)
	{
		if (!(curr_format = wcschr(format_ptr, '%')))
		{
			if ((num_chars = wcslen(format_ptr)) != 0)
			{
				if (num_chars <= space_remaining)						
				{
					wmemcpy(str, format_ptr, num_chars);

					chars_written   += num_chars;
					str             += num_chars;
					space_remaining -= num_chars;
				}
				else
					return (0);
			}

			break;
		}

		if ((num_chars = curr_format - format_ptr) != 0)
		{
			if (num_chars <= space_remaining)							
			{
				wmemcpy(str, format_ptr, num_chars);

				chars_written += num_chars;
				str           += num_chars;
				space_remaining -= num_chars;							
			}
			else														
				return (0);												
		}

		format_ptr = curr_format;
		if ((*(format_ptr+1) == L'E') || (*(format_ptr+1) == L'O'))	
			++format_ptr;											
			
		switch (*++format_ptr)
		{
			case L'a':
				strcpy(temp_string, (const char *)__MSL_extract_name(current_locale_ptr->time_cmpt_ptr->Day_Names, tm.tm_wday * 2));	/*- cc 030131 -*/	
				num_chars = wemit(str, 3, &space_remaining, L"%s", temp_string);
				break;

			case L'A':
				strcpy(temp_string, (const char *)__MSL_extract_name(current_locale_ptr->time_cmpt_ptr->Day_Names, tm.tm_wday * 2 + 1));/*- cc 030131 -*/		
				num_chars = wemit(str, strlen(temp_string), &space_remaining, L"%s", temp_string); 							
				break;

			case L'b':
			case L'h':
				strcpy(temp_string, (const char *)__MSL_extract_name(current_locale_ptr->time_cmpt_ptr->MonthNames, tm.tm_mon * 2 + 1));/*- cc 030131 -*/		
				num_chars = wemit(str, 3, &space_remaining, L"%.3s", temp_string); 
				break;

			case L'B':
				strcpy(temp_string, (const char *)__MSL_extract_name(current_locale_ptr->time_cmpt_ptr->MonthNames, tm.tm_mon * 2 + 1));/*- cc 030131 -*/		
				num_chars = wemit(str, strlen(temp_string), &space_remaining, L"%s", temp_string);							
				break;

			case L'c':
				charptr = current_locale_ptr->time_cmpt_ptr->DateTime_Format;
				char_cnt = mbsrtowcs(wtemp_string, &charptr, 32, NULL);
				if (char_cnt == -1)
					return (0);
				num_chars = wcsftime(str, space_remaining+1, wtemp_string, &tm);		
				space_remaining -= num_chars;
				break;

			case L'd':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_mday);
				break;
			
			case L'D':																		
				num_chars = wcsftime(str, space_remaining+1, L"%m/%d/%y", &tm);				
				break;																		

			case L'e':																		
				num_chars = wemit(str, 2, &space_remaining, L"%2d", tm.tm_mday);			
				break;																		

			case L'F':																		
				num_chars = wemit(str, 10, &space_remaining, L"%.4d-%.2d-%.2d", 			
											tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);	
				break;	
				
		#ifndef _No_Floating_Point																	

			case 'g':																		
				ISO8601WeekNo = __MSL_ISO8601Week(timeptr, &ISO8601Year);							
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", ISO8601Year % 100);   	
				break;																		

			case 'G':																		
				ISO8601WeekNo = __MSL_ISO8601Week(timeptr, &ISO8601Year);							
				num_chars = wemit(str, 4, &space_remaining, L"%.4d", ISO8601Year + 1900);		
				break;	
																					
		#endif /* _No_Floating_Point */

			case L'H':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_hour);
				break;

			case L'I':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", (n = tm.tm_hour % 12) ? n : 12);
				break;

			case L'j':
				num_chars = wemit(str, 3, &space_remaining, L"%.3d", tm.tm_yday + 1);
				break;

			case L'm':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_mon + 1);
				break;

			case L'M':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_min);
				break;

			case L'n':																		
				num_chars = wemit(str, 2, &space_remaining, L"\n");							
				break;

			case L'p':
				num_chars = wemit(str, 2, &space_remaining, L"%.2s", tm.tm_hour < 12 ? "AM" : "PM");
				break;
				
			case L'r':
				charptr = current_locale_ptr->time_cmpt_ptr->Twelve_hr_format;
				char_cnt = mbsrtowcs(wtemp_string, &charptr, 32, NULL);
				if (char_cnt == -1)
					return (0);
				num_chars = wcsftime(str, space_remaining+1, wtemp_string, &tm);		
				space_remaining -= num_chars;
				break;
			
			case L'R':
				num_chars = wcsftime(str, space_remaining+1, L"%H:%M", &tm); 
				space_remaining -= num_chars;	
				break;

			case L'S':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_sec);
				break;

			case 't':
				num_chars = wemit(str, 2, &space_remaining, L"\t");							
				break;

			case L'T':
				num_chars = wcsftime(str, space_remaining+1, L"%H:%M:%S", &tm); 
				space_remaining -= num_chars;	
				break;

			case 'u':
				if (tm.tm_wday == 0)														
					num_chars = wemit(str, 1, &space_remaining, L"7");						
				else																		
					num_chars = wemit(str, 1, &space_remaining, L"%.1d", tm.tm_wday);			
				break;																		

			case L'U':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", week_num(&tm, 0));
				break;

		#ifndef _No_Floating_Point
			case 'V':																		
				ISO8601WeekNo = __MSL_ISO8601Week(timeptr, &ISO8601Year);					
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", ISO8601WeekNo);			
				break;	
		#endif /* _No_Floating_Point */	
															
			case L'w':
				num_chars = wemit(str, 1, &space_remaining, L"%.1d", tm.tm_wday);
				break;

			case L'W':
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", week_num(&tm, 1));
				break;

			case L'x':
				num_chars = wcsftime(str, space_remaining, L"%d %B, %Y", &tm);
				max_size -= num_chars;
				break;

			case L'X':
				num_chars = wcsftime(str, space_remaining, L"%H:%M:%S", &tm);
				max_size -= num_chars;
				break;

			case L'y':
			case L'C':																/*- mm 021218 -*/
				num_chars = wemit(str, 2, &space_remaining, L"%.2d", tm.tm_year % 100);   /*- mm 970728 -*/
				break;

			case L'Y':
				num_chars = wemit(str, 4, &space_remaining, L"%.4d", tm.tm_year + 1900);
				break;

		#ifndef _No_Floating_Point
			case L'z':					/*- mm 030103 -*/
			{
				time_t local, utc, now;
			    struct tm localtm, *utctmptr;
			    double diff, diffmins, diffhours;
		#ifndef _No_Time_OS_Support													
			    now = time(NULL);
			    utctmptr = gmtime(&now);
			#else																		
				now = NULL;													
				utctmptr = NULL;											
		#endif   /*	#ifndef _No_Time_OS_Support */									
			    if (utctmptr == NULL)
			    	num_chars = wemit(str, 4, &space_remaining, L"0000");
			    else
			    {
			    	localtm = *localtime(&now);
				    local = mktime(&localtm);
				    utc   = mktime(utctmptr);
				    diff  = difftime(local, utc);
				    diffhours = (int)diff/3600;
				    diffmins  = abs(diff/60 - diffhours*60);
				    num_chars = wemit(str, 5, &space_remaining, L"%+03.0f%02.0f", diffhours, diffmins);
				}
				break;
				    
			}
		#endif /* _No_Floating_Point */	

			case L'Z':	
				if (*current_locale_ptr->time_cmpt_ptr->TimeZone == '\0')												
				{
					num_chars = 0;
					str[0] = '\0';
				}
				else
				    num_chars = wemit(str, strlen(current_locale_ptr->time_cmpt_ptr->TimeZone), &space_remaining, L"%s",	
				                                                     current_locale_ptr->time_cmpt_ptr->TimeZone);		
				break;
				
			case L'%':                    									
				num_chars = wemit(str,2, &space_remaining, L"%%", *format_ptr);
				break;

			default:
				num_chars = wemit(str, 2, &space_remaining, L"%%%c", *format_ptr);
				break;
		}

		if (!num_chars)
			return(0);

		chars_written += num_chars;
		str           += num_chars;

		++format_ptr;
	}

	*str = 0;
	if(max_size  < chars_written) 
		return (0);
	else 
		return(chars_written);

}

#endif /* _MSL_C99 */													/*- mm 030304 -*/
#endif /* #if _MSL_WIDE_CHAR*/											/*- mm 981020 -*/
/*- end of mm 021220 -*/

/* Change record:
 * JCM 980128 First code release.
 * mf  980514 wince changes
 * mm  981020 Added #if _MSL_WIDE_CHAR wrappers
 * mm  990322 Allow for the fact that the count wsprintf includes the terminating null char.  See C9x
 * mm  990322 Make two char string constants into wchar_t constants.	
 * mm  990331 Correct length to allow for the fact that swfprintf takes %s to designate a char and not wide char str
 * mm  990809 Added include of wtime.h
 * cc  000326 Removed dest_os to be_os  
 * mm  010327 Commented wasctime and wctime out since they are not defined in C99 and wasctime tampered with gmtime's threadlocal data
 * mm  010421 Corrected setting of tm_isdst
 * cc  010510 Changed __add to __msl_add
 * cc  010510 Changed __div to __msl_div
 * cc  010510 Changed __ladd to __msl_ladd
 * cc  010510 Changed __lmul to __msl_lmul
 * cc  010510 Changed __mod to __msl_mod
 * mm  010521 Deleted #include of ThreadLocalData.h
 * JWW 010918 Use time_api.h to get clock and time APIs
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * cc  010210 Added changes from msl_core_1 for e68k team
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * mm  021220 Many changes to wcsftime() to bring into C99 conformance.
 * mm  030103 Corrected case of case label in wcsftime()
 * cc  030131 Added cast to const char *
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030304 Added _MSL_C99 wrapper
 */