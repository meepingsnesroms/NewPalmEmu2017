/* Metrowerks ARM Runtime Support Library 
 * Copyright � 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2003/03/18 18:08:51 $ 
 * $Revision: 1.2 $ 
 */ 

/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	NMWException.cp											*/
/*	Purpose...:	portable exception handling								*/
/************************************************************************/

#ifdef __MC68K__
#pragma far_data off
#endif

#define __NOSTRING__	//	do not include <string>

//#include <Types.h>    // hh 971215 commented out per John McEnerney's instructions
#include <stdlib.h>
#include <CPlusLib.h>
#include <exception.h>
#include <NMWException.h>		 // ra 990322 changed form "" to <>

#ifndef _MSL_NO_CPP_NAMESPACE      // hh 971207 Added namespace support
	namespace std {
#endif

#if __POWERPC__ && __MWERKS__>=0x2400
#define ARRAY_HEADER_SIZE	16
#else
#define ARRAY_HEADER_SIZE	(2*sizeof(size_t))
#endif

static void dthandler()		{ abort(); };			//	default terminate handler function
static terminate_handler	thandler = dthandler;	//	pointer to terminate handler function
static void duhandler()		{ terminate(); };		//	default unexpected handler function
static unexpected_handler	uhandler = duhandler;	//	pointer to unexpected handler function

/************************************************************************/
/*	Purpose..: 	Set a terminate handler function						*/
/*	Input....:	pointer to terminate handler function					*/
/*	Return...:	---														*/
/************************************************************************/
extern terminate_handler set_terminate(terminate_handler handler) throw()  // hh 980102 added exception specific
{
	terminate_handler old=thandler; thandler=handler; return old;
}

/************************************************************************/
/*	Purpose..: 	Terminate exception handling							*/
/*	Input....:	---														*/
/*	Return...:	--- (shall not return to caller)						*/
/************************************************************************/
extern void terminate()
{
	thandler();
}

/************************************************************************/
/*	Purpose..: 	Set an unexpected handler function						*/
/*	Input....:	pointer to unexpected handler function					*/
/*	Return...:	---														*/
/************************************************************************/
extern unexpected_handler set_unexpected(unexpected_handler handler) throw()  // hh 980102 added exception specific
{
	unexpected_handler old=uhandler; uhandler=handler; return old;
}

/************************************************************************/
/*	Purpose..: 	Handle unexpected exception								*/
/*	Input....:	---														*/
/*	Return...:	--- (shall not return to caller)						*/
/************************************************************************/
extern void unexpected()
{
	uhandler();
}

#ifndef _MSL_NO_CPP_NAMESPACE
	}
#endif

/************************************************************************/
/*	Purpose..: 	Register a global object for later destruction			*/
/*	Input....:	pointer to global object								*/
/*	Input....:	pointer to destructor function							*/
/*	Input....:	pointer to global registration structure				*/
/*	Return...:	pointer to global object (pass thru)					*/
/************************************************************************/
#if !defined(__POWERPC__) && !defined(__CFM68K__)		//	only needed for classic 68K ...

extern void *__register_global_object(void *object,void *destructor,void *regmem)
{
	((DestructorChain *)regmem)->next=__global_destructor_chain;
	((DestructorChain *)regmem)->destructor=destructor;
	((DestructorChain *)regmem)->object=object;
	__global_destructor_chain=(DestructorChain *)regmem;

	return object;
}

#endif

#if IA64_CPP_ABI
#define CONSTQUALCHAR	'K'
#else
#define CONSTQUALCHAR	'C'
#endif

/************************************************************************/
/* Purpose..: Compare a throw and a catch type							*/
/* Input....: pointer to throw type										*/
/* Input....: pointer to catch type (0L: catch(...)						*/
/* Return...: true: can catch; false: cannot catch						*/
/************************************************************************/
extern char __throw_catch_compare(const char *throwtype,const char *catchtype,long *offset_result)
{
	const char	*cptr1,*cptr2;

	*offset_result=0;	
	if((cptr2=catchtype)==0)
	{	//	catch(...)
		return true;
	}
	cptr1=throwtype;
	if(*cptr2=='P')
	{	//	catch(cv T *)
		cptr2++;
#if IA64_CPP_ABI
		if(*cptr2=='V') cptr2++;
		if(*cptr2==CONSTQUALCHAR) cptr2++;
#else
		if(*cptr2==CONSTQUALCHAR) cptr2++;
		if(*cptr2=='V') cptr2++;
#endif
		if(*cptr2=='v')
		{	//	catch(cv void *)
			if(*cptr1=='P' || *cptr1=='*')
			{	//	throw T*;
				return true;
			}
		}
		cptr2=catchtype;
	}

	switch(*cptr1)
	{	//	class pointer/reference throw
	case '*':
	case '!':
		if(*cptr1++!=*cptr2++) return false;
		for(;;)
		{	//	class name compare loop
			if(*cptr1==*cptr2++)
			{
				if(*cptr1++=='!')
				{	//	class match found / get offset
					long offset;

					for(offset=0; *cptr1!='!';) offset=offset*10+*cptr1++-'0';
					*offset_result=offset; return true;
				}
			}
			else
			{
				while(*cptr1++!='!') ;			//	skip class name
				while(*cptr1++!='!') ;			//	skip offset
				if(*cptr1==0) return false;		//	no more class names => no match
				cptr2=catchtype+1;				//	retry with next class name
			}
		}
		return false;
	}

	while((*cptr1=='P' || *cptr1=='R') && *cptr1==*cptr2)
	{	//	pointer/reference catch => match cv-qualifiers
		cptr1++; cptr2++;
		if(*cptr2==CONSTQUALCHAR)
		{	//	ignore 'const' in throw type
			if(*cptr1==CONSTQUALCHAR) cptr1++;
			cptr2++;
		}
		if(*cptr1==CONSTQUALCHAR) return false;	//	throw type is more cv-qualified

		if(*cptr2=='V')
		{	//	ignore 'volatile' in throw type
			if(*cptr1=='V') cptr1++;
			cptr2++;
		}
		if(*cptr1=='V') return false;	//	throw type is more cv-qualified
	}

	//	plain type throw catch
	for(; *cptr1==*cptr2; cptr1++,cptr2++) if(*cptr1==0) return true;
	return false;
}

