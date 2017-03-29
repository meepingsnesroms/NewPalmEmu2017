/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: HardBall.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *	  This is considered PRE-ALPHA code!  It's intention is to demonstrate
 *   a working example of an animated game on the Pilot.  There are some
 *	  specific features worth studying for use in other games:
 *
 *		1) The timing of the game.  Waiting a constant period and then 
 *			drawing followed by updating the game state.
 *
 *		2) The handling of windows appearing above the game window.
 *
 *		3) The handling of the hard buttons.
 *
 *		4) The conversion of PICT resources (bitmaps) into window buffers
 *			for improved speed and to enable the use of masks (screen OR/ANDNOT)
 *
 *			Note: There is a patent covering the use of XORing an image in
 *			a buffer to the screen.  In order to use XORing, an agreement with 
 *			the patent holder must be reached. Typically, the patent holder requests
 *			two percent of the product's revenue.This patent expires in 1997.
 *
 *			HardBall does not contain XOR.
 *
 *		5) The handling of sound in the game. Includes priorities  and different sound 
 *			durations.
 *
 *		6) The handling of saving the game to state while switching to another app 
 *			and successfully restoring.
 *
 *		7) The design of a high score mechanism.
 *
 *
 *	  Comments: please send comments and bugs/fixes to Palm Computing for 
 *	  inclusion into further revisions. devsupp@palm.com
 *
 *
 *
 *	Model for Game World Updating
 *	
 *	The model below is used for animated games.  The idea is to draw the game
 *	state at regular time periods.  To this end, the first thing done, when a
 *	time period begins, is the game state is drawn.  Anything that is not a 
 *	draw operation is performed after.  Two copies of the game state are
 *	stored - the last and the next states.  This is useful for HardBall because
 *	if a ball becomes stuck in an object it is bounced from it's last position.
 *	After the game state is drawn the game state is advanced - the next state
 *	is moved to the last state.  Next, changes while the time period elaspses
 *	are made to form a new next state.  Buttons depressed by the user are
 *	polled and responded to.  Lastly, a sound is played.  The variable time
 *	until the beginning of the next time period is free to MemHandle system events.
 *	Also, when the prior routines take longer than average they consume part
 *	of the variable time.  If Graffiti characters were used, the recognition
 *	should happen during the variable time and the effect should be handled 
 *	when the next period elapses.
 *	
 *	
 *	The flow of a time period T:
 *	
 *	appStartEvent
 *		
 *		GameStatus.status = gameInitializing	// suspend updates
 *	
 *	frmOpenEvent	
 *	
 *		GameStart
 *			GameInitLevel
 *		GameStateDraw
 *	
 *	0T
 *	
 *		GameBallAdd
 *	
 *	nT
 *	
 *		GameStateDrawChanges			// erase last, draw next
 *		GameStateAdvance				// move next over last
 *		GameStateElapse				// calc new next, respond to pressed buttons
 *		GamePlaySounds					// play a sound
 *		variable time
 *	
 *	nT + T
 *	
 *	
 *	
 *	Things to change
 *	
 *	1) Add bricks that require multiple	bounces to break.  This is primarily
 * to assist the creation of interesting levels.  At this point, there are 
 * enough levels (few people have played them all) so this idea is not as 
 * useful and it will complicate the code. Eventually, it will probably be 
 * worthwhile to do because everyone will tire of the standard blocks.
 *	
 *	2) A interesting change to the code would be to change the ball motion
 *	description from degrees to a vector.  Degrees seemed simpler
 *	than they were.  A vector would also allow balls to move at different 
 *	speeds.
 *
 * NOTE: Before using this code for a game, check out the code for SubHunt,
 *     which demonstrates moving many objects at the same time.
 *
 *
 ************************************************************************************************
 *
 *
 * Changes made to support drawing low density bitmaps to a 1.5x QVGA display:
 *
 *
 *
 * HardBall has always allocated three offscreen windows:  a background window, a ball window,  
 * and an array of offscreen windows that is used for the application bitmaps.  For each frame, 
 *
 * 1. copy an area from the screen, 3 times the size of the ball, centered around the 
 *    current ball position, to the ball window
 * 2. erase the ball in the ball window by copying over it from the background offscreen window
 * 3. draw the ball in it's new relative position on the ball window
 * 4. copy the ball window back to the screen
 * 
 * Like SubHunt, the calls to WinCreateOffscreenWindow was using the screenFormat argument.  
 * Changing the argument to nativeFormat helped eliminate some drawing problems, but the 
 * animation still did not draw properly.  
 *
 * When the application includes native density bitmaps, the tools generate the 1.5x members 
 * of the bitmap family based on floor(1.5 x (low density dimensions)).  For example, if the 
 * low density ball was 7 x 7, thne 1.5x ball would be 10 x 10.  The use of the floor function 
 * ensures that the screen footprints of the bitmap family’s 1.5x bitmaps are not larger than 
 * the screen footprint of the bitmap family’s corresponding 1x and 2x bitmaps.
 * 
 * In contrast, when WinCreateOffscreenWindow is called with standard coordinates, the Window 
 * Manager uses ceiling(1.5 x (low density dimensions)) to allocate the window, thereby ensuring 
 * that the offscreen window is not smaller than the data.  
 *
 * If all of the bitmaps had an even width and height, rounding errors would not occur.  
 * But since some bitmaps have odd dimensions, the 1.5x windows are larger than the 1.5x source 
 * bitmap, the excess is not being clipped by the application, and the excess is improperly drawn. 
 *
 * There are two techniques that can be used to prevent rounding errors.
 *
 * 1.  Use even coordinates.  The ball width and height were changed from 7 to 8, the paddle
 * height was changed from 5 to 6, and most of the drawing problems disappeared. 
 *
 * 2.  Use native coordinates.  The 1x brick bitmaps have an odd height.  As an alternative 
 * to changing the brick bitmaps, DrawObject uses native coordinates.  This ensures that only  
 * the bitmap data is drawn to the screen.
 *
 *****************************************************************************/

#include <PalmOS.h>
#include <DLServer.h>
#include <Window.h>
#include <PalmUtils.h>

#include "HardBallRsc.h"


/***********************************************************************
 *
 *	Entry Points
 *
 ***********************************************************************/
#define appFileCreator				'hbal'
#define appPrefID						0
#define appSavedGameID				0
#define appPrefVersion				2
#define appSavedGameVersion		2

#define version30						0x03000000

/***********************************************************************
 *
 *	Constants 
 *
 ***********************************************************************/

#define firstLevelPlayed			0
#define ballsPerGame					3

// List of key bindings
#define moveLeftKey			keyBitHard1		// polled every game period
#define moveLeftKeyAlt		keyBitHard2		// polled every game period
#define moveRightKey			keyBitHard4		// polled every game period
#define moveRightKeyAlt		keyBitHard3		// polled every game period

// Note that these two characters are currently virtual, and thus the
// code handling them checks for the command bit in the event record.
#define releaseBallChr		vchrPageUp
#define restartGameChar		vchrPageDown

// List of bitmaps
#define paddleBitmap					0
#define ballBitmap					1
#define solid1BrickBitmap			2
#define solid2BrickBitmap			3
#define solid3BrickBitmap			4
#define unbreakableBrickBitmap	5
#define ballBrickBitmap				6
#define sidePaddleBrickBitmap		7
#define bitmapTypeCount				8

#define firstPaddleBitmap	paddleBitmap
#define firstBallBitmap		ballBitmap
#define firstBrickBitmap	solid1BrickBitmap

#define normalPaddle			0
#define normalBall			0


// Board settings
#define boardTopLeftX		4
#define boardTopLeftY		20
#define boardWidth			(160-8)		// width of screen less width of border graphic
#define boardHeight			140

#define boardBmpXOffset		-4			// The border graphics starts outside the board.
#define boardBmpYOffset		-4


// Title bar displays

// Ball gauge position
#define ballGaugeX			53

#define ballGaugeSeparator	1	// prevent string "Score" from being clipped by balls in title bar area

#define ballGaugeY			4
#define ballsDisplayable	5

// Score gauge position
#define scoreX					130
#define scoreY					2
#define maxScoreDigits 		5
#define maxScoreDisplayed 	100000


// Level Names
#define levelNameFont			largeFont
#define levelNameLengthMax		16


// Brick settings
#define columnsOfBricks			9
#define rowsOfBricks				11
#define brickStartRow			1
#define brickEndRow				7
#define brickWidth				16
#define brickHeight				9
#define brickMortarThickness	1
#define brokenBricksMax			10	// 2 * ballsMax + fudge

// Ball settings
#define ballWidth				8	// The ball width and height are used to create offscreen windows.
#define ballHeight				8	// Use even coordinates to prevent rounding error.

#define halfBallWidth		((ballWidth + 1) / 2)
#define ballAmountNeededToBreakABrick	2
#define halfBallHeight		((ballHeight + 1) / 2)
#define ballsMax				4
#define ballTrappedInLoopThreshold		12
#define firstBonusBallAwardedAtScore	2000

// Paddle settings
#define paddleWidth		26
#define paddleHeight		6
#define paddlesMax		2
#define paddleHorizontalSpacing	paddleWidth		// space between side by side paddles
#define paddleMovement	4			// faster than a ball

// List of all the degrees
#define degrees0			0
#define degrees22			1
#define degrees45			2
#define degrees67			3
#define degrees90			4
#define degrees112		5
#define degrees135		6
#define degrees157		7
#define degrees180		8
#define degrees202		9
#define degrees225		10
#define degrees247		11
#define degrees270		12
#define degrees292		13
#define degrees315		14
#define degrees337		15
#define degrees360		16
#define degreesMax		16

// List of surfaces
#define surfaceNone			degreesMax
#define surfaceTop			degrees0
#define surfaceRight			degrees90
#define surfaceBottom		degrees180
#define surfaceLeft			degrees270
#define surfaceHorizontal	surfaceTop
#define surfaceVertical		surfaceRight


// Motion of the surface (paddle) collided into
#define noMotion			1
#define leftMotion		2
#define rightMotion		3


#if EMULATION_LEVEL != EMULATION_NONE
#define defaultPeriodLength	3				// the emulator is slow, run as fast as possible
#else
#define defaultPeriodLength	4
#endif
#define minPeriodLength	1

// Various time intervals
#define levelOverTimeInterval	(4 * 60)
#define gameOverTimeInterval	(2 * 60)			// time to pause after game over and before high scores
#define pauseLengthBeforeResumingSavedGame			(3 * sysTicksPerSecond)
#define pauseLengthBeforeResumingInterruptedGame	(3 * sysTicksPerSecond)
#define pauseLengthToDisplayLevelName					((2 * sysTicksPerSecond) / defaultPeriodLength)


// High Scores settings
#define highScoreFont				stdFont
#define firstHighScoreY				28
#define highScoreHeight				12
#define highScoreNameColumnX		17
#define highScoreScoreColumnX		119		// Right aligned
#define highScoreLevelColumnX		149		// Right aligned
#define nameLengthMax	15
#define highScoreMax		9

// Preferences UI settings
#define startLevelsSelectable			3	
#define defaultStartLevelItem			0


/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/

// List of possible sounds
typedef enum 
	{
	noSound, 
	brickBreak, 
	brickNoBreak, 
	paddleBounce, 
	paddleSpinBounce, 
	wallBounce, 
	playBall, 
	speedBall, 
	extraBall, 
	extraPaddle,
	bonusBall, 
	newHighScore,
	soundTypeCount
	} SoundType;

typedef struct
	{
	UInt8 priority;
	UInt8 periods;
	Int32 frequency;
	UInt16 duration;
	} SoundInfo;

typedef struct
	{
	UInt16 initDelay;
	UInt16 period;
	UInt16 doubleTapDelay;
	Boolean queueAhead;
	} KeyRateType;

enum gameProgress 
	{
	gameResuming, 			// don't draw or change the game state.  Do resume the save game.
	gameInitializing, 	// don't draw or change the game state
	presentingLevel,		// display level name for brief period.  Go to waitingForBall upon user input.
	waitingForBall, 		// advance and draw the game state (allows paddle to move)
	ballInMotion, 	 		// advance and draw the game state
	levelOver, 	 			// pause, start new level, and go to waitingForBall
	gameOver,				// don't draw or change the game state, pause before high score check
	checkHighScores		// check for high score, get name if high score.
	};


typedef enum 
	{
	empty, 
	brick1, brick2, brick3, 	// adds points to the score
	unbreakable, 					// This brick doesn't break
	ballBrick, 						// releases a ball
	sidePaddleBrick, 				// adds a side paddle
	brickTypeCount
	} BrickType;

typedef struct 
	{
	char					name[levelNameLengthMax];
	BrickType			brick[rowsOfBricks][columnsOfBricks];
	} LevelType;
	
typedef struct 
	{
	AbsRectType			sides;
	Boolean				usable;
	Boolean				changed;
	UInt8					type;
	UInt8					heading;
	UInt8					bouncesWithoutBreakingABrick;	// used to detect unescapeable patterns.
	} ObjectType;

typedef struct 
	{
	Int32						score;
	ObjectType				paddle[paddlesMax];
	ObjectType				ball[ballsMax];
	} WorldState;

// Removed bricks are bricks broken during the game period
typedef struct 
	{
	Int16						row;
	Int16						column;
	} RemovedBrick;

typedef struct 
	{
	enum gameProgress		status;
	UInt8						periodLength;		// duration of period in ticks
	UInt32					nextPeriodTime;	// time when next period occurs
	UInt32					periodsToWait;		// time until something should happen
	Boolean					paused;				// indicates that time should not pass
	UInt32					pausedTime;			// Used to 
	BrickType				brick[rowsOfBricks][columnsOfBricks];
	UInt8						bricksRemaining;	// bricks remaining this level 
														// unbreakable bricks are ignored
	UInt8						level;				// controls the brick layout
	WorldState				last;					// world last drawn
	WorldState				next;					// world to be drawn
	RemovedBrick			brokenBricks[brokenBricksMax];	// bricks to erase
	Int16						brokenBricksCount;
	UInt8						ballsRemaining;	// balls remaining this game
	Boolean					movePaddleLeft;	// paddle moved and value cleared during GameStateElapse
	Boolean					movePaddleRight;	// paddle moved and value cleared during GameStateElapse
	SoundType				soundToMake;		// one sound can be made per game period
	Int8						soundPeriodsRemaining;	// times to repeat the sound
	Int32						scoreToAwardBonusBall;	// reaching this score awards an extra ball
	Boolean					lowestHighScorePassed;	// User beat the lowest high score
	Boolean					highestHighScorePassed;	// User beat the highest high score
	Boolean					gameSpedUp;			// reduces period time.  True if ball touches top wall
	Boolean					cheatMode;			// if true don't accept high score
	UInt32					startTime;			// Time since starting HardBall
	} GameStatusType;


