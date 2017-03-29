/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/06/19 13:26:16 $
 * $Revision: 1.18.2.1 $
 */

// MSLstring.cpp

#include <MSLstring.h>
#include <msl_utility>

#undef NDEBUG

#include <cassert>

#ifndef _MSL_NO_EXCEPTIONS

#include <string>
#include <cstring>

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#if _MSL_FORCE_ENUMS_ALWAYS_INT
		#pragma enumsalwaysint on
	#else
		#pragma enumsalwaysint off
	#endif
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#if _MSL_FORCE_ENABLE_BOOL_SUPPORT
		#pragma bool on
	#else
		#pragma bool off
	#endif
#endif

_STD::_MSLstring::_MSLstring(const string& value)
	: data_(new char [value.size()+1], detail::apply_array_delete())
{
	strcpy(const_cast<char*>(static_cast<const char*>(data_.get())), value.c_str());
}

#endif // _MSL_NO_EXCEPTIONS

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace Metrowerks {
#else
	#ifndef Metrowerks
		#define Metrowerks
	#endif
#endif

_MSL_IMP_EXP_CPP bool operator==(const msl_settings& x, const msl_settings& y)
{
	if (x.data_[0] != y.data_[0])
		assert(!"msl_settings: inconsistent setting for _MSL_NO_LOCALE");
	if (x.data_[1] != y.data_[1])
		assert(!"msl_settings: inconsistent setting for _MSL_SINGLE_THREAD");
	if (x.data_[2] != y.data_[2])
		assert(!"msl_settings: inconsistent setting for _MSL_NO_EXCEPTIONS");
	if (x.data_[3] != y.data_[3])
		assert(!"msl_settings: inconsistent setting for _MSL_NO_WCHART_CPP_SUPPORT");
	if (x.data_[4] != y.data_[4])
		assert(!"msl_settings: inconsistent setting for _MSL_FORCE_ENUMS_ALWAYS_INT");
	if (x.data_[5] != y.data_[5])
		assert(!"msl_settings: inconsistent setting for _MSL_FORCE_ENABLE_BOOL_SUPPORT");
	if (x.data_[6] != y.data_[6])
		assert(!"msl_settings: inconsistent setting for _MSL_DEBUG");
	if (x.data_[7] != y.data_[7])
		assert(!"msl_settings: inconsistent setting for _MSL_USING_MSL_C");
	if (x.data_[8] != y.data_[8])
		assert(!"msl_settings: inconsistent setting for _MSL_EXTENDED_PRECISION_OUTP");
	if (x.data_[9] != y.data_[9])
		assert(!"msl_settings: inconsistent setting for _Inhibit_Container_Optimization");
	if (x.data_[10] != y.data_[10])
		assert(!"msl_settings: inconsistent setting for _MSL_RAW_ITERATORS");
	if (x.data_[11] != y.data_[11])
		assert(!"msl_settings: inconsistent setting for _MSL_NO_IO");
	if (x.data_[12] != y.data_[12])
		assert(!"msl_settings: inconsistent setting for _MSL_NO_CONSOLE_IO");
	if (x.data_[13] != y.data_[13])
		assert(!"msl_settings: inconsistent setting for _MSL_LL_FILE_SUPPORT");
	if (x.data_[14] != y.data_[14])
		assert(!"msl_settings: inconsistent setting for _No_Floating_Point");
	if (x.data_[15] != y.data_[15])
		assert(!"msl_settings: inconsistent setting for _MSL_SHARED_PTR_HAS_MUTEX");
	return true;
}

#undef check

_MSL_IMP_EXP_CPP bool check(const msl_settings& t)
{
	return msl_settings() == t;
}

#ifndef _MSL_NO_CPP_NAMESPACE
	} // namespace Metrowerks
#endif

// hh 990120 changed name of MSIPL flags
// hh 990314 Added const char* constructor to support nonstandard const char* constructors
//           on all of the standard exceptions.
// hh 030213 Installed check(const msl_settings& t), 0x8603
