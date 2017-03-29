/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: PuzzleApp.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *	  This is the main source module for the Puzzle(15) game.
 *
 *****************************************************************************/

#include <PalmOS.h>

#include "PuzzleRsc.h"

/***********************************************************************
 *
 *	Entry Points
 *
 ***********************************************************************/


/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
#define puzzleAppCreator					'puzl'

#define version20					0x02000000

#define boardX					18
#define boardY					26


#define pieceWidth			30
#define pieceHeight			30

#define pieceCornerDiameter	7

#define pieceFrameWidth		1
#define pieceSpace			pieceFrameWidth		// space between pieces
#define boardFrameMargin	pieceFrameWidth
#define boardFrameWidth		3

#define boardRows				4
#define boardColumns			4

#define numPositions	(boardRows * boardColumns)

#define minRow					0
#define minColumn				0
#define maxRow					(boardRows - 1)					// 0-based
#define maxColumn				(boardColumns - 1)				// 0-based

#define emptySquareID		0

// Number of moves the puzzle is shuffled from a solved position
#define numShuffleMoves		700


/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/
typedef struct PieceCoordType {
	Int16		row;							// 0-based
	Int16		col;							// 0-based
	} PieceCoordType;


typedef union GameBoardType {
	UInt8		square[numPositions];
	UInt32	save[(numPositions+3)/4];
	} GameBoardType;


/***********************************************************************
 *
 *	Private global variables
 *
 ***********************************************************************/
static GameBoardType	GameBoard;
static Int16				EmptyPos;


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/
static UInt16 StartApplication (void);
static void StopApplication (void);
static Boolean MainFormDoCommand (UInt16 command);
static void MainFormInit (FormPtr frm);
static Boolean MainFormHandleEvent (EventPtr event);
static void AppEventLoop (void);


static void		InitGameBoard(void);
static Int16	CoordToPosition(PieceCoordType coord);
static PieceCoordType	PositionToCoord(Int16 pos);
static Int16	GetEmptyPos(void);
static void		MoveOnePiece(Int16 from, Boolean draw);
static void		MoveRange(Int16 from, Boolean draw);
static void		DrawGameBoard(void);
static Int16	MapPenPosition(Int16 penX, Int16 penY);
static void		DrawPiece(Int16 pos);
static void		ShuffleGameBoard(UInt32 moves);
static void		SaveGameBoard(void);
static void		LoadGameBoard(void);



#if 0				// CASTRATED
/***********************************************************************
 *
 * FUNCTION:     PrvRandomNum
 *
 * DESCRIPTION:	Generate a pseudo-random number using Linear Congruential
 *						Method from Sedgewick.
 *
 *						The logic is as follows:
 *
 *						a = current random seed
 *						a1 = next random seed
 *						b = random constant "b"
 *						m = random constant "m"
 *						r = result range (the result will be >= 0 and < r)
 *
 *						Equation to generate the next random seed:
 *							(a * b + 1) mod m.
 *
 *						Equation to apply the range to the random seed:
 *							(a * r) mod m.  Using this method for applying the
 *							range avoids anomalies by using the middle part of
 *							a1 (Knuth).
 *
 *						Here is how it all works:
 *
 *						(a * b + 1) mod m  produces a1 (0 <= a1 < m).
 *						a1 can be expressed as (m - k), where 0 < k <= m.
 *						The range is applied to a1 by the formula (a1 * r) div m.
 *						This can be expressed as ((m - k) * r) div m, or
 *						(mr - kr) div m.  Since mr >= kr, 0 <= (mr - kr) < mr.
 *						Therefore, the result of
 *						((mr - kr) div m) is less than r and greater than or equal
 *						to zero(vmk).
 *
 * PARAMETERS:	range		-- limits the result to: 0 - (range - 1)
 *
 * RETURNED:	pseudo-random number
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static UInt16 PrvRandomNum(UInt16 range)
{
	return( (UInt16)SysRandom( 0 ) % range );
}
#endif	// 0				// CASTRATED


/***********************************************************************
 *
 * FUNCTION:     InitGameBoard
 *
 * DESCRIPTION:	Generate a new game.
 *
 * PARAMETERS:	none
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void InitGameBoard(void)
{
	UInt8		i;
	for ( i=0; i < (numPositions - 1); i++ )
		GameBoard.square[i] = i + 1;
	GameBoard.square[numPositions - 1] = emptySquareID;
	EmptyPos = numPositions - 1;
}


/***********************************************************************
 *
 * FUNCTION:     ShuffleGameBoard
 *
 * DESCRIPTION:	Shuffle the game board, updating it visually with each
 *						step.
 *
 * PARAMETERS:	moves		-- number of moves to shuffle
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/20/95	Initial Version
 *
 ***********************************************************************/
