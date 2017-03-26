#ifndef DISPLAYDRIVER
#define DISPLAYDRIVER

#include "m68k.h"

// Selectors for the PIN trap dispatcher
#define	pinPINSetInputAreaState			  0
#define pinPINGetInputAreaState			  1
#define pinPINSetInputTriggerState		  2
#define pinPINGetInputTriggerState	 	  3
#define pinPINAltInputSystemEnabled		  4
#define pinPINGetCurrentPinletName		  5
#define pinPINSwitchToPinlet			  6
#define pinPINCountPinlets				  7
#define pinPINGetPinletInfo				  8
#define pinPINSetInputMode				  9
#define pinPINGetInputMode				  10
#define pinPINClearPinletState			  11
#define pinPINShowReferenceDialog		  12
#define pinWinSetConstraintsSize		  13
#define pinFrmSetDIAPolicyAttr			  14
#define pinFrmGetDIAPolicyAttr			  15
#define pinStatHide						  16
#define pinStatShow						  17
#define pinStatGetAttribute				  18

#define pinSysGetOrientation              19
#define pinSysSetOrientation              20
#define pinSysGetOrientationTriggerState  21
#define pinSysSetOrientationTriggerState  22

#define pinStatBarSetIcon				  23
#define pinStatBarGetIcon				  24


// high density trap selectors (D2 values for sysTrapHighDensityDispatch)
#define HDSelectorBmpGetNextBitmapAnyDensity		0
#define HDSelectorBmpGetVersion						1
#define HDSelectorBmpGetCompressionType				2
#define HDSelectorBmpGetDensity						3
#define HDSelectorBmpSetDensity						4
#define HDSelectorBmpGetTransparentValue			5
#define HDSelectorBmpSetTransparentValue			6
#define HDSelectorBmpCreateBitmapV3					7
#define HDSelectorWinSetCoordinateSystem			8
#define HDSelectorWinGetCoordinateSystem			9
#define HDSelectorWinScalePoint						10
#define HDSelectorWinUnscalePoint					11
#define HDSelectorWinScaleRectangle					12
#define HDSelectorWinUnscaleRectangle				13
#define HDSelectorWinScreenGetAttribute				14
#define HDSelectorWinPaintTiledBitmap				15
#define HDSelectorWinGetSupportedDensity			16
#define HDSelectorEvtGetPenNative					17
#define HDSelectorWinScaleCoord						18
#define HDSelectorWinUnscaleCoord					19
#define HDSelectorWinPaintRoundedRectangleFrame		20
#define HDSelectorWinSetScalingMode					21
#define HDSelectorWinGetScalingMode					22
#define HDSelectorInvalid							23//leave this selector at end

//menu keycodes
#define vchrMenu 261
#define vchrCommand 262

//Standard Frame Types
#define noFrame         0
#define simpleFrame     1
#define rectangleFrame  1
#define simple3DFrame   0x0012			 // 3d, frame = 2
#define roundFrame      0x0401          // corner = 7, frame = 1
#define boldRoundFrame  0x0702          // corner = 7, frame = 2
#define popupFrame      0x0205          // corner = 2,  frame = 1, shadow = 1
#define dialogFrame     0x0302          // corner = 3,  frame = 2
#define menuFrame       popupFrame

// Gadget support:
#define formGadgetDrawCmd			0	// paramP is unspecified
#define formGadgetEraseCmd			1	// paramP is unspecified
#define formGadgetHandleEventCmd	2	// paramP is an EventType *for the relevant event.
#define formGadgetDeleteCmd			3	// paramP is unspecified.

// Update code send as part of a frmUpdate event.
#define frmRedrawUpdateCode			0x8000

//drawing methods
enum{
	winPaint = 0,
	winErase,
	winMask,
	winInvert,
	winOverlay,
	winPaintInverse,
	winSwap
};

//ways to lock the lcd / use double buffering
enum{
	winLockCopy,
	winLockErase,
	winLockDontCare
};

//winscreenmode commands
enum{
	winScreenModeGetDefaults = 0,
	winScreenModeGet,
	winScreenModeSetToDefaults,
	winScreenModeSet,
	winScreenModeGetSupportedDepths,
	winScreenModeGetSupportsColor
};

//winscreengetattribute commands
enum{
	winScreenWidth,
	winScreenHeight,
	winScreenRowBytes,
	winScreenDepth,
	winScreenAllDepths,
	winScreenDensity,
	winScreenPixelFormat,
	winScreenResolutionX,
	winScreenResolutionY
};

