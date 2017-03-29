/******************************************************************************
 *
 * Copyright (c) 1998-2004 PalmSource, Inc. All rights reserved.
 *
 * File: OmGlue.h
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *		Header file for OmGlue library routines.
 *
 *		Glue providing overlay manager utility routines.
 *
 *****************************************************************************/

#ifndef __OMGLUE_H__
#define __OMGLUE_H__

#include <OverlayMgr.h>

#ifdef __cplusplus
	extern "C" {
#endif

void OmGlueGetCurrentLocale(OmLocaleType *currentLocale);

void OmGlueGetSystemLocale(OmLocaleType *systemLocale);

#ifdef __cplusplus
	}
#endif

#endif	// __OMGLUE_H__
