/*
	File:		TwMpARM.c

	Description:Contains the ARM portion of the Tapwave Native Application.  This code contains 
				the event loop and bluetooth communications code.

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
#include "TwMpARMRsc.h"

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
#define appName    "TwMp TNA Sample"
#define appCreator 'MPTN'

// Custom error codes
#define appErrNoError   errNone
#define appErrNotHosting (appErrorClass | 0x01)

// Possible game states 
#define appStateInit 0          // Initialize the game
#define appStateFindAndInvite 1 // Inviting player
#define appStateStartingGame 2  // Invitation accepted, starting game
#define appStateInGame 3        // In the game
#define appStateShuttingDown 4  // Shutting down game
#define appStateIdle 5          // Not in the game, but app still running

#define appL2capSocketMtu (BT_L2CAP_MTU) // MTU for L2Cap socket

#define appInvalidSocket ((BtLibSocketRef) 0xFFFF) // -1 for invalid socket

// Strings for various game states
#define appInvitationString "Handling Invitation..."
#define appStartingString "Starting Game..."
#define appShutdownString "Shutting Down..."
#define appIdleString     "Idle"

// How long, in seconds, to wait before sending count update
#define appSendDelay 1 

// Our UUID unique to this test app 
// 13e67f33-6179-44cb-b468-cdd2e613aa39
// A UUID is a Universally Unique IDentifier that is a 128 bit number
// that is generated (usually using the ethernet address of the device it is
// generated on) to guarantee that it is unique.  Bluetooth uses UUIDs to 
// define unique services that can be discovered by other bluetooth devices.
// This uuid was generated using Microsoft Visual Studio's uuidgen command
// line application. 
static BtLibSdpUuidType appUUID = {btLibUuidSize128, 
{ 0x13, 0xe6, 0x7f, 0x33, 0x61, 0x79, 0x44, 0xcb, 0xb4, 0x68, 
	0xcd, 0xd2, 0xe6, 0x13, 0xaa, 0x39 } };

/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/


/***********************************************************************
 *
 *	Globals
 *
 ***********************************************************************/
static Int32 gTimeout = 0;        // right now we run continuously  
static Boolean gTwMpOpen = false; // true if TwMp library is open

static UInt32 gAppState = appStateInit; // Keep track of app state

static BtLibSocketRef gListenerSocket = appInvalidSocket;
static BtLibSdpRecordHandle gSdpRecordH = 0;
static BtLibSocketRef gConnectionSocket = appInvalidSocket;
static BtLibDeviceAddressType gBdAddr = {0}; // address of other player

// Game State Info
static Int32 gNextSendTime = 0;  // Stores the time when the next send will happen
static Boolean gSendPending = false; // true if I am waiting for a response
                                     // false if it is my turn to send the count
static Boolean gUpdateScreen = false; // If true screen will be updated
static UInt16 gCount = 0;  // Count to display
static UInt8 gData[sizeof(UInt16)] = {0};  //Packet data

/***********************************************************************
 *
 * FUNCTION:    PrvTwMpOpen
 *
 * DESCRIPTION: Open TwMpSession but only once
 *
 * PARAMETERS:  
 *
 * RETURNED:    
 *
 ***********************************************************************/
Err PrvTwMpOpen(void)
{
    Err err;

	if(!gTwMpOpen)
	    err = TwMpOpen();
	else
		err = twMpErrNoError;    
			    
	if(!err)
	{
	    gTwMpOpen = true;
	}
	
	return err;
}

/***********************************************************************
 *
 * FUNCTION:    PrvTwMpClose
 *
 * DESCRIPTION: Close TwMp session if open
 *
 * PARAMETERS:  
 *
 * RETURNED:    
 *
 ***********************************************************************/
Err PrvTwMpClose(void)
{
    Err err = twMpErrNotOpen;
    
    if(gTwMpOpen)
        err = TwMpClose();
        
    gTwMpOpen = false;
    
    return err;
}


