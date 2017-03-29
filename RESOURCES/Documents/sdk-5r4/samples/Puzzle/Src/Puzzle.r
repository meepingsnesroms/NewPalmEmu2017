/******************************************************************************
 *
 * Copyright (c) 1995-1999 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Puzzle.r
 *
 * Release: 
 *
 * Description:
 *		Resource description for generating Pilot resource database for the
 *		Puzzle application
 *
 * History:
 *   	9/14/95 Created by Vitaly Kruglikov from Ron's template
 *
 *****************************************************************************/

// Include definitions of basic Pilot resources.
#include <BuildDefaults.h>
#include <SysResTypes.rh>


// Include the  main code resource
include "Puzzle.code" 'CODE' 1  as sysResTAppCode 1;

// Include the CODE 0 resource which has the global size information in it
include "Puzzle.code" 'CODE' 0 as sysResTAppCode 0;

// Include the DATA 0 resource which has the initialized global data info
include "Puzzle.code" 'DATA' 0 as sysResTAppGData 0;


// Include the Puzzle UI resources
include "PuzzleApp.rsrc";
include "PuzzleMain.rsrc";
include "PuzzleMisc.rsrc";


// Our PREF resource
resource sysResTAppPrefs 0 {
	30,								// priority
	0x1000,							// stack size
	0x1000							// minHeapSpace
	}
