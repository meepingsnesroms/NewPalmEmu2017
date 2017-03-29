/******************************************************************************
 *
 * Copyright (c) 1999-2002 PalmSource, Inc. All rights reserved.
 *
 * File: PalmOptErrorCheckLevel.Release
 *
 * Release: Palm OS 5 SDK (68K) R2.
 *
 *****************************************************************************/

#ifndef __PALMOPTERRORCHECKLEVEL_H__
#define __PALMOPTERRORCHECKLEVEL_H__

#include <BuildDefines.h>

	#ifdef ERROR_CHECK_LEVEL_OK_TO_REDEFINE
		#undef ERROR_CHECK_LEVEL_OK_TO_REDEFINE
		#undef ERROR_CHECK_LEVEL
	#endif

	#ifndef ERROR_CHECK_LEVEL
		#define ERROR_CHECK_LEVEL ERROR_CHECK_PARTIAL
	#endif

#endif
