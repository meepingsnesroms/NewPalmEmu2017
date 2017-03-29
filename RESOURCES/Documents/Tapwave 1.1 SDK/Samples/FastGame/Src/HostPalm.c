/*! file
	File:			HostPalm.c

	Description:	This is the host portion of the example.  OS and device specific code to get the input, 
					load graphics, draw specific graphics, save and load games, and so on belongs 
					in here for use by the game.
	
					This file also provides a TapWave look and feel to the game. This code runs like
					a TapWave app, and can override the game's wishes to provide a best handheld
					interpretation of the game.

					This file is in C like most Palm programs.  It interacts with game.cpp to show
					how to work with C++ programs.

	Author:			Roger Flores

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

/*!

Glossary

game cycle:  Everything needed to advance the game one step.  This includes
    taking input, moving all world objects, triggering events, collision 
    detection, and drawing.

offscreen buffer: A set of pixels not used by the screen.  The graphics 
    are composed there and when done, made visible by the screen, by 
    copying them, or sometimes by pointing the screen hardware to them.
    
landscape mode: The screen placed into 480x320 mode.  No status bar is
    visible.  The Palm coordinate system remains 240x160 (low density).
    
game menu: A UI system to control or configure the game.  The method used
    draws over game in the offscreen buffer.  An alternative is to use 
    the Palm Menu system, but if so, be careful not to draw the game 
    which would overwrite the menus.

Palm bitmaps: Bitmaps in a native Palm format.  Typically created from
    BMP files with pilrc or pasted into Constructor and stored in the
    app's PRC.  Bitmaps can have alternate color depths and resolutions and are 
    collectively called a bitmap family.  The most appropriate family
    member is drawn.  The Palm API usually uses the hardware acceleration 
    when possible.
*/

#include <TapWave.h>
#ifdef __PALMOS_ARMLET__
  #include "BannedTraps.h"
#endif

#include "host.h"
#include "utils.h"
#include "gauge.h"


// Define this to run full speed.  Leave undefined to run at a constant 
// frame rate.
#define OPTION_DELAY_NONE 1


/*
 * UI and graphics for Palm OS software are often edited using the 
 * Constructor tool.  Constructor can be told to describe the UI and
 * graphic resources in a header file.  That header is included here.
 */

#include "FastGameRsc.h"

#define ObjectBitmapFirst       2000
#define ObjectBitmapCount		2



// List of key bindings
#define rotateLeftKey		keyBitHard1 // polled every game period
#define rotateRightKey		keyBitHard2 // polled every game period
#define shootKey			keyBitHard3 // polled every game period
#define thrustKey			keyBitHard4 // polled every game period
#define keysAllowedMask		(rotateLeftKey | rotateRightKey | shootKey | thrustKey )


/* This is the input that we regularly poll for each game cycle.  More
could be added. */
typedef struct 
{
  Int32 joyX;
  Int32 joyY;
} AppJoystickInput;


// This defines the game menu, which is shown while the game is paused.
// It is reached by pressing the Home button.  Pressing Home again 
// switches apps to Home.  Pushing the joystick down selects the game
// resume.
#define GameMenuResume  0
#define GameMenuExit    1
#define GameMenuCount   2

// The ARM compiler does not link strings in a Position Independent code model.
// A workaround is to fully allocate the storage.
char GameMenuText[GameMenuCount][8] = 
{
    "Resume",
    "Exit"
};

#define FPS_DATA_MAX 300
typedef struct
{
	int time[FPS_DATA_MAX];
	int count;
	int time_of_last_data_out;
} FPSType;

