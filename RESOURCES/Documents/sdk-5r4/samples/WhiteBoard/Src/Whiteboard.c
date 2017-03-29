/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: Whiteboard.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *		Bluetooth Whiteboard sample application
 *
 *****************************************************************************/

#include <PalmOS.h>
#include <BtLib.h>
#include <unix_stdarg.h>
#include "WhiteboardRsc.h"


/***********************************************************************
 *   Constants
 ***********************************************************************/

#define kAppFileCreator				'btwb'	// register your own at http://www.palmos.com/dev/creatorid/
#define kAppBtName					"Whiteboard Piconet Example Application"

#define kInvalidSocket				0xFFFF
#define kL2CapSocketMtu				500
#define kMaxDevices 				7
#define kBdAddrStrSize 				18
#define kQueueSendTriggerSecs	 	1
#define kMaxQueueSize				100

// {83E087AE-4E18-46be-83E0-7B3DE6A1C33B}
static const BtLibSdpUuidType kWhiteboardUUID = {btLibUuidSize128, 
{ 0x83, 0xe0, 0x87, 0xae, 0x4e, 0x18, 0x46, 0xbe, 0x83, 0xe0, 0x7b, 0x3d, 0xe6, 0xa1, 0xc3, 0x3b } };
	
static const BtLibClassOfDeviceType kDeviceFilter = (btLibCOD_ServiceAny | btLibCOD_Major_Computer | btLibCOD_Minor_Comp_Palm);

static const Char kLockStr[] = "Lock";
static const Char kUnlockStr[] = "Unlock";	

static const RectangleType kDrawRect = {0,0,160,143}; // Draw area


/***********************************************************************
 *   Structures
 ***********************************************************************/

typedef	struct _WhiteBoardRemoteDrawEvent
{
	Boolean		clear;		//if clear is set, lines values are meaningless
	PointType	lineStart;
	PointType	lineStop;
} WhiteBoardRemoteDrawEvent;

typedef struct _BtDeviceInfoType
{
	BtLibDeviceAddressType	bdAddr;
	BtLibSocketRef 			connectionSocket;
} BtDeviceInfoType;
	
typedef struct _DeviceAddList
{
	BtLibDeviceAddressType	selectedDevices[kMaxDevices];
	UInt8					numSelectedDevices;
} DeviceAddList;


/***********************************************************************
 *   Entry Points
 ***********************************************************************/

void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon);
void BtLibL2CAPCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon);
void BtLibSDPCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon);
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags);


/***********************************************************************
 *   Global variables
 ***********************************************************************/

static Boolean			gIsMaster;
UInt16					gSavedAutoOff;

static UInt16 			gBtLibRefNum = 0;

BtLibSocketRef			gListenerSocket = kInvalidSocket;
BtLibSdpRecordHandle 	gSdpRecordH = 0;
BtDeviceInfoType		gDevices[kMaxDevices] ={ {{0}, kInvalidSocket}, 
											{{0}, kInvalidSocket}, {{0}, kInvalidSocket}, 
											{{0}, kInvalidSocket}, {{0}, kInvalidSocket}, 
											{{0}, kInvalidSocket}, {{0}, kInvalidSocket} };
UInt16  				gNumDevices = 0;
UInt16  				gNumConnections = 0;
UInt8   				gPendingLinks = 0;

// For adding devices to the piconet
DeviceAddList 			gSelectedDevicesList = { {{0},{0},{0},{0},{0},{0}, {0}}, 0};
static Char 			gBdAddrStr[kBdAddrStrSize];

/* WhiteBoard Data */
PointType 				gLastLocalPenLocation = {0,0};
Boolean					gPenIsDown = false;
UInt32  				gLastPenMoveTicks = 0;
WhiteBoardRemoteDrawEvent gRemoteDrawingQueue[kMaxQueueSize]; //the queue of events to send
UInt16					gRemoteQueueFisrtIndex = 0;
UInt16					gRemoteQueueLength = 0;
Boolean					gPendingQueueSend = false;
 
WinHandle 				gOffscreenWinH = 0; // Draw to this window so data is stored off screen

Char 					gStatus[100];		// String to store status information for display
UInt32					gTimeToClearError = 0;	// Errors are cleared after some elapsed period


/***********************************************************************
 *   Internal Functions
 ***********************************************************************/
 
static Boolean	MainFormHandleEvent(EventPtr eventP);
static Boolean	DrawingFormHandleEvent(EventPtr eventP);

static Err 		BluetoothInit(void);
static void 	BluetoothCleanup(void);
 
static Boolean	L2CapValidChannel(void);
static Boolean	L2CapSendPending(void);
static Err		L2CapConnect(UInt8 index, BtLibL2CapPsmType psm);
static Err		L2CapFindPsm(void);
static void		L2CapDisconnect(BtLibSocketRef socket);

static void		DiscoverAndAdd(void);
static void		AclCreateLinks(void);
static void 	AclCreateNextLink(void);
static void		AclHandleDisconnect(BtLibDeviceAddressTypePtr bdAddr);
static void		DestroyPiconet();

static Boolean  AddDrawEventToQueue(UInt8 clear, UInt16 startX, UInt16 startY, UInt16 endX, UInt16 endY);
static Int16  	IndexOfHeadOfQueue(void);
static Boolean	RemoveHeadOfQueue(UInt16 num);
static void 	ResetQueue(void);
static UInt16 	AttemptToSendNext_N_EnquedEvents(UInt16 num);
static void 	AttemptQueueSend(void);