/***********************************************************************
 *
 * FUNCTION:    PrvBdAddrCompare
 *
 * DESCRIPTION: Compare two bluetooth addresses
 *
 * PARAMETERS:  bdAddr1P - first address to compare
 *
 *              bdAddr2P - second address to compare
 *
 * RETURNED:    0 if match, non zero if no match
 *
 ***********************************************************************/
UInt8 PrvBdAddrCompare(BtLibDeviceAddressTypePtr bdAddr1P, BtLibDeviceAddressTypePtr bdAddr2P)
{
	UInt8 i;

	for(i = 0; i < btLibDeviceAddressSize; i++)
	{
		if(bdAddr1P->address[i] != bdAddr2P->address[i])
			return 1;
	}
	
	return 0;
}

/***********************************************************************
 *
 * FUNCTION:    PrvUpdateState
 *
 * DESCRIPTION: Update the game state
 *
 * PARAMETERS:  appState - new state
 *
 *              updateScreen - does the screen need to be updated
 *
 * RETURNED:    
 *
 ***********************************************************************/
void PrvUpdateState(UInt32 appState, Boolean updateScreen)
{
    gAppState = appState;
    
    if(false == gUpdateScreen)
        gUpdateScreen = updateScreen;
}

/***********************************************************************
 *
 * FUNCTION:    PrvGameGotoIdle
 *
 * DESCRIPTION: End Multiplayer game portion
 *
 * PARAMETERS:  
 *
 * RETURNED:    
 *
 ***********************************************************************/
static void PrvGameGotoIdle(void)
{
    EventType event = {0};

    switch(gAppState)
    {
    // If we are in the game, close the connection socket        
    case appStateInGame:
        BtLibSocketClose(gConnectionSocket);
        gConnectionSocket = appInvalidSocket;
        PrvUpdateState(appStateShuttingDown, true);    
        break;
    
    case appStateFindAndInvite:
    case appStateStartingGame:
        PrvUpdateState(appStateIdle, true);    
        break;
    
    // Otherwise, just Idle 
    case appStateShuttingDown:
    case appStateInit:       
    case appStateIdle:
        PrvUpdateState(appStateIdle, true);    
        break;    
    }

}

