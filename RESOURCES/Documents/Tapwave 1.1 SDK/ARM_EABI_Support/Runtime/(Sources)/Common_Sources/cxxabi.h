/************************************************************************/
/*	Project...:	C++ ABI Runtime functions								*/
/*	Name......:	cxxabi.h												*/
/*	Purpose...: implementation of the portable Itanium C++ ABI			*/
/*				see http://www.codesourcery.com/cxx-abi/				*/
/*  Copyright.: ©Copyright 2003 by metrowerks inc. All rights reserved. */
/************************************************************************/

#ifndef __CXXABI_H__
#define __CXXABI_H__

#include <stddef.h>
#include <typeinfo>

/*	Older versions of MSL's <typeinfo> must be updated to use this type_info for the __IA64_CPP_ABI__ !!! 

namespace std {

	class type_info {
	public:
		virtual ~type_info();
		bool operator==(const type_info &rhs) const;
		bool operator!=(const type_info &rhs) const;
		bool before(const type_info &rhs) const;
		const char* name() const {return __type_name;}
	private:
		type_info (const type_info& rhs);				//  not defined
		type_info& operator= (const type_info& rhs);	//  not defined

		const char *__type_name;
	};

}

*/

namespace abi {

	class __fundamental_type_info : public std::type_info {
	public:
		virtual ~__fundamental_type_info();

		//	no additional members
	};

	class __array_type_info : public std::type_info {
	public:
		virtual ~__array_type_info();

		//	no additional members
	};

	class __function_type_info : public std::type_info {
	public:
		virtual ~__function_type_info();

		//	no additional members
	};

	class __enum_type_info : public std::type_info {
	public:
		virtual ~__enum_type_info();

		//	no additional members
	};

	class __class_type_info : public std::type_info {
	public:
		virtual ~__class_type_info();

		//	no additional members
	};

	class __si_class_type_info : public __class_type_info {
	public:
		virtual ~__si_class_type_info();

		const __class_type_info *__base_type;
	};

	struct __base_class_type_info {
	public:
		const __class_type_info *__base_type;

#if 0
	//	32-bit ABI (no longer used)
		int				__offset;
		unsigned int	__flags;

		enum _flags_masks {
			__virtual_mask = 0x1,
			__public_mask = 0x2
		};

		inline int __get_offset() const { return __offset; }
		inline int __is_virtual() const { return __flags&__virtual_mask; }
		inline int __is_public() const { return __flags&__public_mask; }
#else
	//	64-bit ABI
		long __offset_flags;

		enum __offset_flags_masks {
			__virtual_mask = 0x1,
			__public_mask = 0x2,
			__offset_shift = 8
		};

		inline long __get_offset() const { return __offset_flags>>__offset_shift; }
		inline int __is_virtual() const { return __offset_flags&__virtual_mask; }
		inline int __is_public() const { return __offset_flags&__public_mask; }
#endif
	};

	class __vmi_class_type_info : public __class_type_info {
	public:
		virtual ~__vmi_class_type_info();

		unsigned int __flags;
		unsigned int __base_count;
		__base_class_type_info __base_info[1];

		enum __flags_masks {
			__non_diamond_repeat_mask = 0x1,
			__diamond_shaped_mask = 0x2
		};
	};

	class __pbase_type_info : public std::type_info {
	public:
		virtual ~__pbase_type_info();

		unsigned int __flags;
		const std::type_info *__pointee;

		enum __masks {
			__const_mask = 0x1,
			__volatile_mask = 0x2,
			__restrict_mask = 0x4,
			__incomplete_mask = 0x8,
			__incomplete_class_mask = 0x10
		};
	};

	class __pointer_type_info : public __pbase_type_info {
	public:
		virtual ~__pointer_type_info();

		//	no additional members
	};

	class __pointer_to_member_type_info : public __pbase_type_info {
	public:
		virtual ~__pointer_to_member_type_info();

		//	no additional members
	};
}


//	Prototypes

//	cxxabi_alloc.cpp
extern "C" void * __cxa_vec_new (
            size_t element_count,
            size_t element_size,
            size_t padding_size,
            void (*constructor) ( void *thisp ),
            void (*destructor) ( void *thisp ) );

extern "C" void * __cxa_vec_new2 (
            size_t element_count,
            size_t element_size,
            size_t padding_size,
            void (*constructor) ( void *thisp ),
            void (*destructor) ( void *thisp ),
            void* (*alloc) ( size_t size ),
            void (*dealloc) ( void *obj ) );

extern "C" void * __cxa_vec_new3 (
            size_t element_count,
            size_t element_size,
            size_t padding_size,
            void (*constructor) ( void *thisp ),
            void (*destructor) ( void *thisp ),
            void* (*alloc) ( size_t size ),
            void (*dealloc) ( void *obj, size_t size ) );

extern "C" void __cxa_vec_ctor (
            void *array_address,
            size_t element_count,
            size_t element_size,
            void (*constructor) ( void *thisp ),
            void (*destructor) ( void *thisp ) );

extern "C" void __cxa_vec_dtor (
            void *array_address,
            size_t element_count,
            size_t element_size,
            void (*destructor) ( void *thisp ) );

extern "C" void __cxa_vec_cleanup (
            void *array_address,
            size_t element_count,
            size_t element_size,
            void (*destructor) ( void *thisp ) );

extern "C" void __cxa_vec_delete (
            void *array_address,
            size_t element_size,
            size_t padding_size,
            void (*destructor) ( void *thisp ) );

extern "C" void __cxa_vec_delete2 (
            void *array_address,
            size_t element_size,
            size_t padding_size,
            void (*destructor) ( void *thisp ),
            void (*dealloc) ( void *obj ) );

extern "C" void __cxa_vec_delete3 (
            void *array_address,
            size_t element_size,
            size_t padding_size,
            void (*destructor) ( void *thisp ),
            void (*dealloc) ( void *obj, size_t size ) );

extern "C" void __cxa_vec_cctor (
            void *dest_array,
            void *src_array,
            size_t element_count,
            size_t element_size,
            void (*constructor) (void *, void *),
            void (*destructor) (void *));

//	cxxabi_badeh.cpp
extern "C" void __cxa_bad_cast ();
extern "C" void __cxa_bad_typeid ();

//	cxxabi_onetimeinit.cpp
#if __IA64_CPP_ABI_ARM__
extern "C" __declspec(weak) int __cxa_guard_acquire ( int *guard_object );
extern "C" __declspec(weak) void __cxa_guard_release ( int *guard_object );
extern "C" __declspec(weak) void __cxa_guard_abort ( int *guard_object );
#else
extern "C" __declspec(weak) int __cxa_guard_acquire ( unsigned char *guard_object );
extern "C" __declspec(weak) void __cxa_guard_release ( unsigned char *guard_object );
extern "C" __declspec(weak) void __cxa_guard_abort ( unsigned char *guard_object );
#endif

//	cxxabi_rtti.cpp
extern "C" void* __dynamic_cast (
	const void *sub,
	const abi::__class_type_info *src,
	const abi::__class_type_info *dst,
	ptrdiff_t src2dst_offset
);

#endif
