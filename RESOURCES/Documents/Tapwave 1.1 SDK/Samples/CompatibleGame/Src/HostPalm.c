/*
	File:			HostPalm.c	

	Description:	This is the host portion of the example.  OS and device specific code to get the input, 
					load graphics, draw specific graphics, save and load games, and so on belongs 
					in here for use by the game.

					This file also provides a TapWave look and feel to the game. This code runs like
					a TapWave app, and can override the game's wishes to provide a best handheld
					interpretation of the game.

					This file is in C like most Palm programs.  It interacts with game.cpp to show
					how to work with C++ programs.

	Author:		

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



#include <PalmOS.h>
#include <DLServer.h>           // Needed for DlkGetSyncInfo (HotSync Name)
#include <FeatureMgr.h>         // Needed to detect ROM versions
#include <TapWave.h>            // For screen and input APIs

#include "host.h"

/* UI and graphics for Palm OS software are often edited using the 
   Constructor tool.  Constructor can be told to describe the UI and
   graphic resources in a header file.  That header is included here.
   */

#include "CompatibleGameRsc.h"

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
const char GameMenuText[GameMenuCount][7] = {
    "Resume",
    "Exit"
};

typedef struct
{
    MemHandle pictureBitmapH[ObjectBitmapCount];
    BitmapPtr pictureBitmapP[ObjectBitmapCount];
    
    //! These are only used if customBlitting is true.  They cache some of the info on
    //! the pictures that will be used often.  Custom blitting means using 
    //! a custom blitter drawing to a frame buffer, versus using the standard
    //! API calls.
    MemPtr pictureBitmapBitsP[ObjectBitmapCount];
    Boolean pictureIsTransparent[ObjectBitmapCount];
    Boolean pad1[3];
    UInt32 pictureTransparencyIndex[ObjectBitmapCount];
    Boolean customBlitting;
    Boolean pad2[3];

    UInt16 soundAmp;            // default sound amplitude
    UInt16 pad3[1];

    Int16 screenWidth;
    Int16 screenHeight;
	
	// This is the offscreen buffer which is copied to the screen.
    WinHandle screenBufferH;    // screenBuffer
    UInt8 * screenBufferP;
    WinHandle currentDrawWindowH;    // Draw window before buffer
    
    
    //! These are used to get the input.  isInputMasked prevents them
    //! from being set or unset repeatedly.  The padding inserted is
	//! to achieve ARM alignment for these data structures.
	//! NOTE: replace with compiler options when CW9 is avaiable.
    Boolean isInputMasked;
    Boolean pad4[3];
    AppJoystickInput joystickInput;
    TwInputHandle inputQueueP;
    Int32 *inputFormatP;
    
    //! Indicates which game menu item is selected.
    Int16 gameMenuSelected;
    Int16 pad5[1];
    
    //! Controls when the next cycle starts
    UInt32 cycleNextTime;
    UInt32 cycleDurationTime;
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


static const RGBColorType ColorGameMenu = { 0, 239, 211, 16 };




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
    UInt16 error;
    RectangleType bounds;
    WinHandle oldDrawWinH;


    if (GameApp.screenBufferH)
    {
        WinDeleteWindow(GameApp.screenBufferH, false);
    }

    // Setup the screenBuffer.  Clear it for use.
    GameApp.screenBufferH =
        WinCreateOffscreenWindow(buffer_width, buffer_height, nativeFormat, &error);

   if (GameApp.customBlitting)
      GameApp.screenBufferP = BmpGetBits(WinGetBitmap(GameApp.screenBufferH));

    oldDrawWinH = WinGetDrawWindow();

    WinSetDrawWindow(GameApp.screenBufferH);
// WinSetBackColor(UIColorGetTableEntryIndex(UIFormFill));
    bounds.topLeft.x = 0;
    bounds.topLeft.y = 0;
    bounds.extent.x = buffer_width;
    bounds.extent.y = buffer_height;
    WinEraseRectangle(&bounds, 0);


    WinSetDrawWindow(oldDrawWinH);
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
        GameApp.currentDrawWindowH != NULL, "Open screen");

    // Set the draw window to the screenBuffer so that all the draw operations act on the
    // screenBuffer which we draw later.
    GameApp.currentDrawWindowH = WinSetDrawWindow(GameApp.screenBufferH);

    WinPushDrawState();
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
    RectangleType sourceBounds;

    sourceBounds.topLeft.x = sourceX;
    sourceBounds.topLeft.y = sourceY;
    sourceBounds.extent.x = sourceWidth;
    sourceBounds.extent.y = sourceHeight;

    // Copy the screenBuffer if there is something 
    WinCopyRectangle(GameApp.screenBufferH, 0, &sourceBounds, 
		(Coord) (screenTopLeftXOffset + destX),
        (Coord) (screenTopLeftYOffset + destY), winPaint);
}