typedef struct
{
    TwGfxSurfaceType * pictureBitmapP[ObjectBitmapCount];
    
    //! These are only used if customBlitting is true.  They cache some of the info on
    //! the pictures that will be used often.  Custom blitting means using 
    //! a custom blitter drawing to a frame buffer, versus using the standard
    //! API calls.
    TwGfxType * GFX;
    TwGfxSurfaceType * displaySurface;
    
    MemPtr pictureBitmapBitsP[ObjectBitmapCount];
    Boolean pictureIsTransparent[ObjectBitmapCount];
    Int16 _pad_;
    UInt32 pictureTransparencyIndex[ObjectBitmapCount];
    Boolean customBlitting;
    Boolean isInputMasked;

    UInt16 soundAmp;            // default sound amplitude

    Int32 screenWidth;
    Int32 screenHeight;
	
	// This is the offscreen buffer which is copied to the screen.
    TwGfxSurfaceType * screenBufferH;    // screenBuffer
    UInt8 * screenBufferP;  // DOLATER - This is really a pointer to the pixels!
    
    
	TwDeviceHandle rumblerH;	// device to play the rumble data
    
    //! These are used to get the input.  isInputMasked prevents them
    //! from being set or unset repeatedly.  The padding inserted is
	//! to achieve ARM alignment for these data structures.
	//! NOTE: replace with compiler options when CW9 is avaiable.
    AppJoystickInput joystickInput;
    TwInputHandle inputQueueP;
    Int32 *inputFormatP;
    
    //! Indicates which game menu item is selected.
    Int16 gameMenuSelected;
    Int16 pad5[1];
    
    //! Controls when the next cycle starts
    UInt32 cycleNextTime;
    UInt32 cycleDurationTime;
    
    //! Gauges
    GaugeFIFOType * SPFGauge;	// Seconds per frame
    GaugeFIFOType * FPSGauge;	// Frames per second
    FPSType fps;
} App;

static App GameApp;

//! Set to true if TapWave support is detected.  This means that those APIs
//! can be used to widen the screen and read the joystick.
static Boolean TapWaveSupport;

//! Array of input information the app is interested in.  Other values 
//! like buttons could also be included here.
//!
//! NOTE: This structure must be four bytes aligned because it is used by ARM based
//! API.
static Int32 InputFormats[] = {twInputNavX, twInputNavY};


//static const RGBColorType ColorGameMenu = { 0, 239, 211, 16 };
static TwGfxPackedRGBType ColorGameMenu;


static Int32 GTimeOut = 0;


/*! \brief  Mask the keys to reduce keyDownEvents from being sent.

This app does not use the events but polls the keys instead.  This also
sets up the joystick for analog polling.

\see HostUnmaskKeys

*/
void
HostMaskKeys()
{
    if (!GameApp.isInputMasked)
    {
        // Set the keys we poll to not generate events.  This saves cpu cycles
        // by avoiding the events flowing through the event loop which we will 
        // ignore anyways.
        KeySetMask(~keysAllowedMask);
        
        
        if (TapWaveSupport)
        {
            // Open an input queue for the joystick.  The queue is polled before
            // advancing each game cycle.
            TwInputOpen(&GameApp.inputQueueP, "twinput", "r");
            
            // The input format must be four byte aligned.  A 
            // simple way to do this for all compilers is to allocate it and
            // move the data into it.  Metrowerks compilers (>= version 9)
            // can use "#pragma options align=4".  Gcc compilers can use 
            // "static Int32 InputFormats[] __attribute__ ((aligned (4))) = {...};"
            GameApp.inputFormatP = MemPtrNew(sizeof(InputFormats));
            MemMove(GameApp.inputFormatP, InputFormats, sizeof(InputFormats));
            TwInputSetFormat(GameApp.inputQueueP, GameApp.inputFormatP, sizeof(InputFormats));
            
            // Activating the queue stops the joystick from generating
            // keyDownEvents.  If this is not done, then every direction
            // visited while polling will cause a corresponding keyDownEvent
            // in that direction, and if the polling duration exceeds 
            // the keyDown repeat duration, then a repeating keyDownEvent 
            // will be generated too.
            TwInputActivate(GameApp.inputQueueP);
        }
        
        
        GameApp.isInputMasked = true;
    }
    
    return;
}


/*! \brief  Unmask the keys so they can generate events again.

Also, closes the joystick so it can generate events again.

\see HostMaskKeys
*/
void
HostUnmaskKeys()
{
    if (GameApp.isInputMasked)
    {
        // Set the keys we poll to not generate events.  This saves cpu cycles.
        KeySetMask(keyBitsAll);
        
        if (TapWaveSupport)
        {
            TwInputClose(GameApp.inputQueueP);
            
            MemPtrFree(GameApp.inputFormatP);
        }
        
        GameApp.isInputMasked = false;
    }
}