static void		OffscreenDrawLine(Coord x1, Coord y1, Coord x2, Coord y2);
static void		ClearDrawArea(void);
static UInt8	FindDeviceIndex(BtLibDeviceAddressTypePtr bdAddrP);
static UInt8	FindSocketIndex(BtLibSocketRef socket);
static void		HandleL2CapDrawData( BtLibSocketEventType *sEvent);
static void		ChangeLabel( UInt16 labelID, const Char *newLabel);
static void		UpdateStatusDisplay();
static void 	StatusMsg(const char *formatStr, ...);
static void 	ErrorMsg(const char *formatStr, ...);

#define min(a, b) (((a) < (b)) ? (a) : (b))



/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: Event handler of the main form
 *
 * PARAMETERS:  The event
 *
 * RETURNED:    true if event was handled
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	Boolean		handled = true;
  	FormPtr		frmP;
	Err			error;

	switch (eventP->eType)
	{
		case menuEvent:
			if (eventP->data.menu.itemID == MainOptionsAboutWhiteboard)
			{
				MenuEraseStatus(0);	// Clear the menu status from the display.
				AbtShowAbout(kAppFileCreator);
				break;
			}
			break;

		case ctlSelectEvent:
			switch (eventP->data.ctlSelect.controlID)
			{
					
				case MainHostButton:
					gIsMaster = true;	
					error = BtLibPiconetCreate(gBtLibRefNum, true, true);
					if(!error)
						FrmGotoForm(DrawingForm); 
					else
						ErrorMsg("Failed to create piconet");
					break;		

				case MainConnectButton:
					gIsMaster = false;
					error = BtLibDiscoverSingleDevice(gBtLibRefNum, NULL, (BtLibClassOfDeviceType*)&kDeviceFilter, 1,
							 	&(gSelectedDevicesList.selectedDevices[0]), false, false);					
					if( !error)
					{
						gSelectedDevicesList.numSelectedDevices = 1;
						AclCreateLinks();
					}
					else
						ErrorMsg("Discovery result: 0x%hx", error);
					break;
			
			}
			break;
			
		case frmOpenEvent:	
        	frmP = FrmGetActiveForm();
			FrmDrawForm (frmP);
			gIsMaster = false;
			break;
			
		default:
			handled = false;
	}

   	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    DrawingFormHandleEvent
 *
 * DESCRIPTION: Event handler of the drawing form
 *
 * PARAMETERS:  The event
 *
 * RETURNED:    true if event was handled
 *
 ***********************************************************************/
static Boolean DrawingFormHandleEvent(EventPtr eventP)
{
	FormPtr     frmP = FrmGetActiveForm();
	ControlPtr  ctrlP;   
	Boolean     handled = true;
   	UInt16 		error;
  
	switch (eventP->eType)
	{
		case nilEvent:
			if (L2CapValidChannel())
			{
				UInt32 timeSinceLastMove = (TimGetTicks() - gLastPenMoveTicks)/SysTicksPerSecond();
				if (gPenIsDown && timeSinceLastMove >= kQueueSendTriggerSecs)
					gPendingQueueSend = true;
				if (gPendingQueueSend)
					AttemptQueueSend();
			}
			handled = false;
			break;
			
		case penDownEvent:
			if (L2CapValidChannel())
			{
				gPenIsDown = true;
				gLastLocalPenLocation.x = eventP->screenX;
				gLastLocalPenLocation.y = eventP->screenY;	
			}
			handled = false;
			break;
			
		case penUpEvent:
			if (L2CapValidChannel())
			{
				gPenIsDown = false;
				AttemptQueueSend();
			}
			handled = false;
			break;
			
		case penMoveEvent:
			if ( L2CapValidChannel() && gOffscreenWinH &&
				eventP->screenY < kDrawRect.topLeft.y + kDrawRect.extent.y)
			{
				gLastPenMoveTicks = TimGetTicks();

				OffscreenDrawLine(gLastLocalPenLocation.x, gLastLocalPenLocation.y, eventP->screenX, eventP->screenY);
								
				AddDrawEventToQueue( false, gLastLocalPenLocation.x, gLastLocalPenLocation.y, eventP->screenX, eventP->screenY);
				AttemptQueueSend();
				gLastLocalPenLocation.x = eventP->screenX;
				gLastLocalPenLocation.y = eventP->screenY;
			}
			handled = false;
			break;	
		   
	   case ctlSelectEvent:		   	
		   	if(gPendingLinks != 0)
		   		break; // No UI interaction while adding devices
		   		
			switch (eventP->data.ctlSelect.controlID)
			{
			
				case DrawingClearScreenButton:
					ClearDrawArea();
					AddDrawEventToQueue( true, 0,0,0,0);
					AttemptQueueSend();
					break;
					
				case DrawingLeaveButton:
					if (gIsMaster)
						DestroyPiconet();
					else
						L2CapDisconnect(gDevices[0].connectionSocket);
			   		break;
			   		
				case DrawingAddDevicesButton:
					DiscoverAndAdd();
					break;
					 
				case DrawingToggleLockButton: 
				{
					ctrlP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, DrawingToggleLockButton));
					if(!StrCompare(CtlGetLabel(ctrlP), kLockStr))
						BtLibPiconetLockInbound(gBtLibRefNum);
					else
						BtLibPiconetUnlockInbound(gBtLibRefNum, true);		
					break;
				}								
				  
        		default:
  	    	  		handled = false;
	     	   		break;
			}
			break;

     	case frmOpenEvent:
			if (!gIsMaster)
			{
				// We are a slave so no add or lock buttons
				FrmHideObject(frmP, FrmGetObjectIndex(frmP, DrawingAddDevicesButton));
				FrmHideObject(frmP, FrmGetObjectIndex(frmP, DrawingToggleLockButton));		
			}		
			gOffscreenWinH = WinCreateOffscreenWindow(kDrawRect.extent.x, kDrawRect.extent.y, genericFormat, &error);
			ErrFatalDisplayIf(gOffscreenWinH == 0,"Could not create offscreen window");
			FrmDrawForm (frmP);
			break;
			
		case frmCloseEvent:	
			WinDeleteWindow(gOffscreenWinH, false);				
		    handled = false;
		    break;
		
		case frmUpdateEvent:
			//Copy Offscreen window to the display
			FrmDrawForm(frmP);
			WinCopyRectangle(gOffscreenWinH, NULL, &kDrawRect,  0, 0, winPaint);
			break;
			
		default:
			handled = false;
			break;
   }
	return handled;
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:     BluetoothInit
 *
 * DESCRIPTION:  Find/Load/Open the lib and setup our listener
 *
 * PARAMETERS:   Nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 ***********************************************************************/