typedef struct
	{
	char						name[nameLengthMax + 1];
	Int32						score;
	Int16						level;
	} SavedScore;

typedef struct
	{
	SavedScore				highScore[highScoreMax];
	UInt8						lastHighScore;
	UInt8						startLevel;			// the level to start at
	UInt32					accumulatedTime;	// Total time spent by player playing HardBall
	} HardBallPreferenceType;



/***********************************************************************
 *
 *	Global variables
 *
 ***********************************************************************/

#include "HardBallLevels.h"		// common settings are separated for ease of changing

static GameStatusType		GameStatus;
static MemHandle				ObjectBitmapHandles[bitmapTypeCount];
static BitmapPtr				ObjectBitmapPtr[bitmapTypeCount];
static WinHandle				ObjectWindowHandles[bitmapTypeCount];

// keep background bitmap in memory 
static WinHandle				BackgroundWindowHandle;		
static WinHandle				BallEraseWindow;

static enum gameProgress	SavedGameStatus;


static Int16						MovementX[degreesMax] = {
	2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1, 0, 1, 2, 2
	};
static Int16						MovementY[degreesMax] = {
	0, -1, -2, -2, -2, -2, -2, -1, 0, 1, 2, 2, 2, 2, 2, 1
	};

#define startHeadingsCount 4
static UInt8 BallStartHeadings[startHeadingsCount] = {
	degrees45, degrees67, degrees112, degrees135
	};

static UInt8 BallReflections[2][degreesMax] = 
	{
		// List the horizontal reflections first
		{
		degrees180, degrees337, degrees315, degrees292,
		degrees270, degrees247, degrees225, degrees202,
		degrees0, degrees157, degrees135, degrees112,
		degrees90, degrees67, degrees45, degrees22
		},
		// List the vertical reflections second
		{
		degrees180, degrees157, degrees135, degrees112,
		degrees270, degrees67, degrees45, degrees22,
		degrees0, degrees337, degrees315, degrees292,
		degrees90, degrees247, degrees225, degrees202
		}
	};
		
static UInt16 SoundAmp;		// default sound amplitude

static SoundInfo  Sound[soundTypeCount] = 
	{
		{0,	0,		0, 	0},			// no sound
		{30,	1,		200,	30},			// break brick
		{20,	1,		160,	50},			// no break brick
		{40,	1,		320,	30},			// paddle bounce
		{50,	1,		480,	50},			// paddle spin
		{10,	1,		180,	40},			// wall bounce
		{60,	1,		550,	60},			// play a ball
		{80,	4,		760,	50},			// speed up ball
		{60,	3,		550,	50},			// add a ball
		{70,	4,		860,	50},			// add a paddle
		{90,	6,		3740,	20},			// extra ball awarded
		{90,	8,		2500,	20},			// high score passed
	};
		

// The original values for key rates.		
KeyRateType KeyRate;

// Mappings for the start level UI
UInt8 StartLevelMappings[startLevelsSelectable] =
	{
	0, 5, 10
	};

// Used by the Preference Dialog
UInt8 NewStartLevel;
		
// The following global variable are saved to a state file.

// Scores
HardBallPreferenceType		Prefs;


/***********************************************************************
 *
 *	Macros
 *
 ***********************************************************************/

#define noItemSelection			-1


#define BrickX(c)					((c) * (brickWidth + brickMortarThickness))
#define BrickY(r)					((r) * (brickHeight + brickMortarThickness))
#define BrickAtX(c) 				((c) / (brickWidth + brickMortarThickness))
#define BrickAtY(r) 				((r) / (brickHeight + brickMortarThickness))
#define BrickExists(c, r)  	((r < rowsOfBricks) && (c < columnsOfBricks) && \
										(GameStatus.brick[r][c] != empty))

#define ScoreForBrick(r, c) 	(BrickScores[GameStatus.brick[r][c]])

#define headingVertically(h)	((h >= degrees45 && h <= degrees135) || \
										(h >= degrees225 && h <= degrees315))

#define HeadingDown(h)			(degrees180 < (h)  && (h) < degrees360)
#define HeadingUp(h)				(degrees0 < (h)  && (h) < degrees180)
#define HeadingLeft(h)			(degrees90 < (h)  && (h) < degrees270)
#define HeadingRight(h)			(degrees270 < (h)  || (h) < degrees90)
#define GetPaddleBitmap(t)		((t) + firstPaddleBitmap)
#define GetBallBitmap(t)		((t) + firstBallBitmap)
#define GetBrickBitmap(t)		((t) - 1 + firstBrickBitmap)

#define randN(N)	((((Int32) SysRandom (TimGetTicks())) * N) / ((Int32) sysRandomMax + 1))


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/
static void GameStart ();
static void GameDrawBallGauge (void);
static void HighScoresAddScore ( const Char * name, Int32 score, Int16 level, 
	Boolean dontAddIfExists);
static void HighScoresCheckScore (void);



/***********************************************************************
 *
 * FUNCTION:     TimeUntillNextPeriod
 *
 * DESCRIPTION:  Return the time until the next world advance.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     system ticks until the next world advance.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/95	Initial Revision
 *
 ***********************************************************************/
static Int32 TimeUntillNextPeriod (void)
{
	Int32 timeRemaining;
	
	
	if (GameStatus.status == gameInitializing || 
		GameStatus.status == gameResuming || 
		GameStatus.status == checkHighScores ||
		GameStatus.paused)
		return evtWaitForever;
		
		
	timeRemaining = GameStatus.nextPeriodTime - TimGetTicks();
	if (timeRemaining < 0)
		timeRemaining = 0;
		
	return timeRemaining;
}


/***********************************************************************
 *
 * FUNCTION:     StartApplication
 *
 * DESCRIPTION:  This routine sets up the application.  It gets the 
 * system volume preferences, loads in the graphics used, gets the high
 * scores or enters default ones, resumes any saved game or starts a new
 * one, plus other startup details.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     true if there is an error starting the application.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/6/95	Initial Revision
 *			jmp	12/16/99	When resuming from the initialization state,
 *								make sure we stay in the initialization state.
 *
 ***********************************************************************/
static UInt16 StartApplication (void)
{
	int i;
	WinHandle oldDrawWinH;
	UInt16 error;
	UInt16 prefsSize;
	MemHandle	TempBitmapHandle;
	BitmapPtr	TempBitmapPtr;
	Coord bitmapWidth, bitmapHeight;
	
	// Get SoundAmp for the sound code.  If game sounds are desired use
	// the default sound else set the volume to zero to turn it off.
	SoundAmp = PrefGetPreference(prefGameSoundVolume);


	// Get the key repeat rate for when we want to restore it after the game.
	KeyRates(false, &KeyRate.initDelay, &KeyRate.period, &KeyRate.doubleTapDelay, 
		&KeyRate.queueAhead);
	
	
	// Keep the Object graphics locked because they are frequently used
	oldDrawWinH = WinGetDrawWindow();
	
	for (i = 0; i < bitmapTypeCount; i++)
		{
		ObjectBitmapHandles[i] = DmGetResource( bitmapRsc, firstObjectBmp + i);
		ObjectBitmapPtr[i] = MemHandleLock(ObjectBitmapHandles[i]);
		
		// on OS versions <= 4.1, it is actually faster to store the graphics
		// as window images.  It is faster because WinDrawBitmap constructs a
		// window from the bitmap on the fly before drawing.  
		// We can do this as long as there is enough memory free in the dynamic
		// ram.  We don't do this to large images.
		
		if (i == 999)			// don't skip any bitmaps we use
			{
			ObjectWindowHandles[i] = 0;
			}
		else
			{
			BmpGetDimensions(ObjectBitmapPtr[i], &bitmapWidth, &bitmapHeight, NULL);			
			ObjectWindowHandles[i] = WinCreateOffscreenWindow( bitmapWidth, bitmapHeight,
															   	nativeFormat, &error);
			ErrFatalDisplayIf(error, "Error loading images");
			WinSetDrawWindow(ObjectWindowHandles[i]);
			WinDrawBitmap(ObjectBitmapPtr[i], 0, 0);
			}
		}

	TempBitmapHandle = DmGetResource( bitmapRsc, BoardBmp );
	TempBitmapPtr = MemHandleLock( TempBitmapHandle );
	BmpGetDimensions(TempBitmapPtr, &bitmapWidth, &bitmapHeight, NULL);
	
	{
	RectangleType bounds;

	BackgroundWindowHandle = WinCreateOffscreenWindow( bitmapWidth, bitmapHeight,
														nativeFormat, &error );
	ErrFatalDisplayIf(error, "Error loading background image");
	WinSetDrawWindow(BackgroundWindowHandle);
		
	// Initialize window to black.  
	WinGetBounds(BackgroundWindowHandle, &bounds);
	WinInvertRectangle(&bounds, 0);
	}
	
	WinDrawBitmap(TempBitmapPtr, 0, 0);
	
	MemPtrUnlock(TempBitmapPtr);
	DmReleaseResource(TempBitmapHandle);
		
	 
	BallEraseWindow = WinCreateOffscreenWindow( ballWidth*3, ballHeight*3,
												nativeFormat, &error );
	ErrFatalDisplayIf(BallEraseWindow==0,"oops!");
	ErrFatalDisplayIf(error, "Error creating ball erase window" );
	
	WinSetDrawWindow(oldDrawWinH);
	
	
	// Restore the app's preferences.
	prefsSize = sizeof (HardBallPreferenceType);
	if (PrefGetAppPreferences (appFileCreator, appPrefID, &Prefs, &prefsSize, 
		true) == noPreferenceFound)
		{
		// There aren't any preferences
		
		// Clear the high scores.
		for (i = 0; i < highScoreMax; i++)
			{
			Prefs.highScore[i].name[0] = '\0';
			Prefs.highScore[i].score = 0;
			Prefs.highScore[i].level = 1;
			}
		
		// Add Best Score
		HighScoresAddScore ("Rocket Boy", 7236, 11, true);
		HighScoresAddScore ("Briester", 2415, 5, true);
		HighScoresAddScore ("the Jode", 2900, 5, true);
		HighScoresAddScore ("Mr. P", 9825, 17, true);

		// No last high score
		Prefs.lastHighScore = highScoreMax;
		
		// Begin at the first level.
		Prefs.startLevel = firstLevelPlayed;
		
		// No time has been recorded.
		Prefs.accumulatedTime = 0;
		}
	
	
	// Restore a saved game.  Games are kept in the unsaved preference database.
	prefsSize = sizeof (GameStatus);
	if (PrefGetAppPreferences (appFileCreator, appSavedGameID, &GameStatus, 
		&prefsSize, false) == noPreferenceFound)
		{
		// Initialize this now so that the GetNextEvent wait time is set properly.	
		GameStatus.status = gameInitializing;		// don't draw yet!
		
		
		// Now display the about box and instructions.  This appears automatically
		// the first time the program is run.
#ifndef DETERMINISTIC_PLAY
//		InfoDisplay();
		FrmHelp (InstructionsStr);
#endif
		}
	else
		{
		if (GameStatus.status != checkHighScores)
			{
			SavedGameStatus = GameStatus.status;
			
			// Don't draw yet unless we're resuming in the initialization state.
			if (GameStatus.status != gameInitializing)
				GameStatus.status = gameResuming;
			}
		}


	// Record the start time of this game session.
	GameStatus.startTime = TimGetTicks();

	// Initialize the random number generator
	SysRandom (GameStatus.startTime);
	
	return 0;		// no error
}


/***********************************************************************
 *
 * FUNCTION:    StopApplication
 *
 * DESCRIPTION: Release the graphics and save the high scores, time played,
 * and any game in progress.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/6/95	Initial Revision
 *			jmp	10/22/99	Call FrmCloseAllForms() to eliminate "memory leak" error that
 *								comes up on debug ROMs.
 *
 ***********************************************************************/
static void StopApplication (void)
{
	int i;

	// Unlock and release the locked bitmaps.
	for (i = 0; i < bitmapTypeCount; i++)
		{
		MemPtrUnlock(ObjectBitmapPtr[i]);
		DmReleaseResource(ObjectBitmapHandles[i]);

		if (ObjectWindowHandles[i]) 
			WinDeleteWindow(ObjectWindowHandles[i], false);
		}

	// delete background image
	
	if (BackgroundWindowHandle)
		WinDeleteWindow( BackgroundWindowHandle, false );

	if (BallEraseWindow)
		WinDeleteWindow( BallEraseWindow, false );
		
	// Update the time accounting.
	Prefs.accumulatedTime += (TimGetTicks() - GameStatus.startTime);
	
	// If we are saving a game resuming (it hasn't started playing yet)
	// then preserve the game status.
	if (GameStatus.status == gameResuming)
		{
		GameStatus.status = SavedGameStatus;
		}

	// Perform error checking on the saved data.
	ErrNonFatalDisplayIf(Prefs.startLevel > StartLevelMappings[startLevelsSelectable - 1], "Bad start level");
	
	// Save state/prefs.
	PrefSetAppPreferences (appFileCreator, appPrefID, appPrefVersion, 
		&Prefs, sizeof (Prefs), true);

	PrefSetAppPreferences (appFileCreator, appSavedGameID, appSavedGameVersion, 
		&GameStatus, sizeof (GameStatus), false);
		
	// Close all the open forms.
	FrmCloseAllForms ();
}


/***********************************************************************
 *
 * FUNCTION:    RomVersionCompatible
 *
 * DESCRIPTION: This routine checks that a ROM version meets your
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

	// See if we have at least the minimum required version of the ROM or later.
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
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  objectID - id of the object to get
 *
 * RETURNED:    pointer to the object
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/6/95	Initial Revision
 *
 ***********************************************************************/
static void * GetObjectPtr (UInt16 objectID)
{
	FormPtr frm;
	void * obj;
	
	frm = FrmGetActiveForm ();
	obj = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, objectID));

	return obj;
}


/***********************************************************************
 *
 * FUNCTION:    MapToPosition
 *
 * DESCRIPTION:	Map a value to it's position in an array.  If the passed
 *						value is not found in the mappings array, a default
 *						mappings item will be returned.
 *
 * PARAMETERS:  value	- value to look for
 *
 * RETURNED:    position value found in
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/21/96	Initial Revision
 *
 ***********************************************************************/
