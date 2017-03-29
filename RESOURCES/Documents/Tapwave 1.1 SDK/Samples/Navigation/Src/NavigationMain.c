/*
 * Navigation.c
 *
 * main file for ButtonAndNavigatorTest
 *
 * This wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *
 * Copyright (c) 1999-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 */
 
#include <PalmOS.h>
#include <PalmUtils.h>
#include <PenInputMgr.h>

#include "MathLib.h"


/* Palm OS Glue headers */
#include <PalmOSGlue.h>		/* includes all other glue headers */
#ifndef TxtGlueCharIsSpace
#include <CharAttr.h>		/* needed by TxtGlue.h */
#endif

#include <TapWave.h>
#include <TwVdRumbler.h>

#include "Navigation.h"
#include "NavigationRsc.h"

// override the one from PalmOS 5.0 SDK R3 because in debug mode that version
// uses a trap call which is unimplemented.
#undef FixedDiv
#define	FixedDiv(lhs, rhs)		((((lhs) == 72) && ((rhs) == 108))  ? kFixedTwoThirds : (((FixedType) (lhs) << kFixedBias) / (rhs)))


/*********************************************************************
 * Application-specific Types
 *********************************************************************/

static const Int32 formatAllGameControls[] = {
    twInputPenX,
    twInputPenY,
    twInputPenZ,
	twInputNavX,
	twInputNavY,
	twInputNavR,
	twInputNavTheta,
    twInput4Way,
    twInput8Way,
    twInputActionA,
    twInputActionB,
    twInputActionC,
    twInputActionD,
    twInputTriggerA,
    twInputTriggerB,
    twInputNavUp,
    twInputNavDown,
    twInputNavLeft,
    twInputNavRight,
	twInputNavSelect,
	twInputFunction,
    twInputHard1,
    twInputHard2,
    twInputHard3,
    twInputHard4
};

typedef struct MyTwEventTag {
	Int32 penX;
	Int32 penY;
	Int32 penZ;
	Int32 navX;
	Int32 navY;
	Int32 navR;
	Int32 navTheta;
    Int32 nav4Way;
    Int32 nav8Way;
    Int32 actionA;
    Int32 actionB;
    Int32 actionC;
    Int32 actionD;
    Int32 triggerLeft;
    Int32 triggerRight;
    Int32 navUp;
    Int32 navDown;
    Int32 navLeft;
    Int32 navRight;
    Int32 navSelect;
    Int32 function;
    Int32 hard1;
    Int32 hard2;
    Int32 hard3;
    Int32 hard4;
} MyTwEventType;

#define MAX_POINTS_SHIFT 2
#define MAX_POINTS (1 << MAX_POINTS_SHIFT)

static Int32 pointsIndex;
static Int32 pointsX[MAX_POINTS];
static Int32 pointsY[MAX_POINTS];
static Int32 pointsSumX;
static Int32 pointsSumY;

/*********************************************************************
 * Entry Points
 *********************************************************************/

static Boolean PollTwInput(FormType *formP);
static void * GetObjectPtr(FormType *formP, UInt16 objectID);


/*********************************************************************
 * Global variables
 *********************************************************************/

/* g_prefs
 * cache for application preferences during program execution */
MyTwEventType g_lastEvent;
MyTwEventType *g_currentEventP = NULL;
UInt32 g_keyLastState;
UInt32 g_keyCurrentState;
TwInputHandle g_input;
UInt16 MathLibRef;
Boolean gNavReset;

/*********************************************************************
 * Internal Constants
 *********************************************************************/

/* Define the minimum OS version we support */
#define ourMinVersion    sysMakeROMVersion(5,2,0,sysROMStageDevelopment,0)
#define kPalmOS20Version sysMakeROMVersion(2,0,0,sysROMStageDevelopment,0)


/*********************************************************************
 * Utility Functions
 *********************************************************************/
 
static void PrvByteSwap4(void *addrP)
{
    UInt8 byte[4];
    byte[0] = *((UInt8*)addrP);
    byte[1] = *(((UInt8*)addrP)+1);
    byte[2] = *(((UInt8*)addrP)+2);
    byte[3] = *(((UInt8*)addrP)+3);
    *((UInt8*)addrP) = byte[3];
    *(((UInt8*)addrP)+1) = byte[2];
    *(((UInt8*)addrP)+2) = byte[1];
    *(((UInt8*)addrP)+3) = byte[0];
}

static void PrvAddPointGetAverage(Int32 *xP, Int32 *yP)
{
    pointsSumX -= pointsX[pointsIndex];
    pointsSumY -= pointsY[pointsIndex];
    pointsSumX += pointsX[pointsIndex] = *xP;
    pointsSumY += pointsY[pointsIndex] = *yP;
    *xP = pointsSumX >> MAX_POINTS_SHIFT;
    *yP = pointsSumY >> MAX_POINTS_SHIFT;
    if (++pointsIndex >= MAX_POINTS)
        pointsIndex = 0;
    
}

static void PrvDrawCircle(Coord centerX, Coord centerY, Coord radius, Coord width)
{
    RectangleType rect;
    
    rect.topLeft.x = centerX - radius;
    rect.topLeft.y = centerY - radius;
    rect.extent.x = 2 * radius;
    rect.extent.y = 2 * radius;
    WinPaintRoundedRectangleFrame(&rect, width, radius, 0);
}


static Int16 PrvSquareRoot(Int32 val)
// see http://www.azillionmonkeys.com/qed/sqroot.html for a faster/unrolled version
{
	unsigned long temp, g=0, b = 0x8000, bshft = 15;
	do {
		if (val >= (temp = (((g<<1)+b)<<bshft--))) {
			g += b;
			val -= temp;
		}
	} while (b >>= 1);
	return g;
}

