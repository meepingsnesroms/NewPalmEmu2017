/*
	File:		GameStarter.c

	Description:Contains the ARM portion of the Tapwave Native Application.  This code contains 
				the event loop and game engine.

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

#include "GameStarter.h"
#include "GameStarterRsc.h"

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/

#define kGameAppCreator					'STRT'
#define kGamePrefVersionNumber			1
#define kGamePrefId						0x00

/***********************************************************************
 *
 *	Internal Globals
 *
 ***********************************************************************/

Int16				gCurrentLevel;
Int32				gScreenWidth;
Int32				gScreenHeight;
TwGfxType*			gGfx = NULL;
TwGfxSurfaceType*	gSurface = NULL;

/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/
 
// This is the structure of the preferences/game state data.
typedef struct 
{
	Int16			level;
	Int16			reserved;
} GamePreferenceType;

/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/ 
 

#ifndef USE_BACKING_STORE
/***********************************************************************
 *
 * FUNCTION:    GameRefreshBitmap
 *
 * DESCRIPTION: Refresh the surface by loading the bitmap back into it.
 *
 * PARAMETERS:  resId - The id of the bitmap to load.
 *				surface - A pointer to the surface to refresh.
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void GameRefreshBitmap( Int16 resId, TwGfxSurfaceType* surface )
{
	TwGfxPointType 			dp = {0, 0};
	
#ifdef __PALMOS_ARMLET__
    MemHandle resH = DmGetResource('Tbmp', resId );
#else
    MemHandle resH = DmGetResource('abmp', resId );
#endif
	if (resH != NULL) 
    {
        BitmapType* resBmp = (BitmapType*)MemHandleLock(resH);
        if (resBmp)
        {          
        	// Load the bitmap into the surface. 
            TwGfxDrawPalmBitmap( surface, &dp, resBmp );
            MemHandleUnlock(resH);
        }
        
        DmReleaseResource( resH );
	}

}

/***********************************************************************
 *
 * FUNCTION:    GameWakeupHandler
 *
 * DESCRIPTION: Handles the wakeup notification from the OS.
 *
 * PARAMETERS:  resId - The id of the bitmap to load.
 *				surface - A pointer to the surface to refresh.
 *
 * RETURNED:    Any errors that occurred handling the notification
 *
 ***********************************************************************/
SYSTEM_CALLBACK Err GameWakeupHandler(SysNotifyParamType *notifyParamsP)
{
	// Refresh the surface
	GameRefreshBitmap( GameBitmapFamily, gSurface );
	return (errNone);
}
#endif

/***********************************************************************
 *
 * FUNCTION:    GameLoadBitmap
 *
 * DESCRIPTION: Load a bitmap into a newly allocated surface.
 *
 * PARAMETERS:  resId - The id of the bitmap to load.
 *				gfx - A pointer to the gfx world.
 *
 * RETURNED:    The allocated surface
 *
 ***********************************************************************/
static TwGfxSurfaceType* GameLoadBitmap( Int16 resId, TwGfxType* gfx ) 
{
    TwGfxSurfaceType* 		surf = NULL;
    TwGfxSurfaceInfoType 	surfInfo;
    TwGfxPointType 			dp = {0, 0};
    Err						error = errNone;
	
#ifdef __PALMOS_ARMLET__
    MemHandle resH = DmGetResource('Tbmp', resId );
#else
    MemHandle resH = DmGetResource('abmp', resId );
#endif
    if (resH != NULL) 
    {
        BitmapType* resBmp = (BitmapType*)MemHandleLock(resH);
        if (resBmp)
        {
            UInt16 prevcs = WinSetCoordinateSystem(kCoordinatesNative);

            // Get information about bitmap
            Coord w, h;
            WinGetBitmapDimensions(resBmp, &w, &h);

            // Allocate a surface to hold the image
            surfInfo.size = sizeof(surfInfo);
            surfInfo.width = w;
            surfInfo.height = h;
#ifdef USE_BACKING_STORE
            surfInfo.location = twGfxLocationAcceleratorMemory;
#else
			surfInfo.location = twGfxLocationAcceleratorMemoryNoBackingStore;
#endif
            surfInfo.pixelFormat = twGfxPixelFormatRGB565;
            error = TwGfxAllocSurface( gfx, &surf, &surfInfo );

            // Load the bitmap into the surface.
            error = TwGfxDrawPalmBitmap( surf, &dp, resBmp );
            MemHandleUnlock(resH);

            WinSetCoordinateSystem(prevcs);
        }
        
        DmReleaseResource( resH );
	}

    return surf;
}

/***********************************************************************
 *
 * FUNCTION:    GameHandleEvent
 *
 * DESCRIPTION: This is the main game event handler.
 *
 * PARAMETERS:  eventP - A pointer to the event structure.
 *
 * RETURNED:    True if handled, false otherwise
 *
 ***********************************************************************/
