/*
	File:			Application.cpp	

	Description:	Contains the 68K portion of the Palm ARMlet.  It sets up a form so that
					the UI works with the Palm UI, and it calls the ARMlet.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

#include <TapWave.h>
#include <TwRuntime.h>

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/

#define RomIncompatibleAlert 1000

/***********************************************************************
 *
 * FUNCTION:    RomVersionCompatible
 *
 * DESCRIPTION: This routine checks that a ROM version is meet your
 *              minimum requirement.
 *
 * PARAMETERS:  requiredVersion - minimum rom version required
 *                                (see sysFtrNumROMVersion in SystemMgr.h 
 *                                for format)
 *              launchFlags     - flags that indicate if the application 
 *                                UI is initialized.
 *
 * RETURNED:    error code or zero if rom is compatible
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err RomVersionCompatible(UInt16 launchFlags)
{
	UInt32 romVersion;

    // Check Tapwave Native Application glue.
    if (errNone == FtrGet(twFtrCreator, twFtrAPIGlue, &romVersion)) {
        return errNone;
    }

    // Show dialog if we can.
    if ((launchFlags & sysAppLaunchFlagNewGlobals) && (launchFlags & sysAppLaunchFlagUIApp)) {
        FrmAlert(RomIncompatibleAlert);
    }

    // Palm OS 1.0 will continuously relaunch this app unless we
    // switch to another safe one.
    FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
    if (romVersion <= sysMakeROMVersion(1,0,0,sysROMStageRelease,0)) {
        AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
    }

    return sysErrRomIncompatible;
}

/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt32 res = errNone;
    NativeFuncType* entry;
	
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		if (!RomVersionCompatible(launchFlags)) {
            res = TwLoadModule(0, 0, 0, 1, twLoadFlagTNA|twLoadFlagQuickRun, &entry);
        }
	}
	
	return res;
}