static void ShuffleGameBoard(UInt32 moves)
{
	UInt16		rand;
	PieceCoordType	coord;


	InitGameBoard();
	
	do	{
		rand = (UInt16)SysRandom( 0 ) % 8;				// generate 0-7
		coord = PositionToCoord( EmptyPos );
		if ( rand & 4L )
			coord.row = (Int16)(rand & 3L);
		else
			coord.col = (Int16)(rand & 3L);
		MoveRange( CoordToPosition(coord), false/*draw*/ );
		}
	while ( --moves );
}


/***********************************************************************
 *
 * FUNCTION:     SaveGameBoard
 *
 * DESCRIPTION:	Save game in the feature registry.
 *
 * PARAMETERS:	none
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void SaveGameBoard(void)
{
	UInt16		featureNum;
	UInt16		numFeatures;
	
	numFeatures = sizeof(GameBoard.save) / sizeof(GameBoard.save[0]);
	
	for ( featureNum = 0; featureNum < numFeatures; featureNum++ )
		FtrSet( puzzleAppCreator, featureNum, GameBoard.save[featureNum] );
}


/***********************************************************************
 *
 * FUNCTION:     LoadGameBoard
 *
 * DESCRIPTION:	Load saved game from the feature registry.
 *
 * PARAMETERS:	none
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void LoadGameBoard(void)
{
	Err		err = 0;
	UInt16		featureNum;
	UInt16		numFeatures;
	
	numFeatures = sizeof(GameBoard.save) / sizeof(GameBoard.save[0]);
	
	// Load game board from feature registry
	for ( featureNum = 0; featureNum < numFeatures; featureNum++ )
		{
		err = FtrGet( puzzleAppCreator, featureNum, &GameBoard.save[featureNum] );
		if ( err )	break;
		}

	// Initialize the board of load failed
	if ( !err  )
		{
		EmptyPos = GetEmptyPos();
		}
	else
		{
		InitGameBoard();
		}
}


/***********************************************************************
 *
 * FUNCTION:     GetEmptyPos
 *
 * DESCRIPTION:	Get position of the empty square
 *
 * PARAMETERS:	none
  *
 * RETURNED:	position of the empty square(0-based)
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static Int16 GetEmptyPos(void)
{
	Int16		pos;
	
	for ( pos=0; pos < numPositions; pos++ )
		if ( GameBoard.square[pos] == emptySquareID )
			return( pos );
	
	ErrDisplay( "didn't find empty square position" );
	return( 0 );
}


/***********************************************************************
 *
 * FUNCTION:     CoordToPosition
 *
 * DESCRIPTION:	Convert row and column pair to a 0-based position
 *
 * PARAMETERS:	coord		-- piece row and column
  *
 * RETURNED:	piece position (0-based)
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static Int16 CoordToPosition(PieceCoordType coord)
{
	return( (coord.row * boardColumns) + coord.col );
}


/***********************************************************************
 *
 * FUNCTION:     PositionToCoord
 *
 * DESCRIPTION:	Convert a 0-based position to row and column pair
 *
 * PARAMETERS:	pos		-- piece position (0-based)
 *
 * RETURNED:	row and column
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static PieceCoordType PositionToCoord(Int16 pos)
{
	PieceCoordType		coord;
	
	ErrFatalDisplayIf( pos >= numPositions, "pos out of bounds" );

	coord.row = pos / boardColumns;
	coord.col = pos % boardColumns;
	
	return( coord );
}


/***********************************************************************
 *
 * FUNCTION:     MapPenPosition
 *
 * DESCRIPTION:	Map a screen-relative pen position to a game piece
 *						position;
 *
 * PARAMETERS:	penX		-- display-relative x position
 *					penY		-- display-relative y position
 *
 * RETURNED:	piece position (0-based)
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static Int16 MapPenPosition(Int16 penX, Int16 penY)
{
	Int16		x;
	Int16		y;
	RectangleType	rect;
	PieceCoordType	coord;
	
	// Map display relative coordinates to window-relative
	x = (Int16)penX;
	y = (Int16)penY;
	WinDisplayToWindowPt( &x, &y );
	
	rect.topLeft.x = boardX + boardFrameMargin;
	rect.topLeft.y = boardY + boardFrameMargin;
	rect.extent.x = (boardColumns * pieceWidth) +
			((boardColumns - 1) * pieceSpace);
	rect.extent.y = (boardRows * pieceHeight) +
			((boardRows - 1) * pieceSpace);
	
	if ( !RctPtInRectangle(x, y, &rect) )
		return( -1 );
	
	// Convert to board-relative coordinates
	x -= boardX;
	y -= boardY;
	
	if ( x < 0 )
		{
		ErrDisplay( "board x is negative" );
		x = 0;
		}
	if ( y < 0 )
		{
		ErrDisplay( "board y is negative" );
		y = 0;
		}
	
	// Get the piece position
	coord.col = x / (pieceWidth + pieceSpace);
	coord.row = y / (pieceHeight + pieceSpace);
	if ( coord.col > maxColumn )
		{
		ErrDisplay( "column out of bounds" );
		coord.col = maxColumn;
		}
	if ( coord.row > maxRow )
		{
		ErrDisplay( "row out of bounds" );
		coord.row = maxRow;
		}
	
	return( CoordToPosition(coord) );
}


/***********************************************************************
 *
 * FUNCTION:     DrawPiece
 *
 * DESCRIPTION:	Draw a game piece
 *
 * PARAMETERS:	pos		-- piece position (0-based)
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void DrawPiece(Int16 pos)
{
	RectangleType	rect;
	PieceCoordType	coord;
	FontID			oldFontID;
	
	ErrFatalDisplayIf( pos >= numPositions, "pos out of bounds" );
	
	// Compute the piece rectangle
	coord = PositionToCoord( pos );
	//PrvPieceCoordToRect( coord, &rect );
	rect.topLeft.x = boardX + boardFrameMargin + (pieceWidth * coord.col) +
			(coord.col * pieceSpace);
	rect.topLeft.y = boardY + boardFrameMargin + pieceHeight *coord.row +
			(coord.row * pieceSpace);
	rect.extent.x = pieceWidth;
	rect.extent.y = pieceHeight;
	
	// Erase the old piece

	// If this is the empty square, erase the old game piece
	if ( GameBoard.square[pos] == emptySquareID )
		{
		RectangleType	erase;
	
		WinEraseRectangle( &rect, 0/*cornerDiam*/ );
		
		// Clean up the pieces of frame around board edges
		if ( coord.col == minColumn )
			{
			erase = rect;
			erase.topLeft.x -= pieceFrameWidth;
			erase.topLeft.y -= pieceFrameWidth;
			erase.extent.x = pieceFrameWidth;
			erase.extent.y = pieceHeight + (pieceFrameWidth * 2);
			WinEraseRectangle( &erase, 0/*cornerDiam*/ );
			}
		else if ( coord.col == maxColumn )
			{
			erase = rect;
			erase.topLeft.x += rect.extent.x;
			erase.topLeft.y -= pieceFrameWidth;
			erase.extent.x = pieceFrameWidth;
			erase.extent.y = pieceHeight + (pieceFrameWidth * 2);
			WinEraseRectangle( &erase, 0/*cornerDiam*/ );
			}
			
		if ( coord.row == minRow )
			{
			erase = rect;
			erase.topLeft.x -= pieceFrameWidth;
			erase.topLeft.y -= pieceFrameWidth;
			erase.extent.x = pieceWidth + (pieceFrameWidth * 2);
			erase.extent.y = pieceFrameWidth;
			WinEraseRectangle( &erase, 0/*cornerDiam*/ );
			}
		else if ( coord.row == maxRow )
			{
			erase = rect;
			erase.topLeft.x -= pieceFrameWidth;
			erase.topLeft.y += rect.extent.y;
			erase.extent.x = pieceWidth + (pieceFrameWidth * 2);
			erase.extent.y = pieceFrameWidth;
			WinEraseRectangle( &erase, 0/*cornerDiam*/ );
			}
		} // If this is the empty square, erase the old game piece
	
	// Erase the old piece frame
	else
		{
		// For now, we are always drawing new pieces over empty squares,
		// and do not need to erase anything
		//WinEraseRectangleFrame( frameBits.word, &rect );
		}
	
	//
	// Draw the new piece
	//
	
	if ( GameBoard.square[pos] != emptySquareID )
		{
		FrameBitsType	frameBits;
		Char				text[32];
		UInt16				textLen;
		Int16				textHeight;
		Int16				textWidth;
		Int16				x, y;
		
		// Draw the frame
		frameBits.word = 0;					// initialize the entire structure
		frameBits.bits.cornerDiam = pieceCornerDiameter;
		frameBits.bits.shadowWidth = 0;
		frameBits.bits.width = pieceFrameWidth;
		WinDrawRectangleFrame( frameBits.word, &rect );
		
		// Draw the label
		StrIToA( text, GameBoard.square[pos] );
		textLen = StrLen( text );
		oldFontID = FntSetFont( ledFont );
		textHeight = FntLineHeight();
		textWidth = FntCharsWidth( text, textLen );
		x = rect.topLeft.x + ((rect.extent.x - textWidth) / 2);
		y = rect.topLeft.y + ((rect.extent.y - textHeight) /2 );
		WinDrawChars( text, textLen, x, y);
		FntSetFont( oldFontID );
		}

}


