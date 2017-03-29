/******************************************************************************
 *
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * File: TwMp.h
 *
 * Description:
 *              Public API for Multiplayer Game Invitation
 *              The main benefit of this API is that it allows
 *              the host to invite other players to play a game
 *              without having the game running.  The game is
 *              launched on the guest's device if the user accepts
 *              the invitation.  
 *
 * History:
 *	10/15/03 	ecm 	Created
 *
 *****************************************************************************/

#ifndef __TwMp_H__
#define	__TwMp_H__

#include <BtLibTypes.h>
#include "TwError.h"
#include "TwTraps.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************
 * Constants
 ********************************************************************/

#define kTwMpName			"Tapwave Multiplayer Library"	
#define sysFileCTwMp		'twMU'
#define twMpFtrCreator      sysFileCTwMp

/*
 * Error Codes
 */
#define twMpErrNoError				(0)
#define twMpErrError				(twMpErrorBase | 0xFF)
#define twMpErrNotOpen				(twMpErrorBase | 0x01)
#define twMpErrNotHost				(twMpErrorBase | 0x02)
#define twMpErrInvitationRejected	(twMpErrorBase | 0x03)
#define twMpErrHost					(twMpErrorBase | 0x04)
#define twMpErrOutOfMemory			(twMpErrorBase | 0x05)
#define twMpErrNotEnough			(twMpErrorBase | 0x06)
#define twMpErrInProgress			(twMpErrorBase | 0x07)
#define twMpErrParamError			(twMpErrorBase | 0x08)
#define twMpErrTooMany				(twMpErrorBase | 0x09)
#define twMpErrPending				(twMpErrorBase | 0x0A)
#define twMpErrNoAccepted		    (twMpErrorBase | 0x0B)
#define twMpErrLeftGame		        (twMpErrorBase | 0x0C)
#define twMpErrDisconnected		    (twMpErrorBase | 0x0D)
#define twMpErrNotHostOrGuest       (twMpErrorBase | 0x0E)
#define twMpErrAlreadyOpen          (twMpErrorBase | 0x0F)
#define twMpErrNoConnection         (twMpErrorBase | 0x10)
#define twMpErrBadObjectVersion     (twMpErrorBase | 0x11)
#define twMpErrUIBusy               (twMpErrorBase | 0x12)
#define twMpErrAlreadyConnected		(twMpErrorBase | 0x13)
#define twMpErrNotFound				(twMpErrorBase | 0x14)
#define twMpErrDisinvited			(twMpErrorBase | 0x15)
#define twMpErrNotLaunched          (twMpErrorBase | 0x16)


/*
 * Feature Numbers
 */

//
// Feature exists if the app was launched by the multiplayer library.  It must be checked by an application
// on application launch with sysAppLaunchCmdNormalLaunch to see if the app was launched by the multiplayer
// library.  The feature stores a pointer to a TwMpLaunchParamsType structure (68K Big Endian byte order)
//

#define twMpFtrNumMultiplayerLaunch                 1

// This feature stores the version of the library.  
#define twMpFtrNumVersion                           2 


/*
 * Launch Codes
 */
 
//
// The OS does not allow reservation of app launch codes.  
// So in order to avoid conflict with any potential custom launch codes you may want to add to your 
// application we set our base for the custom launch codes you need to support if you use this API
// to sysAppLaunchCmdCustomBase + 0x6FFF, or 0xEFFF. The app will be sublaunched with this code to
// allow replacement of the Invitation dialog.  
// 
#define twMpAppLaunchCmdCustomBase                  (sysAppLaunchCmdCustomBase + 0x6FFF)  
 
// Allow the app to replace the default UI for asking the user
// if he/she wants to join the game.  
#define twMpAppLaunchCmdAskUser				        (twMpAppLaunchCmdCustomBase)

/*
 * Misc. Constants
 */
 
// Results returned from PilotMain when sublaunched with twMpAppLaunchCmdAskUser
// to override the default invitation UI. 
#define twMpResultAsk       (0) // Default invitation dialog will be displayed.
#define twMpResultAccept    (1) // Invitation Accepted (app will be launched by TwMp)
#define twMpResultDecline   (2) // Invitation Declined 
 
// You can have 8 devices in a piconet which means 7 other players
#define kTwMpMaxOtherPlayers  (7)

/********************************************************************
 * Structures and Types
 ********************************************************************/
// Possible player states
	
// This player is hosting the game.  
#define	twMpPlayerHosting       1
	
