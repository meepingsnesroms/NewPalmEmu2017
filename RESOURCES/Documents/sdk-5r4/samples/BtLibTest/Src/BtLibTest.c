/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: BtLibTest.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *              Bluetooth library test tool
 *
 *****************************************************************************/

#include <PalmOS.h>
#include <BtLib.h>
#include <unix_stdarg.h>

#include "BtLibTestRsc.h"


/***********************************************************************
 *   Constants
 ***********************************************************************/

// {99ABEE90-122D-4242-9E8E-F47F7C5365E3}
static const BtLibSdpUuidType kL2capUUID = {btLibUuidSize128, 
{ 0x99, 0xab, 0xee, 0x90, 0x12, 0x2d, 0x42, 0x42, 0x9e, 0x8e, 
	0xf4, 0x7f, 0x7c, 0x53, 0x65, 0xe3 } };


// {7D97B361-6221-4459-9241-227576CC6AB8}
static const BtLibSdpUuidType kRfCommUUID = {btLibUuidSize128,
{ 0x7d, 0x97, 0xb3, 0x61, 0x62, 0x21, 0x44, 0x59, 0x92, 0x41, 
	0x22, 0x75, 0x76, 0xcc, 0x6a, 0xb8 } };


#define kAppFileCreator			'btlt'
#define kAppBtName 				"BtLibTest"

#define kMaxSizeLog				4096
#define kBdAddrStringSize	   	18
#define kL2capSocketMtu			100

#define kInvalidSocket			0xFFFF
#define kInvalidSdpRecord 		0

#define UNUSED(x) (x=x) // To avoid compiler warning about unused arguments


/***********************************************************************
 *   Global variables
 ***********************************************************************/

UInt16 					gBtLibRefNum = 0;

BtLibDeviceAddressType	gBdAddr;
Char					gBdAddrStr[kBdAddrStringSize];
Char 					gDataStr[kL2capSocketMtu];

BtLibSocketRef			gListenerSocket = kInvalidSocket;
BtLibSocketRef			gConnectionSocket = kInvalidSocket;
BtLibSocketRef			gSdpSocket = kInvalidSocket;

BtLibSdpRecordHandle	gSdpRecordH = kInvalidSdpRecord;

Boolean					gLibOpened = false;
Boolean					gCanDraw = true;


/***********************************************************************
 *   Internal Functions
 ***********************************************************************/

static void 	BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon);
static void 	BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon);
static void 	ChangeLabel(UInt16 labelID, const Char *newLabel);
static void 	UpdateScrollbar(void);
static void 	ScrollLines(UInt16 numLinesToScroll, WinDirectionType direction, Boolean update);
static void 	LogPrintF(const Char *format, ...);