/***********************************************************************
 *
 * FUNCTION:     DrawGameBoard
 *
 * DESCRIPTION:	Draw the game board
 *
 * PARAMETERS:	pos		-- piece position (0-based)
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *			vmk	12/17/97	Fixed drawing glitch by initializing the "word"
 *								field of frameBits.
 *
 ***********************************************************************/
static void DrawGameBoard(void)
{
	RectangleType	rect;
	Int16				i;
	FrameBitsType	frameBits;
	
	// Draw the board frame
	rect.topLeft.x = boardX;
	rect.topLeft.y = boardY;
	rect.extent.x = (boardColumns * pieceWidth) + (boardFrameMargin * 2) +
			((boardColumns - 1) * pieceSpace);
	rect.extent.y = (boardRows * pieceHeight) + (boardFrameMargin * 2) +
			((boardRows - 1) * pieceSpace);
	WinEraseRectangle( &rect, 0/*cornerDiam*/ );
	
	frameBits.word = 0;					// initialize the entire structure
	frameBits.bits.cornerDiam = 0;
	frameBits.bits.threeD = 0;
	frameBits.bits.shadowWidth = 0;
	frameBits.bits.width = boardFrameWidth;
	WinDrawGrayRectangleFrame ( frameBits.word, &rect );
	
	// Draw the game pieces
	for ( i=0; i < numPositions; i++ )
		DrawPiece(i);

	
}