static UInt16 MapToPosition (UInt8 *mappingArray, UInt8 value,
									UInt16 mappings, UInt16 defaultItem)
{
	UInt16 i;
	
	i = 0;
	while (mappingArray[i] != value && i < mappings)
		i++;
	if (i >= mappings)
		return defaultItem;

	return i;
}


/***********************************************************************
 *
 * FUNCTION:     GameMaskKeys
 *
 * DESCRIPTION:  Mask the keys to reduce keyDownEvents from being sent.
 * This saves time.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/25/96	Initial Revision
 *
 ***********************************************************************/
static void GameMaskKeys ()
{
	UInt16 initDelay;
	UInt16 period;
	Boolean queueAhead;
	
	
	// Set the keys we poll to not generate events.  This saves cpu cycles.
	KeySetMask(	~(moveLeftKey | moveLeftKeyAlt | moveRightKey | moveRightKeyAlt) );
	
	// Avoid the code below because KeyRates is broken.
	return;
	
	// Also set the key repeat rate low to avoid constantly checking them.
	initDelay = slowestKeyDelayRate;
	period = slowestKeyPeriodRate;
	queueAhead = false;
	KeyRates(true, &initDelay, &period, &period, &queueAhead);
}


/***********************************************************************
 *
 * FUNCTION:     GameUnmaskKeys
 *
 * DESCRIPTION:  Unmask the keys.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/25/96	Initial Revision
 *
 ***********************************************************************/
static void GameUnmaskKeys ()
{
	// Set the keys we poll to not generate events.  This saves cpu cycles.
	KeySetMask(	keyBitsAll );
	
	// Avoid the code below because KeyRates is broken.
	return;
	
	// Also set the key repeat rate low to avoid constantly checking them.
	KeyRates(true, &KeyRate.initDelay, &KeyRate.period, &KeyRate.doubleTapDelay, 
		&KeyRate.queueAhead);
}


/***********************************************************************
 *
 * FUNCTION:		DrawBitmap
 *
 * DESCRIPTION:	Get and draw a bitmap at a specified location
 *
 * PARAMETERS:	resID		-- bitmap resource id
 *					x, y		-- bitmap origin relative to current window
 *
 * RETURNED:	nothing.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			vmk	10/9/95	Initial Revision
 *
 ***********************************************************************/
static void DrawBitmap(Int16 resID, Int16 x, Int16 y)
{
	MemHandle		resH;
	BitmapPtr	resP;


	resH = DmGetResource( bitmapRsc, resID );
	ErrFatalDisplayIf( !resH, "Missing bitmap" );
	resP = MemHandleLock(resH);
	WinDrawBitmap (resP, x, y);
	MemPtrUnlock(resP);
	DmReleaseResource( resH );
}


/***********************************************************************
 *
 * FUNCTION:		DrawObject
 *
 * DESCRIPTION:	Draw an object at a specified location and mode
 *
 * PARAMETERS:	bitmapNumber -- bitmap number
 *					x, y		-- bitmap origin relative to current window
 *					mode		-- transfer mode (scrANDNOT for masks)
 *
 * RETURNED:	nothing.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/29/96	Initial Revision
 *
 ***********************************************************************/
static void DrawObject(Int16 bitmapNumber, Int16 x, Int16 y, WinDrawOperation mode)
{
	RectangleType srcRect;
	UInt16 oldCoordSys;

	ErrFatalDisplayIf (ObjectWindowHandles[bitmapNumber] == 0, "Unhandled object image");
	
	// Copy the entire source window.
	WinGetBounds(ObjectWindowHandles[bitmapNumber], &srcRect);

	// Use native coordinates because on a 1.5x device, a rounding error shows up when
	// drawing the bricks due to the odd height of the 1x bitmaps.
	oldCoordSys = WinSetCoordinateSystem(kCoordinatesNative);
	
	// Use the floor function when scaling to avoid drawing more data than what exists
	// in the source bitmap.
	WinScalePoint(&srcRect.topLeft, true);
	WinScalePoint(&srcRect.extent, true);
	
	// Copy the source window (contains the image to draw) to the draw window.
	WinCopyRectangle(ObjectWindowHandles[bitmapNumber], 0, &srcRect, 
					  WinScaleCoord(x, false), WinScaleCoord(y, false), mode);					  

	WinSetCoordinateSystem(oldCoordSys);
}


/***********************************************************************
 *
 * FUNCTION:     GameRequestSound
 *
 * DESCRIPTION:  Setup to play a game sound. Sound will be played unless
 *				a higher priority sound is already requested.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *
 ***********************************************************************/
static void GameRequestSound (SoundType sound)
{
	if (Sound[sound].priority >= Sound[GameStatus.soundToMake].priority)
		{
		GameStatus.soundToMake = sound;
		GameStatus.soundPeriodsRemaining = Sound[sound].periods;
		}
}


/***********************************************************************
 *
 * FUNCTION:     IncreaseScore
 *
 * DESCRIPTION:  Increase the score by some amount
 *
 * PARAMETERS:   score - the amount to add to the score.
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/20/96	Initial Revision
 *
 ***********************************************************************/
static void IncreaseScore (Int32 score)
{
	GameStatus.next.score += score;
	
	// Beep if the user is setting a new high score. Don't beep if not
	// all the high scores were already set (it's annoying).
	if (!GameStatus.lowestHighScorePassed &&
		GameStatus.next.score > Prefs.highScore[highScoreMax - 1].score &&
		Prefs.highScore[highScoreMax - 1].score > 0)
		{
		GameStatus.lowestHighScorePassed = true;
		if (GameStatus.next.score > 0)
			GameRequestSound (newHighScore);
		}


	// Beep if the user is setting the highest score.
	if (!GameStatus.highestHighScorePassed &&
		GameStatus.next.score > Prefs.highScore[0].score &&
		Prefs.highScore[0].score > 0)
		{
		GameStatus.highestHighScorePassed = true;
		if (GameStatus.next.score > 0)
			GameRequestSound (newHighScore);
		}


	// Beep if the user is awarded an extra ball.
	if (GameStatus.next.score >= GameStatus.scoreToAwardBonusBall)
		{
		GameStatus.scoreToAwardBonusBall *= 2;
		
		// Add a ball to those remaining and update the ball gauge.
		GameStatus.ballsRemaining++;
		GameDrawBallGauge();

		GameRequestSound (bonusBall);
		}

}


/***********************************************************************
 *
 * FUNCTION:     PaddleAddSidePaddle
 *
 * DESCRIPTION:  Add a paddle to play
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/1/96	Initial Revision
 *
 ***********************************************************************/

static void PaddleAddSidePaddle ()
{
	Boolean paddlePaddleOnRightSide;
	
	
	GameStatus.next.paddle[1].usable = true;
	GameStatus.next.paddle[1].changed = true;
	GameStatus.next.paddle[1].type = normalPaddle;
	
	// Place at the same height as the first paddle
	GameStatus.next.paddle[1].sides.top = GameStatus.next.paddle[0].sides.top;
	GameStatus.next.paddle[1].sides.bottom = GameStatus.next.paddle[0].sides.bottom;
	

	paddlePaddleOnRightSide = GameStatus.next.paddle[0].sides.left + 
		(GameStatus.next.paddle[0].sides.right - GameStatus.next.paddle[0].sides.left)
		> boardWidth / 2;
	if (paddlePaddleOnRightSide)
		{
		// Add the next one of the left side
		GameStatus.next.paddle[1].sides.left = GameStatus.next.paddle[0].sides.left -
			paddleHorizontalSpacing - paddleWidth;
		}
	else
		{
		// Add the next one of the right side
		GameStatus.next.paddle[1].sides.left = GameStatus.next.paddle[0].sides.right +
			paddleHorizontalSpacing;
		}
	
	GameStatus.next.paddle[1].sides.right = GameStatus.next.paddle[1].sides.left + paddleWidth;
}


/***********************************************************************
 *
 * FUNCTION:     ResetPaddles
 *
 * DESCRIPTION:  Resets the paddle to only one showing
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/1/96	Initial Revision
 *
 ***********************************************************************/

static void ResetPaddles ()
{
	int i;
	
	
	// Reset the paddles
	for (i = paddlesMax - 1; i >= 0; i--)
		{
		// Allow only one paddle
		if (i > 0)
			{
			// If was usable mark it changed so it erases
			if (GameStatus.next.paddle[i].usable)
				GameStatus.next.paddle[i].changed = true;
			GameStatus.next.paddle[i].usable = false;
			
			}
		}
}


/***********************************************************************
 *
 * FUNCTION:     BallAdd
 *
 * DESCRIPTION:  Add a ball to play
 *
 * PARAMETERS:   type - type of ball (i.e. normalBall)
 *					  left - left bounds of the ball
 *					  top - top bounds of the ball
 *					  heading - heading of the ball (i.e. degrees45)
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/23/96	Initial Revision
 *
 ***********************************************************************/

static void BallAdd (UInt8 type, Int16 left, Int16 top, UInt8 heading)
{
	int i;
	
	
	// Find an unused ball
	i = 0;
	while (i < ballsMax && GameStatus.next.ball[i].usable)
		i++;
	
	
	if (i < ballsMax)
		{
		// Set the ball up to draw
		GameStatus.next.ball[i].usable = true;
		GameStatus.next.ball[i].changed = true;
		GameStatus.next.ball[i].type = type;
		GameStatus.next.ball[i].heading = heading;
		GameStatus.next.ball[i].bouncesWithoutBreakingABrick = 0;
		
		// place the ball in the bottom center
		GameStatus.next.ball[i].sides.left = left;
		GameStatus.next.ball[i].sides.top = top;
		GameStatus.next.ball[i].sides.right = left + ballWidth;
		GameStatus.next.ball[i].sides.bottom = top + ballHeight;
		}
	else
		{
		// The user should receive a ball but there isn't a spot for it.
		// Add the ball to the ballsRemaining.
		GameStatus.ballsRemaining++;
		GameDrawBallGauge();
		}
}


/***********************************************************************
 *
 * FUNCTION:     BallRemove
 *
 * DESCRIPTION:  Remove a ball from play.  Ends the game if no balls 
 * remain.
 *
 * PARAMETERS:   ballNumber - which ball to remove
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *
 ***********************************************************************/

static void BallRemove (Int16 ballNumber)
{
	int i;
	
	
	if (GameStatus.next.ball[ballNumber].usable)
		{
		GameStatus.next.ball[ballNumber].usable = false;
		GameStatus.next.ball[ballNumber].changed = true;
		
		
		
		// Find a used ball
		i = 0;
		while (i < ballsMax && !GameStatus.next.ball[i].usable)
			i++;
		
		// If no ball is found either wait for a ball if other balls
		// remain or declare the game over.
		if (i >= ballsMax)
			{
			if (GameStatus.ballsRemaining > 0)
				{
				GameStatus.status = waitingForBall;
				
				// Now loose any special bonuses
				ResetPaddles();

				// Cancel any speed up
				if (GameStatus.gameSpedUp)
					{
					GameStatus.periodLength++;
					GameStatus.gameSpedUp = false;
					}
				}
			else
				{
				GameStatus.status = gameOver;
				GameStatus.nextPeriodTime += gameOverTimeInterval;
				}
			}

		}

}


/***********************************************************************
 *
 * FUNCTION:     BallMove
 *
 * DESCRIPTION:  Move a ball from it's last position to it's next position.
 *
 * PARAMETERS:   ballNumber - the ball to move
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/
static void BallMove (Int16 ballNumber)
{
	ErrFatalDisplayIf(GameStatus.next.ball[ballNumber].heading >= degreesMax, 
		"Bad heading");
	GameStatus.next.ball[ballNumber].sides.left = GameStatus.last.ball[ballNumber].sides.left +
		MovementX[GameStatus.next.ball[ballNumber].heading];
	GameStatus.next.ball[ballNumber].sides.top = GameStatus.last.ball[ballNumber].sides.top +
		MovementY[GameStatus.next.ball[ballNumber].heading];
	GameStatus.next.ball[ballNumber].sides.right = GameStatus.last.ball[ballNumber].sides.right +
		MovementX[GameStatus.next.ball[ballNumber].heading];
	GameStatus.next.ball[ballNumber].sides.bottom = GameStatus.last.ball[ballNumber].sides.bottom +
		MovementY[GameStatus.next.ball[ballNumber].heading];
}


/***********************************************************************
 *
 * FUNCTION:     BallReflect
 *
 * DESCRIPTION:  Reflect a ball off a surface.
 *
 * PARAMETERS:   heading - heading of the moving object
 *					  surface - the direction of the hit surface
 *					  surfaceMotion - surfaces like paddles may have motion
 *							which changes the angle a little more
 *
 * RETURNED:     the new heading
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *			roger 1/30/96	Rewritten to use tables.
 *
 ***********************************************************************/
static UInt8 BallReflect (UInt8 heading, UInt8 surface, UInt8 surfaceMotion)
{
	UInt8 newHeading;
	
	
	// Lookup the new heading in the BallReflections table.  Moving
	// surfaces are accounted for later.
	if (surface == surfaceTop || surface == surfaceBottom)
		newHeading = BallReflections[surfaceHorizontal][heading];
	else
		newHeading = BallReflections[1][heading];


	// Affect the reflection angle based on the movement of the surface
	if (surfaceMotion == leftMotion)
		{
		if ((degrees45 <= newHeading && newHeading <= degrees67) ||
			(degrees135 <= newHeading && newHeading <= degrees157))
			{
			newHeading--;
			GameRequestSound (paddleSpinBounce);
			}
		else if ((degrees202 <= newHeading && newHeading <= degrees225) ||
			(degrees292 <= newHeading && newHeading <= degrees315))
			{
			newHeading++;
			GameRequestSound (paddleSpinBounce);
			}
		}
	else if (surfaceMotion == rightMotion)
		{
		if ((degrees22 <= newHeading && newHeading <= degrees45) ||
			(degrees112 <= newHeading && newHeading <= degrees135))
			{
			newHeading++;
			GameRequestSound (paddleSpinBounce);
			}
		else if ((degrees225 <= newHeading && newHeading <= degrees247) ||
			(degrees315 <= newHeading && newHeading <= degrees337))
			{
			newHeading--;
			GameRequestSound (paddleSpinBounce);
			}
		}
	
	
	return newHeading;
}


