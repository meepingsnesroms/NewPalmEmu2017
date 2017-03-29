/******************************************************************************
 *
 * Copyright (c) 1994-2003 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: PenInputMgr.h
 *
 * Release: 
 *
 * Description:
 *
 *    This file defines the Pen Input Manager structures and functions.
 *
 *    For OS 5.x, this file also defines the Status Bar Manager constants  
 *    and functions that are used for the 5.x control bar, as well as
 *    the functions to deal with landscape orientation.
 *
 *****************************************************************************/

#ifndef _TWPENINPUTMGR_H_
#define _TWPENINPUTMGR_H_

#include <PalmTypes.h>
#include <Preferences.h>
#include <Window.h>
#include <Form.h>
#include <ErrorBase.h>
#include <NotifyMgr.h>

// If nobody has explicitly specified whether the pins trap dispatcher 
// should be used, set it based on the CPU type.
#if CPU_TYPE == CPU_68K
    #define USE_PINSDISPATCH_TRAPS  1
#else
    #define USE_PINSDISPATCH_TRAPS  0
#endif

// If nobody has explicitly specified whether the high density trap dispatcher 
// should be used, set it based on the emulation level.
#ifndef USE_PINSDISPATCH_TRAPS
    #if EMULATION_LEVEL == EMULATION_NONE
        #define USE_PINSDISPATCH_TRAPS  1
    #else
        #define USE_PINSDISPATCH_TRAPS  0
    #endif
#endif

#if USE_PINSDISPATCH_TRAPS
    #define PINS_TRAP(selector) \
        _SYSTEM_API(_CALL_WITH_SELECTOR)(_SYSTEM_TABLE, sysTrapPinsDispatch, selector)
#else
    #define PINS_TRAP(selector)
#endif


// Notification for window resize
#ifndef sysNotifyDisplayResizedEvent
    #define sysNotifyDisplayResizedEvent 'scrs'

typedef struct SysNotifyDisplayResizedDetailsTag {
    RectangleType newBounds;
}  SysNotifyDisplayResizedDetailsType;

#endif


// event for display state change
#ifndef winDisplayChangedEvent
    enum winDisplayChangedEventHack
    {
	    winDisplayChangedEvent = 0x4101
    };
#endif

#define sysTrapPinsDispatch             0xA470

// constant for feature for active silkscreen flags, from SystemMgr.h
#ifndef sysFtrNumInputAreaFlags
    #define sysFtrNumInputAreaFlags     26          // Active silkscreen flags
#endif

// Graffiti feature flags, from Graffiti.h
#ifndef grfFtrInputAreaFlagDynamic
    // Flags for the sysFtrCreator/sysFtrNumInputAreaFlags feature.
    #define grfFtrInputAreaFlagDynamic              0x00000001
    #define grfFtrInputAreaFlagLiveInk              0x00000002
    #define grfFtrInputAreaFlagCollapsible          0x00000004
    #define grfFtrInputAreaFlagLandscape            0x00000008
    #define grfFtrInputAreaFlagReversePortrait      0x00000010
    #define grfFtrInputAreaFlagReverseLandscape     0x00000020
    #define grfFtrInputAreaFlagLefthanded           0x00000040
#endif

// Handedness states
// in PalmOS Preferences.h
#ifndef prefRightHanded
#define prefHandednessChoice          55    // for use with PrefGetPreference
#define prefRightHanded                0
#define prefLeftHanded                 1
#endif