// compute a "circularized" coordinate.
// Assumes *xP and *yP are between -r and r, in "square" coordinates
// modifies *xP and *yP to be scaled to a circular area with radius r.
// returns the effective radius of the scaled point
static Coord PrvSquareToCircle(Int32 *xP, Int32 *yP, Coord r)
{
	Int32 xSquared, ySquared, rSquared;
	Int32 temp;
	FixedType tempFixed;
	Int32 xi, yi, xr, yr, xp, yp, xo, yo;
	
	// edge cases
	if (*xP == 0)
		return *yP;
	if (*yP == 0)
		return *xP;
	
	xi = *xP;
	yi = *yP;
	
	xSquared = xi * xi;
	ySquared = yi * yi;
	rSquared = r;
	rSquared *= rSquared;
	
	if (Abs(xi) >= Abs(yi))
	{
		// compute y-projected, based on proportion yp/r = yi/xi
		yp = r;
		yp *= yi;
		yp /= xi;
		if (yp < 0) yp = -yp;	// only use positive values for math
		
		// compute y-at-radius, based on xr^2 + yr^2 = r^2 and xr/yr = xi/yi
		tempFixed = FixedDiv(xSquared, ySquared);
		tempFixed += FixedFromInteger(1);
		temp = FixedDiv(rSquared, tempFixed);
		yr = PrvSquareRoot(temp);
		
		// compute y-out and x-out, based on proportion yo/yi = xo/xi = yp/yr
		yo = yi * yr / yp;
		xo = xi * yr / yp;
	}
	else
	{
		// compute x-projected, based on proportion xp/r = xi/xi
		xp = r;
		xp *= xi;
		xp /= xi;
		if (xp < 0) xp = -xp;	// only use positive values for math
		
		// compute y-at-radius, based on xr^2 + yr^2 = r^2 and xr/yr = xi/yi
		tempFixed = FixedDiv(xSquared, ySquared);
		tempFixed += FixedFromInteger(1);
		temp = FixedDiv(rSquared, tempFixed);
		xr = PrvSquareRoot(temp);
		
		// compute y-out and x-out, based on proportion yo/yi = xo/xi = xp/xr
		yo = yi * xr / xp;
		xo = xi * xr / xp;
	}

	*xP = xo;
	*yP = yo;
	
	// get the distance from center of the circularized point
	xSquared = xr;
	xSquared *= xSquared;
	ySquared = yr;
	ySquared *= ySquared;
	rSquared = xSquared + ySquared;
	temp = PrvSquareRoot(rSquared);
	
	return (Int16)temp;
}



/*********************************************************************
 * "Navigator" Gadget Functions
 *********************************************************************/

typedef struct MyNavGadgetDataTag {
	FormType *formP;
	WinHandle offscreenWin;
	Coord xc, yc, radius;
	Int32 xl, yl;
	Int32 r, theta;
	BitmapType *bitmapP;
	MemHandle bitmapRscH;
} MyNavGadgetDataType;

#define PrvDrawNavGadget(formP) PrvNavGadgetHandler(GetObjectPtr(formP, MainNavGadget), formGadgetDrawCmd, NULL)
Boolean PrvNavGadgetHandler(struct FormGadgetTypeInCallback *gadgetP, UInt16 cmd, void *paramP);
void PrvRefreshNavGadget(FormType *formP);

static void PrvInitializeNavGadget(FormType *formP)
{
	// initialize nav gadget
	WinHandle oldWin;
	Err err;
	MyNavGadgetDataType *dataP;
	RectangleType r;

	FrmGetObjectBounds(formP,  FrmGetObjectIndex(formP, MainNavGadget), &r);

	dataP = MemPtrNew(sizeof(MyNavGadgetDataType));
	dataP->formP = formP;
	dataP->offscreenWin = WinCreateOffscreenWindow(r.extent.x, r.extent.y, nativeFormat, &err);
	dataP->bitmapRscH = DmGetResource(bitmapRsc, CursorBitmapFamily);
	dataP->bitmapP = MemHandleLock(dataP->bitmapRscH);

	oldWin = WinSetDrawWindow(dataP->offscreenWin);
	WinSetCoordinateSystem(kCoordinatesNative);
	
	WinScaleRectangle(&r);
	r.extent.x--; r.extent.y--;	 // better to have an odd sized rectangle

	dataP->radius = min(r.extent.x / 2, r.extent.y / 2) - 4;
	dataP->xc = r.extent.x / 2;
	dataP->yc = r.extent.y / 2;
	dataP->xl = 0;
	dataP->yl = 0;

	WinSetCoordinateSystem(kCoordinatesStandard);
	WinSetDrawWindow(oldWin);

	FrmSetGadgetData(formP,  FrmGetObjectIndex(formP, MainNavGadget), dataP);
	FrmSetGadgetHandler(formP,  FrmGetObjectIndex(formP, MainNavGadget), &PrvNavGadgetHandler);
	
	PrvRefreshNavGadget(formP);
}

static const RGBColorType kBackColor = {0, 0xFF, 0xFF, 0xFF};
static const RGBColorType kTrailColor = {0, 0xBB, 0xBB, 0xBB};
static const RGBColorType kTargetOutColor = {0, 0x25, 0x5C, 0xA0};
static const RGBColorType kTarget4WayLineColor = {0, 0x5E, 0x99, 0xD1};
static const RGBColorType kTarget8WayLineColor = {0, 0x5E, 0x99, 0xD1};
static const RGBColorType kTargetRadiusLineColor = {0, 0x5E, 0x99, 0xD1};
static const RGBColorType kPolarColor = {0, 0xAA, 0xAA, 0x00};
static const RGBColorType kCalibrationColor = {0, 0xAA, 0x00, 0x00};

