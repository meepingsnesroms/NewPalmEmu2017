/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: SubHunt.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *	  This is the SubHunt Book application's main module.  This module
 *   starts the application, dispatches events, and stops
 *   the application.
 *
 * This code is derived from the HardBall code.  It reuses the same
 * techniques shown by the HardBall code:
 *
 *		1) The timing of the game.  Waiting a constant period and then
 *			drawing followed by updating the game state.
 *
 *		2) The handling of windows appearing above the game window.
 *
 *		3) The handling of the hard buttons.wincreateoffw
 *
 *		4) The conversion of PICT resources (bitmaps) into window buffers
 *			for improved speed and to enable the use of masks (screen OR/ANDNOT)
 *
 *			Note that there is a patent covering the use of xoring an image in
 *			a buffer to the screen.  If you decide you wish to do this you
 *			reach an agreement with the patent holder who typically requests
 *			two percent of the product's revenue!  This is yet another good
 *			example of why patents shouldn't be allowed for software.  It's too
 *			easy to write a piece of code and discover that someone patented it's
 *			concept.  The patent mentioned expires in 1997.
 *
 *			SubHunt is XOR free!
 *
 *		5) The sound code (priorities, different durations).
 *
 *		6) Saving the game to state while switching to another app and successfully
 *			restoring.
 *
 *		7) High score mechanism.
 *
 *
 * To these are added the following:
 *
 *		8) Different speeds of motion for objects by having objects wait
 *			an amount turns in between each move.
 *
 *
 *
 * Things to change
 *
 * 1) Possibly add more sub types.  It's tough coming up with interesting
 *		subs which don't upset the game play and balance and which don't
 *		slow down the code too much.
 *
 *
 * !!! Before using this code for your game, check out the code for Rocks,
 *     which demonstrates techniques like double buffering for more
 *		 sophisticated animation and fractional coordinates for smoother
 *		 movement.  Rocks will eventually appear at our web site.
 *
 *
 *
 * Other things
 *
 * Armed with these code examples, I would love to see people develope
 * some other games, especially some of the classic ones like space
 * invaders, galaxian, phoenix, and so on.  Let's talk about how to
 * do some of the simpler ones:
 *
 * Space Invaders style
 *
 * This can be written similer to SubHunt.  The ship gets moved down to
 * the bottom and fires up.  Instead of an array of subs there is a two
 * dimensional array of aliens.  There should be an extent box indicating
 * which aliens in the grid are still alive.  Extra code will need to be
 * added for the bonus alien which flies across the top.  A good scheme
 * for the bunkers at the bottom will be needed.  The issue is I bet alien
 * shots traveled through the bunkers until they hit a screen pixel and
 * then they removed it and a few around.  On the Pilot, the screen can
 * be overwritten (alarms, low battery) or the app can be exited.  The
 * bunkers should look the same after these events.
 *
 * My first crack at the structure would be:
 *
 *	typedef struct {
 *		UInt8 x;			// possibly not needed
 *		UInt8 y;			// possibly not needed
 *		UInt8 type;
 *		Boolean alive;
 *		} AlienType;
 *
 *	typedef struct {
 *		RectangleType bounds;			// fleet bounds on screen
 *		AlienType alien[fleetHeight][fleetWidth];
 *		RectAbsType aliensAlive;		// fleet bounds in alien units
 *		UInt8 aliensAliveInColumn[fleetWidth];
 *		} FleetType;
 *
 *
 * Galaxian style
 *
 * Internally, this game is like space invaders but with extra aliens
 * dropping down.  There needs to be a fleet.  An alien needs to know
 * it's position in the fleet so after it leaves it knows where to
 * return to.  Besides the fleet, there needs to be a list of aliens
 * dropping down.  Aliens should be able to form a formation as they
 * fall so they will either need to keep their position relative to
 * a specific alien (who might die) or refer to a formation structure
 * somewhere.  This alien list could be similar to the falling depth
 * charges in SubHunt, with aliens ordered by depth.  The some fancier
 * games like Galaga had their aliens follow each other in a row in
 * paths all over the screen.  Clearly they didn't depth order their
 * list.   They also had multiple chains of aliens onscreen at the same
 * time.  Interesting!  Lastly, the aliens tend to fly over each other.
 * To MemHandle this cleanly might mean using the double buffering code
 * from Rocks.
 *
 *****************************************************************************/

#include <PalmOS.h>
#include	<DLServer.h>			//	Needed for user name

#include <PalmUtils.h>

#include "SubHuntRsc.h"

/***********************************************************************
 *
 *	Entry Points
 *
 ***********************************************************************/

#define appFileCreator			'subh'
#define appPrefID					0
#define appSavedGameID			0
#define appPrefVersion			2
#define appSavedGameVersion	2

#define version30					0x03000000

/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/

#define firstLevelPlayed			0

// List of key bindings
#define moveLeftKey			keyBitHard1		// polled every game period
#define dropLeftKey			keyBitHard2		// polled every game period
#define moveRightKey			keyBitHard4		// polled every game period
#define dropRightKey			keyBitHard3		// polled every game period
#define keysAllowedMask		(moveLeftKey | dropLeftKey | moveRightKey | dropRightKey)
#define releaseBallChr		vchrPageUp
#define restartGameChar		vchrPageDown

// List of bitmaps
#define OverlayBmp							1000
#define shipBitmap							0
#define shipDamagedBitmap					1
#define shipAboutToSinkBitmap				2
#define subHeadingRightBitmap				3
#define subHeadingLeftBitmap				4
#define verneSubHeadingRightBitmap		5
#define verneSubHeadingLeftBitmap		6
#define squidHeadingRightBitmap			7
#define squidHeadingLeftBitmap			8
#define whaleHeadingRightBitmap			9
#define whaleHeadingLeftBitmap			10
#define chargeBitmap							11
#define mineBitmap							12
#define fastMineBitmap						13
#define magneticMineBitmap					14
#define splashBitmap							15
#define explosionBitmap						16
#define explosionMask						17
#define waterLineBitmap						18
#define bitmapTypeCount						19

#define firstShipBitmap				shipBitmap
#define lastShipBitmap				shipAboutToSinkBitmap
#define firstChargeBitmap			chargeBitmap
#define firstMineBitmap				mineBitmap
#define firstSubBitmap				subHeadingRightBitmap
#define firstExplosionBitmap		explosionBitmap

#define normalShip					0
#define normalSub						0
#define verneSub						1
#define squidSub						2
#define whaleSub						3
#define normalCharge					0
#define normalMine					1
#define fastMine						2
#define magneticMine					3
#define splashMine					4		// draw self as a column of water
#define explosionMine				5		// draw self as a round explosion

#define gameWidth						160
#define gameHeight					(160 - 20)
#define waterLine						11
#define waterThickness				3
#define subAboveWaterPosition		(waterLine - 2)
#define subSubmergedPosition 		(waterLine + waterThickness + spaceBetweenWaterAndSubs)

// Board settings
#define overlayTopLeftX				0
#define overlayTopLeftY				15
#define boardWidth					gameWidth
#define boardHeight					gameHeight

#define overlayBmpXOffset			0
#define overlayBmpYOffset			0

// Graphic bounds
#define explosionWidth				12
#define explosionHeight				12
#define splashWidth					5
#define splashHeight					10


// Title bar displays
#define chargeLeftGaugeX			53				// left bounds of left depth charges
#define chargeLeftGaugeY			6
#define chargeRightGaugeX			119			// right bounds of right depth charges
#define chargeRightGaugeY			6
#define chargeGaugeSeparator		2
#define chargesDisplayable			5

// Score position
#define scoreX							74
#define scoreY							2
#define maxScoreDigits				5
#define scoreCharWidth				5			// width of numbers in the bold font
#define scoreWidth					(maxScoreDigits * scoreCharWidth - 1)
#define scoreFont						boldFont

// Level position
#define levelX							148
#define levelY							2
#define maxlevelDigits				2
#define levelCharWidth				5			// width of numbers in the bold font
#define levelWidth					(maxlevelDigits * levelCharWidth - 1)
#define levelFont						boldFont


// Depth charge settings
#define chargeWidth					2
#define chargeHeight					2
#define chargesMax					(chargeCapacity * 2 * 2)
#define rightSide						0			// charges dropped from the right side
#define leftSide						1			// charges dropped from the left side
#define sideCount						2			// count of places which can drop charges
#define chargeCapacity				5			// charges each launcher can store
#define periodsBetweenChargeDrops	20
#define periodsBetweenChargeReloads	70		// 80
#define periodsSpentExploding			10

// Ship settings
#define shipWidth						36
#define shipHeight					10
#define spaceRequiredToDropCharges	5
#define shipMovement					2				// faster than a charge
#define shipHitLimit					3
#define spaceUntilDepthChargeLauncherSubmerged	5
#define periodsToSinkOneNotch			40
#define shipCompletelySunkAmount		shipHeight


// Sub settings
#define normalSubWidth				33
#define normalSubHeight				12
#define verneSubWidth				41
#define verneSubHeight				12
#define squidSubWidth				33
#define squidSubHeight				11
#define whaleSubWidth				33
#define whaleSubHeight				9
#define subMovement					2				// faster than a charge
#define subVerticalSpacing			13
#define subsMax						9
#define chanceForNewSub				4				// percent per period
#define spaceBetweenWaterAndSubs	7
#define periodsSpentSinking		(periodsSpentExploding + 8)
#define subScoreDigits				3				// <= 999
#define subScoreYOffset				10
#define subLeftScoreXOffset			6				// use even offsets to avoid irregular scaled
#define subRightScoreXOffset		26				//	offsets when drawing to QVGA display
#define firstSquidLevel				5
#define firstVerneLevel				8				// 8 + 1 = 9
#define pickSubSpeed 				(RandN(10) + 1)		// 1 - 10
#define pickVerneSubSpeed			(RandN(2) + 9)			// 9 - 10
#define pickSquidSubSpeed			(RandN(3) + 4)			// 4 - 6
#define pickWhaleSubSpeed			(RandN(3) + 4)			// 4 - 6
#define changeDirectionPercent	75
#define shipLevel						-1
#define squidTouchAmount			3				// amount of touching needed to choke ship
#define periodsForSquidToChoke	60
#define verneSubScore				150
#define squidSubScore				100
#define whaleSubScore				75

