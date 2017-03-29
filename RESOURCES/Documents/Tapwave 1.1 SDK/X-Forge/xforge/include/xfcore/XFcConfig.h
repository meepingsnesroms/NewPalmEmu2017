/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief This file takes care of most of platform-dependent (type) definitions.
 * 
 * $Id: XFcConfig.h,v 1.24 2003/10/06 12:50:06 jari Exp $
 * $Date: 2003/10/06 12:50:06 $ 
 * $Revision: 1.24 $
 */

#ifndef XFC_CORE_XFCCONFIG_H_INCLUDED
#define XFC_CORE_XFCCONFIG_H_INCLUDED

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Detect platform if possible (most of the time it's safer to trust the predefined macros)
//////////////////////////////////////////////////////////////////////////

#if !(defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE) || defined(XFC_PLATFORM_EPOC6) || defined(XFC_PLATFORM_LINUX) || defined(XFC_PLATFORM_SDL) || defined(XFC_PLATFORM_PALM))

// Codewarrior doesn't support predefined macros in any sensible way, so
// for convenience we're detecting the platform here and setting the macros.
#if defined(__PALMOS_ARMLET__) && defined(__MWERKS__) 
#undef XFC_FORCEDEVICE_TAPWAVE
#define XFC_PLATFORM_PALM
#define XFC_FORCEDEVICE_TAPWAVE
#endif

#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Check if platform has been set in predefined macros
//////////////////////////////////////////////////////////////////////////

#if defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE) || defined(XFC_PLATFORM_EPOC6) || defined(XFC_PLATFORM_LINUX) || defined(XFC_PLATFORM_SDL) || defined(XFC_PLATFORM_PALM)
#else
#pragma message("--")
#pragma message("Please define X-Forge Core platform in order to compile.")
#pragma message("Legal defines: XFC_PLATFORM_DESKTOPWINDOWS XFC_PLATFORM_WINCE XFC_PLATFORM_EPOC5 XFC_PLATFORM_EPOC6 XFC_PLATFORM_LINUX XFC_PLATFORM_PALM.")
#pragma message("You can also define XFC_USE_DLL if you're using a dll version.")
#pragma message("You can also define XFC_MEMMGR_DISABLE to disable memory manager. (Mixing dll and app code with different setting on memory manager is unwise)")
#pragma message("when embedding desktop windows platform you should use XFC_USE_DLL and XFC_MEMMGR_DISABLE.")
#pragma message("You can also define XFC_COMPILER_GNUC, XFC_COMPILER_MSVC or XFC_COMPILER_ARMCPP to target for a compiler (this is detected by default)")
#pragma message("--")
#error Platform not defined.
#endif 

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Detect compiler
//////////////////////////////////////////////////////////////////////////

#if !defined(XFC_COMPILER_GNUC) && !defined(XFC_COMPILER_MSVC) && !defined(XFC_COMPILER_ARMCPP) && !defined(XFC_COMPILER_MW)
#if defined(__GNUC__) 
#define XFC_COMPILER_GNUC // GNU C++ compiler
#endif
#if defined(_MSC_VER)
#define XFC_COMPILER_MSVC // Microsoft C++ compiler (eVC or visual studio)
#endif
#if defined(__MWERKS__)   
#define XFC_COMPILER_MW   // Metrowerks codewarrior
#endif
#if defined(__ARMCC_VERSION) 
#define XFC_COMPILER_ADS  // ARM development suite
#endif
#endif

#if defined(XFC_COMPILER_GNUC)
#define XFC_COMPILER GNUC
#endif
#if defined(XFC_COMPILER_MSVC)
#define XFC_COMPILER MSVC
#endif
#if defined(XFC_COMPILER_ADS)
#define XFC_COMPILER ADS
#endif
#if defined(XFC_COMPILER_MW)
#define XFC_COMPILER MW
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Set up common defines for several platforms
//////////////////////////////////////////////////////////////////////////

#ifdef XFC_PLATFORM_EPOC6
#define XFC_PLATFORM_EPOC
#endif

#if defined(XFC_PLATFORM_WINCE) || defined(XFC_PLATFORM_DESKTOPWINDOWS)
#define XFC_PLATFORM_WINDOWS
#endif

#if defined(XFC_PLATFORM_SDL) && (defined(XFC_PLATFORM_SDL_WINDOWS) || defined(XFC_PLATFORM_SDL_LINUX))
#if defined(XFC_COMPILER_MSVC)
#define XFC_PLATFORM_SDL_WINDOWS
#else
#define XFC_PLATFORM_SDL_LINUX
#endif
#endif

#if defined(XFC_PLATFORM_WINCE)
#if defined(XFC_FORCEDEVICE_POCKETPC)
#define XFC_WINCE_POCKETPC
#elif defined(XFC_FORCEDEVICE_SMARTPHONE)
#define XFC_WINCE_SMARTPHONE
#elif CE_BUILD_VER == 12255 // Smartphone2002 = 12255
#define XFC_WINCE_SMARTPHONE
#else
#define XFC_WINCE_POCKETPC // default to pocketpc
#endif
#endif // wince

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Make sure our types have unique names
//////////////////////////////////////////////////////////////////////////

#define INT8 XFCINT8
#define INT16 XFCINT16
#define INT32 XFCINT32
#define INT64 XFCINT64
#define UINT8 XFCUINT8
#define UINT16 XFCUINT16
#define UINT32 XFCUINT32
//#define UINT64 XFCUINT64
#define FLOAT32 XFCFLOAT32
#define FLOAT64 XFCFLOAT64
#define REAL XFCREAL
#define INT XFCINT
#define UINT XFCUINT
#define CHAR8 XFCCHAR8
#define CHAR16 XFCCHAR16
#define CHAR XFCCHAR


//////////////////////////////////////////////////////////////////////////
// Assertion macros for all builds

#define XFCASSERT_ALWAYS_STR(arg) #arg
#define XFCASSERT_ALWAYS_STR_EXPAND(arg) XFCASSERT_ALWAYS_STR(arg)
//! Assertion which is tested against in both release and debug builds.
/*! Stops application execution with XFcCore::systemPanic() if assertion fails.
 */
#define XFCASSERT_ALWAYS(expr) do { if (!(expr)) XFcCore::systemPanic("Assertion failed in file " __FILE__ " line " XFCASSERT_ALWAYS_STR_EXPAND(__LINE__)); } while (0)

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Type definitions: EPOC platforms
//////////////////////////////////////////////////////////////////////////

class XFcFixed;

#if defined(XFC_PLATFORM_EPOC)

#ifdef __WINS__
    #define XFC_MEMMGR_DISABLE
    // MSVC doesn't like typenames
    #define typename
#endif

#define XFCASSERT(expr)

#undef NULL
#include <e32base.h>
#ifndef __WINS__
#ifndef XFCEPOCGETTLS
#define XFCEPOCGETTLS
__attribute__ ((unused)) static TAny * xfcEpocGetTls() { return Dll::Tls(); };
#endif
#endif

typedef TInt8 INT8;
typedef TInt16 INT16;
typedef TInt32 INT32;
typedef TInt64 INT64;
typedef TUint8 UINT8;
typedef TUint16 UINT16;
typedef TUint32 UINT32;
//typedef unsigned __int64 UINT64;
typedef TReal32 FLOAT32;
typedef TReal64 FLOAT64;
typedef XFcFixed REAL;
typedef INT32 INT;
typedef UINT32 UINT;
typedef char CHAR8;
typedef short CHAR16;
typedef CHAR8 CHAR;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Type definitions: Windows platforms
//////////////////////////////////////////////////////////////////////////

#elif defined(XFC_PLATFORM_WINDOWS)

#if defined(XFC_PLATFORM_WINCE)
#define XFCASSERT(expr) ASSERT(expr)
#elif defined(XFC_PLATFORM_DESKTOPWINDOWS) 
#include <crtdbg.h>
#define XFCASSERT(expr) _ASSERTE(expr)
#else
#define XFCASSERT(expr)
//#include <windows.h>
#endif

// MSVC doesn't like typenames
#define typename


typedef signed char INT8;
typedef signed short INT16;
typedef signed long INT32;
typedef signed __int64 INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;
//typedef unsigned __int64 UINT64;
typedef float FLOAT32;
typedef double FLOAT64;
#if defined(XFC_USE_FLOAT)
    typedef FLOAT32 REAL;
#else
    typedef XFcFixed REAL;
#endif
typedef INT32 INT;
typedef unsigned int UINT;
typedef char CHAR8;
typedef short CHAR16;
typedef CHAR8 CHAR;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Type definitions: Linux platforms
//////////////////////////////////////////////////////////////////////////

#elif defined(XFC_PLATFORM_LINUX)

#include <assert.h>
#define XFCASSERT(expr) assert(expr)

// gcc does not know about __cdecl's
#define __cdecl

typedef signed char INT8;
typedef signed short INT16;
typedef signed long INT32;
typedef signed long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;
//typedef unsigned long long UINT64;
typedef float FLOAT32;
typedef double FLOAT64;
typedef XFcFixed REAL;
typedef INT32 INT;
typedef UINT32 UINT;
typedef char CHAR8;
typedef short CHAR16;
typedef CHAR8 CHAR;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Type definitions: GNUC, MW and ARMCPP defaults
//////////////////////////////////////////////////////////////////////////

#elif defined(XFC_COMPILER_GNUC) || defined(XFC_COMPILER_ADS) || defined(XFC_COMPILER_MW)

#if defined(XFC_COMPILER_MW) && defined(XFC_PLATFORM_PALM)
// Don't define assertions on palm & metrowerks
#define XFCASSERT(expr)
//#define XFCASSERT(expr) do { if (!(expr)) xfcPalmAssertionFailure(__FILE__, __LINE__, "Assertion failed"); } while (0);
//extern "C" void xfcPalmAssertionFailure(const char * filename, int line, const char * errormessage);

// Needed to make new and delete operators to work
#ifndef XFC_MEMMGR_DISABLE
#include <new.h>
#endif

#else
#include <assert.h>
#define XFCASSERT(expr) assert(expr)
#endif

typedef signed char INT8;
typedef signed short INT16;
typedef signed long INT32;
typedef signed long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;
//typedef unsigned long long UINT64;
typedef float FLOAT32;
typedef double FLOAT64;
typedef XFcFixed REAL;
typedef INT32 INT;
typedef UINT32 UINT;
typedef char CHAR8;
typedef short CHAR16;
typedef CHAR8 CHAR;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Type definitions: MSVC defaults
//////////////////////////////////////////////////////////////////////////

#elif defined(XFC_COMPILER_MSVC)

// MSVC doesn't like typenames
#define typename

#define XFCASSERT(expr)

typedef signed char INT8;
typedef signed short INT16;
typedef signed long INT32;
typedef signed __int64 INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;

typedef float FLOAT32;
typedef double FLOAT64;
#if defined(XFC_USE_FLOAT)
    typedef FLOAT32 REAL;
#else
    typedef XFcFixed REAL;
#endif
typedef INT32 INT;
typedef unsigned int UINT;
typedef char CHAR8;
typedef short CHAR16;
typedef CHAR8 CHAR;

// unless we're compiling for palmsim, we can do direct cast
#ifndef XFC_PLATFORM_PALM
#define XFC_CAN_DO_DIRECT_CAST 
#endif
#else
#error Platform misconfiguration
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// NULL is not neccessarily defined.
//////////////////////////////////////////////////////////////////////////

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// DLL export/import handling
// By default, we don't do any dll stuff
//////////////////////////////////////////////////////////////////////////

#define XFCDLLEXPORT
#define XFCEXPORT
#define XFCIMPORT

#if (defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE)) && defined(XFC_MAKEDLL)
#undef XFCDLLEXPORT
#define XFCDLLEXPORT __declspec(dllexport) 
#elif (defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE)) && defined(XFC_USE_DLL)
#undef XFCDLLEXPORT
#define XFCDLLEXPORT __declspec(dllimport) 
#endif

#if (defined(XFC_MAKEDLL) || defined(XFC_USE_DLL)) && defined(XFC_PLATFORM_EPOC)
#undef XFCEXPORT
#undef XFCIMPORT
#define XFCEXPORT EXPORT_C
#define XFCIMPORT IMPORT_C
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Macro to make literal text CHAR string
// (this will handle unicode conversions in the future)
//////////////////////////////////////////////////////////////////////////

//! Converts a literal text string to a CHAR string.
#define XFCSTR(a) (const CHAR *)(a)


#endif // !XFC_CORE_XFCCONFIG_H_INCLUDED