/*! \brief	Send a data stream to the rumbler.

Used at the same time that the buffer is transferred to the screen, to keep 
the tactile stream in sync with the visual stream.
*/
typedef struct
{
	void * data;	// Volume & duration pairs.
	Int32 size;
} EffectInfo;

void
HostPlayRumble(short int effect)
{
    // A real scheme would important data from resources.
    
    // A single, short bump.
    UInt8 EffectBump[] = 
    {
    	128 + 64, 6, 0, 50
	};
    EffectInfo EffectData[1];
    EffectData[0].data = EffectBump;
    EffectData[0].size = sizeof(EffectBump);

    // Send to the rumbler 
    TwDeviceControl(GameApp.rumblerH, 'play', 
    	EffectData[effect].data, 
    	EffectData[effect].size);
}


/*! \brief Create an offscreen buffer of the requested size.

Any existing buffer is freed.  This buffer is also freed by AppStop
before the app exits.

\see HostOpenScreenBuffer
\see HostDrawObject
\see HostCloseScreenBuffer

*/
void
HostNewScreenBuffer(short int buffer_width,
    short int buffer_height)
{
    TwGfxSurfaceInfoType surfInfo;
    Err error;


    if (GameApp.screenBufferH)
    {
        TwGfxFreeSurface(GameApp.screenBufferH);
        GameApp.screenBufferH = NULL;
    }

    // Setup the screenBuffer.  Clear it for use.
    surfInfo.size = sizeof(surfInfo);
    surfInfo.width = buffer_width;
    surfInfo.height = buffer_height;
    surfInfo.location = twGfxLocationAcceleratorMemory;
    surfInfo.pixelFormat = twGfxPixelFormatRGB565;
    error = TwGfxAllocSurface(GameApp.GFX, &GameApp.screenBufferH, &surfInfo);

    GameApp.screenBufferP = NULL;
}

/*! \brief	Set draws to occur at the screen buffer

\see HostNewScreenBuffer
\see HostDrawObject
\see HostDrawGameMenu
\see HostDrawBuffer
\see HostCloseScreenBuffer
*/
void
HostOpenScreenBuffer(void)
{
    ErrNonFatalDisplayIf(GameApp.screenBufferH == NULL ||
        GameApp.screenBufferP != NULL, "Open screen");

    // Set the draw window to the screenBuffer so that all the draw operations act on the
    // screenBuffer which we draw later.
    if (GameApp.customBlitting)
        TwGfxLockSurface(GameApp.screenBufferH, (void**)&GameApp.screenBufferP);
}


void
FPSAdd(FPSType * fps, Int32 time)
{
	Int32 tooOld;
	
	
	if (fps->count == 0)
		fps->time_of_last_data_out = time;
	
	else if (fps->count == FPS_DATA_MAX)
		fps->count--;
	
	// discard data that's too old;
#if CPU_TYPE == CPU_x86
	tooOld = time - 10000;
#else
	tooOld = time - 1000;
#endif
	while (fps->count >= 1 && fps->time[fps->count - 1] < tooOld)
		fps->count--;
		
	MemMove(&fps->time[1], &fps->time[0], 
		sizeof(*fps->time) * fps->count);
	
    fps->count++;
	fps->time[0] = time;
}


void
DrawGauges(short int destX,
    short int destY)
{
    Int32 time;
	
	
	// Draw Gauges.  This adds a variable amount of time to the start 
	// of the game cycle.  This should probably be moved to the end of the cycle.
	GaugeDraw(GameApp.SPFGauge, GameApp.screenBufferH, 
		TwGfxComponentsToPackedRGB(0xff, 0, 0),
		destX, 315 + destY);
	
	time = TimGetTicks();
	FPSAdd(&GameApp.fps, time);
	if (time - GameApp.fps.time_of_last_data_out >= 1000)
	{
		GameApp.fps.time_of_last_data_out = time;
        GaugeAdd(GameApp.FPSGauge, GameApp.fps.count);

	}
	GaugeDraw(GameApp.FPSGauge, GameApp.screenBufferH, 
		TwGfxComponentsToPackedRGB(0, 0xff, 0),
		destX, 285 + destY);
}