/***********************************************************************
 *
 * FUNCTION:     GameDrawBallGauge
 *
 * DESCRIPTION:  Draw the ball gauge.  Balls remaining are drawn.  Balls
 * no longer remaining are erased.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/25/96	Initial Revision
 *
 ***********************************************************************/

static void GameDrawBallGauge (void)
{
	int i;
	RectangleType bounds;


	// Draw some of the balls remaining	
	for (i = 0; i < ballsDisplayable; i++)
		{
		if (GameStatus.ballsRemaining > i)
			{
			WinDrawBitmap (ObjectBitmapPtr[firstBallBitmap], 
				ballGaugeX + i * (ballWidth + ballGaugeSeparator), ballGaugeY);
			}
		else
			{
			bounds.topLeft.x = ballGaugeX + i * (ballWidth + ballGaugeSeparator);
			bounds.topLeft.y = ballGaugeY;
			bounds.extent.x = ballWidth;
			bounds.extent.y = ballHeight;
			WinEraseRectangle(&bounds, 0);
			}
		}
}


/***********************************************************************
 *
 * FUNCTION:     GameDrawScoreGauge
 *
 * DESCRIPTION:  Draw the score gauge given a score to display.
 *
 * PARAMETERS:   score - the score to display
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/12/96	Initial Revision - code clean up
 *
 ***********************************************************************/
static void GameDrawScoreGauge (Int32 score)
{
	char scoreText[maxScoreDigits + 1];
	FontID currFont;


	// Draw the score
	if (score > 0)
		{
		score = score % maxScoreDisplayed;
		StrIToA(scoreText, score);
		}
	else
		{
		Char numSpace;
		ChrNumericSpace(&numSpace);
		// Write numeric spaces to remove old score
		MemSet(scoreText, maxScoreDigits, numSpace);			
		scoreText[0] = '0';
		scoreText[maxScoreDigits - 1] = '\0';
		}
	currFont = FntSetFont(boldFont);
	WinDrawChars (scoreText, StrLen(scoreText), scoreX, scoreY);
	FntSetFont(currFont);
}


/***********************************************************************
 *
 * FUNCTION:     GameStateDraw
 *
 * DESCRIPTION:  Redraw the world.  Everything in the last world is 
 * is erased and redrawn
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/23/96	Initial Revision
 *
 ***********************************************************************/

static void GameStateDraw (void)
{
	int i;
	int x;
	int y;
	
	// Draw a blank board
	DrawBitmap(BoardBmp, 
		boardTopLeftX + boardBmpXOffset, 
		boardTopLeftY + boardBmpYOffset);


	// Draw the bricks that exist
	for (y = 0; y < rowsOfBricks; y++)
		{
		for (x = 0; x < columnsOfBricks; x++)
			{
			if (GameStatus.brick[y][x] != empty)
				{
				DrawObject (GetBrickBitmap(GameStatus.brick[y][x]), 
					boardTopLeftX + BrickX(x), boardTopLeftY + BrickY(y),
					winPaint);
				}
			}
		}


	// Draw the paddles
	for (i = paddlesMax - 1; i >= 0; i--)
		{
		// Draw the paddle
		if (GameStatus.last.paddle[i].usable)
			{
			DrawObject (GetPaddleBitmap(GameStatus.last.paddle[i].type), 
				boardTopLeftX + GameStatus.last.paddle[i].sides.left, 
				boardTopLeftY + GameStatus.last.paddle[i].sides.top,
				winPaint);
			}
		}


	// Draw the balls
	for (i = ballsMax - 1; i >= 0; i--)
		{
		// Draw the ball
		if (GameStatus.last.ball[i].usable)
			{
			DrawObject (GetBallBitmap(GameStatus.last.ball[i].type), 
				boardTopLeftX + GameStatus.last.ball[i].sides.left, 
				boardTopLeftY + GameStatus.last.ball[i].sides.top,
				winPaint);
			}
		}
	
	
	GameDrawScoreGauge (GameStatus.last.score);
	GameDrawBallGauge();
}



/***********************************************************************
 *
 * FUNCTION:     GameStateDrawChanges
 *
 * DESCRIPTION:  Show the world.  Visually moves the balls and the paddle.  
 * Removes bricks.  Redraws the score.
 *
 * No changes are made to the world here.  Scores do not change, nothing 
 * moves internally.  All visual moves are the display now reflecting the 
 * changes made to the world during the last period.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/22/96	Initial Revision
 *			jmp	10/11/99	"Old" balls used to be erased by using winMask (aka scrANDNOT) transfer
 *								mode.  But PalmOS 3.5 doesn't support winMask unless the fore/back colors
 *								are black/white.  So, replaced the use of drawing with winMask with
 *								WinEraseRectangle().  Also, eliminated winOverlay and 
 *
 ***********************************************************************/

static void GameStateDrawChanges (void)
{
	RectangleType	bounds,
					screenBounds,
					eraseBounds;
	WinHandle		oldDrawWin;
	Int16 			i,x,y,xoff,yoff;
	
	// Visually remove broken bricks
	while (GameStatus.brokenBricksCount > 0)
		{
		GameStatus.brokenBricksCount--;
		
		xoff = BrickX(GameStatus.brokenBricks[GameStatus.brokenBricksCount].column) - boardBmpXOffset;
		yoff = BrickY(GameStatus.brokenBricks[GameStatus.brokenBricksCount].row) - boardBmpYOffset;
		bounds.topLeft.x = xoff;
		bounds.topLeft.y = yoff;
		bounds.extent.x  = brickWidth;
		bounds.extent.y  = brickHeight;
		
		WinCopyRectangle( BackgroundWindowHandle, 0, &bounds, 
							xoff + boardTopLeftX + boardBmpXOffset,  
							yoff + boardTopLeftY + boardBmpYOffset, winPaint );	
		}

		
	// Visually move the paddles
	for (i = paddlesMax - 1; i >= 0; i--)
		{
		// Erase the old paddle
		if (GameStatus.last.paddle[i].usable &&
			GameStatus.next.paddle[i].changed)
			{
			// if this paddle is still good the next go around, only do the partial
			// erase 
			if (GameStatus.next.paddle[i].usable)
				{
				bounds.extent.x  = GameStatus.next.paddle[i].sides.left - GameStatus.last.paddle[i].sides.left;
				bounds.extent.y  = GameStatus.last.paddle[i].sides.bottom - GameStatus.last.paddle[i].sides.top;
			
				if (bounds.extent.x<0) bounds.extent.x = -bounds.extent.x;
			
				if (GameStatus.next.paddle[i].sides.left-GameStatus.last.paddle[i].sides.left>0)
					{
					bounds.topLeft.x = GameStatus.last.paddle[i].sides.left-boardBmpXOffset;
					bounds.topLeft.y = GameStatus.last.paddle[i].sides.top-boardBmpYOffset;
					}
				else
					{
					bounds.topLeft.x = GameStatus.next.paddle[i].sides.right-boardBmpXOffset;
					bounds.topLeft.y = GameStatus.next.paddle[i].sides.top-boardBmpYOffset;
					}
				}
			else // otherwise this paddle needs to go away, erase the whole paddle
				{
				bounds.topLeft.x = GameStatus.last.paddle[i].sides.left - boardBmpXOffset;
				bounds.topLeft.y = GameStatus.last.paddle[i].sides.top - boardBmpYOffset;
				bounds.extent.x  = GameStatus.last.paddle[i].sides.right - GameStatus.last.paddle[i].sides.left;
				bounds.extent.y  = GameStatus.last.paddle[i].sides.bottom - GameStatus.last.paddle[i].sides.top;
				}
			
			xoff = bounds.topLeft.x;
			yoff = bounds.topLeft.y;

			WinCopyRectangle( BackgroundWindowHandle, 0, &bounds, 
								xoff + boardTopLeftX + boardBmpXOffset, 
								yoff + boardTopLeftY + boardBmpYOffset, winPaint );	
									
			//WinEraseRectangle(&bounds, 0);
			}

		// Draw the new paddle
		if (GameStatus.next.paddle[i].usable &&
			GameStatus.next.paddle[i].changed)
			{
			DrawObject (GetPaddleBitmap(GameStatus.next.paddle[i].type), 
				boardTopLeftX + GameStatus.next.paddle[i].sides.left, 
				boardTopLeftY + GameStatus.next.paddle[i].sides.top,
				winPaint);
			}
		}


	// Visually move the balls
	for (i = ballsMax - 1; i >= 0; i--)
		{
		bounds.topLeft.x = -1;
		
		// Erase the old ball
		if (GameStatus.last.ball[i].usable &&
			GameStatus.next.ball[i].changed)
			{
						
			// new method to erase ball:
			// 1) copy an area from the screen, 3 times the size of the ball, centered around
			//    the current ball position, to an offscreen window
			// 2) erase the ball in the offscreen window, by copying over it from the background 
			//    screen
			// 3) draw the ball in it's new relative position on the offscreen window
			// 4) copy the offscreen window back to the screen
			//
			
			// get the bounding rectangle 3x bigger than the ball, centered on the ball is possible.
			// if we're close enough to the edge of the background bitmap that we can't center
			// the ball, shift the rectangle we're working in to fit within the background bitmap
			// and adjust the xoff/yoff values
			
			// xoff/yoff is the position of the current ball in our 'erase' window
			
			xoff = ballWidth;
			yoff = ballHeight;
			
			bounds.topLeft.x = GameStatus.last.ball[i].sides.left - xoff;
			bounds.topLeft.y = GameStatus.last.ball[i].sides.top - yoff;
			bounds.extent.x = ballWidth*3;
			bounds.extent.y = ballHeight*3;
			
			// if the erase window would be off the board, adjust it to be entirely on
			// the board, and adjust the xoff/yoff position accordingly

			if (bounds.topLeft.x<0)
			{
				xoff += bounds.topLeft.x;
				bounds.topLeft.x = 0;
			}
			
			if (bounds.topLeft.y<0)
			{
				yoff += bounds.topLeft.y;
				bounds.topLeft.y = 0;
			}
			

			// adjust for screen coordinates
						
			screenBounds = bounds;
			screenBounds.topLeft.x += boardTopLeftX;
			screenBounds.topLeft.y += boardTopLeftY;
			
			// copy corresponding image from the screen to the offscreen window
		
			WinCopyRectangle( 0, BallEraseWindow, &screenBounds, 0, 0, winPaint );
			
			// get the bounding rectangle for the old ball position, relative to the background bitmap
			
			eraseBounds.topLeft.x = GameStatus.last.ball[i].sides.left-boardBmpXOffset;
			eraseBounds.topLeft.y = GameStatus.last.ball[i].sides.top-boardBmpYOffset;
			eraseBounds.extent.x  = ballWidth;
			eraseBounds.extent.y  = ballHeight;
			
			// copy from the background bitmap over the ball in the offscreen window
			// which is a position (xoff,yoff) within the erase window
			
			WinCopyRectangle( BackgroundWindowHandle, BallEraseWindow, &eraseBounds, 
								xoff, yoff, winPaint );

			}

		// Draw the new ball
		if (GameStatus.next.ball[i].usable &&
			GameStatus.next.ball[i].changed)
			{
				oldDrawWin = WinSetDrawWindow( BallEraseWindow );
				WinDrawBitmap( ObjectBitmapPtr[ballBitmap], 
					GameStatus.next.ball[i].sides.left - GameStatus.last.ball[i].sides.left + xoff, 
					GameStatus.next.ball[i].sides.top - GameStatus.last.ball[i].sides.top + yoff );

				WinSetDrawWindow( oldDrawWin );
			}
			
		// now copy the offscreen window back to the screen
			
		if (bounds.topLeft.x!=-1)
			{
				// screenBounds.topleft correspond to the origin from which screen data was copied 
				// from the screen to BallEraseWindow.  Use the same coordinates to position where 
				// BallEraseWindow is copied back to the screen.   
				x = screenBounds.topLeft.x;		
				y = screenBounds.topLeft.y;		
				
				bounds.topLeft.x = 0;
				bounds.topLeft.y = 0;
				bounds.extent.x = ballWidth*3;
				bounds.extent.y = ballHeight*3;
				
				WinCopyRectangle( BallEraseWindow, 0, &bounds, x, y, winPaint );
			}
		}


	// Update the score
	if (GameStatus.last.score != GameStatus.next.score)
		{
		GameDrawScoreGauge(GameStatus.next.score);
		}
		
}


/***********************************************************************
 *
 * FUNCTION:     GameInitLevel
 *
 * DESCRIPTION:  Set the data to start a new level
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/22/96	Initial Revision
 *
 ***********************************************************************/

