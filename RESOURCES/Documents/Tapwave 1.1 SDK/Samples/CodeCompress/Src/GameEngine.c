/*
	File:		GameEngine.c

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

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/
 

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
	Boolean			handled = false;
	RectangleType 	bounds;
	static const 	RGBColorType 	fill = {0, 0x00, 0xFF, 0x00}; 
	
	switch (eventP->eType)
	{
		case winDisplayChangedEvent:
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinSetBounds( WinGetActiveWindow(), &bounds );
			
			handled = true;
			break;

		case nilEvent:
		case frmUpdateEvent:
			// Paint the screen green just so we draw something.
			WinPushDrawState();
			WinSetDrawMode( winPaint );
			WinSetForeColorRGB( &fill, NULL );
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinPaintRectangle( &bounds, 0 );
			WinPopDrawState();
	
			handled = true;
			break;
	}

	return (handled);
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
		// Get the screen to a state we want.
		PINSetInputAreaState(pinInputAreaHide);
		StatHide();
		SysSetOrientation(sysOrientationLandscape);
		
		// Set everything up.
		TwAppStart(&GameHandleEvent);

		// Run event loop.
		TwAppRun(&timeOut);

		// Tear everything down.
		TwAppStop();
	}
	
	return 0;
}