static Err BluetoothInit(void)
{
   Err error = errNone;
   BtLibSocketListenInfoType listenInfo;
    
	// Find the Library
	if( SysLibFind( btLibName, &gBtLibRefNum) )
	{
		// Load it if it can't be found	
		error = SysLibLoad( sysFileTLibrary , sysFileCBtLib, &gBtLibRefNum) ;
		ErrFatalDisplayIf(error, "Unable to load the Bluetooth stack");
	}

	error = BtLibOpen(gBtLibRefNum,false);
	if(error)
		return error;
	BtLibRegisterManagementNotification(gBtLibRefNum, BtLibMECallbackProc, 0);
	
	error = BtLibSocketCreate( gBtLibRefNum, &gListenerSocket, BtLibL2CAPCallbackProc, 0, btLibL2CapProtocol);
	ErrFatalDisplayIf(error, "L2CAP Socket Creation Failure");
	
	listenInfo.data.L2Cap.localPsm = BT_L2CAP_RANDOM_PSM;
	listenInfo.data.L2Cap.localMtu = kL2CapSocketMtu; 
	listenInfo.data.L2Cap.minRemoteMtu = kL2CapSocketMtu;
	error = BtLibSocketListen( gBtLibRefNum, gListenerSocket, &listenInfo);
	if(!error)
	{
		error = BtLibSdpServiceRecordCreate(gBtLibRefNum, &gSdpRecordH );
		if(!error)
		{
			BtLibSdpServiceRecordSetAttributesForSocket(gBtLibRefNum,  gListenerSocket, 
					(BtLibSdpUuidType*) &kWhiteboardUUID, 1, kAppBtName, StrLen(kAppBtName), gSdpRecordH);
			BtLibSdpServiceRecordStartAdvertising(gBtLibRefNum, gSdpRecordH);
		}
	}
	ErrFatalDisplayIf(error, "L2CAP Listen Failure");
	  
   return error;
}


/***********************************************************************
 *
 * FUNCTION:     BluetoothCleanup
 *
 * DESCRIPTION:  Destroy SDP record, close listener socket, 
 *               unregister callback and close lib
 *
 * PARAMETERS:   Nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 ***********************************************************************/
static void BluetoothCleanup(void)
{
	BtLibSdpServiceRecordDestroy(gBtLibRefNum, gSdpRecordH);	
	BtLibSocketClose(gBtLibRefNum, gListenerSocket);
	BtLibRegisterManagementNotification(gBtLibRefNum, 0, 0);
	BtLibClose(gBtLibRefNum);
}