/* \brief	Draw the offscreen buffer to the screen.

Used after all drawing is done and typically after the buffer is closed to
transfer the results to the screen.
*/
#define screenTopLeftXOffset		0
#define screenTopLeftYOffset		0
void
HostDrawBuffer(short int destX,
    short int destY,
    short int sourceX,
    short int sourceY,
    short int sourceWidth,
    short int sourceHeight)
{
    TwGfxRectType sourceBounds;
    TwGfxPointType destPoint;
	
	DrawGauges(sourceX, sourceY);
    
    sourceBounds.x = sourceX;
    sourceBounds.y = sourceY;
    sourceBounds.w = sourceWidth;
    sourceBounds.h = sourceHeight;
    destPoint.x = screenTopLeftXOffset + destX;
    destPoint.y = screenTopLeftYOffset + destY;

    // Copy the screenBuffer.  Have it wait until the 
    // next VSync to copy cleanly visually, and to give
    // improve performance.
    TwGfxBitBlt(GameApp.displaySurface, &destPoint,
                GameApp.screenBufferH, &sourceBounds);
}

/*! \brief Get the width of the Palm bitmap.

The result is in the native coordinate system (480x320).
NOTE: It's probably worthwhile to simply cache this information
after allocating the bitmap.

\see HostDrawObject
*/

int
HostGetBitmapWidth(int bitmapNumber)
{
	TwGfxSurfaceInfoType surfInfo;
	
    surfInfo.size = sizeof(surfInfo);
    TwGfxGetSurfaceInfo(GameApp.pictureBitmapP[bitmapNumber], &surfInfo);
    
    return surfInfo.width;
}


/*! \brief Get the height of the Palm bitmap.

The result is in the native coordinate system (480x320).
NOTE: It's probably worthwhile to simply cache this information
after allocating the bitmap.

\see HostDrawObject
*/

int
HostGetBitmapHeight(int bitmapNumber)
{
	TwGfxSurfaceInfoType surfInfo;
	
    surfInfo.size = sizeof(surfInfo);
    TwGfxGetSurfaceInfo(GameApp.pictureBitmapP[bitmapNumber], &surfInfo);
    
    return surfInfo.height;
}


/*! \brief Draw the picture directly to the offscreen buffer.

This is a private function called when customBlitting is true.
It is intended as an example of how to get at the offscreen buffer's bits.

\see HostDrawObject
*/
static void
FastDrawPicture(int picture,
   int x,
   int y)
{
   UInt8 p;
   Int32 screenWidth = GameApp.screenWidth;


   if (GameApp.pictureIsTransparent[picture])
   {
      UInt8 *src;
      UInt8 *dest;
      UInt8 index = (UInt8) GameApp.pictureTransparencyIndex[picture];
      int row;

      src = GameApp.pictureBitmapBitsP[picture];
      dest = &GameApp.screenBufferP[y * GameApp.screenHeight + x];

      for (row = 15; row > 0; row--)
      {
         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         p = *src++;
         if (p != index)
            *dest = p;
         dest++;

         (UInt8 *) dest += screenWidth;
      }
   }
   else
   {
      UInt32 *src;
      UInt32 *dest;
      int row;


      src = GameApp.pictureBitmapBitsP[picture];
      dest = (UInt32 *) & GameApp.screenBufferP[y * GameApp.screenHeight + x];

      // Draw 15x15 16 bit bitmap quickly.
      for (row = 15; row > 0; row--)
      {
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
          *src++ = *dest++;
#if 0
          *((UInt16 *) src) = *((UInt16 *) dest);
          ((UInt16 *) src)++;
          ((UInt16 *) dest)++;
#endif
          (UInt8 *) dest += screenWidth;
      }

   }

}


/*! \brief	Draw an object at a specified location and mode

HostOpenScreenBuffer must be called first.

\see HostOpenScreenBuffer
\see HostDrawGameMenu
\see HostCloseScreenBuffer

*/
void
HostDrawObject(int bitmapNumber,
    short int x,
    short int y)
{
	TwGfxRectType sourceBounds;
	TwGfxPointType destPoint;
	Err err;

    ErrNonFatalDisplayIf(GameApp.pictureBitmapP[bitmapNumber] == 0, "Unhandled object image");

    if (GameApp.customBlitting)
    {
        FastDrawPicture(bitmapNumber, x, y);
    }
    else
    {
        sourceBounds.x = 0;
        sourceBounds.y = 0;
        sourceBounds.w = HostGetBitmapWidth(bitmapNumber);
        sourceBounds.h = HostGetBitmapHeight(bitmapNumber);
        destPoint.x = x;
        destPoint.y = y;
        
        // Copy the source window (contains the image to draw) to the draw window.
        err = TwGfxBitBlt(GameApp.screenBufferH, &destPoint, GameApp.pictureBitmapP[bitmapNumber], &sourceBounds);
	    ErrNonFatalDisplayIf(err != errNone, "TwGfxBitBlt problem");
    }
}