#if defined(__MC68K__)	

/************************************************************************/
/*	Purpose..: 	Initialize a new allocated array of objects				*/
/*	Input....:	pointer to allocated memory (+8 bytes) (0L: error)		*/
/*	Input....:	pointer to default constructor function	(or 0L)			*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	pointer to first object in array						*/
/************************************************************************/
extern void *__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor_arg,size_t size,size_t n)
{
	char	*ptr;

	if((ptr=(char *)block)!=0L)
	{
		size_t *p = (size_t *)ptr;
		//	store number of allocated objects and size of one object at the beginnig of the allocated block
		p[0]=size;
		p[1]=n;
		ptr+=ARRAY_HEADER_SIZE;

		if(ctor)
		{	//	call constructor to initialize array
			volatile ConstructorDestructor	dtor=dtor_arg;	//	force reference to dtor
			char							*p;
			size_t							i;

			#pragma exception_arrayinit
			//	this #pragma adds partial array construction exception action (ptr,dtor,size,i)

			for(i=0,p=ptr; i<n; i++,p+=size)
			{
				CTORCALL_COMPLETE(ctor,p);
			}
		}
	}
	return ptr;	//	return pointer to first object;
}

/************************************************************************/
/*	Purpose..: 	Construct an array of objects							*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to default constructor function					*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	---														*/
/************************************************************************/
extern void __construct_array(void *ptr,ConstructorDestructor ctor,ConstructorDestructor dtor_arg,size_t size,size_t n)
{
	volatile ConstructorDestructor	dtor=dtor_arg;	//	force reference to dtor
	char							*p;
	size_t							i;

	#pragma exception_arrayinit
	//	this #pragma adds partial array construction exception action (ptr,dtor,size,i)

	for(i=0,p=(char *)ptr; i<n; i++,p+=size)
	{
		CTORCALL_COMPLETE(ctor,p);
	}
}

#else

//	class __partial_array_destructor
//
//		This class is used to guarantee correct destruction of partially
//		constructed arrays if an exception is thrown from an array-element constructor.
//		We use the members of this class to keep track of the partially-constructed
//		state of the array. If the destructor for this class is called and the
//		array was not fully-constructed, we must have thrown an exception, so we
//		destroy each fully-constructed element of the array in reverse order.

class __partial_array_destructor {
private:
	void*					p;		//	pointer to start of array being constructed
	size_t					size;	//	size of each array element
	size_t					n;		//	# of elements being constructed
	ConstructorDestructor	dtor;	//	pointer to destructor for elements or 0
public:
	size_t					i;		//	current element being constructed
	
	__partial_array_destructor(void* array, size_t elementsize, size_t nelements, ConstructorDestructor destructor)
	{
		p=array; size=elementsize; n=nelements; dtor=destructor; i=n;
	}
		
	_MSL_IMP_EXP_RUNTIME ~__partial_array_destructor()
	{
		char *ptr;
		
		if(i<n && dtor)
		{
			for(ptr=(char *)p+size*i; i>0; i--)
			{
				ptr-=size;
				DTORCALL_COMPLETE(dtor,ptr);
			}
		}
	}
};

/************************************************************************/
/*	Purpose..: 	Initialize a new allocated array of objects				*/
/*	Input....:	pointer to allocated memory (+8 bytes) (0L: error)		*/
/*	Input....:	pointer to default constructor function	(or 0L)			*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	pointer to first object in array						*/
/************************************************************************/
extern void *__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n)
{
	char	*ptr;

	if((ptr=(char *)block)!=0L)
	{
		size_t *p = (size_t *)ptr;
		//	store number of allocated objects and size of one object at the beginnig of the allocated block
		p[0]=size;
		p[1]=n;
		ptr+=ARRAY_HEADER_SIZE;

		if(ctor)
		{	//	call constructor to initialize array
			__partial_array_destructor pad(ptr,size,n,dtor);
			char	*p;

			for(pad.i=0,p=(char *)ptr; pad.i<n; pad.i++,p+=size) CTORCALL_COMPLETE(ctor,p);
		}
	}
	return ptr;	//	return pointer to first object;
}

