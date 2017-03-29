/*
	File:		SimpleForm.c

	Description:Contains all of the code for SimpleForm.
	
	Author:		

	Copyright:	Copyright © 2003 by Tapwave, Inc.

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
#include "SimpleFormRsc.h"

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
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the 
 *				current form.
 *
 * PARAMETERS:  objectId - The id of the object to use.
 *
 * RETURNED:    Address of the object as a void pointer.
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID)
{
	FormType * frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

/***********************************************************************
 *
 * FUNCTION:    MainFormResize
 *
 * DESCRIPTION: This routine resizes a form and moves the objects
 *				on the form.
 *
 * PARAMETERS:  frmP - A pointer to the form.
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void MainFormResize(FormPtr frmP)
{
	RectangleType 	dispBounds, bounds;
	UInt16 			index;
	Coord 			dX, dY;
	
	// Get/Set the window bounds
	WinGetBounds( WinGetDisplayWindow(), &dispBounds );
	FrmGetFormBounds( frmP, &bounds );
	dX = dispBounds.extent.x - bounds.extent.x;
	dY = dispBounds.extent.y - bounds.extent.y;
	WinSetWindowBounds( FrmGetWindowHandle(frmP), &dispBounds );
	
	// Move the button
	index = FrmGetObjectIndex( frmP, MainFormTextButton );
	FrmGetObjectBounds( frmP, index, &bounds );
	bounds.topLeft.x += dX;
	bounds.topLeft.y += dY;
	FrmSetObjectBounds( frmP, index, &bounds );
}

/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the "MainForm" of this 
 * 				application.
 *
 * PARAMETERS:  eventP - A pointer to the EventType structure.
 *
 * RETURNED:    true if the event was handled and should be passed to
 *				FrmHandleEvent.
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventType * eventP)
{
	Boolean 		handled = false;
	FormType* 		frmP = FrmGetActiveForm();
	UInt32 			flags, pinMgrVersion;
	Err				err = errNone;

	switch (eventP->eType) 
	{
		case frmOpenEvent:
			// Setup the form state
			WinSetConstraintsSize(FrmGetWindowHandle(frmP), 160, 160, 240, 160, 160, 240);
			FrmSetDIAPolicyAttr( frmP, frmDIAPolicyCustom );
			
			// Check to make sure that the device we're running on supports
			// version 1.1 of the Pin Input Manager before making our calls.
			err = FtrGet( pinCreator, pinFtrAPIVersion, &pinMgrVersion );
			if (!err && pinMgrVersion == pinAPIVersion1_1)
			{
				flags = FtrGet( sysFtrCreator, sysFtrNumInputAreaFlags, &flags );
				
				/* Uncomment or comment the lines below based on
				   the behavior that you desire */
                    	  
				/* Hide or show the grafitti area .
				   Use pinInputAreaHide or pinInputAreaShow or pinInputAreaUser */
				if (flags & grfFtrInputAreaFlagCollapsible)
					PINSetInputAreaState(pinInputAreaUser);
				
				/* Hide or show the status area */
				if (flags & grfFtrInputAreaFlagCollapsible)
					StatShow();
				
				/* Enable or disable the grafitti trigger.
				   User pinInputTriggerDisabled or pinInputTriggerEnabled  */
				if (flags & grfFtrInputAreaFlagCollapsible)
					PINSetInputTriggerState(pinInputTriggerEnabled);
				
				/* Enable or disable the screen orientation trigger.
				   Use sysOrientationTriggerDisabled or sysOrientationTriggerEnabled  */
				SysSetOrientationTriggerState(sysOrientationTriggerEnabled);
					
				/* Set the screen orientation.  The default is landscape.
				   Use sysOrientationLandscape, sysOrientationPortrait, or sysOrientationUser.
				   Be sure to check the flags to ensure that the orientation you want is
				   supported -- portrait mode is assumed. */
				SysSetOrientation(sysOrientationUser);
			}		
			
			// Resize the form and it's objects
			MainFormResize( frmP );

			// Finally, draw the form.
			FrmDrawForm(frmP);
			
			handled = true;
			break;
			
        case winDisplayChangedEvent:
        	// First make sure the active form is our form. Then resize the
        	// form and objects on the form.
        	if (FrmGetActiveFormID() == MainForm)
        	{
				MainFormResize( frmP );
				if (FrmVisible(frmP)) FrmDrawForm(frmP);
			}
			
		case winEnterEvent:
			// Note that the grafitti, status, screen orientation, and trigger
			// states may not be what you expect when your form first receives 
			// this event.  Return false to have the OS set-up the correct 
			// environment for your  application, otherwise you'll need to set 
			// the state yourself.
			handled = false;
			break;
	}
    
	return handled;
}

/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and set the event
 * 				handler for the form loaded.
 *
 * PARAMETERS:  eventP - A pointer to the EventType structure.
 *
 * RETURNED:    true if the event was handled and should not be passed
 *				to a higher level handler.
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventType* eventP)
{
	UInt16 formId;
	FormType * frmP;

	if (eventP->eType == frmLoadEvent)
	{
		/* Load the form resource. */
		formId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(formId);
		FrmSetActiveForm(frmP);

		/* 
		 * Set the event handler for the form.  The handler of the
		 * currently active form is called by FrmHandleEvent each
		 * time is receives an event. 
		 */
		switch (formId)
		{
			case MainForm:
				FrmSetEventHandler( frmP, MainFormHandleEvent );
				break;
		}
		return true;
	}

	return false;
}

/***********************************************************************
 *
 * FUNCTION:    AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;

	do 
	{
		/* change timeout if you need periodic nilEvents */
		EvtGetEvent(&event, evtWaitForever);

		if (! SysHandleEvent(&event))
		{
			if (! MenuHandleEvent(0, &event, &error))
			{
				if (! AppHandleEvent(&event))
				{
					FrmDispatchEvent(&event);
				}
			}
		}
	} while (event.eType != appStopEvent);
}

/***********************************************************************
 *
 * FUNCTION:    AppStart
 *
 * DESCRIPTION: Initialize the application.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static Err AppStart(void)
{
	return errNone;
}

/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Cleanup the application.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AppStop(void)
{
	// Close all the open forms.
	FrmCloseAllForms();

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
	Err error;

	error = RomVersionCompatible (kOurMinVersion, launchFlags);
	if (error) return (error);

	switch (cmd)
	{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error) 
				return error;

			/* 
			 * start application by opening the main form
			 * and then entering the main event loop 
			 */
			FrmGotoForm( MainForm );
			AppEventLoop();

			AppStop();
			break;
	}

	return errNone;
}