//constants used by WinSetCoordinateSystem
#define kCoordinatesNative			0
#define kCoordinatesStandard		72
#define kCoordinatesOneAndAHalf		108
#define kCoordinatesDouble			144
#define kCoordinatesTriple			216
#define kCoordinatesQuadruple		288
enum{
	kDensityLow				= 72,
	kDensityOneAndAHalf		= 108,
	kDensityDouble			= 144,
	kDensityTriple			= 216,
	kDensityQuadruple		= 288
};

//bitmap pixel format types
enum{
	pixelFormatIndexed,
	pixelFormat565,
	pixelFormat565LE,
	pixelFormatIndexedLE
};

//Types of object in a dialog box
enum{
	frmFieldObj,
	frmControlObj,
	frmListObj,
	frmTableObj,
	frmBitmapObj,
	frmLineObj,
	frmFrameObj,
	frmRectangleObj,
	frmLabelObj,
	frmTitleObj,
	frmPopupObj,
	frmGraffitiStateObj,
	frmGadgetObj,
	frmScrollBarObj
};

//controlType objects
enum{
	buttonCtl,
	pushButtonCtl,
	checkboxCtl,
	popupTriggerCtl,
	selectorTriggerCtl,
	repeatingButtonCtl,
	sliderCtl,
	feedbackSliderCtl
};

//alert types
enum{
	informationAlert,
	confirmationAlert,
	warningAlert,
	errorAlert
};



//what drawing commands use
extern CPTR currentdrawwindow;

//what is on the display
extern CPTR currentactivewindow;

//virtual gpu ops
void dot();
void rectangle();
void copyrectangle();
void circle();
void bitmap();
void text();

//event handlers
void formeventhandler(CPTR formptr,CPTR eventptr);
void menueventhandler(CPTR menubarptr,CPTR eventptr,CPTR errorptr);
void controleventhandler(CPTR controlptr,CPTR eventptr);
void fieldeventhandler(CPTR fieldptr,CPTR eventptr);

//win functions
void wincreateoffscreenwindow();
void wincreatebitmapwindow();
void windeletewindow();
void wingetbitmap();
void winsetforecolor();
void winsetbackcolor();
void winsettextcolor();
void winsetdrawwindow();
void wineraserectangle();
void windrawrectangle();
void windrawrectangleframe();
void windrawbitmap();
void winscreenmode();
void winscreenlock();
void winscreenunlock();
void wingetdrawwindow();
void windrawpixel();
void wingetdisplaywindow();
void winsetactivewindow();
void winsetclip();
void windrawchars();
void winresetclip();
void wincopyrectangle();
void winpalette();
void winrgbtoindex();
void winpushdrawstate();
void winpopdrawstate();
void wingetdisplayextent();
void winerasewindow();
void windrawline();
void winerasepixel();
void winpaintbitmap();
void winscreengetattribute();//not in trap table (HighDensityDispatch)
void wingetcoordinatesystem();//not in trap table (HighDensityDispatch)
void winsetcoordinatesystem();//not in trap table (HighDensityDispatch)

//bmp functions
void bmpgetbits();
void bmpbitssize();
void bmpgetdensity();//not in trap table (HighDensityDispatch)
void bmpcreate();
void bmpcreatebitmapv3();//not in trap table (HighDensityDispatch)
void bmpgetdimensions();

//font functions
void fntgetfont();
void fntsetfont();
void fntgetfontptr();
void fntbaseline();
void fntcharheight();
void fntcharswidth();
void fntlineheight();

//form functions
void frmgotoform();
void frmgetformptr();
void frmgetwindowhandle();
void frmdispatchevent();
void frmhandleevent();
void frminitform();
void frmdeleteform();
void frmcloseallforms();
void frmsetactiveform();
void frmgetactiveform();
void frmgetactiveformid();
void frmseteventhandler();
void frmsettitle();
void frmdrawform();
void frmcustomalert();
void frmalert();
void frmgetobjectindex();
void frmsetgadgethandler();
void frmgetobjectptr();
void frmhideobject();
void frmsetfocus();
void frmsetcontrolvalue();

//menu
void menuhandleevent();

//uicolor
void uicolorgettableentryrgb();
void uicolortablesettableentry();
void uicolorgettableentryindex();

//field
void fldsetuseable();
void flderasefield();
void fldsettextptr();
void fldsettexthandle();
void flddrawfield();
void fldgettextptr();
void fldgettexthandle();

//controls
void ctlsetusable();

//other
void evtgetpen();
void rctsetrectangle();
void rctptinrectangle();
void evtgetpenbuttonlist();
void highdensitydispatch();
void pinsdispatch();

//part of evtgetevent
void evtgeteventWIN();

//sets up memory and varibles
bool initdisplaydriver();
void deinitdisplaydriver();



//drivers
void appTouchDriver(int x,int y,bool pressed);
void appKeyDriver(char thiskey, bool pressed);

#endif // DISPLAYDRIVER

