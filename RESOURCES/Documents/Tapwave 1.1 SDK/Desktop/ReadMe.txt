*********************************************************************
*                   Tapwave CDK - ReadMe File              	    *
*                                                                   *
* IMPORTANT: Read before using the CDK files                	    *
*********************************************************************

These files are meant to replace their corresponding files in
PalmSources' Conduit Developers Kit.  You can download the full
CDK at http://www.palmsource.com/developers.

The following files are included in the Tapwave CDK:

InstAide.h/InstAide.lib
These files are necessary to access the new PlmSlotInstallFileToDir
function.  This function is defined in the Tapwave Programmer's 
Reference.

UserData.h/UserData.lib
This file has no API changes, but does have some internal changes
for Zodiac specific reasons.

SyncManager.h/SyncManager.lib
These files are necessary in order to use the new functionality for 
handling large resources and records in your conduit development.
Eight new functions have been defined for handling large resources 
and records.

Each function definition includes extensive documentation in
front of it's definition.