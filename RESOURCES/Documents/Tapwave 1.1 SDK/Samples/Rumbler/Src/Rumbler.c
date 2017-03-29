/*
 * Midi.c
 *
 * main file for Midi
 *
 * This wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *
 * Copyright (c) 1999-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 */
 
#include <Tapwave.h>

#include "Rumbler.h"
#include "Rumbler_Rsc.h"

/*********************************************************************
 * Entry Points
 *********************************************************************/

/*********************************************************************
 * Global variables
 *********************************************************************/

TwDeviceHandle 	gRumblerH = NULL;

/*********************************************************************
 * Internal Constants
 *********************************************************************/

/* Define the minimum OS version we support */
#define ourMinVersion    sysMakeROMVersion(5,2,0,sysROMStageDevelopment,0)
#define kPalmOS20Version sysMakeROMVersion(2,0,0,sysROMStageDevelopment,0)

/*********************************************************************
 * Internal Functions
 *********************************************************************/

/*
 * FUNCTION: GetObjectPtr
 *
 * DESCRIPTION:
 *
 * This routine returns a pointer to an object in the current form.
 *
 * PARAMETERS:
 *
 * formId
 *     id of the form to display
 *
 * RETURNED:
 *     address of object as a void pointer
 */

static void * GetObjectPtr(UInt16 objectID)
{
	FormType * frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

static UInt8* GetEffectArray()
{
	FieldPtr 	fieldP = GetObjectPtr( MainPatternField );
	Char* 		textP = FldGetTextPtr( fieldP );
	Char* 		temp;
	Char*		temp2;
	UInt8* 		result = MemPtrNew( sizeof(UInt8)*1024 );
	UInt32		count = 0;
	Char*		textCopyP = MemPtrNew( MemPtrSize( textP ) );
	
	MemMove( textCopyP, textP, MemPtrSize(textP));
	temp2 = textCopyP;
	
	if (textP)
	{
		temp = textCopyP;
		while (*textCopyP++)
		{
			if (*textCopyP == '.')
			{
				*textCopyP++ = NULL;
				result[count++] = StrAToI( temp );
				temp = &(*textCopyP); 
			}
		}
		
		MemPtrResize( result, sizeof(UInt8)*count );
	}
	
	MemPtrFree( temp2 );
	return (result);
}

static void PutEffectArray( UInt8 patternId )
{
	static UInt8 EffectExplosion[] =
	{
		255,25,0,5,255,5,0,5,255,5
	};
	
	static UInt8 EffectEarthquake[] =
	{
		255,20,0,5,255,7,0,4,255,10,0,4,255,7,0,5,255,7,0,5,255,7,0,5,255,10,0,4,255,15,0,50,255,7,0,5,255,10,0,4
	};
	
	static UInt8 EffectCrash[] =
	{
		255,20,0,5,255,10
	};
	
	static UInt8 EffectOffroad[] =
	{
		255,5,0,5,255,10,0,10,255,5,0,20,255,20,0,10,255,10,0,10,255,5,0,7,255,10,0,10,255,5,0,5,255,15,0,10,255,10,0,20,255,20,0,5,255,5,0,5
	};

	static UInt8 EffectRocket[] =
	{
		255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,3,255,3,0,4,255,4,0,4,255,4,0,4,255,4,0,4,255,4,0,4,255,4,0,4,255,4,0,4,255,4,0,4,255,100
	};
	
	
	UInt8*		effect;
	UInt16		i;
	FieldPtr 	fieldP = GetObjectPtr( MainPatternField );
	Char*		textP = MemPtrNew( sizeof(Char)*1024 );
	Char		temp[10];
	UInt8		size;
	
	MemSet( textP, sizeof(Char)*1024, 0 );
	
	switch (patternId)
	{
		case 0:
			effect = EffectExplosion;
			size = sizeof(EffectExplosion);
			break;
			
		case 1:
			effect = EffectEarthquake;
			size = sizeof(EffectEarthquake);
			break;
			
		case 2:
			effect = EffectCrash;
			size = sizeof(EffectCrash);
			break;
			
		case 3:
			effect = EffectOffroad;
			size = sizeof(EffectOffroad);
			break;
			
		case 4:
			effect = EffectRocket;
			size = sizeof(EffectRocket);
			break;
	}

	for (i=0; i<size; i++)
	{
		StrCat( textP, StrIToA(temp, effect[i]) );
		StrCat( textP, "." );
	}
	
	FldDelete( fieldP, 0, 0xFFFF );					
	FldDrawField( fieldP );
	FldInsert( fieldP, textP, StrLen(textP) );
	MemPtrFree( textP );
}


/*
 * FUNCTION: DoVibrate
 *
 * DESCRIPTION: This routine either turns on or off the vibrator.
 *
 * PARAMETERS:
 *
 * on
 *     A boolean indicating whether to turn on or off the vibrator
 */

static void DoVibrate(UInt16 commandId)
{
	switch (commandId)
	{
		case 0:
			TwDeviceControl(gRumblerH, 'stop', NULL, NULL);
			break;
			
		case 1:
			TwDeviceControl(gRumblerH, 'strt', NULL, NULL);
			break;
			
		case 2:
			TwDeviceControl(gRumblerH, 'slow', NULL, NULL);
			break;
			
		case 3:
			TwDeviceControl(gRumblerH, 'medi', NULL, NULL);
			break;
			
		case 4:
			TwDeviceControl(gRumblerH, 'fast', NULL, NULL);
			break;
	}
}

/*
 * FUNCTION: PlayVibrate
 *
 * DESCRIPTION: This routine plays a pre-set vibrate pattern.
 *
 * PARAMETERS:
 *
 * on
 *     The pattern id
 */
static void PlayVibrate(UInt16 patternId)
{
	// This is test code for now.
	UInt8*	effect = GetEffectArray();
    MemPtrFree(effect);

	// Replace once we have the final stuff
	switch (patternId)
	{
		case 0:
			TwDeviceControl(gRumblerH, 'play', 
       						effect, 
       						MemPtrSize(effect));
			break;
			
		case 1:
			TwDeviceControl(gRumblerH, 'play', 
       						effect, 
       						MemPtrSize(effect));
			break;
			
		case 2:
			TwDeviceControl(gRumblerH, 'play', 
       						effect, 
       						MemPtrSize(effect));
			break;
			
		case 3:
			TwDeviceControl(gRumblerH, 'rept', 
       						effect, 
       						MemPtrSize(effect));
			break;
			
		case 4:
			TwDeviceControl(gRumblerH, 'play', 
       						effect, 
       						MemPtrSize(effect));
			break;
	}
	
}

/*
 * FUNCTION: MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:
 *
 * frm
 *     pointer to the MainForm form.
 */

static void MainFormInit(FormType *frmP)
{
	// DEBUG CODE, REMOVE LATER!!!
	PutEffectArray( 0 );
}

/*
 * FUNCTION: MainFormHandleEvent
 *
 * DESCRIPTION:
 *
 * This routine is the event handler for the "MainForm" of this 
 * application.
 *
 * PARAMETERS:
 *
 * eventP
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed to
 *     FrmHandleEvent
 */

static Boolean MainFormHandleEvent(EventType * eventP)
{
	Boolean 		handled = false;
	FormType* 		frmP;
	ListPtr			listP;

	switch (eventP->eType) 
	{
		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			FrmDrawForm(frmP);
			MainFormInit(frmP);
			handled = true;
			break;
            
		case ctlSelectEvent:
		{
			if (eventP->data.ctlSelect.controlID == MainDoItTextButton)
			{
				listP = GetObjectPtr( MainCommandList );
				DoVibrate( LstGetSelection(listP) );
				break;
			}
			
			if (eventP->data.ctlSelect.controlID == MainPlayTextButton)
			{
				listP = GetObjectPtr( MainPatternList );
				PlayVibrate( LstGetSelection(listP) );
				break;
			}

			break;
		}
		
		case popSelectEvent:
		{	
			if (eventP->data.popSelect.controlID == MainPatternTrigger)
				PutEffectArray( eventP->data.popSelect.selection );
		}
	}
    
	return handled;
}

/*
 * FUNCTION: AppHandleEvent
 *
 * DESCRIPTION: 
 *
 * This routine loads form resources and set the event handler for
 * the form loaded.
 *
 * PARAMETERS:
 *
 * event
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed
 *     to a higher level handler.
 */

static Boolean AppHandleEvent(EventType * eventP)
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
				FrmSetEventHandler(frmP, MainFormHandleEvent);
				break;

		}
		return true;
	}

	return false;
}