/***********************************************************************
 *
 * FUNCTION:    BtLibMECallbackProc
 *
 * DESCRIPTION: Handle radio events.
 *
 * PARAMETERS:  See BtLib.h
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
SYSTEM_CALLBACK void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon)
{	
	switch(mEventP->event)
	{						
		case btLibManagementEventACLDisconnect:
		    PrvGameGotoIdle();
			break;						
	}
}

/***********************************************************************
 *
 * FUNCTION:    BtLibSocketCallbackProc
 *
 * DESCRIPTION: Handle socket events.
 *
 * PARAMETERS:  See BtLib.h 
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
SYSTEM_CALLBACK void BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	Err error;
	
	switch(sEventP->event)
	{			
		case btLibSocketEventSdpGetPsmByUuid:
			{										
			error = BtLibSocketClose(gConnectionSocket);
			
			// Unlike ACL disconnects, closing a connected socket 
			// will not result in a callback, so mark the socket invalid now
			if( !(error == btLibErrNoError || error == btLibErrPending))	
				ErrFatalDisplayIf(error, "Could not close SDP socket");
					
			if(sEventP->status == btLibErrNoError)
			{	
				BtLibSocketConnectInfoType connectInfo;			
																	
				error = BtLibSocketCreate(&gConnectionSocket , BtLibSocketCallbackProc, refCon,
				     btLibL2CapProtocol);
				
				if (!error)
				{
					connectInfo.remoteDeviceP = &gBdAddr;
					connectInfo.data.L2Cap.remotePsm = sEventP->eventData.sdpByUuid.param.psm;
					connectInfo.data.L2Cap.localMtu = appL2capSocketMtu; 
					connectInfo.data.L2Cap.minRemoteMtu = appL2capSocketMtu;
					error = BtLibSocketConnect(gConnectionSocket, &connectInfo);
				}										
			}
			
			if(sEventP->status || (error != btLibErrPending))
			{			
				BtLibLinkDisconnect(&gBdAddr);								
			}
							
			}	
			break;
						
		case btLibSocketEventConnectRequest:
			BtLibSocketRespondToConnection(sEventP->socket, true);
			break;

		case btLibSocketEventConnectedInbound:		    
			gConnectionSocket =  sEventP->eventData.newSocket;
			
			PrvUpdateState(appStateInGame, true);
			gSendPending = true;
    		
    		error =  BtLibSocketGetInfo(gConnectionSocket, btLibSocketInfo_RemoteDeviceAddress, 
				&gBdAddr, sizeof(BtLibDeviceAddressType));

    		//Clean up the listeners and SDP since a connection is accepted
    		BtLibSdpServiceRecordStopAdvertising(gSdpRecordH);
    	    BtLibSdpServiceRecordDestroy(gSdpRecordH);
    	    gSdpRecordH = 0;

    	    BtLibSocketClose(gListenerSocket);
    	    gListenerSocket = appInvalidSocket;
			break;

		case btLibSocketEventConnectedOutbound:
			PrvUpdateState(appStateInGame, true);		
			break;

		case btLibSocketEventDisconnected:
			// Disconnected sockets should be closed
			BtLibSocketClose(sEventP->socket);
			gConnectionSocket = appInvalidSocket;
			// Disconnect the link and make sure we are in 
			// shutting down state.  
			BtLibLinkDisconnect(&gBdAddr);
			PrvUpdateState(appStateShuttingDown, true);					
   			break;

		case btLibSocketEventSendComplete:
			break;
			
		case btLibSocketEventData:
		    {
		    UInt16 l2capCount;
		    
		    // Receive the count
		    MemMove(&l2capCount, sEventP->eventData.data.data, sizeof(UInt16));
		    gCount = BtLibL2CapNToHS(l2capCount); 
		                
            // Update the screen with new count on next GameHandleEvent
            gUpdateScreen = true;
            
            // Our turn to send so set sendPending to false
		    gSendPending = false;
		    
		    // Set the next time that we should send
		    // Note that we don't handle the rollover case
            gNextSendTime = TimGetTicks() + (SysTicksPerSecond() * appSendDelay);
			}
			break;			
	}
		
}
/***********************************************************************
 *
 * FUNCTION:    PrvL2CapListenAndAdvertise
 *
 * DESCRIPTION: Create and advertise listener on guest device
 *
 * PARAMETERS:  
 *
 * RETURNED:    error returned by BtLib APIs (should be btLibErrNoError)
 *
 ***********************************************************************/
static Err PrvL2CapListenAndAdvertise(void)
{
    Err error;
   	BtLibSocketListenInfoType listenInfo;
					
	error = BtLibSocketCreate(&gListenerSocket, BtLibSocketCallbackProc,
				0, btLibL2CapProtocol);
	if ( !error)
	{
		listenInfo.data.L2Cap.localPsm = BT_L2CAP_RANDOM_PSM;
		listenInfo.data.L2Cap.localMtu = appL2capSocketMtu; //Must be less then 672
		listenInfo.data.L2Cap.minRemoteMtu = appL2capSocketMtu;
		error = BtLibSocketListen(gListenerSocket, &listenInfo);
	}
	
    if(!error)
    {	
    	error = BtLibSdpServiceRecordCreate(&gSdpRecordH);
    					
    	if(!error)
    	{	
    		error  = BtLibSdpServiceRecordSetAttributesForSocket(gListenerSocket, 
    						(BtLibSdpUuidType*) &appUUID, 1, appName, StrLen(appName), 
    						gSdpRecordH);
    						
    		if(!error)
    		{
    			error = BtLibSdpServiceRecordStartAdvertising(gSdpRecordH);
    		}
    	}
	}	
	
	return error;
}

/***********************************************************************
 *
 * FUNCTION:    PrvConnectToDevice
 *
 * DESCRIPTION: Start the connect process by doing SDP on the other
 *              device in the game
 *
 * PARAMETERS:  
 *
 * RETURNED:    error returned by BtLib APIs (should be btLibErrPending)
 *
 ***********************************************************************/
