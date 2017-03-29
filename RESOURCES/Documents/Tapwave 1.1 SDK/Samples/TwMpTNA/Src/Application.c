/*
	File:		Application.c

	Description:Contains the 68K portion of the Tapwave ARMlet.  This code simply calls into
				the ARMlet.

	Author:		

	Copyright:	Copyright © 2004 by Tapwave, Inc.

	Disclaimer:	IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
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
#include "TwMpARMRsc.h"

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/

// Define the minimum OS version we support (5.0 for now).
#define kOurMinVersion		sysMakeROMVersion(5,0,0,sysROMStageRelease,0)
#define kPalmOS10Version	sysMakeROMVersion(1,0,0,sysROMStageRelease,0)


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/


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
 ***********************************************************************/
static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;
	UInt32 manufacturer;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	FtrGet(sysFileCSystem, sysFtrNumOEMCompanyID, &manufacturer);
	
	// Display an alert if the version number doesn't match, or if we aren't
	// running on Tapwave hardware.
	if (romVersion < requiredVersion || manufacturer != twCreatorID)
	{
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
		{
			FrmAlert( RomIncompatibleAlert );
		
			// Palm OS 1.0 will continuously relaunch this app unless we switch to 
			// another safe one.
			if (romVersion <= kPalmOS10Version)
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
		}
		
		return (sysErrRomIncompatible);
	}	

	return (errNone);
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
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt32 res = errNone;
    NativeFuncType* entry;
	
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		if (!RomVersionCompatible(kOurMinVersion, launchFlags)) {
            res = TwLoadModule(0, 0, 0, 1, twLoadFlagTNA|twLoadFlagQuickRun, &entry);
        }
	}
	else if (cmd == twMpAppLaunchCmdAskUser)
	{
	    // The invitation dialog has to be replaced in the 68K portion 
	    // of the TNA application, because the launch codes are only
	    // sent to the 68K entry point of the Tapwave Native Application.  
	
        // A TwMpAskUserParamType structure is passed in the parameter
        // block
        TwMpAskUserParamType* askParamP = (TwMpAskUserParamType*) cmdPBP;
        UInt16 buttonID;
            
        // Display simple invitation getting host name form parameter block.
        // This is just a simple example replacement dialog.  Sometthing more 
        // elaborate is recommended to give your game invitation the look and
        // feel of your game.  
        buttonID = FrmCustomAlert(TwMpInvitationAlert, (const Char*) (askParamP->hostName.name), 0, 0);
            
        if(buttonID == 0 /* Yes */)
        {
            // Tell the system that we accept the game invite
            res = twMpResultAccept;
        }
        else
        {
            // Tell the system we decline the game invite
            res = twMpResultDecline;            
        }
	}
	
	return res;
}