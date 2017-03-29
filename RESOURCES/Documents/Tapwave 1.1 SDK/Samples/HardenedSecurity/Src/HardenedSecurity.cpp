/*
	File:		HardenedSecurity.cpp

	Description:This is an example of how to use DRM to protect your application.  You 
				shouldn't copy the code here exactly since all apps should implement their
				own scheme slightly differently.
				
				The emphasis in this sample is on code clarity.  You should make your
				solution less obvious.

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
				10/8/2003 - ryw
				Added verification that the TAL owns the security funtion pointers.
				
*/

#include <PalmOS.h>
#include <Tapwave.h>

#include "HardenedSecurityRsc.h"
#include "DRMStaticData.c" 			// all the const static data for the various tests

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
// Set SECURE_BUILD to 1 to enable all app based DRM.  To run in this mode
// the app will have to be signed by the TapWave Developer Server.
#define SECURE_BUILD 	0

#if SECURE_BUILD
#define Error(msg) ErrFatalDisplay(msg)
#else
#define Error(msg) FrmCustomAlert(ErrorAlert, msg, 0, 0)
#endif

const TwSecTableType 			*security; // table of function pointers to security functions

#define kSignedResType 			'tSTR'
#define kSignatureResType 		'mySg'
#define kSignedResBase 			1000
#define kSignedResNumber 		8
#define kNumResTests 			40 

#define kSigSigningType 		'sgSg'
#define kSigSigningId			1000

// Define the minimum OS version we support (5.0 for now).
#define kOurMinVersion			sysMakeROMVersion(5,0,0,sysROMStageRelease,0)
#define kPalmOS10Version		sysMakeROMVersion(1,0,0,sysROMStageRelease,0)

#define FunctionPtrFrom68kStub(stub) SwapPointer(*(((void **)(stub)) + 1))

/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/

/***********************************************************************
 *
 *	THESE FUNCTIONS ARE ALL RELATED TO VALIDATING THE SECURITY OF THE
 *  DEVICE.
 *
 ***********************************************************************/
 
 /***********************************************************************
 *
 * FUNCTION:    HashOfRomKeys
 *
 * DESCRIPTION: Hash all the keys: 
 *				SystemKey + [twSecFixedKeyBase, twSecFixedKeyBase + twSecNumFixedKeys]
 *
 * PARAMETERS:  None
 *
 * RETURNED:    The hash value.
 *
 ***********************************************************************/
static UInt32 HashOfRomKeys()
{
	UInt32 hash = 0;
	TwSecPublicKeyType key;
	
	security->TwSecGetPublicKey(&key, twSecSystemKey);
	hash = SimpleHash(hash, key.data, twSecPublicKeySize);
	for(int i = twSecFixedKeyBase; i < twSecFixedKeyBase + twSecNumFixedKeys; ++i)
	{
		security->TwSecGetPublicKey(&key, i);
		hash = SimpleHash(hash, key.data, twSecPublicKeySize);	
	}
	
	return (hash);
}

 /***********************************************************************
 *
 * FUNCTION:    HashOfAppKey
 *
 * DESCRIPTION: 
 *
 * PARAMETERS:  None
 *
 * RETURNED:    The hash value.
 *
 ***********************************************************************/
static UInt32 HashOfAppKey()
{
	return (SimpleHash(0, gAppPublicKey.data, twSecPublicKeySize));
}

/***********************************************************************
 *
 * FUNCTION:    DrmBehaviorTest
 *
 * DESCRIPTION: Test to make sure the DRM verify is functioning correctly.
 *				Meaning that it verifies valid things and rejects invalid things.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    True if the check succeeded, false otherwise.
 *
 ***********************************************************************/
static Boolean DrmBehaviorTest(void)
{
	MemHandle dataH;
	MemHandle sigH;
	UInt16 resId;
	UInt16 sigId;
	Boolean verified;
	
	// There is an array of resources that have been signed in this app.
	// Iterate over them randomly and require that verification suceed 
	// only when the resource and the signature match.
	SysRandom(TimGetTicks());
	for(int i = 0; i < kNumResTests; ++i)
	{
		resId = kSignedResBase + SysRandom(0) % kSignedResNumber;
		if(SysRandom(0) % 1){
			sigId = kSignedResBase + SysRandom(0) % kSignedResNumber; 
		}
		else{
			sigId = resId;
		}
		dataH = DmGetResource(kSignedResType, resId);
		sigH = DmGetResource(kSignatureResType, sigId);
		if(!dataH || !sigH){
			if(dataH){ DmReleaseResource(dataH); }
			if(sigH){ DmReleaseResource(sigH); }
			return false;
		}

		verified = security->TwSecVerifyMemory((UInt8 *)MemHandleLock(dataH), MemHandleSize(dataH), 
		                                       &gAppPublicKey, (TwSecSignatureType *)MemHandleLock(sigH), 
		                                       0, twSecReturnOnFail);

		MemHandleUnlock(dataH);
		MemHandleUnlock(sigH);
		DmReleaseResource(dataH);
		DmReleaseResource(sigH);

		if((sigId == resId) != verified){
			return false;
		}		
	}
	
	// if this is a secure build then require that the application can be verified,
	// and that the return reason is properly rotated (this property makes it harder to 
	// point the verify routine at some code in ROM that always returns true).
	bool result;
	UInt32 failureReason = SysRandom(0);
	UInt32 rot19 = (failureReason << 19) ^ (failureReason >> (32 - 19));
	result = security->TwSecVerifyCurrentApp(&failureReason, twSecReturnOnFail);
	
	return (result && (failureReason == rot19));
}