/*! \brief Get the width of the Palm bitmap.

The result is in the Palm coordinate system (low density (160x160)).

\see HostDrawObject
*/

int
HostGetBitmapWidth(int bitmapNumber)
{
    Coord width;

    BmpGetDimensions(GameApp.pictureBitmapP[bitmapNumber], &width, NULL, NULL);
    // The bitmap width is returned in terms of pixels, but the coordinate system is in low
    // density, transform appropriately.
    width =
        (Coord) (((Int32) width * kDensityLow) /
        BmpGetDensity(GameApp.pictureBitmapP[bitmapNumber]));
    return width;
}


/*! \brief Get the height of the Palm bitmap.

The result is in the Palm coordinate system (low density (160x160)).

\see HostDrawObject
*/

int
HostGetBitmapHeight(int bitmapNumber)
{
    Coord height;

    BmpGetDimensions(GameApp.pictureBitmapP[bitmapNumber], NULL, &height, NULL);

    // The bitmap height is returned in terms of pixels, but the coordinate system is in low
    // density, transform appropriately.
    height = (Coord) (((Int32) height * kDensityLow) /
        BmpGetDensity(GameApp.pictureBitmapP[bitmapNumber]));

    return height;
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
   int screenWidth = GameApp.screenWidth;

   // Units are drawn with the color of the owning team "underneath".
// WinDrawBitmap(PictureBitmapPtr[firstTeamBitmap + team_number], screenX, screenY);

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
    ErrNonFatalDisplayIf(GameApp.pictureBitmapP[bitmapNumber] == 0, "Unhandled object image");

    if (GameApp.customBlitting)
    {
        FastDrawPicture(bitmapNumber, x, y);
    }
    else
    {
        // Copy the source window (contains the image to draw) to the draw window.
        WinDrawBitmap(GameApp.pictureBitmapP[bitmapNumber], x, y);
    }
}


/*! \brief Draw the game menu visible while the game is paused.

Usually called by the game when it knows it is paused.  This function 
is in the Host side so it can use the Palm OS fonts and drawing API.

\see HostOpenScreenBuffer
\see HostDrawGameMenu
\see HostCloseScreenBuffer

*/
void
HostDrawGameMenu(int left,
    int top,
    int width,
    int height)
{
    int i;
    Int16 textLength;
    Coord x;
    Coord y;
    Coord lineHeight;
    Coord itemWidth;
    Coord itemWidest = 0;
    

    // Pushing the state saves the current graphic modes before they
    // are set to what is needed.  They are popped after the drawing.
    // Pushing is a slow but complete method.  The alternative is to 
    // get and remember each setting.  There is a very limited number 
    // pushes allowed so do not nest.
    WinPushDrawState();
    WinSetForeColorRGB(&ColorGameMenu, NULL);
    WinSetTextColorRGB(&ColorGameMenu, NULL);
    FntSetFont(largeFont);
    WinSetDrawMode(winOverlay);
    
    lineHeight = FntLineHeight();
    lineHeight += lineHeight / 2;

    // Center the items vertically
    top += (height - lineHeight * GameMenuCount - lineHeight / 3) / 2;

    for (i = 0; i < GameMenuCount; i++)
    {
        textLength = (Int16) StrLen(GameMenuText[i]);
        
        // Each item is drawn centered.
        itemWidth = FntCharsWidth(GameMenuText[i], textLength);
        if (itemWidth > itemWidest)
            itemWidest = itemWidth;
        x = left + width / 2 - itemWidth / 2;
        y = top + lineHeight * i;
        WinPaintChars(GameMenuText[i], textLength, x, y);
    }
    
    // Show the selected item.  For now draw a line above and below
    // the item to indicate selection.
    x = left + width / 2 - itemWidest / 2;
    y = top + lineHeight * GameApp.gameMenuSelected;
    WinDrawLine(x, (Coord) (y - 1), (Coord) (x + itemWidest), (Coord) (y - 1));
    lineHeight = (lineHeight * 2) / 3;
    WinDrawLine(x, (Coord) (y + lineHeight), (Coord) (x + itemWidest), (Coord) (y + lineHeight));
    

    WinPopDrawState();
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
    // Now restore the draw window 
    WinPopDrawState();
    WinSetDrawWindow(GameApp.currentDrawWindowH);
    GameApp.currentDrawWindowH = NULL;
}