static Err PrvConnectToDevice(void)
{
    Err error;

	error = BtLibSocketCreate(&gConnectionSocket, BtLibSocketCallbackProc, 0, btLibSdpProtocol);
	if (!error)
	{
		// Use SDP to get the PSM, the connection is made in the callback
		error = BtLibSdpGetPsmByUuid(gConnectionSocket, &gBdAddr,
			    (BtLibSdpUuidType*) &appUUID, 1);
	}
	
	return error;				
}

/***********************************************************************
 *
 * FUNCTION:    TwMpCallback
 *
 * DESCRIPTION: Callback for TwMp APIs
 *
 * PARAMETERS:  mpEventP - event info
 *
 *              refCon - user defined callback data.  
 *
 * RETURNED:    
 *
 ***********************************************************************/
SYSTEM_CALLBACK void TwMpCallback (TwMpEventType *mpEventP, UInt32 refCon)
{
    Err error = errNone;

    switch(mpEventP->event)
    {
    case twMpEventPlayerState:
        if(!PrvBdAddrCompare(&(mpEventP->eventData.state.bdAddr), &gBdAddr))
        {
            switch(mpEventP->eventData.state.newState)
            {
            case twMpPlayerAccepted:
                // Other player accepted, so start the game        
                error = TwMpHostStartGame();
                if(error != twMpErrPending)
                {
                    // Unexpected error, shutdown
                    PrvGameGotoIdle();
                }
                else
                {
                    // Update the state to reflect that we are
                    // starting the game.  
                    PrvUpdateState(appStateStartingGame, true);
                }
                break;
                
            case twMpPlayerDeclined:
            case twMpPlayerFailed:
                // Other player failed or declined, so exit
                error = TwMpCancelGame();
                PrvGameGotoIdle();
                break;
            }
        }
        break;

    case twMpEventGameCanceled:
        // In this example you will only get this event on a guest
        PrvGameGotoIdle();
        break;
                
    case twMpEventGuestStartGame:
	// IMPORTANT: the btlib is left open by the multiplayer library
    // so that the ACL links can be left in place.  This means you do 
    // no have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
    // will close the BtLib for the multiplayer library.  Since the BtLib
    // keeps an open count you also need to close the library for every time 
    // that it is opened independently by the application as well.  
        
        // This event happens on the guest and then the host gets the start event, so
        // set up your SDP records and Listener socket.  This example uses
        // L2Cap, but you can use RFCOMM too.  
        BtLibRegisterManagementNotification(BtLibMECallbackProc, NULL);
        PrvL2CapListenAndAdvertise();
        break;
        
    case twMpEventHostStartGame:
	// IMPORTANT: the btlib is left open by the multiplayer library
    // so that the ACL links can be left in place.  This means you do 
    // no have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
    // will close the BtLib for the multiplayer library.  Since the BtLib
    // keeps an open count you also need to close the library for every time 
    // that it is opened independently by the application as well.  

        BtLibRegisterManagementNotification(BtLibMECallbackProc, NULL);
                
        //Connect player who accepted invitation.  
        error = PrvConnectToDevice();
        if(error != btLibErrPending)
        {
           // Something bad happened, exit 
           PrvGameGotoIdle();    
        }
        break;
    
    default:
        ErrNonFatalDisplayIf(1, "Unhandled TwMpCallback Event");
        break;
    
    };
}

/***********************************************************************
 *
 * FUNCTION:    PrvUpdateStatusString
 *
 * DESCRIPTION: Draw string in center of screen
 *
 * PARAMETERS:  msg - string to draw
 *
 * RETURNED:    
 *
 ***********************************************************************/
