/******************************************************************************
 *
 * Copyright (c) 1995-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: ToDo.r
 *
 * Release: 
 *
 * Description:
 *		Resource description for generating Touchdown resource database
 *
 * History:
 *   	2/3/95 Created by Ron Marianetti
 *		1/4/99 ADH	Separate databases for Eleven and non Eleven devices.
 *
 *****************************************************************************/

// Include definitions of basic Touchdown resources.
#include <BuildDefaults.h>
#include <SysResTypes.rh>

// Include the  main code resource
include "ToDo.code" 'CODE' 1  as sysResTAppCode 1;

// Include the CODE 0 resource which has the global size information in it
include "ToDo.code" 'CODE' 0 as sysResTAppCode 0;

// Include the DATA 0 resource which has the initialized global data info
include "ToDo.code" 'DATA' 0 as sysResTAppGData 0;

// Include the default database.  Currenly there are separate databases for Eleven and
// standard devices.  Standard devices also have the option of using a demo database

// DOLATER: ToDoDBEleven has ONLY one default item: "Check www.palm.net for more PQAs"
// ToDoDB has more up-to-date Palm data.  ToDoDBEleven should be updated, and perhaps
// a new Eleven-specific target should be generated, called ToDoEleven.prc for Eleven ROMs...
// NOTE:  USER_MODE_DEMO should be obsolete; demo data should come from a demo overlay.

#if DEFAULT_DATA == USE_DEFAULT_DATA
//#if MODEL == MODEL_ELEVEN
//read "ToDoDBEleven.pdb" as sysResTDefaultDB sysResIDDefaultDB;
//#else
read "ToDoDB.pdb" as sysResTDefaultDB sysResIDDefaultDB;
//#endif
#endif

// Include the ToDO UI resources
include "ToDoList.rsrc";
include "ToDoDelete.rsrc";
include "ToDoDeleteComplete.rsrc";
include "ToDoDetails.rsrc";
include "ToDoOptions.rsrc";
include "ToDoMisc.rsrc";


// Our PREF resource
resource sysResTAppPrefs 0 {
	30,								// priority
	0x1000,							// stack size
	0x1000							// minHeapSpace
	}