static void GameInitLevel (void)
{
	int i;
	int x;
	int y;
	FontID currFont;
	Char * nameP;
	Int16 nameLength;
	Int16 nameWidth;
	RectangleType bounds;
	
	
	// The game speeds up every time the levels wrap
	GameStatus.periodLength = max(defaultPeriodLength - GameStatus.level / levelCount, 
		minPeriodLength);
	GameStatus.status = presentingLevel;

	// Cancel any gameSpedUp
	if (GameStatus.gameSpedUp)
		{
		GameStatus.periodLength++;
		GameStatus.gameSpedUp = false;
		}
	
	// Set up the paddles.  All the paddles except the first are not used.  The
	// first is set to the bottom center of the board.

	// Reset the paddles
	for (i = paddlesMax - 1; i >= 0; i--)
		{
		GameStatus.next.paddle[i].usable = false;
		GameStatus.next.paddle[i].changed = false;
		}
	
	// Set the paddle up to draw
	GameStatus.next.paddle[0].usable = true;
	GameStatus.next.paddle[0].changed = false;
	GameStatus.next.paddle[0].type = normalPaddle;
	
	// place the paddle in the bottom center
	GameStatus.next.paddle[0].sides.left = (boardWidth - paddleWidth) / 2;
	GameStatus.next.paddle[0].sides.top = boardHeight - paddleHeight;
	GameStatus.next.paddle[0].sides.right = GameStatus.next.paddle[0].sides.left + paddleWidth;
	GameStatus.next.paddle[0].sides.bottom = GameStatus.next.paddle[0].sides.top + paddleHeight;


	// Start without any balls.  The user will add a ball into play later.
	for (i = ballsMax - 1; i >= 0; i--)
		{
		GameStatus.next.ball[i].usable = false;
		GameStatus.next.ball[i].changed = false;
		}


	// Setup a pattern of bricks for this level
	GameStatus.bricksRemaining = 0;
	MemMove(&GameStatus.brick, &levelInfo[GameStatus.level % levelCount].brick, 
		sizeof(BrickType) * rowsOfBricks * columnsOfBricks);
	
	// Count the bricks remaining to break
	for (y = 0; y < rowsOfBricks; y++)
		{
		for (x = 0; x < columnsOfBricks; x++)
			{
			if (GameStatus.brick[y][x] != empty &&
				GameStatus.brick[y][x] != unbreakable)
				GameStatus.bricksRemaining++;
			}
		}

	
	GameStatus.brokenBricksCount = 0;
	
	// Update the screen to draw the new level
	MemMove(&GameStatus.last, &GameStatus.next, sizeof(WorldState));
	GameStateDraw ();
	
	
	// Prepare to draw the level name
	currFont = FntSetFont(levelNameFont);
	nameP = levelInfo[GameStatus.level % levelCount].name;
	nameLength = StrLen(nameP);
	nameWidth = FntCharsWidth(nameP, nameLength);
	
	// Clear a surrounding box to make the text more distinguishable
	bounds.extent.y = FntLineHeight();
	bounds.extent.y += bounds.extent.y / 2;
	bounds.extent.x = nameWidth + bounds.extent.y;
	bounds.topLeft.x = boardTopLeftX + (boardWidth - bounds.extent.x) / 2;
	bounds.topLeft.y = boardTopLeftY + (boardHeight - FntLineHeight()) / 3;
	WinEraseRectangle(&bounds, 7);
	WinDrawRectangleFrame(boldRoundFrame, &bounds);

	// Draw the level name
	WinDrawChars (nameP, nameLength, 
		boardTopLeftX + (boardWidth - nameWidth) / 2,
		bounds.topLeft.y + FntLineHeight() / 4);
	FntSetFont(currFont);
	
	// Display the name for a while.  We'll remove it if the time is fully passed.
	GameStatus.periodsToWait = pauseLengthToDisplayLevelName;
}


/***********************************************************************
 *
 * FUNCTION:     GameStateAdvance
 *
 * DESCRIPTION:  Advance the world state by copying the next state
 * to the last state.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/

static void GameStateAdvance (void)
{
	MemMove(&GameStatus.last, &GameStatus.next, sizeof(WorldState));

	if (GameStatus.status == levelOver)
		{
		GameStatus.level++;
		GameStatus.ballsRemaining++;
		GameInitLevel();
		}
		
}


/***********************************************************************
 *
 * FUNCTION:     GameStart
 *
 * DESCRIPTION:  Initialize the game to start.  Nothing visual.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/23/96	Initial Revision
 *
 ***********************************************************************/
static void GameStart ()
{

	// Set the keys
	GameMaskKeys ();
	
	GameStatus.paused = false;
	GameStatus.pausedTime = 0;

	if (GameStatus.status != gameResuming)
		{
		GameStatus.next.score = 0;
		GameStatus.scoreToAwardBonusBall = firstBonusBallAwardedAtScore;
		GameStatus.soundToMake = noSound;
		GameStatus.level = Prefs.startLevel;
		GameStatus.lowestHighScorePassed = false;
		GameStatus.highestHighScorePassed = false;
		
		GameStatus.ballsRemaining = ballsPerGame;
		GameStatus.gameSpedUp = false;
		GameStatus.cheatMode = false;
		
		
		GameInitLevel ();
		GameStateAdvance();
		}
	else
		{
		GameStatus.status = SavedGameStatus;
		
		// Give the player time to get ready to play
		GameStatus.nextPeriodTime = TimGetTicks() + pauseLengthBeforeResumingSavedGame;
		
		// Show where the player left off
		GameStateDraw ();
		}

}


/***********************************************************************
 *
 * FUNCTION:     GamePlayABall
 *
 * DESCRIPTION:  Place one of the remaining balls into play moving up from
 * the paddle.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/23/96	Initial Revision
 *
 ***********************************************************************/
static void GamePlayABall ()
{
	Int16	left;
	Int16	top;
	
	
	GameStatus.ballsRemaining--;
	
	// Set play in motion
	if (GameStatus.status == waitingForBall)
		{
		GameStatus.status = ballInMotion;
		GameStatus.nextPeriodTime = TimGetTicks();
		}
		
	
	// Place a ball above paddle 0 heading up somewhere
	left = GameStatus.next.paddle[0].sides.left + (GameStatus.next.paddle[0].sides.right - 
		GameStatus.next.paddle[0].sides.left - ballWidth) / 2;
	top = GameStatus.next.paddle[0].sides.top - ballHeight;
	BallAdd(normalBall, left, top, BallStartHeadings[randN(startHeadingsCount)]);
	GameRequestSound (playBall);
	
	GameDrawBallGauge();
}


/***********************************************************************
 *
 * FUNCTION:     BrickBreak
 *
 * DESCRIPTION:  Record a brick as broken. Updates score.  Note that
 * sometimes bricks don't break.
 *
 * PARAMETERS:   row - row of the brick
 *					  column - column of the brick
 *					  ball - the ball breaking the brick.
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/
static void BrickBreak (Int16 row, Int16 column, ObjectType *ball)
{
	Int16 left;
	Int16 top;
	
	
	if (BrickExists(column, row))
		{
		if (GameStatus.brick[row][column] == unbreakable)
			{
			GameRequestSound (wallBounce);
			ball->bouncesWithoutBreakingABrick++;
			}
		else
			{
			// Add the brick to the brokenBricks list for removal during GameStateDrawChanges
			GameStatus.brokenBricks[GameStatus.brokenBricksCount].row = row;
			GameStatus.brokenBricks[GameStatus.brokenBricksCount].column = column;
			GameStatus.brokenBricksCount++;

			// Since this brick is being broken the ball won't bounce here again.  
			// Clear bouncesWithoutBreakingABrick.
			ball->bouncesWithoutBreakingABrick = 0;
			
			// Some bricks have special effects
			switch (GameStatus.brick[row][column])
				{
				case ballBrick:
					left = BrickX(column) + (brickWidth - ballWidth) / 2;
					top = BrickY(row) + (brickHeight - ballHeight) / 2;
					BallAdd(normalBall, left, top, BallStartHeadings[randN(startHeadingsCount)]);
					GameRequestSound (extraBall);
					break;
					
				case sidePaddleBrick:
					PaddleAddSidePaddle ();
					GameRequestSound (extraPaddle);
					break;
				}
							
			IncreaseScore(ScoreForBrick(row, column));
			GameStatus.brick[row][column] = empty;
			GameStatus.bricksRemaining--;
			
			GameRequestSound (brickBreak);
			}
		}
}


/***********************************************************************
 *
 * FUNCTION:     GetNearestSurface
 *
 * DESCRIPTION:  Get the rectangle surface that a ball is closest to.
 *   Most importantly this routine determines the tricky corner cases.
 *
 * PARAMETERS:   ball - the ball to check
 *					  r - rectangle of surfaces
 *
 * RETURNED:     the surface.  surfaceNone may be returned if the ball missed.
 *   The ball may miss because the course collision checking is retangular
 *   but the bitmap is round.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/29/96	Initial Revision
 *
 ***********************************************************************/