// Mine settings
#define normalMineWidth				3
#define normalMineHeight			3
#define fastMineWidth				3
#define fastMineHeight				3
#define magneticMineWidth			4
#define magneticMineHeight			4
#define minesMax						40
#define mineLimitForVerneSubs		minesMax
#define mineLimitForSubs			(mineLimitForVerneSubs - 10)
#define maxLayMinePerThousand		250			// out of 1000 (25%)
#define firstMagneticMineLevel	14
#define magneticMineChance			10				// 10%
#define magneticMineFollowChance	66				// 66%


// This controls how often an object is moved.  An object moving at maxSpeed moves
// once every game period.  An object moves every (maxSpeed - speed + 1) periods.
#define maxSpeed					10
#define chargeSpeed				9
#define mineSpeed					4
#define fastMineSpeed			7
#define animalFleeingSpeed		9

#if EMULATION_LEVEL != EMULATION_NONE
#define advanceTimeInterval	3				// the emulator is slow, run as fast as possible
#else
#define advanceTimeInterval	4
#endif

// Various time intervals
#define levelOverTimeInterval	(125)			// (sysTicksPerSecond / 4 * 5)
#define gameOverTimeInterval	(2 * 60)			// time to pause after game over and before high scores
#define pauseLengthBeforeResumingSavedGame			(3 * sysTicksPerSecond)
#define pauseLengthBeforeResumingInterruptedGame	(2 * sysTicksPerSecond)


// High Scores settings
#define highScoreFont				stdFont
#define firstHighScoreY				28
#define highScoreHeight				12
#define highScoreNameColumnX		17
#define highScoreScoreColumnX		119		// Right aligned
#define highScoreLevelColumnX		149		// Right aligned
#define nameLengthMax	15
#define highScoreMax		9


// Report settings
#define clearMessageX		30
#define clearMessageY		80
#define reportFont			largeFont


// Preferences UI settings
#define startLevelsSelectable			3
#define defaultStartLevelItem			0


// List of sounds possible
typedef enum
	{
	noSound,
	releaseCharge,
	chargeSplash,
	explosion,
	surfaceExplosion,
	shipHit,
	shipSinking,
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
	waitingForSubs, 		// advance and draw the game state (allows ship to move)
	SubsInMotion, 	 		// advance and draw the game state
	levelOver, 	 			// pause, start new level, and go to waitingForBall
	gameOver,				// don't draw or change the game state, pause before high score check
	checkHighScores		// check for high score, get name if high score.
	};

typedef struct
	{
	AbsRectType			sides;
	Boolean				usable;
	Boolean				changed;
	Boolean				sinking;
	Boolean				beingAttacked;
	UInt8					type;
	UInt8					heading;
	UInt8					speed;
	Int8					desiredSpeed;		// different if the sub wants to change speed
													// a negative speed means change direction.
	Int8					desiredLevel;		// different if the sub wants to change levels
	UInt8					score;
	Int8					periodsUntilMove;
	char					scoreText[subScoreDigits + 1];
	UInt8					scoreDigits;
	} ObjectType;

typedef struct
	{
	AbsRectType			sides;
	Boolean				usable;
	Boolean				changed;
	Boolean				exploding;			// The duration is set by periodsUntilMove
	UInt8					type;
	Int8					periodsUntilMove;
	} ExplosiveType;

typedef struct
	{
	Int32						score;
	UInt8						chargeCount;		// charges in the water sinking
	UInt8						mineCount;			// mines in the water rising
	ObjectType				ship;
	ObjectType				sub[subsMax];
	ExplosiveType			charge[chargesMax];
	ExplosiveType			mine[minesMax];
	} WorldState;


typedef struct {
	enum gameProgress		status;
	UInt32					nextPeriodTime;	// time when next period occurs
	Boolean					paused;				// indicates that time should not pass
	UInt32					pausedTime;			// Used to
	UInt32					startTime;			// Time since starting HardBall
	UInt32					accumulatedTime;	// Total time spent by player playing HardBall
	UInt8						subsThisLevel;		// subs to send this level
	UInt8						subsRemaining;		// subs remaining this level
	UInt8						subUnderWaterCount;	// all subs unde water must leave before level over
	UInt8						subsDestroyedThisLevel;		// subs sunk this level
	UInt8						shipHitCount;		// number of times the ship is struck by a mine
	UInt8						shipSunkAmount;	// amount the ship has sunk
	UInt8						level;				// controls the subs
	Int16						periodsTillNextLevel;	// time between levels
	WorldState				last;					// world last drawn
	WorldState				next;					// world to be drawn
	UInt8						chargesAvailable[sideCount];	// charges available to drop
	UInt8						periodsTillNextDrop[sideCount];
	UInt8						periodsTillNextReload[sideCount];
	Boolean					moveShipLeft;		// ship moved and flag cleared during GameStateElapse
	Boolean					moveShipRight;		// ship moved and flag cleared during GameStateElapse
	SoundType				soundToMake;		// one sound can be made per game period
	Int8						soundPeriodsRemaining;	// times to repeat the sound
	Boolean					waterLineDirty;	// true if the water line was overwritten
	Boolean					lowestHighScorePassed;	// User beat the lowest high score
	Boolean					highestHighScorePassed;	// User beat the highest high score
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
	UInt32						accumulatedTime;	// Total time spent by player playing HardBall
	} SubHuntPreferenceType;



/***********************************************************************
 *
 *	Global variables
 *
 ***********************************************************************/

static GameStatusType		GameStatus;
static MemHandle					ObjectBitmapHandles[bitmapTypeCount];
static BitmapPtr				ObjectBitmapPtr[bitmapTypeCount];
static WinHandle				ObjectWindowHandles[bitmapTypeCount];

static enum gameProgress	SavedGameStatus;


static UInt16 SoundAmp;		// default sound amplitude

static SoundInfo  Sound[soundTypeCount] =
	{
		{0,	0,		0, 	0},			// no sound
		{0,	1,		700,	30},
		{0,	1,		250,	30},
		{40,	4,		180,	30},			// explosion
		{30,	3,		140,	40},			// surface explosion
		{80,	12,	550,	50},			// Ship hit
		{60,	8,		760,	60},			// Ship sinking
		{90,	8,		2500,	50},			// high score passed
	};

// The original values for key rates.
KeyRateType KeyRate;

// Mappings for the start level UI
UInt8 StartLevelMappings[startLevelsSelectable] =
	{
	0, firstSquidLevel, firstMagneticMineLevel
	};

// Used by the Preference Dialog
UInt8 NewStartLevel;

// The following global variable are saved to a state file.

// Scores
SubHuntPreferenceType		Prefs;



/***********************************************************************
 *
 *	Macros
 *
 ***********************************************************************/

#define noItemSelection			-1



#define GetShipBitmap(t, damage)		(min((t) + firstShipBitmap + damage, lastShipBitmap))
#define GetSubBitmap(t, side)	((t) * sideCount + firstSubBitmap + (side))
#define GetChargeBitmap(t)		((t) + firstChargeBitmap)
#define GetMineBitmap(t)		((t) + firstMineBitmap - normalMine)

#define subLaysMines(t)			((t) <= verneSub)
#define subDisplaysScore(t)	((t) <= verneSub)

#define oppositeHeading(h)		(h == leftSide ? rightSide : leftSide)
#define subAttackingShip(s)	((s)->sides.top < subSubmergedPosition)


