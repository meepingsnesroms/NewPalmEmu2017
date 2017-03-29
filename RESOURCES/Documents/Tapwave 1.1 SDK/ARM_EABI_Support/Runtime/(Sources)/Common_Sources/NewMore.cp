/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	NewMore.cp												*/
/*	Purpose...:	standard C++ library									*/
/*  Copyright.: Copyright © 1993-1997 Metrowerks, Inc.					*/
/************************************************************************/

#include <new>
#if __dest_os == __mac_os
#include <MacMemory.h>
#endif
#include <CPlusLib.h>

#ifndef _MSL_NO_CPP_NAMESPACE        // hh 971207 Added namespace support
	namespace std {
#endif

#ifdef __MC68K__
#pragma a6frames on
#endif

char			__throws_bad_alloc = 1;		//	default: throw bad_alloc exception
new_handler		__new_handler;

/************************************************************************/
/*	Purpose..: 	throw a bad_alloc excpetion								*/
/*	Input....:	---														*/
/*	Return...:	---														*/
/************************************************************************/
extern void __throw_bad_alloc()
{
	if(__throws_bad_alloc) throw bad_alloc();
}

/************************************************************************/
/*	Purpose..: 	Set new_handler function								*/
/*	Input....:	new_handler function pointer (or NULL)					*/
/*	Return...:	old new_handler function pointer						*/
/************************************************************************/
extern new_handler set_new_handler(new_handler new_new_handler) throw()
{
	new_handler old_new_handler = __new_handler;
	__new_handler = new_new_handler;
	return old_new_handler;
}

#ifndef _MSL_NO_CPP_NAMESPACE
	}
#endif

#if __dest_os == __mac_os

/************************************************************************/
/*	Purpose..: 	Allocate memory	(handle)								*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	handle to memory or 0L									*/
/************************************************************************/
void *__new_hdl(size_t size)
{
	void *ptr;

	for(;;)
	{
		if((ptr=NewHandle(size))!=NULL) break;
		if(!_STD::__new_handler)
		{
			_STD::__throw_bad_alloc();
			break;
		}
		_STD::__new_handler();
	}
	return ptr;
}

/************************************************************************/
/*	Purpose..: 	Dispose memory (handle)									*/
/*	Input....:	handle to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
void __del_hdl(void *hdl)
{
	if(hdl) DisposeHandle((Handle)hdl);
}

#endif /* __dest_os == __mac_os */

// hh 971207 Added namespace support
// bds 990322 ifdefed MacOS-specific code so this compiles on BeOS
