/******************************************************************************
 *
 * Copyright (c) 1998-2001 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: BtTransportLib.h
 *
 * Release: 
 *
 * Description:
 *          	Public Bluetooth HCI transport definitions.
 *
 * History:
 *		Name	Date		Description
 *		----	----		-----------
 *		jhl	08/24/00	Initial Revision
 *		jhl	11/30/00	Convert to single transport type per instance of library.
 *
 *****************************************************************************/

#ifndef _BTTRANSPORTLIB_H
#define _BTTRANSPORTLIB_H

#include "BtTransportLibTypes.h"


//============================================================================
// Library API definitions
//============================================================================

#ifdef __cplusplus
extern "C" {
#endif


Err BtTransportOpen(UInt16 libRefNum,
	BtTransportProcSpecType *procSpecP)
		SYS_TRAP(sysLibTrapOpen);
					
Err BtTransportClose(UInt16 libRefNum)
		SYS_TRAP(sysLibTrapClose);
					
Err BtTransportSleep(UInt16 libRefNum)
		SYS_TRAP(sysLibTrapSleep);
					
Err BtTransportWake(UInt16 libRefNum)
		SYS_TRAP(sysLibTrapWake);
		
Err BtTransportSend(UInt16 libRefNum,
	void *bufHandleP,
	UInt8 type,
	UInt8 *fragP[],
	UInt16 fragLen[],
	UInt16 frags)
		SYS_TRAP(btTransportLibTrapSend);

Err BtTransportControl(UInt16 libRefNum,
	UInt16 control,
	void *paramP,
	UInt16 *paramLengthP)
		SYS_TRAP(btTransportLibTrapControl);
	

#ifdef __cplusplus
}
#endif

#endif	// _BTTRANSPORTLIB_H
