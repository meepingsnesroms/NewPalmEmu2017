/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: BtPiconet.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *		Main file for BtPiconet sample application
 *
 *****************************************************************************/

/*	What  BtPiconet does:
	===================

	BtPiconet show the three  ways that a Piconet can be formed:
	1. The master waits passively for slaves to connect
	2. The master finds slaves and brings them into the Piconet
	3. While a Piconet is up, the master can discover additional slaves

	Once connected, the master sends a "ping" packet to all the slaves.
	The ping packet contains information on the status of the other slaves.  
	The slave immediately responds to the ping.  
	When the master receives the response, it advances the animation one movement.

	How to use BtPiconet:
	===================
	From the main screen, decide if the Palm device is a master or a slave, and tap the appropriate button.
	On the "Action" screen, the slaves only have one option; tapping "Leave" makes them leave the Piconet.
	The Master has 3 buttons: "Leave" disconnets all the slaves and returns to the initial screen;
	"Add" adds more slaves to the Piconet;
	"Lock" or "Unlock" allows or prevents other slaves from joining the Piconet.
	Having the Piconet locked will typically result in a 10% performance improvement over an unlocked Piconet.
*/

// In this sample, the ACL connection can be initiated by either master or slave.  Slaves
// create L2CAP listening sockets and advertise them.  The master does a SDP query and
// L2CAP connection after the ACL link is up.  It is possible for the slaves to initiate
// the L2CAP connection; the advantages and disadvantages are discussed here:
// 
// 1. Master is "passive" and slaves initiate the L2CAP connection
// ===============================================================
// The Master can create a single L2CAP listening socket, and advertise it using SDP.  There is
// no need for the slave to do this.  After the ACL connection has been established, the
// slaves makes a SDP query to find the L2CAP PSM that the master is listening on.  Once it
// has this PSM value, it can do a L2CAP socket connect to the master.  When a slave connects
// to the master, a socket is "spawned" off the original listening socket. So, in a Piconet
// with 7 slaves (and 1 master), the master would have 1 listening socket and 7 "spawned"
// sockets.  Each slave would only have 1 socket (conected to the master). 
//
// Problem: While the master is trying to establish connections with additional slaves, the
// slaves are trying to do SDP queries and initiate L2CAP connections.  In theory, the Bluetooth
// radios should be able to handle this - but it doesn't seem to work!  So, this architecture
// will only work if the master waits passively for slaves to join the Piconet, or the master
// only discovers and joins one slave at a time.  If you can accept these limitations, then 
// you can use this method.
//
// 2. Master is "active" and can initiate L2CAP connects to multiple slaves at the same time
// =========================================================================================
// This is what this application does.  When connecting to multiple slaves, the master 
// waits until ALL the ACL conections have been established BEFORE initiating any SDP queries
// to the slaves.  Here each slave has to create a listening socket and advertise it using SDP.
// So, in a Piconet with 7 slaves (and 1 master), the master has no listening sockets and
// 7 L2CAP sockets.  Each slave will have a listening socket and a "spawned" socket that was
// created when the master connected to it.  This architecture allows for both a "passive" and
// "active" master.
//
//
// You cannot have sockets between slaves.  There is currently a maximum of 16 sockets - so you
// could have 2 sockets to each slave, or 1 to each slave except the last which could have
// 9.  Very flexible!
//
// Data can flow from master to slave, and slave to master in a single socket.  Stated differently,
// all sockets are bi-directional.
//
// L2CAP sockets (which this sample uses) differ from RFCOMM sockets in 1 important way: any
// number of sockets can be "spawned" from a single listening L2CAP socket.  Not so with RFCOMM
// sockets which can only accept one inbound connection per socket.  Also, once a listening RFCOMM
// socket has received an inbound connection you still have just one socket!  However, there's
// less protocol overhead when using L2CAP (RFCOMM actually rides on top of L2CAP).
//
// If you try to close the original L2CAP socket while an "spawned" inbound connection is still
// active you'll get a BUSY error.  You cannot close the listening socket while there are any
// "spawned" sockets still open!  So, how do you prevent others from connecting to the socket?
// Easy - you just stop advertising it (via SDP)!  In this application this is of no concern to
// us; Once the slave is part of the Piconet it can't be discovered nor connected to and there
// can't be socket connections between slaves.
//
// Callbacks are sometimes (all the time?) difficult to follow, so here is an outline of 
// what happens, and the order it happens in:
//
// Slave creates listening socket (can be done before any ACL connections are in place)
// Slave creates and advertises SDP entry (can be done before ACL connections are in place)
// <--- ACL connection initiated by either master or slave --->
// Master creates SDP socket (BtLibSocketCreate)
// Master initiates PSM retrieval using SDP (BtLibSdpGetPsmByUUID) (*1)
// Master receives callback - btLibSocketEventSdpGetPsmByUUID
// Master closes SDP socket (BtLibSocketClose)
// Master creates L2CAP socket (BtLibSocketCreate)
// Master initiates L2CAP connection using retrieved PSM (BtLibSocketConnect) (*2)
// Master receives callback - btLibSocketEventConnectedOutbound (*3)
// Connection up!  Send and receive possible
//
// (*1) Slave is unaware that the master is querying its SDP database!
// (*2) Slave receives callback - btLibSocketEventConnectRequest
//      Slave then accepts or rejects the connection (BtLibSocketConnectionRespond)
// (*3) Slave receives callback - btLibSocketEventConnectedInbound
//      Connection is up! Send and receive possible
//
// Passing data:
// To send data, call BtLibSocketSend.  When the data has been sent, you will receive a
// callback (btLibSocketEventSendComplete).  There can only be one outstanding data packet
// per socket.  To receive data, you will receive a callback too (btLibSocketEventData).
//
// The other often asked question - "How much processing can you do in a callback?".  The
// Bluetooth stack is timing sensitive, so not much.  It's difficult to quantify exactly
// how much because it depends on so many things, like the number of ACL links, processor
// speed, speed of HCI connection to the Bluetooth radio, the type of callback etc.  Just do
// very minimal non-blocking stuff in the callback, and post a custom event to the event
// queue if you need to do intensive processing.


#include <PalmOS.h>
#include <unix_stdarg.h>

#include "BtPiconetRsc.h"
#include "BtLib.h"


/***********************************************************************
 *	Constants
 ***********************************************************************/

#define kAppFileCreator			'btpi'	// register your own at http://www.palmos.com/dev/creatorid/
#define kAppBtName 				"BtPiconet"

#define kMaxSlaves 				7	// Maximum number of slaves in a Piconet
#define kInvalidSocket 			0xFFFF	// Invalid value used for initialisations

#define kL2CapSocketMtu 		100

#define kButtonUnknown			0	// Lock/Unlock button status is unknown
#define kButtonLock				1	// Button label should be changed to "LOCK"
#define kButtonUnlock			2	// Button label should be changed to "UNLOCK"

#define kMsgLength 				70	// Maximum string length for error and status messages

// We need to keep track of what we do, to make cleanup easier.  These are bit fields
#define kStateLibraryOpened			1	// Bluetooth library has been opened
#define kStateRadioOkay				2	// Radio initialised okay
#define kStatePiconetCreated		4	// A Piconet was created (BtLibPiconetCreate)
#define kStatePiconetLocked			8	// Piconet has been locked
#define kStateListenerSocketCreated	16	// A L2CAP listener has been created (slave)
#define kStateDataSocketCreated		32	// A L2CAP socket has been spawned from the listener socket (slave)
#define kStateSdpRecordCreated		64	// An SDP record was created and advertised

