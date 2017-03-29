/******************************************************************************
 *
 * Copyright (c) 1995-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Memo.r
 *
 * Release: 
 *
 * Description:
 *		Resource description for generating Touchdown resource database
 *
 * History:
 *   	2/3/95 Created by Ron Marianetti
 *		1/4/99 ADH	Eleven has a different default database then the 
 *		standard main line sources.
 *
 *****************************************************************************/

// Include definitions of basic Touchdown resources.
#include <BuildDefaults.h>
#include <SysResTypes.rh>

// Include the  main code resource
include "Memo.code" 'CODE' 1  as sysResTAppCode 1;

// Include the CODE 0 resource which has the global size information in it
include "Memo.code" 'CODE' 0 as sysResTAppCode 0;

// Include the DATA 0 resource which has the initialized global data info
include "Memo.code" 'DATA' 0 as sysResTAppGData 0;

// Include the default database.  Currenly there are separate databases for Eleven and
// standard devices.  Standard devices also have the option of using a demo database

// DOLATER: MemoDBEleven has only Eleven-specific data, but older versions of other demo data.
// MemoDB has more up-to-date Palm data.  MemoDBEleven should be updated, and perhaps
// a new Eleven-specific target should be generated, called MemoEleven.prc for Eleven ROMs...
// NOTE:  USER_MODE_DEMO should be obsolete, demo data should come from a demo overlay.

#if DEFAULT_DATA == USE_DEFAULT_DATA
//#if MODEL == MODEL_ELEVEN
//read "MemoDBEleven.pdb" as sysResTDefaultDB sysResIDDefaultDB;
//#else
read "MemoDB.pdb" as sysResTDefaultDB sysResIDDefaultDB;
//#endif
#endif

// Include the Calculator UI resources
include "MemoDetails.rsrc";
include "MemoEdit.rsrc";
include "MemoList.rsrc";
include "MemoMisc.rsrc";
include "MemoPrefer.rsrc";
include "MemoDelete.rsrc";
include "MemoApp.rsrc";

// Our PREF resource
resource sysResTAppPrefs 0 {
	30,								// priority
	0x1000,							// stack size
	0x1000							// minHeapSpace
	}