static void PrvRefreshNavGadget(FormType *formP)
{
	MyNavGadgetDataType *dataP = FrmGetGadgetData(formP, FrmGetObjectIndex(formP, MainNavGadget));
	WinHandle oldWin;
	Coord radius;
	Coord xc, yc;
	Int32 xr, yr;

	oldWin = WinSetDrawWindow(dataP->offscreenWin);
	WinPushDrawState();
	WinSetCoordinateSystem(kCoordinatesNative);
	// WinSetBackColorRGB(&white, NULL);
	WinEraseWindow();
	
	radius = dataP->radius;
	xc = dataP->xc;
	yc = dataP->yc;
	
	xr = radius;
	yr = (radius * 106) >> 8; // 106/256 is approx sin(22.5)/cos(22.5), or 1/4 of a 90 degree angle
	PrvSquareToCircle(&xr, &yr, radius);
	WinSetForeColorRGB(&kTarget8WayLineColor, NULL);
	WinDrawLine(xc, yc, xc + xr, yc + yr);
	WinDrawLine(xc, yc, xc + xr, yc - yr);
	WinDrawLine(xc, yc, xc - xr, yc + yr);
	WinDrawLine(xc, yc, xc - xr, yc - yr);
	WinDrawLine(xc, yc, xc + yr, yc + xr);
	WinDrawLine(xc, yc, xc + yr, yc - xr);
	WinDrawLine(xc, yc, xc - yr, yc + xr);
	WinDrawLine(xc, yc, xc - yr, yc - xr);
	
	xr = radius;
	yr = radius;
	PrvSquareToCircle(&xr, &yr, radius);
	WinSetForeColorRGB(&kTarget4WayLineColor, NULL);
	WinDrawLine(xc, yc, xc + xr, yc + yr);
	WinDrawLine(xc, yc, xc + xr, yc - yr);
	WinDrawLine(xc, yc, xc - xr, yc + yr);
	WinDrawLine(xc, yc, xc - xr, yc - yr);
	
	WinSetForeColorRGB(&kTargetRadiusLineColor, NULL);
	PrvDrawCircle(xc, yc, radius * 3 / 4, 1);
	PrvDrawCircle(xc, yc, radius * 2 / 4, 1);
	PrvDrawCircle(xc, yc, radius * 1 / 4, 1);

	WinSetForeColorRGB(&kTargetOutColor, NULL);
	PrvDrawCircle(xc, yc, radius, 2);
	
	WinPopDrawState();
	WinSetDrawWindow(oldWin);
}

static void PrvAnimateNavGadget(FormType *formP, Int32 ox, Int32 oy, Int32 x, Int32 y, Int32 r, Int32 theta)
{
	MyNavGadgetDataType *dataP = FrmGetGadgetData(formP, FrmGetObjectIndex(formP, MainNavGadget));
	RectangleType rect;
	Coord radius, gx, gy;
	WinHandle oldWin;
	double v;
	Int32 rt;
	Int32 xr, yr;
	FlpCompDouble result;
	
	FrmGetObjectBounds(formP, FrmGetObjectIndex(formP, MainNavGadget), &rect);
	radius = dataP->radius;
	
	dataP->xl = x;
	dataP->yl = y;
		
	ox *= radius;
	ox /= twInputNavMax;
	oy *= radius;
	oy /= twInputNavMax;

	x *= radius;
	x /= twInputNavMax;
	y *= radius;
	y /= twInputNavMax;
		
	WinPushDrawState();
	WinScreenLock(winLockCopy);
	oldWin = WinSetDrawWindow(dataP->offscreenWin);
	WinSetCoordinateSystem(kCoordinatesNative);
	WinSetForeColorRGB(&kTrailColor, NULL);
	WinDrawLine(dataP->xc + ox, dataP->yc + oy, dataP->xc + x, dataP->yc + y);
	WinSetDrawWindow(oldWin);

	WinScaleRectangle(&rect);
	gx = rect.topLeft.x;
	gy = rect.topLeft.y;
	rect.topLeft.x = 0;
	rect.topLeft.y = 0;
	WinCopyRectangle(dataP->offscreenWin, NULL, &rect, gx, gy, winPaint);

    gx += dataP->xc;
    gy += dataP->yc;

    if (r > 0)
    {
    	WinSetForeColorRGB(&kPolarColor, NULL);
        rt = r;
        rt *= radius;
        rt /= twInputNavMax;

    	v = 0.017453292519943;  // 2 * pi / 360
    	v *= theta;
    	MathLibCos(MathLibRef, v, &(result.d));
    	result.d *= dataP->radius;
    	MathLibTrunc(MathLibRef, result.d, &result.d);
    	xr = _d_dtoi(result.fd);
    	
    	MathLibSin(MathLibRef, v, &result.d);
    	result.d *= (Int32)dataP->radius;
    	MathLibTrunc(MathLibRef, result.d, &result.d);
    	yr = _d_dtoi(result.fd);
    	    	
    	WinDrawLine(gx, gy, gx + xr, gy + yr);
    	PrvDrawCircle(gx, gy, rt, 1);
    	
    }
    
    WinDrawBitmap(dataP->bitmapP, gx + x - 4, gy + y - 4);
    WinScreenUnlock();
	WinPopDrawState();
}

static Boolean PrvNavGadgetHandler(struct FormGadgetTypeInCallback *gadgetP, UInt16 cmd, void *paramP)
{
	MyNavGadgetDataType *dataP = (MyNavGadgetDataType *)gadgetP->data;
	
	switch (cmd)
	{
		case formGadgetDrawCmd:   // paramP is unspecified
			PrvAnimateNavGadget(dataP->formP, dataP->xl, dataP->yl, dataP->xl, dataP->yl, dataP->r, dataP->theta);
			return true;
			
		case formGadgetEraseCmd:	// paramP is unspecified
			return false;
			
		case formGadgetHandleEventCmd:	// paramP is an (EventType *) for the relevant event.
			return false;
			
		case formGadgetDeleteCmd:	// paramP is unspecified.
			if (dataP != NULL)
			{
				MemHandleUnlock(dataP->bitmapRscH);
				DmReleaseResource(dataP->bitmapRscH);
				WinDeleteWindow(dataP->offscreenWin, false);
				MemPtrFree(dataP);
				gadgetP->data = NULL;
			}
			return true;
			
		default:
			return false;
	}
}