/***********************************************************************
 *
 * FUNCTION:    BtLibMECallbackProc
 *
 * DESCRIPTION: Radio event callback
 *
 * PARAMETERS:  See BtLib.h
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon)
{
	switch(mEventP->event)
	{
	
		case btLibManagementEventRadioState:
			if (mEventP->status == btLibErrRadioInitialized)
				StatusMsg("Radio Inited");
			else
				ErrorMsg("Radio Failed");
			break;
			
		case btLibManagementEventPiconetCreated:
			break;
			
		case btLibManagementEventPiconetDestroyed:	
			FrmGotoForm(MainForm);
			break;
			
		case btLibManagementEventACLConnectOutbound:
			gPendingLinks--;				
			if (gIsMaster)
			{
				// Lock when outbound links are complete
				if(gPendingLinks == 0)
					BtLibPiconetLockInbound(gBtLibRefNum);
				else
					AclCreateNextLink();
			}
			else
			{
				// We should have connected to a master of a Piconet, check that we are really a slave
				// (a master/slave switch should have occured)
				BtLibConnectionRoleEnum role;
				Err error;
				error = BtLibLinkGetState(gBtLibRefNum, &mEventP->eventData.bdAddr, btLibLinkPref_LinkRole, &role, sizeof(role));
				if (error || role != btLibSlaveRole)
				{
					BtLibLinkDisconnect(gBtLibRefNum, &mEventP->eventData.bdAddr);
					break;
				}
			}
			// Intentional fall through
			
		case btLibManagementEventACLConnectInbound:			
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.bdAddr, gBdAddrStr, kBdAddrStrSize);				
			if(mEventP->status == btLibErrNoError)
			{
				MemMove(&gDevices[gNumDevices].bdAddr, &mEventP->eventData.bdAddr, sizeof(BtLibDeviceAddressType));
				gNumDevices++;
				StatusMsg("Link to %s Created", gBdAddrStr);
			}
			else
				ErrorMsg("Link to %s Failed", gBdAddrStr);
				
			if (gIsMaster && gPendingLinks == 0)
				L2CapFindPsm();
			break;
			
		case btLibManagementEventACLDisconnect:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.bdAddr, gBdAddrStr, 
				kBdAddrStrSize);		
			StatusMsg("%s Disc: %hx", gBdAddrStr, mEventP->status);
			AclHandleDisconnect(&mEventP->eventData.bdAddr);	  			
			break;	
			
		case btLibManagementEventAccessibilityChange:
			{
				FormPtr		frmP = FrmGetActiveForm();
				ControlPtr	ctrlP = NULL;
				if (FrmGetActiveFormID() == DrawingForm)
					ctrlP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, DrawingToggleLockButton));
				switch( mEventP->eventData.accessible)
				{
					case btLibNotAccessible:
						StatusMsg( "Not Accessible");
						if (ctrlP)
							CtlSetLabel(ctrlP, kUnlockStr);
						break;
					case btLibConnectableOnly:
						StatusMsg( "Connectable");
						if (ctrlP)
							CtlSetLabel(ctrlP, kLockStr);
						break;
					case btLibDiscoverableAndConnectable:
						StatusMsg( "Discoverable and Connectable");
						if (ctrlP)
							CtlSetLabel(ctrlP, kLockStr);
						break;
	
				}
			}
			break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    BtLibL2CAPCallbackProc
 *
 * DESCRIPTION: Handle L2CAP events
 *
 * PARAMETERS:  See BtLib.h
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
void BtLibL2CAPCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	switch(sEventP->event)
	{
			case btLibSocketEventConnectRequest:
				// Slave always accept master connection
				BtLibSocketRespondToConnection( gBtLibRefNum, sEventP->socket, true);
				StatusMsg( "Socket %i: Inbound Req Accepted",sEventP->socket); 
				break;
				
			case btLibSocketEventConnectedInbound:
				// Slave is connected by master
				if (sEventP->status == errNone)
				{
					gDevices[0].connectionSocket = sEventP->eventData.newSocket;
					gNumConnections++;	
					FrmGotoForm(DrawingForm);  		
					StatusMsg("Draw");
				}
				else
					ErrorMsg("Socket Error 0x%hx", sEventP->status);
				break;
				
			case btLibSocketEventConnectedOutbound:
				// Master just connected to a slave
				if (sEventP->status == errNone)
				{
					StatusMsg("Draw");
					gNumConnections++;
				}
				else
					ErrorMsg("Socket Error 0x%hx", sEventP->status);
				break;
				
			case btLibSocketEventDisconnected:
				// Master or slave lost a connection. Close socket and disconnect ACL
				gNumConnections--;
				L2CapDisconnect(sEventP->socket);
				StatusMsg( "Socket %i: Disconnect",sEventP->socket);
				break;
				
			case btLibSocketEventSendComplete:
				// Ignored since sending is done by polling
				break;
				
			case btLibSocketEventData:
				// Process a drawing event locally. The master also forwards it to slaves.
				HandleL2CapDrawData(sEventP);
				break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    BtLibSDPCallbackProc
 *
 * DESCRIPTION: Handle SDP events
 *
 * PARAMETERS:  see BtLib.h
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
void BtLibSDPCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	Err error;
	UInt8 index = 0;
	
	switch(sEventP->event)
	{
		case btLibSocketEventSdpGetPsmByUuid:
		{
			if(sEventP->status == btLibErrNoError)
			{	
				index = FindSocketIndex(sEventP->socket);				
				error = BtLibSocketClose(gBtLibRefNum, sEventP->socket);			
				if(error != btLibErrNoError)
					ErrorMsg("Could not close SDP socket");		
				gDevices[index].connectionSocket = kInvalidSocket;				
				//Found the psm so lets connect to the device
				L2CapConnect(index, sEventP->eventData.sdpByUuid.param.psm);		
			}
			else
			{
				// Treat failed search like a disconnect
				L2CapDisconnect(sEventP->socket);
			}
			break;
		}
	}
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    L2CapValidChannel
 *
 * DESCRIPTION: Check that we are connected
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    true if L2Cap channel is valid
 *
 ***********************************************************************/
static Boolean L2CapValidChannel(void)
{
	BtLibL2CapChannelIdType channel;
	Err	error;
	
	error = BtLibSocketGetInfo(gBtLibRefNum, gDevices[0].connectionSocket, btLibSocketInfo_L2CapChannel, 
		&channel, sizeof(channel));
	return (error == btLibErrNoError);
}


/***********************************************************************
 *
 * FUNCTION:    L2CapSendPending
 *
 * DESCRIPTION: Check if a send operation is pending on any active connection
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    true if a send operation is pending
 *
 ***********************************************************************/
static Boolean L2CapSendPending(void)
{
	Boolean sending = false;
	UInt16 i = 0;
	
	for(i = 0; i < gNumDevices && gDevices[i].connectionSocket != kInvalidSocket; i++)
	{
		BtLibSocketGetInfo(gBtLibRefNum, gDevices[i].connectionSocket, btLibSocketInfo_SendPending, 
			&sending, sizeof(sending)); 
		
		if(sending)
			return true;
	}
		
	return false;	
}


/***********************************************************************
 *
 * FUNCTION:    L2CapConnect
 *
 * DESCRIPTION: Connect an L2Cap socket
 *
 * PARAMETERS:  Device index and PSM to connect to
 *
 * RETURNED:    Error code
 *
 ***********************************************************************/
