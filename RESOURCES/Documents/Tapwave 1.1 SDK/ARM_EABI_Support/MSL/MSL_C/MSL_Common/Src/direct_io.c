/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/11 20:03:14 $
 * $Revision: 1.28 $
 */

/*
 *	Routines
 *	--------
 *		fread
 *		fwrite
 */

#include <stdio.h>
#include <string.h>
#include <ansi_files.h>
#include <file_io.h>
#include <buffer_io.h>
#include <misc_io.h>
#include <critical_regions.h>						/*- mm 001013 -*/

#ifndef _Old_DSP_IO_Interface						/*- cc 010821 -*/

size_t _MSL_CDECL fread(void * _MSL_RESTRICT ptr, size_t memb_size, size_t num_memb, FILE * _MSL_RESTRICT file)
{
	size_t retval;
	int crtrgn;						/*- mm 020627 -*/
	if (file == stdin)						/*- mm 020627 -*/
		crtrgn = stdin_access;				/*- mm 020627 -*/
	else									/*- mm 020627 -*/
		crtrgn = files_access;				/*- mm 020627 -*/
  	__begin_critical_region(crtrgn);		 /*- mm 001013 -*/			/*- mm 020627 -*/
  	retval = __fread(ptr, memb_size, num_memb, file); 	/*- mm 001018 -*/
  	__end_critical_region(crtrgn);		 		/*- mm 001013 -*//*- mm 020627 -*/
  	return(retval);
}

/* This does all the work of fread but is not threadsafe it exists so that other
   library functions can do freads in a loop from within a critical region mm 001018*/			
size_t _MSL_CDECL __fread(void * ptr, size_t memb_size, size_t num_memb, FILE * file)
{
	unsigned char *	read_ptr;
	size_t					num_bytes, bytes_to_go, bytes_read;
	int							ioresult, always_buffer;
	
#if _MSL_WIDE_CHAR && _MSL_C99								/*- mm 980205 -*/	/*- mm 030314 -*/
	if (fwide(file, 0) == 0)
		fwide(file, -1);
#endif /* _MSL_WIDE_CHAR && _MSL_C99 */                     /*- mm 980205 -*/	/*- mm 030314 -*/

	bytes_to_go = memb_size * num_memb;
	
	if (!bytes_to_go || file->state.error || file->mode.file_kind == __closed_file)
		return(0);
	
	always_buffer = !file->mode.binary_io || file->mode.buffer_mode == _IOFBF;  /*- mm 961107 -*/ /*- mm 990816 -*/
	
	if (file->state.io_state == __neutral)
		if (file->mode.io_mode & __read)
		{
			file->state.io_state = __reading;
			file->buffer_len     = 0;
		}
	
	if (file->state.io_state < __reading)
	{
		set_error(file);
		return(0);
	}

     /*- mm 970708 -*/
	if (file->mode.buffer_mode & (_IOLBF | _IONBF)) {
		if (__flush_line_buffered_output_files()) {
			set_error(file);
			return 0;
		}
	}
     /*- mm 970708 -*/
	
	read_ptr    = (unsigned char *) ptr;
	bytes_read  = 0;
	
	if (bytes_to_go && file->state.io_state >= __rereading)
	{
		do
		{
	
#if _MSL_WIDE_CHAR && _MSL_C99						/*- mm 980205 -*/	/*- mm 030314 -*/
			if (fwide(file, 0) == 1)
			{
				*(wchar_t*)read_ptr = file->ungetwc_buffer[file->state.io_state - __rereading];
				read_ptr   += sizeof(wchar_t);
				bytes_read += sizeof(wchar_t);
				bytes_to_go-= sizeof(wchar_t);
			}
			else
			{
				*read_ptr++ = file->ungetc_buffer[file->state.io_state - __rereading];
				bytes_read++;
				bytes_to_go--;
			}
#else
			*read_ptr++ = file->ungetc_buffer[file->state.io_state - __rereading];
			bytes_read++;
			bytes_to_go--;
#endif /* _MSL_WIDE_CHAR && _MSL_C99 */             /*- mm 980205 -*/	/*- mm 030314 -*/
			
			
			file->state.io_state--;
		}
		while (bytes_to_go && file->state.io_state >= __rereading);
		
		if (file->state.io_state == __reading)
			file->buffer_len = file->saved_buffer_len;
	}
	
	if (bytes_to_go && (file->buffer_len || always_buffer))
		do
		{
			if (!file->buffer_len)
			{
				ioresult = __load_buffer(file, NULL, __align_buffer);
				
				if (ioresult)
				{
					if (ioresult == __io_error)
						set_error(file);
					else
						set_eof(file);
					bytes_to_go = 0;
					break;
				}
			}
			
			num_bytes = file->buffer_len;
			
			if (num_bytes > bytes_to_go)
				num_bytes = bytes_to_go;
			
			memcpy(read_ptr, file->buffer_ptr, num_bytes);
			
			read_ptr    += num_bytes;
			bytes_read  += num_bytes;
			bytes_to_go -= num_bytes;
			
			file->buffer_ptr += num_bytes;
			file->buffer_len -= num_bytes;
		}
		while (bytes_to_go && always_buffer);
	
	if (bytes_to_go && !always_buffer)
	{
		unsigned char *	save_buffer = file->buffer;
		size_t					save_size   = file->buffer_size;
		
		file->buffer      = read_ptr;
		file->buffer_size = bytes_to_go;
		
		ioresult = __load_buffer(file, &num_bytes, __dont_align_buffer);
		
		if (ioresult)
			if (ioresult == __io_error)
				set_error(file);
			else
				set_eof(file);
		
		bytes_read += num_bytes;
		
		file->buffer        = save_buffer;
		file->buffer_size   = save_size;
		
		__prep_buffer(file);
		
		file->buffer_len = 0;
	}
	
	return(bytes_read / memb_size);                         /*- mm 980203 -*/
}