/*! \brief Resize the form to fit the screen.

Check if screen is a different size and adjust the form and it's 
active area gadget (which acts as it's view), to match.

If TapWave APIs are present, use them to set the screen to full landscape width.
*/

static void
MainFormResize(FormType * formP //!  The form to resize
    )
{
    RectangleType activeAreaBounds;
    RectangleType formBounds;
    UInt32 featureValue;
    WinHandle draw;


    // Find the screen bounds. 
    // Here we check if the TapWave API exists, and if so, use it to 
    // set the screen to be wider.  We also widen the gadget that we 
    // draw to, as well as the form that the gadget is in (which would 
    // otherwise clip it).
    TapWaveSupport = (Boolean) (FtrGet(twCreatorID, twFtrAPIVersion, &featureValue) == errNone);
    if (TapWaveSupport)
    {
        // Set the screen to use the entire width of the screen. 
        // Graffiti becomes unavailable, but this is fine since 
        // our input is only joystick and buttons.
        draw = WinGetDrawWindow();
		SysSetOrientation(sysOrientationLandscape);
	 	PINSetInputAreaState(pinInputAreaHide);
	   	StatHide();
        draw = WinGetDrawWindow();

        // widen the form. 
        // There is no form API to set the bounds, but a form is a window 
        // and there is a window API.
        FrmGetFormBounds(formP, &formBounds);
        formBounds.extent.x = 240;
        WinSetBounds((WinHandle) formP, &formBounds);


        FrmGetObjectBounds(formP, FrmGetObjectIndex(formP, MainActiveAreaGadget),
            &activeAreaBounds);

        // widen the gadget in the form.
        activeAreaBounds.extent.x += 80;
        FrmSetObjectBounds(formP, FrmGetObjectIndex(formP, MainActiveAreaGadget),
            &activeAreaBounds);

    }

    // Cache these often used values.
    FrmGetFormBounds(formP, &formBounds);
    GameApp.screenWidth = formBounds.extent.x;
    GameApp.screenHeight = formBounds.extent.y;

}


/*! \brief The MainForm event handler.
 *
 * \return    true if the event was handled and should not be passed
 *              to a higher level handler.
*/
static Boolean
MainFormHandleEvent(EventType * eventP  //!<  pointer to an EventType structure
    )
{
    FormType *formP;
    Boolean handled = false;
	EventType newEvent;


    if (eventP->eType == keyDownEvent)
    {
        // Both the joystick and the action keys can generate a vchrPageDown
        if (eventP->data.keyDown.chr == vchrPageDown)
        {
            if (game_get_pause() == game_pause)
            {
                if (GameApp.gameMenuSelected < GameMenuCount - 1)
                    GameApp.gameMenuSelected++;
            }
            
            handled = true;
        }
        // Both the joystick and the action keys can generate a vchrPageUp
        else if (eventP->data.keyDown.chr == vchrPageUp)
        {
            if (game_get_pause() == game_pause)
            {
                if (GameApp.gameMenuSelected > 0)
                    GameApp.gameMenuSelected--;
            }
            
            handled = true;
        }
        // Act on the selected menu item.
        else if (eventP->data.keyDown.chr == vchrNavSelect)
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
                    // Enqueue an appStopEvent to exit this app.
                    // The OS switches to the last app, which typically
                    // is a launcher.
                	MemSet(&newEvent, sizeof(newEvent), 0);
                	newEvent.eType = appStopEvent;
                	EvtAddEventToQueue (&newEvent);
                }
            }
            
            handled = true;
        }
        // Frames per second
        if (eventP->data.keyDown.chr == 'f')
        {
//          FPSToggle();
            handled = true;
        }
    }


#if 0
    else if (eventP->eType == menuEvent)
    {
        MainFormDoCommand(eventP->data.menu.itemID);
        return true;
    }

    else if (eventP->eType == frmCloseEvent)
    {
    }

