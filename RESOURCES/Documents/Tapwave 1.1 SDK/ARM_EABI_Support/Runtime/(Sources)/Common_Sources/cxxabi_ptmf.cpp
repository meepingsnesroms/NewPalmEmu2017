/************************************************************************/
/*	Project...:	Portable IA64 C++ ABI Runtime functions					*/
/*	Name......:	cxxabi_ptmf.cpp											*/
/*	Purpose...: implementation of the portable Itanium C++ ABI			*/
/*				see http://www.codesourcery.com/cxx-abi/				*/
/*  Copyright.: �Copyright 2003 by metrowerks inc. All rights reserved. */
/************************************************************************/

#include <cxxabi.h>
#include <stddef.h>

/*

2.3 Member Pointers 

A pointer to data member is an offset from the base address of the class object
containing it, represented as a ptrdiff_t. It has the size and alignment attributes
of a ptrdiff_t. A NULL pointer is represented as -1. 

A pointer to member function is a pair as follows: 

ptr: 
For a non-virtual function, this field is a simple function pointer.
(Under current base Itanium psABI conventions, that is a pointer to a GP/function
address pair.) For a virtual function, it is 1 plus the virtual table offset (in bytes)
of the function, represented as a ptrdiff_t. The value zero represents a NULL pointer,
independent of the adjustment field value below. 

adj: 
The required adjustment to this, represented as a ptrdiff_t. 

It has the size, data size, and alignment of a class containing those two members,
in that order. (For 64-bit Itanium, that will be 16, 16, and 8 bytes respectively.) 

*/

//	private definitions/declarations

namespace {
	struct PTMF {
		union {
			void		(*func_addr)();		//	nonvirtual function address
			ptrdiff_t	ventry_offset;		//	offset of virtual function entry in vtable
		}	ptr;
		ptrdiff_t		adj;				//	delta to this pointer
	};
}

//	Note these are CW specific helper functions/definitions,
//	they are not part of the generic C++ ABI.

//
//	Public Data
//
extern const PTMF __ptmf_null = { 0, 0 };
