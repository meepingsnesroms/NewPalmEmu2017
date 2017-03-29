/*
	File:			host.h

	Description:	Host header file.

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

/* Define how some common types are defined on the
host machine.
*/

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef long intptr;
typedef unsigned long uintptr;

#ifndef __cplusplus
typedef unsigned char bool;
#endif

#ifndef NULL
#define NULL	0
#endif

#include <TapWave.h>

// The API to the host functions is C based.
#ifdef __cplusplus
extern "C"
{
#endif

// Host provided functions
    extern void HostMaskKeys(void);
    extern void HostUnmaskKeys(void);
    extern long int HostGetConsoleInput(void);
    extern void GamePlaySounds(void);
    extern void HostDrawObject(int bitmapNumber,
    short int x,
    short int y);
    extern void HostDrawGameMenu(int left,
        int top,
        int width,
        int height);
    extern void HostDrawPoint(int x,
        int y);
    extern void HostFlushPoints(void);
    extern void HostNewScreenBuffer(short int buffer_width,
    short int buffer_height);
    extern void HostDrawBuffer(short int destX,
    short int destY,
    short int sourceX,
    short int sourceY,
    short int sourceWidth,
    short int sourceHeight);
    extern long int HostPeriodDuration(void);
// extern void HostSetForeColor(ColorType color);

// extern void HostSetBackColor(ColorType color);

    extern void HostOpenScreenBuffer(void);
    extern void HostCloseScreenBuffer(void);
    extern int HostGetBitmapWidth(int bitmapNumber);
    extern int HostGetBitmapHeight(int bitmapNumber);
	
	extern void HostPlayRumble(short int effect);

// Game provided functions.
#define game_pause 1
#define game_run 0

    extern void game_set_pause(int value);
    extern int game_get_pause(void);
    extern void game_new(int width,
        int height,
        int random_number_seed);
	extern int game_exists(void);
    extern int game_advance(unsigned long int keys, long int joystickX, long int joystickY);

    extern void game_delete(void);

#ifdef __cplusplus
}
#endif