/***********************************************************************
 *
 * FUNCTION:    VerifySignatureSigning
 *
 * DESCRIPTION: For this app we sign the application signature (TSIG.2) generated by the TapWave 
 *				server using the private application key (owned by the developer).  The signature
 *				this signature is stored in a resource that is in the skip list (TSIG.0) since it
 *				it can't be part of the signed application.  That's OK because noone else has the
 *				private application key, so we'll also test to make sure the application key hasn't 
 *				been modified.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    True if the check succeeded, false otherwise.
 *
 ***********************************************************************/
static Boolean VerifySignatureSigning()
{
	Boolean verified = false;
	MemHandle sigSigH;
	MemHandle sigH;
	
	if(gAppPublicKey.data[20] != 0x8d)
	{
		return false;
	}
	
	sigH = DmGetResource('TSIG', 2);
	sigSigH = DmGetResource(kSigSigningType, kSigSigningId);
	if(!sigSigH || !sigH){
		if(sigSigH){ DmReleaseResource(sigSigH); }
		if(sigH){ DmReleaseResource(sigH); }
		return false;
	}

	verified = security->TwSecVerifyMemory((UInt8 *)MemHandleLock(sigH), MemHandleSize(sigH), 
		                                       &gAppPublicKey, (TwSecSignatureType *)MemHandleLock(sigSigH), 
		                                       0, twSecReturnOnFail);
		                                       
	MemHandleUnlock(sigH);
	MemHandleUnlock(sigSigH);
	DmReleaseResource(sigH);
	DmReleaseResource(sigSigH);
	
	return (verified);
}

/***********************************************************************
 *
 * FUNCTION:    VerifyOneFunction
 *
 * DESCRIPTION: 
 *
 * PARAMETERS:  ptr - the function pointer to test
 *              sysKey - pointer to the systemKey
 *
 * RETURNED:    returns true if TAL.prc owns the pointer and is verified
 *
 ***********************************************************************/
static bool VerifyOneFunction(void *ptr, const TwSecPublicKeyType *sysKey)
{
	LocalID id;
	
	id = DmFindDatabase(0, "Tapwave Application Layer");
	
	if(id){
		return security->TwSecVerifyPointerOwnership(0, id, sysKey, ptr, 0, twSecReturnOnFail);	
	}
	return false;
}

/***********************************************************************
 *
 * FUNCTION:    SwapU32
 *
 * DESCRIPTION: 
 *
 * PARAMETERS:  value - The data to swap
 *
 * RETURNED:    The swapped data.
 *
 ***********************************************************************/
static UInt32 SwapU32( UInt32 value )
{
	UInt32 result = 0;
	
	result |= value & 0x000000FF;
	result <<= 8;
	value >>= 8;
	result |= value & 0x000000FF;
	result <<= 8;
	value >>= 8;
	result |= value & 0x000000FF;
	result <<= 8;
	value >>= 8;
	result |= value & 0x000000FF;
	
	return (result);
}

/***********************************************************************
 *
 * FUNCTION:    SwapPointer
 *
 * DESCRIPTION: This function changes the endianness of a 32-bit value.
 *
 * PARAMETERS:  p - A pointer to the data to swap
 *
 * RETURNED:    A pointer to the swapped data.
 *
 ***********************************************************************/
static void* SwapPointer(void *p)
{
	return ((void*)SwapU32((UInt32)p));
}

/***********************************************************************
 *
 * FUNCTION:    VerifySecurityFunctionsV1
 *
 * DESCRIPTION: Make sure all the pointers point to code owned by TAL.prc.
 *				Note you can at least reorder these tests to make the code unique.
 *
 * PARAMETERS:  functionsP - a pointer to the security functions table.
 *
 * RETURNED:    true if the verification failed, false otherwise.
 *
 ***********************************************************************/
static Boolean VerifySecurityFunctionsV1(const TwSecTableType* functionsP)
{
	Boolean failed = false;
	TwSecPublicKeyType sysKey;
	
	if(functionsP->version != 1){
		Error("wrong version of fuctions for this test");
		return false;
	}
	
	TwSecGetPublicKey(&sysKey, twSecSystemKey);
	
#if 1
	// 68k version
	// For 68k the security functions pointers are really emulation stubs that have to be decoded to 
	// get the real function address for testing.
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecGetPublicKey), &sysKey);
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecGetHardwareId), &sysKey);
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecVerifyDatabase), &sysKey);
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecVerifyCurrentApp), &sysKey);
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecVerifyMemory), &sysKey);
    failed = failed || !VerifyOneFunction(FunctionPtrFrom68kStub(functionsP->TwSecFailureReset), &sysKey);
