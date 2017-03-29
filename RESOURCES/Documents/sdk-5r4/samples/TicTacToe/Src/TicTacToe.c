/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: TicTacToe.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *		TIC-TAC-TOE game via Bluetooth Exchange Manager Library.
 *
 *****************************************************************************/

/***********************************************************************
 *   Includes
 ***********************************************************************/

#define TRACE_OUTPUT TRACE_OUTPUT_ON // Debug traces On / Off

#include <PalmOS.h>
#include <TraceMgr.h>
#include "BtLib.h"
#include "BtExgLib.h"

#include "TicTacToeRsc.h"

/***********************************************************************
 *   Constants
 ***********************************************************************/

#define kAppFileCreator	'Tict'

#define kExgFileName	"TicTacToe"	// OBEX file name
#define kExgFileExt		"Tict"		// OBEX file extension
#define kExgFile		(kExgFileName "." kExgFileExt)

#define kMaxUrlSize		100
#define kMaxStatusSize	100

#define kGameBoardSize	3 // Board has 3*3 squares usually

#define kEventProcessGamePacket (eventsEnum)(firstUserEvent)


/***********************************************************************
 *   Types
 ***********************************************************************/

typedef enum {
	kStateIdle = 0,		// No game in progress
	kStateConnecting,	// Sending a game request or receiving one
	kStateStarting,		// Sending a game acknowledgment
	kStateYourTurn,		// Your turn to play
	kStateOpponentTurn	// Waiting for opponent to play
} StateEnumType, *StateEnumPtr;

typedef enum {	
	kSquareEmpty	= 0,
	kSquareCircle	= 1, // The initiator plays with circles
	kSquareCross	= 2, // The acceptor plays with crosses
	kSquareTemporary= 4  // Temporary visual effect
} SquareEnumType, *SquareEnumPtr;
				
typedef enum {	
	kGameRequest,		// Game request
	kGameAck,			// Request acknowledgement
	kGameMove,			// Game move
	kGameCancel 		// Cancel indication
} PacketEnumType, *PacketEnumPtr;

typedef struct {
	PacketEnumType	type; // As defined above
	Coord			x, y; // Move coordonates, only for kGameMove
} GamePacketType, *GamePacketPtr;


/***********************************************************************
 *   Global variables
 ***********************************************************************/

Char			gOpponentURL[kMaxUrlSize]; // Opponent URL, once known
StateEnumType	gState; // Current state, as defined above
Boolean			gIsInitiator; // True if initiator of the game, false if acceptor
UInt16			gMoveCount; // To detect when game board is full
SquareEnumType	gGameBoard [kGameBoardSize][kGameBoardSize]; // The game board
GamePacketType	gPacket; // Current game packet
RectangleType	gBounds; // Game board bounds
Coord			gSquareSize; // In pixels


/***********************************************************************
 *   Internal Functions
 ***********************************************************************/

static Err  SendGamePacket(PacketEnumType type, Coord x, Coord y);
static Err  AcceptGamePacket(ExgSocketPtr exgSocketP, Boolean isRunning);
static void ProcessGamePacket();
static void ConfirmGameStart(ExgAskParamPtr exgP, Boolean isRunning);
static void GotoGameStart(GoToParamsPtr gotoP);
static void GetUrlFromSocketRef(ExgSocketPtr exgSocketP, Char *url, UInt16 urlSize);

static void SetState(StateEnumType state);
static void DrawSquare(Coord x, Coord y);
static void StartNewGame(Boolean isInitiator);
static void EndGame();
static void CancelGame();
static void CheckWinLossDraw();


/***********************************************************************
 *
 * FUNCTION:    SendGamePacket
 *
 * DESCRIPTION: Send a game packet such as a game request or 
 *				a game move at position x,y
 *
 * PARAMETERS:  type - the message type
 *				x and y - column and row if type is kGameMove
 *
 * RETURNED:    0 on sucess or an error code
 *
 ***********************************************************************/
