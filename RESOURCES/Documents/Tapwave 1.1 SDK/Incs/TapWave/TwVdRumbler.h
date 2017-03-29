/*
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * File:        TwVdRumbler.h
 *
 * Author:      DFC
 *
 * Contains:    Virtual Device Driver Interface for the RoadDawg Rumbler (vibrator).
 *
 * Exported File:  Yes
 *
 * REVISION HISTORY:
 *      Name    Date        Description
 *      ----    ----        -----------
 *      dfc     03/12/03    initial Revision
 *      dfc     03/19/03    Revise API - replace write with control; repeat play
 */

#ifndef __TWVDRUMBLER_H__
#define __TWVDRUMBLER_H__

#define TW_VD_RUMBLER "vibrator0"      /* Name of the Rumbler Device */

/*
 * Definition of one "frame" of a rumbler "stream".
 * Create an array of these to provide different streams to "play" on the rumbler
 * to get different effects.
 * Alternate periods of "silence" with periods of rumbling to get different feels.
 */

/*
 * NOTE: Because some compilers pad structure definitions, you should just use an
 *       array of characters to represent the TwVdRumblerFrame structure.
 *
 *  typedef struct TwVdRumblerFrame
 *  {
 *      UInt8 rumbleSpeed;     // Rotation speed, 0 = rumbler off, 255 = fastest.
 *      UInt8 rumbleDuration;  // Amount of time, in 1/100 seconds, for the device
 *                             // to be active (or to be silent, if rumbleSpeed == 0).
 *  } TwVdRumblerFrame;
 *
 */
 
/*
 * These are safe to use on any compiler (68K, ARM, ...) because just a byte stream.
 */
typedef UInt8 *TwVdRumblerFramePtr;

#define SizeOfTwVdRumblerFrame      2
#define TwVdRumblerFrameSpeed(p)    *(p)
#define TwVdRumblerFrameDuration(p) *((p)+1)

/* NOTE:  Only valid TwDevice APIs for the Rumbler are:
 *    err = TwDeviceOpen(&handle, TW_VD_RUMBLER, "rw");
 *    err = TwDeviceClose(handle);
 *    err = TwDeviceGetProperty(handle, property, buf, len); // see below for properties
 *    err = TwDeviceControl(handle, cmd, buf, len);          // see below for commands
 *
 *    Note also that although there is only one rumbler, mutiple open's of the rumbler device will work fine.
 *    The absolute value of the handle returned will be different for each open, however all instances will share
 *    the same global state.  And, like printf, "the last command wins".
 */

/*
 * Properties of the Rumbler device
 */

#define TW_VD_RUMBLER_MAX_SPEED 'sped'      /* The maximum speed of the rumbler device. */
                                            /*  GET only. Returns a UInt8 value */
#define TW_VD_RUMBLER_IS_ANALOG 'anlg'      /* TRUE if the rumbler speed is variable, false if it's (on/off) only. */
                                            /*  GET only. Returns a UInt8 value, 1 == TRUE, 0 == FALSE */
#define TW_VD_RUMBLER_MAX_TIME  'dura'      /* Maximum duration of rumbler ON cycle, in 1/100 seconds */
                                            /*  GET only.  Returns a UInt8 value */
#define TW_VD_RUMBLER_PLAYING   'plng'      /* Indicates if the rumbler is currently playing. */
                                            /*  GET only.  Returns a UInt8 value, 0 = NO, 1 = playing */
                                       
/*
 * TwDeviceControl commands for the Rumbler device
 */
#define TW_VD_RUMBLER_CMD_ON  'strt'        /* Command to turn on the Rumbler. */
                                            /* NOTE: You must explicity turn it off or it will run forever */
#define TW_VD_RUMBLER_CMD_OFF 'stop'        /* Command to turn off the Rumbler. */
                                            /* Will also abort any playing frame and stop rumbler immediatly. */
#define TW_VD_RUMBLER_CMD_PLAY 'play'       /* Command to play a rumbler stream once, then stop. */
                                            /* A pointer to the stream is passed in via the "buf" argument,
                                               with the len argument the number of bytes in the stream.
                                               An error is returned if number of bytes is not a mutiple of 2.
                                               An internal copy is made of the stream.  Max size is 1024 byes. */
#define TW_VD_RUMBLER_CMD_REPEAT 'rept'     /* Command to play a rumbler stream repeatedly, until an OFF cmd is received */
                                            /* A pointer to the stream is passed in via the "buf" argument,
                                               with the len argument the number of bytes in the stream.
                                               An error is returned if number of bytes is not a mutiple of 2.
                                               An internal copy is made of the stream.  Max size is 1024 byes. */

#define TW_VD_RUMBLER_CMD_ON_FAST   'fast'  /* Convenience command -- turns rumbler on full blast. */
                                            /* NOTE: You must explicity turn it off or it will run forever */
#define TW_VD_RUMBLER_CMD_ON_MEDIUM 'medi'  /* Convenience command -- turns rumbler on full blast. */
                                            /* NOTE: You must explicity turn it off or it will run forever */
#define TW_VD_RUMBLER_CMD_ON_SLOW   'slow'  /* Convenience command -- turns rumbler on full blast. */
                                            /* NOTE: You must explicity turn it off or it will run forever */

#endif /* __TWVDRUMBLER_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