#define RandN(N)	((((Int32) SysRandom (0)) * N) / ((Int32) sysRandomMax + 1))


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/
static void GameStart ();
static void HighScoresAddScore (const Char * name, Int32 score, Int16 level,
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
 * RETURNED:     nothing
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
 *
 ***********************************************************************/
static UInt16 StartApplication (void)
{
	int i;
	WinHandle oldDrawWinH;
	UInt16 error;
	UInt16 prefsSize;
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

		// It is actually faster and more versatile to store the graphics
		// as window images.  It is faster because WinDrawBitmap constructs a
		// window from the bitmap on the fly before drawing.  It is more
		// versatile because when the window is copied to the screen a
		// screen copy mode like scrCopyNot can be used.  This makes
		// images masks possible.
		// We can do this as long as their is enough memory free in the dynamic
		// ram.  We don't do this to large images.
		if (i == 999)			// don't skip any bitmaps we use
			{
			ObjectWindowHandles[i] = 0;
			}
		else
			{
			BmpGetDimensions(ObjectBitmapPtr[i], &bitmapWidth, &bitmapHeight, NULL);

			ObjectWindowHandles[i] = WinCreateOffscreenWindow(
				bitmapWidth, bitmapHeight,
				screenFormat, &error);
			ErrFatalDisplayIf(error, "Error loading images");
			WinSetDrawWindow(ObjectWindowHandles[i]);
			WinDrawBitmap(ObjectBitmapPtr[i], 0, 0);
			}

		}
	WinSetDrawWindow(oldDrawWinH);



	// Restore the app's preferences.
	prefsSize = sizeof (SubHuntPreferenceType);
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
		HighScoresAddScore ("Ain", 	23456, 20, true);
		HighScoresAddScore ("Shelldon", 	20268, 19, true);
		HighScoresAddScore ("the Jode", 	19193, 18, true);
		HighScoresAddScore ("Rocket Boy", 	12430, 14, true);
		HighScoresAddScore ("Mr. P", 42752, 25, true);

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
		}
	else
		{
		if (GameStatus.status != checkHighScores)
			{
			SavedGameStatus = GameStatus.status;
			GameStatus.status = gameResuming;		// don't draw yet!
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

	// Update the time accounting.
	Prefs.accumulatedTime += (TimGetTicks() - GameStatus.startTime);

	// If we are saving a game resuming (it hasn't started playing yet)
	// then preserve the game status.
	if (GameStatus.status == gameResuming)
		{
		GameStatus.status = SavedGameStatus;
		}

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
	KeySetMask(	~(moveLeftKey | dropLeftKey | dropRightKey | moveRightKey) );


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
	KeySetMask(keyBitsAll);


	return;

	// Also set the key repeat rate low to avoid constantly checking them.
	KeyRates(true, &KeyRate.initDelay, &KeyRate.period, &KeyRate.doubleTapDelay,
		&KeyRate.queueAhead);
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
	RectangleType srcR;
	RectangleType windowBounds;

	ErrFatalDisplayIf (ObjectWindowHandles[bitmapNumber] == 0, "Unhandled object image");
	// Copy the entire source window.
	WinGetBounds(ObjectWindowHandles[bitmapNumber], &windowBounds);
	MemMove (&srcR, &windowBounds, sizeof(RectangleType));

	// Copy the source window (contains the image to draw) to the draw window.
	WinCopyRectangle(ObjectWindowHandles[bitmapNumber], 0, &srcR, x, y, mode);
}


/***********************************************************************
 *
 * FUNCTION:     GameRequestSound
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
}


/***********************************************************************
 *
 * FUNCTION:     ShipAdd
 *
 * DESCRIPTION:  Place a new ship at the center of the screen
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/12/96	Initial Revision
 *
 ***********************************************************************/

static void ShipAdd ()
{
	GameStatus.next.ship.changed = true;
	GameStatus.next.ship.usable = true;
	GameStatus.next.ship.sinking = false;
	GameStatus.shipSunkAmount = 0;
	GameStatus.next.ship.sides.left = (gameWidth - shipWidth) / 2;
	GameStatus.next.ship.sides.top = 1;
	GameStatus.next.ship.sides.right = GameStatus.next.ship.sides.left + shipWidth;
	GameStatus.next.ship.sides.bottom = GameStatus.next.ship.sides.top + shipHeight;


	GameStatus.chargesAvailable[leftSide] = chargeCapacity;
	GameStatus.periodsTillNextDrop[leftSide] = 0;
	GameStatus.periodsTillNextReload[leftSide] = periodsBetweenChargeReloads;

	GameStatus.chargesAvailable[rightSide] = chargeCapacity;
	GameStatus.periodsTillNextDrop[rightSide] = 0;
	GameStatus.periodsTillNextReload[rightSide] = periodsBetweenChargeReloads;
}


/***********************************************************************
 *
 * FUNCTION:     ShipHit
 *
 * DESCRIPTION:  show the effects of the ship being hit
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/8/96	Initial Revision
 *
 ***********************************************************************/

static void ShipHit()
{
	GameStatus.shipHitCount++;
	GameStatus.next.ship.changed = true;		// redraw with a more damaged appearance
	if (GameStatus.shipHitCount >= shipHitLimit)
		{
		// The ship has struck too many times.  Sink it.
		GameStatus.shipSunkAmount++;
		GameStatus.next.ship.periodsUntilMove = 0;
		}

	GameRequestSound (shipHit);
}


/***********************************************************************
 *
 * FUNCTION:     DepthChargeAdd
 *
 * DESCRIPTION:  Add a charge to play
 *
 * PARAMETERS:   type - type of charge
 *					  side - the ship side over which the charge is dropped
 *
 * RETURNED:     true if a depth charge is sent
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/12/96	Initial Revision
 *
 ***********************************************************************/

static Boolean DepthChargeAdd (UInt8 type, UInt8 side)
{
	int chargeNum;
	ExplosiveType *charge;


	// Remember that new charges are ordered by depth.  A new charge is
	// therefore added at the end.
	if (GameStatus.next.chargeCount >= chargesMax)
		return false;
	chargeNum = GameStatus.next.chargeCount++;
	charge = &GameStatus.next.charge[chargeNum];


	// Set the charge up to draw
	charge->usable = true;
	charge->changed = true;
	charge->exploding = false;
	charge->type = type;

	// Set the bounds of the charge
	if (side == leftSide)
		charge->sides.left = GameStatus.next.ship.sides.left -
			spaceRequiredToDropCharges;
	else
		charge->sides.left = GameStatus.next.ship.sides.right +
			spaceRequiredToDropCharges - chargeWidth;

	charge->sides.top = GameStatus.next.ship.sides.bottom;
	charge->sides.right = charge->sides.left +
		chargeWidth;
	charge->sides.bottom = charge->sides.top +
		chargeHeight;

	charge->periodsUntilMove = 0;		// move right away


	// Now deduct the depth charge from the ship.
	GameStatus.chargesAvailable[side]--;
	GameStatus.periodsTillNextDrop[side] = periodsBetweenChargeDrops;


	return true;
}


/***********************************************************************
 *
 * FUNCTION:     DepthChargeExplode
 *
 * DESCRIPTION:  Have the depth charge become an explosion.
 * remain.
 *
 * PARAMETERS:   chargeNumber - which charge to explode
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/

static void DepthChargeExplode (Int16 chargeNumber)
{
	ExplosiveType *charge;


	charge = &GameStatus.next.charge[chargeNumber];


	charge->sides.left += (chargeWidth - explosionWidth) / 2;
	charge->sides.top += (chargeHeight - explosionHeight) / 2;
	charge->sides.right = charge->sides.left + explosionWidth;
	charge->sides.bottom = charge->sides.top + explosionHeight;


	charge->exploding = true;
	charge->periodsUntilMove = periodsSpentExploding;
	charge->changed = true;

	GameRequestSound (explosion);
}


/***********************************************************************
 *
 * FUNCTION:     DepthChargeRemove
 *
 * DESCRIPTION:  Remove a charge from play.
 * remain.
 *
 * PARAMETERS:   chargeNumber - which charge to remove
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *
 ***********************************************************************/

static void DepthChargeRemove (Int16 chargeNumber)
{
	ErrFatalDisplayIf(chargeNumber >= GameStatus.next.chargeCount,
		"Removing a charge that doesn't exist");


	// Maintain the charges ordered in depth ordered by shrinking the list
	// This only needs to be done if the item isn't the last one in the list.
	if (GameStatus.next.chargeCount - chargeNumber > 1)
		{
		MemMove(&GameStatus.next.charge[chargeNumber],
			&GameStatus.next.charge[chargeNumber + 1],
			(GameStatus.next.chargeCount - 1 - chargeNumber) * sizeof (ExplosiveType));

		MemMove(&GameStatus.last.charge[chargeNumber],
			&GameStatus.last.charge[chargeNumber + 1],
			(GameStatus.last.chargeCount - 1 - chargeNumber) * sizeof (ExplosiveType));
		}

	// Wipe over the last charge since it was copied.
	GameStatus.next.charge[GameStatus.next.chargeCount - 1].usable = false;
	GameStatus.next.charge[GameStatus.next.chargeCount - 1].changed = false;

	GameStatus.last.charge[GameStatus.next.chargeCount - 1].usable = false;
	GameStatus.last.charge[GameStatus.next.chargeCount - 1].changed = false;

	GameStatus.next.chargeCount--;
}


/***********************************************************************
 *
 * FUNCTION:     MineAdd
 *
 * DESCRIPTION:  Add a mine to play
 *
 * PARAMETERS:   mineX, mineY - where to place the mine
 *
 * RETURNED:     true if a mine is placed
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/5/96	Initial Revision
 *
 ***********************************************************************/

static Boolean MineAdd (UInt8 mineType, Int16 mineX, Int16 mineY, UInt8 subType)
{
	int mineNum;
	int mineWidth;
	int mineHeight;
	ExplosiveType *mine;


	// determine the width and height of the mine
	switch (mineType)
		{
		case normalMine:
			mineWidth = normalMineWidth;
			mineHeight = normalMineHeight;
			break;

		case fastMine:
			mineWidth = fastMineWidth;
			mineHeight = fastMineHeight;
			break;

		case magneticMine:
			mineWidth = magneticMineWidth;
			mineHeight = magneticMineHeight;
			break;
		}


	// Remember that new mines are ordered by depth.  A new mine is
	// therefore added at the end.
	if (GameStatus.next.mineCount >= (subType == verneSub ?
			mineLimitForVerneSubs : mineLimitForSubs) ||
		(mineX + mineWidth) < 0 ||
		mineX > boardWidth)
		return false;


	// Find out where in the list to place the mine
	for (mineNum = GameStatus.next.mineCount - 1; mineNum >= 0; mineNum--)
		{
		mine = &GameStatus.next.mine[mineNum];

		if (mine->sides.top <= mineY)
			{
			// Now insure the new mine doesn't overlap the this mine
			// It is guessed that overlapping mines leave greebles.
			if (mineY < mine->sides.bottom &&
				mineX >= mine->sides.left &&
				mineX < mine->sides.right)
				return false;

			// place after this mine since this mine is shallower
			mineNum++;
			mine = &GameStatus.next.mine[mineNum];

			// Now insure the new mine doesn't overlap the following mine.  Check if
			// either the top or bottom of the new mine overlaps the existing mine and
			// that either the left or right side overlap too.
			if (((mineY >= mine->sides.top &&
				   mineY <= mine->sides.bottom) ||
				  ((mineY + mineHeight - 1) >= mine->sides.top &&
				   (mineY + mineHeight - 1) <= mine->sides.bottom)) &&
				 ((mineX >= mine->sides.left &&
				   mineX < mine->sides.right) ||
				  ((mineX + mineWidth - 1) >= mine->sides.left &&
					(mineX + mineWidth - 1) < mine->sides.right)))
				return false;

			break;
			}
		}


	// If there are no mines use the first position
	if (mineNum < 0)
		{
		mineNum = 0;
		mine = &GameStatus.next.mine[0];
		}


	// If there are other mines and we are inserting the mine before the last place
	// move some of the mines to make a slot for the mine to be inserted in.
	if (GameStatus.next.mineCount > 0 &&
		GameStatus.next.mineCount > mineNum)

		{
		// There are some mines.  Make room for the mine so we can insert it.
		MemMove(mine + 1,
			mine,
			(GameStatus.next.mineCount - mineNum) * sizeof (ExplosiveType));

		// Perform the same move on the last mines so the history is correct.
		MemMove(&GameStatus.last.mine[mineNum + 1],
			&GameStatus.last.mine[mineNum],
			(GameStatus.last.mineCount - mineNum) * sizeof (ExplosiveType));
		}

	// Set the mine up to draw
	mine->usable = true;
	mine->changed = true;
	mine->exploding = false;
	mine->type = mineType;


	// Set the bounds of the mine
	mine->sides.left = mineX;

	mine->sides.top = mineY;
	mine->sides.right = mine->sides.left + mineWidth;
	mine->sides.bottom = mine->sides.top + mineHeight;

	mine->periodsUntilMove = 0;		// move right away

	GameStatus.next.mineCount++;

	return true;
}


/***********************************************************************
 *
 * FUNCTION:     MineExplode
 *
 * DESCRIPTION:  Have the mine become an explosion.  Mines explode only
 * on the surface with a splash.  When a mine is struck by a charge, the
 * mine is removed and the charge handles the explosion.
 * remain.
 *
 * PARAMETERS:   mineNumber - which mine to explode
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/

static void MineExplode (Int16 mineNumber)
{
	ExplosiveType *mine;


	mine = &GameStatus.next.mine[mineNumber];


	mine->exploding = true;
	mine->periodsUntilMove = periodsSpentExploding;
	mine->changed = true;


	// Does the mine explode under the ship?
	if (mine->sides.left >= GameStatus.next.ship.sides.left &&
		mine->sides.right <= GameStatus.next.ship.sides.right)
		{
		// Appear as an explosion above water
		mine->sides.left += (mine->sides.right - mine->sides.left - explosionWidth) / 2;
		mine->sides.top -= explosionHeight;
		mine->sides.right = mine->sides.left + explosionWidth;
		mine->sides.bottom = mine->sides.top + explosionHeight;
		mine->type = explosionMine;


		ShipHit();
		}
	else
		{
		// Appear as a splash above water
		mine->sides.left += (mine->sides.right - mine->sides.left - splashWidth) / 2;
		mine->sides.top -= splashHeight;
		mine->sides.right = mine->sides.left +
			splashWidth;
		mine->sides.bottom = mine->sides.top +
			splashHeight;
		mine->type = splashMine;


		GameRequestSound (surfaceExplosion);
		}

}


/***********************************************************************
 *
 * FUNCTION:     MineRemove
 *
 * DESCRIPTION:  Remove a mine from play.
 * remain.
 *
 * PARAMETERS:   mineNumber - which mine to remove
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	1/30/96	Initial Revision
 *
 ***********************************************************************/

static void MineRemove (Int16 mineNumber)
{
	ErrFatalDisplayIf(mineNumber >= GameStatus.next.mineCount,
		"Removing a mine that doesn't exist");


	// Maintain the mines ordered in depth ordered by shrinking the list
	// This only needs to be done if the item isn't the last one in the list.
	if (GameStatus.next.mineCount - mineNumber > 1)
		{
		MemMove(&GameStatus.next.mine[mineNumber],
			&GameStatus.next.mine[mineNumber + 1],
			(GameStatus.next.mineCount - 1 - mineNumber) * sizeof (ExplosiveType));

		MemMove(&GameStatus.last.mine[mineNumber],
			&GameStatus.last.mine[mineNumber + 1],
			(GameStatus.last.mineCount - 1 - mineNumber) * sizeof (ExplosiveType));
		}

	// Wipe over the last mine since it was copied.
	GameStatus.next.mine[GameStatus.next.mineCount - 1].usable = false;
	GameStatus.next.mine[GameStatus.next.mineCount - 1].changed = false;

	GameStatus.last.mine[GameStatus.next.mineCount - 1].usable = false;
	GameStatus.last.mine[GameStatus.next.mineCount - 1].changed = false;

	GameStatus.next.mineCount--;
}


/***********************************************************************
 *
 * FUNCTION:     SubAdd
 *
 * DESCRIPTION:  Add a sub to play
 *
 * PARAMETERS:   type - type of sub
 *					  side - the ship side over which the sub is dropped
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/12/96	Initial Revision
 *
 ***********************************************************************/

static void SubAdd (UInt8 heading)
{
	int subNum;
	int subWidth;
	int subHeight;
	UInt8 type;
	ObjectType *sub;


	// Remember that new subs are ordered by depth.  A new sub is
	// therefore added at the end.
	subNum = RandN(subsMax);
	sub = &GameStatus.next.sub[subNum];

	if (sub->usable ||
		sub->changed)
		return;						// the sub is used or hasn't completely erased itself

	// Do not use a sub if the one below is moving in!  Non normal subs do this.
	if (subNum == subsMax - 1 ||
		(GameStatus.next.sub[subNum + 1].desiredLevel == subNum &&
		GameStatus.next.sub[subNum + 1].usable))
		return;

	if (GameStatus.subsRemaining == 0)
		return;						// enough subs have been sent


	GameStatus.subsRemaining--;
	GameStatus.subUnderWaterCount++;


	type = normalSub;

	// maybe add a squid instead.
	if (GameStatus.level >= firstSquidLevel &&
		RandN(100) < (5 + (GameStatus.level - firstSquidLevel) / 4))
		type = squidSub;

	// maybe add a verne sub instead.
	if (GameStatus.level >= firstVerneLevel &&
		RandN(100) < (3 + (GameStatus.level - firstVerneLevel) / 2))
		type = verneSub;


	// Set the sub up to draw
	sub->usable = true;
	sub->changed = true;
	sub->sinking = false;
	sub->beingAttacked = false;
	sub->type = type;


	switch (type)
		{
		case normalSub:
			subWidth = normalSubWidth;
			subHeight = normalSubHeight;
			sub->speed = pickSubSpeed;
			sub->score = (subNum + 1) *
				sub->speed;
			StrIToA(sub->scoreText, sub->score);
			sub->scoreDigits = StrLen(sub->scoreText);
			break;

		case verneSub:
			subWidth = verneSubWidth;
			subHeight = verneSubHeight;
			sub->speed = pickVerneSubSpeed;
			sub->score = verneSubScore;
			StrIToA(sub->scoreText, sub->score);
			sub->scoreDigits = StrLen(sub->scoreText);
			break;

		case squidSub:
			subWidth = squidSubWidth;
			subHeight = squidSubHeight;
			sub->speed = pickSquidSubSpeed;
			sub->score = squidSubScore;
			break;

		case whaleSub:
			subWidth = whaleSubWidth;
			subHeight = whaleSubHeight;
			sub->speed = pickWhaleSubSpeed;
			sub->score = whaleSubScore;
			break;
		}


	sub->desiredSpeed = sub->speed;
	sub->desiredLevel = subNum;

	if (heading == rightSide)
		sub->sides.left = 0 - subWidth;
	else
		sub->sides.left = boardWidth;
	sub->sides.top = subSubmergedPosition +
		subNum * subVerticalSpacing;

	sub->sides.right = sub->sides.left + subWidth;
	sub->sides.bottom = sub->sides.top + subHeight;

	sub->heading = heading;
	sub->periodsUntilMove = 0;		// appear right away

}


/***********************************************************************
 *
 * FUNCTION:     SubRemove
 *
 * DESCRIPTION:  Remove the sub.
 *
 * PARAMETERS:   chargeNumber - the charge to check
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/
static void SubRemove (Int16 subNumber)
{
	ObjectType	*sub;


	GameStatus.subUnderWaterCount--;
	sub = &GameStatus.next.sub[subNumber];

	sub->usable = false;
	sub->changed = true;
}


/***********************************************************************
 *
 * FUNCTION:     SubDestroy
 *
 * DESCRIPTION:  Explode the charge and sink the sub.  If it's a squid
 * let it flee once.
 *
 * PARAMETERS:   chargeNumber - the charge to check
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/
static void SubDestroy (Int16 chargeNumber, Int16 subNumber)
{
	ObjectType	*sub;


	sub = &GameStatus.next.sub[subNumber];

	if (sub->type >= squidSub && !sub->beingAttacked)
		{
		sub->beingAttacked = true;

		// If the sub isn't attacking the ship or sometimes even if it is,
		// have the squid flee.
		if (!subAttackingShip(sub) ||
			RandN(100) < 75)
			{
			sub->heading = oppositeHeading(sub->heading);
			sub->speed = animalFleeingSpeed;
			sub->desiredSpeed = animalFleeingSpeed;
			sub->periodsUntilMove = 0;			// flee now!

			// If it was attacking the sub have it sink back down.
			if (subAttackingShip(sub))
				sub->desiredLevel = 0;
			}
		}
	else if (!sub->sinking)
		{
		sub->sinking = true;
		sub->periodsUntilMove = periodsSpentSinking;
		IncreaseScore(sub->score);
		GameStatus.subsDestroyedThisLevel++;
		}

	DepthChargeExplode(chargeNumber);
}


/***********************************************************************
 *
 * FUNCTION:     IsSubUnderShip
 *
 * DESCRIPTION:  Returns true if the sub is under the ship
 *
 * PARAMETERS:   subNumber - the sub to check for
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	4/5/96	Initial Revision
 *
 ***********************************************************************/
static Boolean IsSubUnderShip (Int16 subNumber)
{

	// Return true if the either side of the sub overlaps the ship.
	return ((GameStatus.next.sub[subNumber].sides.left >= GameStatus.next.ship.sides.left &&
		GameStatus.next.sub[subNumber].sides.left < GameStatus.next.ship.sides.right) ||
		(GameStatus.next.sub[subNumber].sides.right < GameStatus.next.ship.sides.right &&
		GameStatus.next.sub[subNumber].sides.right >= GameStatus.next.ship.sides.left));
}


/***********************************************************************
 *
 * FUNCTION:     GameDrawChargeGauge
 *
 * DESCRIPTION:  Draw the charge gauge.  Charges remaining are drawn.  Balls
 * no longer remaining are erased.  Two gauges are present - one for each side.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/12/96	Initial Revision
 *
 ***********************************************************************/

static void GameDrawChargeGauge (void)
{
	int i;
	RectangleType bounds;
	int side;


	// Draw some of the charges remaining
	for (side = rightSide; side <= leftSide; side++)
		{
		for (i = 0; i < chargesDisplayable; i++)
			{
			// calculate the top left of where the charge belongs
			if (side == leftSide)
				{
				bounds.topLeft.x = chargeLeftGaugeX + i * (chargeWidth + chargeGaugeSeparator);
				bounds.topLeft.y = chargeLeftGaugeY;
				}
			else
				{
				bounds.topLeft.x = chargeRightGaugeX - i * (chargeWidth + chargeGaugeSeparator);
				bounds.topLeft.y = chargeLeftGaugeY;
				}


			// Now draw or erase the charge
			if (GameStatus.chargesAvailable[side] > i)
				{
				DrawObject (firstChargeBitmap, bounds.topLeft.x, bounds.topLeft.y, winPaint);
				}
			else
				{
				bounds.extent.x = chargeWidth;
				bounds.extent.y = chargeHeight;
				WinEraseRectangle(&bounds, 0);
				}
			}
		}
}


/***********************************************************************
 *
 * FUNCTION:     GameDrawScoreGauge
 *
 * DESCRIPTION:  Draw the score gauge given a score to display.
 *
 * PARAMETERS:   score - score to draw in the gauge's area
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
	Int16 scoreLength;


	currFont = FntSetFont(scoreFont);

	// Draw the score
	if (score > 0)
		StrIToA(scoreText, score);
	else
		{
		Char numSpace;
		ChrNumericSpace(&numSpace);
		// First draw spaces over a prior score to blank it out.
		MemSet(scoreText, maxScoreDigits, numSpace);			// Write numeric spaces to remove old score
		WinDrawChars (scoreText, maxScoreDigits, scoreX, scoreY);

		// Now set up to draw a score of zero.
		scoreText[0] = '0';
		scoreText[1] = '\0';
		}
	scoreLength = StrLen(scoreText);
	WinDrawChars (scoreText, scoreLength,
		scoreX + (scoreWidth - scoreCharWidth * scoreLength) / 2, 	// center the score
		scoreY);

	FntSetFont(currFont);
}


/***********************************************************************
 *
 * FUNCTION:     GameDrawLevelGauge
 *
 * DESCRIPTION:  Draw the level gauge given a level to display.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/5/96	Initial Revision
 *
 ***********************************************************************/

static void GameDrawLevelGauge (level)
{
	char levelText[maxlevelDigits + 1];
	FontID currFont;
	Int16 levelLength;


	currFont = FntSetFont(levelFont);

	// Clear the gauge if the game is new.
	if (GameStatus.next.score == 0)
		{
		Char numSpace;
		ChrNumericSpace(&numSpace);
		// First draw spaces over a prior level to blank it out.
		MemSet(levelText, maxlevelDigits, numSpace);			// Write numeric spaces to remove old level
		WinDrawChars (levelText, maxlevelDigits, levelX, levelY);
		}

	// Draw the level
	StrIToA(levelText, level);
	levelLength = StrLen(levelText);
	WinDrawChars (levelText, levelLength, levelX, levelY);

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


	// Draw a blank board
	DrawBitmap(OverlayBmp,
		overlayTopLeftX + overlayBmpXOffset,
		overlayTopLeftY + overlayBmpYOffset);

	GameStatus.waterLineDirty = false;

	// Draw the ship
	if (GameStatus.last.ship.usable)
		{
		DrawObject (GetShipBitmap(GameStatus.last.ship.type, GameStatus.shipHitCount),
			overlayTopLeftX + GameStatus.last.ship.sides.left,
			overlayTopLeftY + GameStatus.last.ship.sides.top,
			winPaint);
		}


	// Draw the subs
	for (i = subsMax - 1; i >= 0; i--)
		{
		// Draw the sub
		if (GameStatus.last.sub[i].usable)
			{
			DrawObject (GetSubBitmap(GameStatus.last.sub[i].type,
				GameStatus.last.sub[i].heading),
				overlayTopLeftX + GameStatus.last.sub[i].sides.left,
				overlayTopLeftY + GameStatus.last.sub[i].sides.top,
				(GameStatus.next.sub[i].sides.top < subSubmergedPosition) ? winOverlay : winPaint);
			}
		}


	// Draw the charges
	for (i = GameStatus.next.chargeCount - 1; i >= 0; i--)
		{
		// Draw the charge
		if (GameStatus.last.charge[i].usable)
			{
			DrawObject (GetChargeBitmap(GameStatus.last.charge[i].type),
				overlayTopLeftX + GameStatus.last.charge[i].sides.left,
				overlayTopLeftY + GameStatus.last.charge[i].sides.top,
				winPaint);
			}
		}


	// Draw the mines
	for (i = GameStatus.next.mineCount - 1; i >= 0; i--)
		{
		// Draw the mine
		if (GameStatus.last.mine[i].usable)
			{
			DrawObject (GetMineBitmap(GameStatus.last.mine[i].type),
				overlayTopLeftX + GameStatus.last.mine[i].sides.left,
				overlayTopLeftY + GameStatus.last.mine[i].sides.top,
				winOverlay);
			}
		}


	GameDrawScoreGauge (GameStatus.last.score);
	GameDrawChargeGauge();

	GameDrawLevelGauge(GameStatus.level + 1);
}



/***********************************************************************
 *
 * FUNCTION:     GameStateDrawChanges
 *
 * DESCRIPTION:  Show the world.  Moves the charges and the ship.  Removes
 * bricks.  Redraws the score.
 *
 * No changes are made to the world here.  Scores do not change, nothing moves.
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

static void GameStateDrawChanges (void)
{
	RectangleType bounds;
	register Int16 i;
	FontID currFont;
	ObjectType *shipLastP, *shipNextP;
	ObjectType *subLastP, *subNextP;
	ExplosiveType *chargeLastP, *chargeNextP;
	ExplosiveType *mineLastP, *mineNextP;
	UInt16 savedCoordSys;

	currFont = FntSetFont(scoreFont);


	// Update the water line
	if (GameStatus.waterLineDirty)
		{
		DrawObject (waterLineBitmap,
			overlayTopLeftX + 0,
			overlayTopLeftY + waterLine,
			winPaint);
		}


	// Visually move the ship

	shipLastP = &GameStatus.last.ship;
	shipNextP = &GameStatus.next.ship;

	// Erase the old ship
	if (shipLastP->usable &&
		shipNextP->changed)
		{
		bounds.topLeft.x = overlayTopLeftX + shipLastP->sides.left;
		bounds.topLeft.y = overlayTopLeftY + shipLastP->sides.top;
		bounds.extent.x = shipLastP->sides.right - shipLastP->sides.left;
		bounds.extent.y = shipLastP->sides.bottom - shipLastP->sides.top;
		WinEraseRectangle(&bounds, 0);
		}

	// Draw the new ship
	if ((shipNextP->usable &&
		shipNextP->changed) ||
		GameStatus.waterLineDirty)
		{
		// The ship is sinking, the ship is drawn lower than otherwise.  Clip the portion
		// which would lie underwater.
		if (GameStatus.shipSunkAmount)
			{
			bounds.topLeft.x = overlayTopLeftX + shipNextP->sides.left;
			bounds.topLeft.y = overlayTopLeftY + shipNextP->sides.top;
			bounds.extent.x = shipNextP->sides.right - shipNextP->sides.left;
			bounds.extent.y = shipNextP->sides.bottom - shipNextP->sides.top;
			WinSetClip(&bounds);
			}

		DrawObject (GetShipBitmap(shipNextP->type, GameStatus.shipHitCount),
			overlayTopLeftX + shipNextP->sides.left,
			overlayTopLeftY + shipNextP->sides.top + GameStatus.shipSunkAmount,
			winPaint);

		if (GameStatus.shipSunkAmount)
			WinResetClip();

		GameStatus.waterLineDirty = false;
		}


	// Visually move the subs
	for (i = subsMax - 1; i >= 0; i--)
		{
		subLastP = &GameStatus.last.sub[i];
		subNextP = &GameStatus.next.sub[i];

		// Erase the old sub
		if (subLastP->usable &&
			subNextP->changed)
			{
			// use native coordinates to avoid rounding error caused
			// by low density sub bitmaps that have an odd width
			savedCoordSys = WinSetCoordinateSystem(kCoordinatesNative);

			bounds.topLeft.x = overlayTopLeftX + subLastP->sides.left;
			bounds.topLeft.y = overlayTopLeftY + subLastP->sides.top;
			bounds.extent.x = subLastP->sides.right - subLastP->sides.left;
			bounds.extent.y = subLastP->sides.bottom - subLastP->sides.top;
			WinScalePoint(&bounds.topLeft, false);
			WinScalePoint(&bounds.extent, false);

			WinEraseRectangle(&bounds, 0);
			WinSetCoordinateSystem(savedCoordSys);
			}

		// Draw the new sub
		if (subNextP->usable &&
			subNextP->changed)
			{
			DrawObject (GetSubBitmap(subNextP->type, subNextP->heading),
				overlayTopLeftX + subNextP->sides.left,
				overlayTopLeftY + subNextP->sides.top,
				(subNextP->sides.top < subSubmergedPosition) ? winOverlay : winPaint);

			// Now draw the score over the sub
			if (subDisplaysScore(subNextP->type))
				{
				WinEraseChars(subNextP->scoreText, subNextP->scoreDigits,
					overlayTopLeftX + subNextP->sides.left +
						(subLastP->heading == leftSide ? subLeftScoreXOffset :
							subRightScoreXOffset - subNextP->scoreDigits * scoreCharWidth),
					overlayTopLeftY + subNextP->sides.bottom - subScoreYOffset);
				}
			}
		}

	// Redraw the water line if it is partially erased by the top submarine
	if (subLastP->usable &&
		subNextP->changed &&
		subLastP->sides.top < waterLine + waterThickness)
		{
		GameStatus.waterLineDirty = true;
		}



	// Visually move the charges
	for (i = GameStatus.next.chargeCount - 1; i >= 0; i--)
		{
		chargeLastP = &GameStatus.last.charge[i];
		chargeNextP = &GameStatus.next.charge[i];

		// Erase the old charge
		if (chargeLastP->usable &&
			chargeNextP->changed)
			{
			if (!chargeLastP->exploding)
				{
				// The charge has moved through the waterLine - causing it to be
				// partially erased (dirty).  A better way is to XOR the graphic
				// but there's a patent on it. !%#@$^#$!
				if (chargeLastP->sides.top == (waterLine + waterThickness))
					{
					GameStatus.waterLineDirty = true;
					}

				// If the charge is below the water line we erase it
				bounds.topLeft.x = overlayTopLeftX + chargeLastP->sides.left;
				bounds.topLeft.y = overlayTopLeftY + chargeLastP->sides.top;
				bounds.extent.x = chargeLastP->sides.right - chargeLastP->sides.left;
				bounds.extent.y = chargeLastP->sides.bottom - chargeLastP->sides.top;
				WinEraseRectangle(&bounds, 0);
				}
			else
				{
				DrawObject (explosionMask,
					overlayTopLeftX + chargeLastP->sides.left,
					overlayTopLeftY + chargeLastP->sides.top,
					winMask);
				}
			}

		// Draw the new charge
		if (chargeNextP->usable &&
			chargeNextP->changed)
			{
			if (!chargeNextP->exploding)
				DrawObject (GetChargeBitmap(chargeNextP->type),
					overlayTopLeftX + chargeNextP->sides.left,
					overlayTopLeftY + chargeNextP->sides.top,
					winPaint);
			else
				{
				DrawObject (explosionMask,
					overlayTopLeftX + chargeNextP->sides.left,
					overlayTopLeftY + chargeNextP->sides.top,
					winMask);
				DrawObject (explosionBitmap,
					overlayTopLeftX + chargeNextP->sides.left,
					overlayTopLeftY + chargeNextP->sides.top,
					winOverlay);
				}
			}
		}


	// Visually move the mines.  Do all the erases first and then the draws.
	// This corrects cases where mines are overlapping
	for (i = GameStatus.next.mineCount - 1; i >= 0; i--)
		{
		mineLastP = &GameStatus.last.mine[i];
		mineNextP = &GameStatus.next.mine[i];

		// Erase the old mine
		if (mineLastP->usable &&
			mineNextP->changed)
			{
			// Redraw the water line if it is partially erased.
			if (mineLastP->sides.top < waterLine + waterThickness)
				GameStatus.waterLineDirty = true;

			// use native coordinates to avoid rounding error caused
			// by low density mine bitmaps that have an odd width
			savedCoordSys = WinSetCoordinateSystem(kCoordinatesNative);

			bounds.topLeft.x = overlayTopLeftX + mineLastP->sides.left;
			bounds.topLeft.y = overlayTopLeftY + mineLastP->sides.top;
			bounds.extent.x = mineLastP->sides.right - mineLastP->sides.left;
			bounds.extent.y = mineLastP->sides.bottom - mineLastP->sides.top;
			WinScalePoint(&bounds.topLeft, false);
			WinScalePoint(&bounds.extent, false);

			WinEraseRectangle(&bounds, 0);
			WinSetCoordinateSystem(savedCoordSys);
			}

		// Draw the new mine
		if (mineNextP->usable &&
			mineNextP->changed)
			{
			DrawObject (GetMineBitmap(mineNextP->type),
				overlayTopLeftX + mineNextP->sides.left,
				overlayTopLeftY + mineNextP->sides.top,
				(mineNextP->type == explosionMine) ? winMask : winOverlay);
			}
		}


	// Update the score
	if (GameStatus.last.score != GameStatus.next.score)
		{
		GameDrawScoreGauge(GameStatus.next.score);
		}

	FntSetFont(currFont);
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


	GameDrawLevelGauge(GameStatus.level + 1);

	// Wipe the display clean (gets rid of the end of level report).
	GameStateDraw();


	GameStatus.status = SubsInMotion;

	// Set up the subs.  All the subs are not used.

	// Reset the subs
	GameStatus.subsThisLevel = GameStatus.level * 5 + 5;
	GameStatus.subsRemaining = GameStatus.subsThisLevel;
	GameStatus.subUnderWaterCount = 0;
	GameStatus.subsDestroyedThisLevel = 0;
	for (i = subsMax - 1; i >= 0; i--)
		{
		GameStatus.next.sub[i].usable = false;
		GameStatus.next.sub[i].changed = false;
		}

}


/***********************************************************************
 *
 * FUNCTION:     GameEndLevel
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

static void GameEndLevel (void)
{
	Char * subsClearedString;
	char ratingText[3 + 1 + 1];		// percent digits + percent sign + null char
	Int16 ratingLength;
	FontID currFont;


	// Set the game status to advance to the next level
	GameStatus.status = levelOver;
	GameStatus.periodsTillNextLevel = levelOverTimeInterval +
		(sysTicksPerSecond / 5) * GameStatus.level;


	currFont = FntSetFont(reportFont);

	// Report how many subs were sunk
	StrIToA(ratingText, (GameStatus.subsDestroyedThisLevel * 100) / GameStatus.subsThisLevel);
	StrCat(ratingText, "%");
	ratingLength = StrLen(ratingText);

	subsClearedString = MemHandleLock (DmGetResource (strRsc, subsClearedStr));

	WinDrawChars(subsClearedString, StrLen(subsClearedString),
		clearMessageX, clearMessageY);
	WinDrawChars (ratingText, ratingLength,
		clearMessageX + FntCharsWidth(subsClearedString, StrLen(subsClearedString)),
		clearMessageY);


	MemPtrUnlock(subsClearedString);
	FntSetFont(currFont);
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

	if (GameStatus.status == levelOver &&
		GameStatus.periodsTillNextLevel == 0)
		{
		GameStatus.level++;
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
	int i;


	// Set the keys
	GameMaskKeys ();

	GameStatus.paused = false;
	GameStatus.pausedTime = 0;

	if (GameStatus.status != gameResuming)
		{
		GameStatus.next.score = 0;
		GameStatus.soundToMake = noSound;
		GameStatus.level = Prefs.startLevel;
		GameStatus.lowestHighScorePassed = false;
		GameStatus.highestHighScorePassed = false;

		GameStatus.shipHitCount = 0;
		GameStatus.next.chargeCount = 0;
		GameStatus.next.mineCount = 0;

		// Clear all charges
		for (i = 0; i < chargesMax; i++)
			{
			GameStatus.next.charge[i].usable = false;
			GameStatus.next.charge[i].changed = false;
			}


		// Clear all mines
		for (i = 0; i < minesMax; i++)
			{
			GameStatus.next.mine[i].usable = false;
			GameStatus.next.mine[i].changed = false;
			}


		GameInitLevel ();
		ShipAdd();
		GameStateAdvance();

		// Synchronize the periods to the timer.
		GameStatus.nextPeriodTime = TimGetTicks() + advanceTimeInterval;
		}
	else
		{
		GameStatus.status = SavedGameStatus;
		GameStatus.nextPeriodTime = TimGetTicks() + pauseLengthBeforeResumingSavedGame;
		}
}


/***********************************************************************
 *
 * FUNCTION:     CheckChargeAndSubCollisionCarefully
 *
 * DESCRIPTION:  Check for collisions of a charge into a sub.  This is
 * a detailed calculation and thus isn't trivially quick.
 *
 * So far the detailed calculations haven't been needed.
 *
 * PARAMETERS:   charge - the charge to check
 *					  sub - the sub to check
 *
 * RETURNED:     true if they hit
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/
static Boolean CheckChargeAndSubCollisionCarefully (ExplosiveType	*UNUSED_PARAM(charge),
	ObjectType *UNUSED_PARAM(sub))
{
	// Add logic to detect if the charge really touches the sub
	return true;
}


/***********************************************************************
 *
 * FUNCTION:     CheckChargeWithSubCollisions
 *
 * DESCRIPTION:  Check for collisions of charges into subs and MemHandle
 * the results if so.
 *
 * If the charge touches a sub, the charge is
 *
 * PARAMETERS:   chargeNumber - the charge to check
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	2/27/96	Initial Revision
 *
 ***********************************************************************/
static void CheckChargeWithSubCollisions ()
{
	ExplosiveType	*charge;
	ObjectType	*sub;
	Int16 chargeNumber = GameStatus.next.chargeCount - 1;	// shallowest charge
	Int16 subNumber = 0;			// shallowest sub


	charge = &GameStatus.next.charge[chargeNumber];
	sub = &GameStatus.next.sub[subNumber];


	while (subNumber < subsMax && chargeNumber >= 0)
		{
		if (charge->exploding)
			{
			chargeNumber--;
			charge = &GameStatus.next.charge[chargeNumber];
			}
		else if (sub->usable)
			{
			// if the charge is below the sub look for a deeper sub
			if (charge->sides.top > sub->sides.bottom)
				{
				subNumber++;
				sub = &GameStatus.next.sub[subNumber];
				}
			// If the charge is above the sub look for a deeper charge
			else if (charge->sides.bottom < sub->sides.top)
				{
				chargeNumber--;
				charge = &GameStatus.next.charge[chargeNumber];
				}
			// The sub and charge are at the same depth.  Check if bounding boxes touch
			else if (charge->sides.right >= sub->sides.left &&
					charge->sides.left <= sub->sides.right &&
					CheckChargeAndSubCollisionCarefully(charge, sub))
				{
				// We have a collision!
				SubDestroy(chargeNumber, subNumber);

				subNumber++;
				sub = &GameStatus.next.sub[subNumber];
				chargeNumber--;
				charge = &GameStatus.next.charge[chargeNumber];
				}
			else
				{
				// The charge can't possibly hit another sub because only one sub is
				// allowed at this depth.  The sub can possibly hit another charge.
				// So try the next charge.
				chargeNumber--;
				charge = &GameStatus.next.charge[chargeNumber];
				}
			}
		else
			{
			subNumber++;
			sub = &GameStatus.next.sub[subNumber];
			}
		}

}


/***********************************************************************
 *
 * FUNCTION:     ShipMove
 *
 * DESCRIPTION:  Move the ship if requested.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/22/96	Initial Revision
 *
 ***********************************************************************/
static void ShipMove (UInt32 hardKeyState)
{
	Int16 smallestMove;
	ObjectType *shipNextP;


	GameStatus.moveShipLeft = false;
	GameStatus.moveShipRight = false;
	smallestMove = shipMovement;


	shipNextP = &GameStatus.next.ship;


	// Move the ships in a direction.  Remember that there may be multiple ships.
	// If one ship can't move then none can move.
	if (hardKeyState & moveLeftKey && !(hardKeyState & moveRightKey))
		{
		// Move the ship as much as possible to the left
		if (shipNextP->usable &&
			GameStatus.shipSunkAmount == 0)
			{
			smallestMove = min(smallestMove, shipNextP->sides.left -
				spaceRequiredToDropCharges);
			if (smallestMove > 0)
				{
				shipNextP->sides.left -= smallestMove;
				shipNextP->sides.right -= smallestMove;
				shipNextP->changed = true;
				GameStatus.moveShipLeft = true;
				}
			}
		}
	else if (hardKeyState & moveRightKey && !(hardKeyState & moveLeftKey))
		{
		// Move the ship as much as possible to the left
		if (shipNextP->usable &&
			GameStatus.shipSunkAmount == 0)
			{
			smallestMove = min(smallestMove, (boardWidth - spaceRequiredToDropCharges) -
					shipNextP->sides.right);
			if (smallestMove > 0)
				{
				shipNextP->sides.left += smallestMove;
				shipNextP->sides.right += smallestMove;
				shipNextP->changed = true;
				GameStatus.moveShipRight = true;
				}
			}
		}
	else 	// the ship moved neither direction
		{
		shipNextP->changed = false;
		}
}


/***********************************************************************
 *
 * FUNCTION:     SubMoveAll
 *
 * DESCRIPTION:  Move all the subs.  This routine also contains the logic
 * for subs to change speed, direction, and levels.  It also has stuff
 * to move the sub to the surface and attack the ship.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/22/96	Initial Revision
 *
 ***********************************************************************/
static void SubMoveAll ()
{
	int i;
	int chance;
	ObjectType	*sub;
	int moveAmount;
	UInt8 mineType;


	// Move the subs.  Subs may lay mines
	for (i = subsMax - 1; i >= 0; i--)
		{
		sub = &GameStatus.next.sub[i];

		// Ignore unusable subs
		if (!sub->usable)
			{
			sub->usable = false;
			sub->changed = false;
			}
		else
			{
			// Move the sub if there are no more periods to wait until it moves
			sub->periodsUntilMove--;
			if (sub->periodsUntilMove <= 0)
				{
				// Was the sub sinking?
				if (sub->sinking)
					{
					SubRemove(i);
					continue;
					}


				// if verne sub at the top give it the chance to ram the ship
				if (i == 0 &&
					!subAttackingShip(sub) &&
					((sub->type == verneSub && RandN(1000) < 32) ||
					(sub->type > verneSub && RandN(1000) < 48)))
					{
					sub->desiredSpeed = maxSpeed;
					sub->desiredLevel = shipLevel;
					}

				// Does the sub want to change it's speed if it's not already doing so
				// and it isn't set to attack the ship on the surface.
				else if (sub->speed == sub->desiredSpeed &&
					!subAttackingShip(sub) &&
					((sub->type == verneSub && RandN(1000) < 16) ||
					(sub->type >= squidSub && RandN(1000) < 20)))
					{
					switch (sub->type)
						{
						case verneSub:
							sub->desiredSpeed = pickVerneSubSpeed;
							break;

						case squidSub:
							sub->desiredSpeed = pickSquidSubSpeed;
							break;

						case whaleSub:
							sub->desiredSpeed = pickWhaleSubSpeed;
							break;
						}

					// Change directions?
					if (RandN(100) < changeDirectionPercent)
						{
						sub->desiredSpeed = -sub->desiredSpeed;
						}
					}

				// Work to change speeds
				if (sub->speed != sub->desiredSpeed)
					{
					if (sub->desiredSpeed > sub->speed)
						{
						sub->speed += 2;
						}
					else
						{
						// Slow down and eventually switch directions when the speed
						// wil become zero.
						// change heading?
						if (sub->speed <= 2)
							{
							sub->speed = 1;
							sub->heading = oppositeHeading(sub->heading);
							sub->desiredSpeed = -sub->desiredSpeed;
							}
						else
							sub->speed -= 2;
						}
					}


				// Does the sub want to change it's level if it's not already doing so
				// and it isn't set to attack the ship on the surface.
				else if (sub->desiredLevel == i &&
					!subAttackingShip(sub) &&
					i > 0 &&
					GameStatus.next.sub[i-1].usable == false &&
					GameStatus.next.sub[i-1].changed == false &&
					((sub->type == verneSub && RandN(1000) < 16) ||
					(sub->type >= squidSub && RandN(1000) < 30 +
						(sub->sides.left < GameStatus.next.ship.sides.right &&
						sub->sides.right >= GameStatus.next.ship.sides.left) ? 100 : 0)))
					{
					sub->desiredLevel--;
					}


				sub->periodsUntilMove = maxSpeed -
					sub->speed + 1;		// 0 to maxSpeed

				sub->changed = true;

				if (sub->heading == leftSide)
					{
					sub->sides.left--;
					sub->sides.right--;

					// did the sub move off the screen (and therefore leave)?
					if (sub->sides.right < 0)
						{
						sub->usable = false;
						GameStatus.subUnderWaterCount--;
						}

					}
				else
					{
					sub->sides.left++;
					sub->sides.right++;

					// did the sub move off the screen (and therefore leave)?
					if (sub->sides.left > boardWidth)
						{
						sub->usable = false;
						GameStatus.subUnderWaterCount--;
						}

					}

				// MemHandle subs at the surface
				if (i == 0)
					{
					// Help the sub surface if it's trying to
					if (sub->desiredLevel == shipLevel &&
						sub->sides.top > subAboveWaterPosition)
						{
						sub->sides.top--;
						sub->sides.bottom--;
						}
					// Help the sub submerge if it's trying to
					else if (sub->desiredLevel == 0 &&
						sub->sides.top < subSubmergedPosition)
						{
						sub->sides.top++;
						sub->sides.bottom++;
						}

					// ram the ship!
					if (sub->sides.top == subAboveWaterPosition &&
						sub->type == verneSub &&
						((sub->heading == leftSide &&
							sub->sides.left == GameStatus.next.ship.sides.right - 4) ||
						(sub->heading == rightSide &&
							sub->sides.right == GameStatus.next.ship.sides.left - 4)))
						{
						ShipHit();
						sub->desiredLevel = 0;		// dive!
						}
					// choke the ship!  When a animal is hit it's set to move immediately.
					// Don't let the animal choke the ship this time because it hasn't
					// waited long enough to choke the ship, it's just fleeing.
					else if (sub->sides.top <= subAboveWaterPosition &&
						sub->type >= squidSub &&
						sub->speed != animalFleeingSpeed)
						{
						// If we touch the ship we hit it!
						if (sub->sides.left < GameStatus.next.ship.sides.right - squidTouchAmount &&
							sub->sides.right >= GameStatus.next.ship.sides.left + squidTouchAmount)
							{
							ShipHit();
							sub->periodsUntilMove = periodsForSquidToChoke;
							sub->sides.top -= 4;		// rise up on the ship!
							sub->sides.bottom -= 4;

							// Make sure the squid isn't above the ship
							moveAmount = GameStatus.next.ship.sides.top + GameStatus.shipSunkAmount -
								sub->sides.top;
							if (moveAmount > 0)
								{
								sub->sides.top += moveAmount;
								sub->sides.bottom += moveAmount;
								}


							// Move the tentacles on the ship because they don't touch the ship!
							if (sub->heading == leftSide &&
								GameStatus.next.ship.sides.right < sub->sides.right)
								{
								sub->heading = rightSide;
								moveAmount = (sub->sides.left - GameStatus.next.ship.sides.left) / 2;
								sub->sides.left -= moveAmount;
								sub->sides.right -= moveAmount;
								}
							else if (sub->heading == rightSide &&
								GameStatus.next.ship.sides.left > sub->sides.left)
								{
								sub->heading = leftSide;
								moveAmount = (GameStatus.next.ship.sides.right - sub->sides.right) / 2;
								sub->sides.left += moveAmount;
								sub->sides.right += moveAmount;
								}
							}
						else
							{
							// The sub may have moved from the squid.  If the squid still
							// thinks it's on the ship move it back into the water.
							if (sub->sides.top < subAboveWaterPosition)
								{
								sub->sides.top += 4;		// sink back to the surface
								sub->sides.bottom += 4;
								}

							// head toward the ship!
							if (sub->sides.left >= GameStatus.next.ship.sides.right)
								{
								sub->heading = leftSide;
								}
							// head toward the ship!
							else if (sub->sides.right <= GameStatus.next.ship.sides.left)
								{
								sub->heading = rightSide;
								}
							}
						}
					}
				else
					// MemHandle subs changing levels
					{
					if (sub->desiredLevel < i)
						{
						sub->sides.top--;
						sub->sides.bottom--;

						if (sub->sides.top == subSubmergedPosition +
							sub->desiredLevel * subVerticalSpacing)
							{
							MemMove(&GameStatus.next.sub[i - 1], sub, sizeof(ObjectType));
							// So the DrawChanges routine can erase the old position
							MemMove(&GameStatus.last.sub[i - 1], &GameStatus.last.sub[i], sizeof(ObjectType));

							// Remove sub from current location
							sub->usable = false;
							sub->changed = false;		// avoid redraws

							i--;			// skip the next sub (we just copied over it)
							continue;
							}

						}
					}



				// Does the moving sub want to lay a mine?  Squids and whales may not
				// lay mines.  Verne subs are twice as likely to lay a mine if the ship
				// is above.  Verne subs launch fastMines.
				if (subLaysMines(sub->type) &&
					sub->sides.top >= subSubmergedPosition &&
					(chance = RandN(1000)) < min(maxLayMinePerThousand, ((GameStatus.level * 6 *
						((sub->type == verneSub && IsSubUnderShip(i)) ?
						2 * 6 : 6)) / 4)))
					{
					// Lay the mine from the top middle of the sub.  Normal subs lay normal mines.
					// Verne subs lay fast mines, although there is a chance in the higher levels
					// for them to lay a magnetic mine.
					if (sub->type == verneSub)
						{
						if (GameStatus.level >= firstMagneticMineLevel &&
							RandN(100) < magneticMineChance)
							{
							mineType = magneticMine;
							}
						else
							mineType = fastMine;
						}
					else
						mineType = normalMine;

					MineAdd(mineType,
						(sub->sides.right + sub->sides.left) / 2,	// the middle of the sub
						sub->sides.top, sub->type);
					}
				}
			else
				{
				// The sub didn't move yet
				sub->changed = false;
				}
			}
		}
}


/***********************************************************************
 *
 * FUNCTION:     ChargesMoveAll
 *
 * DESCRIPTION:  Move all the depth charges.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/22/96	Initial Revision
 *
 ***********************************************************************/
static void ChargesMoveAll ()
{
	int i;
	ExplosiveType *charge;


	// Move the charges
	// Do this before dropping a charge to insure that one just dropped can move
	// out of the way of the next one.
	for (i = GameStatus.next.chargeCount - 1; i >= 0; i--)
		{
		charge = &GameStatus.next.charge[i];


		// Remove unusable charges
		if (!charge->usable)
			{
			DepthChargeRemove(i);
			}
		else
			{
			// Move the charge if there are no more periods to wait until it moves
			charge->periodsUntilMove--;
			if (charge->periodsUntilMove <= 0)
				{
				if (charge->exploding)
					{
					// erase the old image
					charge->changed = true;

					// don't draw another image.  mark to be removed.
					charge->usable = false;

					continue;
					}

				charge->periodsUntilMove = maxSpeed - chargeSpeed +1;
				charge->changed = true;

				charge->sides.top++;
				charge->sides.bottom++;

				// did the charge move off the screen (and therefore leave)?
				if (charge->sides.top > gameHeight)
					{
					// erase the old image
					charge->changed = true;

					// don't draw another image.  mark to be removed.
					charge->usable = false;
					}
				}
			else
				{
				// The charge didn't move yet
				charge->changed = false;
				}
			}

		}
}


/***********************************************************************
 *
 * FUNCTION:     MineMoveAll
 *
 * DESCRIPTION:  Move all the mines.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			roger	3/22/96	Initial Revision
 *
 ***********************************************************************/
static void MineMoveAll ()
{
	int i;
	ExplosiveType *mine;


	// Move the mines
	for (i = GameStatus.next.mineCount - 1; i >= 0; i--)
		{
		mine = &GameStatus.next.mine[i];


		// Remove unusable mines
		if (!mine->usable)
			{
			MineRemove(i);
			}
		else
			{
			// Move the mine if there are no more periods to wait until it moves
			mine->periodsUntilMove--;
			if (mine->periodsUntilMove <= 0)
				{
				if (mine->exploding)
					{
					// erase the old image
					mine->changed = true;

					// don't draw another image.  mark to be removed.
					mine->usable = false;

					continue;
					}

				switch (mine->type)
					{
					case fastMine:
						mine->periodsUntilMove = 1 + maxSpeed - fastMineSpeed;
						break;

					default:
						mine->periodsUntilMove = 1 + maxSpeed - mineSpeed;
						break;
					}

				mine->changed = true;

				// Mines float up to the surface
				mine->sides.top--;
				mine->sides.bottom--;


				// Magnetic mines tend to follow the ship
				if (mine->type == magneticMine &&
					RandN(100) < magneticMineFollowChance)
					{
					// Because the mines must move left or right they can never stay
					// centered.  They therefore can appear to wander but I think that's
					// OK.
					if ((GameStatus.next.ship.sides.left + GameStatus.next.ship.sides.right) / 2 >
						(mine->sides.left + mine->sides.right) / 2)
						{
						mine->sides.left++;
						mine->sides.right++;
						}
					else
						{
						mine->sides.left--;
						mine->sides.right--;
						}
					}


				// did the mine reach the surface?
				if (mine->sides.top <= (waterLine + waterThickness))
					{
					// mines explode with a splash when they reach the surface.
					MineExplode(i);
					}
				}
			else
				{
				// The mine didn't move yet
				mine->changed = false;
				}
			}

		}
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
	UInt32 hardKeyState;
	int chance;
	Boolean updateChargesDisplayed = false;
	int side;


	// Don't advance past checking high scores.
	if (GameStatus.status == checkHighScores)
		return;

	// We have paused after the game.  Now check for a high score.
	if (GameStatus.status == gameOver)
		{
		// Cancel any sounds being played so they don't blurt out later
		GameStatus.soundToMake = noSound;

		GameStatus.status = checkHighScores;
		HighScoresCheckScore();

		// Allow the hard keys to switch to another app now that the player is done.
		GameUnmaskKeys ();
		return;
		}

	// When all the subs are clear advance to the next level.
	if (GameStatus.subsRemaining == 0 &&
		GameStatus.subUnderWaterCount == 0 &&
		GameStatus.status == SubsInMotion)
		{
		GameEndLevel();
		return;
		}


	// The time between the last advance and the next is constant
	GameStatus.nextPeriodTime = GameStatus.nextPeriodTime + advanceTimeInterval;


	// When a level is over there is a period of quite time during which
	// no subs are sent.
	if (GameStatus.status == levelOver)
		{
		GameStatus.periodsTillNextLevel--;
		}
	else
		{
		// Add more subs.  The higher the level the more likely a sub is added.
		while ((chance = RandN(100)) < (GameStatus.level / 2 + 2))	// chanceForNewSub
			{
			SubAdd(RandN(sideCount));
			}
		}


	// Move the ship
	hardKeyState = KeyCurrentState() & keysAllowedMask;
	ShipMove (hardKeyState);

	// MemHandle the ship sinking
	if (GameStatus.shipSunkAmount > 0)
		{
		GameStatus.next.ship.periodsUntilMove--;
		if (GameStatus.next.ship.periodsUntilMove <= 0)
			{
			GameStatus.shipSunkAmount++;
			GameStatus.next.ship.changed = true;
			GameStatus.next.ship.periodsUntilMove = periodsToSinkOneNotch;

			if (GameStatus.shipSunkAmount >= shipCompletelySunkAmount)
				GameStatus.status = gameOver;

			GameRequestSound (shipSinking);
			}
		}



	SubMoveAll ();


	ChargesMoveAll();


	// Now perform one period of updating the charge inventory
	for (side = rightSide; side <= leftSide; side++)
		{
		if (GameStatus.periodsTillNextDrop[side] > 0)
			GameStatus.periodsTillNextDrop[side]--;

		if (GameStatus.chargesAvailable[side] < chargeCapacity)
			{
			GameStatus.periodsTillNextReload[side]--;
			if (GameStatus.periodsTillNextReload[side] == 0)
				{
				GameStatus.chargesAvailable[side]++;
				GameStatus.periodsTillNextReload[side] = periodsBetweenChargeReloads;
				updateChargesDisplayed = true;
				}
			}
		}


	// Drop a depth charge over the side
	if ((hardKeyState & dropLeftKey) &&
		GameStatus.next.ship.usable &&
		GameStatus.shipSunkAmount < spaceUntilDepthChargeLauncherSubmerged &&
		GameStatus.next.ship.sides.left >= spaceRequiredToDropCharges &&
		GameStatus.chargesAvailable[leftSide] > 0 &&
		GameStatus.periodsTillNextDrop[leftSide] == 0)
		{
		updateChargesDisplayed = DepthChargeAdd(normalCharge, leftSide) || updateChargesDisplayed;
		}
	else if ((hardKeyState & dropRightKey) &&
		GameStatus.next.ship.usable &&
		GameStatus.shipSunkAmount < spaceUntilDepthChargeLauncherSubmerged &&
		GameStatus.next.ship.sides.right <= (gameWidth - spaceRequiredToDropCharges) &&
		GameStatus.chargesAvailable[rightSide] > 0 &&
		GameStatus.periodsTillNextDrop[rightSide] == 0)
		{
		updateChargesDisplayed = DepthChargeAdd(normalCharge, rightSide) || updateChargesDisplayed;
		}



	MineMoveAll ();


	// If a charge was dropped or one was reloaded update the display
	if (updateChargesDisplayed)
		GameDrawChargeGauge();


	CheckChargeWithSubCollisions();


	// redraw the attacking sub if the ship is being redrawn.  Otherwise if the
	// two overlap and the ship is erased and redrawn the sub will not be
	// visible until it moves.  In the meantime the squid may be sucking on the
	// ship without the player seeing it and they won't be happy when the squid
	// reappears out of nowhere!
	if (GameStatus.next.ship.changed &&
		subAttackingShip(&GameStatus.next.sub[0]))
		GameStatus.next.sub[0].changed = true;
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

		SndDoCmd( 0, &sndCmd, true);

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
 *			roger	4/23/96	Added a cancel button
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
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    true if the command was handled
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
			GameStateDraw ();
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
 *			kwk	12/03/98	Check for not cmd key before handling 's' & 't' events.
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
		else if (EvtKeydownIsVirtual(event))
			{
			if (event->data.keyDown.chr == restartGameChar)
				{
				if (GameStatus.status == checkHighScores)
					{
					GameStart();
					GameStateDraw ();
					}
				}
			}
		// command to skip to the next level
		else if (event->data.keyDown.chr == 's')
			{
			GameStatus.status = levelOver;
			}

		// time spent playing		(quick code at this point.)
		else if (event->data.keyDown.chr == 't')
			{
			char timeString[timeStringLength + 5];
			UInt32 seconds;
			DateTimeType timeSpent;

			seconds = (Prefs.accumulatedTime + (TimGetTicks() -
				GameStatus.startTime)) / sysTicksPerSecond;
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
		GameStateDraw ();

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
 * DESCRIPTION: This routine loads form resources and set the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has MemHandle and should not be passed
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
			// In the current code, the menu doesn't remove itself when it receives
			// a winExitEvent.
			if (event.data.winEnter.enterWindow == (WinHandle) FrmGetFormPtr(BoardView) &&
				event.data.winEnter.enterWindow == (WinHandle) FrmGetFirstForm())
				{
				// Sometimes we can enter the game's window without knowing it was
				// ever left.  In that case the pause time will not have been recorded.
				// Set the current period back to it's beginning
				if (!GameStatus.paused)
					{
					GameStatus.nextPeriodTime = TimGetTicks() + advanceTimeInterval;
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
 * FUNCTION:    SubHuntMain
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