static UInt8 GetNearestSurface (ObjectType	*ball, AbsRectType *r)
{
	int Xb, Yb;			// ball center.
	int Xs, Ys;			// rectangle surface
	int b;				// intersection of ball with Y axis. (point slope equ.)
	int d2;				// distance between the ball and point of intersection
	int shortestDistance;	// shortest distance;
	UInt8 surface;		// surface with shortest distance
	
	
	shortestDistance = boardWidth + boardHeight;
	surface = surfaceNone;
	
	
	// For each surface find the distance of the ball to it's intersection
	// with the surface.
	
	// First, make a line equation describing the motion of the ball.
	// Yb = h * Xb + b.  h is the ball heading Yb and Xb are the ball's center.
	// b is unknown.  Solve for it.
	Xb = ball->sides.left + (ball->sides.right - ball->sides.left) / 2;
	Yb = ball->sides.top + (ball->sides.bottom - ball->sides.top) / 2;
	b = Yb - ((Xb * MovementY[ball->heading]) / MovementX[ball->heading]);
	
	
	// Now find the intersection of the center of the ball to the top surface.
	if (HeadingDown(ball->heading))
		{
		Ys = r->top;
		Xs = (((Ys - b) * MovementX[ball->heading]) / MovementY[ball->heading]);
		if ((r->left <= Xs + halfBallWidth) && (Xs - halfBallWidth <= r->right))
			{
			d2 = (Xb - Xs) * (Xb - Xs) + (Yb - Ys) * (Yb - Ys);
			
			shortestDistance = d2;
	
			// The corner cases should go to the other edge
			if (Xs < r->left && HeadingRight(ball->heading))
				surface = surfaceLeft;
			else if (Xs > r->right && HeadingLeft(ball->heading))
				surface = surfaceRight;
			else
				surface = surfaceTop;
			}
		}
	
	
	// Now find the intersection of the center of the ball to the bottom surface.
	if (HeadingUp(ball->heading))
		{
		Ys = r->bottom;
		Xs = (((Ys - b) * MovementX[ball->heading]) / MovementY[ball->heading]);
		if ((r->left <= Xs + halfBallWidth) && (Xs - halfBallWidth <= r->right))
			{
			d2 = (Xb - Xs) * (Xb - Xs) + (Yb - Ys) * (Yb - Ys);
			
			if (d2 < shortestDistance)
				{
				// The corner cases should go to the other edge
				if (Xs < r->left && HeadingRight(ball->heading))
					surface = surfaceLeft;
				else if (Xs > r->right && HeadingLeft(ball->heading))
					surface = surfaceRight;
				else
					surface = surfaceBottom;
	
				shortestDistance = d2;
				}
			}
		}
	
	
	// Now find the intersection of the center of the ball to the left surface.
	if (HeadingRight(ball->heading))
		{
		Xs = r->left;
		Ys = ((Xs * MovementY[ball->heading]) / MovementX[ball->heading]) + b;
		if ((r->top <= Ys + halfBallHeight) && (Ys - halfBallHeight <= r->bottom))
			{
			d2 = (Xb - Xs) * (Xb - Xs) + (Yb - Ys) * (Yb - Ys);
			
			if (d2 < shortestDistance)
				{
				// The corner cases should go to the other edge
				if (Ys < r->top && HeadingDown(ball->heading))
					surface = surfaceTop;
				else if (Ys > r->bottom && HeadingUp(ball->heading))
					surface = surfaceBottom;
				else
					surface = surfaceLeft;
	
				shortestDistance = d2;
				}
			}
		}
	
	
	// Now find the intersection of the center of the ball to the right surface.
	if (HeadingLeft(ball->heading))
		{
		Xs = r->right;
		Ys = ((Xs * MovementY[ball->heading]) / MovementX[ball->heading]) + b;
		if ((r->top <= Ys + halfBallHeight) && (Ys - halfBallHeight <= r->bottom))
			{
			d2 = (Xb - Xs) * (Xb - Xs) + (Yb - Ys) * (Yb - Ys);
			
			if (d2 < shortestDistance)
				{
				// The corner cases should go to the other edge
				if (Ys < r->top && HeadingDown(ball->heading))
					surface = surfaceTop;
				else if (Ys > r->bottom && HeadingUp(ball->heading))
					surface = surfaceBottom;
				else
					surface = surfaceRight;
					
				shortestDistance = d2;
				}
			}
		}
		
	
	return surface;
}
	
	
/***********************************************************************
 *
 * FUNCTION:     CheckBallWithWallCollisions
 *
 * DESCRIPTION:  Check for collisions of a ball into the walls.
 *
 * If the ball is past a boundary, the ball is reflected and moved from
 * it's last position.  The caller should call this again for corners
 * which involve two collisions.
 *
 * PARAMETERS:   ballNumber - the ball to check
 *
 * RETURNED:     true if a collision occurred
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/
static Boolean CheckBallWithWallCollisions (Int16 ballNumber)
{
	ObjectType	*ball;
	
	
	ball = &GameStatus.next.ball[ballNumber];
	if (ball->sides.left < 0)
		{
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		GameRequestSound (wallBounce);
		return true;
		}
	else if (ball->sides.right > boardWidth)
		{
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		GameRequestSound (wallBounce);
		return true;
		}
	
	if (ball->sides.top < 0)
		{
		ball->heading = BallReflect(ball->heading, surfaceHorizontal, noMotion);
		BallMove(ballNumber);
		GameRequestSound (wallBounce);
		
		// When the top wall is hit the game speeds up if the period is slower than one tick.
		// At one tick or faster the game is too fast!
		if (!GameStatus.gameSpedUp &&
			GameStatus.periodLength > minPeriodLength)
			{
			GameStatus.periodLength--;
			GameStatus.gameSpedUp = true;
			GameRequestSound (speedBall);
			}
		return true;
		}

	// Check if the ball completely moved off the bottom
	if (ball->sides.top > boardHeight)
		{
		BallRemove (ballNumber);
		return false;
		}

	return false;

}


/***********************************************************************
 *
 * FUNCTION:     CheckBallWithBrickCollisions
 *
 * DESCRIPTION:  Check for collisions of a ball into the bricks.
 *
 * Each ball corner is capable of breaking a brick.  For each corner
 * find out which brick it touches.  The combination of bricks touched
 * determines which bricks are broken and how the ball reflects.
 *
 * No ball may move more than the height of a brick in one period.
 *
 * 0.   B		the top left and bottom right are in the same brick
 *      B		reflect once, break brick
 *
 * 1.  B x		the top left and bottom right are in different bricks
 *     x B		reflect twice, break both
 *
 * 2.  x B		the top right and bottom left are in different bricks
 *     B x		reflect twice, break both
 *
 * 3.  B B		the tops touch one or two bricks
 *     x x		reflect once, break one or two bricks
 *
 * 4.  x x		the bottoms touch one or two bricks
 *     B B		reflect once, break one or two bricks
 *
 * 5.  B x		the lefts touch one or two bricks
 *     B x		reflect once, break one or two bricks
 *
 * 6.  x B		the rights touch one or two bricks
 *     x B		reflect once, break one or two bricks
 *
 * 7.  B B		not possible because ball can't move more than one brick height
 *     B B		
 *
 * Cases of only one brick existing are covered by cases 3 and 4.  They perform
 * special checking for the ball bouncing off a corner when there is one brick.
 *
 * Cases 3 to 6 check to see if enough of the ball is touching a brick before it
 *	is removed.  The ball is fat enough compared to the bricks to often touch two
 * bricks at the same time.  This code requires more than the corner of a ball to
 * touch before removing a brick.
 *
 *		2) When a corner is touched cases 3 & 4 tend to activate when a vertical
 *			bounce is expected because the ball touches more vertical than horizontal
 *			surface.  Code detects this and leaves cases 5 & 6 to reflect the ball.
 *
 * PARAMETERS:   ballNumber - the ball to check
 *
 * RETURNED:     true if a collision occurred
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/
static Boolean CheckBallWithBrickCollisions (Int16 ballNumber)
{
	ObjectType	*ball;
	PointType ballCorner[4];		// topleft, topRight, bottomRight, bottomLeft
											// Brick touched by the corner
	Boolean brickExists[4];			// true if a brick exists at the ball corner
	PointType brick1, brick2;		// two bricks may be broken
	Boolean brickFound = false;
	AbsRectType	bounds;				// bounds of a brick
	Int16 amountTouching;				// amount of the ball touching a brick
	UInt8 surface;						// surface to bounce the ball off of
	
	
	ball = &GameStatus.next.ball[ballNumber];
	
	// Trivial rejection case: the ball is below all the bricks.
	if (ball->sides.top >= BrickY(rowsOfBricks))
		return false;
	
	// Calculate two of the corners for case 0
	ballCorner[0].x = BrickAtX(ball->sides.left);
	ballCorner[0].y = BrickAtY(ball->sides.top);
	ballCorner[2].x = BrickAtX(ball->sides.right);
	ballCorner[2].y = BrickAtY(ball->sides.bottom);
	
	
	// Case 0:
	if (ballCorner[0].x == ballCorner[2].x &&
		ballCorner[0].y == ballCorner[2].y)
		{
		if (!BrickExists(ballCorner[0].x, ballCorner[0].y))
			return false;
		
		ErrFatalDisplayIf(ballCorner[0].y > brickEndRow, "Bad bounce");
		
		// Reflect the ball once
		ball->heading = BallReflect(ball->heading, surfaceHorizontal, noMotion);
		BallMove(ballNumber);
		
		// Designate one brick to break.
		brickFound = true;
		brick1.x = ballCorner[0].x;
		brick1.y = ballCorner[0].y;
		brick2.x = ballCorner[0].x;
		brick2.y = ballCorner[0].y;
		goto brickFound;
		}
	
	
	// Calculate the remaining two of the corners for the rest of the cases
	ballCorner[1].x = BrickAtX(ball->sides.right);
	ballCorner[1].y = BrickAtY(ball->sides.top);
	ballCorner[3].x = BrickAtX(ball->sides.left);
	ballCorner[3].y = BrickAtY(ball->sides.bottom);
	
	// Determine which corners touch a brick.
	brickExists[0] = BrickExists(ballCorner[0].x, ballCorner[0].y);
	brickExists[1] = BrickExists(ballCorner[1].x, ballCorner[1].y);
	brickExists[2] = BrickExists(ballCorner[2].x, ballCorner[2].y);
	brickExists[3] = BrickExists(ballCorner[3].x, ballCorner[3].y);
	
	
	// If no corner touches a brick then return no collision
	if (brickExists[0] + brickExists[1] + brickExists[2] + brickExists[3] == 0)
		return false;
		
	
	// Case 1:  This case and Case 2 must be done before the rest
	if (brickExists[0] && brickExists[2])
		{
		// Reflect the ball twice
		ball->heading = BallReflect(ball->heading, surfaceHorizontal, noMotion);
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		
		// Designate two bricks to break.
		brickFound = true;
		brick1.x = ballCorner[0].x;
		brick1.y = ballCorner[0].y;
		brick2.x = ballCorner[2].x;
		brick2.y = ballCorner[2].y;
		goto brickFound;
		}
	
	// Case 2:  This case and Case 1 must be done before the rest
	else if (brickExists[1] && brickExists[3])
		{
		// Reflect the ball twice
		ball->heading = BallReflect(ball->heading, surfaceHorizontal, noMotion);
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		
		// Designate two bricks to break.
		brickFound = true;
		brick1.x = ballCorner[1].x;
		brick1.y = ballCorner[1].y;
		brick2.x = ballCorner[3].x;
		brick2.y = ballCorner[3].y;
		goto brickFound;
		}
	
	
	// Case 5:  MemHandle this case and case 6 next.
	if ((brickExists[0] && brickExists[3])) 
		{
		// Reflect the ball once
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		
		// Designate two bricks to break.
		brickFound = true;
		brick1.x = ballCorner[0].x;
		brick1.y = ballCorner[0].y;
		brick2.x = ballCorner[3].x;
		brick2.y = ballCorner[3].y;
			
		// Detect if both bricks are hit.  If so require that they be hit by
		// a certain amount of the ball.
		if (brickExists[0] && brickExists[3] &&
			(brick1.x != brick2.x))
			{
			amountTouching = ball->sides.bottom - BrickY(brick2.y);
			// Touching brick2 enough?
			if (amountTouching < ballAmountNeededToBreakABrick)
				{
				brick2.x = brick1.x;
				brick2.y = brick1.y;
				}
			// Touching brick1 enough?
			else if ((ballHeight - amountTouching) < ballAmountNeededToBreakABrick)
				{
				brick1.x = brick2.x;
				brick1.y = brick2.y;
				}
			}
		}
	
	// Case 6:
	else if ((brickExists[1] && brickExists[2])) 
		{
		// Reflect the ball once
		ball->heading = BallReflect(ball->heading, surfaceVertical, noMotion);
		BallMove(ballNumber);
		
		// Designate two bricks to break.
		brickFound = true;
		brick1.x = ballCorner[1].x;
		brick1.y = ballCorner[1].y;
		brick2.x = ballCorner[2].x;
		brick2.y = ballCorner[2].y;

		// Detect if both bricks are hit.  If so require that they be hit by
		// a certain amount of the ball.
		if (brickExists[1] && brickExists[2] &&
			(brick1.x != brick2.x))
			{
			amountTouching = ball->sides.bottom - BrickY(brick2.y);
			// Touching brick2 enough?
			if (amountTouching < ballAmountNeededToBreakABrick)
				{
				brick2.x = brick1.x;
				brick2.y = brick1.y;
				}
			// Touching brick1 enough?
			else if ((ballHeight - amountTouching) < ballAmountNeededToBreakABrick)
				{
				brick1.x = brick2.x;
				brick1.y = brick2.y;
				}
			}
		}
	
	// Case 3:  Probably the most likely case.  The following two cases have
	// been generalized to MemHandle one or two bricks present.  This means they
	// cover and therefore must follow the cases above which are more specific.
	else if ((brickExists[0] || brickExists[1])) 
		{
		// Calculate the surface.  Since we cover the cases where there exists only
		// one brick the ball may actually hit a corner.  If only one corner is
		// in a brick let GetNearestSurface determine which sides of the brick
		// is hit.
		if (brickExists[0] && !brickExists[1])
			{
			bounds.top = BrickY(ballCorner[0].y);
			bounds.bottom = bounds.top + brickHeight;
			bounds.left = BrickX(ballCorner[0].x);
			bounds.right = bounds.left + brickWidth;
			
			surface = GetNearestSurface (ball, &bounds);
			}
		else if (!brickExists[0] && brickExists[1])
			{
			bounds.top = BrickY(ballCorner[1].y);
			bounds.bottom = bounds.top + brickHeight;
			bounds.left = BrickX(ballCorner[1].x);
			bounds.right = bounds.left + brickWidth;
			
			surface = GetNearestSurface (ball, &bounds);
			}
		else 
			{
			surface = surfaceHorizontal;
			}
		
		if (surface != surfaceNone)
			{
			// Reflect the ball once
			ball->heading = BallReflect(ball->heading, surface, noMotion);
			BallMove(ballNumber);
			
			// Designate two bricks to break.
			brickFound = true;
			brick1.x = ballCorner[0].x;
			brick1.y = ballCorner[0].y;
			brick2.x = ballCorner[1].x;
			brick2.y = ballCorner[1].y;
			
			// Detect if both bricks are hit.  If so require that they be hit by
			// a certain amount of the ball.
			if (brickExists[0] && brickExists[1] &&
				(brick1.x != brick2.x))
				{
				amountTouching = ball->sides.right - BrickX(brick2.x);
				// Touching brick2 enough?
				if (amountTouching < ballAmountNeededToBreakABrick)
					{
					brick2.x = brick1.x;
					brick2.y = brick1.y;
					}
				// Touching brick1 enough?
				else if ((ballWidth - amountTouching) < ballAmountNeededToBreakABrick)
					{
					brick1.x = brick2.x;
					brick1.y = brick2.y;
					}
				}
			}
		}
	
	// Case 4:  Next most likely case
	else if ((brickExists[2] || brickExists[3])) 
		{
		// Calculate the surface.  Since we cover the cases where there exists only
		// one brick the ball may actually hit a corner.  If only one corner is
		// in a brick let GetNearestSurface determine which sides of the brick
		// is hit.
		if (brickExists[2] && !brickExists[3])
			{
			bounds.top = BrickY(ballCorner[2].y);
			bounds.bottom = bounds.top + brickHeight;
			bounds.left = BrickX(ballCorner[2].x);
			bounds.right = bounds.left + brickWidth;
			
			surface = GetNearestSurface (ball, &bounds);
			}
		else if (!brickExists[2] && brickExists[3])
			{
			bounds.top = BrickY(ballCorner[3].y);
			bounds.bottom = bounds.top + brickHeight;
			bounds.left = BrickX(ballCorner[3].x);
			bounds.right = bounds.left + brickWidth;
			
			surface = GetNearestSurface (ball, &bounds);
			}
		else 
			{
			surface = surfaceHorizontal;
			}
		
		if (surface != surfaceNone)
			{
			// Reflect the ball once
			ball->heading = BallReflect(ball->heading, surface, noMotion);
			BallMove(ballNumber);
			
			// Designate two bricks to break.
			brickFound = true;
			brick1.x = ballCorner[3].x;
			brick1.y = ballCorner[3].y;
			brick2.x = ballCorner[2].x;
			brick2.y = ballCorner[2].y;
			
			// Detect if both bricks are hit.  If so require that they be hit by
			// a certain amount of the ball.
			if (brickExists[2] && brickExists[3] &&
				(brick1.x != brick2.x))
				{
				amountTouching = ball->sides.right - BrickX(brick2.x);
				// Touching brick2 enough?
				if (amountTouching < ballAmountNeededToBreakABrick)
					{
					brick2.x = brick1.x;
					brick2.y = brick1.y;
					}
				// Touching brick1 enough?
				else if ((ballWidth - amountTouching) < ballAmountNeededToBreakABrick)
					{
					brick1.x = brick2.x;
					brick1.y = brick2.y;
					}
				}
			}
		}
	
	
	
	
	if (brickFound)
		{
brickFound:
		// Award points for the brick and remove it.
		BrickBreak(brick1.y, brick1.x, ball);
		
		// If brick2 is the same as brick1 nothing will be done (it is empty now).
		BrickBreak(brick2.y, brick2.x, ball);
		}
	
	return brickFound;
}


/***********************************************************************
 *
 * FUNCTION:     CheckBallWithPaddleCollisions
 *
 * DESCRIPTION:  Check for collisions of a ball into the paddles.
 *
 * If the ball touches a paddle, the ball is reflected and moved from
 * it's last position.  The caller should call this again for corners
 * which involve two collisions.
 *
 * PARAMETERS:   ballNumber - the ball to check
 *
 * RETURNED:     true if a collision occurred
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/24/96	Initial Revision
 *
 ***********************************************************************/
static Boolean CheckBallWithPaddleCollisions (Int16 ballNumber)
{
	ObjectType	*ball;
	int i;
	UInt8 surface;
	UInt8 motion;
	
	
	ball = &GameStatus.next.ball[ballNumber];

	for (i = paddlesMax - 1; i >= 0; i--)
		{
		if (GameStatus.next.paddle[i].usable)
			{
			if ((ball->sides.bottom >= GameStatus.next.paddle[i].sides.top &&
				ball->sides.bottom <= GameStatus.next.paddle[i].sides.bottom) ||
				(ball->sides.top >= GameStatus.next.paddle[i].sides.top &&
				ball->sides.top <= GameStatus.next.paddle[i].sides.bottom))
				{
				// Now worry about the side of the paddle
				if (ball->sides.right < GameStatus.next.paddle[i].sides.left ||
					ball->sides.left > GameStatus.next.paddle[i].sides.right)
					continue;
				
				
				surface = GetNearestSurface (ball, &GameStatus.next.paddle[i].sides);
				if (surface == surfaceNone)
					continue;
				
				if (GameStatus.movePaddleLeft)
					motion = leftMotion;
				else if (GameStatus.movePaddleRight)
					motion = rightMotion;
				else
					motion = noMotion;
				
				// The ball did hit the paddle.  Bounce it off.
				ball->heading = BallReflect(ball->heading, surface, motion);
				BallMove(ballNumber);
				ball->bouncesWithoutBreakingABrick = 0;
				
				// If the ball collided with the side of a paddle while it was moving
				// give the ball an extra kick to keep it outside of the bounds of the
				// paddle.  The physically correct way should be to increase the velocity
				// of the ball because momentum is transfered from the paddle to the ball.
				// Our model keeps the ball at a fixed velocity so we just move the ball
				// some more.
				if (motion != noMotion)
					{
					// Did the ball hit a side surface of a paddle?
					if (surface == surfaceLeft)
						{
						ball->sides.left -= paddleMovement;
						ball->sides.right -= paddleMovement;
						}
					else if (surface == surfaceRight)
						{
						ball->sides.left += paddleMovement;
						ball->sides.right += paddleMovement;
						}
					}

				// The paddle bounced the ball. 
				GameRequestSound (paddleBounce);

				return true;
				}
			}
		}

	return false;
}


/***********************************************************************
 *
 * FUNCTION:     GameStateElapse
 *
 * DESCRIPTION:  Increment the state of the game world.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/23/96	Initial Revision
 *
 ***********************************************************************/