// Waiting for bluetooth connection to get in place 
#define twMpPlayerWaiting       2
	
// Connected to device looking for Multiplayer service
#define	twMpPlayerAclConnected  3
	
// Connected to service.  Player being asked to join the game.  
#define twMpPlayerConnected     4
		
// Player has accepted the game invitation
#define	twMpPlayerAccepted      5
	
// Player has declined the game invitation
#define	twMpPlayerDeclined      6
	
// Connection to bluetooth device failed
#define	twMpPlayerFailed        7

typedef UInt32 TwMpPlayerStateEnum;

// Update the connection status of a player
#define	twMpEventPlayerState        1
	
// Game has been canceled.  Or if you are a guest, you have been
// removed from the game. 
// IMPORTANT: the btlib is left open by the multiplayer library
// so that the ACL links can be left in place.  This means you do 
// not have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
// will close the BtLib for the multiplayer library.  Since the BtLib
// keeps an open count you also need to close the library for every time 
// that it is opened independently by the application as well.  
#define	twMpEventGameCanceled       2
	
// For non-hosts, Initiate listener sockets and advertise them 
// so the host can connect to them for the game when it receives
// the twMpEventHostStartGameEvent. 
// IMPORTANT: the btlib is left open by the multiplayer library
// so that the ACL links can be left in place.  This means you do 
// not have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
// will close the BtLib for the multiplayer library.  Since the BtLib
// keeps an open count you also need to close the library for every time 
// that it is opened independently by the application as well.  
#define	twMpEventGuestStartGame     3
	
// Host can initiate the game. All slaves should have their listeners
// and only the ACL links to devices still exist.  Comes with a list
// of addresses.
// IMPORTANT: the btlib is left open by the multiplayer library
// so that the ACL links can be left in place.  This means you do 
// not have to call BtLibOpen to use the BtLib APIs.  A call to TwMpClose
// will close the BtLib for the multiplayer library.  Since the BtLib
// keeps an open count you also need to close the library for every time 
// that it is opened independently by the application as well.  
#define	twMpEventHostStartGame      4

typedef UInt32 TwMpEventEnum;

#define twMpEventTypeVersion (1)
typedef struct _TwMpEventType{

    UInt32 version;

	TwMpEventEnum event;
		
	union
	{
		// Event: twMpEventPlayerState
		struct
		{
			TwMpPlayerStateEnum newState; //updated player state
			
			//16 bit error code, 32 bits for structure alignment
			UInt32 reason; //reason for transition to a state (for twMpPlayerFailed)
			BtLibDeviceAddressType bdAddr;
		} state;
		
		// Event: twMpEventHostStartGame
		struct
		{
			// List of accepted players
			BtLibDeviceAddressType hostAddr;
			BtLibDeviceAddressType guestAddrs[kTwMpMaxOtherPlayers];
			UInt32 numGuests;
		} acceptedPlayers;
		
		// Event: twMpEventGuestStartGame		
		BtLibDeviceAddressType hostAddr; 		
	
	}eventData; 

} TwMpEventType;

// Callback definition
// In Tapwave Native Applications make sure the callback definition
// is preceded by the SYSTEM_CALLBACK specifier.  Also make sure that
// any BtLib callbacks have the SYSTEM_CALLBACK specifier.  
typedef void (*TwMpProcPtr) (TwMpEventType *mpEvent, UInt32 refCon);

// ARM aligned name structure
typedef struct _TwMpPlayerNameType
{
    UInt8* name;
    UInt32 nameLength;
} TwMpPlayerNameType;


#define twMpAskUserParamTypeVersion (1)
// Param structure passed into PilotMain sublaunch to replace
// invitation dialog.  
typedef struct _TwMpAskUserParamType
{
    UInt32 version;
    TwMpPlayerNameType hostName;  //Name of game host.  
} TwMpAskUserParamType;


#define twMpLaunchParamsTypeVersion (1)
// Structure stored in twMpFtrNumMultiplayerLaunch feature number
typedef struct _TwMpLaunchParamsType
{
    UInt32 version;
    // If fromCard is true then volRefNum and path are valid, otherwise not.  
    Boolean fromCard;  
    UInt8 reserved[3];  // padding          
    UInt16 volRefNum;   // volume app was stored on
    UInt8 reserved1[2]; // padding
    const Char* path;   // path of the prc
} TwMpLaunchParamsType;