#endif

    else if (eventP->eType == frmOpenEvent)
    {
        formP = FrmGetActiveForm();
        MainFormResize(formP);
        FrmDrawForm(formP);
		WinDrawChars("foo", 3, 10, 10);

        // One goal of the game should be to display something as soon as possible.  If starting
        // the game or loading the graphics takes a noticeable time, it's probably good to display
        // a splash screen first.  This makes the app feel responsive.

        // Allocate a screen buffer one tile larger in both directions. 
        // Scrolling can cause part of the tiles on opposite ends to be 
        // visible at once.  Clipping is done when copying from the 
        // screen buffer to the screen.
        HostNewScreenBuffer((Coord) (GameApp.screenWidth + HostGetBitmapWidth(0)),
            (Coord) (GameApp.screenHeight + HostGetBitmapHeight(0)));
        game_new(GameApp.screenWidth, GameApp.screenHeight, 0);
        GameApp.cycleNextTime = TimGetTicks() + GameApp.cycleDurationTime;
        handled = true;
    }

    else if (eventP->eType == frmUpdateEvent)
    {
        // If the OS requested the redraw, redraw everything, including the form. Since the
        // MainForm has no UI objects other than the gadget, we technically don't need to call
        // FrmDrawForm(), but this is good technique incase someone copies and pastes this code.
        // Since the MainForm has a gadget containing the drawing, we could register a function
        // with the gadget to draw the gadget and then ignore this event here.  FrmDispatchForm()
        // will then handle the frmUpdateEvent, asking the gadget to draw, which will then call
        // the function registered.
        if (eventP->data.frmUpdate.updateCode == frmRedrawUpdateCode)
        {
            FrmDrawForm(FrmGetFormPtr(MainForm));

//          GameStateDrawEverything();

            handled = true;
        }
    }

    return handled;
}


/* \brief  Return the time (ticks) to wait until the next game cycle.

\see AppEventLoop
 */
static Int32
TimeUntillNextPeriod(void)
{
    Int32 timeRemaining = evtWaitForever;


#ifdef OPTION_DELAY_NONE
    return 0;
#endif

	if (game_exists())
    {
        
        timeRemaining = (Int32) (GameApp.cycleNextTime - TimGetTicks());
        if (timeRemaining < 0)
            timeRemaining = 0;
    }


    return timeRemaining;
}