static void GameStateElapse ()
{
	int i;
	Int16 smallestMove;
	UInt32 hardKeyState;
	Boolean ballCollided;
	int collisionCount;
	
	
	// Don't advance past checking high scores.
	if (GameStatus.status == checkHighScores)
		return;
	
	// We have paused after the game.  Now check for a high score.
	if (GameStatus.status == gameOver)
		{
		GameStatus.status = checkHighScores;
		if (!GameStatus.cheatMode)
			HighScoresCheckScore();
		
		// Allow the hard keys to switch to another app now that the player is done.
		GameUnmaskKeys ();
		return;
		}
	
	// When all the bricks are cleared advance to the next level.
	if (GameStatus.bricksRemaining == 0)
		{
		GameStatus.status = levelOver;
		GameStatus.nextPeriodTime += levelOverTimeInterval;
		return;
		}
		
		
	// The time between the last advance and the next is constant
	GameStatus.nextPeriodTime = GameStatus.nextPeriodTime + GameStatus.periodLength;
	
	
	// Move the paddles
	GameStatus.movePaddleLeft = false;
	GameStatus.movePaddleRight = false;
	hardKeyState = KeyCurrentState() & (moveLeftKey | moveLeftKeyAlt | moveRightKey | moveRightKeyAlt);
	smallestMove = paddleMovement;
	
	// If the level name is showing and the user is ready to play or enough time has
	// passed then remove the name
	if (GameStatus.status == presentingLevel)
		{
		GameStatus.periodsToWait--;
		if (hardKeyState ||
			GameStatus.periodsToWait == 0)
			{
			GameStateDraw();
			GameStatus.status = waitingForBall;
			}
		}
		

		
	// Move the paddles in a direction.  Remember that there may be multiple paddles.
	// If one paddle can't move then none can move.
	if (hardKeyState == moveLeftKey || hardKeyState == moveLeftKeyAlt)
		{
		// Find the smallest amount a paddle may move left
		for (i = paddlesMax - 1; i >= 0; i--)
			{
			if (GameStatus.next.paddle[i].usable)
				{
				smallestMove = min(smallestMove, GameStatus.next.paddle[i].sides.left);
				}
			}
		
		// If all the paddles can move at least a little bit do it
		if (smallestMove > 0)
			{
			for (i = paddlesMax - 1; i >= 0; i--)
				{
				if (GameStatus.next.paddle[i].usable)
					{
					GameStatus.next.paddle[i].sides.left -= smallestMove;
					GameStatus.next.paddle[i].sides.right -= smallestMove;
					GameStatus.next.paddle[i].changed = true;
					}
				}
			
			GameStatus.movePaddleLeft = true;
			}

		}
	else if (hardKeyState == moveRightKey || hardKeyState == moveRightKeyAlt)
		{
		// Find the smallest amount a paddle may move right
		for (i = paddlesMax - 1; i >= 0; i--)
			{
			if (GameStatus.next.paddle[i].usable)
				{
				smallestMove = min(smallestMove, 
					boardWidth - GameStatus.next.paddle[i].sides.right);
				}
			}
		
		// If all the paddles can move at least a little bit do it
		if (smallestMove > 0)
			{
			for (i = paddlesMax - 1; i >= 0; i--)
				{
				if (GameStatus.next.paddle[i].usable)
					{
					GameStatus.next.paddle[i].sides.left += smallestMove;
					GameStatus.next.paddle[i].sides.right += smallestMove;
					GameStatus.next.paddle[i].changed = true;
					}
				}
			
			GameStatus.movePaddleRight = true;
			}
		}
	else 	// Paddles moved neither direction
		{
		// Mark each paddle as unchanged
		for (i = paddlesMax - 1; i >= 0; i--)
			{
			GameStatus.next.paddle[i].changed = false;
			}
		}

	
	// Move the balls
	for (i = ballsMax - 1; i >= 0; i--)
		{
		// Ignore unusable balls
		if (!GameStatus.next.ball[i].usable)
			{
			GameStatus.next.ball[i].usable = false;
			GameStatus.next.ball[i].changed = false;
			}
		// Don't process balls added this period by a ball brick.  BallMove relys
		// on valid bounds from the last period and so it doesn't MemHandle new balls. 
		else if (GameStatus.last.ball[i].usable)
			{
			GameStatus.next.ball[i].changed = true;
			// Add a movement vector based on the ball's heading
			BallMove(i);
			
			// Now check for collisions
			collisionCount = 0;
			do
				{
				// Check for paddle collisions
				ballCollided = CheckBallWithPaddleCollisions (i);
				
				// Check for a brick collision
				if (CheckBallWithBrickCollisions (i))
					ballCollided = true;
				
				// check for wall collisions.  Repeat until no more collisions (corners 
				// have two colisions).
				while (CheckBallWithWallCollisions (i))
					{
					ballCollided = true;
					};
				
				if (ballCollided)
					{
					collisionCount++;
				
				
					// See if the ball seems to be trapped in a pattern of unbreakable bricks and walls.
					if (GameStatus.next.ball[i].bouncesWithoutBreakingABrick > ballTrappedInLoopThreshold)
						{
						// Tweak the heading by one angle in the hopes of dislodging the ball from
						// it's pattern.
						if (GameStatus.next.ball[i].heading == degrees22 ||
							GameStatus.next.ball[i].heading == degrees112 ||
							GameStatus.next.ball[i].heading == degrees202 ||
							GameStatus.next.ball[i].heading == degrees292)
							{
							GameStatus.last.ball[i].heading++;
							}
						else if (GameStatus.next.ball[i].heading == degrees67 ||
							GameStatus.next.ball[i].heading == degrees157 ||
							GameStatus.next.ball[i].heading == degrees247 ||
							GameStatus.next.ball[i].heading == degrees337)
							{
							GameStatus.next.ball[i].heading--;
							}
						else 
							{
							// 50% chance of the ball going one way or the other
							if (randN(100) < 50)
								{
								GameStatus.next.ball[i].heading++;
								}
							else
								{
								GameStatus.next.ball[i].heading--;
								}
							}
						BallMove(i);				// move it in the new direction instead.

						// Tweak the ball again if it doesn't break out of it's pattern soon.
						GameStatus.next.ball[i].bouncesWithoutBreakingABrick = 0;
						}
						
					
					// Check to see if the ball can't move anywhere.  If so remove it.  It probably
					// is being crushed between the paddle and a wall.
					if (collisionCount >= 5)
						{
						// If the ball is being destroyed above the paddle then give the user
						// another ball and give them some bonus points!
						//
						// Some levels can cause the ball to be destroyed in certain cases.
						if (GameStatus.next.ball[i].sides.bottom < 
							GameStatus.next.paddle[0].sides.top)
							{
							GameStatus.ballsRemaining++;
							GameDrawBallGauge();
							
							IncreaseScore(100);		// Points for destroying the ball
							}
						BallRemove (i);
						break;
						}
					}

				}
			while (ballCollided);
			}

		}
	
}


/***********************************************************************
 *
 * FUNCTION:     GamePlaySounds
 *
 * DESCRIPTION:  Play a game sound.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *			roger	1/30/98	Changed to play asynchronus sounds
 *
 ***********************************************************************/
static void GamePlaySounds ()
{
	SndCommandType		sndCmd;


	if (GameStatus.soundToMake != noSound)
		{
		sndCmd.cmd = sndCmdFrqOn;
		sndCmd.param1 = Sound[GameStatus.soundToMake].frequency;
		sndCmd.param2 = Sound[GameStatus.soundToMake].duration;
		sndCmd.param3 = SoundAmp;

		SndDoCmd( 0, &sndCmd, true/*noWait*/ );

		GameStatus.soundPeriodsRemaining--;
		if (GameStatus.soundPeriodsRemaining <= 0)
			GameStatus.soundToMake = noSound;
		
		}
}


/***********************************************************************
 *
 * FUNCTION:    HighScoresClear
 *
 * DESCRIPTION: Clear the high scores and the dialog.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/23/96	Initial Revision
 *
 ***********************************************************************/
static void HighScoresClear (void)
{
	int i;
	RectangleType bounds;
	

	// Clear the high scores.
	for (i = 0; i < highScoreMax; i++)
		{
		Prefs.highScore[i].name[0] = '\0';
		Prefs.highScore[i].score = 0;
		Prefs.highScore[i].level = 1;
		}
	
	// Clear the scores listed.  This is much easier than making the 
	// form redraw itself properly. 
	bounds.topLeft.x = 0;
	bounds.topLeft.y = firstHighScoreY;
	bounds.extent.x = highScoreLevelColumnX;
	bounds.extent.y = highScoreMax * highScoreHeight;
	WinEraseRectangle(&bounds, 0);

}


/***********************************************************************
 *
 * FUNCTION:    HighScoresEventHandler
 *
 * DESCRIPTION: MemHandle the Clear button
 *
 * PARAMETERS:  eventP - event to MemHandle
 *
 * RETURNED:    true if event handled
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/23/96	Initial Revision
 *
 ***********************************************************************/
static Boolean HighScoresEventHandler (EventPtr eventP)
{
	if (eventP->eType == ctlSelectEvent)
		{
		if (eventP->data.ctlSelect.controlID == HighScoresClearButton)
			{
			if (FrmAlert(ClearHighScoresAlert) == ClearHighScoresYes)
				HighScoresClear();
			
			return true;
			}
		}
	
	return false;
}


/***********************************************************************
 *
 * FUNCTION:    HighScoresDisplay
 *
 * DESCRIPTION: Display the high score dialog
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/11/96	Initial Revision
 *
 ***********************************************************************/
static void HighScoresDisplay (void)
{
	FormPtr curFormP;
	FormPtr formP;
	MemHandle titleH;
	Char * titleP;
	char string[16];
	FontID currFont;
	int i;
	Int16 y;


	curFormP = FrmGetActiveForm ();
	formP = FrmInitForm (HighScoresDialog);
	FrmSetActiveForm (formP);
	FrmDrawForm (formP);

	// Remember the font	
	currFont = FntSetFont(boldFont);
	
	
	// Draw the titles of the columns
	titleH = DmGetResource(strRsc, NameColumnStr);
	titleP = MemHandleLock(titleH);
	WinDrawChars(titleP, StrLen(titleP), highScoreNameColumnX,
		firstHighScoreY - highScoreHeight);
	MemPtrUnlock(titleP);	

	titleH = DmGetResource(strRsc, ScoreColumnStr);
	titleP = MemHandleLock(titleH);
	WinDrawChars(titleP, StrLen(titleP), highScoreScoreColumnX - 
		FntCharsWidth(titleP, StrLen(titleP)), firstHighScoreY - highScoreHeight);
	MemPtrUnlock(titleP);	

	titleH = DmGetResource(strRsc, LevelColumnStr);
	titleP = MemHandleLock(titleH);
	WinDrawChars(titleP, StrLen(titleP), highScoreLevelColumnX - 
		FntCharsWidth(titleP, StrLen(titleP)), firstHighScoreY - highScoreHeight);
	MemPtrUnlock(titleP);	


	WinDrawLine(highScoreNameColumnX, firstHighScoreY - 1, highScoreLevelColumnX, firstHighScoreY - 1);
	// Draw each high score in the right spot
	for (i = 0; i < highScoreMax && Prefs.highScore[i].score > 0; i++)
		{
		y = firstHighScoreY + i * highScoreHeight;

		// Differentiate the last high score by choosing a different font.
		if (i == Prefs.lastHighScore)
			FntSetFont(boldFont);
		else
			FntSetFont(highScoreFont);
		
		// Display the score number
		StrIToA(string, i + 1);
		StrCat(string, ". ");
		WinDrawChars(string, StrLen(string), highScoreNameColumnX - 
			FntCharsWidth(string, StrLen(string)), y);
		
		WinDrawChars(Prefs.highScore[i].name, StrLen(Prefs.highScore[i].name),
			highScoreNameColumnX, y);
		
		StrIToA(string, Prefs.highScore[i].score);
		WinDrawChars(string, StrLen(string), highScoreScoreColumnX - 
			FntCharsWidth(string, StrLen(string)), y);
		
		StrIToA(string, Prefs.highScore[i].level);
		WinDrawChars(string, StrLen(string), highScoreLevelColumnX - 
			FntCharsWidth(string, StrLen(string)), y);
		}
	FntSetFont(currFont);

	FrmSetEventHandler(formP, HighScoresEventHandler);		// MemHandle the clear button
	
	FrmDoDialog (formP);
	FrmDeleteForm (formP);
	FrmSetActiveForm (curFormP);
}


/***********************************************************************
 *
 * FUNCTION:    HighScoresAddScore
 *
 * DESCRIPTION: Add the new score.
 *
 * PARAMETERS:  position - the position to add the score
 *					 name - name to add
 *					 score - score to add
 *					 level - level to add
 *					 dontAddIfExists - used when initializing scores
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/13/96	Initial Revision
 *			roger	3/19/96	Broke out the check and contratulations dialog
 *
 ***********************************************************************/
static void HighScoresAddScore (const Char * name, Int32 score, Int16 level, 
	Boolean dontAddIfExists)
{
	int position;
	
	
	// Find where the score belongs.  The new score looses any ties.
	position = highScoreMax;
	while (position > 0 &&
		score > Prefs.highScore[position - 1].score)
		{
		position--;
		}
	
	
	// Leave if the score doesn't make it into the high scores.
	if (position >= highScoreMax)
		return;
	
	if (dontAddIfExists &&
		position > 0 &&
		StrCompare(name, Prefs.highScore[position - 1].name) == 0 &&
		score == Prefs.highScore[position - 1].score &&
		level == Prefs.highScore[position - 1].level)
		return;
		
	// Move down the scores to make room for the new high score.
	MemMove(&Prefs.highScore[position + 1], &Prefs.highScore[position],
		(highScoreMax - 1 - position) * sizeof (SavedScore));
	
	
	Prefs.highScore[position].score = score;
	Prefs.highScore[position].level = level;
	StrCopy(Prefs.highScore[position].name, name);
	
	
	// Record this new score as the last one entered.
	Prefs.lastHighScore = position;
}


/***********************************************************************
 *
 * FUNCTION:    HighScoresCheckScore
 *
 * DESCRIPTION: Check if the current score is a high one and call
 *	HighScoresAddScore if so.
 *
 * PARAMETERS:  score - score to possibly add
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/13/96	Initial Revision
 *			roger	3/19/96	Broke into separate routine
 *			jmp	10/25/99	Don't use nameP unless it's locked; fixes
 *								bug #21539.
 *
 ***********************************************************************/