// Some macros to manage the above bit fields
#define IsBitSet(x) (gState & x)
#define ClearBit(x) (gState &= ~x)
#define SetBit(x)   (gState |= x)

// The UUID is a 128-bit number, derived from your PC's Ethernet MAC address, date & time
// and a random number.  Create your own unique UUID using any tool you like.  The best way
// to find one is to enter "UUID generator" in a web search engine.
// Here is UUID {81ED261A-3902-464c-80ED-DCC739CE8211}
static const BtLibSdpUuidType kAppUUID = {btLibUuidSize128, 
	{ 0x81, 0xed, 0x26, 0x1a, 0x39, 0x02, 0x46, 0x4c, 0x80, 0xed, 
	  0xdc, 0xc7, 0x39, 0xce, 0x82, 0x11 } };

// Filter PalmOS handheld for discovery
static const BtLibClassOfDeviceType	kDeviceFilter =
	(btLibCOD_ServiceAny | btLibCOD_Major_Computer | btLibCOD_Minor_Comp_Palm);

static const BtLibDeviceAddressType kInvalidBdAddr = {0, 0, 0, 0, 0, 0};

static const Char kLockStr[] = "Lock";
static const Char kUnlockStr[] = "Unlock";


/***********************************************************************
 *	Structures
 ***********************************************************************/

// SlaveStateEnum describes the possible states the connection to a slave could be in.  This is
// used to generate the slave status display
typedef enum {
	kAnimNoSlave,		// No ACL or socket connection to the slave
	kAnimPingError, 	// Timeout sending to or receiving from slave
	kAnim1,				// animation state 1
	kAnim2,				// animation state 2
	kAnim3,				// animation state 3
	kAnim4,				// animation state 4
	kAnim5,				// animation state 5
	kAnim6,				// animation state 6
	kAnim7,				// animation state 7
	kAnim8,				// animation state 8
	kAnim9,				// animation state 9
	kAnim10,			// animation state 10
	kAnim11,			// animation state 11
	kAnim12 			// animation state 12
} SlaveStateEnum;


// SendStatusEnum describes the possible states of the "ping" between master and
// slave.  Packets containing the Piconet state are sent by the master to all slaves,
// which then return the packet to the master.
typedef enum {
	kStatusNotConnected,			// There is no conection to the slave (initial state)
	kStatusAclLinkUp,			// ACL link to slave is up, but not necessarily a L2CAP connection
	kStatusSdpQueryInProgress,	// SDP query has been made, waiting for response
	kStatusWaitingForL2Cap,		// Waiting for L2CAP connection
	kStatusSlaveIdle,				// ACL and L2CAP connection to slave. Slave is ready to receive
	kStatusSendingToSlave,		// Master has sent to slave, waiting for ACK of the send
	kStatusWaitingForSlave 		// Send confirmed, waiting for slave to reply
} SlaveStatusEnum;


// RoleEnum describes the current role of the device in the Piconet.
typedef enum {
	kRoleUndecided,		// Main screen, user hasn't tapped "Host" or "Join"
	kRoleMaster,		// User tapped master button
	kRoleSlave			// User tapped slave button
} RoleEnum;


// SlaveInfoType contains data on each slave.  This is only used by the master
typedef struct {
	SlaveStatusEnum 		sendStatus;	// Status of the connection to the slave
	BtLibDeviceAddressType	bdaddr;		// Bluetooth device address
	BtLibSocketRef 			socket;		// Socket used for data connections between master & slave
} SlaveInfoType;


// PingDataType is the packet that is sent fron the master to the slaves, and returned by
// the slaves.  The slave determines its "slave number" from the packet.  When it responds,
// it sends exactly the same packet it received. The data is populated by the master, who
// controls all aspects of the connection and monitors slave performance.
typedef struct {
	UInt16 			slaveNumber; // Tells slave what number they are in the Piconet (1-7)
	UInt16 			seqNum;	// Sequential number to verify the packet is pinged correctly
	SlaveStateEnum	slaveState[kMaxSlaves+1]; // Data on each slave in the Piconet (first position in array not used!)
} PingDataType;

// Define custom events to reduce the amount of processing that occurs during a callback
#define SlaveMustReplyEvent (eventsEnum)(firstUserEvent)
#define DataSentToSlaveEvent (eventsEnum)(firstUserEvent+1)
#define ResponseFromSlaveEvent (eventsEnum)(firstUserEvent+2)
#define SlaveAddedEvent (eventsEnum)(firstUserEvent+3)
#define ConnectToNextSlaveEvent (eventsEnum)(firstUserEvent+4)


/***********************************************************************
 *	Entry Points
 ***********************************************************************/

void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon);
void BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon);
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags);


/***********************************************************************
 *	Global variables
 ***********************************************************************/

// General variables
static UInt16 gSavedAutoOff;		// Disable the auto-power off function while this app is running
static UInt16 gState;				// Bit fields: keeps track of what we need to cleanup

static Char gStatus[kMsgLength];	// String to store status information for display
static UInt32 gTimeToClearError;	// Errors are cleared after some elapsed period
static Char gBdAddrStr[18];			// Used to covert BD_ADDR to something printable

// Bluetooth variables used by both master and slave
static UInt16 gBtLibRefNum;					// Bluetooth library reference number
static RoleEnum gRole;						// Role of device - master or slave
static PingDataType gData;					// Data that is sent between the master and each slave

// Bluetooth variables only used by slaves
static BtLibSocketRef gListenerSocket;		// Used to listen for inbound L2CAP connections
static BtLibSocketRef gDataSocket;			// Used for L2CAP data connection to master
static BtLibDeviceAddressType gMasterAddr;// The master's Bluetooth device address
static BtLibSdpRecordHandle gSdpRecordH;	// SDP record handle used to advertise BtPiconet service

// Bluetooth variables only used by the master
static SlaveInfoType gSlave[kMaxSlaves+1];	// Information on the slaves (first position in array not used!)
static UInt16 gNextSlaveToPing;				// Next slave to be ping'ed by the master
static UInt32 gLastPing;					// Time (seconds) when last ping was performed
static UInt16 gSequenceNum;					// Sequence number for ping packets
static BtLibDeviceAddressType gDeviceArray[kMaxSlaves]; // Array of BD_ADDRs to connect to
static UInt8 gNextSlaveToConnectTo;			// Next slave in array to connect to
static Boolean gPendingLink;				// ACL link is being established
static Boolean gPendingDiscovery;			// A discovery is in progress


/***********************************************************************
 *	Internal Functions
 ***********************************************************************/

static Err DiscoverAndConnectMultiple();
static Err AclCreateLink(BtLibDeviceAddressType* deviceArray);
static void GetPSMUsingSDP();
static Boolean NoMoreSlaves();
static Boolean BusyPinging();
static void CleanupSlave(UInt16 slaveNo);
static void ReturnToInitialState();
static void UpdateLockUnlockButtonLabel(UInt8 state);
static void FindAndOpenLibrary(void);
static void CreateListenerSocketAndRegisterUUID();
static void CloseListenerSocketAndUnregisterUUID();

static void InitialisePiconetVariables();
static void InitialiseStatusDisplay();
static void UpdateStatusDisplay();
static void DisplayPiconetStatus(PingDataType *ping);
static void StatusMsg(const char *formatStr, ...);
static void ErrorMsg(const char *formatStr, ...);
static Char *ConvertBdAddrToStr(BtLibDeviceAddressType *bdAddrP);
static void ChangeLabel(UInt16 labelID, const Char *newLabel);

Char *ConvertBtErrToString(Err errno);