static Err SendGamePacket(PacketEnumType type, Coord x, Coord y)
{
	ExgSocketType	exgSocket;
	Err				err;
	
	// The first time, we'll discover the receiving device. Otherwise gOpponentURL
	// holds the opponent BT address
	if (type == kGameRequest) 
		StrPrintF(gOpponentURL, "%s%s%s", btexgPrefix, btexgSingleSufix, kExgFile);

	// Create the exchange socket
	MemSet(&exgSocket, sizeof(ExgSocketType), 0);
	exgSocket.count = 1;
	exgSocket.description = (char*)"Tic Tac Toe game";
	exgSocket.length = StrLen(exgSocket.description);
	exgSocket.name = gOpponentURL;
	err = ExgPut(&exgSocket);
	if (err == errNone)
	{
		// The first time, get the URL that now contains the BT address
		if (type == kGameRequest)
			GetUrlFromSocketRef(&exgSocket, gOpponentURL, kMaxUrlSize);
	
		// Now send the game packet
		gPacket.type = type;
		gPacket.x = x;
		gPacket.y = y;
		ExgSend(&exgSocket, &gPacket, sizeof(GamePacketType), &err);
	}
	ExgDisconnect(&exgSocket, err);
		
	// Handle errors and disconnect
	if (err == exgErrUserCancel)
		TraceOutput(TL(appErrorClass + 1, "SendGamePacket: User canceled"));
	else if (err != errNone)
		TraceOutput(TL(appErrorClass + 1, "SendGamePacket: *** Error %hx while putting/sending", err));
	else
		TraceOutput(TL(appErrorClass + 1, "SendGamePacket: Sending type %hi, row %hi, column %hi", type, x, y));


	return err;
}


/***********************************************************************
 *
 * FUNCTION:    AcceptGamePacket
 *
 * DESCRIPTION: Accept the incoming game packet
 *
 * PARAMETERS:  Exchange socket pointer and flag that indicates if
 *              application is already running
 *
 * RETURNED:    0 on sucess or an error code
 *
 ***********************************************************************/
