/* Metrowerks ARM Runtime Support Library 
 * Copyright � 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2003/05/08 23:50:28 $ 
 * $Revision: 1.4 $ 
 */ 

/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	CPlusLib.h												*/
/*	Purpose...:	C++ specific runtime functions							*/
/************************************************************************/

#ifndef __CPLUSLIB__
#define __CPLUSLIB__

#include <stddef.h>

//
//	#define CABI_ZEROOFFSETVTABLE		1
//		
//	forces vtable pointer to point to the first virtual function pointer,
//	the RTTI header will be at offset -sizeof(RTTIVTableHeader)
//	This flag must be set in CABI.c and in MWRTTI.cp
//

//#define __INTEL__ 1	//	define to 1 to test WIN_ABI

#if __MWERKS__ == 0x3000
	#ifndef IA64_CPP_ABI
	#define IA64_CPP_ABI	0
	#endif
#elif __MWERKS__ >= 0x3100
	#ifndef IA64_CPP_ABI
	#define IA64_CPP_ABI	1
	#endif
#endif

#if defined(__INTEL__) || IA64_CPP_ABI

#define CABI_ZEROOFFSETVTABLE		1

#else

#define CABI_ZEROOFFSETVTABLE		0

#endif

//
//	invisible constructor/destructor argument handling
//

#ifdef __INTEL__

#define CTORARG_TYPE			int
#define CTORARG_PARTIAL			(0)				//	construct non-virtual bases
#define CTORARG_COMPLETE		(1)				//	construct all bases	

#define CTORCALL_COMPLETE(ctor,objptr)\
	(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE))

#define DTORARG_TYPE			int
#define DTORARG_DELETEFLAG		0x0001			//	delete after destruction
#define DTORARG_VECTORFLAG		0x0002			//	array destruction

#define DTORCALL_COMPLETE(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,0))

#define DTORCALL_PARTIAL(dtor,objptr)\
	(((void (*)(void *))dtor)(objptr))

#else

#define CTORARG_TYPE			short
#define CTORARG_PARTIAL			(0)				//	construct non-virtual bases
#define CTORARG_COMPLETE		(1)				//	construct all bases	

#if __CFM68K__

	long __getA7(void) = { 0x200F };
	void __setA7(long a7:__d0) = { 0x2E40 };

#define CTORCALL_COMPLETE(ctor,objptr)\
	{\
		long __savedA7 = __getA7();\
		(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE));\
		__setA7(__savedA7);\
	}

#else

#define CTORCALL_COMPLETE(ctor,objptr)\
	(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE))

#endif

#define DTORARG_TYPE			short
#define DTORARG_PARTIAL			(0)				//	destroy non-virtual bases	
#define DTORARG_COMPLETE		(-1)			//	destroy all bases	
#define DTORARG_DELETE			(1)				//	destroy all bases and delete object

#define DTORCALL_COMPLETE(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,DTORARG_COMPLETE))

#define DTORCALL_PARTIAL(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,DTORARG_PARTIAL))

#define DTORCALL_VTTOBJECT(dtor,objptr,vttptr)\
	(((void (*)(void *,void*))dtor)(objptr,vttptr))

#endif

typedef void *ConstructorDestructor;	//	constructor/destructor function	pointer

typedef struct PTMF {
	long	this_delta;					//	delta to this pointer
	long	vtbl_offset;				//	offset of virtual function pointer in vtable (<0: non-virtual function address)
	union {
		void	*func_addr;				//	non-virtual function address
		long	ventry_offset;			//	offset of vtable pointer in class
	}	func_data;
}	PTMF;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MC68K__
extern long							__ptmf_test(const PTMF *ptmf);
extern long							__ptmf_cmpr(const PTMF *ptmf1,const PTMF *ptmf2);
extern void							__ptmf_call(...);
extern void							__ptmf_scall(...);
#endif

extern PTMF							*__ptmf_cast(long offset,const PTMF *ptmfrom,PTMF *ptmto);

_MSL_IMP_EXP_RUNTIME extern void	*__copy(char *to,char *from,size_t size);
_MSL_IMP_EXP_RUNTIME extern void	*__clear(char *mem,size_t size);
_MSL_IMP_EXP_RUNTIME extern void	*__new_hdl(size_t size);
_MSL_IMP_EXP_RUNTIME extern void	__del_hdl(void *hdl);
_MSL_IMP_EXP_RUNTIME extern void	*__init_arr(void *memptr,ConstructorDestructor constructor,size_t object_size,size_t nobjects);
_MSL_IMP_EXP_RUNTIME extern void	*__new_arr(ConstructorDestructor constructor,size_t object_size,size_t objects);
_MSL_IMP_EXP_RUNTIME extern void	__del_arr(void *memptr,ConstructorDestructor destructor);
_MSL_IMP_EXP_RUNTIME extern void	__dc_arr(void *mem,ConstructorDestructor con_des,short object_size,short objects);

_MSL_IMP_EXP_RUNTIME extern void	__construct_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
_MSL_IMP_EXP_RUNTIME extern void	__destroy_arr(void *block,ConstructorDestructor dtor,size_t size,size_t n);
_MSL_IMP_EXP_RUNTIME extern void	*__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
_MSL_IMP_EXP_RUNTIME extern void	__destroy_new_array(void *block,ConstructorDestructor dtor);
_MSL_IMP_EXP_RUNTIME extern void	*__destroy_new_array2(void *block,ConstructorDestructor dtor);
_MSL_IMP_EXP_RUNTIME extern void	__destroy_new_array3(void *block,ConstructorDestructor dtor,void *dealloc_func,short has_size_t_param);

#ifdef __cplusplus
}
#endif

#endif
// JWW 000418 export routines to remove dependency on the .exp file