/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: SimNative.h
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *    The following ifdef block is the standard way of creating macros which make exporting 
 *    from a DLL simpler. All files within this DLL are compiled with the SIMPLE_EXPORTS
 *    symbol defined on the command line. this symbol should not be defined on any project
 *    that uses this DLL. This way any other project whose source files include this file see 
 *    SIMPLE_API functions as being imported from a DLL, wheras this DLL sees symbols
 *    defined with this macro as being exported.
 *
 *****************************************************************************/

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#ifdef SIMPLE_EXPORTS
#define SIMPLE_API __declspec(dllexport)
#else
#define SIMPLE_API __declspec(dllimport)
#endif

#include "PceNativeCall.h"

#ifdef __cplusplus
extern "C"{
#endif 

	SIMPLE_API unsigned long PNOMain(const void* emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP);

#ifdef __cplusplus
}
#endif 