/*********************************************************************
 * "X Value" Gadget Functions
 *********************************************************************/

typedef struct MyValueGadgetDateTag {
	FormType *formP;
	BitmapType *bitmapP;
	MemHandle bitmapRscH;
	Boolean isX;
} MyValueGadgetDataType;

#define PrvDrawXValueGadget(formP, val) PrvValueGadgetHandler(GetObjectPtr(formP, MainXValueGadget), formGadgetDrawCmd, (void *)(val))
#define PrvDrawYValueGadget(formP, val) PrvValueGadgetHandler(GetObjectPtr(formP, MainYValueGadget), formGadgetDrawCmd, (void *)(val))
Boolean PrvValueGadgetHandler(struct FormGadgetTypeInCallback *gadgetP, UInt16 cmd, void *paramP);

static void PrvInitializeValueGadget(FormType *formP, Boolean isX)
{
	// initialize nav gadget
	MyValueGadgetDataType *dataP;
	RectangleType r;
	UInt16 index;

	if (isX)
		index = FrmGetObjectIndex(formP, MainXValueGadget);
	else
		index = FrmGetObjectIndex(formP, MainYValueGadget);
	
	FrmGetObjectBounds(formP, index, &r);
	
	dataP = MemPtrNew(sizeof(MyValueGadgetDataType));
	dataP->formP = formP;
	if (isX)
		dataP->bitmapRscH = DmGetResource(bitmapRsc, XIndexBitmapFamily);
	else
		dataP->bitmapRscH = DmGetResource(bitmapRsc, YIndexBitmapFamily);
	dataP->bitmapP = MemHandleLock(dataP->bitmapRscH);
	dataP->isX = isX;

	FrmSetGadgetData(formP, index, dataP);
	FrmSetGadgetHandler(formP, index, &PrvValueGadgetHandler);
}


static Boolean PrvValueGadgetHandler(struct FormGadgetTypeInCallback *gadgetP, UInt16 cmd, void *paramP)
{
	MyValueGadgetDataType *dataP = (MyValueGadgetDataType *)gadgetP->data;
	RectangleType r;
	Int32 i = (Int32)paramP;
	
	switch (cmd)
	{
		case formGadgetDrawCmd:   // paramP is unspecified
			r = gadgetP->rect;
			WinSetCoordinateSystem(kCoordinatesNative);
			WinScaleRectangle(&r);
			WinEraseRectangle(&r, 0);
			if (dataP->isX)
			{
				i *= (r.extent.x - 11) / 2;
				i /= twInputNavMax;
				i += r.topLeft.x + ((r.extent.x - 11) / 2);
				WinDrawLine(r.topLeft.x + 4, r.topLeft.y + 8, r.topLeft.x + r.extent.x - 8, r.topLeft.y + 8);
				WinDrawBitmap(dataP->bitmapP, i, r.topLeft.y);
			}
			else
			{
				i *= (r.extent.y - 11) / 2;
				i /= twInputNavMax;
				i += r.topLeft.y + ((r.extent.y - 11) / 2);
				WinDrawLine(r.topLeft.x + 8, r.topLeft.y + 4, r.topLeft.x + 8, r.topLeft.y + r.extent.y - 8);
				WinDrawBitmap(dataP->bitmapP, r.topLeft.x, i);
			}
			WinSetCoordinateSystem(kCoordinatesStandard);
			return true;
			
		case formGadgetEraseCmd:	// paramP is unspecified
			return false;
			
		case formGadgetHandleEventCmd:	// paramP is an (EventType *) for the relevant event.
			return false;
			
		case formGadgetDeleteCmd:	// paramP is unspecified.
			if (dataP != NULL)
			{
				MemHandleUnlock(dataP->bitmapRscH);
				DmReleaseResource(dataP->bitmapRscH);
				MemPtrFree(dataP);
				gadgetP->data = NULL;
			}
			return true;
			
		default:
			return false;
	}
}


/*********************************************************************
 * General Internal Functions
 *********************************************************************/

