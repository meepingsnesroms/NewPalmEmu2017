/******************************************************************************
 *
 * Copyright (c) 2003-2004 Tapwave Inc.
 *
 * File: TwMpTest.c
 *
 *
 *****************************************************************************/

#include <Tapwave.h>
#include "TwMpTestRsc.h"

// Define this if you want to replace the standard invitation dialog
//#define REPLACE_INVITATION_DIALOG 1

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
#define appFileCreator				'MPTE'	// register your own at http://www.palmos.com/dev/creatorid/
#define appVersionNum				0x01

#define appName 					"TwMpTest"

#define appTableNameColumn 			0        // The first column is for the device name
#define appTableStateColumn 		1       // The second column is for state of device

// Adjustments to the text to make them look good
#define appTableNameColumnTab 		(3)
#define appTableStateColumnTab 		(3)

#define appStringIndexAppNotFound 	(twMpPlayerFailed + 1)
#define appStringListMaxLength 		(15)  // Max length of state strings

#define appGuestMaxStrLen 			(13)       // Max length of guest game string

#define appL2capSocketMtu 			(BT_L2CAP_MTU) // MTU for L2Cap socket

#define appInvalidSocket 			((BtLibSocketRef) 0xFFFF) // -1 for invalid socket

// Define the minimum OS version we support (5.0 for now).
#define ourMinVersion				sysMakeROMVersion(5,0,0,sysROMStageRelease,0)
#define kPalmOS10Version			sysMakeROMVersion(1,0,0,sysROMStageRelease,0)


// Our UUID unique to this test app
// bd085d91-ba06-4244-958a-807b5a2b9604
// A UUID is a Universally Unique IDentifier that is a 128 bit number
// that is generated (usually using the ethernet address of the device it is
// generated on) to guarantee that it is unique.  Bluetooth uses UUIDs to 
// define unique services that can be discovered by other bluetooth devices.
// This uuid was generated using Microsoft Visual Studio's uuidgen command
// line application. 
static BtLibSdpUuidType appUUID = {btLibUuidSize128, 
{ 0xbd, 0x08, 0x5d, 0x91, 0xba, 0x06, 0x42, 0x44, 0x95, 0x8a, 
	0x80, 0x7b, 0x5a, 0x2b, 0x96, 0x04 } };



/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/


/***********************************************************************
 *
 *	Global variables
 *
 ***********************************************************************/
static UInt16 gBtLibRefNum;
static TwMpLaunchParamsType* gTwMpLaunchParamsP = NULL;  // If not null means we were launched by the multiplayer
                                                        // library.    

// 8 possible players in a game if you include the host
static UInt8 gNumPlayers = 0;
static BtLibDeviceAddressType gPlayers[kTwMpMaxOtherPlayers + 1];
static Boolean gHosting = false; //true if we are hosting the game
static Boolean gTwMpOpen = false; //true if TwMp library is open
static Boolean gCloseMultiplayer = false; //Close the library on form close event

// For guests
static BtLibSocketRef gListenerSocket = appInvalidSocket;
static BtLibSdpRecordHandle gSdpRecordH = 0;
static Char gLabelStr[appGuestMaxStrLen] = "";

// For Hosts
static BtLibSocketRef gSockets[kTwMpMaxOtherPlayers + 1] = {appInvalidSocket, appInvalidSocket, appInvalidSocket, appInvalidSocket,
                                                            appInvalidSocket, appInvalidSocket, appInvalidSocket, appInvalidSocket};
static UInt8 gNumConnections = 0;    