static Err AcceptGamePacket(ExgSocketPtr exgSocketP, Boolean isRunning)
{
	Err					err = errNone;
	EventType			event;
	GamePacketType		packet;
	Char *				urlP;

	// Accept the incoming object
	err = ExgAccept(exgSocketP);
	ErrFatalDisplayIf(err, "AcceptGamePacket: cannot ExgAccept");

	// Receive the game packet and disconnect
	ExgReceive(exgSocketP, &packet, sizeof(GamePacketType), &err);
	ExgDisconnect(exgSocketP, err);

	if (err == exgErrUserCancel)
		TraceOutput(TL(appErrorClass + 1, "AcceptGamePacket: User canceled"));
	else if (err != errNone)
		TraceOutput(TL(appErrorClass + 1, "AcceptGamePacket: *** Error %hx while receiving", err));
	else
		TraceOutput(TL(appErrorClass + 1, "AcceptGamePacket: Type %hu x %hu y %hu", packet.type, packet.x, packet.y));
	if (err)
		return err;
		
	if (isRunning)
	{
		// We receive something while the application is active
		// If we're idle, copy the URL the game packet in our globals
		if (gState == kStateIdle)
			GetUrlFromSocketRef(exgSocketP, gOpponentURL, kMaxUrlSize);
		MemMove(&gPacket, &packet, sizeof(GamePacketType));
			
		// Now indirectly continue in ProcessGamePacket function
		// We must go through the event loop before reusing the BT Exg lib.
		MemSet(&event, sizeof(event), 0);
		event.eType = kEventProcessGamePacket;
		EvtAddEventToQueue(&event);
	}
	else
	{
		// We received something while not beeing the active app
		// If it's a game request, ask ExgMgr to launch us,
		// and pass it the URL
		if (packet.type == kGameRequest)
		{
			TraceOutput(TL(appErrorClass + 1, "AcceptGamePacket: Received a game request, switching to Tic Tac Toe"));
			urlP = MemPtrNew(kMaxUrlSize);
			if (!urlP)
				return sysErrNoFreeRAM;		
			MemPtrSetOwner(urlP, 0);
			// urlP will be copied in globals and freed later in GotoGameStart
			GetUrlFromSocketRef(exgSocketP, urlP, kMaxUrlSize);
			exgSocketP->goToParams.matchCustom = (UInt32)urlP;
			exgSocketP->goToCreator = kAppFileCreator;
		}
		else
			TraceOutput(TL(appErrorClass + 1, "AcceptGamePacket: Was expecting a game request, received %hu", packet.type));
	}
	
	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    ProcessGamePacket
 *
 * DESCRIPTION: Process the game packet, eventually reply to it
 *
 * PARAMETERS:  None
 *
 * RETURNED:    0 on sucess or an error code
 *
 ***********************************************************************/
static void ProcessGamePacket()
{
	TraceOutput(TL(appErrorClass + 1,"ProcessGamePacket: Going to reply to Type %hu x %hu y %hu", gPacket.type, gPacket.x, gPacket.y));

	switch (gState)
	{
	case kStateIdle:
		// If idle and receiving a game request, reply with an acknowledgement
		if(gPacket.type == kGameRequest)
			StartNewGame(false);
		else
			TraceOutput(TL(appErrorClass + 1, "ProcessGamePacket:kStateIdle: Dropped an unexpected game packet!"));
		return;
		
	case kStateStarting:
		// After sending a game request, expect to receive an acknowledgement
		if (gIsInitiator && gPacket.type == kGameAck)
			SetState(kStateYourTurn);
		else
			TraceOutput(TL(appErrorClass + 1, "ProcessGamePacket:kStateStarting: Dropped an unexpected game packet!"));
		return;
		
	case kStateOpponentTurn:
		// While it's the opponent's turn, expect a move packet or a cancel indication
		switch(gPacket.type)
		{
		case kGameCancel:
			EndGame();
			return;
		case kGameMove:
			gGameBoard[gPacket.x][gPacket.y] = (gIsInitiator ? kSquareCross : kSquareCircle);
			DrawSquare(gPacket.x, gPacket.y);
			SetState(kStateYourTurn);
			CheckWinLossDraw();
			return;
		default:
			TraceOutput(TL(appErrorClass + 1, "ProcessGamePacket:kStateOpponentTurn: Dropped an unexpected game packet!"));
			return;
		}
		
	case kStateYourTurn:
		// While it's your turn, only expect a cancel indication
		if (gPacket.type == kGameCancel)
			EndGame();
		else
			TraceOutput(TL(appErrorClass + 1, "ProcessGamePacket:kStateYourTurn: Dropped an unexpected game packet!"));
		return;
		
	default:
		TraceOutput(TL(appErrorClass + 1, "ProcessGamePacket:Other: Dropped an unexpected game packet!"));
		return;
	}
}


/***********************************************************************
 *
 * FUNCTION:    ConfirmGameStart
 *
 * DESCRIPTION: Display "Do you want to play with device X?"
 *
 * PARAMETERS:  Exchange socket pointer and flag that indicates if
 *              application is already running
 *
 * RETURNED:    Nothing
 *
 ***********************************************************************/
static void ConfirmGameStart(ExgAskParamPtr exgP, Boolean isRunning)
{
	UInt16					refNum;
	Err						err;
	BtLibDeviceAddressType	btAddress;
	BtLibFriendlyNameType	friendly;
	Char					url[kMaxUrlSize];
	Char					name[btLibMaxDeviceNameLength];
	Char 					*btAddrString;
	
	// Auto accept game packet, only the game start needs to be confirmed
	if (isRunning && gState != kStateIdle)
	{
		exgP->result = exgAskOk;
		return;
	}
	
	// Get the opponent URL and extract the BT device address
	GetUrlFromSocketRef(exgP->socketP, url, sizeof(url));
	ErrFatalDisplayIf(StrNCompare(url, btexgPrefix, StrLen(btexgPrefix)) != 0,"ConfirmGameStart: invalid URL");
	btAddrString = url + StrLen(btexgPrefix);
	*(StrStr(btAddrString, btexgURLSeparator)) = '\0'; // To isolate the BT address
	TraceOutput(TL(appErrorClass + 1,"ConfirmGameStart: Received game request from '%s'", btAddrString));
	
	// Get the opponent device name from its BT address
	// At this point the BtLib is already loaded
	err = SysLibFind(btLibName, &refNum);
	ErrFatalDisplayIf(err != 0, "ConfirmGameStart: BT lib not found");
	BtLibAddrAToBtd(refNum, btAddrString, &btAddress);
	friendly.name = (UInt8*) name;
	friendly.nameLength = sizeof(name);
	err = BtLibGetRemoteDeviceName(refNum, &btAddress, &friendly, btLibCachedOnly);
	if (err)
		StrCopy(name, btAddrString); // In case, use BT address
	
	// Ask user to confirm start of game
	exgP->result = 
		FrmCustomAlert(ConfirmGameStartAlert, name, NULL, NULL) == ConfirmGameStartYes ?
		exgAskOk : exgAskCancel;
}


/***********************************************************************
 *
 * FUNCTION:    GotoGameStart
 *
 * DESCRIPTION: While sublaunched by the Exchange Manager, memorize
 *              the initiator BT address. A new game will start with it.
 *
 * PARAMETERS:  GotoParamsType *
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void GotoGameStart(GoToParamsPtr gotoP)
{
	if (gotoP->matchCustom)
	{
		StrCopy(gOpponentURL, (Char*)gotoP->matchCustom);
		MemPtrFree((Char*)gotoP->matchCustom);
	}
	gState = kStateConnecting;
}


/***********************************************************************
 *
 * FUNCTION:    GetUrlFromSocketRef
 *
 * DESCRIPTION: Get the URL from a socket reference, after a ExgPut
 *				or a ExgAccept.
 *
 * PARAMETERS:  In: the socket, an empty buffer and its size
 *              Out: the URL
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void GetUrlFromSocketRef(ExgSocketPtr exgSocketP, Char *url, UInt16 urlSize)
{
	ExgCtlGetURLType	getUrl;
	UInt16				getUrlLen;
	Err					err;
	
	// Get URL size
	getUrl.socketP = exgSocketP;
	getUrl.URLP = NULL;
	getUrl.URLSize = 0;
	getUrlLen =  sizeof(getUrl);
	err = ExgControl(exgSocketP, exgLibCtlGetURL, &getUrl, &getUrlLen);
	ErrFatalDisplayIf(err,"GetUrlFromSocketRef: cannot get size of URL");
	
	// Now get URL with the right size
	getUrl.URLP = MemPtrNew(getUrl.URLSize);
	ExgControl(exgSocketP, exgLibCtlGetURL, &getUrl, &getUrlLen);
	ErrFatalDisplayIf(urlSize <= getUrlLen + StrLen(kExgFile), "GetUrlFromSocketRef: URL too long");
	StrPrintF(url, "%s%s", getUrl.URLP, kExgFile);
	MemPtrFree(getUrl.URLP);
}
	
#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    SetFieldTextFromHandle
 *
 * DESCRIPTION: Change the field text from a handle. Free the old handle
 *				Must be an editable field.
 *
 * PARAMETERS:  The field Id and the text handle
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void SetFieldTextFromHandle(UInt16 fieldId, MemHandle txtH)
{
	MemHandle 	oldTextH;
	FormPtr		frmP;
	FieldPtr	fieldP;

	/* Get the field and the field's current text handle */
	frmP = FrmGetFormPtr(MainForm);
	fieldP = FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, fieldId));
	oldTextH = FldGetTextHandle(fieldP);
	
	/* Set the field text to the new text */
	FldSetTextHandle(fieldP, txtH);
	FldDrawField(fieldP);
	
	/* Free the handle AFTER we call FldSetTextHandle() */
	if (oldTextH)
		MemHandleFree(oldTextH);
	
}

