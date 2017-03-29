/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWINPUT_H__
#define __TWINPUT_H__

#include <PalmOS.h>
#include <TwChars.h>
#include <TwTraps.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TwInputHandle
typedef Int32 TwInputHandle;
#endif

/*
 * virtual key 0 - 9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * virtual key A - Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 * anything else will be defined later as needed
 */

/* for digitizer x, y, and pressure */
#define twInputPenX             256
#define twInputPenY             257
#define twInputPenZ             258


/* for joystick positions */
#define twInputNavX             259
#define twInputNavY             260

#define twInputNavMin		(-0x7fff)
#define twInputNavMax		 (0x7fff)
#define twInputNavCenter	 (0x0000)

/* equivalent to KeyCurrentState() */
#define twInputKeyState         261

/* for 4-way and 8-way navigator */
/* please see vchrJoyXXX for meaningful values */
#define twInput4Way             262
#define twInput8Way             263

#   define twNavigatorCenter      0
#   define twNavigatorUp          1
#   define twNavigatorUpRight     2
#   define twNavigatorRight       3
#   define twNavigatorDownRight   4
#   define twNavigatorDown        5
#   define twNavigatorDownLeft    6
#   define twNavigatorLeft        7
#   define twNavigatorUpLeft      8

/* for special purpose buttons */
#define twInputLaunch           270
#define twInputPower            271

#define twInputBluetooth        272
#define twInputFunction         273

/* for action buttons */
#define twInputActionA          274
#define twInputActionB          275
#define twInputActionC          276
#define twInputActionD          277

/* for left and right triggers */
#define twInputTriggerA         282
#define twInputTriggerB         283

/* for standard 4-way navigator buttons */
#define twInputNavUp            284
#define twInputNavDown          285
#define twInputNavLeft          286
#define twInputNavRight         287
#define twInputNavSelect        288

/* for classic palm application buttons */
#define twInputHard1            290
#define twInputHard2            291
#define twInputHard3            292
#define twInputHard4            293

/* current time, milli seconds since last boot */ 
#define twInputTimeStamp        294

/* event sequential number */
#define twInputSequence         295

/* polar coordinate navigator values */
#define twInputNavR			    298
#define twInputNavTheta		    299

Err TwInputOpen(TwInputHandle* input, const Char* name, const Char* mode)
    TAL_TRAP(trapTwInputOpen);

Err TwInputClose(TwInputHandle input)
    TAL_TRAP(trapTwInputClose);

Err TwInputActivate(TwInputHandle input)
    TAL_TRAP(trapTwInputActivate);

Err TwInputDeactivate(TwInputHandle input)
    TAL_TRAP(trapTwInputDeactivate);

Err TwInputGetPeriod(TwInputHandle input, Int32* millis)
    TAL_TRAP(trapTwInputGetPeriod);

Err TwInputSetPeriod(TwInputHandle input, Int32 millis)
    TAL_TRAP(trapTwInputSetPeriod);

Err TwInputGetCapacity(TwInputHandle input, Int32* sizeInEvents)
    TAL_TRAP(trapTwInputGetCapacity);

Err TwInputSetCapacity(TwInputHandle input, Int32 sizeInEvents)
    TAL_TRAP(trapTwInputSetCapacity);

Err TwInputGetFormat(TwInputHandle input, Int32* features, Int32* sizeInBytes)
    TAL_TRAP(trapTwInputGetFormat);

Err TwInputSetFormat(TwInputHandle input, Int32* features, Int32 sizeInBytes)
    TAL_TRAP(trapTwInputSetFormat);

Err TwInputPeek(TwInputHandle input, Int32* event, Int32 sizeInBytes)
    TAL_TRAP(trapTwInputPeek);

Err TwInputRead(TwInputHandle input, Int32* event, Int32 sizeInBytes)
    TAL_TRAP(trapTwInputRead);

Err TwInputPoll(TwInputHandle input, Int32* event, Int32 sizeInBytes)
    TAL_TRAP(trapTwInputPoll);

Err TwInputControl(TwInputHandle input, Int32 cmd, void* buf, Int32 sizeInBytes)
    TAL_TRAP(trapTwInputControl);

#ifdef __cplusplus
}
#endif

#endif /* __TWINPUT_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