/************************************************************************/
/*	Purpose..: 	Construct an array of objects							*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to default constructor function					*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	---														*/
/************************************************************************/
extern void __construct_array(void *ptr,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n)
{
	__partial_array_destructor pad(ptr,size,n,dtor);
	char	*p;

	for(pad.i=0,p=(char *)ptr; pad.i<n; pad.i++,p+=size) CTORCALL_COMPLETE(ctor,p);
}

#endif

/************************************************************************/
/*	Purpose..: 	Destroy an array of objects								*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to destructor function							*/
/*	Input....:	size of one object										*/
/*	Input....:	number of objects										*/
/*	Return...:	---														*/
/************************************************************************/
extern void __destroy_arr(void *block,ConstructorDestructor dtor,size_t size,size_t n)
{
	char	*p;

	for(p=(char *)block+size*n; n>0; n--)
	{
		p-=size;
		DTORCALL_COMPLETE(dtor,p);
	}
}

/************************************************************************/
/*	Purpose..: 	Delete an array of objects								*/
/*	Input....:	pointer to first object	(can be NULL)					*/
/*	Input....:	pointer to destructor function							*/
/*	Return...:	---														*/
/************************************************************************/
extern void __destroy_new_array(void *block,ConstructorDestructor dtor)
{
	if(block)
	{
		if(dtor)
		{
			size_t	i,objects,objectsize;
			char	*p;

			objectsize=*(size_t *)((char *)block-ARRAY_HEADER_SIZE);
			objects=((size_t *)((char *)block-ARRAY_HEADER_SIZE))[1];
			p=(char *)block+objectsize*objects;
			for(i=0; i<objects; i++)
			{
				p-=objectsize;
				DTORCALL_COMPLETE(dtor,p);
			}
		}
		#if __MWERKS__>=0x2020
		::operator delete[] ((char *)block-ARRAY_HEADER_SIZE);
		#else
		::operator delete ((char *)block-ARRAY_HEADER_SIZE);
		#endif
	}
}

/************************************************************************/
/*	Purpose..: 	Destroy a new allocated array of objects				*/
/*	Input....:	pointer to first object	(can be NULL)					*/
/*	Input....:	pointer to destructor function (not NULL)				*/
/*	Return...:	pointer to complete array block							*/
/************************************************************************/
extern void *__destroy_new_array2(void *block,ConstructorDestructor dtor)
{
	size_t	i,objects,objectsize;
	char	*p;

	if(block==NULL) return NULL;

	if(dtor)
	{	//	destroy array members
		objectsize=*(size_t *)((char *)block-ARRAY_HEADER_SIZE);
		objects=((size_t *)((char *)block-ARRAY_HEADER_SIZE))[1];
		p=(char *)block+objectsize*objects;
		for(i=0; i<objects; i++)
		{
			p-=objectsize;
			DTORCALL_COMPLETE(dtor,p);
		}
	}

	//	return pointer to complete array block
	return (char *)block-ARRAY_HEADER_SIZE;
}

/************************************************************************/
/*	Purpose..: 	Destroy/delete a new allocated array of objects			*/
/*	Input....:	pointer to first object	(or NULL)						*/
/*	Input....:	pointer to destructor function (or NULL)				*/
/*	Input....:	pointer to deallocation function (or NULL)				*/
/*	Input....:	1: deallocation has size_t parameter					*/
/*	Return...:	pointer to complete array block							*/
/************************************************************************/
extern void __destroy_new_array3(void *block,ConstructorDestructor dtor,void *dealloc_func,short has_size_t_param)
{
	size_t	i,elements,elementsize;
	char	*p;

	if(block)
	{
		elements	= ((size_t *)((char *)block-ARRAY_HEADER_SIZE))[1];
		elementsize	= *(size_t *)((char *)block-ARRAY_HEADER_SIZE);

		if(dtor!=NULL)
		{	//	destroy array elements
			p=(char *)block+elements*elementsize;
			for(i=0; i<elements; i++)
			{
				p-=elementsize;
				DTORCALL_COMPLETE(dtor,p);
			}
		}

		if(dealloc_func!=NULL)
		{	//	call deallocation functiuon
			p=(char *)block-ARRAY_HEADER_SIZE;
			if(has_size_t_param)
			{
				((void (*)(void *,size_t))dealloc_func)(p,elements*elementsize+ARRAY_HEADER_SIZE);
			}
			else ((void (*)(void *))dealloc_func)(p);
		}
	}
}

//  hh 971207 Added namespace support
//  hh 971215 commented out <Types.h> per John McEnerney's instructions
//  hh 980102 added exception specific to set_terminate and set_unexpected
// JWW 000418 export partial array destructor to remove dependency on the .exp file