/***********************************************************************
 *
 * FUNCTION:    SetState
 *
 * DESCRIPTION: Update the global state and the status field
 *
 * PARAMETERS:  The new state
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void SetState(StateEnumType state)
{
	MemHandle	newTextH = MemHandleNew(kMaxStatusSize);
	MemPtr		newTextP = MemHandleLock(newTextH);
	
	SysStringByIndex(StatusStringList, state, newTextP, kMaxStatusSize);
	TraceOutput(TL(appErrorClass + 1, "SetState: now is '%s'", newTextP));
	MemHandleUnlock(newTextH);
	SetFieldTextFromHandle(MainStatusField, newTextH);

	gState = state;
}


/***********************************************************************
 *
 * FUNCTION:    DrawSquare
 *
 * DESCRIPTION: Draw the square content at position x,y
 *
 * PARAMETERS:  x and y - column and row
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void DrawSquare(Coord x, Coord y)
{
	Coord			squareX, squareY;
	RectangleType	box;

	// The cross or the circle uses 3/5 of the square size and is centered,
	// leaving 1/5 of free space on each side.
	squareX = gBounds.topLeft.x + gSquareSize * x + gSquareSize / 5;
	squareY = gBounds.topLeft.y + gSquareSize * y + gSquareSize / 5;

	// Erase previous drawing
	box.topLeft.x = squareX - gSquareSize / 5 + 1;
	box.topLeft.y = squareY - gSquareSize / 5 + 1;
	box.extent.x = gSquareSize - 1;
	box.extent.y = gSquareSize - 1;
	WinEraseRectangle(&box, 0);
	
	// And draw the new one
	switch (gGameBoard[x][y])
	{
	
	case kSquareEmpty:
		break;
		
	case kSquareCircle:
		box.topLeft.x = squareX;
		box.topLeft.y = squareY;
		box.extent.x = gSquareSize * 3 / 5;
		box.extent.y = box.extent.x;
		WinDrawRectangle(&box, (UInt16)(box.extent.x / 2));
		box.topLeft.x++; 
		box.topLeft.y++;
		box.extent.x -=2; 
		box.extent.y = box.extent.x; 
		WinInvertRectangle(&box, (UInt16)(box.extent.x / 2));
		break;
		
	case kSquareCross:
		WinDrawLine(squareX, squareY, squareX + gSquareSize * 3 / 5, squareY + gSquareSize * 3 / 5);
		WinDrawLine(squareX, squareY + gSquareSize * 3 / 5, squareX + gSquareSize * 3 / 5, squareY);
		break;
		
	case kSquareTemporary:
		WinDrawRectangle(&box, 0);
		break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    StartNewGame
 *
 * DESCRIPTION: Start a new game, as an initiator or as the acceptor
 *
 * PARAMETERS:  true for initiator, false for acceptor
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void StartNewGame(Boolean isInitiator)
{
	Err 	err = errNone;
	FormPtr	frmP = FrmGetFormPtr(MainForm);
	
	if (gState == kStateIdle || (!isInitiator && gState == kStateConnecting))
	{
		FrmHideObject (frmP, FrmGetObjectIndex(frmP, MainStartButton));
		FrmShowObject (frmP, FrmGetObjectIndex(frmP, MainCancelButton));	
			
		gIsInitiator = isInitiator;
		gMoveCount = 0;
		MemSet(&gGameBoard, sizeof(gGameBoard), 0);
		FrmDrawForm ( frmP);

		// Send either a game request or a game acknowledgment
		if (isInitiator)
		{
			SetState(kStateConnecting);
			err = SendGamePacket(kGameRequest, 0, 0);
			SetState(kStateStarting);
		}
		else
		{
			SetState(kStateStarting);
			err = SendGamePacket(kGameAck, 0, 0);
			SetState(kStateOpponentTurn);
		}
		
		if (err)
			EndGame();
			
	}
	else
		FrmAlert(GameInProgressAlert);
}


/***********************************************************************
 *
 * FUNCTION:    EndGame
 *
 * DESCRIPTION: Back to idle mode
 *
 * PARAMETERS:  none
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void EndGame()
{
	FormPtr			frmP = FrmGetFormPtr(MainForm);
	FrmHideObject (frmP, FrmGetObjectIndex(frmP, MainCancelButton));
	FrmShowObject (frmP, FrmGetObjectIndex(frmP, MainStartButton));
	SetState(kStateIdle);
}


/***********************************************************************
 *
 * FUNCTION:    CancelGame
 *
 * DESCRIPTION: Cancel current game, if any. Send a cancel packet.
 *
 * PARAMETERS:  none
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void CancelGame()
{
	Err err;
	switch (gState)
	{
	
	case kStateYourTurn:
	case kStateOpponentTurn:
		err = SendGamePacket(kGameCancel, 0, 0);
		if (err != exgErrUserCancel)
			EndGame();
			
	case kStateStarting:
		EndGame();
		break;
	}
}


/***********************************************************************
 *
 * FUNCTION:    CheckWinLossDraw
 *
 * DESCRIPTION: Check if a player wins (n pawns aligned in any direction)
 *				or if game is a draw
 *
 * PARAMETERS:  none
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void CheckWinLossDraw()
{
	Coord	x, y;
	UInt16	winHoriz, winVert, winDiag1, winDiag2;
	UInt16	win, draw;
		
	// Check for Win/Loss
	// On each row, column and diagonal, we do an AND operation.
	// For example, if the result is kSquareCross, it means that an entire
	// line contains crosses and that the acceptor wins.
	win = kSquareEmpty;
	winDiag1 = winDiag2 = kSquareCross + kSquareCircle;
	for (x = 0; x < kGameBoardSize && !win; x++)
	{	
		winHoriz = winVert = kSquareCross + kSquareCircle;
		for (y=0; y < kGameBoardSize; y++)
		{
			winVert &= gGameBoard[x][y];
			winHoriz &= gGameBoard[y][x];
		}
		win = winHoriz | winVert;
		winDiag1 &= gGameBoard[x][x];
		winDiag2 &= gGameBoard[x][kGameBoardSize-1 - x];
	}
	win |= winDiag1 | winDiag2;
	
	if(win == kSquareCircle) // The initiator plays with circles
		FrmAlert( (UInt16)(gIsInitiator ? YouWinAlert : YouLoseAlert ) );
	else if (win == kSquareCross) // The acceptor plays with crosses
		FrmAlert( (UInt16)(gIsInitiator ? YouLoseAlert : YouWinAlert) );
	else
	{
		// Draw game is declared when game board is full
		gMoveCount++;
		draw = (UInt16)(gMoveCount == kGameBoardSize * kGameBoardSize);
		if (draw)
			FrmAlert(DrawGameAlert);
	}
	
	if (win || draw)
		EndGame();
}

#pragma mark -

/***********************************************************************
 *
 * FUNCTION:    GameBoardHandler
 *
 * DESCRIPTION: Event handler for the game board gadget 
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event was handled
 *
 ***********************************************************************/

