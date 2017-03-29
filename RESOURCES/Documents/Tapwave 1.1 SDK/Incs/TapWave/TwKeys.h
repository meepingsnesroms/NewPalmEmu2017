/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWKEYS_H__
#define __TWKEYS_H__

#include <PalmOS.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * These key bits are used by KeyCurrentState() and HALKeyGetState().
 */

/*
 * PalmOS 5.0 SDK R2 defines the following constants for 5-way controller and thumbwheel
 * we define them here as well in case the developer is not using the latest SDK
 * we use the same bits for our function button and 5-way nav events
 */
#if !defined(keyBitRockerUp)
#define keyBitRockerUp          0x00010000      // 5-way rocker
#define keyBitRockerDown        0x00020000
#define keyBitRockerLeft        0x00040000
#define keyBitRockerRight       0x00080000
#define keyBitRockerCenter      0x00100000
#endif

#if !defined(keyBitJogBack)
#define	keyBitJogBack           0x00008000	// jog wheel back button
#endif

#define keyBitLaunch            0x00800000

#define keyBitBluetooth         0x01000000
#define keyBitFunction          keyBitJogBack

#define keyBitTriggerA          0x04000000
#define keyBitTriggerB          0x08000000

#define keyBitActionA           0x10000000
#define keyBitActionB           0x20000000
#define keyBitActionC           0x40000000
#define keyBitActionD           0x80000000


/* These direction bits are physically exclusive of each other. */
#define keyBitNavUp             keyBitRockerUp
#define keyBitNavDown           keyBitRockerDown
#define keyBitNavLeft           keyBitRockerLeft
#define keyBitNavRight          keyBitRockerRight
#define keyBitNavSelect         keyBitRockerCenter

/* 
 * NOTE: These corner directions are the union of two directions each. 
 * Each corner direction is exclusive of the others.
 * 
 * These are often used after a 5-way keyDownEvent to check for 
 * corner input because no keyDownEvents are generated for the corners.
 */
#define keyBitsNavAll           0x001F0000
#define keyBitsNavUpLeft        0x00050000
#define keyBitsNavUpRight       0x00090000
#define keyBitsNavDownLeft      0x00060000
#define keyBitsNavDownRight     0x000A0000

#ifdef __cplusplus
}
#endif

#endif /* __TWKEYS_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
