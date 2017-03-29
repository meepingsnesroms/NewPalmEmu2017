/******************************************************************************
 *
 * Copyright (c) 1998-2001 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: AutoRun.h
 *
 * Release: 
 *
 * Description:
 *		SDIO AutoRun data structure and supporting info V0.0 03/01/2001
 *
 * History:
 *		03/01/2001 LLu Create the header using Pfutz's original header

 *		03/07/2001 Pfz adding mode function info.
 *
 *****************************************************************************/

#ifndef _AUTORUN_H
#define _AUTORUN_H

 

#include <NotifyMgr.h>  
#include <PalmTypes.h> 

 

//68K Notification event (The struct passed is in 68K endianism & size)
#define sysNotifyDriverSearch			'arun'		//This is for 68K programs
													//Sent after a card has been
													//inserted and the card's information
													//has been identified.
													//Is used for the RAM based sdio drivers
													//to launch themselves
													//param: ptr to AutoRunInfoType 

//AutoRun defines and structs 
typedef UInt32 AutoRunMediaType;		//This is the hardware that is requesting to run a program


//The next 4 typedefs these depend upon the AutoRunMediaType and are found on the "card" or "hardware"
typedef UInt32 AutoRunOemManufacturerType;	//A manufacturer number from the device
typedef UInt32 AutoRunOemProductIDType;		//A manufacturers product number from the device
typedef UInt16 AutoRunFunctionNumType;		//For multi-function devices, (if needed) 
typedef UInt16 AutoRunFunctionStandardType;	//For standard predefined Functions in a specification (i.e. modem, UART,...), (if needed) 


typedef UInt16 AutoRunSourceType;			//This defines which Union to use for information of the event source

#define autoRunSourceNone					((AutoRunSourceType)0)	//Driver source is: not used
#define autoRunSourceSlotDriverType			((AutoRunSourceType)1)	//Driver source is: AutoRunSlotDriverType



//
// Media types and expected associated info
//
#define	autoRunMediaMMCmem		((AutoRunMediaType)'mcmm')	//MMC memory cards
 //AutoRunOemManufacturerType = MMC's CID register, MID (8-bit unsigned Manufacturer field)
 //AutoRunOemProductIDType = MMC's CID Register, OID (16 bit unsigned OEM/Application ID)
 //AutoRunFunctionNumType = (not used)
 //AutoRunFunctionStandardType = (not used)
 //AutoRunSourceType=autoRunSourceSlotDriverType

#define	autoRunMediaMMCrom		((AutoRunMediaType)'mcrm')	//MMC ROM cards
 //AutoRunOemManufacturerType = MMC's CID register, MID (8-bit unsigned Manufacturer field)
 //AutoRunOemProductIDType = MMC's CID Register, OID (16 bit unsigned OEM/Application ID)
 //AutoRunFunctionNumType = (not used)
 //AutoRunFunctionStandardType = (not used)
 //AutoRunSourceType=autoRunSourceSlotDriverType

#define	autoRunMediaSDmem		((AutoRunMediaType)'sdmm')	//SD memory cards
 //AutoRunOemManufacturerType = SD's CID register, MID (8-bit unsigned Manufacturer field)
 //AutoRunOemProductIDType = SD's CID Register, OID (16 bit unsigned OEM/Application ID)
 //AutoRunFunctionNumType = (not used)
 //AutoRunFunctionStandardType = (not used)
 //AutoRunSourceType=autoRunSourceSlotDriverType

#define	autoRunMediaSDrom		((AutoRunMediaType)'sdrm')	//SD ROM cards
 //AutoRunOemManufacturerType = SD's CID register, MID (8-bit unsigned Manufacturer field)
 //AutoRunOemProductIDType = SD's CID Register, OID (16 bit unsigned OEM/Application ID)
 //AutoRunFunctionNumType = (not used)
 //AutoRunFunctionStandardType = (not used)
 //AutoRunSourceType=autoRunSourceSlotDriverType

#define	autoRunMediaSDIO		((AutoRunMediaType)'sdio')	//SD I/O cards
 //AutoRunOemManufacturerType = TPLMID_MANF field inside the function's CID CISTPL_MANFID tuple(16-bit Manufacturer field)
 //AutoRunOemProductIDType = TPLMID_CARD field inside the function's CID CISTPL_MANFID tuple(16 bit OEM/Application ID)
 //AutoRunFunctionNumType = 1-7
 //AutoRunFunctionStandardType = SD's FBR "I/O device interface code"

 #define autoRunFunctionStandardSDIOCustom			((AutoRunFunctionStandardType)0)	//driver for Custom function
 #define autoRunFunctionStandardSDIOUart			((AutoRunFunctionStandardType)1)	//driver for SDIO UART
 #define autoRunFunctionStandardSDIOBlueToothFat	((AutoRunFunctionStandardType)2)	//driver for SDIO Bluetooth Fat
 #define autoRunFunctionStandardSDIOBlueToothThin	((AutoRunFunctionStandardType)3)	//driver for SDIO BlueTooth Thin
 //AutoRunSourceType=autoRunSourceSlotDriverType


#define	autoRunMediaPnps		((AutoRunMediaType)'pnps')	//Plug and Play for a Serial Perpherial
 //AutoRunOemManufacturerType = Pnps's Configuration Data Structure, Vendor ID (16-bit unsigned field)
 //AutoRunOemProductIDType = Pnps's Configuration Data Structure, Device ID (16-bit unsigned field)
 //AutoRunFunctionNumType = (not used)
 //AutoRunFunctionStandardType = (not used)
 //AutoRunSourceType=autoRunSourceSlotDriverType




//--------------------------------------------------------------------------------------------------------------------------
//Data Structures that identify the broadcaster (for the "source" union)
//

typedef struct AutoRunSlotDriverType	
{
    UInt16 volRefNum;       //if!=vfsInvalidVolRef an optional file system was mounted
    UInt16 slotLibRefNum;   //slot driver that originated this call
    UInt16 slotRefNum;      //if!=expInvalidSlotRefNum, slot driver that originated this call
}AutoRunSlotDriverType;


//--------------------------------------------------------------------------------------------------------------------------
//Data Structure to be broadcast to the drivers to identify the card
//inserted and for each registered driver to examine. 
//Use/Check the handled variable included in the SysNotifyParamType to indicate
//that:
// 1) if handled=true, it is already being used by another driver or
// 2) if handled=false, then set handled=true to indicate that you (the driver) are in control of this device. 
//

typedef struct _AutoRunInfoType
{
AutoRunMediaType    			media;            //AutoRun's official media type
AutoRunOemManufacturerType		oemManufacturer;		//A manufacturer number from the device
AutoRunOemProductIDType			oemID;					//A manufacturers product number from the device
AutoRunFunctionNumType			oemFunctionNum;			//For multi-function devices, (if needed) 
AutoRunFunctionStandardType		oemFunctionStandard;	//For standard predefined Functions in a specification (i.e. modem, UART,...), (if needed) 
AutoRunSourceType   			sourceStruct;     //This defines which Union to use for information of the event source
	union						//Information about finding the driver source, see sourceStruct
	{
	     AutoRunSlotDriverType	slotDriver;
	}source;
}AutoRunInfoType;


typedef AutoRunInfoType* AutoRunInfoP;

#endif //_AUTORUN_H