/*! \brief Draw the game menu visible while the game is paused.

Usually called by the game when it knows it is paused.  This function 
is in the Host side so it can use the Palm OS fonts and drawing API.

\see HostOpenScreenBuffer
\see HostDrawGameMenu
\see HostCloseScreenBuffer

*/
#define FontAscent 4    /* the space between the top of a captial 
                           letter and the font box, sometimes occupied 
                           by accents. */
void
HostDrawGameMenu(int left,
    int top,
    int width,
    int height)
{
    int i;
    Int32 textLength;
    Int32 x;
    Int32 y;
    Int32 lineHeight;
    Int32 itemWidth;
    Int32 itemWidest = 0;
    TwGfxPointType lineEnds[4];
    
    
    // Pushing the state saves the current graphic modes before they
    // are set to what is needed.  They are popped after the drawing.
    // Pushing is a slow but complete method.  The alternative is to 
    // get and remember each setting.  There is a very limited number 
    // pushes allowed so do not nest.
    
    lineHeight = FontGetLineHeight();
//    lineHeight += lineHeight / 2;

    // Center the items vertically
    top += (int) (height - lineHeight * GameMenuCount - lineHeight / 3) / 2;

    for (i = 0; i < GameMenuCount; i++)
    {
        textLength = (Int16) StrLen(GameMenuText[i]);
        
        // Each item is drawn centered.
        itemWidth = 0;
        FontGetCharsInWidth(GameMenuText[i], &textLength, &itemWidth, NULL);
        if (itemWidth > itemWidest)
            itemWidest = itemWidth;
        x = left + width / 2 - itemWidth / 2;
        y = top + lineHeight * i;
        FontDrawChars(GameMenuText[i], textLength, 
            GameApp.screenBufferH, x, y);
    }
    
    // Show the selected item.  For now draw a line above and below
    // the item to indicate selection.
    x = left + width / 2 - itemWidest / 2;
    y = top + lineHeight * GameApp.gameMenuSelected + FontAscent;
    lineEnds[0].x = x;
    lineEnds[0].y = (Coord) (y - 1);
    lineEnds[1].x = (Coord) (x + itemWidest);
    lineEnds[1].y = (Coord) (y - 1);
    lineHeight = (lineHeight * 2) / 3;
    lineEnds[2].x = x;
    lineEnds[2].y = (Coord) (y + lineHeight);
    lineEnds[3].x = (Coord) (x + itemWidest);
    lineEnds[3].y = (Coord) (y + lineHeight);
    
    TwGfxDrawLineSegments(GameApp.screenBufferH, lineEnds, 4, ColorGameMenu);
}


/*! \brief	Stop draws to the screen buffer

\see HostOpenScreenBuffer
\see HostNewScreenBuffer
\see HostDrawObject
\see HostDrawBuffer
*/
void
HostCloseScreenBuffer(void)
{
/*	ErrNonFatalDisplayIf(GameApp.currentDrawWindowH == NULL, 
		"Close screen");
*/
    // Now unlock the screen buffer surface. 
    if (GameApp.customBlitting)
    {
        TwGfxUnlockSurface(GameApp.screenBufferH, true);    // DOLATER true needed?
        GameApp.screenBufferP = NULL;
    }
}


/* \brief  Return the time (ticks) to wait until the next game cycle.

\see AppHandleEvent
 */
static Int32
TimeUntillNextPeriod(void)
{
    Int32 timeRemaining = evtWaitForever;

	if (game_exists())
    {
        timeRemaining = (Int32) (GameApp.cycleNextTime - TimGetTicks());
        if (timeRemaining < 0)
        {
            timeRemaining = 0;
        }
    }

    return timeRemaining;
}


/*! \brief An event handler for keyDownEvents.
 *
 * \return    true if the event was handled and should not be passed
 *              to a higher level handler.
 */