static Boolean GameBoardHandler (struct FormGadgetTypeInCallback * gadgetP, UInt16 cmd, void *paramP)
{
	Coord			squareX, squareY;
	Coord			x, y;
	EventPtr		eventP;
	
	switch (cmd)
	{
	
	case formGadgetDrawCmd:
		
		TraceOutput(TL(appErrorClass + 1, "GameBoardHandler: formGadgetDrawCmd"));
		// Draw the squares' pattern
		for (x=0; x <= kGameBoardSize; x++)
		{
			squareX = gBounds.topLeft.x + x * gSquareSize;
			squareY = gBounds.topLeft.y + x * gSquareSize;
			WinDrawLine(squareX, gBounds.topLeft.y, squareX, gBounds.topLeft.y + gBounds.extent.y);
			WinDrawLine(gBounds.topLeft.x, squareY, gBounds.topLeft.x + gBounds.extent.x, squareY);
		}	
		// And now the squares' content
		for (x=0; x < kGameBoardSize; x++)
			for (y=0; y < kGameBoardSize; y++)
				DrawSquare(x, y);

		gadgetP->attr.visible = true;
		return true;

	case formGadgetHandleEventCmd:
		eventP = (EventPtr)paramP;
		switch (eventP->eType)
		{
		
		case frmGadgetEnterEvent:
			// Locate the tap and identify the square
			x = (eventP->screenX - gBounds.topLeft.x) / gSquareSize;
			y = (eventP->screenY - gBounds.topLeft.y) / gSquareSize;
			TraceOutput(TL(appErrorClass + 1, "GameBoardHandler: Tap at %hu, %hu", x, y));
			if (gState == kStateYourTurn)
			{				
				// Check that it's empty
				if (gGameBoard[x][y] == kSquareEmpty)
				{
					gGameBoard[x][y] = kSquareTemporary;
					DrawSquare(x, y);					
					// Send the move to the opponent.
					switch (SendGamePacket(kGameMove, x, y))
					{
					case errNone:
						// Update the board. Check for win/loss/draw
						gGameBoard[x][y] = (gIsInitiator ? kSquareCircle : kSquareCross);
						DrawSquare(x, y);
						SetState(kStateOpponentTurn);
						CheckWinLossDraw();
						break;					
					case exgErrUserCancel:
						// Move canceled
						gGameBoard[x][y] = kSquareEmpty;
						DrawSquare(x, y);
						break;
					default:
						// Any other error: end game
						EndGame();
					}
				}
			}
			else
			{
				// Flash effect on the square tapped, plus a beep to warn user that
				// it's not his turn
				SquareEnumType realContent = gGameBoard[x][y];
				gGameBoard[x][y] = kSquareTemporary;
				DrawSquare(x, y);
				SndPlaySystemSound(sndWarning);
				SysTaskDelay(SysTicksPerSecond()/20);
				gGameBoard[x][y] = realContent;
				DrawSquare(x, y);
			}
			return true;
			
		default:
			return false;
		}
		
	default:
		return false;
	}
}


