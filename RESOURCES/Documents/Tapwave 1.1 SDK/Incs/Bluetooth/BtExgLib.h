/***********************************************************************
 *
 * Copyright (c) 2000-2001 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: BtExgLib.h
 *
 * Release: 
 *
 * Description: 
 *		Public include file for the Bluetooth Exchange Library.
 *
 * History:
 *      5/31/00 Created by Tom Keel
 *
 **********************************************************************/

#ifndef BTEXGLIB_H
#define BTEXGLIB_H

//  The Bluetooth Exchange Library is a concrete, Bluetooth-specific 
//  implementation of the abstract Exchange Library.
//
//  The file ExgLib.h defines public things that are common to all
//  Exchange Libraries, including entrypoint trapnumbers.
//
//  This file defines public things that are specific to the Bluetooth
//  Exchange Library, including trapnumbers for entrypoints that extend
//  the Exchange Library.

#include <ExgLib.h>

/*-------------------------------------+
 |  Types and constants                |
 *-------------------------------------*/

//  Name of this library
//
#define btexgLibName "Bluetooth Exchange Library"

//  Feature Creators and Feature Numbers, for use with the FtrGet() call.
//  The version number format is 0xMMmfsbbb, where MM is major version,
//  m is minor version, f is bug fix, s is stage, and  bbb is build number
//  for non-releases. Stage is 3=release, 2=beta, 1=alpha, 0=development.
//      V1.12b3 ==  0x01122003
//      V2.00a2 ==  0x02001002
//      V1.01   ==  0x01013000
//
#define btexgFtrCreator     sysFileCBtExgLib
#define btexgFtrNumVersion  0

// Pre-defined URL schemes
#define btexgScheme				"_btobex"
#define btexgSingleScheme		"_single"
#define btexgMultiScheme		"_multi"
#define	btexgURLSeparator		"/"
#define	btexgBdAddrSeparator	","

// Pre-defined URL prefixes
#define btexgPrefix				(btexgScheme "://")
#define btexgSimplifiedPrefix	(btexgScheme ":")

// Pre-defined URL suffixes
#define btexgSingleSufix	("?" btexgSingleScheme btexgURLSeparator)
#define btexgMultiSufix		("?" btexgMultiScheme btexgURLSeparator)

// The following defentions are from an updated version fo ExgMgr.h (post 4.1)
// they are included here incase the ExgMrg.h is not up to date
#ifndef exgLibCtlGetURL
	#define exgLibCtlGetURL			4					// get current URL
	
	typedef struct ExgCtlGetURLType {
		ExgSocketType	*socketP;
		Char			*URLP;
		UInt16			URLSize;
	} ExgCtlGetURLType;
#endif // #ifndef exgLibCtlGetURL

//------------------
//
//  Trapnumbers beyond those of the generic Exchange Library (EgxLib.h).
//  The first trapnumber defined here must be equal to exgLibTrapLast.
//  btexgLibTrapLast must be set equal to the first available trapnumber
//  beyond those defined here.
//
//  For now, there are no non-generic trapnumbers.
//
#ifdef __GNUC__
#   define btExgLibTrapUnload  (exgLibTrapLast)
#   define btexgLibTrapLast    (exgLibTrapLast+1)
#else
#   pragma mark Traps
    typedef enum
    {
        btExgLibTrapUnload = exgLibTrapLast,

        btexgLibTrapLast
    }
    btexgLibTrapNumberEnum;
#endif

/*-------------------------------------+
 |  Public functions                   |
 *-------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

//------------------
//
//  Entrypoints beyond those of the generic Exchange Library (ExgLib.h).
//  For now, there are no non-generic entrypoints, but they would look like:
//
//  Err BtExgAnEntrypoint(
//      UInt16 refNum,    // library reference number
//      UInt32 param1,    // parameter number 1
//      UInt32 param2     // parameter number 2 ...
//  )
//      SYS_TRAP( btexgLibTrapAnEntrypoint );

#ifndef PUBLIC_STUFF_STRIPPED
#pragma mark *-------- Non-Public----------*

//--------------------------------------------------------------------	
// Directs library to release all resources and prepare to be removed.
//
Err BtExgLibUnload(UInt16 btLibRefNum)
	SYS_TRAP(btExgLibTrapUnload);

#endif // PUBLIC_STUFF_STRIPPED

#ifdef __cplusplus 
}
#endif

#endif // BTEXGLIB_H
