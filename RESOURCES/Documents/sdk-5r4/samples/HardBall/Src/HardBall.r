/******************************************************************************
 *
 * Copyright (c) 1996-1999 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: HardBall.r
 *
 * Release: 
 *
 * Description:
 *		Resource description for generating Pilot resource database
 *
 * History:
 *   	1/29/96 Created by Roger Flores
 *
 *****************************************************************************/

// Include definitions of basic Pilot resources.
#include <BuildDefaults.h>
#include <SysResTypes.rh>

// Include the  main code resource
include "HardBall.code" 'CODE' 1 as sysResTAppCode 1;

// Include the CODE 0 resource which has the global size information in it
include "HardBall.code" 'CODE' 0 as sysResTAppCode 0;

// Include the DATA 0 resource which has the initialized global data info
include "HardBall.code" 'DATA' 0 as sysResTAppGData 0;


// Include the HardBall UI resources
include "HardBallBoard.rsrc";
include "HardBallMisc.rsrc";
include "HardBallHighScores.rsrc";
include "HardBallNewHighScore.rsrc";
include "HardBallPrefs.rsrc";


// Our PREF resource
resource sysResTAppPrefs 0 {
	30,								// priority
	0x1000,							// stack size
	0x1000							// minHeapSpace
	}
