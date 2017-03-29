/******************************************************************************
 *
 * Copyright (c) 1995-1999 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Mine.r
 *
 * Release: 
 *
 * Description:
 *		Resource description for generating Touchdown resource database for the
 *		MineHunt application
 *
 * History:
 *   	10/8/95 Created by Vitaly Kruglikov from Ron's template
 *
 *****************************************************************************/

// Include definitions of basic Touchdown resources.
#include <BuildDefaults.h>
#include <SysResTypes.rh>

// Include the  main code resource
include "MineHunt.code" 'CODE' 1  as sysResTAppCode 1;

// Include the CODE 0 resource which has the global size information in it
include "MineHunt.code" 'CODE' 0 as sysResTAppCode 0;

// Include the DATA 0 resource which has the initialized global data info
include "MineHunt.code" 'DATA' 0 as sysResTAppGData 0;


// Include the Puzzle UI resources
include "MineApp.rsrc";
include "MineMain.rsrc";
include "MineMisc.rsrc";
include "MinePref.rsrc";


// Our PREF resource
resource sysResTAppPrefs 0 {
	30,								// priority
	0x1000,							// stack size
	0x1000							// minHeapSpace
	}