static Err L2CapConnect(UInt8 index, BtLibL2CapPsmType psm)
{
	Err error;
	BtLibSocketConnectInfoType connectInfo;
	
	connectInfo.data.L2Cap.remotePsm = psm;
	connectInfo.data.L2Cap.localMtu = kL2CapSocketMtu; 
	connectInfo.data.L2Cap.minRemoteMtu = kL2CapSocketMtu;
					
	if (gDevices[index].connectionSocket != kInvalidSocket)
		ErrorMsg("Trying to connect already valid socket");
			
	error = BtLibSocketCreate( gBtLibRefNum, &gDevices[index].connectionSocket, 
								BtLibL2CAPCallbackProc, 0, btLibL2CapProtocol);
	if( error == btLibErrNoError)
	{	
		connectInfo.remoteDeviceP = &gDevices[index].bdAddr;
	
		error = BtLibSocketConnect(gBtLibRefNum, gDevices[index].connectionSocket, &connectInfo);
		if (error == btLibErrPending) 
			StatusMsg( "Connecting... ");
		else
			ErrorMsg("Socket Connect failed");
	}
	else
		ErrorMsg("L2CAP Socket Creation Failure");
	
	return error;
}


/***********************************************************************
 *
 * FUNCTION:    L2CapFindPsm
 *
 * DESCRIPTION: Master uses SDP to find the Whiteboard psm for l2cap
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Error code
 *
 ***********************************************************************/
static Err L2CapFindPsm(void)
{
	Err error = errNone;
	UInt16 i;

	for(i = 0; i < gNumDevices; i++)
	{ 
		if(gDevices[i].connectionSocket == kInvalidSocket)
		{
			error = BtLibSocketCreate( gBtLibRefNum, &gDevices[i].connectionSocket, 
										BtLibSDPCallbackProc, 0, btLibSdpProtocol);
			if (!error)
			{
				// Use SDP to get the psm, the connection is made in the callback
				error = BtLibSdpGetPsmByUuid(gBtLibRefNum, gDevices[i].connectionSocket, &gDevices[i].bdAddr,
					(BtLibSdpUuidType*) &kWhiteboardUUID, 1);
			}
			if (error == btLibErrPending) 
				StatusMsg("Getting PSM... ");
			else 
				ErrorMsg("PSM retrieval failed, err 0x%hx", error);
		}
	}
	return error;
}


/***********************************************************************
 *
 * FUNCTION:    L2CapDisconnect
 *
 * DESCRIPTION: Close socket and disconnect ACL
 *
 * PARAMETERS:  The socket ref
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void L2CapDisconnect(BtLibSocketRef socket)
{
	Err error;
	UInt8 index;
			
	error = BtLibSocketClose(gBtLibRefNum, socket);
	
	index = FindSocketIndex(socket);
	gDevices[index].connectionSocket = kInvalidSocket;

	error = BtLibLinkDisconnect(gBtLibRefNum, &(gDevices[index].bdAddr));
			
	if(gNumConnections == 0)
		ResetQueue();		
}


#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    DiscoverAndAdd
 *
 * DESCRIPTION: Discover new devices and connect to those selected
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void DiscoverAndAdd(void)
{
	Err error;
	Boolean showLastDiscovery = false;
	BtLibClassOfDeviceType deviceFilter = (btLibCOD_ServiceAny | btLibCOD_Major_Computer | btLibCOD_Minor_Comp_Palm);
					
	// Discover some devices to add to the piconet, but loop if we exceed the maximum
	while(1)
	{					
		error = BtLibDiscoverMultipleDevices(gBtLibRefNum, NULL, NULL, &deviceFilter, 1, &(gSelectedDevicesList.numSelectedDevices), false, showLastDiscovery);		
		if(gSelectedDevicesList.numSelectedDevices <= (kMaxDevices - gNumDevices) || error)
			break;
			
		FrmCustomAlert(GeneralAlert, "The number of devices you selected would exceed the maximum allowed participants.  Please select again.",0,0);
		// If this discovery is wrong then we need to show the last discovery
		showLastDiscovery = true;
	} 
					
	if(error == btLibErrNoError)
	{			
		BtLibGetSelectedDevices(gBtLibRefNum, gSelectedDevicesList.selectedDevices, gSelectedDevicesList.numSelectedDevices, &(gSelectedDevicesList.numSelectedDevices));
		AclCreateLinks();
	}								
}


/***********************************************************************
 *
 * FUNCTION:    AclCreateLinks
 *
 * DESCRIPTION: Create an ACL link to 1 or more devices
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void AclCreateLinks(void)
{
	gPendingLinks =	gSelectedDevicesList.numSelectedDevices;	
	if(gPendingLinks != 0)
	{
		StatusMsg("Creating Link(s)");
		AclCreateNextLink();
	}
	else
		StatusMsg("Could not add devices to piconet");
	
}

/***********************************************************************
 *
 * FUNCTION:    AclCreateNextLink
 *
 * DESCRIPTION: Create the next link based on the gSelectedDevicesList and gPendingLinks
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AclCreateNextLink(void)
{
	Err  error;
	
	// Connect to the next device. In case it fails or it is already done, try with another device
	do
	{
		error = BtLibLinkConnect( gBtLibRefNum, 
			&(gSelectedDevicesList.selectedDevices[gSelectedDevicesList.numSelectedDevices - gPendingLinks]) );
		if(error != btLibErrPending)
		{
			gPendingLinks--;	
			BtLibAddrBtdToA(gBtLibRefNum, &(gSelectedDevicesList.selectedDevices[gSelectedDevicesList.numSelectedDevices - gPendingLinks]), gBdAddrStr, kBdAddrStrSize);
			StatusMsg( "ACL to %s failed, continuing", gBdAddrStr);
		}
	} while (error != btLibErrPending && gPendingLinks != 0);
			
}


/***********************************************************************
 *
 * FUNCTION:    AclHandleDisconnect
 *
 * DESCRIPTION: Handle ACL disconnection
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AclHandleDisconnect(BtLibDeviceAddressTypePtr bdAddr)
{
	UInt8 i;

	i = FindDeviceIndex(bdAddr);
	if (i < gNumDevices)
	{
		if (gDevices[i].connectionSocket != kInvalidSocket)
		{
			gNumConnections--;
			BtLibSocketClose(gBtLibRefNum, gDevices[i].connectionSocket);
		}
		
		if(i < gNumDevices-1)
		{
			// Compact array of device
			MemMove(&gDevices[i], &gDevices[i+1], (gNumDevices - i) * sizeof(BtDeviceInfoType));
		}
		
		gNumDevices--;
		gDevices[gNumDevices].connectionSocket = kInvalidSocket;
	}
		
	if(!gIsMaster)
		FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    DestroyPiconet
 *
 * DESCRIPTION: Close all sockets, ACL connections and destroy the piconet
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void DestroyPiconet()
{
	UInt16 i;
	for (i=0; i<gNumDevices;i++)
	{
		BtLibSocketClose(gBtLibRefNum, gDevices[i].connectionSocket);
		BtLibLinkDisconnect(gBtLibRefNum, &gDevices[i].bdAddr);
	}
	if (BtLibPiconetDestroy(gBtLibRefNum) == errNone)
		FrmGotoForm(MainForm);
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    AddDrawEventToQueue
 *
 * DESCRIPTION: Add a drawing event (a line) or a clear event to the queue
 *
 * PARAMETERS:  clear: if true, a clear event is enqueued, else a drawing event
 *              startX, startY: the origin point for drawing event
 *              destX, destY: the destination point for drawing event
 *
 * RETURNED:    true if event was added
 *
 ***********************************************************************/