SYSTEM_CALLBACK Boolean
AppHandleEvent(EventType * eventP)
{
    Boolean handled = false;

#ifndef OPTION_DELAY_NONE
    GTimeOut = TimeUntillNextPeriod();
#endif

    if (eventP->eType == nilEvent)
    {
        int startTime;
        int endTime;

        startTime = TimGetTicks();
            
        TwInputPoll(GameApp.inputQueueP, (Int32 *) &GameApp.joystickInput, sizeof(GameApp.joystickInput));
        game_advance(KeyCurrentState(), GameApp.joystickInput.joyX, GameApp.joystickInput.joyY);
            
        endTime = TimGetTicks();
        
        GaugeAdd(GameApp.SPFGauge, endTime - startTime);
        handled = true;
    }
    else if (eventP->eType == winExitEvent)
    {
        game_set_pause(game_pause);
        handled = false;
    }
    // Notice when drawing to the MainForm is safe again. Safe means
    // that our window is on top, and therefore not obscured.
    else if (eventP->eType == winEnterEvent)
    {
        game_set_pause(game_run);
        handled = false;
    }
    // If the launcher key is pressed, pause the game. 
    // If the game was already paused, then switch to the launcher.
    else if (eventP->eType == appStopEvent && game_get_pause() == game_run)
    {
        game_set_pause(game_pause);
        handled = true;
    }
    // Consume the hard keys, which other SysHandleEvent will see and
    // decide to switch to the app assigned to the key.
    else if (eventP->eType == keyDownEvent)
    {
        // Both the joystick and the action keys can generate a vchrPageDown
        if (eventP->data.keyDown.chr == vchrPageDown)
        {
            if (game_get_pause() == game_pause)
            {
                if (GameApp.gameMenuSelected < GameMenuCount - 1) {
                    GameApp.gameMenuSelected++;
                }
                handled = true;
            }
        }
        // Both the joystick and the action keys can generate a vchrPageUp
        else if (eventP->data.keyDown.chr == vchrPageUp)
        {
            if (game_get_pause() == game_pause)
            {
                if (GameApp.gameMenuSelected > 0) {
                    GameApp.gameMenuSelected--;
                }
                handled = true;
            }
        }
        // Act on the selected menu item.
        else if (eventP->data.keyDown.chr == vchrNavSelect ||
        	eventP->data.keyDown.chr == vchrFunction)
        {
            if (game_get_pause() == game_pause)
            {
                if (GameApp.gameMenuSelected == 0)
                {
                    game_set_pause(game_run);
                    
                    // Adjust the cycleNextTime which the pause changes.
                    GameApp.cycleNextTime = TimGetTicks() + GameApp.cycleDurationTime;
                }
                else if (GameApp.gameMenuSelected == 1)
                {
                    EventType newEvent;
                    // Enqueue an appStopEvent to exit this app. The
                    // OS switches to the last app, which typically is
                    // a launcher.
                	MemSet(&newEvent, sizeof(newEvent), 0);
                	newEvent.eType = appStopEvent;
                	EvtAddEventToQueue(&newEvent);
                }
            }

            handled = true;
        }
    }

    return handled;
}