// Info on a specific player
typedef struct _TwMpPlayerInfoType
{
    UInt32 size;                // Caller MUST set this to sizeof(TwMpPlayerInfoType)
	TwMpPlayerStateEnum state;  // State of the player
	UInt32 reason;              // Reason if state is twMpPlayerFailed 16 bit error code, 32 for alignment
	TwMpPlayerNameType name;    // Name  of the player,NEEDS TO BE INITIALIZED PRIOR TO CALLING
	                            // TwMpGetPlayerInfo(). 
} TwMpPlayerInfoType;

/********************************************************************
 * Methods
 ********************************************************************/

/*
 * Open the multiplayer library.  Every Open requires a corresponding
 * call to TwMpClose
 */
Err TwMpOpen(void)
    TAL_TRAP(trapTwMpOpen);

/*
 * Close the multiplayer library
 */
Err TwMpClose(void)
    TAL_TRAP(trapTwMpClose);

/*
 * Register a callback and refcon for device status.  Set the creator of 
 * the game you will be hosting so it can be launched on the remote device.  
 * This API calls BtLibOpen and BtLibPiconetCreate.  In order to use this 
 * API, you must not have any ACL links in place and not have a piconet 
 * created.  
 */
Err TwMpHostGame(UInt32 creator, TwMpProcPtr callbackP, UInt32 refcon)
    TAL_TRAP(trapTwMpHostGame);

/*
 *	Add device to the piconet.  Once one device is added the callbacks
 *  to update the state of each device will begin.  Can be called in a 
 *  loop and the devices will be queue up by the library.  
 */
Err TwMpHostInvitePlayer(BtLibDeviceAddressType* bdAddrP)
    TAL_TRAP(trapTwMpHostInvitePlayer);

/*
 * If an application is launched by the multiplayer library by a user
 * accepting an invitation.  You can detect this type of launch by looking
 * for the twMpFtrNumMultiplayerLaunch on a sysAppLaunchCmdNormalLaunch. 
 * If the featur exists the app needs to call TwMpOpen and then this API.
 * to register a callback for updates on other players.  .  
 */
Err TwMpGuestAcceptInvitation(TwMpProcPtr callbackP, UInt32 refCon)
    TAL_TRAP(trapTwMpGuestAcceptInvitation);

/*
 * Disinvite a player
 */ 
Err TwMpHostDisinvitePlayer(BtLibDeviceAddressType* bdAddrP)
    TAL_TRAP(trapTwMpHostDisinvitePlayer);

/*
 * Start the game.  Guests will receive their final event 
 * twMpEventGuestStartGame to create listener sockets and advertise
 * them.  Then a the host will get a final callback with event 
 * twMpEventHostStartGame that has a list of the devices in the game.
 * These callbacks are staged so that there is no race condition.  
 */
Err TwMpHostStartGame(void)
    TAL_TRAP(trapTwMpHostStartGame);

/*
 * On a host, kills all connections to devices.  
 * On a non-host, just kill your connection and exit the game formation process.
 * Implicitly unregisters your callback function either immediately or on 
 * reception of the twMpEventGameCanceled event.  
 */
Err TwMpCancelGame(void)
    TAL_TRAP(trapTwMpCancelGame);

/*
 * Get information about a player, In particular its, name and state.
 */
Err TwMpGetPlayerInfo(BtLibDeviceAddressType* bdAddrP, TwMpPlayerInfoType* infoP)
    TAL_TRAP(trapTwMpGetPlayerInfo);

/*
 * Get the number of players, including the host and those who have declined or failed
 * In short every device that has been invited to the game.  
 */
Err TwMpGetNumPlayers(UInt8* numPlayers)
    TAL_TRAP(trapTwMpGetNumPlayers);
 
/*
 * Get all the players, including the host and those who have declined or failed
 */
Err TwMpGetAllPlayers(BtLibDeviceAddressType bdAddr[], UInt8 arraySize, UInt8* numPlayersReturnedP)
    TAL_TRAP(trapTwMpGetAllPlayers);

/*
 * Get number of players who have accepted a game invitation
 */ 
Err TwMpGetNumAcceptedPlayers(UInt8* numPlayers)
    TAL_TRAP(trapTwMpGetNumAcceptedPlayers);

/*
 * Get a list of players who have accepted the game invitation so far.  
 */
Err TwMpGetAcceptedPlayers(BtLibDeviceAddressType bdAddr[], UInt8 arraySize, UInt8* numPlayersReturnedP)
    TAL_TRAP(trapTwMpGetAcceptedPlayers);

#ifdef __cplusplus
}
#endif

#endif //__TwMp_H__

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