/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              initial form (startup screen).
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if event was handled
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP;
	Err error;

	switch (eventP->eType) 
	{
		case menuEvent:
			if (eventP->data.menu.itemID == MainOptionsAboutBtPiconet)
			{
				MenuEraseStatus(0); // Clear the menu status from the display.
				AbtShowAbout(kAppFileCreator);
				handled = true;
				break;
			}
			break;


		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			FrmDrawForm (frmP);

			// Make sure the Bluetooth library is open
			FindAndOpenLibrary();

			// Create the listener socket for the master to connect to
			// There is no downside for the master to do this, except for the small memory overhead
			// of having a listener socket.  There is also a small chance that a slave could connect to
			// the listener socket - but the master would FatalExcept in this case, limiting damage. 
			CreateListenerSocketAndRegisterUUID();
				
			if (IsBitSet(kStateRadioOkay))
				StatusMsg("Ready ...");
			else
				StatusMsg("Not ready yet ...");
			handled = true;
			break;
			
		case ctlSelectEvent:
			// Allow error messages to be overwritten
			gTimeToClearError = 0;

			// Prevent any operation if the library is not open
			if (!IsBitSet(kStateLibraryOpened))
			{
				StatusMsg("Bluetooth library not found!");
				handled = true;
				break;
			}

			// Prevent any operation if the radio is not okay
			if (!IsBitSet(kStateRadioOkay))
			{
				StatusMsg("Bluetooth radio not initialised");
				handled = true;
				break;
			}

			switch (eventP->data.ctlSelect.controlID) 
			{
				case MainHostAndWaitButton:
					// Host (be master of) a Piconet; wait for others to join
					gRole = kRoleMaster;
					
					// Set the radio to "force master" state.  If there is already a link up
					// and this device is not master, BtLibPiconetCreate will return "Pending"
					// while a master/slave switch is performed (btLibManagementEventPiconetCreated
					// callback). Since there is no link up, we expect btLibErrNoError.
					if (BtLibPiconetCreate(gBtLibRefNum, true, true) == btLibErrNoError)
					{
						SetBit(kStatePiconetCreated);
						FrmGotoForm(ActionForm);
					}
					else
					{
						ErrorMsg("Unable to create a Piconet");
						ReturnToInitialState();
					}
					
					handled = true;
					break;

				case MainFindAndHostButton:
					// Host (be master of) a Piconet; discover devices
					gRole = kRoleMaster;

					// Set the radio to "force master" state.  If there is already a link up
					// and this device is not master, BtLibPiconetCreate will return "Pending"
					// while a master/slave switch is performed (btLibManagementEventPiconetCreated
					// callback). Since there is no link up, we expect btLibErrNoError.
					if (BtLibPiconetCreate(gBtLibRefNum, true, true) == btLibErrNoError)
					{
						SetBit(kStatePiconetCreated);
						if ((error = DiscoverAndConnectMultiple()) == btLibErrPending)
						{
							// Go to the "action" form
							FrmGotoForm(ActionForm);
							StatusMsg("Connecting to slaves ...");
						}
						else
						{
							ErrorMsg("Discover error (%s)", ConvertBtErrToString(error));
							ReturnToInitialState();
						}
					}
					else
					{
						ErrorMsg("Unable to create a Piconet");
						ReturnToInitialState();
					}
					
					handled = true;
					break;

				case MainJoinButton:
					// Find and join a Piconet.  The device will be a slave
					gRole = kRoleSlave;
					
					// The creation of the listener socket, and advertising it must have
					// been successful
					if (!IsBitSet(kStateSdpRecordCreated))
					{
						StatusMsg("Error while listening");
						handled = true;
						break;
					}
					
					// Discover the host (master)
					gPendingDiscovery = true;
					error = BtLibDiscoverSingleDevice(gBtLibRefNum, NULL, (BtLibClassOfDeviceType*)&kDeviceFilter, 1, 
							&gMasterAddr, false, false);
					gPendingDiscovery = false;
				
					if (error == btLibErrNoError)
					{
						// Create an ACL link to the master
						if (AclCreateLink(&gMasterAddr) == btLibErrPending)
						{
							// The ACL link is being created.  Look for the
							// btLibManagementEventACLConnectOutbound callback event
							// Don't move to the "action" screen until both the ACL
							// and L2CAP connections are up
							StatusMsg("Trying to connect ...");
						}
						else
						{
							ErrorMsg("Link error (%s)", ConvertBtErrToString(error));
							ReturnToInitialState();
							break;
						}
					}
					else
					{
						ErrorMsg("Discover error (%s)", ConvertBtErrToString(error));
						ReturnToInitialState();
					}
						
					handled = true;
					break;
			}
			break;

		case ConnectToNextSlaveEvent:
			// Connect to the next slave
			if (!gPendingLink && gNextSlaveToConnectTo)
			{
				AclCreateLink(&gDeviceArray[gNextSlaveToConnectTo -1]);
				if (gNextSlaveToConnectTo == 1)
					StatusMsg("1 slave to go ...");
				else
					StatusMsg("%d slaves to go ...", gNextSlaveToConnectTo);
				gNextSlaveToConnectTo--;
			}
			break;
	}
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    ActionFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              action screen, where the master is pinging the slaves
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if event was handled
 *
 ***********************************************************************/