size_t _MSL_CDECL fwrite(const void * _MSL_RESTRICT ptr, size_t memb_size, size_t num_memb, FILE * _MSL_RESTRICT file)
{
	size_t retval;
	int crtrgn;						/*- mm 020627 -*/
	if (file == stdout)				/*- mm 020627 -*/
		crtrgn = stdout_access;				/*- mm 020627 -*/
	else if (file == stderr)				/*- mm 020627 -*/
		crtrgn = stderr_access;				/*- mm 020627 -*/
	else									/*- mm 020627 -*/
		crtrgn = files_access;				/*- mm 020627 -*/
  	__begin_critical_region(crtrgn);		 /*- mm 001013 -*/			/*- mm 020627 -*/
  	retval = __fwrite(ptr, memb_size, num_memb, file); 	/*- mm 001018 -*/
  	__end_critical_region(crtrgn);		 		/*- mm 001013 -*//*- mm 020627 -*/
  	return(retval);
}

/* This does all the work of fwrite but is not threadsafe it exists so that other
   library functions can do fwrites in a loop from within a critical region mm 001018*/			
size_t _MSL_CDECL __fwrite(const void * ptr, size_t memb_size, size_t num_memb, FILE * file)
{
	unsigned char *	write_ptr;
	size_t					num_bytes, bytes_to_go, bytes_written;
	int							ioresult, always_buffer;
	
	
#if _MSL_WIDE_CHAR && _MSL_C99							/*- mm 980205 -*/	/*- mm 030314 -*/
	if (fwide(file, 0) == 0)
		fwide(file, -1);
#endif /* _MSL_WIDE_CHAR && _MSL_C99 */                 /*- mm 980205 -*/	/*- mm 030314 -*/

	bytes_to_go = memb_size * num_memb;
	
	if (!bytes_to_go || file->state.error || file->mode.file_kind == __closed_file)
		return(0);

	if (file->mode.file_kind == __console_file)
		__stdio_atexit();
	
	always_buffer = !file->mode.binary_io ||
					 file->mode.buffer_mode == _IOFBF           ||  /*- mm 961107 -*/
					 file->mode.buffer_mode == _IOLBF;
	
	if (file->state.io_state == __neutral)
		if (file->mode.io_mode & __write)
		{
#if !defined( __BEOS__) && !defined(_No_Disk_File_OS_Support)   /* we do O_APPEND on open */ /*- mm 970708 -*/
			if (file->mode.io_mode & __append)
				if (fseek(file, 0, SEEK_END))
					return(0);
#endif                                          /*- mm 970708 -*/
						
			file->state.io_state = __writing;
			
			__prep_buffer(file);
		}
	
	if (file->state.io_state != __writing)
	{
		set_error(file);
		return(0);
	}

	write_ptr     = (unsigned char *) ptr;
	bytes_written = 0;
	
	if (bytes_to_go && (file->buffer_ptr != file->buffer || always_buffer))
	{
		file->buffer_len = file->buffer_size - (file->buffer_ptr - file->buffer);
		
		do
		{
			unsigned char *	newline = NULL;
			
			num_bytes = file->buffer_len;
			
			if (num_bytes > bytes_to_go)
				num_bytes = bytes_to_go;
			
#ifndef _Unbuffered_IO

			if (file->mode.buffer_mode == _IOLBF && num_bytes)
				if((newline = (unsigned char *) __memrchr(write_ptr, '\n', num_bytes)) != NULL)
					num_bytes = newline + 1 - write_ptr;
			
#endif
			
			if (num_bytes)
			{
				memcpy(file->buffer_ptr, write_ptr, num_bytes);
				
				write_ptr     += num_bytes;
				bytes_written += num_bytes;
				bytes_to_go   -= num_bytes;
				
				file->buffer_ptr += num_bytes;
				file->buffer_len -= num_bytes;
			}
			if (!file->buffer_len || newline != NULL || (file->mode.buffer_mode == _IONBF))  /*- mm 970716 -*/
			{
				ioresult = __flush_buffer(file, NULL);
				
				if (ioresult)
				{
					set_error(file);
					bytes_to_go = 0;
					break;
				}
			}
		}
		while (bytes_to_go && always_buffer);
	}
	
	if (bytes_to_go && !always_buffer)
	{
		unsigned char *	save_buffer = file->buffer;
		size_t					save_size   = file->buffer_size;
		
		file->buffer      = write_ptr;
		file->buffer_size = bytes_to_go;
		file->buffer_ptr  = write_ptr + bytes_to_go;
		
		if (__flush_buffer(file, &num_bytes) != __no_io_error)
			set_error(file);
		
		bytes_written += num_bytes;
		
		file->buffer      = save_buffer;
		file->buffer_size = save_size;
		
		__prep_buffer(file);
		
		file->buffer_len = 0;
	}
	
	if (file->mode.buffer_mode != _IOFBF)
		file->buffer_len = 0;
		
	return((bytes_written + memb_size - 1) / memb_size);
}

