/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWCHARS_H__
#define __TWCHARS_H__

#include <PalmOS.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef vchrTapWaveMin
#define vchrTapWaveMin          0x1B00
#endif

#ifndef vchrTapWaveMax
#define vchrTapWaveMax          0x1BFF
#endif

/*
 * PalmOS 5.0 SDK R2 defines the following constants for thumb wheel controllers.
 * we define them here as well in case the SDK is not updated
 * we use the same keycode for the "function" button
 */
#if !defined(vchrThumbWheelBack)
#define vchrThumbWheelBack		0x0131		// optional thumb-wheel cluster back
#endif

/*
 * PalmOS 5.0 SDK R2 defines the following constants for 5-way controller.
 * we define them here as well in case the SDK is not updated
 * we use the same keycode for the navigator 5-way events
 */
#if !defined(vchrRockerUp)
#define vchrRockerUp            0x0132      // 5-way rocker up
#define vchrRockerDown          0x0133      // 5-way rocker down
#define vchrRockerLeft          0x0134      // 5-way rocker left
#define vchrRockerRight         0x0135      // 5-way rocker right
#define vchrRockerCenter        0x0136      // 5-way rocker center/press
#endif


/* Virtual character for TapWave input event. */
#define vchrTwInput             (vchrTapWaveMin + 0)

/* Virtual character for changing orientation and graffiti. */
#define vchrTwConfig            (vchrTapWaveMin + 1)

/* Virtual characters for special reserved buttons. */
#define vchrBluetooth           (vchrTapWaveMin + 2)
#define vchrHome				vchrLaunch

/* Virtual characters for gaming buttons */
#define vchrFunction            vchrThumbWheelBack

/* Virtual characters for triggers. */
#define vchrTriggerLeft         (vchrTapWaveMin + 4)
#define vchrTriggerRight        (vchrTapWaveMin + 5)
#define vchrTriggerA            vchrTriggerLeft
#define vchrTriggerB            vchrTriggerRight

/* Map action buttons to Palm buttons for compatibility. */
#define vchrActionUp            (vchrTapWaveMin + 6)
#define vchrActionRight         (vchrTapWaveMin + 7)
#define vchrActionDown          (vchrTapWaveMin + 8)
#define vchrActionLeft          (vchrTapWaveMin + 9)

#define vchrActionA             vchrActionUp
#define vchrActionB             vchrActionRight
#define vchrActionC             vchrActionDown
#define vchrActionD             vchrActionLeft

/* Private virtual character used for generate keyUpEvent */
#define vchrTwKeyUp             (vchrTapWaveMin + 10)

/* Virtual characters for 5-way navigator. */
#define vchrNavUp               vchrRockerUp
#define vchrNavDown             vchrRockerDown
#define vchrNavLeft             vchrRockerLeft
#define vchrNavRight            vchrRockerRight
#define vchrNavSelect           vchrRockerCenter

/* Virtual characters for 9-way joystick corners. 
 * NOTE: These are never returned by EvtGetEvent().
 * Only the 5-way edges are returned by EvtGetEvent().
 * This results in better targetability with old
 * legacy apps that only understand the 5-way model.
 * 9-way apps, which want the corners, must check
 * the corners after receiving a 5-way keyDownEvent 
 * using KeyCurrentState() like so:
 *
 * Int32 keyState = KeyCurrentState();
 * if ((keyState & keyBitsNavUpLeft) == keyBitsNavUpLeft)
 *    keyCode = vchrNavUpLeft;
 *
 * The codes below are suggested as "safe" key codes.
 */
#define vchrNavUpLeft           (vchrTapWaveMin + 11)
#define vchrNavUpRight          (vchrTapWaveMin + 12)
#define vchrNavDownLeft         (vchrTapWaveMin + 13)
#define vchrNavDownRight        (vchrTapWaveMin + 14)

// keys sent by bluetooth hard button
#define vchrTwBluetoothLongPress    (vchrTapWaveMin + 15)
#define vchrTwBluetoothShortPress	(vchrTapWaveMin + 16)

/* Virtual character for background play status button. */
#define vchrTwMusicControl      (vchrTapWaveMin + 17)

// BB: 1/27/04 Key sent by app to turn off BT
#define vchrTwBluetoothOff		    (vchrTapWaveMin + 18)


#ifdef __cplusplus
}
#endif

#endif /* __TWCHARS_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