/***********************************************************************
 *
 * FUNCTION:    MainFormHandler
 *
 * DESCRIPTION: This is the event handler of the main form
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event was handled
 *
 ***********************************************************************/
static Boolean MainFormHandler(EventPtr eventP)
{
	FormPtr	frmP;
	
	switch (eventP->eType) 
	{
	case menuEvent:
		switch (eventP->data.menu.itemID)
		{

		case MainOptionsStartanewgame:
			StartNewGame(true);
			return true;
	
		case MainOptionsCancelcurrentgame:
			// Cancel current game. If gremlins are running, ignore 98% of taps
			if (!HostGremlinIsRunning() || (UInt32)SysRandom(0) * 100L / sysRandomMax <= 1)
				CancelGame();
			return true;

		case MainOptionsAboutTicTacToe:		
			MenuEraseStatus(0);
			AbtShowAbout(kAppFileCreator);
			return true;
			
		default:
			return false;
		}

	case frmOpenEvent:
		// Get game board bounds and calculate square size
		frmP = FrmGetActiveForm();
		FrmSetGadgetHandler(frmP, FrmGetObjectIndex(frmP, MainGameBoardGadget), GameBoardHandler);
		FrmGetObjectBounds(frmP, FrmGetObjectIndex(frmP, MainGameBoardGadget), &gBounds);
		gSquareSize = gBounds.extent.x / kGameBoardSize;
		FrmDrawForm ( frmP);
		if (gState == kStateConnecting)
			StartNewGame(false);
		else
			SetState(kStateIdle);
		return true;

	// Transform a button event in its equivallent menu event
	case ctlSelectEvent:
		switch (eventP->data.ctlSelect.controlID)
		{
		case MainStartButton:
			eventP->eType = menuEvent;
			eventP->data.menu.itemID = MainOptionsStartanewgame;
			EvtAddEventToQueue(eventP);
			return true;
		case MainCancelButton:
			eventP->eType = menuEvent;
			eventP->data.menu.itemID = MainOptionsCancelcurrentgame;
			EvtAddEventToQueue(eventP);
			return true;
		}
				
	default:
		return false;		
	}
}