static Boolean ActionFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP;
	UInt16 i;
	EventType event;


	switch (eventP->eType) 
	{
		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			FrmDrawForm (frmP);
			if (gRole == kRoleSlave)
			{
				// Hide the Add and Lock buttons - only master can do these functions
				FrmHideObject(frmP, FrmGetObjectIndex(frmP, ActionAddButton));
				FrmHideObject(frmP, FrmGetObjectIndex(frmP, ActionLockButton));
			}
			else if (gRole == kRoleMaster)
			{
				// Update the Master/Slave display to reflect that this is the master
				ChangeLabel(ActionWhichLabel, "Master");
				UpdateLockUnlockButtonLabel(kButtonUnknown);
			}

			DisplayPiconetStatus(&gData);
			UpdateStatusDisplay();
			handled = true;
			break;
			
		case ctlSelectEvent:
			switch (eventP->data.ctlSelect.controlID) 
			{
				case ActionLeaveButton:
					// Leave the Piconet
					ReturnToInitialState();
					handled = true;
					break;

				case ActionAddButton:
					// Add a new device to the Piconet (master only)
					DiscoverAndConnectMultiple();
					handled = true;
					break;
					
				case ActionLockButton:
					// Lock or Unlock the Piconet (master only)
					if (IsBitSet(kStatePiconetLocked))
					{
						// Piconet was locked, so unlock it (allow inbound connections)
						// Expect btLibManagementEventAccesibleChange callback when change is made
						BtLibPiconetUnlockInbound(gBtLibRefNum, true);
					}
					else
					{
						// Piconet was unlocked, so lock it (prevent inbound connections)
						// Expect btLibManagementEventAccesibleChange callback when change is made
						BtLibPiconetLockInbound(gBtLibRefNum);
					}
					handled = true;
					break;
			}
			break;
			
		case ConnectToNextSlaveEvent:
			// Connect to the next slave
			if (!gPendingLink && gNextSlaveToConnectTo)
			{
				AclCreateLink(&gDeviceArray[gNextSlaveToConnectTo -1]);
				if (gNextSlaveToConnectTo == 1)
					StatusMsg("1 slave to go ...");
				else
					StatusMsg("%d slaves to go ...", gNextSlaveToConnectTo);
				gNextSlaveToConnectTo--;
			}
			break;

		case SlaveAddedEvent:
			// The master should get this event.  A slave has been added to the Piconet (an L2CAP
			// connection has been created to the slave).
			if (gRole == kRoleMaster)
			{
				// If currently pinging slaves, just wait for the next round of pings
				// otherwise force the next round of pings
				if (!BusyPinging())
				{
					event.eType = ResponseFromSlaveEvent;
					EvtAddUniqueEventToQueue(&event, 0, true);
				}
			}
			handled = true;
			break;
			
		case SlaveMustReplyEvent:
			// The slave should get this event.  Data has been received from a master.  The
			// slave needs to respond as soon as possible.
			if (gRole == kRoleSlave)
			{
				// Send the data back to the master
				BtLibSocketSend(gBtLibRefNum, gDataSocket, (UInt8 *) &gData, sizeof(gData));
				
				// Update the status display
				DisplayPiconetStatus(&gData);
				
				StatusMsg("Responding ...");
			}
			handled = true;
			break;
			
			
		case DataSentToSlaveEvent:
			// The master should get this event.  Data has been sent to a slave.  If there
			// are more slaves to send to, then send the data now.
			if (gRole == kRoleMaster)
			{
				for ( ; gNextSlaveToPing <= kMaxSlaves; gNextSlaveToPing++)
				{
					if (gSlave[gNextSlaveToPing].sendStatus == kStatusSlaveIdle)
					{					
						// This slave is idle, so ping it
						gSlave[gNextSlaveToPing].sendStatus = kStatusSendingToSlave;
						gData.slaveNumber = gNextSlaveToPing;
						BtLibSocketSend(gBtLibRefNum, gSlave[gNextSlaveToPing].socket, (UInt8 *) &gData, sizeof(gData));
						gNextSlaveToPing++;
						break;
					}
				}
			}
			handled = true;
			break;
			
		case ResponseFromSlaveEvent:
			// The master should get this event. A response has been received from a slave.
			if (gRole == kRoleMaster)
			{
				// The packet was verified and the slave status updated in the callback
				// (btLibSocketEventData).  If this was the last slave to respond, then
				// restart the ping round to all slaves.
				if (!BusyPinging())
				{
					StatusMsg("Pinging slaves ...");
					
					// Update the Piconet status display.  This is only done once every "ping cycle"
					DisplayPiconetStatus(&gData);

					// Increment the  packet a sequence number. Don't care about wrap-around, since only
					// 1 packet is outstanding at any time
					gData.seqNum = ++gSequenceNum;		

					// Start pinging all the slaves again, starting with the first slave
					gNextSlaveToPing = 1;
				
					// Make a note of the time the ping started	
					gLastPing = TimGetSeconds();
					
					// Kick off sending data to the first slave
					event.eType = DataSentToSlaveEvent;
					EvtAddUniqueEventToQueue(&event, 0, true);
				}
			}
			handled = true;
			break;
			
		case nilEvent:
			// Are we still waiting for a slave to reply after 2 seconds?
			if ((gRole == kRoleMaster) && BusyPinging())
			{
				if (TimGetSeconds() > (gLastPing + 2))
				{
					for (i=1; i<=kMaxSlaves; i++)
					{
						if ((gSlave[i].sendStatus == kStatusSendingToSlave) ||
						    (gSlave[i].sendStatus == kStatusWaitingForSlave))
						{						
							// Found a slave that hasn't responded
							// Update the slave status to reflect this, and reset the slave comms
							if (gSlave[i].sendStatus == kStatusSendingToSlave)
								ErrorMsg("Unable to send to slave %i", i);
							else
								gSlave[i].sendStatus = kStatusSlaveIdle;
								
							gData.slaveState[i] = kAnimPingError;
						}
					}
					
					// Update the Piconet status display
					DisplayPiconetStatus(&gData);
					
					// Restart the ping round
					gNextSlaveToPing = kMaxSlaves + 1;
					event.eType = ResponseFromSlaveEvent;
					EvtAddUniqueEventToQueue(&event, 0, true);
				}
			}
			handled = true;
			break;
			
	}

	return handled;
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    BtLibMECallbackProc
 *
 * DESCRIPTION: Radio event callback
 *
 * PARAMETERS:  See BtLib.h
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
void BtLibMECallbackProc(BtLibManagementEventType *mEventP, UInt32 refCon)
{
	UInt8 i;
	EventType event;
	Err error;
	
	switch(mEventP->event)
	{
		case btLibManagementEventRadioState:
			// The radio state is saved because you shouldn't be able to leave the main screen
			// with the radio inoperable
			if (mEventP->status == btLibErrRadioInitialized)
			{
				SetBit(kStateRadioOkay);
				StatusMsg("Radio Initialised");
			}
			else
			{
				ClearBit(kStateRadioOkay);
				StatusMsg("Radio Init Failed");
				ReturnToInitialState();
			}
			break;
			
		case btLibManagementEventPiconetCreated:
			// Calling BtLibPiconetCreate with no ACL links in place should return immediately
			// with btLibErrNoError.  If there are ACL links up, then the radio has to do
			// a master/slave switch with the other device, so this could take some time.
			// Nothing to do here, so ...
			break;
			
		case btLibManagementEventPiconetDestroyed:	
			// Result of BtLibPiconetDestroy.  Cleanup already done.
			break;		

		case btLibManagementEventACLConnectOutbound:
			if (gRole == kRoleMaster)
			{
				// Master will connect to the next slave
				gPendingLink = false;	
				if(gNextSlaveToConnectTo != 0)
				{
					event.eType = ConnectToNextSlaveEvent;
					EvtAddUniqueEventToQueue(&event, 0, true);
				}
			}
			else
			{
				// We should have connected to a master of a Piconet, check that we are really a slave
				// (a master/slave switch should have occured)
				BtLibConnectionRoleEnum role;
				error = BtLibLinkGetState(gBtLibRefNum, &gMasterAddr, btLibLinkPref_LinkRole, &role, sizeof(role));
				if (error || role != btLibSlaveRole)
				{
					ReturnToInitialState();
					BtLibLinkDisconnect(gBtLibRefNum, &gMasterAddr);
					break;
				}
			}
			// Intentional fall-through 
			
		case btLibManagementEventACLConnectInbound: 
			// Either a master or slave has made an ACL connection
			
			if (mEventP->status != btLibErrNoError)
			{
				ErrorMsg("Can't connect (%s)", ConvertBtErrToString(mEventP->status));
				if (gRole == kRoleSlave)
					ReturnToInitialState();
				else
				{
					// If there are no pending ACL connections to make, start making SDP queries
					// to find the L2CAP PSM's that the slaves are listening on
					if (gNextSlaveToConnectTo == 0)
						GetPSMUsingSDP();
				}	
				break;
			}
			
			// Could have been that the "slave" was on the main screen, and the master
			// discovered it and connected to it.  In this case, the device must now
			// be a slave
			if (gRole == kRoleUndecided)
			{
				gRole = kRoleSlave;
				
				// Get the Bluetooth device address of the device that connected to us
				MemMove(&gMasterAddr, &mEventP->eventData.bdAddr, sizeof(BtLibDeviceAddressType));
			}
			
			// Now that the ACL link is up, the master is responsible for establishing the
			// L2CAP connection
			if (gRole == kRoleSlave)
			{
				// Nothing to do here. 
				StatusMsg("Connected to %s", ConvertBdAddrToStr(&mEventP->eventData.bdAddr));
				break;
			}

			// find an "empty slot" for this slave
			for (i=1; i<= kMaxSlaves; i++)
			{
				if (gSlave[i].sendStatus == kStatusNotConnected)
				{						
					// Make a note that the ACL connection to the slave is up
					gSlave[i].sendStatus = kStatusAclLinkUp;				
					// Save the BD_ADDR of the slave connected to
					MemMove(&gSlave[i].bdaddr, &mEventP->eventData.bdAddr, sizeof(BtLibDeviceAddressType));
					break;
				}
			}
			
			// The empty slot must exist!
			ErrFatalDisplayIf((i > kMaxSlaves), "No slot for slave");
			
			// If there are no pending ACL connections to make, start making SDP queries
			// to find the L2CAP PSM's that the slaves are listening on
			if (gNextSlaveToConnectTo == 0)
				GetPSMUsingSDP();
			
			break;	
			
		case btLibManagementEventACLDisconnect:
			// Existing ACL link that was torn down
			if (gRole == kRoleUndecided)
				break;

			StatusMsg("Disconnect (%s)", ConvertBtErrToString(mEventP->status));
			if (gRole == kRoleSlave)
			{
				if (!gPendingDiscovery)
					ReturnToInitialState();
				break;
			}
				
			// Master: close the socket to the slave if not already closed
			for (i=1; i<=kMaxSlaves; i++)
			{
				// find the slave that we disconnected from
				if (MemCmp(&gSlave[i].bdaddr,&mEventP->eventData.bdAddr, sizeof(BtLibDeviceAddressType)) == 0)
				{
					// Found the slave.  Cleanup slave data
					CleanupSlave(i);
					break;
				}
			}

			// If that was the last slave then return to the main screen
			if (NoMoreSlaves() && !gPendingDiscovery)
				ReturnToInitialState();
			
			// Restart the ping round
			if (!gPendingDiscovery)
			{
				event.eType = ResponseFromSlaveEvent;
				EvtAddUniqueEventToQueue(&event, 0, true);
			}
			break;	
			
		case btLibManagementEventAccessibilityChange:
			switch( mEventP->eventData.accessible)
			{
				case btLibNotAccessible:
					StatusMsg("Not Discoverable nor Connectable");
					SetBit(kStatePiconetLocked);
					UpdateLockUnlockButtonLabel(kButtonUnlock);
					break;
				case btLibConnectableOnly:
					StatusMsg("Connectable");
					ClearBit(kStatePiconetLocked);
					UpdateLockUnlockButtonLabel(kButtonLock);
					break;
				case btLibDiscoverableAndConnectable:
					StatusMsg("Discoverable and Connectable");
					ClearBit(kStatePiconetLocked);
					UpdateLockUnlockButtonLabel(kButtonLock);
					break;
			}
			break;
		}
}


