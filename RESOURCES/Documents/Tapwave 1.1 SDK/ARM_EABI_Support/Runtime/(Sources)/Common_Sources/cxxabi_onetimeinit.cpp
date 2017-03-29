/************************************************************************/
/*	Project...:	C++ ABI Runtime functions								*/
/*	Name......:	cxxabi_onetimeinit.cpp									*/
/*	Purpose...: implementation of the portable Itanium C++ ABI			*/
/*				see http://www.codesourcery.com/cxx-abi/				*/
/*  Copyright.: ©Copyright 2003 by metrowerks inc. All rights reserved. */
/************************************************************************/

#include <cxxabi.h>

#if __IA64_CPP_ABI_ARM__

#define INITIALIZED  1
#define INITIALIZING 2

//	extern "C" int __cxa_guard_acquire ( int *guard_object );
extern "C" __declspec(weak) int __cxa_guard_acquire ( int *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	if(*guard_object&INITIALIZED) return true;
	return false;
}

//	extern "C" void __cxa_guard_release ( int *guard_object );
extern "C" __declspec(weak) void __cxa_guard_release ( int *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	*guard_object |= INITIALIZED;
}


//	extern "C" void __cxa_guard_abort ( int *guard_object );
extern "C" __declspec(weak) void __cxa_guard_abort ( int *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	//	currently not used by CW compilers
	*guard_object &= ~(INITIALIZED|INITIALIZING);
}

#else

//	The guard_object argument is the guard variable (see Section 2.8) associated with the
//	object to be initialized. If it indicates that the object has been initialized already,
//	return false (0) immediately. Otherwise, acquire a lock associated with the guard variable
//	(possibly part of it, but unspecified by this ABI). If the object has now been initialized,
//	release the lock and return false (0). If not, return true (1) without releasing the lock. 
//
//	extern "C" int __cxa_guard_acquire ( __int64_t *guard_object );
extern "C" __declspec(weak) int __cxa_guard_acquire ( unsigned char *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	if(*guard_object==0) return true;
	return false;
}

//	The guard_object argument is the guard variable (see Section 2.8) associated with the object
//	being initialized. Set it to indicate that initialization is complete, release the associated
//	lock (in that order), and return. 
//
//	extern "C" void __cxa_guard_release ( __int64_t *guard_object );
extern "C" __declspec(weak) void __cxa_guard_release ( unsigned char *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	*guard_object = true;
}


//	The guard_object argument is the guard variable (see Section 2.8) associated with an object
//	being initialized. Set it to indicate that initialization is not complete, release the
//	associated lock (in that order), and return. This routine is intended for use when the
//	initialization raises an exception, which requires that initialization be attempted again
//	by the next pass through the object's scope. 
//
//	extern "C" void __cxa_guard_abort ( __int64_t *guard_object );
extern "C" __declspec(weak) void __cxa_guard_abort ( unsigned char *guard_object )
{
	//	!!! dummy implementation / has to be replaced with a real thread safe version !!!
	//	currently not used by CW compilers
	*guard_object = false;
}

#endif
