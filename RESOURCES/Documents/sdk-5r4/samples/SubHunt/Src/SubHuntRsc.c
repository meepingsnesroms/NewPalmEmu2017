/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: SubHuntRsc.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *	  The list of resources are stored here.
 *
 *****************************************************************************/

#include <BuildDefaults.h>

// RESOURCE_FILE_PREFIX is now defined in :Incs:BuildDefaults.h based on LANGUAGE.
 
const char *AppResourceList[] = {
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntMain.rsrc", 
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntMisc.rsrc", 
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntNewHighScore.rsrc", 
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntHighScores.rsrc", 
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntPrefs.rsrc", 
	"::Rsc:"RESOURCE_FILE_PREFIX"SubHuntInfo.rsrc", 
	""
	};