/*! \brief The event loop for the aplication.  

The primary functions is to wait until the next game cycle and then
call the game to do it's thing.  But all other device input and activity 
is processed here too, like switching apps, turning off the device, 
alarms, and so on.
*/
static void
AppEventLoop(void)
{
    // Wait until the next game period.  This call either returns
    // immeadiately with an event, or blocks until the time requested
    // has passed, in which case it returns a nilEvent.
    // 
    // Palm OS does not have timers or threads or vertical syncs
    // available to signal a time to draw.  It only has machine ticks
    // which occur 1000 times per second while the device is awake.
    // 
    // To draw frames at a consistent interval we draw and then
    // perform work for the next frame that hopefully takes less time
    // than the desired frame rate permits.  If we finish early then
    // we wait the needed amount of ticks.  Otherwise we wait zero
    // ticks (but still allow the OS time for housekeeping).
    // 
    // An interesting topic is what to do when to much time is spent
    // preparing the next frame.  The two options are to do less work
    // or to slip a frame.
    // 
    // Doing less work can mean drawing less detail, less effects, or
    // lower quality drawing.  The idea is to not let the person
    // notice.  Applying lower quality to new visual elements can be
    // better than reducing something already seen.
    // 
    // Slipping a frame can be done occasionally without a noticeable
    // effect.  And when enough slippage happens it's the only way to
    // avoid a "rubberband" effect catching back up to the expected
    // time.  Skipping the drawing but not the world update is a good
    // way to recover some time but keep the world flowing smoothly.
    // It is a poor way to recover a lot of time because the player
    // feels out of control.
    // 
    // Not tracking the ticks, but simply waiting a constant time
    // makes the frame rate subject to the variability of the game
    // cycle.
    // 
    // It is important to qualify all game cycles for a typical game.
    // The game should have a mode to deterministically play through.
    // The number of ticks for each game cycle should be measured.
    // The average must be slightly less than the desired frame rate,
    // although a graph is much more informative.  The worst cases
    // should be recorded and replayed and examined to improve the
    // performance.  The worse game cycles are the most important,
    // because they cause the noticeable stuttering in otherwise silky
    // smooth games.
    //
    // The app stays in the loop above until an appStopEvent is
    // received by the user switching to another app.  Users of Palm
    // apps do not think of exiting an app, they simply go to another
    // app, and the current app gets an appStopEvent.

    TwAppRun(&GTimeOut);
}


/*! \brief Load the graphic resources needed for the game.

Load the graphics into memory.  Custom blitting info is setup if needed too.  This
version uses gzipped BMP bitmaps.

*/
static void
AppLoadGraphics(App * app)
{
    int i;
    Err error;

    
	// Keep the Object graphics locked because they are frequently used
    /* Bitmaps can be either Palm specific resources or custom resources.

       Palm specific resources are fine because there is tool support and 
       the blitting code is already written and hardware accelerated.  
       For an example using them, see the GoCart example.
       
       This code shows how to use a custom graphics format.  This example
       uses images in the BMP format because it supported by many tools.
       Since BMP images are not compressed when they have more than 256 
       colors, they are compressed using gzip on the desktop.  The
       images are listed in the RCP file and so included into the prc.
       
       Other formats could certainly be used, and might be perform better.
       So explore!
	*/
	
	/* This is a simple scheme that loads all graphics.  A smarter scheme 
	   would load the graphics only as they are needed.  This would reduce
	   memory usage by keeping less graphics around at any given point.  
	   This would also reduce load times by spreading the graphic loads
	   through out time.
	*/
    app->customBlitting = false;
    for (i = 0; i < ObjectBitmapCount; i++)
    {
        void * image;
        void * imageUncompressed;
        Int32 imageSize;
        MemHandle imageH;
        
        imageH = DmGetResource('BMPf', (UInt16) (ObjectBitmapFirst + i));
        image = MemHandleLock(imageH);
        imageSize = MemHandleSize(imageH);
        
        // Some of the images are compressed using gzip.  BMP images > 256 colors
        // are not compressed.  GZip is quite effective, quick and portable and makes a 
        // good choice.
        imageUncompressed = gunzip(image, imageSize);
        
        error = AppReadBMP(app->GFX, &app->pictureBitmapP[i], 
        	imageUncompressed == NULL ? image : imageUncompressed, imageSize);
        
        if (imageUncompressed != NULL)
        	MemPtrFree(imageUncompressed);
        
        MemHandleUnlock(imageH);
        DmReleaseResource(imageH);
        
        // If custom blitting can be used, then cache some of the info on
        // the pictures that will be used often. 
        if (app->customBlitting)
        {
            // Pixels in TwGfxSurfaces are not accessible until the surface is
            // locked.  Leave locked to avoid repeating the locking overhead,
            // but unlock later.
            error = TwGfxLockSurface(app->pictureBitmapP[i], &app->pictureBitmapBitsP[i]);
#if 0
            app->pictureIsTransparent[i] = BmpGetTransparentValue(
               app->pictureBitmapP[i], &app->pictureTransparencyIndex[i]);
#endif
        }
    }

}