/***********************************************************************
 *
 * FUNCTION:     MoveOnePiece
 *
 * DESCRIPTION:	Move a game piece to the empty position
 *
 * PARAMETERS:	from		-- piece position (0-based)
 *					draw		-- non-zero to update visually
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void MoveOnePiece(Int16 from, Boolean draw)
{
	Int16		newPos;
	
	ErrFatalDisplayIf( from >= numPositions, "from position out of bounds" );

	ErrFatalDisplayIf( EmptyPos != GetEmptyPos(), "EmptyPos is invalid" );

	newPos = EmptyPos;
	
	GameBoard.square[newPos] = GameBoard.square[from];
	GameBoard.square[from] = emptySquareID;
	EmptyPos = from;
	
	// Update display
	if ( draw )
		{
		DrawPiece( from );
		DrawPiece( newPos );
		}
}


/***********************************************************************
 *
 * FUNCTION:     MoveRange
 *
 * DESCRIPTION:	Shift game pieces to the empty position
 *
 *						Enforces rules for moving:
 *							the from piece must be in the same row or column
 *							as the empty square
 *
 * PARAMETERS:	from		-- first piece position (0-based)
 *					draw		-- non-zero to update visually
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void MoveRange(Int16 from, Boolean draw)
{
	PieceCoordType	emptyCoord;
	PieceCoordType	fromCoord;
	Int16		movePos;
	Int16		increment;

	ErrFatalDisplayIf( from >= numPositions, "from position out of bounds" );
	ErrFatalDisplayIf( EmptyPos != GetEmptyPos(), "EmptyPos is invalid" );
	
	if ( from == EmptyPos )
		return;
	
	// Make sure the from piece is in the same row or the same column
	// as the empty square
	fromCoord = PositionToCoord( from );
	emptyCoord = PositionToCoord( EmptyPos );
	
	// Are we in the same row as the empty square ?
	if ( fromCoord.row == emptyCoord.row )
		{
		// Are we to the left of the empty square ?
		if ( fromCoord.col < emptyCoord.col )
			{
			emptyCoord.col--;						// trash empty square coord
			movePos = CoordToPosition( emptyCoord );
			increment = -1;
			}
		// nope, we're to the right of the empty square
		else
			{
			emptyCoord.col++;						// trash empty square coord
			movePos = CoordToPosition( emptyCoord );
			increment = 1;
			}
		} // Are we in the same row as the empty square ?
		
	// Are we in the same column as the empty square ?
	else if ( fromCoord.col == emptyCoord.col )
		{
		// Are we above the empty square ?
		if ( fromCoord.row < emptyCoord.row )
			{
			emptyCoord.row--;						// trash empty square coord
			movePos = CoordToPosition( emptyCoord );
			increment = -1 * boardColumns;
			}
		// nope, we're below the empty square
		else
			{
			emptyCoord.row++;						// trash empty square coord
			movePos = CoordToPosition( emptyCoord );
			increment = boardColumns;
			}
		} // Are we in the same column as the empty square ?
	
	// Illegal move
	else
		{
		return;
		}
	
	
	// Move the pieces
	do	{
		MoveOnePiece( movePos, draw );
		if ( movePos == from )
			break;
		movePos += increment;
		}
	while (true);
}


/***********************************************************************
 *
 * FUNCTION:     StartApplication
 *
 * DESCRIPTION:	Initialize application.
 *
 *						Load board from features, or generate a new board
 *
 * PARAMETERS:   none
 *
 * RETURNED:     0 on success
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static UInt16 StartApplication (void)
{
	// Initialize the random number seed;
	SysRandom( TimGetSeconds() );
	
	LoadGameBoard();

	return( 0 );
}


/***********************************************************************
 *
 * FUNCTION:	StopApplication
 *
 * DESCRIPTION:	Save the current state of the application and close all
 *						forms.
 *
 * PARAMETERS:	none
 *
 * RETURNED:	nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void StopApplication (void)
{
	SaveGameBoard();
	FrmCloseAllForms ();
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
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			art	11/15/96	Initial Revision
 *
 ***********************************************************************/
