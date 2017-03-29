/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: pnolet-simple.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *    This is an example of a most trivial pnomlet; it simply returns the
 *    same pointer it receives.
 *
 *    PACE byte-swaps userData68KP (but not what it points to!) so it's ready
 *    to be dereferenced.  PACE also byte-swaps the 4-byte return value, so the
 *    calling function receives back the same pointer it passed in.
 *
 *    The pnolet entry point needs to be the first function in the file.
 *
 *****************************************************************************/


#define __OS5DBG__

#include <AdnDebugMgr.h>
#include <ByteOrderutils.h>
#include "example_data_type.h"
#include <ByteOrderUtils.h>

#include "PceNativeCall.h"
#ifdef WIN32
	#include "SimNative.h"
#endif

unsigned long PNOMain(const void *, void *, Call68KFuncType *);


unsigned long PNOMain(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
	AdnDebugEnableSet(kAdnEnableMasterSwitch | kAdnEnableDebugIndicator | kAdnEnableFullDebugging | kAdnEnableShowSafeFatalAlerts);
	AdnDebugNativeRegister('appl', 'apno', 'ARMC', 0x1000);
	AdnDebugBreak();
	return (unsigned long)userData68KP;
}


