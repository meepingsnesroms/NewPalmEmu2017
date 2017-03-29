/******************************************************************************
 *
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * File: TwOSAdditions.h
 *
 * Description: This header file defines a bunch of future PalmOS functions
 * that we needed implemented on the TapWave devices.
 *
 *****************************************************************************/

#ifndef __TWOSADDITIONS_H__
#define __TWOSADDITIONS_H__

#include <PalmOS.h>
#include <VFSMgr.h>
#include <TwTraps.h>

#ifdef __cplusplus
extern "C" {
#endif

// constants for titleDrawFlags in TwDrawTitleBar
#define twTitleFlagRefresh   0x0000001
#define twTitleFlagNoBattery 0x0000002
#define twTitleFlagNoClock   0x0000004

// constants for sizeFlags in TwGetGraphicForButton
#define twButtonGraphicSizeStandard 11

// constants for TwPickColorStartType
#define TwPickColorStartPalette 0
#define TwPickColorStartRGB     1
#define TwPickColorStartHSV     2
#define TwPickColorStartTheme   3

// constants for TwGetSlotNumberForVolume()
#define twSlotUnknown           -1
#define twSlotInternal          0
#define twSlotLeft              1
#define twSlotRight             2

// constants for TwGet{PRC|DB}DataDirectory
#define kTwDirectoryPrefix      "/PALM/Programs/"
#define kTwPathNameResType      'Twdp'
#define kTwPathNameResID        0

typedef UInt16 TwPickColorStartType;

#define kCompatibleLegacyKeys 9
#define kCompatibleLegacyTestBits  {keyBitActionA, keyBitActionB, keyBitActionC,  keyBitActionD, keyBitNavUp,  keyBitNavDown,  keyBitNavLeft, keyBitNavRight, keyBitFunction}
#define kCompatibleLegacySetBits   {keyBitPageUp,  keyBitHard4,   keyBitPageDown, keyBitHard3,   keyBitPageUp, keyBitPageDown, keyBitHard1,   keyBitHard2,    0}
#define kCompatibleLegacyTestChars {vchrActionA,   vchrActionB,   vchrActionC,    vchrActionD,   vchrNavUp,    vchrNavDown,    vchrNavLeft,   vchrNavRight,   vchrFunction}
#define kCompatibleLegacySetChars  {vchrPageUp,    vchrHard4,     vchrPageDown,   vchrHard3,     vchrPageUp,   vchrPageDown,   vchrHard1,     vchrHard2,      vchrCalc}

#define kCompatible5wayKeys 7
#define kCompatible5wayTestBits  {keyBitActionA, keyBitActionB, keyBitActionC,  keyBitActionD, keyBitNavUp,  keyBitNavDown,  keyBitFunction}
#define kCompatible5waySetBits   {keyBitHard2,   keyBitHard4,   keyBitHard3,    keyBitHard1,   keyBitPageUp, keyBitPageDown, 0}
#define kCompatible5wayTestChars {vchrActionA,   vchrActionB,   vchrActionC,    vchrActionD,   vchrNavUp,    vchrNavDown,    vchrFunction}
#define kCompatible5waySetChars  {vchrHard2,     vchrHard4,     vchrHard3,      vchrHard1,     vchrPageUp,   vchrPageDown,   vchrCalc}

#ifndef __FRMGLUE_H__
// this is the ARM version of a function that's provided by PalmOS as 68K glue
void FrmGlueSetHelpID(FormType * formP, UInt16 helpRscID);
#endif

#ifndef __WINGLUE_H__
// this is the ARM version of a function that's provided by PalmOS as 68K glue
void WinGlueSetFrameType(WinHandle winH, FrameType newFrame);
#endif

void CtlSetFrameStyle(ControlType *ctlP, ButtonFrameType newStyle)
    TAL_TRAP(trapTwCtlSetFrameStyle);

void WinGetBitmapDimensions(BitmapType *bmP, Coord *widthP, Coord *heightP)
    TAL_TRAP(trapWinGetBitmapDimensions);

void TwDrawTitleBar(const FormType *formP, const Char *title, Coord arcX, const RGBColorType *colorThemeP, UInt32 titleDrawFlags)
    TAL_TRAP(trapTwDrawTitleBar);

void TwSetTapwaveScrollBar(ScrollBarPtr barP, Boolean isTapwave, RGBColorType *colorP)
    TAL_TRAP(trapTwSetTapwaveScrollBar);

Int16 TwGetSlotNumberForVolume(UInt16 volRef)
    TAL_TRAP(trapTwGetSlotNumberForVolume);

UInt16 TwGetSlotRefNumForSlot(Int16 physicalSlot)
    TAL_TRAP(trapTwGetSlotRefNumForSlot);

Err  TwCreateDatabaseFromImage(MemPtr image, Char *dbNameP)
    TAL_TRAP(trapTwCreateDatabaseFromImage);

const BitmapType *TwGetGraphicForButton(WChar chr, Int32 size)
    TAL_TRAP(trapTwGetGraphicForButton);

Err TwGetPRCDataDirectory(FileRef fileRef, Char *pathNameP, UInt16 maxLen)
    TAL_TRAP(trapTwGetPRCDataDirectory);

#if CPU_TYPE == CPU_68K
Err TwGetDBDataDirectory(UInt16 cardNo, LocalID dbH, UInt16 *volRefNumP, Char *pathNameP, UInt16 maxLen)
    TAL_TRAP(trapTwGetPRCDataDirectory);
#else
Err TwGetDBDataDirectory(MemHandle dbH, UInt16 *volRefNumP, Char *pathNameP, UInt16 maxLen)
    TAL_TRAP(trapTwGetPRCDataDirectory);
#endif

Int32 TwGetMicroSeconds(void)
    TAL_TRAP(trapTwGetMicroSeconds);

Boolean TwPickColor(IndexedColorType* indexP, RGBColorType * rgbP,
                    TwPickColorStartType start, const Char * titleP,
                    const Char * tipP)
    TAL_TRAP(trapTwPickColor);

void TwAdjustColor(RGBColorType *rgbP, Int16 adjH, Int16 adjS, Int16 adjV)
    TAL_TRAP(trapTwAdjustColor);

Boolean TwMenuIsVisible(MenuBarType * menuP)
    TAL_TRAP(trapTwMenuIsVisible);

SysBatteryState TwBatteryState(void)
    TAL_TRAP(trapTwBatteryState);

Boolean TwConfirmQuit(const Char *message)
    TAL_TRAP(trapTwConfirmQuit);

Err TwSetCompatibleKeys(Int32 count, const UInt32 *testBits, const UInt32 *setBits, const WChar *testChars, const WChar *setChars)
    TAL_TRAP(trapTwSetCompatibleKeys);

// these flags will fill the background window with the appropriate
// background image prior to tinting, none will not change the bitmap
#define twBackgroundNone            0x00000000
#define twBackgroundSimple          0x00010000
#define twBackgroundNavigator       0x00020000
#define twBackgroundRight           0x00040000
#define twBackgroundFullScreen      0x00080000
#define twBackgroundApplyTint       0x00100000
#define twBackgroundArcPosMask      0x0000FFFF

Err TwCreateAppBackground(WinHandle winH, UInt32 whichFlags, const RGBColorType *colorP)
    TAL_TRAP(trapTwCreateAppBackground);


/* Convenient gzip and gunzip functions */
MemPtr gunzip(MemPtr image, UInt32 length);
MemPtr gzip(MemPtr image, UInt32 length);

/*
 * Special notification sent right before app exits. The
 * notifyDetailsP IS the mem owner of exiting application.
 *
 * COMMENT: this notification is VERY VERY VERY different from
 * sysNotifyAppQuittingEvent. Latter is sent after app fully quits,
 * i.e. memory have been freed, vfs handles have been closed, sound
 * streams have been deleted, even app info block is freed. It is
 * almost impossible to do anything useful at that point.
 */
#define twNotifyAppExitEvent        'twAX'

#ifdef __cplusplus
}
#endif

#endif /* __TWOSADDITIONS_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