static Boolean PollTwInput(FormType *formP)
{
	Err err;
	
	if (g_input == NULL || g_currentEventP == NULL)
		return false;
		
	g_keyCurrentState = KeyCurrentState();
	err = TwInputPoll(g_input, (Int32 *)g_currentEventP, sizeof(MyTwEventType));
	
	// Turn the line below on to get an averaged (smoother) cursor point
	// PrvAddPointGetAverage(&g_currentEventP->navX, &g_currentEventP->navY);
	
		
	if (g_currentEventP->navSelect != g_lastEvent.navSelect)
	{
        CtlSetValue(GetObjectPtr(formP,MainNavSelectPushButton), g_currentEventP->navSelect);
		if (g_currentEventP->navSelect)
		{
			PrvRefreshNavGadget(formP);
			PrvDrawNavGadget(formP);
		}
	}
	
	if ((g_currentEventP->navX != g_lastEvent.navX)
		|| (g_currentEventP->navY != g_lastEvent.navY))
	{
		PrvDrawXValueGadget(formP, g_currentEventP->navX);
		PrvDrawYValueGadget(formP, g_currentEventP->navY);
		PrvAnimateNavGadget(formP, g_lastEvent.navX, g_lastEvent.navY, g_currentEventP->navX, g_currentEventP->navY, g_currentEventP->navR, g_currentEventP->navTheta);
	}
	
    if (g_lastEvent.triggerLeft != g_currentEventP->triggerLeft)
    	CtlSetValue(GetObjectPtr(formP, MainLeftTriggerPushButton), g_currentEventP->triggerLeft != 0);
    if (g_lastEvent.triggerRight != g_currentEventP->triggerRight)
    	CtlSetValue(GetObjectPtr(formP, MainRightTriggerPushButton), g_currentEventP->triggerRight != 0);
	
    if (g_lastEvent.actionA != g_currentEventP->actionA)
    	CtlSetValue(GetObjectPtr(formP, MainActionAPushButton), g_currentEventP->actionA != 0);
    if (g_lastEvent.actionB != g_currentEventP->actionB)
    	CtlSetValue(GetObjectPtr(formP, MainActionBPushButton), g_currentEventP->actionB != 0);
    if (g_lastEvent.actionC != g_currentEventP->actionC)
    	CtlSetValue(GetObjectPtr(formP, MainActionCPushButton), g_currentEventP->actionC != 0);
    if (g_lastEvent.actionD != g_currentEventP->actionD)
    	CtlSetValue(GetObjectPtr(formP, MainActionDPushButton), g_currentEventP->actionD != 0);
	
    if (g_lastEvent.navUp != g_currentEventP->navUp)
    	CtlSetValue(GetObjectPtr(formP, MainNavUpPushButton), g_currentEventP->navUp != 0);
    if (g_lastEvent.navDown != g_currentEventP->navDown)
    	CtlSetValue(GetObjectPtr(formP, MainNavDownPushButton), g_currentEventP->navDown != 0);
    if (g_lastEvent.navLeft != g_currentEventP->navLeft)
    	CtlSetValue(GetObjectPtr(formP, MainNavLeftPushButton), g_currentEventP->navLeft != 0);
    if (g_lastEvent.navRight != g_currentEventP->navRight)
    	CtlSetValue(GetObjectPtr(formP, MainNavRightPushButton), g_currentEventP->navRight != 0);
    if (g_lastEvent.navSelect != g_currentEventP->navSelect)
    	CtlSetValue(GetObjectPtr(formP, MainNavCenterPushButton), g_currentEventP->navSelect != 0);
    if (g_lastEvent.function != g_currentEventP->function)
    	CtlSetValue(GetObjectPtr(formP, MainButtonFunctionPushButton), g_currentEventP->function != 0);

    if (g_lastEvent.hard1 != g_currentEventP->hard1)
    	CtlSetValue(GetObjectPtr(formP, MainBitHard1PushButton), g_currentEventP->hard1 != 0);
    if (g_lastEvent.hard2 != g_currentEventP->hard2)
    	CtlSetValue(GetObjectPtr(formP, MainBitHard2PushButton), g_currentEventP->hard2 != 0);
    if (g_lastEvent.hard3 != g_currentEventP->hard3)
    	CtlSetValue(GetObjectPtr(formP, MainBitHard3PushButton), g_currentEventP->hard3 != 0);
    if (g_lastEvent.hard4 != g_currentEventP->hard4)
    	CtlSetValue(GetObjectPtr(formP, MainBitHard4PushButton), g_currentEventP->hard4 != 0);
    	
    if (g_lastEvent.nav4Way != g_currentEventP->nav4Way)
    {
        switch (g_lastEvent.nav4Way)
        {
            case twNavigatorCenter:
                CtlSetValue(GetObjectPtr(formP,Main4WayCenterPushButton), false);
                break;
            case twNavigatorUp:
                CtlSetValue(GetObjectPtr(formP,Main4WayUpPushButton), false);
                break;
            case twNavigatorRight:
                CtlSetValue(GetObjectPtr(formP,Main4WayRightPushButton), false);
                break;
            case twNavigatorDown:
                CtlSetValue(GetObjectPtr(formP,Main4WayDownPushButton), false);
                break;
            case twNavigatorLeft:
                CtlSetValue(GetObjectPtr(formP,Main4WayLeftPushButton), false);
                break;
        }
        switch (g_currentEventP->nav4Way)
        {
            case twNavigatorCenter:
                CtlSetValue(GetObjectPtr(formP,Main4WayCenterPushButton), true);
                break;
            case twNavigatorUp:
                CtlSetValue(GetObjectPtr(formP,Main4WayUpPushButton), true);
                break;
            case twNavigatorRight:
                CtlSetValue(GetObjectPtr(formP,Main4WayRightPushButton), true);
                break;
            case twNavigatorDown:
                CtlSetValue(GetObjectPtr(formP,Main4WayDownPushButton), true);
                break;
            case twNavigatorLeft:
                CtlSetValue(GetObjectPtr(formP,Main4WayLeftPushButton), true);
                break;
        }
    }
        
    if (g_lastEvent.nav8Way != g_currentEventP->nav8Way)
    {
        switch (g_lastEvent.nav8Way)
        {
            case twNavigatorCenter:
                CtlSetValue(GetObjectPtr(formP,Main8WayCenterPushButton), false);
                break;
            case twNavigatorUp:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpPushButton), false);
                break;
            case twNavigatorUpRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpRightPushButton), false);
                break;
            case twNavigatorRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayRightPushButton), false);
                break;
            case twNavigatorDownRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownRightPushButton), false);
                break;
            case twNavigatorDown:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownPushButton), false);
                break;
            case twNavigatorDownLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownLeftPushButton), false);
                break;
            case twNavigatorLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayLeftPushButton), false);
                break;
            case twNavigatorUpLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpLeftPushButton), false);
                break;
        }
        switch (g_currentEventP->nav8Way)
        {
            case twNavigatorCenter:
                CtlSetValue(GetObjectPtr(formP,Main8WayCenterPushButton), true);
                break;
            case twNavigatorUp:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpPushButton), true);
                break;
            case twNavigatorUpRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpRightPushButton), true);
                break;
            case twNavigatorRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayRightPushButton), true);
                break;
            case twNavigatorDownRight:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownRightPushButton), true);
                break;
            case twNavigatorDown:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownPushButton), true);
                break;
            case twNavigatorDownLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayDownLeftPushButton), true);
                break;
            case twNavigatorLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayLeftPushButton), true);
                break;
            case twNavigatorUpLeft:
                CtlSetValue(GetObjectPtr(formP,Main8WayUpLeftPushButton), true);
                break;
        }
    }
    
    if ((g_keyLastState & keyBitHard1) != (g_keyCurrentState & keyBitHard1))
        CtlSetValue(GetObjectPtr(formP, MainBitHard1PushButton), (g_keyCurrentState & keyBitHard1) != 0);
    if ((g_keyLastState & keyBitHard2) != (g_keyCurrentState & keyBitHard2))
        CtlSetValue(GetObjectPtr(formP, MainBitHard2PushButton), (g_keyCurrentState & keyBitHard2) != 0);
    if ((g_keyLastState & keyBitHard3) != (g_keyCurrentState & keyBitHard3))
        CtlSetValue(GetObjectPtr(formP, MainBitHard3PushButton), (g_keyCurrentState & keyBitHard3) != 0);
    if ((g_keyLastState & keyBitHard4) != (g_keyCurrentState & keyBitHard4))
        CtlSetValue(GetObjectPtr(formP, MainBitHard4PushButton), (g_keyCurrentState & keyBitHard4) != 0);
    	
    if ((g_keyLastState & keyBitPageUp) != (g_keyCurrentState & keyBitPageUp))
        CtlSetValue(GetObjectPtr(formP, MainBitPageUpPushButton), (g_keyCurrentState & keyBitPageUp) != 0);
    if ((g_keyLastState & keyBitPageDown) != (g_keyCurrentState & keyBitPageDown))
        CtlSetValue(GetObjectPtr(formP, MainBitPageDownPushButton), (g_keyCurrentState & keyBitPageDown) != 0);

    if ((g_keyLastState & keyBitActionA) != (g_keyCurrentState & keyBitActionA))
        CtlSetValue(GetObjectPtr(formP, MainBitActionAPushButton), (g_keyCurrentState & keyBitActionA) != 0);
    if ((g_keyLastState & keyBitActionB) != (g_keyCurrentState & keyBitActionB))
        CtlSetValue(GetObjectPtr(formP, MainBitActionBPushButton), (g_keyCurrentState & keyBitActionB) != 0);
    if ((g_keyLastState & keyBitActionC) != (g_keyCurrentState & keyBitActionC))
        CtlSetValue(GetObjectPtr(formP, MainBitActionCPushButton), (g_keyCurrentState & keyBitActionC) != 0);
    if ((g_keyLastState & keyBitActionD) != (g_keyCurrentState & keyBitActionD))
        CtlSetValue(GetObjectPtr(formP, MainBitActionDPushButton), (g_keyCurrentState & keyBitActionD) != 0);

    if ((g_keyLastState & keyBitRockerUp) != (g_keyCurrentState & keyBitRockerUp))
        CtlSetValue(GetObjectPtr(formP, MainBitRockerUpPushButton), (g_keyCurrentState & keyBitRockerUp) != 0);
    if ((g_keyLastState & keyBitRockerRight) != (g_keyCurrentState & keyBitRockerRight))
        CtlSetValue(GetObjectPtr(formP, MainBitRockerRightPushButton), (g_keyCurrentState & keyBitRockerRight) != 0);
    if ((g_keyLastState & keyBitRockerDown) != (g_keyCurrentState & keyBitRockerDown))
        CtlSetValue(GetObjectPtr(formP, MainBitRockerDownPushButton), (g_keyCurrentState & keyBitRockerDown) != 0);
    if ((g_keyLastState & keyBitRockerLeft) != (g_keyCurrentState & keyBitRockerLeft))
        CtlSetValue(GetObjectPtr(formP, MainBitRockerLeftPushButton), (g_keyCurrentState & keyBitRockerLeft) != 0);
    if ((g_keyLastState & keyBitRockerCenter) != (g_keyCurrentState & keyBitRockerCenter))
        CtlSetValue(GetObjectPtr(formP, MainBitRockerCenterPushButton), (g_keyCurrentState & keyBitRockerCenter) != 0);

    if ((g_keyLastState & keyBitFunction) != (g_keyCurrentState & keyBitFunction))
        CtlSetValue(GetObjectPtr(formP, MainBitFunctionPushButton), (g_keyCurrentState & keyBitFunction) != 0);

    if ((g_keyLastState & keyBitTriggerA) != (g_keyCurrentState & keyBitTriggerA))
        CtlSetValue(GetObjectPtr(formP, MainBitLeftTriggerPushButton), (g_keyCurrentState & keyBitTriggerA) != 0);
    if ((g_keyLastState & keyBitTriggerB) != (g_keyCurrentState & keyBitTriggerB))
        CtlSetValue(GetObjectPtr(formP, MainBitRightTriggerPushButton), (g_keyCurrentState & keyBitTriggerB) != 0);

	g_lastEvent = *g_currentEventP;
	g_keyLastState = g_keyCurrentState;
	return true;
}