/*
 * FUNCTION: AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.
 */

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

/*
 * FUNCTION: AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * RETURNED:
 *     errNone - if nothing went wrong
 */

static Err AppStart(void)
{
	// Open the rumbler
	TwDeviceOpen(&gRumblerH, "vibrator0", "w");
	
	return errNone;
}

/*
 * FUNCTION: AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 */

static void AppStop(void)
{
	// Close the rumbler and null out the handle
    TwDeviceClose(gRumblerH);
    gRumblerH = NULL;
    
	/* Close all the open forms. */
	FrmCloseAllForms();

}

/*
 * FUNCTION: RomVersionCompatible
 *
 * DESCRIPTION: 
 *
 * This routine checks that a ROM version is meet your minimum 
 * requirement.
 *
 * PARAMETERS:
 *
 * requiredVersion
 *     minimum rom version required
 *     (see sysFtrNumROMVersion in SystemMgr.h for format)
 *
 * launchFlags
 *     flags that indicate if the application UI is initialized
 *     These flags are one of the parameters to your app's PilotMain
 *
 * RETURNED:
 *     error code or zero if ROM version is compatible
 */

static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	/* See if we're on in minimum required version of the ROM or later. */
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
	{
		if ((launchFlags & 
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
		{
			FrmAlert (RomIncompatibleAlert);

			/* Palm OS versions before 2.0 will continuously relaunch this
			 * app unless we switch to another safe one. */
			if (romVersion < kPalmOS20Version)
			{
				AppLaunchWithCommand(
					sysFileCDefaultApp, 
					sysAppLaunchCmdNormalLaunch, NULL);
			}
		}

		return sysErrRomIncompatible;
	}

	return errNone;
}

/*
 * FUNCTION: PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 * 
 * PARAMETERS:
 *
 * cmd
 *     word value specifying the launch code. 
 *
 * cmdPB
 *     pointer to a structure that is associated with the launch code
 *
 * launchFlags
 *     word value providing extra information about the launch.
 *
 * RETURNED:
 *     Result of launch, errNone if all went OK
 */

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	Err error;

	error = RomVersionCompatible (ourMinVersion, launchFlags);
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
			FrmGotoForm(MainForm);
			AppEventLoop();

			AppStop();
			break;
	}

	return errNone;
}