static Boolean	AddDrawEventToQueue(UInt8 clear, UInt16 startX, UInt16 startY, UInt16 endX, UInt16 endY)
{
	UInt8	firstEmpty;

	// Check if the queue is full
	if ( gRemoteQueueLength == kMaxQueueSize )
	{
		FrmCustomAlert(GeneralAlert, "Queue Overflow", 0, 0);
		return false;
	}

	// Calculate the first empty slot
	firstEmpty = (gRemoteQueueFisrtIndex + gRemoteQueueLength) % kMaxQueueSize;
	gRemoteQueueLength++;
	
	gRemoteDrawingQueue[firstEmpty].clear = clear;
	if( !clear )
	{
		// Add the line data
		gRemoteDrawingQueue[firstEmpty].lineStart.x = startX;
		gRemoteDrawingQueue[firstEmpty].lineStart.y = startY;
		gRemoteDrawingQueue[firstEmpty].lineStop.x = endX;
		gRemoteDrawingQueue[firstEmpty].lineStop.y = endY;
	}
	return true;
}


/***********************************************************************
 *
 * FUNCTION:    IndexOfHeadOfQueue
 *
 * DESCRIPTION: Trivial
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    -1 if empty, else the head index
 *
 ***********************************************************************/
static Int16 IndexOfHeadOfQueue(void)
{
	if ( gRemoteQueueLength == 0 )
		return -1;
	else
		return gRemoteQueueFisrtIndex;
}


/***********************************************************************
 *
 * FUNCTION:	RemoveHeadOfQueue
 *
 * DESCRIPTION: Remove the n-th first events of the queue
 *
 * PARAMETERS:	num - the number of events to remove from head
 * 
 * RETURNED:	-1 if empty, else the index
 *
 ***********************************************************************/
static Boolean RemoveHeadOfQueue(UInt16 num)
{	
	// Make sure there are enough to remove
	if ( gRemoteQueueLength < num )
		return false;
	
	// Decrement the length
	gRemoteQueueLength = gRemoteQueueLength - num;
	
	// Update the head index
	gRemoteQueueFisrtIndex = (gRemoteQueueFisrtIndex + num) % kMaxQueueSize;
	
	return true;
}


/***********************************************************************
 *
 * FUNCTION:    ResetQueue
 *
 * DESCRIPTION: Reinitialise queue
 *
 * PARAMETERS:  nothing
 * 
 * RETURNED:   	nothing
 *
 ***********************************************************************/
static void ResetQueue(void)
{
	gPendingQueueSend = false;
	gRemoteQueueLength = 0;
	gRemoteQueueFisrtIndex = 0;
}


/***********************************************************************
 *
 * FUNCTION:    AttemptQueueSend
 *
 * DESCRIPTION: Attempt to send all queued events
 *
 * PARAMETERS:	Nothing
 * 
 * RETURNED:	Nothing
 *
 ***********************************************************************/
static void AttemptQueueSend(void)
{
	if( gRemoteQueueLength == 0)
		return;

	AttemptToSendNext_N_EnquedEvents(gRemoteQueueLength);
	
	gPendingQueueSend = (gRemoteQueueLength == 0);
}


/***********************************************************************
 *
 * FUNCTION:	AttemptToSendNext_N_EnquedEvents
 *
 * DESCRIPTION:	Tries to send the next 'num' events as an L2Cap Packet
 *
 * PARAMETERS:	n - the number of events to try to send
 *
 * RETURNED:	Number sent
 *
 ***********************************************************************/