static void PrvUpdateStatusString(const Char* msg)
{
	RectangleType bounds; 
	// Blue background
	static RGBColorType blue = { 0, 0x00, 0x00, 0xFF};
	// Black text
	static RGBColorType black = { 0, 0x00, 0x00, 0x00};
    
    // Only draw if necessary
    if(gUpdateScreen)
    { 
      	WinPushDrawState();
      	WinSetCoordinateSystem(kCoordinatesNative);
    	WinSetDrawMode( winPaint );
    	WinGetBounds( WinGetDisplayWindow(), &bounds );
    	WinSetForeColorRGB(&blue, NULL);
    	WinSetBackColorRGB(&blue, NULL);
    	WinSetTextColorRGB(&black, NULL);
    	WinPaintRectangle( &bounds, 0 );
    		
    	FntSetFont(largeBoldFont);
        
    	WinPaintChars(msg, StrLen(msg), 
            (bounds.extent.x)/2 - FntCharsWidth(msg, StrLen(msg))/2, 
    		(bounds.extent.y)/2 - FntCharHeight()/2);
    		    
        WinPopDrawState();
        
        gUpdateScreen = false;
    }    
}

/***********************************************************************
 *
 * FUNCTION:    PrvUpdateGameState
 *
 * DESCRIPTION: Called by event loop on nilEvent to do any game
 *              processing.
 *
 * PARAMETERS:  
 *
 * RETURNED:    
 *
 ***********************************************************************/
static void PrvGameLoop(void)
{
    Err err = errNone;
    UInt16 buttonID;
	BtLibClassOfDeviceType deviceFilter = (btLibCOD_ServiceAny | btLibCOD_Major_Computer | btLibCOD_Minor_Comp_Palm);
    Char countStr[4];

    switch(gAppState)
    {
    case appStateInit:
        // Do you want to host a game
	    buttonID = FrmAlert(TwMpHostAlert); 
	
	    if(buttonID == 0 /*yes*/)
	    {	
	        // Hosting so do discovery and invite
            err = BtLibOpen(false);
            if(!err)
            {
                err = BtLibDiscoverSingleDevice( NULL, &deviceFilter, 1, 
                    &gBdAddr, false, false);
                if(!err)
                {
                    err = PrvTwMpOpen();
                    if(!err)
                    {
                        // Set up callback, and specify creator
                        err = TwMpHostGame(appCreator, TwMpCallback, 0);
                        if(!err)
                        {
                            // Invite the other palyer
                            err = TwMpHostInvitePlayer(&gBdAddr);
                        }
                    }
                    
                    if(err && (err != twMpErrPending))
                    {
                        PrvTwMpClose();
                    }
                    else
                    {
                        PrvUpdateState(appStateFindAndInvite, true);
                    }
                }
            }
            BtLibClose();
	    }
	    else
	    {
	        // Not hosting, then go to launcher
	        err = appErrNotHosting;
	    }
        break;
        
    case appStateFindAndInvite:
        PrvUpdateStatusString(appInvitationString);
        break;
        
    case appStateStartingGame:
        PrvUpdateStatusString(appStartingString);    
        break;
        
    case appStateInGame:
        // If it is our turn and it is time to send, send count + 1
        if(!gSendPending && ((gNextSendTime == 0) || (TimGetTicks() > gNextSendTime)))
        {       
            UInt16 l2capCount;
                        
            l2capCount = BtLibL2CapHToNS((gCount + 1));
            MemMove(gData, &l2capCount, sizeof(UInt16));
            
            err = BtLibSocketSend(gConnectionSocket, gData, sizeof(UInt16));
            if(err == btLibErrPending)
            {
                gSendPending = true;
            }
        }
        
        // Display the count
        StrPrintF(countStr, "%d", (UInt32) gCount);
        PrvUpdateStatusString( (const Char*) countStr);                 
        break;
        
    case appStateShuttingDown:
        PrvUpdateStatusString(appShutdownString);
        break;
        
    case appStateIdle:
        // We are in the idle state.  Make sure TwMp is closed
        // so we are available for multiplayer invitations.  
        // Must be done here because you can't call TwMpClose
        // from a BtLib or TwMp callback.  
        gCount = 0;
        gSendPending = false;
        gNextSendTime = 0;
        PrvTwMpClose();    
        PrvUpdateStatusString(appIdleString);
        break;
    }
    
    // if something fails then goto idle
    if(err && (err != twMpErrPending) && (err != btLibErrPending))
    {
        PrvUpdateState(appStateIdle, true);
    }
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
	
	switch (eventP->eType)
	{
		case winDisplayChangedEvent:
			// Resize the active window so that it matches the display window.
			WinGetBounds( WinGetDisplayWindow(), &bounds );
			WinSetBounds( WinGetActiveWindow(), &bounds );	
			gUpdateScreen = true;		
			handled = true;
			break;

        case winEnterEvent:
            gUpdateScreen = true;
            handled = false;
            break;

		case nilEvent:
		    // Game processing done here
		    PrvGameLoop();
		    handled = true;
		    break;
				
		// Any key will ask user to shutdown the game    
		case keyDownEvent:
		    // Ignore if we are already shutting down
		    if(gAppState != appStateShuttingDown)
		    {
		        if(gAppState == appStateIdle)
		        {
		            // Start up the game hosting process
		            PrvUpdateState(appStateInit, false);
		        }
		        else
		        {
    		        // Would you like to leave the game?
    		        if(!FrmAlert(TwMpLeaveAlert))
    		        {
    		            // Yes Button == 0
    		            PrvGameGotoIdle();
    		        }
    		        else
    		        {
    		            // No, so redraw to cover form area again
    		            gUpdateScreen = true;
    		        }
    		    }
		    }
		    handled = true;
		    break;		
	}

	return (handled);
}