/*! \brief Obtain and configure resources needed to start the game.

Sets the screen to 16 bit color mode.

\see AppLoadGraphics

*/
static Err
AppStart(App * app)
{
    Err error;
    TwGfxInfoType screenInfo;
    UInt32 featureValue;

    TapWaveSupport = (Boolean) (FtrGet(twFtrCreator, twFtrAPIVersion, &featureValue) == errNone);

	SysSetOrientation(sysOrientationLandscape);
	PINSetInputAreaState(pinInputAreaHide);
	StatHide();
	TwAppStart(AppHandleEvent);
    
    app->isInputMasked = false;
    app->joystickInput.joyX = 0;
    app->joystickInput.joyY = 0;
    
    screenInfo.size = sizeof(screenInfo);
    error = TwGfxOpen(&app->GFX, &screenInfo);
    if (error) return error;

    app->screenWidth = screenInfo.displayWidth;
    app->screenHeight = screenInfo.displayHeight;
    
    error = TwGfxGetDisplaySurface(app->GFX, &app->displaySurface);

    // One goal of the game should be to display something as soon as possible.  If starting
    // the game or loading the graphics takes a noticeable time, it's probably good to display
    // a splash screen first.  This makes the app feel responsive.

    FontInit(app->GFX);
    
	AppLoadGraphics(app);

    ColorGameMenu = TwGfxComponentsToPackedRGB(239, 211, 16);


    // Now set up game info specific to this session.

    app->screenBufferH = NULL;
    
    app->gameMenuSelected = 0;
    
    // Do a frame rate of 33 fps.
    app->cycleDurationTime = SysTicksPerSecond() / 33;
    
    
    TwDeviceOpen(&GameApp.rumblerH, "vibrator0", "w");
    
    GameApp.SPFGauge = GaugeOpen(screenInfo.displayWidth);
    GameApp.FPSGauge = GaugeOpen(screenInfo.displayWidth);
    
    app->fps.count = 0;    

    
    // Allocate a screen buffer one tile larger in both directions. 
    // Scrolling can cause part of the tiles on opposite ends to be 
    // visible at once.  Clipping is done when copying from the 
    // screen buffer to the screen.
    HostNewScreenBuffer((Coord) (app->screenWidth + HostGetBitmapWidth(0)),
        (Coord) (app->screenHeight + HostGetBitmapHeight(0)));
    game_new((int) app->screenWidth, (int) app->screenHeight, 0);
    app->cycleNextTime = TimGetTicks() + app->cycleDurationTime;

    return errNone;                 // no error
}


/*! \brief Cleanup the app by releasing and restoring all resources.

Frees the screen buffer.  Releases all graphics.  Restores the keys.
Closes all open forms.
*/
static void
AppStop(App * app)
{
    int i;

	// Saving isn't implemented, but this is where it would be done.
	// Save the game automatically and restore to where the player left
	// off when the app returns.  The 90% case when starting the app
	// is to resume, using the Main menu is maybe the 10% case, so optimize
	// accordingly.
    game_delete();
    
    TwDeviceClose(GameApp.rumblerH);
    
    // Restore the keys. 
    HostUnmaskKeys();

    // Delete the screenBuffer
    if (GameApp.screenBufferH)
    {
        TwGfxFreeSurface(app->screenBufferH);
        app->screenBufferH = NULL;
    }


    // Unlock and release the locked bitmaps
    for (i = 0; i < ObjectBitmapCount; i++)
    {
        TwGfxFreeSurface(app->pictureBitmapP[i]);
        app->pictureBitmapP[i] = 0;
    }
    
    GaugeClose(GameApp.SPFGauge);
    GaugeClose(GameApp.FPSGauge);
    
    
    // Close the library. This frees up the surfaces we loaded too.
    TwGfxClose(app->GFX);
    app->GFX = NULL;
    app->displaySurface = NULL;

	TwAppStop();
}


/*! \brief The main entry point for the application.

All Palm applications start at PilotMain.
*/
    
UInt32
PilotMain(
    UInt16 cmd,
    MemPtr cmdPBP,
    UInt16 launchFlags)
{
    Err error = errNone;

    /* Palm apps can start for a number of reasons, including to find
       data, to cleanup after a device reset, and so on. Only do
       something for a normal application launch. */
    if (cmd == sysAppLaunchCmdNormalLaunch)
    {
        error = AppStart(&GameApp);

        if (error == errNone)
        {
            AppEventLoop();
            AppStop(&GameApp);
        }
    }

    return error;
}