/*
 * FUNCTION: GetObjectPtr
 *
 * DESCRIPTION:
 *
 * This routine returns a pointer to an object in the current form.
 *
 * PARAMETERS:
 *
 * formId
 *     id of the form to display
 *
 * RETURNED:
 *     address of object as a void pointer
 */

static void * GetObjectPtr(FormType *formP, UInt16 objectID)
{
    return FrmGetObjectPtr(formP, FrmGetObjectIndex(formP, objectID));
}

/*
 * FUNCTION: MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:
 *
 * frm
 *     pointer to the MainForm form.
 */

static void MainFormInit(FormType *formP)
{
	Int32 *formatAligned;
	Err err;
	
	// we know about screen size
	FrmSetDIAPolicyAttr(formP, frmDIAPolicyCustom);
	PINSetInputAreaState(pinInputAreaClosed);
	PINSetInputTriggerState(pinInputTriggerDisabled);
	SysSetOrientation(sysOrientationLandscape);
	SysSetOrientationTriggerState(sysOrientationTriggerDisabled);
	
	err = TwInputOpen(&g_input, "twinput", "r");
	if (err)
		g_input = NULL;
	else
	{
		formatAligned = MemPtrNew(sizeof(formatAllGameControls));
		MemMove(formatAligned, &formatAllGameControls, sizeof(formatAllGameControls));
		TwInputSetFormat(g_input, formatAligned, sizeof(formatAllGameControls));
		MemPtrFree(formatAligned);
	}
	
	g_currentEventP = MemPtrNew(sizeof(MyTwEventType));

	PrvInitializeNavGadget(formP);
	PrvInitializeValueGadget(formP, true);
	PrvInitializeValueGadget(formP, false);
}