/***********************************************************************
 *
 * FUNCTION:    AppStart
 *
 * DESCRIPTION: Start the app
 *
 * PARAMETERS:  
 *
 * RETURNED:    errNone on success, otherwise failure
 *
 ***********************************************************************/
static Err AppStart(void)
{
    Err err = errNone;
    TwMpLaunchParamsType* twMpLaunchParamsP = NULL;  // If not null means we were launched by the
                                                     // multiplayer library.    
	// Get the screen to a state we want.
	PINSetInputAreaState(pinInputAreaHide);
	StatHide();
	SysSetOrientation(sysOrientationLandscape);

	err = FtrGet(twMpFtrCreator, twMpFtrNumMultiplayerLaunch, (UInt32*) &twMpLaunchParamsP); 
	// In this sample we don't care about the contents of this structure, but it
	// will tell you if you were launched from a card or not and the path to the
	// prc.  
	
	if(!err)
	{
	    // If the feature exists then we are being launched by the Multiplayer
	    // library and we need to accept the invitation
	    err = PrvTwMpOpen();
	    if(!err)
	    {
	        err = TwMpGuestAcceptInvitation(TwMpCallback, 0);
	        if(err) 
	            PrvTwMpClose();
	        
	        // Guests jump straight to the app starting state
	        PrvUpdateState(appStateStartingGame, true);  
	    }
	}
	else if(err == ftrErrNoSuchFeature)
	{
	    // If the feature doesn't exist, not an error, just means we were launched
	    // normally.  
	    err = errNone;
	}
	
	if(err == errNone)
	{
	    // Start the game if everything is OK
	    TwAppStart(&GameHandleEvent);
	}
	
	return err;
}

/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Clean up when leaving the application
 *
 * PARAMETERS:  
 *
 * RETURNED:   
 *
 ***********************************************************************/
static void AppStop(void)
{
	// Tear everything down.
    PrvTwMpClose();
	TwAppStop();
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
	Err err = errNone;

    // If you want to replace the invitation dialog by handling the 
    // twMpAppLaunchCmdAskUser launch code, you need to do that in the 
    // 68K pilot main.    
    
	if (cmd == sysAppLaunchCmdNormalLaunch) 
	{
	    err = AppStart();
	    
        if(err == errNone)
        {
	        // Run event loop.
	        TwAppRun(&gTimeout);
            AppStop();
        }        
	}
	
	return err;
}