SYSTEM_CALLBACK Boolean GameHandleEvent(EventType* eventP)
{
	Boolean						handled = false;
	RectangleType 				bounds;
	TwGfxPointType 				destLocation = {0, 0};
	TwGfxRectType      			sourceRect = {0, 0, 0, 0};
	TwGfxSurfaceType* 			displaySurface = NULL;
	TwGfxSurfaceInfoType		surfaceInfo;
	
	switch (eventP->eType)
	{
		case winDisplayChangedEvent:
			// Resize the active window so that it matches the display window.
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinSetBounds( WinGetActiveWindow(), &bounds );
			
			handled = true;
			break;

		case nilEvent:
		case frmUpdateEvent:
			// In a real application you would check the result
			// of each of these functions.
			surfaceInfo.size = sizeof(TwGfxSurfaceInfoType);
			TwGfxGetSurfaceInfo( gSurface, &surfaceInfo );
			sourceRect.h = surfaceInfo.height;
			sourceRect.w = surfaceInfo.width;
			
			TwGfxGetPalmDisplaySurface( gGfx, &displaySurface );
			TwGfxWaitForVBlank( gGfx );
			TwGfxBitBlt( displaySurface, &destLocation, gSurface, &sourceRect );
			
			handled = true;
			break;
	}

	return (handled);
}

/***********************************************************************
 *
 * FUNCTION:    AppStart
 *
 * DESCRIPTION: Application initialization routine
 *
 * PARAMETERS:  None
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AppStart()
{
	GamePreferenceType	prefs;
	UInt16 				prefsSize;
	Int16 				prefsVersion;
	MemHandle			dbH = NULL;
	Err 				err = errNone;
	TwGfxInfoType 		screenInfo;
	
	//////////////////////////
	//  DISPLAY INIT
	//////////////////////////
	
	// Get the screen to a state we want:  landscape with the status area
	// and input area closed.
	PINSetInputAreaState(pinInputAreaHide);
	StatHide();
	SysSetOrientation(sysOrientationLandscape);
	
	//////////////////////////
	//  PREFS INIT
	//////////////////////////
	
	// Load our preferences
	prefsSize = sizeof(GamePreferenceType);
	prefsVersion = PrefGetAppPreferences( kGameAppCreator, kGamePrefId, &prefs, &prefsSize, true );
	
	// Make sure the preferences don't exceed what we know how to handle
	// If they do, then treat it as if there are no prefs.
	if (prefsVersion > kGamePrefVersionNumber)
		prefsVersion = noPreferenceFound;
		
	// If the preferences exist then load up our globals,
	// otherwise load some default values.
	if (prefsVersion > noPreferenceFound)
		gCurrentLevel = prefs.level;
	else
		gCurrentLevel = 0;

#ifndef USE_BACKING_STORE	
	//////////////////////////
	//  NOTIFICATIONS INIT
	//////////////////////////
	
	// Register for the early wakeup notification so we can reload our surfaces.
	err = SysCurAppDatabase( &dbH );
	ErrNonFatalDisplayIf( err != errNone, "can't get app db info" );
	err = SysNotifyRegister( dbH, sysNotifyEarlyWakeupEvent,
								&GameWakeupHandler, sysNotifyNormalPriority, NULL );					
#endif

	//////////////////////////
	//  GFX INIT
	//////////////////////////
	
	screenInfo.size = sizeof(screenInfo);
    err = TwGfxOpen( &gGfx, &screenInfo );
    ErrNonFatalDisplayIf( err != errNone, "can't open gfx" );

    gScreenWidth = screenInfo.displayWidth;
    gScreenHeight = screenInfo.displayHeight;    
    gSurface = GameLoadBitmap( GameBitmapFamily, gGfx );
    
	//////////////////////////
	//  TNA INIT
	//////////////////////////
	
	// Set-up the TNA world.
	TwAppStart( &GameHandleEvent );
}

/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Application destruction routine.
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    None
 *
 ***********************************************************************/
static void AppStop()
{
	GamePreferenceType 		prefs;
	MemHandle				dbH = NULL;
	Err 					err = errNone;

	//////////////////////////
	//  STOP TNA
	//////////////////////////
	TwAppStop();
	
	//////////////////////////
	//  CLOSE GFX
	//////////////////////////
	TwGfxClose( gGfx );
	if (gSurface)
		TwGfxFreeSurface( gSurface );

#ifndef USE_BACKING_STORE
	//////////////////////////
	//  UNREGISTER NOTIFICATIONS
	//////////////////////////
	err = SysCurAppDatabase( &dbH );
	ErrNonFatalDisplayIf( err != errNone, "can't get app db info" );
	err = SysNotifyUnregister( dbH, sysNotifyEarlyWakeupEvent,
								sysNotifyNormalPriority );
#endif
	
	//////////////////////////
	//  SAVE PREFS
	//////////////////////////
	prefs.level = gCurrentLevel;
	PrefSetAppPreferences( kGameAppCreator, kGamePrefId, kGamePrefVersionNumber, &prefs,
						   sizeof(GamePreferenceType), true );
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
 *
 * RETURNED:    Result of launch
 *
 ***********************************************************************/
extern UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	Int32		timeOut = evtWaitForever;
	
	if (cmd == sysAppLaunchCmdNormalLaunch) 
	{
		// Initialize the world
		AppStart();

		// Run event loop.
		TwAppRun(&timeOut);

		// Deconstruct the world
		AppStop();
	}

	return 0;
}