/*! \brief Handle frmLoadEvents by loading the right app form and
setting it's form event handler callback.

All Palm UI forms need to set their event handler callback here.

*/
static Boolean
AppHandleEvent(EventType * eventP)
{
    UInt16 formId;
    FormType *formP;

    if (eventP->eType == frmLoadEvent)
    {
        // Load the form resource.
        formId = eventP->data.frmLoad.formID;
        formP = FrmInitForm(formId);
        FrmSetActiveForm(formP);

        // Set the event handler for the form.  The handler of the currently active form is called
        // by FrmHandleEvent each time is receives an event.
        switch (formId)
        {
            case MainForm:
                FrmSetEventHandler(formP, MainFormHandleEvent);
                break;

        }
        return (true);
    }
    return (false);
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
    UInt16 error;
    EventType event;

    do
    {
        // Wait until the next game period.  This call either returns immeadiately with an event,
        // or blocks until the time requested has passed, in which case it returns a nilEvent.
        // 
        // Palm OS does not have timers or threads or vertical syncs available to signal a time to
        // draw.  It only has machine ticks which occur 100 times per second while the device is
        // awake.
        // 
        // To draw frames at a consistent interval we draw and then 
        // perform work for the next frame that hopefully takes less 
        // time than the desired frame rate permits.  If we finish 
        // early then we wait the needed amount of ticks.  Otherwise 
        // we wait zero ticks (but still allow the OS time for 
        // housekeeping).
        // 
        // An interesting topic is what to do when to much time is spent 
        // preparing the next frame.  The two options are to do less work 
        // or to slip a frame.
        // 
        // Doing less work can mean drawing less detail, less effects, 
        // or lower quality drawing.  The idea is to not let the person 
        // notice.  Applying lower quality to new visual elements can 
        // be better than reducing something already seen.
        // 
        // Slipping a frame can be done occasionally without a noticeable 
        // effect.  And when enough slippage happens it's the only way to 
        // avoid a "rubberband" effect catching back up to the expected 
        // time.  Skipping the drawing but not the world update is a 
        // good way to recover some time but keep the world flowing 
        // smoothly.  It is a poor way to recover a lot of time because 
        // the player feels out of control.
        // 
        // Not tracking the ticks, but simply waiting a constant time 
        // makes the frame rate subject to the variability of the 
        // game cycle.
        // 
        // It is important to qualify all game cycles for a typical 
        // game.  The game should have a mode to deterministically 
        // play through.  The number of ticks for each game cycle 
        // should be measured.  The average must be slightly less than 
        // the desired frame rate, although a graph is much more 
        // informative.  The worst cases should be recorded and replayed 
        // and examined to improve the performance.  The worse game 
        // cycles are the most important, because they cause the 
        // noticeable stuttering in otherwise silky smooth games.
        EvtGetEvent(&event, TimeUntillNextPeriod());


        // PalmOS does not clip draws to windows under other windows. 
        // Instead drawing to obscured windows must halt until they are 
        // no longer obscured. 
        // 
        // Note: In the case of another, nested event loop, an winExitEvent 
        // is not received by this event loop, but by the other one instead.
        if (event.eType == winExitEvent)
        {
            if (event.data.winExit.exitWindow == (WinHandle) FrmGetFormPtr(MainForm))
            {
                game_set_pause(game_pause);
            }
        }

        // Notice when drawing to the MainForm is safe again.  Safe means that our window is on
        // top, and therefore not obscured.
        else if (event.eType == winEnterEvent)
        {
            if (event.data.winEnter.enterWindow == (WinHandle) FrmGetFormPtr(MainForm) &&
                event.data.winEnter.enterWindow == (WinHandle) FrmGetFirstForm())
            {
                game_set_pause(game_run);
            }
        }


        // If it's time, go to the next time period.  The time between the event leaving
        // EvtGetEvent and advancing the game cycle should be as small and consistent as possible, 
        // so this is done here instead of in the MainFormHandleEvent().
        else if (event.eType == nilEvent && TimeUntillNextPeriod() == 0)
        {
            if (TapWaveSupport)
            {
                TwInputPoll(GameApp.inputQueueP, (Int32 *) &GameApp.joystickInput, sizeof(GameApp.joystickInput));
            }
            
            game_advance(KeyCurrentState(), GameApp.joystickInput.joyX, 
                GameApp.joystickInput.joyY);
            continue;
        }

        // Consume the hard keys, which other SysHandleEvent will see and decide to switch to the
        // app assigned to the key.
        else if (event.eType == keyDownEvent)
        {
            // Key events aren't used.  Instead key states are polled each game cycle. Do not
            // consume keys that are used to turn on the device because the user isn't trying to
            // play the game but trying to get to the app assigned to the key.
            if (event.data.keyDown.chr >= hard1Chr && event.data.keyDown.chr <= hard4Chr &&
                !(event.data.keyDown.modifiers & poweredOnKeyMask))
            {
                continue;
            }

            // If the launcher key is pressed, pause the game. 
            // If the game was already paused, then switch to the launcher.
            if (event.data.keyDown.chr == launchChr)
            {
                if (event.data.keyDown.modifiers & poweredOnKeyMask)
                {
                    // fall through to SysHandleEvent to switch apps
                }
                else if (game_get_pause() == game_run)
                {
                    game_set_pause(game_pause);
                    continue;
                }
                else if (game_get_pause() == game_pause)
                {
                    // fall through to SysHandleEvent to switch apps
                }
            }
        }



        if (!SysHandleEvent(&event))

            if (!MenuHandleEvent(0, &event, &error))

                if (!AppHandleEvent(&event))

                    FrmDispatchEvent(&event);

    }
    // The app stays in the loop above until an appStopEvent is received by the user switching to
    // another app.  Users of Palm apps do not think of exiting an app, they simply go to another
    // app, and the current app gets an appStopEvent.
    while (event.eType != appStopEvent);
}


