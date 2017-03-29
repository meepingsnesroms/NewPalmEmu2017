/******************************************************************************
 *
 * Copyright (c) 2000-2002 Palmsource, Inc. All rights reserved.
 *
 * File: BtPrefsPnlTypes.h
 *
 * Release: Palm OS 5 SDK (68K) R2.
 *
 * Description:
 *		Include file for Bluetooth Preferences Panel
 *
 *****************************************************************************/

#ifndef __BTPREFSPNLTYPES_H__
#define __BTPREFSPNLTYPES_H__

#include "BtLibTypes.h"

#define kBluetoothPanelPrefID			0x01
#define kBluetoothPanelPrefVersion		0x01

#ifndef sysFileCBluetoothPanel
#define	sysFileCBluetoothPanel			'abtp'	// Creator type for Bluetooth Panel
#endif

// default panel setting
#define BTLIB_DEFAULT_ACCESS			true
#define BTLIB_DEFAULT_DISCOVERABLE		true
#define BTLIB_DEFAULT_ALLOWWAKEUP		false
#define BTLIB_DEFAULT_USECACHE			true

typedef struct _BluetoothPanelPrefsType {
	Boolean					bBlueTooth;		// Bluetooth On/Off
	Boolean					bDiscoverable;	// Can be discovered
	Char					friendlyName[btLibMaxDeviceNameLength];	// Device name, -HotSync- name as default
	Boolean					bAllowWakeup;	// Allow to wake-up
	UInt16					WakeupAlert;	// Alert type
	Boolean					bUseCache; // Method of getting the name from the cache or the remote device
} BluetoothPanelPrefsType;

// Service Panel parameter block structure for sysAppLaunchCmdPanelCalledFromApp
// The parameter block must be allocated using MemPtrNew, with the owner set to 0 (zero)
// using MemPtrSetOwner(void * p, UInt16 owner).  All data must be contained within the single
// memory chunk.
//
typedef enum SvcCalledFromAppCmdEnum {
	svcCFACmdSetBtOnOff = 1,				// Set prefs bluetooth on/off
	svcCFACmdLaunchTrustForm,				// Launch the Trusted Device Form
	
	// Add new commands here before svcCFACmdLast
	
	svcCFACmdLast
} SvcCalledFromAppCmdEnum;

typedef struct SvcCalledFromAppPBType {
	SvcCalledFromAppCmdEnum	cmd;					// command
	// Union of command data structures
	union {
		Boolean	bValue;
	} data;	
} SvcCalledFromAppPBType;

typedef SvcCalledFromAppPBType*	SvcCalledFromAppPBPtr;


#endif