#else
	// ARM native version
    failed = failed || !VerifyOneFunction(functionsP->TwSecGetPublicKey, &sysKey);
    failed = failed || !VerifyOneFunction(functionsP->TwSecGetHardwareId, &sysKey);
    failed = failed || !VerifyOneFunction(functionsP->TwSecVerifyDatabase, &sysKey);
    failed = failed || !VerifyOneFunction(functionsP->TwSecVerifyCurrentApp, &sysKey);
    failed = failed || !VerifyOneFunction(functionsP->TwSecVerifyMemory, &sysKey);
    failed = failed || !VerifyOneFunction(functionsP->TwSecFailureReset, &sysKey);	
#endif

	return (!failed);
}

/***********************************************************************
 *
 * FUNCTION:    AppTestSecurity
 *
 * DESCRIPTION: This routine tests various security features and
 *				reports any problems that it encounters.
 *
 * PARAMETERS:  None.
 *
 * RETURNED:    Nothing.
 *
 ***********************************************************************/
static void AppTestSecurity()
{
	security = TwSecGetFunctions(1, 0, 0, 0); // these last 3 arguments are not used
	
	if(!VerifySecurityFunctionsV1(security))
	{
		Error("Security function do not point to ROM.");
	}
	
	if(HashOfRomKeys() != kHashOfRomKeys)
	{
		Error("ROM keys have been modified");
	}
	
	if(HashOfAppKey() != kHashOfAppKey)
	{
		Error("application key has been modified");
	}
	
#if SECURE_BUILD
	if(!DrmBehaviorTest())
	{
		Error("DRM is not responding correctly");
	}
	
	if(!VerifySignatureSigning())
	{
		Error("This signature was not signed by the application key");
	}
#endif
}

/***********************************************************************
 *
 *	THE FUNCTIONS BELOW THIS POINT ARE FORM RELATED FUNCTIONS.
 *
 ***********************************************************************/

/***********************************************************************
 *
 * FUNCTION:    MainFormDisplayHashValues
 *
 * DESCRIPTION: This routine displays the hash of the ROM keys and the
 *				hash of the app key.
 *
 * PARAMETERS:  None.
 *
 * RETURNED:    Nothing.
 *
 ***********************************************************************/
static void MainFormDisplayHashValues()
{
	UInt32 	hash = HashOfRomKeys();
	char 	msg[120];
	
	StrPrintF(msg, "hash of rom keys = %lu", hash);
	WinDrawChars(msg, StrLen(msg), 10, 20);

	StrPrintF(msg, "hash of app key = %lu", HashOfAppKey());
	WinDrawChars(msg, StrLen(msg), 10, 35);
}

/***********************************************************************
 *
 * FUNCTION:    MainFormUseGfx
 *
 * DESCRIPTION: This routine will draw a number of line segments using
 *              TwGfx.
 *
 * PARAMETERS:  None.
 *
 * RETURNED:    Nothing.
 *
 ***********************************************************************/
static void MainFormUseGfx()
{
	TwGfxType *gfx;
	
	// Using the Gfx API requires that the app be signed or that a
	// Dev Access PRC be found on the device.  So running this code
	// will trigger DRM checks.
	if(TwGfxOpen(&gfx, 0) == errNone)
	{	
		TwGfxSurfaceType *display;
		TwGfxGetDisplaySurface( gfx, &display );
	    TwGfxPointType *points = (TwGfxPointType*)MemPtrNew(sizeof(TwGfxPointType) * 160);
	    for(Int32 i = 0; i < 160; i += 2)
	    {
	     	points[i].x = 10;
	     	points[i].y = 95 + i;
	     	points[i+1].x = 310;
	     	points[i+1].y = 95 + i;
	    }
	    
	    TwGfxDrawLineSegments( display, points, 160, TwGfxComponentsToPackedRGB(0, 0, 255) );
	    MemPtrFree( points );
		TwGfxClose( gfx );
	}
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
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	Boolean		handled = false;
	
	switch (eventP->eType)
	{
		case frmOpenEvent:
			FrmDrawForm( FrmGetActiveForm() );
			AppTestSecurity();
			handled = true;
			break;
			
		case ctlSelectEvent:
			if(eventP->data.ctlSelect.controlID == MainGoButton)
				MainFormUseGfx();
			else if(eventP->data.ctlSelect.controlID == MainConfigureButton)
				MainFormDisplayHashValues();
			break;
	}	

	return (handled);
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
static Boolean AppHandleEvent(EventPtr eventP)
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
static void AppEventLoop()
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
UInt32 PilotMain( UInt16 cmd, MemPtr /*cmdPBP*/, UInt16 launchFlags)
{
	Err error;

	error = RomVersionCompatible( kOurMinVersion, launchFlags );
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