/*! \brief Load the graphic resources needed for the game.

Load the graphics into memory.  Custom blitting info is setup if needed too.  This
version uses Palm native bitmaps for storage and drawing ease.

*/
static void
AppLoadGraphics(App * app)
{
    WinHandle oldDrawWinH;
    int i;

    
	// Keep the Object graphics locked because they are frequently used
    /* Bitmaps can be either Palm specific resources or custom resources.

       Palm specific resources are good because there is tool support and 
       the blitting code is already written and sometimes hardware accelerated.

       Palm specific bitmaps are usually copied from a paint program and pasted 
       into a resource file edited by Constructor.  That resource file is then 
       combined with the object code to produce the prc.  When the program is 
       running, those bitmaps must be found in the PRC in the storage heap 
       and locked down so they cannot move.  Since 
       this takes time, this is done once and released only when the program 
       stops.

       Custom resources are good to take advantage of the game's particular 
       graphics and design to avoid overhead.  For instance, the code can avoid 
       clipping, take advantage of fixed size bitmaps, or have a better compression 
       scheme.  Such graphics will need to get placed in resources included into 
       the application's PRC file, or included as an auxillary PDB (data) file. 
       Game code will need to interpret the resources and draw appropriately.

       It's possible to combine the techniques, like reusing the tool support and 
       Palm formats, but having a custom blitter.  The blitter's output should 
       probably be compared offscreen to the native one to confirm the visual 
       results and performance gains for safety and compatibility.

       This example uses the Palm method for brievity.

     */
    /* If loading the graphics takes a noticeable amount of time, consider doing this after drawing 
       the form and then a splash screen. */
    app->customBlitting = false;
    oldDrawWinH = WinGetDrawWindow();
    for (i = 0; i < ObjectBitmapCount; i++)
    {
        app->pictureBitmapH[i] = DmGetResource(bitmapRsc, (UInt16) (ObjectBitmapFirst + i));
        app->pictureBitmapP[i] = MemHandleLock(app->pictureBitmapH[i]);
        
        // If custom blitting can be used, then cache some of the info on
        // the pictures that will be used often. 
        if (app->customBlitting)
        {
            // These pictures are created for the 68K using little endian.
            // But resources could be created using big endian with a different tool.
            app->pictureBitmapBitsP[i] = BmpGetBits(app->pictureBitmapP[i]);
            app->pictureIsTransparent[i] = BmpGetTransparentValue(
               app->pictureBitmapP[i], &app->pictureTransparencyIndex[i]);
        }
    }
    WinSetDrawWindow(oldDrawWinH);

}


/*! \brief Obtain and configure resources needed to start the game.

Sets the screen to 16 bit color mode.

\see AppLoadGraphics

*/
static Err
AppStart(App * app)
{
    Boolean colorMode;
    UInt32 depth;


    /* Make sure we are running with 16 bits of color. There are no guarantees of the screen mode. 
       The OS sets the mode to the default before the app starts, but the default is a preference
       that can be set to anything, including monochrome! */
    WinScreenMode(winScreenModeGet, NULL, NULL, &depth, &colorMode);
    if (!colorMode ||
        depth < 16)
    {
        colorMode = true;
        depth = 16;
        WinScreenMode(winScreenModeSet, NULL, NULL, &depth, &colorMode);

        /* handle failure by alerting the user and exiting with an error code? */
    }
    
    app->isInputMasked = false;
    app->joystickInput.joyX = 0;
    app->joystickInput.joyY = 0;
    

	AppLoadGraphics(app);

#if 0
    // Now display the about box and instructions.  This appears automatically the first time the
    // program is run.
#if EMULATION_LEVEL == EMULATION_NONE
#ifndef OPTION_DETERMINISTIC_PLAY
    InfoDisplay();
    FrmHelp(InstructionsStr);
#endif
#endif

#endif


    // Now set up game info specific to this session.

    app->screenBufferH = NULL;
    
    app->gameMenuSelected = 0;
    
    // Do a frame rate of 33 fps.
    app->cycleDurationTime = SysTicksPerSecond() / 33;
    

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
    
    
    // Restore the keys. 
    HostUnmaskKeys();

    // Delete the screenBuffer
    if (app->screenBufferH != NULL)
        WinDeleteWindow(app->screenBufferH, false);


    // Unlock and release the locked bitmaps
    for (i = 0; i < ObjectBitmapCount; i++)
    {
        MemPtrUnlock(app->pictureBitmapP[i]);
        DmReleaseResource(app->pictureBitmapH[i]);
    }


    // Close all the open forms.
    FrmCloseAllForms();
}


/*! \brief The main entry point for the application.

All Palm applications start at PilotMain.
*/
UInt32
PilotMain(UInt16 cmd,
    MemPtr cmdPBP,
    UInt16 launchFlags)
{
    Err error = errNone;


    /* Palm apps can start for a number of reasons, including to find data, to cleanup after a
       device reset, and so on. 
       Only do something for a normal application launch. */
    if (cmd == sysAppLaunchCmdNormalLaunch)
    {
        error = AppStart(&GameApp);
        if (error == errNone)
        {
            FrmGotoForm(MainForm);

            AppEventLoop();

            AppStop(&GameApp);
        }
    }

    return error;
}