/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the main form.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void MainFormInit()
{
	FormPtr frmP = FrmGetActiveForm();
	Err 	error;

	// Draw the form
	FrmDrawForm ( frmP);
	ChangeLabel(MainAddrLabel, "No Connection");
	MemSet(&gBdAddr, sizeof(gBdAddr), 0);
	UpdateScrollbar();
	
	// Find the Library
	if( SysLibFind( btLibName, &gBtLibRefNum) )
	{
		// load it if it can't be found	
		error = SysLibLoad( sysFileTLibrary , sysFileCBtLib, &gBtLibRefNum) ;
		if( error  )
			LogPrintF("Could not find BtLib");
		else
			LogPrintF("BtLib Loaded");
	}
	else
		LogPrintF("BtLib Found");
			
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
 ***********************************************************************/
static Boolean MainFormDoCommand(UInt16 command)
{
	Boolean handled = false;
	Err error = 0;

	switch (command)
	{
	
		/******************/
		/* Main Menu      */
		/******************/		
		case MainLibOpen:
			// Open the library
			if( !gLibOpened )
			{
				error = BtLibOpen(gBtLibRefNum,false);
				if(error)
					LogPrintF("BtLib Opened Failed: 0x%hx", error);
				else
				{
					BtLibRegisterManagementNotification(gBtLibRefNum, BtLibMECallbackProc, 0);
					LogPrintF("BtLib Opened");
					gLibOpened = true;
				}	
			}
			else
				LogPrintF("BtLib already opened");
			break;
			
		case MainLibOpenBg:
			// For OS use only
			LogPrintF("OS use only");
			break;
		case MainLibClose:
			// Close the library
			if( gLibOpened )
			{
				error = BtLibClose(gBtLibRefNum);
				if(error)
					LogPrintF("BtLib Close Failed: 0x%hx", error);
				else
				{
					LogPrintF("BtLib Closed");
					gLibOpened = false;
				}
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case MainLibSleep:
			// Sleep the library
			error = BtLibSleep(gBtLibRefNum);
			if(error)
				LogPrintF("BtLib Sleep Failed: 0x%hx", error);
			else
				LogPrintF("BtLib Sleep OK");
			break;
			
		case MainLibWake:
			// Wake the library
			error = BtLibWake(gBtLibRefNum);
			if(error)
				LogPrintF("BtLib Wake Failed: 0x%hx", error);
			else
				LogPrintF("BtLib Wake OK");
			break;
			
		/******************/
		/* ME Menu        */
		/******************/
		case MainMEInquiry:
			if ( gLibOpened )
			{
				error = BtLibStartInquiry(gBtLibRefNum, NULL, 20);
				if(error != btLibErrPending)
					LogPrintF("Start Inq Error: 0x%hx", error);
				else
					LogPrintF("Started Inquiry");
			}
			else
				LogPrintF("BtLib not open");
			break;

		case MainMECancelInquiry:
			if ( gLibOpened )
			{
				error = BtLibCancelInquiry(gBtLibRefNum);
				if(error != btLibErrPending)
					LogPrintF("Cancel Inq Error: 0x%hx", error);
				else
					LogPrintF("Canceling Inquiry...");
			}
			else
				LogPrintF("BtLib not open");
			break;

		case MainMEGetRole:
			if( gLibOpened)
			{
				BtLibConnectionRoleEnum role;
				
				error = BtLibLinkGetState(gBtLibRefNum, &gBdAddr, btLibLinkPref_LinkRole, &role, sizeof(role));
				
				if( error == btLibErrNoError )
					LogPrintF(role == btLibMasterRole ?  "Master" : "Slave");
				else 
					LogPrintF("Get Role Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break;

		case MainMEConnectACL:
			if( gLibOpened)
			{
				// Discover a device
				error = BtLibDiscoverSingleDevice(gBtLibRefNum, NULL, NULL, NULL, &gBdAddr, false, false);
				
				if(error == btLibErrCanceled)
				{
					LogPrintF("Discovery Canceled");
					break;
				}
				
				BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
				LogPrintF("Discovery Selected %s", gBdAddrStr);
				
				error = BtLibLinkConnect( gBtLibRefNum, &gBdAddr);
				if(error != btLibErrPending)
					LogPrintF("Link Create Error: 0x%hx", error);
				else
				{
					BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
					LogPrintF("Creating Link to %s...", gBdAddrStr);
				}
			}
			else
				LogPrintF("BtLib not open");
			break;

		case MainMEGetDeviceName:	
			if( gLibOpened)
			{
				BtLibFriendlyNameType	name;
				UInt8					nameBuff[btLibMaxDeviceNameLength];
				
				// Discover a device
				error = BtLibDiscoverSingleDevice(gBtLibRefNum, NULL, NULL, NULL, &gBdAddr, true, false);
				
				if(error == btLibErrCanceled)
				{
					LogPrintF("Discovery Canceled");
					break;
				}

				BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
				LogPrintF("Discovery Selected %s", gBdAddrStr);
					
				name.name = nameBuff;
				name.nameLength = btLibMaxDeviceNameLength;
					
				error = BtLibGetRemoteDeviceName( gBtLibRefNum,  &gBdAddr, &name, btLibCachedThenRemote);	
				if( error == btLibErrNoError)
					LogPrintF("Got name from cache: %s", name.name);
				else if (error == btLibErrPending)
				{
					BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
					LogPrintF("Getting name of %s...", gBdAddrStr);
				}
				else
					LogPrintF("Get Name Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case MainMEDisconnectACL:
			if( gLibOpened)
			{
				error = BtLibLinkDisconnect(gBtLibRefNum, &gBdAddr);
		
				if( error != btLibErrPending && error != btLibErrNoError)
					LogPrintF("Link Disc Error: 0x%hx", error);
				else
				{
					BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
					LogPrintF("Killing Link to %s...", gBdAddrStr);
				}
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case MainMEAuthenticateLink:
			if( gLibOpened)
			{
				error = BtLibLinkSetState(gBtLibRefNum, &gBdAddr, btLibLinkPref_Authenticated, NULL, 0);
				if( error != btLibErrPending && error != btLibErrNoError)
					LogPrintF("Auth. Error: 0x%hx", error);
				else
				{
					BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
					LogPrintF("Auth. Link to %s...", gBdAddrStr);
				}
				
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case MainMEToggleEncryption:
			if( gLibOpened )
			{
				Boolean encryption;
				
				error = BtLibLinkGetState(gBtLibRefNum, &gBdAddr, btLibLinkPref_Encrypted, &encryption, sizeof(Boolean));			

				if( error != btLibErrNoError)
					LogPrintF("Auth. Error: 0x%hx", error);
				else
				{
					encryption = !encryption;
					error = BtLibLinkSetState(gBtLibRefNum, &gBdAddr, btLibLinkPref_Encrypted, &encryption, sizeof(Boolean));
				
					if( error != btLibErrPending && error != btLibErrNoError)
						LogPrintF("Encryption Error: 0x%hx", error);
					else
					{
						BtLibAddrBtdToA(gBtLibRefNum, &gBdAddr, gBdAddrStr, kBdAddrStringSize);
						if(encryption)
							LogPrintF("Encrypt Link to %s...", gBdAddrStr);
						else
							LogPrintF("Unencrypt Link to %s...", gBdAddrStr);						
					}
				}			
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case MainMEDiscoverMulti:
			if( gLibOpened )
			{
				UInt8 numDevicesSelected;
				
				error = BtLibDiscoverMultipleDevices(gBtLibRefNum, NULL, NULL, NULL, 0, &numDevicesSelected, true, false);
				
				if(error == btLibErrCanceled)
					LogPrintF("Discovery Canceled");
				else if(numDevicesSelected == 0 )
					LogPrintF("Discover Multi: None Selected");	
				else
				{
					UInt8 i;
					BtLibDeviceAddressType* selectedDeviceArray;
					
					selectedDeviceArray = (BtLibDeviceAddressType*) MemPtrNew( numDevicesSelected * sizeof(BtLibDeviceAddressType));
					BtLibGetSelectedDevices(gBtLibRefNum, selectedDeviceArray, numDevicesSelected, &numDevicesSelected);
					LogPrintF("Discover Multi: %hu selected", numDevicesSelected);
					for( i = 0; i < numDevicesSelected; i++)
					{
						BtLibAddrBtdToA(gBtLibRefNum, &selectedDeviceArray[i], gBdAddrStr, kBdAddrStringSize);
						LogPrintF(gBdAddrStr);
					}
					MemPtrFree(selectedDeviceArray);
				}
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		/******************/
		/* L2CAP Menu     */
		/******************/
		case L2CAPListen:
			if( gLibOpened )
			{
				BtLibSocketListenInfoType listenInfo;
				
				error = BtLibSocketCreate( gBtLibRefNum, &gListenerSocket, BtLibSocketCallbackProc,
							0, btLibL2CapProtocol);
				if ( !error)
				{
					listenInfo.data.L2Cap.localPsm = BT_L2CAP_RANDOM_PSM;
					listenInfo.data.L2Cap.localMtu = kL2capSocketMtu; //Must be less then 672
					listenInfo.data.L2Cap.minRemoteMtu = kL2capSocketMtu;
					error = BtLibSocketListen( gBtLibRefNum, gListenerSocket, &listenInfo);
				}
				if( error != btLibErrNoError)
					LogPrintF("L2CAP Listen Error: 0x%hx", error);
				else
				{
					BtLibL2CapPsmType psm;
					
					BtLibSocketGetInfo(gBtLibRefNum, gListenerSocket,
						btLibSocketInfo_L2CapPsm,  &psm, sizeof(BtLibL2CapPsmType));
									
					LogPrintF("Socket %hu: Listening L2Cap %hx...", gListenerSocket, psm);
					
					error = BtLibSdpServiceRecordCreate(gBtLibRefNum, &gSdpRecordH );
					
					if(!error)
					{	
						error  = BtLibSdpServiceRecordSetAttributesForSocket(gBtLibRefNum,  gListenerSocket, 
							(BtLibSdpUuidType*) &kL2capUUID, 1, kAppBtName, StrLen(kAppBtName), gSdpRecordH);
						
						if(!error)
						{
							error = BtLibSdpServiceRecordStartAdvertising(gBtLibRefNum, gSdpRecordH);
						}
					}
					if( error == btLibErrNoError)
						LogPrintF("Listener Advertised via SDP");
					else
						LogPrintF("SDP Advertise Error: 0x%hx", error);
				}
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case L2CAPConnect:
			if( gLibOpened )
			{			
				if(gConnectionSocket != kInvalidSocket)
				{
					LogPrintF("Socket %hu: Already connected", gConnectionSocket);
					break;
				}
				
				error = BtLibSocketCreate( gBtLibRefNum, &gSdpSocket, BtLibSocketCallbackProc, 0, btLibSdpProtocol);
				if (!error)
				{
					// Use SDP to get the PSM, the connection is made in the callback
					error = BtLibSdpGetPsmByUuid(gBtLibRefNum, gSdpSocket, &gBdAddr,
						(BtLibSdpUuidType*) &kL2capUUID, 1);
				}
					
				if( error == btLibErrNoError || error == btLibErrPending)
					LogPrintF("SDP Socket %hu: Getting PSM...", gSdpSocket);
				else
					LogPrintF("SDP Query Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case L2CAPDisconnect:
			if( gLibOpened )
			{			
				error = BtLibSocketClose(gBtLibRefNum, gConnectionSocket);
				
				// Unlike ACL disconnects, closing a connected socket 
				// will not result in a callback, so mark the socket invalid now
				if( error == btLibErrNoError || error == btLibErrPending)
				{
					LogPrintF("Socket %hu: Closed", gConnectionSocket);
					gConnectionSocket = kInvalidSocket;
				}
				else
					LogPrintF("L2CAP Close Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break; 
			
		case L2CAPSend:
			if( gLibOpened )
			{
				FormType* frmP;
				Char* dialogResult;
				
				// Get the input string
				MenuEraseStatus(0);	// Clear the command bar if any
				frmP = FrmInitForm (InputForm);
				FrmSetFocus(frmP, FrmGetObjectIndex(frmP, InputDataField));
				
				// Display the input dialog
				if( FrmDoDialog (frmP) == InputCancelButton )
				{
					FrmDeleteForm (frmP);
					break;
				}
					
				dialogResult = FldGetTextPtr( FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, InputDataField)));
				
				// The the user input data, send it. Otherwise send the default string.
				if(dialogResult)
					StrNCopy(gDataStr, dialogResult, kL2capSocketMtu);
				else
					StrNCopy(gDataStr, "Testing 1 2 3", kL2capSocketMtu);
				
				FrmDeleteForm (frmP); // Free the form resources
				
				error = BtLibSocketSend(gBtLibRefNum, gConnectionSocket, (UInt8*) gDataStr, StrLen(gDataStr) + 1/*include NULL */);
				if( error == btLibErrPending)
					LogPrintF("Socket %hu: Sending...", gConnectionSocket);
				else
					LogPrintF("Socket %hu: Send Error: 0x%hx", gConnectionSocket,  error);
				
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		/******************/
		/* RfComm Menu    */
		/******************/
		case RFCOMMListen:
			if( gLibOpened )
			{			
				error = BtLibSocketCreate( gBtLibRefNum, &gListenerSocket, BtLibSocketCallbackProc, 0, btLibRfCommProtocol);
				if ( !error)
				{
					BtLibSocketListenInfoType listenInfo;
					listenInfo.data.RfComm.advancedCredit = 0;
					
					error = BtLibSocketListen( gBtLibRefNum, gListenerSocket, &listenInfo);
				}
				if( error != btLibErrNoError)
					LogPrintF("RFCOMM Listen Error: 0x%hx", error);
				else
				{
					BtLibRfCommServerIdType serviceID;
					
					BtLibSocketGetInfo(gBtLibRefNum, gListenerSocket, btLibSocketInfo_RfCommServerId,  &serviceID, sizeof(BtLibRfCommServerIdType));
					
					LogPrintF("Socket %hu: Listening RfComm %hu...", gListenerSocket, serviceID);
					
					error = BtLibSdpServiceRecordCreate(gBtLibRefNum, &gSdpRecordH );
					
					if(!error)
					{	
						error  = BtLibSdpServiceRecordSetAttributesForSocket(gBtLibRefNum,  gListenerSocket, 
							(BtLibSdpUuidType*) &kRfCommUUID, 1, kAppBtName, StrLen(kAppBtName), gSdpRecordH);
						
						if(!error)
						{
							error = BtLibSdpServiceRecordStartAdvertising(gBtLibRefNum, gSdpRecordH);
						}
					}
					if( error == btLibErrNoError)
						LogPrintF("Listener Advertised via SDP");
					else
						LogPrintF("SDP Advertise Error: 0x%hx", error);
				}
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case RFCOMMConnect:
			if( gLibOpened )
			{			
				if(gConnectionSocket != kInvalidSocket)
				{
					LogPrintF("Socket %hu: Already connected", gConnectionSocket);
					break;
				}
				
				error = BtLibSocketCreate( gBtLibRefNum, &gSdpSocket, BtLibSocketCallbackProc, 0, btLibSdpProtocol);
				if (!error)
				{
					// Use SDP to get the server channel number, the connection is made in the callback
					error = BtLibSdpGetServerChannelByUuid(gBtLibRefNum, gSdpSocket, &gBdAddr,
						(BtLibSdpUuidType*) &kRfCommUUID, 1);
				}
					
				if( error == btLibErrNoError || error == btLibErrPending)
					LogPrintF("SDP Socket %hu: Getting Channel...", gSdpSocket);
				else
					LogPrintF("SDP Query Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case RFCOMMDisconnect:	
			if( gLibOpened )
			{	
				error = BtLibSocketClose(gBtLibRefNum, gConnectionSocket);
				
				// Unlike ACL disconnects, closing a connected socket 
				// will not result in a callback, so mark the socket invalid now
				if( error == btLibErrNoError || error == btLibErrPending)
				{
					LogPrintF("Socket %hu: Closed", gConnectionSocket);
					gConnectionSocket = kInvalidSocket;
				}
				else
					LogPrintF("RFCOMM Close Error: 0x%hx", error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case RFCOMMSend:
			if( gLibOpened )
			{
				FormType* frmP;
				Char* dialogResult;
				
				// Get the input string
				MenuEraseStatus(0);	// Clear the command bar if any
				frmP = FrmInitForm (InputForm);
				FrmSetFocus(frmP, FrmGetObjectIndex(frmP, InputDataField));
				
				// Display the input dialog
				if( FrmDoDialog (frmP) == InputCancelButton )
				{
					FrmDeleteForm (frmP);
					break;
				}
				
				dialogResult = FldGetTextPtr( FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, InputDataField)));
				
				// If the user input data, send it. Otherwise send the default string.
				if(dialogResult)
					StrNCopy(gDataStr, dialogResult, kL2capSocketMtu);
				else
					StrNCopy(gDataStr, "Testing 1 2 3", kL2capSocketMtu);
				
				FrmDeleteForm (frmP); // Free the form resources
				
				error = BtLibSocketSend(gBtLibRefNum, gConnectionSocket, 
					(UInt8*) gDataStr, StrLen(gDataStr) + 1/*include NULL */);
				if( error == btLibErrPending)
					LogPrintF("Socket %hu: Sending...", gConnectionSocket);
				else
					LogPrintF("Socket %hu: Send Error: 0x%hx", gConnectionSocket, error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		case RFCOMMAdvanceCredit:
			if( gLibOpened )
			{
				// Credit advance is cumulative, so advance one credit at a time
				error = BtLibSocketAdvanceCredit(gBtLibRefNum, gConnectionSocket, 1);
				if( !error)
					LogPrintF("Socket %hu: Advanced 1 credit", gConnectionSocket);
				else
					LogPrintF("Socket %hu: Adv Credit Error: 0x%hx", gConnectionSocket, error);
			}
			else
				LogPrintF("BtLib not open");
			break;
			
		/******************/
		/* Service Menu   */
		/******************/
		case ServToggleMapButtons:
		{
			LogPrintF("OS use only");
			handled = true;
			break;
		}
			
		case ServServRegisterNotif:
		{
			LogPrintF("OS use only");
			handled = true;
			break;
		}
			
		case ServAbout:		
			MenuEraseStatus(0);
			AbtShowAbout(kAppFileCreator);
			handled = true;
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
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	switch (eventP->eType) 
	{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

		case frmOpenEvent:	
			MainFormInit();
			return true;

		case frmCloseEvent:
		{
			FormPtr	frmP = FrmGetFormPtr(MainForm);
			Char *txtP = FldGetTextPtr(FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, MainLogField)));
			if (txtP)
				MemPtrFree(txtP);
			return false;
		}
			
		case sclRepeatEvent:
		{
			Int16 val = eventP->data.sclRepeat.newValue - eventP->data.sclRepeat.value;
			if (val > 0)
				ScrollLines((UInt16)val,  winDown, false);
			else
				ScrollLines((UInt16)-val, winUp,   false);
			return true;
		}
			
		case keyDownEvent:
			switch (eventP->data.keyDown.chr)
			{
				case pageUpChr:
					ScrollLines(0, winUp, true);
					return true;
				case pageDownChr:
					ScrollLines(0, winDown, true);
					return true;
				default:
					return false;
			}		

		default:
			return false;
			
	}
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
 * RETURNED:    true if the event was handled and should not be passed
 *              to a higher level handler.
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventPtr eventP)
{
	if (eventP->eType == frmLoadEvent)
	{
		UInt16	formId;
		FormPtr	formP;
		// Load the form resource.
		formId = eventP->data.frmLoad.formID;
		formP = FrmInitForm(formId);
		FrmSetActiveForm(formP);
		// And set its event handler
		if (formId == MainForm)
			FrmSetEventHandler(formP, MainFormHandleEvent);
		return true;
	}
	else 
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
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;

	do
	{
		EvtGetEvent(&event, evtWaitForever);
		
		// Enable drawing if the main form is active, disable if another
		// form or menu is opened on top
		if (event.eType == winExitEvent &&
			event.data.winExit.exitWindow == (WinHandle) FrmGetFormPtr(MainForm))
			gCanDraw = false;
		else if (event.eType == winEnterEvent &&
				 event.data.winEnter.enterWindow ==  (WinHandle) FrmGetFormPtr(MainForm))
		{
			gCanDraw = true;
			LogPrintF(NULL);
		}
		
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
 * DESCRIPTION:  Initialize the application. Goto the main form.
 *
 * PARAMETERS:   Nothing
 *
 * RETURNED:     Nothing
 *
 ***********************************************************************/
static void AppStart(void)
{
	FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Terminate the application. Close the library.
 *
 * PARAMETERS:  Nothing
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void AppStop(void)
{
	Err err = 0;

	// Close the library
	if(gLibOpened)
	{
		err = BtLibClose(gBtLibRefNum);
	}
		
	// Close all the opened forms.
	FrmCloseAllForms ();
		
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
	UInt32	btVersion;
	UNUSED(cmdPBP);

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
			AppStart();
			AppEventLoop();
			AppStop();
			return errNone;

		default:
			return errNone;

	}	
}


#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    BtLibSocketCallbackProc
 *
 * DESCRIPTION: Handle RfComm and SDP events.
 *
 * PARAMETERS:  See BtLib.h 
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	Err error;
	UNUSED(refCon);
		
	switch(sEventP->event)
	{
	
		case btLibSocketEventSdpGetServerChannelByUuid:
			if(sEventP->status == btLibErrNoError)
			{	
				BtLibSocketConnectInfoType connectInfo;
				
				LogPrintF("Retrieved Channel: %hu", (int) sEventP->eventData.sdpByUuid.param.channel);
			
				error = BtLibSocketClose(gBtLibRefNum, gSdpSocket);
			
				// Unlike ACL disconnects, closing a connected socket 
				// will not result in a callback, so mark the socket invalid now
				if( error == btLibErrNoError || error == btLibErrPending)
					gSdpSocket = kInvalidSocket;
				else
					LogPrintF("SDP Socket Close Error: 0x%hx", error);
			
				if(gConnectionSocket != kInvalidSocket)
				{
					LogPrintF("Socket %hu: Already connected", gConnectionSocket);
					break;
				}
			
				error = BtLibSocketCreate( gBtLibRefNum, &gConnectionSocket, BtLibSocketCallbackProc, 0, 
					btLibRfCommProtocol);
				
				if (!error)
				{
					connectInfo.remoteDeviceP = &gBdAddr;
					connectInfo.data.RfComm.remoteService = sEventP->eventData.sdpByUuid.param.channel;
					connectInfo.data.RfComm.maxFrameSize = BT_RF_DEFAULT_FRAMESIZE; 
					connectInfo.data.RfComm.advancedCredit = 0;
					error = BtLibSocketConnect( gBtLibRefNum,  gConnectionSocket, &connectInfo);
				}
				
				if( error == btLibErrNoError || error == btLibErrPending)
				{
					LogPrintF("Socket %hu: connecting...", gConnectionSocket);
				}
				else
					LogPrintF("RFCOMM Connect Error: 0x%hx", error);
			}
			else
				LogPrintF("SDP Get Channel error: 0x%hx", sEventP->status);
			break;
			
		case btLibSocketEventSdpGetPsmByUuid:
			if(sEventP->status == btLibErrNoError)
			{	
				BtLibSocketConnectInfoType connectInfo;
				
				LogPrintF("Retrieved PSM: %hx", sEventP->eventData.sdpByUuid.param.psm);
			
				error = BtLibSocketClose(gBtLibRefNum, gSdpSocket);
			
				// Unlike ACL disconnects, closing a connected socket 
				// will not result in a callback, so mark the socket invalid now
				if( error == btLibErrNoError || error == btLibErrPending)
					gSdpSocket = kInvalidSocket;
				else
					LogPrintF("SDP Socket Close Error: 0x%hx", error);
			
				if(gConnectionSocket != kInvalidSocket)
				{
					LogPrintF("Socket %hu: Already connected", gConnectionSocket);
					break;
				}
			
				error = BtLibSocketCreate( gBtLibRefNum, &gConnectionSocket, BtLibSocketCallbackProc, 0, btLibL2CapProtocol);
				if (!error)
				{
					connectInfo.remoteDeviceP = &gBdAddr;
					connectInfo.data.L2Cap.remotePsm = sEventP->eventData.sdpByUuid.param.psm;
					connectInfo.data.L2Cap.localMtu = kL2capSocketMtu; //Must be less then 672
					connectInfo.data.L2Cap.minRemoteMtu = kL2capSocketMtu;
					error = BtLibSocketConnect( gBtLibRefNum,  gConnectionSocket, &connectInfo);
				}
				
				if( error == btLibErrNoError || error == btLibErrPending)
				{
					LogPrintF("Socket %hu: connecting...", gConnectionSocket);
				}
				else
					LogPrintF("L2CAP Connect Error: 0x%hx", error);
			}
			else
				LogPrintF("SDP Get Channel error: 0x%hx", sEventP->status);
			break;
						
		case btLibSocketEventConnectRequest:
			// Allow only one connection at a time
			if( gConnectionSocket == kInvalidSocket)
			{
				BtLibSocketRespondToConnection( gBtLibRefNum, sEventP->socket, true);
				LogPrintF("Socket %hu: Inbound Req Accepted",sEventP->socket); 
			}
			else
			{
				BtLibSocketRespondToConnection( gBtLibRefNum, sEventP->socket, false);
				LogPrintF("Socket %hu: Inbound Req Denied",sEventP->socket);
			}
			break;

		case btLibSocketEventConnectedInbound:
			gConnectionSocket = sEventP->eventData.newSocket;
			LogPrintF("Socket %hu: New Inbound Conn", gConnectionSocket);
			break;

		case btLibSocketEventConnectedOutbound:
			gConnectionSocket = sEventP->socket;
			LogPrintF("Socket %hu: Outbound Conn", gConnectionSocket);
			break;

		case btLibSocketEventDisconnected:
			LogPrintF("Socket %hu: Disconnect",sEventP->socket);
			// Disconnected sockets should be closed
			BtLibSocketClose(gBtLibRefNum, sEventP->socket);
			gConnectionSocket = kInvalidSocket;
			break;

		case btLibSocketEventSendComplete:
			LogPrintF("Socket %hu: Send Complete",sEventP->socket);
			break;
			
		case btLibSocketEventData:
			LogPrintF("Socket %hu: Data: %s",sEventP->socket, 
			          sEventP->eventData.data.data);
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
static void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon)
{
	UNUSED(refCon);
	
	switch(mEventP->event)
	{
		case btLibManagementEventRadioState:
			if (mEventP->status == btLibErrRadioInitialized)
				LogPrintF("Radio Init");
			else if (mEventP->status == btLibErrRadioSleepWake)
				LogPrintF("Power Off");
			else
				LogPrintF("Radio Failed");
			break;
			
		case btLibManagementEventInquiryResult:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.inquiryResult.bdAddr, gBdAddrStr, kBdAddrStringSize);
			LogPrintF("%s", gBdAddrStr);
			break;
			
		case btLibManagementEventInquiryComplete:
			LogPrintF("Inquiry complete");
			break;
			
		case btLibManagementEventInquiryCanceled:
			LogPrintF("Inquiry canceled");
			break;
			
		case btLibManagementEventACLConnectOutbound: // Intentional fall through
		case btLibManagementEventACLConnectInbound:
			MemMove(&gBdAddr, &mEventP->eventData.bdAddr, sizeof(BtLibDeviceAddressType));
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.bdAddr, gBdAddrStr, kBdAddrStringSize);
			if(mEventP->status == btLibErrNoError)
			{
				LogPrintF("Link to %s Established", gBdAddrStr);
				ChangeLabel(MainAddrLabel, gBdAddrStr);
			}			
			else
				LogPrintF("Link to %s Failed", gBdAddrStr);
			break;
			
		case btLibManagementEventAuthenticationComplete:
			if (mEventP->status == btLibErrNoError)
				LogPrintF("Authenticate complete");
			else
				LogPrintF("Authenticate Failed: 0x%hx", mEventP->status);
			break;
			
		case btLibManagementEventEncryptionChange:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.encryptionChange.bdAddr, gBdAddrStr, kBdAddrStringSize);		
			if (mEventP->status == btLibErrNoError)
			{
				if(mEventP->eventData.encryptionChange.enabled)
					LogPrintF("%s Encrypted", gBdAddrStr);
				else
					LogPrintF("%s Not Encrypted", gBdAddrStr);					
			}
			else
				LogPrintF("Encryption Failed: 0x%hx", mEventP->status);
			break;
			
		case btLibManagementEventACLDisconnect:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.bdAddr, gBdAddrStr, kBdAddrStringSize);
			LogPrintF("Disconnected from %s, reason: 0x%hx", gBdAddrStr, mEventP->status);
			ChangeLabel(MainAddrLabel, "No Connection");
			MemSet(&gBdAddr, sizeof(gBdAddr), 0);
			break;
				
		case btLibManagementEventNameResult:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.nameResult.bdAddr, gBdAddrStr, kBdAddrStringSize);		
			if(mEventP->status == btLibErrNoError)
				LogPrintF("%s is Remote name of %s", mEventP->eventData.nameResult.name.name, gBdAddrStr);
			else
				LogPrintF("Get Remote Name to %s failed: 0x%hx", gBdAddrStr, mEventP->status);
			break;
			
		case btLibManagementEventRoleChange:
			BtLibAddrBtdToA(gBtLibRefNum, &mEventP->eventData.roleChange.bdAddr, gBdAddrStr, kBdAddrStringSize);		
			if(mEventP->eventData.roleChange.newRole == btLibMasterRole)
				LogPrintF("Became Master of %s", gBdAddrStr);
			else
				LogPrintF("Became Slave of %s", gBdAddrStr);
			break;
			
		case btLibManagementEventAccessibilityChange:
			switch( mEventP->eventData.accessible)
			{
				case btLibNotAccessible:
					LogPrintF("Not Accessible");
					break;
				case btLibConnectableOnly:
					LogPrintF("Connectable");
					break;
				case btLibDiscoverableAndConnectable:
					LogPrintF("Discoverable and Connectable");
					break;
			}
			break;
	}
	
}


#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    ChangeLabel
 *
 * DESCRIPTION: Utility function to change a label
 *				Note: The initial label (done in Constructor) MUST be
 *                    longer than any label you copy over it!!
 *
 * PARAMETERS:  label Id and new text
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void ChangeLabel(UInt16 labelID, const Char *newLabel)
{
	FormPtr frm = FrmGetActiveForm();
	UInt16	labelIndex = FrmGetObjectIndex(frm, labelID);
	
	//Hide the label first to erase old text
	FrmHideObject(frm, labelIndex);
	//Copy in the new string
	FrmCopyLabel(frm, labelID, newLabel);
	//Now force the redraw
	FrmShowObject(frm, labelIndex);
}


/***********************************************************************
 *
 * FUNCTION:    UpdateScrollbar
 *
 * DESCRIPTION: Update the scroll bar related to the log field.
 *
 * PARAMETERS:  None
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void UpdateScrollbar(void)
{
	UInt16 			currentPosition;
	UInt16 			textHeigth;
	UInt16 			fieldHeigth;
	UInt16			maxValue;
	FormPtr			frmP = FrmGetFormPtr(MainForm);
	ScrollBarPtr	scrollP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, MainLogScrollBar));
	FieldPtr		fldP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, MainLogField));
	
	FldGetScrollValues(fldP, &currentPosition, &textHeigth, &fieldHeigth);
	if (textHeigth > fieldHeigth)
		maxValue = textHeigth - fieldHeigth;
	else if (currentPosition)
		maxValue = currentPosition;
	else
		maxValue = 0;
		
	SclSetScrollBar(scrollP, (Int16)currentPosition, 0, (Int16)maxValue, (Int16)(fieldHeigth - 1));
}


/***********************************************************************
 *
 * FUNCTION:    ScrollLines
 *
 * DESCRIPTION: Scroll log field and update its scroll bar.
 *
 * PARAMETERS:  number of lines and direction
 *              0 lines means a page scroll
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void ScrollLines(UInt16 numLinesToScroll, WinDirectionType direction, Boolean update)
{
	FormPtr			frmP = FrmGetFormPtr(MainForm);
	FieldPtr		fldP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, MainLogField));

	if (numLinesToScroll == 0)
		numLinesToScroll = FldGetVisibleLines(fldP) - 1;
	FldScrollField(fldP, numLinesToScroll, direction);
	if (update || (FldGetNumberOfBlankLines(fldP) && direction == winUp))
		UpdateScrollbar();
}


/***********************************************************************
 *
 * FUNCTION:    LogPrintF
 *
 * DESCRIPTION: Add text to the log field, max 128 chars
 *
 * PARAMETERS:  same as StrPrintF
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void LogPrintF(const Char *format, ...)
{
	static UInt16 	gLenConv = 0;
	UInt16			lenMess;
	va_list			args;
	Char			mess[128];
	FormPtr			frmP = FrmGetFormPtr(MainForm);
	FieldPtr		fldP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, MainLogField));
	Char *			txtP = FldGetTextPtr(fldP);

	// The first time, allocate the field with the maximum supported field size
	if (!txtP)
	{
		txtP = MemPtrNew(kMaxSizeLog);
		gLenConv = FldGetVisibleLines(fldP);
		MemSet(txtP, gLenConv, '\n');
		txtP[gLenConv] = '\0';
	}

	// Format the message, if any, and append it to the field
	if (format)
	{
		// Format the message
		va_start(args, format);
		StrVPrintF(mess, format, args);
		va_end(args);
		
		// When field does not have enough room, keep only last half of the conversation
		// Move the last half in replacement of first half
		lenMess = (UInt16) StrLen(mess) + 1;
		if (gLenConv + lenMess >= kMaxSizeLog)
		{
			gLenConv >>= 1;
			MemMove(txtP, txtP + gLenConv + (gLenConv & 1), gLenConv );
		}
	
		// Append a carriage return and update length
		StrPrintF(txtP + gLenConv, "\n%s", mess);
		gLenConv += lenMess;
		FldSetTextPtr(fldP, txtP);
	}
	
	// If drawing is enabled (no menu or form is opened on top of the field)
	if (gCanDraw)
	{	
		// Redraw field and scroll down to the bottom
		FldRecalculateField(fldP, false);
		FldScrollField(fldP, (UInt16) kMaxSizeLog, winDown);
		FldDrawField(fldP);
		UpdateScrollbar();
	}
}