/*
 * FUNCTION: MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:
 *
 * command
 *     menu item id
 */

static Boolean MainFormDoCommand(UInt16 command)
{
    Boolean handled = false;
    FormType * formP;

    switch (command)
    {	        
	    case NavigationAboutNavigation:

	        /* Clear the menu status from the display */
	        MenuEraseStatus(0);

	        /* Display the About Box. */
	        formP = FrmInitForm (AboutForm);
	        FrmDoDialog (formP);                    
	        FrmDeleteForm (formP);

	        handled = true;
	        break;
    }
    
 	
    return handled;
}


/*
 * FUNCTION: MainFormHandleEvent
 *
 * DESCRIPTION:
 *
 * This routine is the event handler for the "MainForm" of this 
 * application.
 *
 * PARAMETERS:
 *
 * eventP
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed to
 *     FrmHandleEvent
 */
static Boolean MainFormHandleEvent(EventType * eventP)
{
    Boolean handled = false;
    FormType * formP = FrmGetActiveForm();
    Char label[50];

    switch (eventP->eType) 
        {
        case keyDownEvent:
            if (eventP->data.keyDown.chr == vchrTwInput && (eventP->data.keyDown.modifiers & commandKeyMask))
        		handled = PollTwInput(formP);
        	StrPrintF(label, "Key Down c:%4hx m:%4hx k:%4hx", eventP->data.keyDown.chr, eventP->data.keyDown.modifiers, eventP->data.keyDown.keyCode); 
        	FrmCopyLabel(formP, MainEventLabel, label);
        	break;
        	
        case keyUpEvent:
        	StrPrintF(label, "Key Up      c:%4hx m:%4hx k:%4hx", eventP->data.keyDown.chr, eventP->data.keyDown.modifiers, eventP->data.keyDown.keyCode); 
        	FrmCopyLabel(formP, MainEventLabel, label);
            break;
            
        case penDownEvent:
        	StrPrintF(label, "Pen Down x:%3hd y:%3hd", eventP->screenX, eventP->screenY); 
        	FrmCopyLabel(formP, MainEventLabel, label);
            break;
            
        case penUpEvent:
        	StrPrintF(label, "Pen Up      x:%3hd y:%3hd", eventP->screenX, eventP->screenY); 
        	FrmCopyLabel(formP, MainEventLabel, label);
            break;
                    		
        case nilEvent:
         	handled = PollTwInput(formP);
         	break;
      
        case menuEvent:
            handled = MainFormDoCommand(eventP->data.menu.itemID);
			break;
			
        case frmOpenEvent:
            MainFormInit(formP);
            FrmDrawForm(formP);
            // TwInputActivate(g_input);
            handled = true;
            break;
            
        case frmUpdateEvent:
            /* To do any custom drawing here, first call
             * FrmDrawForm(), then do your drawing, and
             * then set handled to true. */
            FrmDrawForm(formP);
            handled = true;
            break;
          
        case winDisplayChangedEvent:
        	{
        		RectangleType r;
        		RectangleType oldR;
        		Coord deltaX, deltaY;
        		
        		// force window to be full screen
        		WinGetBounds(FrmGetWindowHandle(formP), &r);
	        	WinGetDisplayExtent(&r.extent.x, &r.extent.y);
	        	WinGetBounds(FrmGetWindowHandle(formP), &oldR);
	        	WinSetBounds(FrmGetWindowHandle(formP), &r);
	        	
	        	if (r.extent.x != oldR.extent.x)
	        		deltaX = (r.extent.x - oldR.extent.x) / 2;
	        	if (r.extent.y != oldR.extent.y)
	        		deltaY = (r.extent.y - oldR.extent.y) / 2;
	        			
	        	FrmGetObjectBounds(formP, FrmGetObjectIndex(formP, MainNavGadget), &r);
	        	r.topLeft.x += deltaX;
	        	r.topLeft.y += deltaY;
	        	FrmSetObjectBounds(formP, FrmGetObjectIndex(formP, MainNavGadget), &r);

	        	FrmGetObjectBounds(formP, FrmGetObjectIndex(formP, MainXValueGadget), &r);
	        	r.topLeft.x += deltaX;
	        	r.topLeft.y += deltaY;
	        	FrmSetObjectBounds(formP, FrmGetObjectIndex(formP, MainXValueGadget), &r);

	        	FrmGetObjectBounds(formP, FrmGetObjectIndex(formP, MainYValueGadget), &r);
	        	r.topLeft.x += deltaX;
	        	r.topLeft.y += deltaY;
	        	FrmSetObjectBounds(formP, FrmGetObjectIndex(formP, MainYValueGadget), &r);

				FrmDrawForm(formP);
	       	}
        	break;

		case frmCloseEvent:
			if (g_currentEventP != NULL)
			{
				MemPtrFree(g_currentEventP);
				g_currentEventP = NULL;
			}
						
			if (g_input != NULL)
			{
				// TwInputDeactivate(g_input);  // TwInputClose deactivates for you
				TwInputClose(g_input);
				g_input = NULL;
			}
			break;
			
        default:
            break;
        }
    
    return handled;
}