static UInt16 AttemptToSendNext_N_EnquedEvents(UInt16 n)
{
	Err    		error;
	UInt16 		headIndex = IndexOfHeadOfQueue();
	UInt16		firstSegmentSize; 
	UInt16		secondSegmentSize = 0;
	UInt16		num;
	UInt16      i;
	Boolean		bAllSuccess = true; // Did all the sends succeed.  
	
	// Don't ask for more than there are and if the queue is empty, return
	num = min( n, gRemoteQueueLength);	
	if( num <= 0)
		return 0;
	
	// Check to see if data to send is wrapping around in the buffer,
	// if so, we will send the first segment and then recurse to send 
	// the second part
	if ( (headIndex + num) > kMaxQueueSize )
	{
		secondSegmentSize = (headIndex + num) % kMaxQueueSize;
	} 
	firstSegmentSize = num - secondSegmentSize;
	
	// Handle case where we might try to send too much
	if(sizeof(WhiteBoardRemoteDrawEvent) * firstSegmentSize > kL2CapSocketMtu)
	{
		// Put the excess in the second segment
		secondSegmentSize += firstSegmentSize - (kL2CapSocketMtu/sizeof(WhiteBoardRemoteDrawEvent));
		
		// Send as much as possible
		firstSegmentSize = kL2CapSocketMtu/sizeof(WhiteBoardRemoteDrawEvent);
	}

	// Make sure we are connected as either the server or the client
	if (!L2CapValidChannel())
	{
		ErrorMsg("L2Cap Session not established");
		return 0;
	}
	
	if(L2CapSendPending())
		return 0;
	for(i = 0; i < gNumDevices; i++)
	{
		error = BtLibSocketSend(gBtLibRefNum, gDevices[i].connectionSocket, (UInt8*) &gRemoteDrawingQueue[headIndex], 
			sizeof(WhiteBoardRemoteDrawEvent) * firstSegmentSize);
			
		if( error != btLibErrPending)
		{
			// Send failed.  Find out what happened.  
			BtLibDeviceAddressType device;
			Err error2;

			error2 = BtLibSocketGetInfo(gBtLibRefNum, gDevices[i].connectionSocket, 
				btLibSocketInfo_RemoteDeviceAddress, &device, sizeof(device));
						
			if(!error2)
			{
				BtLibAddrBtdToA(gBtLibRefNum, &device, gBdAddrStr, kBdAddrStrSize);	
				ErrorMsg( "Send to %s failed: 0x%hx", gBdAddrStr, error);
	  		}
  			return 0;
		}		
	}
		
	// Dequeue the DrawEvents we just sent
	RemoveHeadOfQueue(firstSegmentSize);
	
	// Recurse if needed
	if(secondSegmentSize)
		return firstSegmentSize + AttemptToSendNext_N_EnquedEvents(secondSegmentSize);

	return firstSegmentSize;
	
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    OffscreenDrawLine
 *
 * DESCRIPTION: Draw a line offscreen and then copy the offscreen window
 *              into the screen window
 *
 * PARAMETERS:  Line start and end.
 *
 * RETURNED:	Nothing
 *
 ***********************************************************************/
static void OffscreenDrawLine(Coord x1, Coord y1, Coord x2, Coord y2)
{
	WinHandle oldWinH;
 
  	if(gOffscreenWinH)
	{		
 		oldWinH = WinSetDrawWindow(gOffscreenWinH);
  		WinDrawLine( x1, y1, x2, y2);
  		WinSetDrawWindow(oldWinH);		
 		if(FrmGetActiveFormID() == DrawingForm)
  			WinCopyRectangle(gOffscreenWinH, NULL, &kDrawRect,  0, 0, winPaint);
	}

}


/***********************************************************************
 *
 * FUNCTION:    ClearDrawArea
 *
 * DESCRIPTION: Erase offscreen window and then copy it
 *              into the screen window
 *
 * PARAMETERS:  Line start and end.
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void ClearDrawArea(void)
{  			
	WinHandle oldWinH;
	
	if(gOffscreenWinH)
	{
		oldWinH = WinSetDrawWindow(gOffscreenWinH);	
		WinEraseWindow();		
		WinSetDrawWindow(oldWinH);		
  		if(FrmGetActiveFormID() == DrawingForm)
  			WinCopyRectangle(gOffscreenWinH, NULL, &kDrawRect,  0, 0, winPaint);
	}
}


/***********************************************************************
 *
 * FUNCTION:    FindDeviceIndex
 *
 * DESCRIPTION: Find a device in the array from its address
 *              and return its index
 *
 * PARAMETERS:	The BT address
 *
 * RETURNED:	The index
 *
 ***********************************************************************/
static UInt8 FindDeviceIndex(BtLibDeviceAddressTypePtr bdAddrP)
{
	UInt8 i;
	for(i = 0; i < gNumDevices; i++)
	{
		if(MemCmp(&gDevices[i].bdAddr, bdAddrP, sizeof(BtLibDeviceAddressType)) == 0)
			break;
	}	
	return i;
}


/***********************************************************************
 *
 * FUNCTION:    FindSocketIndex
 *
 * DESCRIPTION: Find a device in the array from its socket ref
 *              and return its index
 *
 * PARAMETERS:	The socket ref
 *
 * RETURNED:	The index
 *
 ***********************************************************************/
static UInt8 FindSocketIndex(BtLibSocketRef socket)
{
	UInt8 i;	
	for(i = 0; i < gNumDevices; i++)
	{
		if(gDevices[i].connectionSocket == socket)
			break;
	}
	return i;
}


/***********************************************************************
 *
 * FUNCTION:    HandleL2CapDrawData
 *
 * DESCRIPTION: Received a drawing event. Execute it locally.
 *              The master also forwards it to slave
 *
 * PARAMETERS:  The drawing event
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void HandleL2CapDrawData( BtLibSocketEventType *sEventP)
{
	WhiteBoardRemoteDrawEvent	*drawDataP;
	UInt16		i,numEvents;
			
  	// For each drawing events
  	numEvents = sEventP->eventData.data.dataLen / sizeof(WhiteBoardRemoteDrawEvent);
  	for( i = 0; i < numEvents; i++)
	{
  		drawDataP = ((WhiteBoardRemoteDrawEvent*) sEventP->eventData.data.data) + i;	
		// Execute it locally
  		if(drawDataP->clear)
  		 	ClearDrawArea();
	  	else
			OffscreenDrawLine( drawDataP->lineStart.x, drawDataP->lineStart.y, drawDataP->lineStop.x, drawDataP->lineStop.y);
		// Master also forwards it to slave
		if(gIsMaster)
  		{ 
			AddDrawEventToQueue(drawDataP->clear, drawDataP->lineStart.x, drawDataP->lineStart.y, 
				drawDataP->lineStop.x, drawDataP->lineStop.y);
  		}
    }
    
    if(gIsMaster)
    	AttemptQueueSend();
}


/***********************************************************************
 *
 * FUNCTION:    ChangeLabel
 *
 * DESCRIPTION: Utility function to change a label
 *				Note: The initial label (done in Constructor) MUST be
 *                    longer than any label you copy over it!!
 *
 * PARAMETERS:  labelID - id of the label to change
 *				char* - new label ptr.  label is copied & need not persist
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void ChangeLabel( UInt16 labelID, const Char *newLabel)
{

	FormPtr frm = FrmGetActiveForm();
	UInt16	labelIndex = FrmGetObjectIndex(frm, labelID);
	
	//Hide the label first to erase old text
	FrmHideObject(frm, labelIndex);
	
	//copy in the new string
	FrmCopyLabel(frm, labelID, newLabel);
	
	//now force the redraw
	FrmShowObject(frm, labelIndex);
}


/***********************************************************************
 *
 * FUNCTION:    UpdateStatusDisplay
 *
 * DESCRIPTION: Displays the status message on the screen.  This is called during a nilEvent
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void UpdateStatusDisplay()
{
	// Keep the error displayed for a while
	if (gTimeToClearError != 0)
	{
		if (TimGetSeconds() < gTimeToClearError)
			return;
		gTimeToClearError = 0;
	}
		
	switch (FrmGetActiveFormID())
	{
		case MainForm:
			ChangeLabel(MainStatusLabel, gStatus);
			break;
			
		case DrawingForm:
			ChangeLabel(DrawingStatusLabel, gStatus);
			break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    StatusMsg
 *
 * DESCRIPTION: Updates the status message string.  The screen is only updated occasionally
 *
 * PARAMETERS:  same as PrintF
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void StatusMsg(const char *formatStr, ...)
{
	_Palm_va_list args;

	va_start(args, formatStr);
	StrVPrintF(gStatus, formatStr, args);
	va_end(args);
	
	UpdateStatusDisplay();
}


/***********************************************************************
 *
 * FUNCTION:    ErrorMsg
 *
 * DESCRIPTION: Updates the error message string and display it.
 *
 * PARAMETERS:  same as PrintF
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void ErrorMsg(const char *formatStr, ...)
{
	_Palm_va_list args;

	va_start(args, formatStr);
	StrVPrintF(gStatus, formatStr, args);
	va_end(args);

	UpdateStatusDisplay();
	// Display the error for at least 5 seconds
	gTimeToClearError = TimGetSeconds() + 5;
}

#pragma mark -

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
		// Set the event handler for the form
		switch (formId)
		{
			case DrawingForm:
		      	FrmSetEventHandler(frmP, DrawingFormHandleEvent);
		        break;
			
			case MainForm:
				FrmSetEventHandler(frmP, MainFormHandleEvent);
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
 * PARAMETERS:  Nothing
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
		EvtGetEvent(&event, SysTicksPerSecond() / 10);

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
 * DESCRIPTION:  Initialize the application
 *
 * PARAMETERS:   Nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 ***********************************************************************/
static Err AppStart(void)
{
    gSavedAutoOff = SysSetAutoOffTime(0);

	FrmGotoForm(MainForm);
  
	return BluetoothInit();  
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Terminate the application.
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AppStop(void)
{ 	
	SysSetAutoOffTime(gSavedAutoOff);

	BluetoothCleanup();
  
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
 *
 * RETURNED:    Result of launch
 *
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	Err error;
	UInt32 btVersion; 
	
	// Check that Bluetooth components are intalled, which imply Palm OS 4.0 or upper
	if (FtrGet(btLibFeatureCreator, btLibFeatureVersion, &btVersion) != errNone)
	{
		// Alert the user if it's the active application
		if ((launchFlags & sysAppLaunchFlagNewGlobals) && (launchFlags & sysAppLaunchFlagUIApp))
			FrmAlert (MissingBtComponentsAlert);
		return sysErrRomIncompatible;
	}

	switch (cmd)
	{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error) 
				return error;			
			AppEventLoop();
			AppStop();
			break;

		default:
			break;

	}
	
	return 0;
}
