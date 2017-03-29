/************************************************************************/
/*	Project...:	C++ ABI Runtime functions								*/
/*	Name......:	cxxabi_badeh.h											*/
/*	Purpose...: implementation of the portable Itanium C++ ABI			*/
/*				see http://www.codesourcery.com/cxx-abi/				*/
/*  Copyright.: ©Copyright 2003 by metrowerks inc. All rights reserved. */
/************************************************************************/

#include <cxxabi.h>
#include <typeinfo>

//	Raise a bad_cast exception (lib.bad.cast, 18.5.2).
//	Does not return (normally), and implementations may note this fact, e.g. with pragmas. 
extern "C" void __cxa_bad_cast ()
{
	throw std::bad_cast();
}


//	Raise a bad_typeid exception (lib.bad.typeid, 18.5.3).
//	Does not return (normally), and implementations may note this fact, e.g. with pragmas. 
extern "C" void __cxa_bad_typeid ()
{
	throw std::bad_typeid();
}