/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/
static void InvitationFormLeaveForm(Boolean fromCallback);
UInt8 PrvBdAddrCompare(BtLibDeviceAddressTypePtr bdAddr1P, BtLibDeviceAddressTypePtr bdAddr2P);
Int16 PrvFindBdAddrIndex(BtLibDeviceAddressType *bdAddrP);
Err PrvTwMpOpen(void);
Err PrvTwMpClose(void);
void TwMpCallback (TwMpEventType *mpEventP, UInt32 refCon);
void PrvInvitationFormTableDrawItem (TableType *tableP, Int16 row, Int16 column, RectangleType *bounds);


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
static void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon)
{	
	switch(mEventP->event)
	{						
		case btLibManagementEventACLDisconnect:
		    gNumConnections--;
		    if(gNumConnections == 0)
		        FrmGotoForm(MainForm);
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
static void BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	Err error;
		
	switch(sEventP->event)
	{			
		case btLibSocketEventSdpGetPsmByUuid:
			{									
			error = BtLibSocketClose(gBtLibRefNum, gSockets[refCon]);
			
			// Unlike ACL disconnects, closing a connected socket 
			// will not result in a callback, so mark the socket invalid now
			if( !(error == btLibErrNoError || error == btLibErrPending))	
				ErrFatalDisplayIf(error, "Could not close SDP socket");
					
			if(sEventP->status == btLibErrNoError)
			{	
				BtLibSocketConnectInfoType connectInfo;			
																	
				error = BtLibSocketCreate(gBtLibRefNum, &(gSockets[refCon]) , BtLibSocketCallbackProc, refCon, btLibL2CapProtocol);
				
				if (!error)
				{
					connectInfo.remoteDeviceP = &(gPlayers[refCon]);
					connectInfo.data.L2Cap.remotePsm = sEventP->eventData.sdpByUuid.param.psm;
					connectInfo.data.L2Cap.localMtu = appL2capSocketMtu; 
					connectInfo.data.L2Cap.minRemoteMtu = appL2capSocketMtu;
					error = BtLibSocketConnect(gBtLibRefNum, gSockets[refCon], &connectInfo);
				}										
			}
			
			if(sEventP->status || (error != btLibErrPending))
			{			
				BtLibLinkDisconnect(gBtLibRefNum, &(gPlayers[refCon]));								
			}
							
			}	
			break;
						
		case btLibSocketEventConnectRequest:
			// If we are not the host, then accept connection, otherwise reject
			if(!gHosting)
			{
				BtLibSocketRespondToConnection(gBtLibRefNum, sEventP->socket, true);
			}
			else
			{
				BtLibSocketRespondToConnection(gBtLibRefNum, sEventP->socket, false);
			}
			break;

		case btLibSocketEventConnectedInbound:
		    gNumConnections++;
		    
		    // Guest store the socket and the hosts bdAddr
			gSockets[0] =  sEventP->eventData.newSocket;
			error =  BtLibSocketGetInfo(gBtLibRefNum, gSockets[0], btLibSocketInfo_RemoteDeviceAddress, 
				&(gPlayers[0]), sizeof(BtLibDeviceAddressType));
			ErrFatalDisplayIf(error != btLibErrNoError, "Can't get bdaddr");		
			FrmGotoForm(GameForm);
			break;

		case btLibSocketEventConnectedOutbound:
			{
            UInt8 *numP;
            
            gNumConnections++;			
			
			// Send out the guest's number
			numP = MemPtrNew(sizeof(UInt8));
			
			*numP = (UInt8) (refCon + 1);
			
			error = BtLibSocketSend(gBtLibRefNum, sEventP->socket, numP, sizeof(UInt8));
			 
			if(error != btLibErrPending)
			    MemPtrFree(numP); 
			}
			break;

		case btLibSocketEventDisconnected:
			// Disconnected sockets should be closed
			BtLibSocketClose(gBtLibRefNum, sEventP->socket);
			gSockets[refCon] = appInvalidSocket;
			BtLibLinkDisconnect(gBtLibRefNum, &(gPlayers[refCon]));
			
   			break;

		case btLibSocketEventSendComplete:
		    // Free the data we sent
		    MemPtrFree(sEventP->eventData.data.data);
			break;
			
		case btLibSocketEventData:
		    {
		    MemHandle memH;
		    Char* str;
		    
		    
		    // Guest received the byte with the guest's number.
		    // Put it in the string we display.  
		    
	        memH = DmGetResource(strRsc, GameGuestString);
	            
	        str = (Char*) MemHandleLock(memH);
	            
	        StrPrintF(gLabelStr, "%s %d", str, *(sEventP->eventData.data.data));
	            	            	            
	        MemHandleUnlock(memH);  
	        
	        DmReleaseResource(memH);   
		    
		    if(GameForm == FrmGetActiveFormID())
		    {
	            FormType* frmP;
		        	            
	            frmP = FrmGetActiveForm();
	            
	            FrmCopyLabel(frmP, GameGameLabel, gLabelStr);	            	            
		    }
		    
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
					
	error = BtLibSocketCreate(gBtLibRefNum, &gListenerSocket, BtLibSocketCallbackProc,
				0, btLibL2CapProtocol);
	if ( !error)
	{
		listenInfo.data.L2Cap.localPsm = BT_L2CAP_RANDOM_PSM;
		listenInfo.data.L2Cap.localMtu = appL2capSocketMtu; //Must be less then 672
		listenInfo.data.L2Cap.minRemoteMtu = appL2capSocketMtu;
		error = BtLibSocketListen(gBtLibRefNum, gListenerSocket, &listenInfo);
	}
	
    if(!error)
    {	
    	error = BtLibSdpServiceRecordCreate(gBtLibRefNum, &gSdpRecordH);
    					
    	if(!error)
    	{	
    		error  = BtLibSdpServiceRecordSetAttributesForSocket(gBtLibRefNum, gListenerSocket, 
    						(BtLibSdpUuidType*) &appUUID, 1, appName, StrLen(appName), 
    						gSdpRecordH);
    						
    		if(!error)
    		{
    			error = BtLibSdpServiceRecordStartAdvertising(gBtLibRefNum, gSdpRecordH);
    		}
    	}
	}	
	
	return error;
}

/***********************************************************************
 *
 * FUNCTION:    PrvConnectToDevices
 *
 * DESCRIPTION: Start the connect process by doing SDP on all the
 *              devices in the game
 *
 * PARAMETERS:  
 *
 * RETURNED:    error returned by BtLib APIs (should be btLibErrPending)
 *
 ***********************************************************************/
static Err PrvConnectToDevices(void)
{
    UInt32 i;
    Err error;

    for(i = 0; i < gNumPlayers; i++)
    {				
	    error = BtLibSocketCreate( gBtLibRefNum, &gSockets[i], BtLibSocketCallbackProc, i, btLibSdpProtocol);
	    if (!error)
	    {
		    // Use SDP to get the PSM, the connection is made in the callback
		    error = BtLibSdpGetPsmByUuid(gBtLibRefNum, gSockets[i], &gPlayers[i],
			    (BtLibSdpUuidType*) &appUUID, 1);
	    }
	}
	
	return error;				
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
 * FUNCTION:    PrvFindBdAddrIndex
 *
 * DESCRIPTION: Find an index in the array that matches an bluetooth 
 *              address.  
 *
 * PARAMETERS:  bdAddrP - address to find
 *
 * RETURNED:    index of the matching entry or -1 if no match
 *
 ***********************************************************************/
Int16 PrvFindBdAddrIndex(BtLibDeviceAddressType *bdAddrP)
{
    UInt8 i;

    for(i = 0; i < gNumPlayers; i++)
    {
        if(!PrvBdAddrCompare(bdAddrP, &(gPlayers[i])))
            break;   
    }
    
    if(i == gNumPlayers)
    {
        return -1;
    }
    
    return i;
} 

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
void TwMpCallback (TwMpEventType *mpEventP, UInt32 refCon)
{
    Int16 i;
	FormPtr frmP;
	TableType* tableP;    

    switch(mpEventP->event)
    {
    case twMpEventPlayerState:
        i = PrvFindBdAddrIndex(&(mpEventP->eventData.state.bdAddr));
        
        if(i == -1)
        {
            // New address, add to list
            if(gNumPlayers < kTwMpMaxOtherPlayers + 1)
            {
                gPlayers[gNumPlayers] = mpEventP->eventData.state.bdAddr;
                i = gNumPlayers;
                gNumPlayers++;
            }
        }
        
        if(InvitationForm == FrmGetActiveFormID())
        {
            frmP = FrmGetActiveForm();
            
            tableP = FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, InvitationPlayersTable));

            TblSetRowUsable(tableP, i, true);            
            TblMarkRowInvalid(tableP, i);
            TblRedrawTable(tableP);
        }    
        break;
        
    case twMpEventGameCanceled:       
        InvitationFormLeaveForm(true);
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
        BtLibRegisterManagementNotification(gBtLibRefNum, BtLibMECallbackProc, NULL);
        PrvL2CapListenAndAdvertise();
        break;
        
    case twMpEventHostStartGame:
	// IMPORTANT: the btlib is left open by the multiplayer library
    // so that the ACL links can be left in place.  This means you do 
    // no have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
    // will close the BtLib for the multiplayer library.  Since the BtLib
    // keeps an open count you also need to close the library for every time 
    // that it is opened independently by the application as well.  

        BtLibRegisterManagementNotification(gBtLibRefNum, BtLibMECallbackProc, NULL);

        //Get the list of accepted devices
        gNumPlayers = (UInt8) (mpEventP->eventData.acceptedPlayers.numGuests);
        
        // Copy guests into the array        
        for(i = 0; i < gNumPlayers; i++)
        {
            gPlayers[i] = mpEventP->eventData.acceptedPlayers.guestAddrs[i];
        }
        
        //Connect to the set of players who accepted invitations.  
        PrvConnectToDevices();
        FrmGotoForm(GameForm);
        break;
    
    default:
        break;
    
    };
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
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  formId - id of the form to display
 *
 * RETURNED:    void *
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID)
{
	FormPtr frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

/***********************************************************************
 *
 * FUNCTION:    GameFormInit
 *
 * DESCRIPTION: This routine initializes the GameForm form.
 *
 * PARAMETERS:  frm - pointer to the GameForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void GameFormInit(FormPtr frmP)
{
    MemHandle memH;
	Char* str;

    // Always hide the status label to start
    FrmHideObject(frmP, FrmGetObjectIndex( frmP, GameLeavingGameLabel));      	               

	if(gHosting)
	{	        
	    memH = DmGetResource(strRsc, GameHostString);
	            
    	str = (Char*) MemHandleLock(memH);
	                         
	    FrmCopyLabel(frmP, GameGameLabel, str);
	            	            
    	MemHandleUnlock(memH);
    	
    	DmReleaseResource(memH);
    }
    else if(StrLen(gLabelStr))
    {
        FrmCopyLabel(frmP, GameGameLabel, gLabelStr);
    }     
}

/***********************************************************************
 *
 * FUNCTION:    GameFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              "GameForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean GameFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP = FrmGetActiveForm();

	switch (eventP->eType) 
		{
		case frmOpenEvent:
			GameFormInit( frmP);
			FrmDrawForm ( frmP);
			handled = true;
			break;
			
		case frmUpdateEvent:
			// To do any custom drawing here, first call FrmDrawForm(), then do your
			// drawing, and then set handled to true.
			break;

        case ctlSelectEvent:
      	    switch( eventP->data.ctlSelect.controlID )
      	    {
      	    case GameLeaveButton:
      	        if(gHosting)
      	        {
      	            UInt8 i;
      	            
      	            for(i = 0; i < kTwMpMaxOtherPlayers + 1; i++)
      	            {
      	                if(gSockets[i] != appInvalidSocket)
      	                {
      	                    BtLibSocketClose(gBtLibRefNum, gSockets[i]);
      	                    gSockets[i] = appInvalidSocket;
      	                }
      	            }
      	        }
      	        else
      	        {
      	            if(gSockets[0] != appInvalidSocket)
      	            {
      	                BtLibSocketClose(gBtLibRefNum, gSockets[0]);
      	                gSockets[0] = appInvalidSocket;
      	            }
      	        }
      	        
      	        // We are leaving, so hide the button and show the leaving game text	                
      	        FrmHideObject(frmP, FrmGetObjectIndex( frmP, GameLeaveButton));
      	        FrmShowObject(frmP, FrmGetObjectIndex( frmP, GameLeavingGameLabel));      	               
      	        break;
      	    };
      	    break;

 		case frmCloseEvent:
 		    // Close the multiplayer library when game is done so that we
 		    // can invite or be invited again.  
            PrvTwMpClose();		            
            break;
                			
		default:
			break;
		
		}
	
	return handled;
}

/***********************************************************************
 *
 * FUNCTION:    PrvInvitationFormTableDrawItem 
 *
 * DESCRIPTION: Callback that draws items in the invitation table of devices
 *
 * PARAMETERS:  tableP - pointer to table structure.
 *
 *              row - row index
 *
 *              column - column index
 *
 *              bounds - defines column screen area
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
void PrvInvitationFormTableDrawItem (TableType *tableP, Int16 row, Int16 column, RectangleType *bounds)
{
    //Check whether row is for a valid player
    if(row < gNumPlayers)
    {
        TwMpPlayerInfoType playerInfo;
        
	    WinPushDrawState();
		
		// Set up the font
	    FntSetFont( stdFont);
	    WinSetUnderlineMode( noUnderline);
	    
	    // Set up the player info structure
	    playerInfo.size = sizeof(TwMpPlayerInfoType);  // Needed to check structure size
	    playerInfo.name.name = MemPtrNew(btLibMaxDeviceNameLength);
	    playerInfo.name.nameLength = btLibMaxDeviceNameLength;
	    
	    TwMpGetPlayerInfo(&(gPlayers[row]), &playerInfo);
	    
	    if(column == appTableNameColumn)
	    {
	    	// If this is the name column then draw the name
	        if(playerInfo.name.nameLength > 0)
	        {
	            WinDrawTruncChars((const char*) (playerInfo.name.name), (Int16) (playerInfo.name.nameLength - 1), 
	                (Coord) (bounds->topLeft.x + appTableNameColumnTab), 
	                bounds->topLeft.y, (Coord) (bounds->extent.x - appTableNameColumnTab));
	        }
	        else
	        {
	            // Use default name if name does not exist.
	            MemHandle memH;
	            Char* str;
	        
	            memH = DmGetResource(strRsc, GenericPlayerString);
	            
	            str = (Char*) MemHandleLock(memH);
	            
	            WinDrawTruncChars(str, StrLen(str), 
	            	(Coord) (bounds->topLeft.x + appTableNameColumnTab), 
	                bounds->topLeft.y, (Coord) (bounds->extent.x - appTableNameColumnTab));
	            
	            MemHandleUnlock(memH);
	            DmReleaseResource(memH);
	            memH = 0;
	        }
        }
        else if(column == appTableStateColumn)
        {
            // If this is the state column then display color codes state string
            char str[appStringListMaxLength];
            RGBColorType rgb = {0, 0, 0, 0}; 
            Int16 strWidth;
            UInt32 strIndex = playerInfo.state;
            
            switch(playerInfo.state)
            {
            case twMpPlayerWaiting:
            case twMpPlayerAclConnected:
            case twMpPlayerConnected:
            case twMpPlayerAccepted:
                //green for good                
                rgb.g = 0xFF;
                WinSetTextColorRGB(&rgb, NULL);
                break;
           
            case twMpPlayerHosting:
                //blue
                rgb.b = 0xFF;
                WinSetTextColorRGB(&rgb, NULL);
                break;
            
            case twMpPlayerFailed:
                if(playerInfo.reason == twMpErrNotFound)
                    strIndex = appStringIndexAppNotFound;
                    
                // Intentional fall through
            case twMpPlayerDeclined:
                //red for bad
                rgb.r = 0xFF;
                WinSetTextColorRGB(&rgb, NULL);
                break;
            
            default:
                break;
            };
            
            //Get string associated with state        
            SysStringByIndex(DeviceStatesStringList, strIndex, str, appStringListMaxLength);
            
            strWidth = FntCharsWidth(str, StrLen(str));
            
            //Adjust the extent so it is at least 3 pixels away from the frame.  
            bounds->extent.x -= appTableStateColumnTab;
            
            // Right hand justify the string
            if(strWidth < bounds->extent.x)
            {
                bounds->topLeft.x += (bounds->extent.x - strWidth);
                bounds->extent.x = strWidth;
            }
                        
            WinDrawTruncChars(str, StrLen(str), bounds->topLeft.x, bounds->topLeft.y, bounds->extent.x);
        }

        WinPopDrawState();
        MemPtrFree(playerInfo.name.name);
    }
    
    return;
}

/***********************************************************************
 *
 * FUNCTION:    InvitationFormInit
 *
 * DESCRIPTION: This routine initializes the InvitationForm form.
 *
 * PARAMETERS:  frm - pointer to the InvitationForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void InvitationFormInit(FormPtr frmP)
{
	Int16 row;
	Int16 rowsInTable;
	TableType* tableP;

	// If we aren't hosting then no start button, and we need to get the
	// players already in the game.  
	if(!gHosting)
	{
	    Err err;
	    
	    err = TwMpGetNumPlayers(&gNumPlayers);
	    
	    ErrFatalDisplayIf(err || gNumPlayers > kTwMpMaxOtherPlayers + 1, "Invalid number of players");
	
	    err = TwMpGetAllPlayers(gPlayers, gNumPlayers, &gNumPlayers);
	    
	    FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationStartButton));
	}
    
    // Always hide the status label to start
    FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationStatusLabel));      	               

	tableP = FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, InvitationPlayersTable));

	// init the table
	rowsInTable = TblGetNumberOfRows (tableP);
	for (row = 0; row < rowsInTable; row++)
	{
		TblSetItemStyle( tableP, row, appTableNameColumn, customTableItem);
		
		TblSetItemStyle( tableP, row, appTableStateColumn, customTableItem);
		
		// Items can't be selected
		TblSetRowSelectable( tableP, row, false);
		
		// Only set valid players usable
		if(row >= gNumPlayers)	
		    TblSetRowUsable( tableP, row, false);
		else
		    TblSetRowUsable( tableP, row, true);
	}

	TblSetColumnUsable( tableP, appTableNameColumn, true);
	
	// Set the callback routine to draw the device name
	TblSetCustomDrawProcedure( tableP, appTableNameColumn, (TableDrawItemFuncPtr) PrvInvitationFormTableDrawItem);

	TblSetColumnUsable( tableP, appTableStateColumn, true);

    // Set the callback routine to draw the device state
	TblSetCustomDrawProcedure( tableP, appTableStateColumn, (TableDrawItemFuncPtr) PrvInvitationFormTableDrawItem);
	
}

/***********************************************************************
 *
 * FUNCTION:    InvitationFormLeaveForm
 *
 * DESCRIPTION: Leave the Invitation Form
 *
 * PARAMETERS:  fromCallback  - true if called from TwMp callback, false otherwise
 *
 * RETURNED:
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void InvitationFormLeaveForm(Boolean fromCallback)
{
    // Can't close the library inside its own callback, so set a flag to 
    // do it on form close
    if(fromCallback)
        gCloseMultiplayer = true;
    else
        PrvTwMpClose();
    
    // Leave the form
    FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    InvitationFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              "InvitaionForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean InvitationFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP;
    TableType *tableP;
    RectangleType r;
    Err err;
    MemHandle memH;
	Char* str;

	frmP = FrmGetActiveForm();

	switch (eventP->eType) 
		{
		case frmOpenEvent:
			InvitationFormInit( frmP);
			//Intentional fall through
		case frmUpdateEvent:
	        tableP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, InvitationPlayersTable));
            FrmDrawForm(frmP);
	        TblGetBounds(tableP, &r);
	        // Draw frame for table
	        WinDrawRectangleFrame(simpleFrame, &r);
            handled = true;
            break;
                        
        case ctlSelectEvent:
      	    switch( eventP->data.ctlSelect.controlID )
      	    {
      	    case InvitationCancelButton:
      	        err = TwMpCancelGame();
      	        if (err == twMpErrPending)
      	        {
      	            // Hide buttons and put up status while we wait for the
      	            // cancelled event.  
	                FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationStartButton));
	                FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationCancelButton));      	               
      	                  	            
	                memH = DmGetResource(strRsc, InvitationCancelString);
	            
    	            str = (Char*) MemHandleLock(memH);
	                         
	                FrmCopyLabel(frmP, InvitationStatusLabel, str);
	            	            
    	            MemHandleUnlock(memH);
    	            
    	            DmReleaseResource(memH);
      	                  	            
      	            FrmShowObject(frmP, FrmGetObjectIndex( frmP, InvitationStatusLabel));      	               
      	        }
      	        else
      	        {
      	            // If we don't have to wait for an event then leave
      	            InvitationFormLeaveForm(false);
      	            if(err) ErrAlert(err);
      	        }
      	        break;
      	    
      	    case InvitationStartButton:
      	        err = TwMpHostStartGame();
      	        if(err == twMpErrPending)
      	        {
      	            // Hide buttons and put up status while we wait for the
      	            // game started event.  
	                FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationStartButton));
	                FrmHideObject(frmP, FrmGetObjectIndex( frmP, InvitationCancelButton));      	               
      	                  	            
	                memH = DmGetResource(strRsc, InvitationStartString);
	            
    	            str = (Char*) MemHandleLock(memH);
	                         
	                FrmCopyLabel(frmP, InvitationStatusLabel, str);
	            	            
    	            MemHandleUnlock(memH);
    	            
    	            DmReleaseResource(memH);
      	                  	            
      	            FrmShowObject(frmP, FrmGetObjectIndex( frmP, InvitationStatusLabel));      	               
                }
                else
                {
      	            InvitationFormLeaveForm(false);
      	            if(err) ErrAlert(err);      	            
                }      	                  	      
      	        break;
      	    };
      	    break;
    
 		case frmCloseEvent:
		    if(gCloseMultiplayer)
		    {
                PrvTwMpClose();		            
		        gCloseMultiplayer = false;
		    }
		    break;
             
		default:
			break;
		
		}
	
	return handled;

}



/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:  frm - pointer to the MainForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void MainFormInit(FormPtr frmP)
{
}


/***********************************************************************
 *
 * FUNCTION:    MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormDoCommand(UInt16 command)
{
	Boolean handled = false;
	FormPtr frmP;

	switch (command)
		{
		case MainOptionsAboutTwMpTest:
			MenuEraseStatus(0);					// Clear the menu status from the display.
			frmP = FrmInitForm (AboutForm);
			FrmDoDialog (frmP);					// Display the About Box.
			FrmDeleteForm (frmP);
			handled = true;
			break;
			
		case TwMpHost:
			{
			UInt8 i;
			Err err;
			UInt8 numDevicesSelected = 0, numDevicesReturned = 0;
			// Only find PDAs
			BtLibClassOfDeviceType deviceFilter = (btLibCOD_ServiceAny | btLibCOD_Major_Computer | btLibCOD_Minor_Comp_Palm);
			BtLibDeviceAddressType *bdAddrP = NULL;
			BtLibDeviceAddressType hostAddr;
			Boolean btLibOpen = false;
			
			//Open the multiplayer session
			err = PrvTwMpOpen();
			    
			if(!err)
			{
			    // Set app creator and register callback
			    err = TwMpHostGame(appFileCreator, TwMpCallback, 0);
			    if(!err)
			    {
			        // Open the BtLib to do the discovery. TwMpHostGame actually
			        // opens the BtLib, but just go ahead and do it again.  
			        err = BtLibOpen(gBtLibRefNum, false);
			        if(!err || err == btLibErrAlreadyOpen)
			        {
			            btLibOpen = true;
			            err = BtLibGetGeneralPreference(gBtLibRefNum, btLibPref_LocalDeviceAddress, &hostAddr, sizeof(BtLibDeviceAddressType));
			            
			            if(!err)
			            {
			                // Store our address as the host
                            gPlayers[0] = hostAddr;
			                gNumPlayers = 1;
			                
			                // Find other players
			                err = BtLibDiscoverMultipleDevices(gBtLibRefNum, NULL, NULL, &deviceFilter, 1, &numDevicesSelected, false, false);
			            }
			        }
			    }
			}
			
			// Don't let us invite more than 7 players
			while(!err && (numDevicesSelected > (kTwMpMaxOtherPlayers - gNumPlayers - 1)))
			{
			    char str[2];
			    
			    StrPrintF(str, "%d", kTwMpMaxOtherPlayers - gNumPlayers);
			    FrmCustomAlert(ExceededMaximumLinksAlert, str, NULL, NULL);
			    err = BtLibDiscoverMultipleDevices(gBtLibRefNum, NULL, NULL, &deviceFilter, 1, &numDevicesSelected, false, true);
			}
			
			if(!err)
			{
			    // Get the invitees
			    err = BtLibGetSelectedDevices(gBtLibRefNum, &(gPlayers[gNumPlayers]), numDevicesSelected, &numDevicesReturned);
			    BtLibClose(gBtLibRefNum);
			    btLibOpen = false;
			    if(!err)
			    {
			        numDevicesSelected += gNumPlayers;
			        for(i = gNumPlayers; i < numDevicesSelected; i++)
			        {
			            // Invite all the players one at a time
				        err = TwMpHostInvitePlayer(&(gPlayers[i]));
				        if(err != twMpErrPending)
				            ErrAlert(err);
				        else
				            gNumPlayers++;	    
			        }
			    }
			}
				
			if(err == twMpErrPending)
			{
			    if(gNumPlayers)
			    {
			        // Go to the form to display invitation states
			        gHosting = true;
			        FrmGotoForm(InvitationForm);
			    }
			}
			else
			{
			    PrvTwMpClose();
			    
			    //For error cases    
			    if(btLibOpen)
			        BtLibClose(gBtLibRefNum);
			    
			    if(err != btLibErrCanceled)    
			        ErrAlert(err);
			}
			
			handled = true;
						
			}
			break;

		}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              "MainForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP;

	switch (eventP->eType) 
		{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			MainFormInit( frmP);
			FrmDrawForm ( frmP);
			handled = true;
			break;
			
		case frmUpdateEvent:
			// To do any custom drawing here, first call FrmDrawForm(), then do your
			// drawing, and then set handled to true.
			break;
			
		default:
			break;
		
		}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and set the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventPtr eventP)
{
	UInt16 formId;
	FormPtr frmP;

	if (eventP->eType == frmLoadEvent)
		{
		// Load the form resource.
		formId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(formId);
		FrmSetActiveForm(frmP);

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
			{
			case MainForm:
				FrmSetEventHandler(frmP, MainFormHandleEvent);
				break;
				
			case InvitationForm:
			    FrmSetEventHandler(frmP, InvitationFormHandleEvent);
			    break;
			    
			case GameForm:
			    FrmSetEventHandler(frmP, GameFormHandleEvent);
			    break;

			default:
				ErrFatalDisplay("Invalid Form Load Event");
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
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
				if (! AppHandleEvent(&event))
					FrmDispatchEvent(&event);

	} while (event.eType != appStopEvent);
}


/***********************************************************************
 *
 * FUNCTION:     AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err AppStart(void)
{
	Err err = errNone;
        
    err = SysLibFind(btLibName, &gBtLibRefNum);
    ErrFatalDisplayIf(err, "Could not find BtLib");
		
	err = FtrGet(twMpFtrCreator, twMpFtrNumMultiplayerLaunch, (UInt32*) &gTwMpLaunchParamsP); 
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
	    }
	}
	else if(err == ftrErrNoSuchFeature)
	{
	    // If the feature doesn't exist, not an error, just means we were launched
	    // normally.  
	    err = errNone;
	}
		
	return err;
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppStop(void)
{		
	// Close all the open forms.
	FrmCloseAllForms();
	
	// Close TwMp session if open
    PrvTwMpClose();
}


/***********************************************************************
 *
 * FUNCTION:    TwMpTestPalmMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static UInt32 TwMpTestPalmMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	Err error;
    UInt32 result = errNone;

	error = RomVersionCompatible (ourMinVersion, launchFlags);
	if (error) return (error);

	switch (cmd)
		{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error) 
				return error;
			
			if(gTwMpLaunchParamsP == NULL)
			{
			    FrmGotoForm(MainForm); // Normal Launch
			}
			else
			{
			    gHosting = false;
			    FrmGotoForm(InvitationForm); // Launched by Multiplayer library
			}
			AppEventLoop();
			AppStop();
			break;


#ifdef REPLACE_INVITATION_DIALOG
        // Replace the system invitation dialog with our own.  
        case twMpAppLaunchCmdAskUser:
            {
            // A TwMpAskUserParamType structure is passed in the parameter
            // block
            TwMpAskUserParamType* askParamP = (TwMpAskUserParamType*) cmdPBP;
            UInt16 buttonID;
            
            // Display simple invitation getting host name form parameter block.
            buttonID = FrmCustomAlert(InvitationDialogAlert, (const Char*) (askParamP->hostName.name), 0, 0);
            
            if(buttonID == InvitationDialogYes)
            {
                // Tell the system that we accept the game invite
                result = twMpResultAccept;
            }
            else
            {
                // Tell the system we decline the game invite
                result = twMpResultDecline;            
            }
            }
            break;
#endif //REPLACE_INVITATION_DIALOG

		default:
			break;

		};
	
	return result;
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
UInt32 PilotMain( UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	return TwMpTestPalmMain(cmd, cmdPBP, launchFlags);
}