/***********************************************************************
 *
 * FUNCTION:    BtLibSocketCallbackProc
 *
 * DESCRIPTION: Handle L2CAP and SDP events
 *
 * PARAMETERS:  see BtLib.h
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
void BtLibSocketCallbackProc(BtLibSocketEventType *sEventP, UInt32 refCon)
{
	UInt16 i;
	BtLibSocketConnectInfoType connectInfo;
	Err error;
	EventType event;
	PingDataType *pingData;
	
	switch(sEventP->event)
	{
		case btLibSocketEventSdpGetPsmByUuid:
			// Result of obtaining L2CAP PSM from the remote device using SDP 
			// In this sample, the master always does a socket connect to the slave,
			// so only a master will receive this callback.	
			ErrFatalDisplayIf((gRole != kRoleMaster), "PSMByUUID not master!");

			// Regardless of success/failure, the SDP socket must be closed
			if (BtLibSocketClose(gBtLibRefNum, sEventP->socket) != btLibErrNoError)
				ErrorMsg("SDP socket close error");
			
			// Find the slave that responded
			for (i=1; i<=kMaxSlaves; i++)
			{
				if (gSlave[i].socket == sEventP->socket)
					break;
			}
			
			// Insist that the socket is found, and that an SDP query was in progress
			ErrFatalDisplayIf((i > kMaxSlaves), "SDP callback - no slave");
			ErrFatalDisplayIf((gSlave[i].sendStatus != kStatusSdpQueryInProgress), "SDP - not expecting response");
			
			// Was the L2CAP PSM obtained successfully (Is the remote device running the same app?)
			if ((error = sEventP->status) == btLibErrNoError)
			{
				// Create the L2CAP socket, and connect it
				error = BtLibSocketCreate(gBtLibRefNum, &gSlave[i].socket, BtLibSocketCallbackProc, 
							0, btLibL2CapProtocol);
				if (error == btLibErrNoError)
				{
					connectInfo.remoteDeviceP = &gSlave[i].bdaddr;
					connectInfo.data.L2Cap.remotePsm = sEventP->eventData.sdpByUuid.param.psm;
					connectInfo.data.L2Cap.localMtu = kL2CapSocketMtu; //Must be less then 672
					connectInfo.data.L2Cap.minRemoteMtu = kL2CapSocketMtu;
					error = BtLibSocketConnect(gBtLibRefNum, gSlave[i].socket, &connectInfo);
				}
			}
			
			if (error == btLibErrPending)
			{
				StatusMsg("Creating socket to %s ...", ConvertBdAddrToStr(&gSlave[i].bdaddr));
				gSlave[i].sendStatus = kStatusWaitingForL2Cap;
			}
			else
			{
				// No sense in continuing, so drop the ACL link to the slave
				CleanupSlave(i);
				
				// If that was the last slave then return to the main screen			
				if (NoMoreSlaves())
					ReturnToInitialState();
			}

			break;
					
		case btLibSocketEventConnectRequest:
			// Incoming connect request on the listening PSM, so accept it.  It is possible to
			// have multiple incoming connections to the same PSM. The socket here is the listening
			// socket.  The actual connection will appear on a new "spawned" socket.
			// In this sample code, only a slave will receive this callback.
			ErrFatalDisplayIf((gRole != kRoleSlave), "ConnectRequest not a slave!");
			ErrFatalDisplayIf((gListenerSocket != sEventP->socket), "Connect req socket mismatch");

			StatusMsg("Req from %s",ConvertBdAddrToStr(&sEventP->eventData.requestingDevice));
			BtLibSocketRespondToConnection(gBtLibRefNum, sEventP->socket, true);
			break;
				
		case btLibSocketEventConnectedInbound:
			// Received after accepting the socket, confirming the socket is operational
			// In this sample code, only a slave will receive this callback.
			ErrFatalDisplayIf((gRole != kRoleSlave), "ConnectedInbound not a slave");

			// store the socket information
			ErrFatalDisplayIf(IsBitSet(kStateDataSocketCreated), "ConnInbound - socket in use!");
			gDataSocket = sEventP->eventData.newSocket;
			SetBit(kStateDataSocketCreated);
			
			// Go to the action form if not already there
			if (FrmGetActiveFormID() != ActionForm)
				FrmGotoForm(ActionForm);  			
			StatusMsg("Inbound from master established");
			break;
				
		case btLibSocketEventConnectedOutbound:
			// Received to confirm the outbound socket request succeeded
			// In this sample code, only the master will receive this callback.
			ErrFatalDisplayIf((gRole != kRoleMaster), "ConnectedOutbound not a master!");
			
			// Find the slave connected to, and mark it connected
			for (i=1; i<=kMaxSlaves; i++)
			{
				if (gSlave[i].socket == sEventP->socket)
					break;
			}
			
			// Insist that the socket is found
			ErrFatalDisplayIf((i > kMaxSlaves), "ConnectedOutbound - can't find socket");
			
			// Make sure that the L2CAP connection was expected
			ErrFatalDisplayIf((gSlave[i].sendStatus != kStatusWaitingForL2Cap), "Unexpected ConnectedOutbound");
					
			gSlave[i].sendStatus = kStatusSlaveIdle;
			gData.slaveState[i] = kAnim1;
			
			StatusMsg("L2CAP Connect to slave %i", i);
			
			// Post an event to the queue to force a ping to the slaves
			event.eType = SlaveAddedEvent;
			EvtAddUniqueEventToQueue(&event, 0, true);
			break;
				
		case btLibSocketEventDisconnected:
			// Socket disconnected or connect attempt failed
			// In this sample code, either the master or slave could receive this callback

			StatusMsg("Socket disc (%s)", ConvertBtErrToString(sEventP->status));
				
			switch (gRole)
			{
				case kRoleMaster:
					// Go through the list of sockets to find the one that closed				
					for (i=1; i<=kMaxSlaves; i++)
					{
						if (gSlave[i].socket == sEventP->socket)
						{								
							// Found the slave.  Cleanup slave data
							CleanupSlave(i);
							break;
						}
					}
					ErrFatalDisplayIf((i > kMaxSlaves), "Can't find disconnected socket!!");
						
					// If there are no more connections then return to the initial screen
					if (NoMoreSlaves())
						ReturnToInitialState();

					break;
						
				case kRoleSlave:
					// Return to the initial screen
					ReturnToInitialState();
					break;
						
				case kRoleUndecided:
					// We probably received ACL disconnect first, and have cleanup up
					// so don't do anything here
					break;
			}
			break;
				
		case btLibSocketEventSendComplete:
			// Notification that the data has been sent.  You can only have one packet 
			// outstanding on any one socket, so this notification lets you know that
			// you can send the next packet.
			//
			// This callback is received by both master and slave.
				
			if (gRole == kRoleSlave)
			{
				StatusMsg("Data sent!");
				break;
			}
				
			// Mark that the data has been sent and we are waiting for a reply
			for (i=1; i<=kMaxSlaves; i++)
			{
				if (gSlave[i].socket == sEventP->socket)
				{							
					ErrFatalDisplayIf((gSlave[i].sendStatus != kStatusSendingToSlave), "SendComplete when not sending");
					gSlave[i].sendStatus = kStatusWaitingForSlave;
					break;
				}
			}

			ErrFatalDisplayIf((i > kMaxSlaves), "SendComplete - socket not found");

			// The packet to the next slave can be sent
			event.eType = DataSentToSlaveEvent;
			EvtAddUniqueEventToQueue(&event, 0, true);
			break;
				
		case btLibSocketEventData:
			// Data has been received
			// This callback is received by both master and slave
			
			// If the packet is not the correct length discard it
			if (sEventP->eventData.data.dataLen != sizeof(gData))
			{
				ErrorMsg("Received packet with incorrect length");
				break;
			}
				
			switch (gRole)
			{
				case kRoleMaster:
					pingData = (PingDataType *) sEventP->eventData.data.data;
					
					// Make a note that the slave is still alive
					for (i=1; i<=kMaxSlaves; i++)
					{
						if (gSlave[i].socket == sEventP->socket)
						{					
							// Check that the sequence number is what is expected
							if (pingData->seqNum != gSequenceNum)
								StatusMsg("Packet out of sequence - slave %i", i);
							
							// Check that the packet came from the correct slave
							if (pingData->slaveNumber != i)
								ErrorMsg("Packet contains incorrect slave number");
								
							// Check that we were waiting for a response from this slave
							if (gSlave[i].sendStatus != kStatusWaitingForSlave)
								StatusMsg("Received unexpected packet from slave %i", i);
								
							gSlave[i].sendStatus = kStatusSlaveIdle;
							
							// Increment the animation
							if (gData.slaveState[i] == kAnim12)
								gData.slaveState[i] = kAnim1;
							else
								gData.slaveState[i]++;
							break;
						}
					}
					ErrFatalDisplayIf((i > kMaxSlaves), "SendComplete - socket not found");
						
//					StatusMsg("Response from slave %i", i);
						
					// Check to see if all the slaves have responded in the form event handler
					event.eType = ResponseFromSlaveEvent;
					EvtAddUniqueEventToQueue(&event, 0, true);
					break;
						
				case kRoleSlave:
					// Copy the data into global storage so it isn't lost for the response
					MemMove(&gData, sEventP->eventData.data.data, sizeof(gData));
					
					StatusMsg("Ping Received");
					
					// Post an event in the event queue to let force a response to the master's ping
					event.eType = SlaveMustReplyEvent;
					EvtAddEventToQueue(&event);
					break;
			}
				
			break;		
	}
}


/***********************************************************************
 *
 * FUNCTION:    DiscoverAndConnectMultiple
 *
 * DESCRIPTION: Discover and connect to multiple devices
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static Err DiscoverAndConnectMultiple()
{
	Err error;
	UInt8 numDevicesSelected;

	// If still busy connecting to slaves then don't do anything
	if (gPendingLink || gNextSlaveToConnectTo != 0)
	{
		StatusMsg("Still busy ...");
		return 0;
	}

	// Blocking call to discover multiple Bluetooth devices
	// Warning: between the discovery progress dialog and the dicovery result,
	// our callbacks can be called (ex: btLibManagementEventACLDisconnect)
	// We should not update the UI at this moment
	gPendingDiscovery = true;
	error = BtLibDiscoverMultipleDevices(gBtLibRefNum, NULL, NULL, (BtLibClassOfDeviceType*)&kDeviceFilter, 1,
										 &numDevicesSelected, false, false);
	gPendingDiscovery = false;

	// In case all slaves left during discovery, go back to the main screen
	if (NoMoreSlaves() && numDevicesSelected == 0)
		ReturnToInitialState();
		
	if (error == btLibErrNoError)
	{
		// Get the list of BD_ADDRs, and the number of devices
		BtLibGetSelectedDevices(gBtLibRefNum, gDeviceArray, kMaxSlaves, &gNextSlaveToConnectTo);
		// Create a link to the first slave
		error = AclCreateLink(&gDeviceArray[gNextSlaveToConnectTo -1]);
		gNextSlaveToConnectTo--;
	}
	else
	{
		// Restart the ping cycle
		EventType	event;
		event.eType = ResponseFromSlaveEvent;
		EvtAddUniqueEventToQueue(&event, 0, true);
	}

	return error;					
}


/***********************************************************************
 *
 * FUNCTION:    AclCreateLink
 *
 * DESCRIPTION: Create an ACL link to one device
 *
 * PARAMETERS:  the device address
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static Err AclCreateLink(BtLibDeviceAddressType* deviceAddress)
{
	Err error;
		
	error = BtLibLinkConnect(gBtLibRefNum, deviceAddress);
	if (error != btLibErrPending)
	{
		if (error != btLibErrAlreadyConnected)
			StatusMsg("Link failed (%s)", ConvertBtErrToString(error));
		return error;
	}
	gPendingLink = true;
	return error;
}


/***********************************************************************
 *
 * FUNCTION:    GetPSMUsingSDP
 *
 * DESCRIPTION: Initiates the retrieval of the L2CAP PSM value
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void GetPSMUsingSDP()
{
	UInt16 i;
	Err error;
	
	for (i=1; i<= kMaxSlaves; i++)
	{
		// Look for a slave with only the ACL link up, no L2CAP conection yet
		if (gSlave[i].sendStatus == kStatusAclLinkUp)
		{
			// Insist thta the socket is not already in use
			ErrFatalDisplayIf((gSlave[i].socket != kInvalidSocket), "Getting PSM - socket in use");
			
			// Create an SDP socket			
			if (BtLibSocketCreate(gBtLibRefNum, &gSlave[i].socket, BtLibSocketCallbackProc, 0,
				btLibSdpProtocol) != btLibErrNoError)
			{
				ErrorMsg("SDP socket create error");
				break;
			}
			
			// Use SDP to get the L2CAP PSM that the salve is listening on..  Once the query
			// has completed, the btLibSocketEventSdpGetPsmByUUID callback event will be generated.
			error = BtLibSdpGetPsmByUuid(gBtLibRefNum, gSlave[i].socket, &gSlave[i].bdaddr,
				(BtLibSdpUuidType*) &kAppUUID, 1);
					
			if (error == btLibErrPending)
			{
				StatusMsg("Getting PSM using SDP ...");
	
				// Make a note that the master is doing an SDP query for the PSM value
				gSlave[i].sendStatus = kStatusSdpQueryInProgress;
			}
			else
				ErrorMsg("SDP Error (%s)", ConvertBtErrToString(error));
		}
	}
}


/***********************************************************************
 *
 * FUNCTION:    NoMoreSlaves
 *
 * DESCRIPTION: Called by the master to check if it is still connected to slaves
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static Boolean NoMoreSlaves()
{
	UInt16 i;

	for (i=1; i<=kMaxSlaves; i++)
	{
		if (gSlave[i].sendStatus != kStatusNotConnected)
			return false;
	}
	
	return true;
}

/***********************************************************************
 *
 * FUNCTION:    BusyPinging
 *
 * DESCRIPTION: Called by the master to see if it is currently pinging slaves
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static Boolean BusyPinging()
{
	UInt16 i;
	
	// If we are in a ping cycle, return true
	if (gNextSlaveToPing <= kMaxSlaves)
		return true;
	
	// If we are waiting for a slave to respond, return true
	for (i=1; i<=kMaxSlaves; i++)
	{
		if ((gSlave[i].sendStatus == kStatusSendingToSlave) || (gSlave[i].sendStatus == kStatusWaitingForSlave))
			return true;
	}
				
	return false;			
}


/***********************************************************************
 *
 * FUNCTION:    CleanupSlave
 *
 * DESCRIPTION: Connection to slave has been lost, so clean up
 *
 * PARAMETERS:  slave number
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void CleanupSlave(UInt16 slaveNo)
{
	// Close the L2CAP socket to the slave, if not already done
	if (gSlave[slaveNo].socket != kInvalidSocket)
	{
		BtLibSocketClose(gBtLibRefNum, gSlave[slaveNo].socket);
		gSlave[slaveNo].socket = kInvalidSocket;
	}
	
	// Disconnet the ACL link to the slave
	if (MemCmp(&gSlave[slaveNo].bdaddr, &kInvalidBdAddr, sizeof(BtLibDeviceAddressType)) != 0)
	{
		BtLibLinkDisconnect(gBtLibRefNum, &gSlave[slaveNo].bdaddr);
		MemMove(&gSlave[slaveNo].bdaddr, &kInvalidBdAddr, sizeof(BtLibDeviceAddressType));
	}

	// Mark that the connection to the slave is no longer there				
	gSlave[slaveNo].sendStatus = kStatusNotConnected;
	gData.slaveState[slaveNo] = kAnimNoSlave;
}


/***********************************************************************
 *
 * FUNCTION:    ReturnToInitialState
 *
 * DESCRIPTION: Close all open sockets, drop all ACL links and
 *              go back to the main form
 *
 * PARAMETERS:  slave number
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void ReturnToInitialState()
{
	UInt16 i;
	
	// The "spawned" sockets must be closed before the listening socket
	if (IsBitSet(kStateDataSocketCreated))
	{
		BtLibSocketClose(gBtLibRefNum, gDataSocket);
		ClearBit(kStateDataSocketCreated);
	}
		
	// Cleanup all the slave info
	for (i=1; i<= kMaxSlaves; i++)
		CleanupSlave(i);
		
	gNextSlaveToPing = kMaxSlaves + 1;

	if (IsBitSet(kStatePiconetCreated))
	{
		BtLibPiconetDestroy(gBtLibRefNum);
		ClearBit(kStatePiconetCreated);
	}
		
	gRole = kRoleUndecided;
	if (FrmGetActiveFormID() != MainForm)
		FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    FindAndOpenLibrary
 *
 * DESCRIPTION: Find/Load/Open the BtLib and register our callback
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void FindAndOpenLibrary(void)
{
	Err error;

	// Don't re-open BtLib if it is already open
	if (IsBitSet(kStateLibraryOpened))
		return;
		
	StatusMsg("Opening Bluetooth library ...");
	
	// Find the Library
	if (SysLibFind(btLibName, &gBtLibRefNum))
	{
		// load it if it can't be found	
		error = SysLibLoad(sysFileTLibrary, sysFileCBtLib, &gBtLibRefNum);
		if (error)
		{
			ErrorMsg("Could not find %s", btLibName);
			return;
		}
		StatusMsg("BtLib Loaded");
	}
	else
	{
		StatusMsg("BtLib Found");
	}
		
	// Open the library
	error = BtLibOpen(gBtLibRefNum, false);
	if (error)
		ErrorMsg("BtLib Open failed (%s)", ConvertBtErrToString(error));
	else
	{
		// Register the callback function
		BtLibRegisterManagementNotification(gBtLibRefNum, BtLibMECallbackProc, 0);
		StatusMsg("BtLib Opened");
		SetBit(kStateLibraryOpened);
	}
}


/***********************************************************************
 *
 * FUNCTION:    CreateListenerSocketAndRegisterUUID
 *
 * DESCRIPTION: The master creates a listener L2CAP socket, and advertises it.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void CreateListenerSocketAndRegisterUUID()
{
	BtLibSocketListenInfoType listenInfo;
	Err error;
		
	// Don't do this if the library is not open
	if (!IsBitSet(kStateLibraryOpened))
		return;
			
	// Don't create a listener socket and advertise it if already done
	if (IsBitSet(kStateSdpRecordCreated))
		return;
					
	error = BtLibSocketCreate(gBtLibRefNum, &gListenerSocket, BtLibSocketCallbackProc, 
			0, btLibL2CapProtocol);
	if (error == btLibErrNoError)
	{
		SetBit(kStateListenerSocketCreated);
		
		// Ask the stack to assign a L2CAP PSM
		listenInfo.data.L2Cap.localPsm = BT_L2CAP_RANDOM_PSM; // Preferred method!
		listenInfo.data.L2Cap.localMtu = kL2CapSocketMtu; //Must be less then 672
		listenInfo.data.L2Cap.minRemoteMtu = kL2CapSocketMtu;
		
		// Set the socket to listen for inbound L2CAP socket connections
		error = BtLibSocketListen(gBtLibRefNum, gListenerSocket, &listenInfo);
	}
					
	if (error != btLibErrNoError)
	{
		ErrorMsg("Listen Error (%s)", ConvertBtErrToString(error));
		return;
	}
				
	// Create an SDP record and start advertising the listening socket
	error = BtLibSdpServiceRecordCreate(gBtLibRefNum, &gSdpRecordH);
	if (error == btLibErrNoError)
	{
		SetBit(kStateSdpRecordCreated);
		error = BtLibSdpServiceRecordSetAttributesForSocket(gBtLibRefNum, gListenerSocket, 
		(BtLibSdpUuidType*) &kAppUUID, 1, kAppBtName, StrLen(kAppBtName), gSdpRecordH);
					
		if (error == btLibErrNoError)
			error = BtLibSdpServiceRecordStartAdvertising(gBtLibRefNum, gSdpRecordH);
			
	}

	// Was the SDP record created successfully?
	if (error != btLibErrNoError)
	{
		ErrorMsg("Error advertising (%s)", ConvertBtErrToString(error));
		CloseListenerSocketAndUnregisterUUID();
	}
	else
		StatusMsg("Socket advertised via SDP");
}


/***********************************************************************
 *
 * FUNCTION:    CloseListenerSocketAndUnregisterUUID
 *
 * DESCRIPTION: Opposite of CreateListenerSocketAndRegisterUUID
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void CloseListenerSocketAndUnregisterUUID()
{
	// Stop advertising
	if (IsBitSet(kStateSdpRecordCreated))
	{
		BtLibSdpServiceRecordDestroy(gBtLibRefNum, gSdpRecordH);
		ClearBit(kStateSdpRecordCreated);
	}

	// Close the listener socket
	if (IsBitSet(kStateListenerSocketCreated))
	{
		BtLibSocketClose(gBtLibRefNum, gListenerSocket);
		ClearBit(kStateListenerSocketCreated);
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

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
		{
			case MainForm:
				FrmSetEventHandler(frmP, MainFormHandleEvent);
				break;

			case ActionForm:
				FrmSetEventHandler(frmP, ActionFormHandleEvent);
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
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;
	Int32 timeout;

	do
	{
		// The Piconet master needs nil events to handle timeouts
		if (gRole == kRoleMaster)
			timeout = SysTicksPerSecond();
		else
			timeout = evtWaitForever;
			
		EvtGetEvent(&event, timeout);

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
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 ***********************************************************************/
static void AppStart(void)
{
    // Disable auto-off while the app is running
    gSavedAutoOff = SysSetAutoOffTime(0);

	// Initialise global variables
	InitialisePiconetVariables();
	
	// And go to the main form
	FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Terminate the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void AppStop(void)
{
	// Reset the auto-off timer
  	SysSetAutoOffTime(gSavedAutoOff);

	// Close the listener socket and stop advertising it
	CloseListenerSocketAndUnregisterUUID();
	
	// Close the Bluetooth library
	if (IsBitSet(kStateLibraryOpened))
		BtLibClose(gBtLibRefNum);

	// Close all the open forms.
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
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
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
			AppStart();
			AppEventLoop();
			AppStop();
			break;

		default:
			break;

	}
	
	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    InitialisePiconetVariables
 *
 * DESCRIPTION: Initialise all the variables used in this app.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void InitialisePiconetVariables()
{
	UInt16 i;
	
	gRole = kRoleUndecided;			// User hasn't pressed "Host" or "Join" yet

	// No error yet
	gTimeToClearError = 0;
	
	// No links pending
	gPendingLink = false;
	gPendingDiscovery = false;
	gNextSlaveToConnectTo = 0;
	
	gNextSlaveToPing = kMaxSlaves + 1;

	// Initialise the slave state
	for (i=1; i<=kMaxSlaves; i++)
	{
		gData.slaveState[i] = kAnimNoSlave;
		gSlave[i].socket = kInvalidSocket;
		MemMove(&gSlave[i].bdaddr, &kInvalidBdAddr, sizeof(BtLibDeviceAddressType));
		gSlave[i].sendStatus = kStatusNotConnected;
	}
}


/***********************************************************************
 *
 * FUNCTION:    DisplayPiconetStatus
 *
 * DESCRIPTION: Updates the graphics on the screen, based on the status of the slaves
 *
 * PARAMETERS:  the slaves status
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void DisplayPiconetStatus(PingDataType *ping)
{
	UInt16 i, iconOffset;
	Char str[10];
	MemHandle hRsc;
	
	if (FrmGetActiveFormID() != ActionForm)
		return;
	
	// Update the slave number
	if (gRole == kRoleSlave)
	{
		StrPrintF(str, "Slave %i", ping->slaveNumber); 
		ChangeLabel(ActionWhichLabel, str);
	}

	for (i=1; i<=kMaxSlaves; i++)
	{
		// Get the correct bitmap
		switch (ping->slaveState[i])
		{
			case kAnimNoSlave:
				hRsc = DmGetResource(bitmapRsc, NoLinkBitmapFamily); 
				break;
			
			case kAnimPingError:
				hRsc = DmGetResource(bitmapRsc, UnknownStateBitmapFamily); 
				break;

			default:
				// This is one of the animation icons
				iconOffset = 100 * (ping->slaveState[i] - kAnim1);
				hRsc = DmGetResource(bitmapRsc, Action1BitmapFamily + (DmResID) iconOffset); 
				break;
		}
		
		// Draw the bitmap onto the screen (x: every 24 pixels; y: fixed at 25 pixels
		WinDrawBitmap((BitmapType*) MemHandleLock(hRsc), (i-1)*24, 25);
			
		// Unlock and release the resources
		MemHandleUnlock(hRsc);
		DmReleaseResource(hRsc);
	}
}


/***********************************************************************
 *
 * FUNCTION:    UpdateLockUnlockButtonLabel
 *
 * DESCRIPTION: Reflect a change in the accessibility of the Piconet
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void UpdateLockUnlockButtonLabel(UInt8 state)
{
	BtLibAccessibleModeEnum access;
	Err error;
	FormPtr frmP = FrmGetActiveForm();
 	
 	// Must be the form with the lock/unlock button on it!
 	if (FrmGetActiveFormID() != ActionForm)
 		return;
 		
	switch (state)
	{
		case kButtonUnknown:
			// Make sure the Lock/Unlock button matches our current accessible state
			error = BtLibGetGeneralPreference(gBtLibRefNum, btLibPref_CurrentAccessible, &access, sizeof(access));
			if (error == btLibErrNoError)
			{
				switch (access)
				{
					case btLibNotAccessible:
						UpdateLockUnlockButtonLabel(kButtonUnlock);
						SetBit(kStatePiconetLocked);
						break;

					case btLibConnectableOnly:	// Intentional fall through
					case btLibDiscoverableAndConnectable:	
						UpdateLockUnlockButtonLabel(kButtonLock);
						ClearBit(kStatePiconetLocked);
						break;						
				}
			}
			break;
			
		case kButtonLock:
			CtlSetLabel(FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, ActionLockButton)), kLockStr);
			break;
			
		case kButtonUnlock:
			CtlSetLabel(FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, ActionLockButton)), kUnlockStr);
			break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    InitialiseStatusDisplay
 *
 * DESCRIPTION: Empty the status display
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void InitialiseStatusDisplay()
{
	StatusMsg("");
	UpdateStatusDisplay();
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
			
		case ActionForm:
			ChangeLabel(ActionStatusLabel, gStatus);
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
	
	// Display the message
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

	// Display the error
	UpdateStatusDisplay();
	
	// Display the error for at least 15 seconds
	gTimeToClearError = TimGetSeconds() + 15;
}


/***********************************************************************
 *
 * FUNCTION:    ConvertBdAddrToStr
 *
 * DESCRIPTION: Convert Bluetooth device address into something printable
 *
 * PARAMETERS:  the BT address
 *
 * RETURNED:    the corresponding string
 *
 ***********************************************************************/
static Char *ConvertBdAddrToStr(BtLibDeviceAddressType *bdAddrP)
{
	BtLibAddrBtdToA(gBtLibRefNum, bdAddrP, gBdAddrStr, sizeof(gBdAddrStr));
	return(gBdAddrStr);
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
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void ChangeLabel(UInt16 labelID, const Char *newLabel)
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