static void HighScoresCheckScore (void)
{
	int i;
	MemHandle nameH;
	Char * nameP;
	Char * firstSpaceP;
	FormPtr curFormP;
	FormPtr formP;
	UInt16 objIndex;
	UInt16 buttonHit;

	i = highScoreMax;
	while (i > 0 &&
		GameStatus.next.score > Prefs.highScore[i - 1].score)
		i--;

	// Leave if the score doesn't make it into the high scores.
	if (i >= highScoreMax)
		return;

	// Allocate a chunk for the user to edit.  The field in the dialog requires
	// the text to be in a chunk so it can be resized.
	nameH = MemHandleNew(dlkMaxUserNameLength + 1);
	nameP = MemHandleLock(nameH);

	// For the name, try and use the name last entered
	if (Prefs.lastHighScore != highScoreMax)
		{
		StrCopy(nameP, Prefs.highScore[Prefs.lastHighScore].name);
		}
	else
		{		
		StrCopy(nameP, "");
		
		// Try and use the user's name
		DlkGetSyncInfo(NULL, NULL, NULL, nameP, NULL, NULL);
		
		// Just use the first name
		firstSpaceP = StrChr(nameP, spaceChr);
		if (firstSpaceP)
		 	*firstSpaceP = '\0';
		
		// Truncate the string to insure it's not too long
		nameP[nameLengthMax] = '\0';
		}
	MemPtrUnlock(nameP);

	// Record this new score as the last one entered.
	Prefs.lastHighScore = i;

	// Now Display a dialog contragulating the user and ask for their name.
	curFormP = FrmGetActiveForm ();
	formP = FrmInitForm (NewHighScoresDialog);

	// Set the field to edit the name.
	objIndex = FrmGetObjectIndex (formP, NewHighScoresNameField);
	FldSetTextHandle(FrmGetObjectPtr (formP, objIndex), nameH);
	// Set the insertion point blinking in the only field.
	FrmSetFocus(formP, objIndex);
	// Set Graffiti to be shifted.
	GrfSetState(false, false, true);
	
	// Allow the user to type in a name.  Wait until a button is pushed. OK is 
	// the default button so if the app is switched the high score is still entered.
	// The user must press cancel to not record the score.
	buttonHit = FrmDoDialog (formP);

	// Take the text MemHandle from the field so the text isn't deleted when the form is.
	FldSetTextHandle(FrmGetObjectPtr (formP, objIndex), 0);
	
	FrmDeleteForm (formP);					// Deletes the field's new text.
	FrmSetActiveForm (curFormP);

	// Add the score unless the user removed the name.  If so they probably didn't
	// want the score entered so don't!
	nameP = MemHandleLock(nameH);
	if (buttonHit == NewHighScoresOKButton &&
		nameP[0] != '\0')	
		HighScoresAddScore(nameP, GameStatus.next.score, GameStatus.level + 1, false);

	// The name is now recorded and no longer needed.
	MemHandleFree(nameH);

	// Now display where the new high score is in relation to the others
	if (buttonHit == NewHighScoresOKButton)
		HighScoresDisplay();
}


/***********************************************************************
 *
 * FUNCTION:    PreferencesDialogInit
 *
 * DESCRIPTION: Initialize the dialog's ui.  Sets the starting
 * level list.
 *
 * PARAMETERS:  frm
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/21/96	Initial Revision
 *
 ***********************************************************************/
static void PreferencesDialogInit (FormPtr formP)
{
	ListPtr listP;
	UInt16 mappedValue;
	
	
	NewStartLevel = Prefs.startLevel;
	
	// Set the time format trigger and list
	listP = FrmGetObjectPtr (formP, FrmGetObjectIndex (formP, PreferencesStartingLevelList));
	mappedValue = MapToPosition ((UInt8 *) StartLevelMappings,
										  Prefs.startLevel,
										  startLevelsSelectable,
										  defaultStartLevelItem);
	LstSetSelection(listP, mappedValue);

}


/***********************************************************************
 *
 * FUNCTION:    PreferencesDialogHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 * "Preferences Dialog"
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has MemHandle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/21/96	Initial Revision
 *
 ***********************************************************************/
static Boolean PreferencesDialogHandleEvent (EventPtr event)
{
	FormPtr frm;
	Boolean handled = false;


	if (event->eType == lstSelectEvent)
		{
		switch (event->data.lstSelect.listID)
			{
			case PreferencesStartingLevelList:
				NewStartLevel = StartLevelMappings[event->data.lstSelect.selection];
				handled = true;
				break;
			}
		}

	else if (event->eType == ctlSelectEvent)
		{
		switch (event->data.ctlSelect.controlID)
			{
			case PreferencesOKButton:
				Prefs.startLevel = NewStartLevel;
				FrmReturnToForm(0);
				handled = true;
				break;

			case PreferencesCancelButton:
				FrmReturnToForm(0);
				handled = true;
				break;
				
			}
		}


	if (event->eType == frmOpenEvent)
		{
		frm = FrmGetActiveForm ();
		
		PreferencesDialogInit(frm);
		FrmDrawForm (frm);

		handled = true;
		}

		
	return (handled);
}


/***********************************************************************
 *
 * FUNCTION:    BoardViewDoCommand
 *
 * DESCRIPTION: Performs the menu command specified.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has MemHandle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *
 ***********************************************************************/
static Boolean BoardViewDoCommand (UInt16 command)
{
	switch (command)
		{
		case BoardGameNewCmd:
			GameStart();
			break;

		case AboutCmd:
			AbtShowAbout (appFileCreator);
			break;
					
		case BoardGameInstructionsCmd:
			FrmHelp (InstructionsStr);
			break;
					
		case BoardGameHighScoresCmd:
			HighScoresDisplay();
			break;
					
		case BoardGamePreferencesCmd:
			FrmPopupForm (PreferencesDialog);
			break;
		}
	
	return true;
}


/***********************************************************************
 *
 * FUNCTION:    BoardViewHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the "Board View"
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has MemHandle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/01/95	Initial Revision
 *			kwk	12/03/98	Limit keydown actions for normal letters to only
 *								work if the command key bit isn't set.
 *			CSS	06/22/99	Standardized keyDownEvent handling
 *								(TxtCharIsHardKey, commandKeyMask, etc.)
 *			jmp	10/11/99 Call FrmDrawForm() at frmUpdateEvent time to fix
 *								update problems on PalOS 3.5 and later debug ROMs.
 *			jmp	12/20/99	Prevent the command bar from interfering from
*								game play by not allowing it to become available.
 *
 ***********************************************************************/
static Boolean BoardViewHandleEvent (EventPtr event)
{
	FormPtr frm;
	Boolean handled = false;

	if (event->eType == nilEvent)
		{
		}

	else if (event->eType == keyDownEvent)
		{
		if (TxtCharIsHardKey(event->data.keyDown.modifiers, event->data.keyDown.chr))
			{
			}

		// The releaseBall & restartGame characters are currently virtual characters,
		// thus the command bit must be set.
		else if (EvtKeydownIsVirtual(event))
			{
			if (event->data.keyDown.chr == releaseBallChr)
				{
				if (GameStatus.status == presentingLevel)
					{
					GameStateDraw();			// Remove the level name
					GameStatus.status = waitingForBall;
					}
					
				if (GameStatus.status == waitingForBall &&
					GameStatus.ballsRemaining > 0)
					{
					GamePlayABall();
					}
				}
			// Restart game using the page down key.  Don't allow this in the
			// middle of a game.  Othewise if the user accidentally presses it
			// they loose their game in progress!
			else if (event->data.keyDown.chr == restartGameChar)
				{
				if (GameStatus.status == checkHighScores)
					{
					GameStart();
					}
				}
			}

		// forward one level
		else if (event->data.keyDown.chr == 'N')
			{
			GameStatus.cheatMode = true;
			GameStatus.bricksRemaining = 0;
			GameStatus.status = ballInMotion;
			}
		// back one level
		else if (event->data.keyDown.chr == 'P')
			{
			GameStatus.cheatMode = true;
			GameStatus.bricksRemaining = 0;
			GameStatus.status = ballInMotion;
			GameStatus.level = max (0, GameStatus.level - 2);
			}
		// replay level
		else if (event->data.keyDown.chr == 'R')
			{
			GameStatus.cheatMode = true;
			GameStatus.bricksRemaining = 0;
			GameStatus.status = ballInMotion;
			GameStatus.level = max (0, GameStatus.level - 1);
			}
		// bonus ball
		else if (event->data.keyDown.chr == 'B')
			{
			GameStatus.cheatMode = true;
			// Add a ball to those remaining and update the ball gauge.
			GameStatus.ballsRemaining++;
			GameDrawBallGauge();
			}
		// time spent playing		(quick code at this point.)
		else if (event->data.keyDown.chr == 't')
			{
			char timeString[timeStringLength + 5];
			UInt32 seconds;
			DateTimeType timeSpent;
			
			seconds = (Prefs.accumulatedTime + (TimGetTicks() - GameStatus.startTime)) / sysTicksPerSecond;
			TimSecondsToDateTime(seconds, &timeSpent);
			TimeToAscii(timeSpent.hour, timeSpent.minute, tfColon24h, timeString);
			StrCat(timeString, ":");
			
			if (timeSpent.second < 10)
				StrCat(timeString, "0");
			StrIToA(&timeString[StrLen(timeString)], timeSpent.second);
			WinDrawChars (timeString, StrLen(timeString), 68, 130);
			}
		
		return true;
		}

	else if (event->eType == menuEvent)
		{
		BoardViewDoCommand (event->data.menu.itemID);
		return true;
		}

		
	else if (event->eType == frmCloseEvent)
		{
		}

	else if (event->eType == frmOpenEvent)
		{
		frm = FrmGetActiveForm ();

		FrmDrawForm (frm);
		GameStart ();

		handled = true;
		}

	else if (event->eType == frmUpdateEvent)
		{
		frm = FrmGetFormPtr (BoardView);
		
		FrmDrawForm (frm);
		GameStateDraw ();
		
		handled = true;
		}
		
	// Don't allow the command bar to come up as it interferes with game play.
	else if (event->eType == menuCmdBarOpenEvent)
		handled = true;
		
	return (handled);
}



/***********************************************************************
 *
 * FUNCTION:    ApplicationHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and sets the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event was handled and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/1/95	Initial Revision
 *
 ***********************************************************************/
static Boolean ApplicationHandleEvent (EventPtr event)
{
	UInt16 formId;
	FormPtr frm;

	if (event->eType == frmLoadEvent)
		{
		// Load the form resource.
		formId = event->data.frmLoad.formID;
		frm = FrmInitForm (formId);
		FrmSetActiveForm (frm);		
		
		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
			{
			case BoardView:
				FrmSetEventHandler (frm, BoardViewHandleEvent);
				break;
		
			case PreferencesDialog:
				FrmSetEventHandler (frm, PreferencesDialogHandleEvent);
				break;
		
			}
		return (true);
		}
	return (false);
}


/***********************************************************************
 *
 * FUNCTION:    EventLoop
 *
 * DESCRIPTION: This routine is the event loop for the aplication.  
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	11/1/95	Initial Revision
 *			CSS	06/22/99	Standardized keyDownEvent handling
 *								(TxtCharIsHardKey, commandKeyMask, etc.)
 *
 ***********************************************************************/
static void EventLoop (void)
{
	UInt16 error;
	EventType event;

	do
		{
		// Wait until the next game period.
		EvtGetEvent (&event, TimeUntillNextPeriod());
		
		
		// Detect exiting the game's window.  This must be checked for.  At this
		// point there probably exists another window which may cover part of
		// the BoardView window.  Suppress drawing.  Otherwise drawing may draw
		// to part of the window covered by the new window.
		if (event.eType == winExitEvent)
			{
			if (event.data.winExit.exitWindow == (WinHandle) FrmGetFormPtr(BoardView))
				{
				GameStatus.paused = true;
				GameStatus.pausedTime = TimGetTicks();
				}
			}

		// Detect entering the game's window.  Resume drawing to our window.
		else if (event.eType == winEnterEvent)
			{
			if (event.data.winEnter.enterWindow == (WinHandle) FrmGetFormPtr(BoardView) &&
				event.data.winEnter.enterWindow == (WinHandle) FrmGetFirstForm())
				{
				// Sometimes we can enter the game's window without knowing it was 
				// ever left.  In that case the pause time will not have been recorded.
				// Set the current period back to it's beginning
				if (!GameStatus.paused)
					{
					GameStatus.nextPeriodTime = TimGetTicks() + GameStatus.periodLength +
						pauseLengthBeforeResumingInterruptedGame;
					}
				else
					{
					// Unpause the game.  Account for time lost during pause
					GameStatus.paused = false;
					GameStatus.nextPeriodTime += (TimGetTicks() - GameStatus.pausedTime) +
						pauseLengthBeforeResumingInterruptedGame;
					
					// Fixup the time spent playing the game by changing the startTime.
					GameStatus.startTime += (TimGetTicks() - GameStatus.pausedTime);
					}
				}
			}

		// If it's time, go to the next time period
		else if (TimeUntillNextPeriod() == 0)
			{
			GameStateDrawChanges();
			GameStateAdvance();
			GameStateElapse();
			GamePlaySounds();
			}

		// Intercept the hard keys to prevent them from switching apps
		if	(	(event.eType == keyDownEvent)
			&&	(TxtCharIsHardKey(event.data.keyDown.modifiers, event.data.keyDown.chr))
			&&	(event.data.keyDown.chr >= vchrHard1)
			&&	(event.data.keyDown.chr <= vchrHard4)
			&&	(GameStatus.status != checkHighScores)
			&& (!(event.data.keyDown.modifiers & poweredOnKeyMask)))
			{
			continue;
			}
		
		
		if (! SysHandleEvent (&event))
		
			if (! MenuHandleEvent (0, &event, &error))
			
				if (! ApplicationHandleEvent (&event))
	
					FrmDispatchEvent (&event); 
		
		}
	while (event.eType != appStopEvent);
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/22/96	Initial Revision
 *			CS		11/14/00	Removed extraneous call to PrefGetPreferences.
 *
 ***********************************************************************/
 
UInt32 PilotMain(UInt16 cmd, void * UNUSED_PARAM(cmdPBP), UInt16 launchFlags)
{
	UInt16 error;


	error = RomVersionCompatible (version30, launchFlags);
	if (error) return (error);


	if (cmd == sysAppLaunchCmdNormalLaunch)
		{
		error = StartApplication ();
	
		FrmGotoForm (BoardView);
		
		if (! error)
			EventLoop ();
	
		StopApplication ();
		}
	
	return 0;
}
