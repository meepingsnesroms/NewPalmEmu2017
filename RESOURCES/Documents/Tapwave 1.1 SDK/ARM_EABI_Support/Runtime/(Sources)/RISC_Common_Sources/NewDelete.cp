/* Metrowerks ARM Runtime Support Library 
 * Copyright © 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2003/03/18 18:08:50 $ 
 * $Revision: 1.2 $ 
 */ 


/*
 *	NewDelete.cp	-	C++ 'new' and 'delete' operators
 *
 */

#include <new>
#include <stdlib.h>


#pragma overload	extern void *operator new(size_t) throw(std::bad_alloc);
#pragma overload	extern void *operator new(size_t,const std::nothrow_t&) throw();
#pragma overload	extern void operator delete(void *) throw();

#if __MWERKS__>=0x2020
#pragma overload	extern void *operator new[](size_t) throw(std::bad_alloc);
#pragma overload	extern void *operator new[](size_t,const std::nothrow_t&) throw();
#pragma overload	extern void operator delete[](void *) throw();
#endif


#ifdef _MSL_USING_NAMESPACE
namespace std {
#endif


	/*	public data	*/

nothrow_t nothrow;						/*	pass this to operator new to avoid exception on failure	*/
char __throws_bad_alloc = 1;			/*	0 -> operator new() may return NULL	*/
new_handler __new_handler = 0;			/*	current operator new() failure handler	*/


/*
 *	set_new_handler	-	setup pointer to new_handler function
 *
 */

new_handler set_new_handler(new_handler new_new_handler) throw()
{
	new_handler old_new_handler = __new_handler;
	char *p = (char *) new_new_handler;
	
	__new_handler = new_new_handler;
	return old_new_handler;
}


#ifdef _MSL_USING_NAMESPACE
}
#endif


/*
 *	operator new	-	standard C++ 'new' operator (throws exception on failure)
 *
 */

void *operator new(size_t size) throw(std::bad_alloc)
{
	void *ptr;
	
		/*	if the caller wants to allocate an object of size 0, allocate 1		*/
		/*	byte so that we return a valid pointer and don't confuse malloc()	*/
	
	if (size == 0)
		size = 1;
		
		/*	try to allocate memory until we fail and/or throw an exception	*/
	
	while ((ptr = malloc(size)) == NULL) {
		if (std::__new_handler)
			std::__new_handler();
		else if (std::__throws_bad_alloc)
			throw std::bad_alloc();
		else
			return NULL;
	}
	
		/*	return the pointer to the allocated memory	*/
	
	return ptr;
}


/*
 *	operator new	-	standard C++ 'new' operator (no exception on failure)
 *
 */

void *operator new(size_t size, const std::nothrow_t&) throw()
{
	void *ptr;
	
		/*	if the caller wants to allocate an object of size 0, allocate 1		*/
		/*	byte so that we return a valid pointer and don't confuse malloc()	*/
	
	if (size == 0)
		size = 1;
		
		/*	try to allocate memory until we fail	*/
	
	while ((ptr = malloc(size)) == NULL) {
		if (std::__new_handler) {
			try {
				std::__new_handler();
			}
			catch (std::bad_alloc) {
				return NULL;
			}
		}
		else
			return NULL;
	}
	
		/*	return the pointer to the allocated memory	*/
	
	return ptr;
}


/*
 *	operator delete	-	standard C++ 'delete' operator
 *
 *	The test for (ptr != NULL) is probably redundant.
 *
 */

void operator delete(void *ptr) throw()
{
	if (ptr != NULL)
		free(ptr);
}


#if __MWERKS__>=0x0202

/*
 *	operator new[]		-	standard C++ 'new[]' operator
 *
 */

void *operator new[](size_t size) throw(std::bad_alloc)
{
	return operator new(size);
}

/*
 *	operator new[]		-	standard C++ 'new[]' operator (no exception on failure)
 *
 */

void *operator new[](size_t size, const std::nothrow_t& nt) throw()
{
	return operator new(size, nt);
}

/*
 *	operator delete[]	-	standard C++ 'delete[]' operator
 *
 */

void operator delete[](void *ptr) throw()
{
	operator delete(ptr);
}

#endif