#endif /* _Old_DSP_IO_Interface */	/*- cc 010821 -*/

/* Change record:
 * JFH 950825 First code release.
 * JFH 960109 At the behest of Be, I put in real output line buffering.
 * JFH 960122 Added casts from (void *) for C++ compatibility.
 * JFH 960212 Added call to __stdio_atexit in fwrite for console files (so they will
 *			  get flushed and closed properly).
 * JFH 960219 Added check for closed files to fread and fwrite.
 * JFH 960425 Modified fread to account for multi-level 'ungetc'.
 * mm  961107 Make sure buffering occurs when _IOFBF is set.
 * mani970101 Make unbuffered stdio really work.
 * SCM 970709 Disabled output line buffering support when _Unbuffered_IO is set.
 *			  Modified to support unbuffered, non-binary files.
 * MEA 970720 Changed __no_os to _No_Disk_File_OS_Support.
 * mm  970708 Inserted Be changes
 * mm  970716 Flush unbuffered files after writing.
 * mm  980203 Corrected return value to fread to round down to the number of complete elements
 *            successfully read.  MW03272
 * mm  980205 Support for wide-characters
 * mm  980715 Made exit from fwrite with string file when buffer (i.e. string) full MW07942    
 * mm  990816 Deleted references to __string_file
 * mm  001013 Threadsafety for fread and fwrite
 * mm  001018 Creation of __fread and __fwrite with no critical regions so that they
 *            called from within a critical region
 * cc  010821 Added eppc to core
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * mm  020627 Changes to prevent io on stdin, stdout, stderr and general files from interfering with each other
 * JWW 020917 Added _MSL_RESTRICT to get the restrict type specifier for certain C99 functions
 * JWW 030224 Changed __NO_WIDE_CHAR flag into the new more configurable _MSL_WIDE_CHAR
 * mm  030314 Added _MSL_C99 wrappers for fwide
 */