/*
 * FUNCTION: AppHandleEvent
 *
 * DESCRIPTION: 
 *
 * This routine loads form resources and set the event handler for
 * the form loaded.
 *
 * PARAMETERS:
 *
 * event
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed
 *     to a higher level handler.
 */

static Boolean AppHandleEvent(EventType * eventP)
{
    UInt16 formId;
    FormType * formP;

    if (eventP->eType == frmLoadEvent)
    {
        /* Load the form resource. */
        formId = eventP->data.frmLoad.formID;
        formP = FrmInitForm(formId);
        FrmSetActiveForm(formP);

        /* Set the event handler for the form.  The handler of the
         * currently active form is called by FrmHandleEvent each
         * time is receives an event. */
        switch (formId)
        {
        case MainForm:
            FrmSetEventHandler(formP, MainFormHandleEvent);
            break;

        default:
            break;

        }
        return true;
    }

    return false;
}

/*
 * FUNCTION: AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.
 */

static void AppEventLoop(void)
{
    UInt16 error;
    EventType event;

    do {
        /* change timeout if you need periodic nilEvents */
        EvtGetEvent(&event, 1);

        if (! SysHandleEvent(&event))
        {
            if (! MenuHandleEvent(0, &event, &error))
            {
                if (! AppHandleEvent(&event))
                {
                    FrmDispatchEvent(&event);
                }
            }
        }
    } while (event.eType != appStopEvent);
}

/*
 * FUNCTION: AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * RETURNED:
 *     errNone - if nothing went wrong
 */

static Err AppStart(void)
{
    Int32 i;
    Err err;
    
    // initialize point debouncer
    pointsIndex = pointsSumX = pointsSumY = 0;
    for (i = 0; i < MAX_POINTS; i++)
        pointsX[i] = pointsY[i] = 0;
        
    err = SysLibFind(MathLibName, &MathLibRef);
    if (err)
        err = SysLibLoad(LibType, MathLibCreator, &MathLibRef);
    if (!err)
        err = MathLibOpen(MathLibRef, MathLibVersion);
    
    return errNone;
}

/*
 * FUNCTION: AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 */

static void AppStop(void)
{
    Err err;
    UInt16 useCount;
            
    /* Close all the open forms. */
    FrmCloseAllForms();
    
    err = MathLibClose(MathLibRef, &useCount);
    if (!err && useCount == 0)
        SysLibRemove(MathLibRef);
}

/* all code from here to end of file should use no global variables */
#pragma warn_a5_access on

/*
 * FUNCTION: RomVersionCompatible
 *
 * DESCRIPTION: 
 *
 * This routine checks that a ROM version is meet your minimum 
 * requirement.
 *
 * PARAMETERS:
 *
 * requiredVersion
 *     minimum rom version required
 *     (see sysFtrNumROMVersion in SystemMgr.h for format)
 *
 * launchFlags
 *     flags that indicate if the application UI is initialized
 *     These flags are one of the parameters to your app's PilotMain
 *
 * RETURNED:
 *     error code or zero if ROM version is compatible
 */

static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
    UInt32 romVersion;

    /* See if we're on in minimum required version of the ROM or later. */
    FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
    if (romVersion < requiredVersion)
    {
        if ((launchFlags & 
            (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
            (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
        {
            FrmAlert (RomIncompatibleAlert);

            /* Palm OS versions before 2.0 will continuously relaunch this
             * app unless we switch to another safe one. */
            if (romVersion < kPalmOS20Version)
            {
                AppLaunchWithCommand(
                    sysFileCDefaultApp, 
                    sysAppLaunchCmdNormalLaunch, NULL);
            }
        }

        return sysErrRomIncompatible;
    }

    return errNone;
}

/*
 * FUNCTION: NavigationPalmMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:
 *
 * cmd
 *     word value specifying the launch code. 
 *
 * cmdPB
 *     pointer to a structure that is associated with the launch code
 *
 * launchFlags
 *     word value providing extra information about the launch
 *
 * RETURNED:
 *     Result of launch, errNone if all went OK
 */

static UInt32 NavigationPalmMain(
    UInt16 cmd, 
    MemPtr /*cmdPBP*/, 
    UInt16 launchFlags)
{
    Err error;

    error = RomVersionCompatible (ourMinVersion, launchFlags);
    if (error) return (error);

    switch (cmd)
    {
    case sysAppLaunchCmdNormalLaunch:
        error = AppStart();
        if (error) 
            return error;

        /* start application by opening the main form
         * and then entering the main event loop */
        FrmGotoForm(MainForm);
        AppEventLoop();
        
        AppStop();
        break;

    default:
        break;
    }

    return errNone;
}

/*
 * FUNCTION: PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 * 
 * PARAMETERS:
 *
 * cmd
 *     word value specifying the launch code. 
 *
 * cmdPB
 *     pointer to a structure that is associated with the launch code
 *
 * launchFlags
 *     word value providing extra information about the launch.
 *
 * RETURNED:
 *     Result of launch, errNone if all went OK
 */
 
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
    return NavigationPalmMain(cmd, cmdPBP, launchFlags);
}

/* turn a5 warning off to prevent it being set off by C++
 * static initializer code generation */
#pragma warn_a5_access reset