/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: Handle application events, after the system but before
 *              the forms.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event was handled
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventPtr eventP)
{
	UInt16	frmId;
	FormPtr	frmP;

	switch (eventP->eType)
	{
	case frmLoadEvent:
		// Load the requested form resource.
		frmId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(frmId);
		FrmSetActiveForm(frmP);
		// And set its event
		if (frmId == MainForm)
			FrmSetEventHandler(frmP, MainFormHandler);
		return true;

	case kEventProcessGamePacket:
		ProcessGamePacket();
		return true;
	}
	
	return false;
}


/***********************************************************************
 *
 * FUNCTION:     AppStart
 *
 * DESCRIPTION:  Initialize the application
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value or 0 if nothing went wrong
 *
 ***********************************************************************/
static void AppStart(void)
{
	gState = kStateIdle;
	ExgRegisterData(kAppFileCreator, exgRegExtensionID, kExgFileExt);
	FrmGotoForm(MainForm);
}


/***********************************************************************
 *
 * FUNCTION:    AppEventLoop
 *
 * DESCRIPTION: The application event loop.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	Err			err;
	EventType	event;

	do
	{
		EvtGetEvent(&event, evtWaitForever);
		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &err))
				if (! AppHandleEvent(&event))
					FrmDispatchEvent(&event);
	} while (event.eType != appStopEvent);
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
	FrmCloseAllForms ();
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: The application entry point.
 *
 * PARAMETERS:  cmd - integer value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  integer value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt32	btVersion;

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
		TraceOutput(TL(appErrorClass + 1,"PilotMain: application started"));
		AppStart();
		AppEventLoop();
		AppStop();
		return errNone;

	case sysAppLaunchCmdSyncNotify:
	case sysAppLaunchCmdSystemReset:
		// Register our extension on SyncNotify so we do not need to
		// be run before we can receive data. Also register on reset for Poser.
		TraceOutput(TL(appErrorClass + 1,"PilotMain: received sysAppLaunchCmdSyncNotify"));
		ExgRegisterData(kAppFileCreator, exgRegExtensionID, kExgFileExt);
		return errNone;
		
	case sysAppLaunchCmdExgAskUser:
		TraceOutput(TL(appErrorClass + 1,"PilotMain: received sysAppLaunchCmdExgAskUser"));
		ConfirmGameStart(cmdPBP, (Boolean)(launchFlags & sysAppLaunchFlagSubCall));
		return errNone;

	case sysAppLaunchCmdExgReceiveData:
		TraceOutput(TL(appErrorClass + 1,"PilotMain: received sysAppLaunchCmdExgReceiveData"));
		AcceptGamePacket(cmdPBP, (Boolean)(launchFlags & sysAppLaunchFlagSubCall));
		return errNone;

	case sysAppLaunchCmdGoTo:
		TraceOutput(TL(appErrorClass + 1,"PilotMain: received sysAppLaunchCmdExgGoto"));
		if (launchFlags & sysAppLaunchFlagNewGlobals)
		{
			AppStart();
			GotoGameStart(cmdPBP);
			AppEventLoop();
			AppStop();
		}
		return errNone;

	default:
		return errNone;

	}
	
}