#ifdef __cplusplus
extern "C" {
#endif

// Input area API
// in PalmOS PenInputMgr.h
#ifndef pinCreator
#define pinPINSetInputAreaState            0
#define pinPINGetInputAreaState            1
#define pinPINSetInputTriggerState         2
#define pinPINGetInputTriggerState         3
#define pinPINAltInputSystemEnabled        4
#define pinPINGetCurrentPinletName         5
#define pinPINSwitchToPinlet               6
#define pinPINCountPinlets                 7
#define pinPINGetPinletInfo                8
#define pinPINSetInputMode                 9
#define pinPINGetInputMode                10
#define pinPINClearPinletState            11
#define pinPINShowReferenceDialog         12

// Pen Input Manager Features
#ifndef pinCreator
#define pinCreator                  'pins'
#define pinFtrAPIVersion            1

#define pinAPIVersion1_0            0x01000000
#define pinAPIVersion1_1            0x01103000


// Pen Input Manager errors
#define pinErrNoSoftInputArea       (pinsErrorClass | 0x00)
#define pinErrInvalidParam          (pinsErrorClass | 0x01)

#ifndef pinsErrorClass
    #define pinsErrorClass              0x5000
#endif

// Input trigger states
typedef enum 
{
    pinInputTriggerEnabled,
    pinInputTriggerDisabled,
    pinInputTriggerNone             // do not use
}
PINInputTriggerStateType;

// Input area states
typedef enum
{
    pinInputAreaOpen,
    pinInputAreaClosed,
    pinInputAreaNone,               // do not use
    reserved1,                      // do not use
    reserved2,                      // do not use
    pinInputAreaUser,               // restore the last user selection of input area state

    pinInputAreaReset = 0xFFFF      // for internal use only
}
PINInputAreaStateType;


UInt16  PINGetInputAreaState(void)
                PINS_TRAP(pinPINGetInputAreaState);
                
Err     PINSetInputAreaState(UInt16 state)
                PINS_TRAP(pinPINSetInputAreaState);
                
UInt16  PINGetInputTriggerState(void)
                PINS_TRAP(pinPINGetInputTriggerState);
                                
Err     PINSetInputTriggerState(UInt16 state)
                PINS_TRAP(pinPINSetInputTriggerState);
#endif

// older constants
#ifndef pinInputAreaHide
#define pinInputAreaHide                pinInputAreaClosed
#define pinInputAreaShow                pinInputAreaOpen
#endif




// status bar API
#ifndef pinStatHide
#define pinStatHide                       16
#define pinStatShow                       17
#define pinStatGetAttribute               18

#ifndef statErrorClass
    #define statErrorClass              0x5100
#endif

// status bar errors
#define statErrInvalidLocation      (statErrorClass | 0x01)
#define statErrInvalidName          (statErrorClass | 0x02)
#define statErrInputWindowOpen      (statErrorClass | 0x03)
#endif

// selectors for StatGetAttribute
#define statAttrBarVisible             0
#define statAttrDimension              1

Err     StatGetAttribute(UInt16 selector, UInt32* dataP)
                PINS_TRAP(pinStatGetAttribute);
                
Err     StatHide(void)
                PINS_TRAP(pinStatHide);
                
Err     StatShow(void)
                PINS_TRAP(pinStatShow);
#endif

// orientation API
// in PalmOS SystemMgr.h
#ifndef pinSysGetOrientation
#define pinSysGetOrientation              19
#define pinSysSetOrientation              20
#define pinSysGetOrientationTriggerState  21
#define pinSysSetOrientationTriggerState  22

// Orientation states
#define sysOrientationUser             0
#define sysOrientationPortrait         1
#define sysOrientationLandscape        2
#define sysOrientationReversePortrait  3
#define sysOrientationReverseLandscape 4

// Orientation trigger states
#define sysOrientationTriggerDisabled  0
#define sysOrientationTriggerEnabled   1

UInt16  SysGetOrientation(void)
                PINS_TRAP(pinSysGetOrientation);
                
Err     SysSetOrientation(UInt16 orientation)
                PINS_TRAP(pinSysSetOrientation);
                
UInt16  SysGetOrientationTriggerState(void)
                PINS_TRAP(pinSysGetOrientationTriggerState);
                
Err     SysSetOrientationTriggerState(UInt16 state)
                PINS_TRAP(pinSysSetOrientationTriggerState);
#endif

// supporting functions
// in PalmOS Window.h
#ifndef pinWinSetConstraintsSize
#define pinWinSetConstraintsSize          13

Err     WinSetConstraintsSize(WinHandle winH, Coord minH, Coord prefH, Coord maxH,
                                              Coord minW, Coord prefW, Coord maxW)
                PINS_TRAP(pinWinSetConstraintsSize);
#endif
                
// in PalmOS Form.h
#ifndef pinFrmSetDIAPolicyAttr
#define pinFrmSetDIAPolicyAttr            14
#define pinFrmGetDIAPolicyAttr            15

// Form Dynamic Input Area Policies
#define frmDIAPolicyStayOpen        0
#define frmDIAPolicyCustom          1

UInt16  FrmGetDIAPolicyAttr (FormPtr formP)
                PINS_TRAP(pinFrmGetDIAPolicyAttr);

Err     FrmSetDIAPolicyAttr (FormPtr formP, UInt16 diaPolicy)
                PINS_TRAP(pinFrmSetDIAPolicyAttr);
#endif

// unused functions that are nonetheless defined
// all return errors if you call them
Boolean PINAltInputSystemEnabled(void)
                PINS_TRAP(pinPINAltInputSystemEnabled);

const Char *PINGetCurrentPinletName(void)
                PINS_TRAP(pinPINGetCurrentPinletName);

Err     PINSwitchToPinlet(const Char *pinletName, UInt16 initialInputMode)
                PINS_TRAP(pinPINSwitchToPinlet);

UInt16  PINCountPinlets(void)
                PINS_TRAP(pinPINCountPinlets);

Err     PINGetPinletInfo(UInt16 index, UInt16 infoSelector, UInt32 *info)
                PINS_TRAP(pinPINGetPinletInfo);

void    PINSetInputMode(UInt16 inputMode)
                PINS_TRAP(pinPINSetInputMode);

UInt16  PINGetInputMode(void)
                PINS_TRAP(pinPINGetInputMode);

void    PINClearPinletState(void)
                PINS_TRAP(pinPINClearPinletState);

void    PINShowReferenceDialog(void)
                PINS_TRAP(pinPINShowReferenceDialog);


#ifdef __cplusplus
}
#endif


#endif // _TWPENINPUTMGR_H_