static Err RomVersionCompatible (UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
		{
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
			{
			FrmAlert (RomIncompatibleAlert);
		
			// Pilot 1.0 will continuously relaunch this app unless we switch to 
			// another safe one.
			if (romVersion < 0x02000000)
				{
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
				}
			}
		
		return (sysErrRomIncompatible);
		}

	return (0);
}


/***********************************************************************
 *
 * FUNCTION:    MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    true if the command was handled
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static Boolean MainFormDoCommand (UInt16 command)
{
	Boolean		handled = false;

	MenuEraseStatus (0);

	switch (command)
		{
		case MainOptionsAboutCmd:
			AbtShowAbout (puzzleAppCreator);
			handled = true;
			break;

		case MainOptionsInstructions:
			FrmHelp (InstructionsStr);
			break;
					
		case MainOptionsSolvePuzzleCmd:
			InitGameBoard();
			DrawGameBoard();
			handled = true;
			break;
		}
		
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the "Main View"
 *
 * PARAMETERS:  frm  - a pointer to the MainForm form
 *
 * RETURNED:    nothing.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Version
 *
 ***********************************************************************/
static void MainFormInit (FormPtr frm)
{
}


/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the "Main View"
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	8/7/95	Initial Revision
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent (EventPtr event)
{
	FormPtr frm;
	Boolean handled = false;


	if (event->eType == ctlSelectEvent)
		{
		switch (event->data.ctlSelect.controlID)
			{
			case MainFormNewPuzzleButton:
				ShuffleGameBoard( numShuffleMoves );
				DrawGameBoard();
				handled = true;
				break;
				
			default:
				break;
			}
		}
	else if ( event->eType == penDownEvent )
		{
		Int16	from;
		from = MapPenPosition( event->screenX, event->screenY );
		if ( from >= 0 )
			{
			MoveRange( from, true/*draw*/ );
			handled = true;
			}
		}
	
				
	else if (event->eType == menuEvent)
		{
		return MainFormDoCommand (event->data.menu.itemID);
		}


	else if (event->eType == frmUpdateEvent)
		{
		FrmDrawForm (FrmGetActiveForm());
		DrawGameBoard();
		handled = true;
		}
	
		
	else if (event->eType == frmOpenEvent)
		{
		frm = FrmGetActiveForm();
		MainFormInit (frm);
		FrmDrawForm (frm);
		DrawGameBoard();
		handled = true;
		}
	
		
	else if (event->eType == frmCloseEvent)
		{
		}

	return (handled);
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
static Boolean AppHandleEvent( EventPtr eventP)
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

			default:
				ErrNonFatalDisplay("Invalid Form Load Event");
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

		// Check the heaps after each event
		#if EMULATION_LEVEL != EMULATION_NONE
			MemHeapCheck(0);
			MemHeapCheck(1);
		#endif

	} while (event.eType != appStopEvent);
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the Puzzle 
 *              application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    0
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	8/19/95	Initial Revision
 *
 ***********************************************************************/
 
UInt32 PilotMain (UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt16 error;

	error = RomVersionCompatible (version20, launchFlags);
	if (error) return (error);


	if ( cmd == sysAppLaunchCmdNormalLaunch )
		{
		error = StartApplication ();
		if (error) return (error);

		FrmGotoForm (MainForm);

		AppEventLoop ();
		StopApplication ();
		}

	return (0);
}
