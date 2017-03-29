/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/03/03 17:14:25 $
 * $Revision: 1.8 $
 */

/*
 *	Routines
 *	--------
 *		_wremove
 *		_wrename
 *		_wtmpnam
 *		_wfopen
 *		_wfreopen
 *
 *		__whandle_reopen
 */

#pragma ANSI_strict off

#include <ansi_parms.h>

#if _MSL_WIDE_CHAR
#if _MSL_WFILEIO_AVAILABLE

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wstring.h>
#include <ansi_files.h>
#include <buffer_io.h>
#include <file_io.h>
#include <misc_io.h>
#include <critical_regions.h>
#include <msl_thread_local_data.h>

#if (__dest_os == __win32_os  || __dest_os == __wince_os)
	#include <crtl.h>							/*- mm 990609 -*/
#endif

#ifndef _No_Disk_File_OS_Support

int _MSL_CDECL _wremove(const wchar_t * name)
{
	return((__wdelete_file(name) == __no_io_error) ? 0 : -1);
}


#if !__MACH__ || _MSL_CARBON_FILE_APIS
int _MSL_CDECL _wrename(const wchar_t * old_name, const wchar_t * new_name)
{
	return((__wrename_file(old_name, new_name) == __no_io_error) ? 0 : -1);
}
#endif


wchar_t * _MSL_CDECL _wtmpnam(wchar_t * name)
{
	/*- BLC 991210 -*/
#if !(_MSL_THREADSAFE && (__dest_os == __win32_os || __dest_os == __wince_os))
	static wchar_t wtemp_name[L_tmpnam];
#endif
	
	if (name)
	{
		__wtemp_file_name(name, NULL);
		return(name);
	}
	else
	{
		/*- KO 961219 -*/
		__wtemp_file_name(_MSL_LOCALDATA(wtemp_name), NULL);
		return(_MSL_LOCALDATA(wtemp_name));
	}
}


FILE * _MSL_CDECL _wfopen(const wchar_t * _MSL_RESTRICT name, const wchar_t * _MSL_RESTRICT mode)
{
	FILE * file;
	
	__begin_critical_region(files_access);
	
	file = _wfreopen(name, mode, __find_unopened_file());
	
	__end_critical_region(files_access);
	
	return(file);
}


FILE * _MSL_CDECL _wfreopen(const wchar_t * _MSL_RESTRICT name, const wchar_t * _MSL_RESTRICT mode, FILE * _MSL_RESTRICT file)
{
	__file_modes	modes;
	
	__stdio_atexit();
	
	if (!file)
		return(NULL);
	
	fclose(file);
	clearerr(file);
	
	if (!__wget_file_modes(mode, &modes))
		return(NULL);
	
	__init_file(file, modes, 0, BUFSIZ);
	
	if (__wopen_file(name, modes, &file->handle))
	{
		file->mode.file_kind = __closed_file;
	    if (file->state.free_buffer)       /*- mm 960719 -*/
	    	free(file->buffer);            /*- mm 960719 -*/
		return(NULL);
	}
	if (modes.io_mode & __append)			/*- mm 990119 -*/
		fseek(file, 0, SEEK_END);			/*- mm 990119 -*/
	
	return(file);
}


FILE * _MSL_CDECL __whandle_open(__file_handle handle, const wchar_t * mode)
{
	FILE * file;
	
	__begin_critical_region(files_access);
	
	file = __whandle_reopen(handle, mode, __find_unopened_file());
	
	__end_critical_region(files_access);
	
	return(file);
}


FILE * _MSL_CDECL __whandle_reopen(__file_handle handle, const wchar_t * mode, FILE * file)
{
	__file_modes	modes;
	
	__stdio_atexit();
	
	if (!file)
		return(NULL);
	
	fclose(file);
	clearerr(file);
	
	if (!__wget_file_modes(mode, &modes))
		return(NULL);
	
	__init_file(file, modes, 0, BUFSIZ);
	
	file->handle = handle;
	
	return(file);
}


int _MSL_CDECL __wget_file_modes(const wchar_t * mode, __file_modes * modes)
{
	const wchar_t *	mode_ptr = mode;
	unsigned long	mode_str;
	unsigned char	open_mode, io_mode;
	
	modes->file_kind = __disk_file;
	modes->file_orientation = __unoriented;
	modes->binary_io = 0;
	
	mode_str = *mode_ptr++;
	
	switch (mode_str)
	{
		case 'r':
			open_mode = __must_exist;
			break;
		
		case 'w':
			open_mode = __create_or_truncate;
			break;
		
		case 'a':
			open_mode = __create_if_necessary;
			break;
		
		default:
			return(0);
	} 
	
	
	modes->open_mode = open_mode;
	
	switch (*mode_ptr++)
	{
		case L'b':
			modes->binary_io = 1;
			
			if (*mode_ptr == L'+')
				mode_str = (mode_str << 8) | '+';
			
			break;
			
		case L'+':
			mode_str = (mode_str << 8) | '+';
			
			if (*mode_ptr == L'b')
				modes->binary_io = 1;
			
			break;
	}
	
	switch (mode_str)
	{
		case 'r':
			io_mode = __read;
			break;
						
		case 'w':
			io_mode = __write;
			break;
			
		case 'a':
			io_mode = __write | __append;
			break;
			
		case 'r+':
			io_mode = __read_write;
			break;
			
		case 'w+':
			io_mode = __read_write;
			break;
			
		case 'a+':
			io_mode = __read_write | __append;
			break;
	}
	
	modes->io_mode = io_mode;
	
	return(1);
}

#endif /* ndef _No_Disk_File_OS_Support */

#endif	/* _MSL_WFILEIO_AVAILABLE */
#endif	/* _MSL_WIDE_CHAR */

/* Change record:
 * JWW 021010 Added wchar_t file I/O routines controlled by _MSL_WFILEIO_AVAILABLE
 * JWW 021031 Made thread local data available for Mach-O
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 */