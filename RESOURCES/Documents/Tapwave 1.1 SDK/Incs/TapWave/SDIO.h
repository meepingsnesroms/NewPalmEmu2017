/******************************************************************************
 *
 * Copyright (c) 1998-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: SDIO.h
 *
 * Release: 
 *
 * Description:
 *        SDIO Slot driver Custom Calls, 07/17/2001
 *        Update for ARM or 68K compile on OS 5.0, 03/19/2002
 *
 *****************************************************************************/

#ifndef __SDIO_h_
#define __SDIO_h_

#include <PalmTypes.h>
#include <SystemResources.h>
#include <NotifyMgr.h>
#include <SystemMgr.h>
#include "SlotDrvrLib.h"
#include "AutoRun.h"

#ifndef INLINE_FNC
#if defined (__arm)			//ARM code warrior method
	#define INLINE_FNC				__inline
#elif defined (__MWERKS__)	//68K code warrior method
	#define INLINE_FNC				inline
#else
	// Define it to nothing
	#define INLINE_FNC
#endif
#endif

#define sysFileApiCreatorSDIO 'sdio'    //API apiCreator for slot driver SlotCustomControl()
//
//    SlotCustomControl() calls, value of "UInt16 apiSelector"
//    note: apiCreator  = sysFileApiCreatorSDIO
//All calls return the proper expansion manager Err (ie expErrUnsupportedOperation) codes.
//    plus the error codes: sysErrParamErr 
//
typedef UInt16 SDIOCustomType;
#define sdioAPIVersion             0  //valueP is a SDIOAPIVersionType
#define sdioGetPower               1  //valueP is a SDIOPowerType
#define sdioSetPower               2  //valueP is a SDIOPowerType
#define sdioGetAutoPowerOff        3  //valueP is a SDIOAutoPowerOffType
#define sdioSetAutoPowerOff        4  //valueP is a SDIOAutoPowerOffType
#define sdioGetCurrentLimit        5  //valueP is a SDIOCurrentLimitType
#define sdioSetCurrentLimit        6  //valueP is a SDIOCurrentLimitType
#define sdioRemainingCurrentLimit  7  //valueP is a SDIOCurrentLimitType
#define sdioGetSlotInfo            8  //valueP is a SDIOSlotInfoType
#define sdioGetInfo                9  //valueP is a SDIOCardInfoType
#define sdioSetBitMode             10 //valueP is a SDIOSDBitModeType, Note: this can be refused by expErrUnsupportedOperation
#define sdioGetCallback            11 //valueP is a SDIOCallbackType
#define sdioSetCallback            12 //valueP is a SDIOCallbackType
#define sdioGetAutoRun             13 //valueP is a AutoRunInfoType
#define sdioRWDirect               14 //valueP is a SDIORWDirectType
#define sdioRWExtendedByte         15 //valueP is a SDIORWExtendedByteType
#define sdioRWExtendedBlock        16 //valueP is a SDIORWExtendedBlockType
#define sdioTupleWalk              17 //valueP is a SDIOTupleType
#define sdioAccessDelay            18 //valueP is a SDIOAccessDelayType
#define sdioDebugOptions           19 //valueP is a SDIODebugOptionType
#define sdioDisableMasterInterrupt 20 //valueP is a NULL
#define sdioEnableMasterInterrupt  21 //valueP is a NULL

typedef UInt16 SDIOFuncType;
#define sdioFunc0    0     //This is for the SDIO function 0 area (CIA) of the SD card.
#define sdioFunc1    1     //This is for the SDIO function 1 area of the SD card
#define sdioFunc2    2     //This is for the SDIO function 2 area of the SD card
#define sdioFunc3    3     //This is for the SDIO function 3 area of the SD card
#define sdioFunc4    4     //This is for the SDIO function 4 area of the SD card
#define sdioFunc5    5     //This is for the SDIO function 5 area of the SD card
#define sdioFunc6    6     //This is for the SDIO function 6 area of the SD card
#define sdioFunc7    7     //This is for the SDIO function 7 area of the SD card
#define sdioFuncEntries  8 //The number of choices to make

typedef UInt16 SDIOSlotType;
#define sdioSlotSDMem    0 //This is for the SDMem Slot (for regular memory cards or SD combo cards)
#define sdioSlotFunc1    1 //This is for the SDIO function 1 Slot for SDIO cards
#define sdioSlotFunc2    2 //This is for the SDIO function 2 Slot for SDIO cards
#define sdioSlotFunc3    3 //This is for the SDIO function 3 Slot for SDIO cards
#define sdioSlotFunc4    4 //This is for the SDIO function 4 Slot for SDIO cards
#define sdioSlotFunc5    5 //This is for the SDIO function 5 Slot for SDIO cards
#define sdioSlotFunc6    6 //This is for the SDIO function 6 Slot for SDIO cards
#define sdioSlotFunc7    7 //This is for the SDIO function 7 Slot for SDIO cards



typedef UInt32 SDIOAPIVersionType;    //a version number of this SDIO slot driver (if an error return, SDIO is not supported)

typedef UInt16 SDIOCardPowerType;
#define sdioCardPowerOff    0    //turn off the card, put the data signals in a low power state
#define sdioCardPowerOn     1    //power on and initialize the card
#define sdioCardResetSDMem  2    //This will force the SDMem portion of a SD combo card to be software reset by a CMD0, the function will return after the card is initialized
#define sdioCardWaitSDIO    3    //This will wait the SDIO portion to of a SD card to be ready (via CMD5), use this after resetting 1 or more function(s). 

typedef struct {                // For sdioGetPower/sdioSetPower
SDIOSlotType sdioSlotNum;       //In/In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
SDIOCardPowerType powerOnCard;  //In/Out: turns on/off the SDIO card
}SDIOPowerType;

typedef struct {		    //Get/Set/Remaining
SDIOSlotType sdioSlotNum;   //In/In/unused; This current Slot driver's function number (Note: sdioFunc0 is reserved for the SDMem Slot driver and function 0)
UInt32 uaMaximum;           //Out/In/Out;Set this functions maximum peak current (in micro-amps) or get the remaining maximum current for the entire card 
}SDIOCurrentLimitType;
//Note: when card is removed, all allocations of current are set to zero.


typedef struct {                //Get/Set: For sdioPowerManagementGet/sdioPowerManagementSet
SDIOSlotType sdioSlotNum;       //In/In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
UInt16 ticksTillOff;            //Out/In: if==0 disable auto time off, if!=0 the SysTicksPerSecond() to approximate delay before auto turning off.
SDIOCardPowerType sleepPower;   //Out/In: Will control the power to the card when going asleep
}SDIOAutoPowerOffType;

typedef struct {
SDIOSlotType sdioSlotNum;   //In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
UInt16    volRefNum;        //Out: if!=vfsInvalidVolRef, an optional file system that was mounted
UInt16    slotLibRefNum;    //Out: always valid for a slot driver call, even if card is removed
UInt16    slotRefNum;       //Out: if!=expInvalidSlotRefNum, a valid slot driver number, even if card is removed
}SDIOSlotInfoType;


typedef UInt16 SDIOBitsOfFileSystemType;
#define  sdioBitsOfFileSystemMemory     0x0001    //This card supports Standard SDMem memory card is present
#define  sdioBitsOfFileSystemFunction1  0x0002    //This card has a standard SDIO file system in function 1
#define  sdioBitsOfFileSystemFunction2  0x0004    //This card has a standard SDIO file system in function 2
#define  sdioBitsOfFileSystemFunction3  0x0008    //This card has a standard SDIO file system in function 3
#define  sdioBitsOfFileSystemFunction4  0x0010    //This card has a standard SDIO file system in function 4
#define  sdioBitsOfFileSystemFunction5  0x0020    //This card has a standard SDIO file system in function 5
#define  sdioBitsOfFileSystemFunction6  0x0040    //This card has a standard SDIO file system in function 6
#define  sdioBitsOfFileSystemFunction7  0x0080    //This card has a standard SDIO file system in function 7

typedef UInt16 SDIOBitsOfStatusType;
#define  sdioBitsOfStatusDriverHandledMemory 0x0001 //This card has an Auto Run function driver in the Standard SDMem memory 
#define  sdioBitsOfStatusDriverHandledFunc1  0x0002 //This card has an Auto Run function driver in function 1
#define  sdioBitsOfStatusDriverHandledFunc2  0x0004 //This card has an Auto Run function driver in function 2
#define  sdioBitsOfStatusDriverHandledFunc3  0x0008 //This card has an Auto Run function driver in function 3
#define  sdioBitsOfStatusDriverHandledFunc4  0x0010 //This card has an Auto Run function driver in function 4
#define  sdioBitsOfStatusDriverHandledFunc5  0x0020 //This card has an Auto Run function driver in function 5
#define  sdioBitsOfStatusDriverHandledFunc6  0x0040 //This card has an Auto Run function driver in function 6
#define  sdioBitsOfStatusDriverHandledFunc7  0x0080 //This card has an Auto Run function driver in function 7
#define sdioBitsOfStatusWriteProtectTab      0x0100 //if==1 the write protect tab on the card indicates that this card is write protected

typedef UInt16 SDIOSDBitModeType;
#define    sdioSD1BitMode    1 //SDIO bit mode 1 (SD or SPI mode)
#define    sdioSD4BitMode    4 //SDIO bit mode 4 (SD mode only)

typedef struct {
SDIOSlotType requestingFunc; //In; The function number (1-7) making this request (to be turned on)
SDIOSDBitModeType  bitMode;  //In; The requested SDIO Bit mode of the card
} SDIOSDBitModeRequestType;

typedef struct {
UInt16                      numberOfFunctions;  //Out; 0=no functions, or 1-7 SDIO functions on the card
SDIOSDBitModeType           bitMode;            //Out; The current SDIO Bit mode of the card
SDIOBitsOfFileSystemType    bitsOfFileSystem;   //Out: bit=1 for file system supported (not necessary mounted!)
SDIOBitsOfStatusType        bitsOfStatus;       //Out: various status bits
}SDIOCardInfoType;

//
//Warning, when using call backs lock you variables and call back routines (applications automatically do this IF they are executing)
//Note: These callbacks are "forgotten" when the SDIO card is inserted or removed!
//
typedef Err (*SDIOCallbackPtr)( SDIOSlotType sdioSlotNum, void *userDataP );

typedef UInt16 SDIOCallbackSelectType;
//Warning, the first 5 callbacks can be called from an interrupt and a non-interrupt routine!
#define sdioCallbackSelectInterruptSDCard    0    //select callback for when an SDIO card interrupts the host (Warning: This is an Interrupt routine)
#define sdioCallbackSelectSleep              1    //select callback for when the Palm wants to go to sleep.
#define sdioCallbackSelectAwake              2    //select callback for when the Palm wants to wake up.
#define sdioCallbackSelectPowerOn            3    //select callback for when the SDIO card power is turned on.
#define sdioCallbackSelectPowerOff           4    //select callback for when the SDIO card power is turned off.
//
#define sdioCallbackSelectReset              5    //select callback for when the SDIO section of the card is reset
#define sdioCallbackSelectBitMode            6	  //select callback for when the bus width of the card is changed
#define sdioCallbackSelectEntries            7    //the number of choices to make

typedef struct {                        //Get/Set
SDIOSlotType sdioSlotNum;               //In/In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
SDIOCallbackSelectType callbackSelect;  //In/In; The callback to modify
SDIOCallbackPtr callBackP;              //Out/In: If!=NULL, pointer to callback function, see callbackSelect for desired callback 
MemPtr userDataP;                       //Out/In; If!=NULL, a pointer to user data so that the user can access variables it needs
}SDIOCallbackType;

//
//See AutoRun.h for the slot driver auto run notifications 
//

typedef struct {
SDIOSlotType sdioSlotNum;    //In/In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
AutoRunInfoType autoRun;     //Out: The Palm Auto Run information filled out. 
}SDIOAutoRunInfoType;

typedef UInt16 SDIORWModeType;
#define sdioRWModeWrite            0x0001    //if set, "bufferP" will be written to the card
#define sdioRWModeRead             0x0002    //if set, a read IO card is issued and data is placed into "bufferP"
#define sdioRWModeWriteRead        (sdioRWModeWrite|sdioRWModeRead)    //if set, "bufferP" will be written to the card, the a read will take place into "bufferP"
#define sdioRWModeFixedAddress     0x0004    //if set, a multibyte read or write is to a fixed address
#define sdioRWModeForceBlockSize   0x0008    //if set, SDIORWExtendedBlock will always set the block size (if driver resets function or reprograms "IO block size" in FBR)

//
//Note: The Slot driver optimizes the SDIO read/write access
//
typedef struct {
SDIOSlotType requestingFunc;    //In; The function number (1-7) making this request (to be turned on)
SDIORWModeType mode;            //In; how to access that card
SDIOFuncType funcNum;           //In; The SDIO cards function number to access. 
UInt32 byteAddress;             //In: 17 bits of SDIO address
UInt8 byteData;                 //In/Out: place to put (read) or get (write) the byte of data
}SDIORWDirectType;

typedef struct {
SDIOSlotType requestingFunc;    //In; The function number (1-7) making this request (to be turned on)
SDIORWModeType mode;            //In; how to access that card
SDIOFuncType funcNum;           //In; The SDIO cards function number to access. 
UInt32 byteAddress;             //In: 17 bits of SDIO address
MemPtr bufferP;                 //In/Out: place to put (read) or get (write) data
UInt16 numBytes;                //In: Number of bytes to transfer (1-511 = 1-511 bytes, 0 or 512 = 512)
}SDIORWExtendedByteType;

typedef struct {
SDIOSlotType requestingFunc;    //In; The function number (1-7) making this request (to be turned on)
SDIORWModeType mode;            //In; how to access that card
SDIOFuncType funcNum;           //In; The SDIO cards function number to access. 
UInt32 byteAddress;             //In: 17 bits of SDIO address
MemPtr bufferP;                 //In/Out: place to put (read) or get (write) data
UInt16 numBlocks;               //In: Number of blocks to transfer (0=forever, 1-511=1-511 blocks)
UInt16 ioBlockSize;             //In: the block size (1-0x0800=1 to 0x0800 bytes/block, all others are illegal)
}SDIORWExtendedBlockType;
//Note: setting numBlocks=0 (forever number of blocks) is currently illegal at this time!

typedef struct {
SDIOSlotType requestingFunc;  //In; The function number (1-7) making this request (to be turned on)
SDIOFuncType funcNum;         //In; The SDIO card function number to access. 
UInt8 tupleToFind;	          //In; The tuple to find
MemPtr bufferP;               //In: The place to put the contents of a found tuple
UInt16 bufferSizeOf;          //In; The size of the supplied buffer
}SDIOTupleType;

typedef UInt16 SDIOAccessDelayType; //In; The Maximum access time (in milliseconds) for reads & writes of SDIO commands CMD52/CMD53

typedef UInt16 SDIODebugOptionType;
//
// Note: these are available ONLY on Debug roms or Debug patches (*.prc's)
// and they require a serial port (ie your handheld must be plugged into cradle! Cradle can be RS232 or USB.)
// for best visual results use a debugger, code warrior works (but it adds more <CR><LF>'s)
//
#define sdioDebugOptionTraceCmds      ((SDIODebugOptionType)0x0001) //if==1, prints all commands to the card on serial port
#define sdioDebugOptionTraceRejection ((SDIODebugOptionType)0x0002) //if==1, prints rejection reasons on serial port
#define sdioDebugOptionTraceCmdData   ((SDIODebugOptionType)0x0004) //if==1, prints the data from commands that have command/response/data, warning, This is alot of data!
#define sdioDebugOptionTraceContents  ((SDIODebugOptionType)0x0008) //if==1, prints the used Contents of Tuples and/or parts of the CSD 
#define sdioDebugOptionTraceProgress  ((SDIODebugOptionType)0x0010) //if==1, prints the progress of the card (ie SD memory card) 
#define sdioDebugOptionTraceISR		  ((SDIODebugOptionType)0x0020) //if==1, allows printing within interrupt routines, Warning: keep stack small to avoid overflows
//
#define sdioDebugOptionTraceMost       (sdioDebugOptionTraceCmds|sdioDebugOptionTraceRejection|sdioDebugOptionTraceContents|sdioDebugOptionTraceProgress|sdioDebugOptionTraceISR) 
#define sdioDebugOptionTraceAll        ((UInt16)-1) //turn on all options.
#define sdioDebugOptionTraceNone       (0)  //turn off all options.

/************************************************************
 *
 *  FUNCTION:    SDIOAPIVersion
 *
 *  DESCRIPTION:    This call is used to detect if the Slot Driver is SDIO aware and want SDIO version software 
 *                  it is executing. If it returns "errNone" the Slot driver is SDIO aware and the version number 
 *                  of the SDIO part of the slot driver is in the SDIOAPIVersionType.
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              versionP         -- Pointer to UInt32 to hold the version number of this SDIO aware slot driver
 *
 *  RETURNS:    errNone          -- versionP successfully set.
 *              sysErrParamErr  - *versionP unrecognizable (it is a NULL)
 *              expErrUnimplemented (or any other error) -- SDIO not supported in this slot driver
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does not require a SDIO card in the slot to work
 *************************************************************/
Err INLINE_FNC SDIOAPIVersion( UInt16 slotLibRefNum, SDIOAPIVersionType *versionP );
Err INLINE_FNC SDIOAPIVersion( UInt16 slotLibRefNum, SDIOAPIVersionType *versionP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioAPIVersion, versionP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetPower & SDIOSetPower
 *
 *  DESCRIPTION: These commands either get the current state of the cards power & bus signals, or sets the 
 *                power and bus signals such that:
 *                1) The entire slot turned on (power is applied to the card and the data bus is ready to transmit 
 *                    or receive commands).
 *                or 
 *                2) Turns off the entire slot for low power consumption (power is removed from the card, 
 *                    and the data bus is set to a low power state).
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              powerP           -- Pointer to SDIOPowerType struct which:
 *                    powerOnCard;    In/Out: turns on/off the SDIO card
 *
 *  RETURNS:    errNone            -- powerP successfully get/set.
 *              sysErrParamErr  - *powerP unrecognizable
 *              expErrCardNotPresent  - Card has been removed
 *	expErrCardBadSector - The card did not initialize
 *              expErrUnimplemented -- SDIO not supported in this slot driver
 *
 *Notes:    
 * - This does NOT check the battery level, turning the SDIO card might lockout the Palm.
 * - This does NOT check the current (micro-ampere) limits
 *
 * Note: These routines are safe for interrupts.
 * Note: Only SDIOSetPower() requires a SDIO card in the slot, turning on power will also access the card (for initialization)
 * Note: Do not call the SDIOSetPower() function from the PowerOn or PowerOff callback
 * Note: When the card is turned off, SDIO interrupts cannot occur.
 *************************************************************/
Err INLINE_FNC SDIOGetPower( UInt16 slotLibRefNum, SDIOPowerType *powerP );
Err INLINE_FNC SDIOGetPower( UInt16 slotLibRefNum, SDIOPowerType *powerP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetPower, powerP, NULL ) );
}
Err INLINE_FNC SDIOSetPower( UInt16 slotLibRefNum, SDIOPowerType *powerP );
Err INLINE_FNC SDIOSetPower( UInt16 slotLibRefNum, SDIOPowerType *powerP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioSetPower, powerP, NULL ) );
}


/************************************************************
 *
 *  FUNCTION:    SDIOGetAutoPowerOff & SDIOSetAutoPowerOff
 *
 *  DESCRIPTION: Every time a card is inserted the card will default to:
 *              "ticksTillOff" = about 15 seconds
 *              "sleepPower" = sdioCardPowerOff 
 *              Another default behavior of the card is when the palm wakes up, it does not turn on the card.
 *              Instead it waits until there is a request to use the card. Then the card is turned on.
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              autoP            -- Pointer to SDIOAutoPowerOffType struct which controls the automatic 
 *                                power management to the SD card/bus. 
 *                    ticksTillOff; Out/In: if==0 disable auto time off, if!=0 the SysTicksPerSecond() to approximate delay 
 *                                        before auto turning off.
 *                    sleepPower;      Out/In: Will control the power to the card when going asleep.
 *
 *  RETURNS:    errNone            -- autoP successfully get/set.
 *              sysErrParamErr  - *autoP unrecognizable
 *              expErrCardNotPresent  - Card has been removed
 *              expErrUnimplemented (or any other error) -- SDIO not supported in this slot driver
 *              sysErrParamErr - a parameter within autoP is not allowed or wrong or missing.
 *
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do require a SDIO card in the slot, since removing a card will erase these settings
 * Note: autoP->sdioSlotNum cannot be memory cards (sdioSlotSDMem)
 *************************************************************/
Err INLINE_FNC SDIOGetAutoPowerOff( UInt16 slotLibRefNum, SDIOAutoPowerOffType *autoP );
Err INLINE_FNC SDIOGetAutoPowerOff( UInt16 slotLibRefNum, SDIOAutoPowerOffType *autoP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetAutoPowerOff, autoP, NULL ) );
}
Err INLINE_FNC SDIOSetAutoPowerOff( UInt16 slotLibRefNum, SDIOAutoPowerOffType *autoP );
Err INLINE_FNC SDIOSetAutoPowerOff( UInt16 slotLibRefNum, SDIOAutoPowerOffType *autoP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioSetAutoPowerOff, autoP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetCurrentLimit & SDIOSetCurrentLimit  & SDIORemainingCurrentLimit
 *
 *  DESCRIPTION: This is an allocation utility, to make sure that the different functions never allocate 
 *                more current than the Palm hardware can handle. The SDIO V1.0 specification states that 
 *                may not draw more than 200ma maximum. "Standard functions" supported by Palm will use the 
 *                "sdioSetCurrentLimit" call to try and allocate (Set) their share of current. User SDIO Function Drivers 
 *                should also use this to limit the total current draw. 
 *                Note: This does NOT reflect how much energy the battery can handle. The Battery manager rates 
 *                    the battery as a percent (not micro-amperes).  
 *                This function only software manages the total maximum current of the card.
 *                It is only needed if the SDIO card can draw more than the SDIO specification maximum of 200ma.  
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              currentLimitP   -- Pointer to SDIOCurrentLimitType struct which:
 *                  slotFuncNum;    //In/In/Unused; This current Slot driver's function number (Note: sdioFunc0 is reserved for the 
 *                                        SDMem Slot driver and function 0)
 *                 uaMaximum;     //Out/In/Out ;Get/Set this functions maximum peak current (in micro-amps) 
 *                                                                   or get the remaining current for the entire SDIO card.
 *
 *  RETURNS:    errNone            -- currentLimitP successfully get/set.
 *              expErrNotEnoughPower - there is not enough current to turn on this function, turn something off! 
 *              sysErrParamErr  - a parameter within currentLimitP is not allowed or wrong or missing. 
 *              expErrCardNotPresent  - Card has been removed
 *              expErrUnimplemented  -- SDIO not supported in this slot driver
 *
 *Notes:    
 *    - This does NOT check the battery level, turning the SDIO card might lockout the Palm.
 *  - When card is removed, all allocations of current are set to zero.
 *  - Remember to call SDIOSetCurrentLimit() after functions have been set to their low current states and 
 *              before functions have been set to their higher current states.
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do require a SDIO card in the slot, since removing a card will erase these settings
 *************************************************************/
Err INLINE_FNC SDIOGetCurrentLimit( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP );
Err INLINE_FNC SDIOGetCurrentLimit( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetCurrentLimit, currentLimitP, NULL ) );
}
Err INLINE_FNC SDIOSetCurrentLimit( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP );
Err INLINE_FNC SDIOSetCurrentLimit( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioSetCurrentLimit, currentLimitP, NULL ) );
}
Err INLINE_FNC SDIORemainingCurrentLimit ( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP );
Err INLINE_FNC SDIORemainingCurrentLimit ( UInt16 slotLibRefNum, SDIOCurrentLimitType *currentLimitP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioRemainingCurrentLimit, currentLimitP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetSlotInfo
 *
 *  DESCRIPTION: This allows the caller to find the slotLibRefNum/slotRefNum numbers of
 *                 another function or the main SDMem Slot driver.
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              slotInfoP         -- Pointer to SDIOSlotInfoType struct which indicates which function/SDMem to find.
 *                    sdioSlotNum; //In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
 *                    volRefNum;           //Out: if!=vfsInvalidVolRef, an optional file system that was mounted
 *                    slotLibRefNum;       //Out: always valid for a slot driver call, even if card is removed
 *                    slotRefNum;            //Out: if!=expInvalidSlotRefNum, a valid slot driver number, even if card is removed
 *
 *  RETURNS:    errNone            -- slotInfoP successfully get.
 *              sysErrParamErr  - *slotInfoP unrecognizable or NULL
 *              expErrUnimplemented -- SDIO not supported in this slot driver
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do not require a SDIO card in the slot
 *************************************************************/
Err INLINE_FNC SDIOGetSlotInfo( UInt16 slotLibRefNum, SDIOSlotInfoType *slotInfoP );
Err INLINE_FNC SDIOGetSlotInfo( UInt16 slotLibRefNum, SDIOSlotInfoType *slotInfoP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetSlotInfo, slotInfoP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetCardInfo
 *
 *  DESCRIPTION: This gives some information about the card 
 *                from the SDIO IO_QUERY command (ACMD57). 
 *                All other information on the card can be obtained by the normal SDIO read & write calls.
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              cardInfoP           -- Pointer to SDIOCardInfoType struct which indicates:
 *                    numberOfFunctions; Output, 0=no functions, or 1-7 SDIO functions on the card
 *                    bitMode;           Output, The current SDIO Bit mode of the card
 *                    bitsOfFileSystem;  Output, multiple bits that if==1 indicate a file system is supported (not necessary mounted!)
 *                    bitsOfStatus;      Out: various status bits
 *
 *  RETURNS:    errNone            -- cardInfoP successfully get.
 *              sysErrParamErr  - *cardInfoP unrecognizable or NULL
 *              expErrCardNotPresent  - Card has been removed
 *              expErrUnimplemented  -- SDIO not supported in this slot driver
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does require a SDIO card in the slot, however information is cached in RAM
 *************************************************************/
Err INLINE_FNC SDIOGetCardInfo( UInt16 slotLibRefNum, SDIOCardInfoType *cardInfoP );
Err INLINE_FNC SDIOGetCardInfo( UInt16 slotLibRefNum, SDIOCardInfoType *cardInfoP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetInfo, cardInfoP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOSetBitMode
 *
 *  DESCRIPTION: This attempts to change the bus width. But due to hardware constraints, this command 
 *                can be rejected and return with "expErrUnsupportedOperation". 
 *                The current bit mode can be obtained by "sdioGetInfo".
 *                Note: The bit mode should be set before callbacks are set (after the card has been inserted).
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              bitModeRequestP        -- Pointer to SDIOSDBitModeRequestType struct which indicates which bit mode to set sdioSD1BitMode/sdioSD4BitMode
 *
 *  RETURNS:    errNone            -- bitModeP successfully set.
 *              sysErrParamErr  - *bitModeP unrecognizable
 *              expErrUnsupportedOperation -- This Hardware does not support the requested bit mode.
 *              expErrCardNotPresent  - Card has been removed
 *              expErrUnimplemented  -- SDIO not supported in this slot driver
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does require a SDIO card in the slot, and it can require turning on and accessing the card
 *************************************************************/
Err INLINE_FNC SDIOSetBitMode( UInt16 slotLibRefNum, SDIOSDBitModeRequestType *bitModeRequestP );
Err INLINE_FNC SDIOSetBitMode( UInt16 slotLibRefNum, SDIOSDBitModeRequestType *bitModeRequestP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioSetBitMode, bitModeRequestP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetCallback & SDIOSetCallback
 *
 *  DESCRIPTION: The Function Driver can set one callback for each function Slot and the SDMem Slot. 
 *                In general, the callbacks will call, the SDMem slot first, then functions 1 to 7. 
 *                So each function can limit itself to dealing with just its function duties.
 *                Note: Callbacks are automatically erased after a card is inserted or removed (before the card removal event)
 *                Use the notification manager to Detect card removal "sysNotifyCardRemovedEvent" event.
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              callBackP   -- Pointer to SDIOCallbackType struct which manages the callback for each function
 *                    sdioSlotNum;    //In/In; the requested function, 0=SD memory card slot driver, 1-7=SDIO functions 1-7
 *                    callbackSelect; //In/In; The callback to modify
 *                    callBackP;      //Out/In: If!=NULL, pointer to callback function, see callbackSelect for desired callback 
 *                    userDataP;      //Out/In: If!=NULL, a pointer to user data so that the user can access variables it needs
 *
 *    Callbacks (callbackSelect):
 *    "sdioCallbackSelectInterruptSDCard" calls the Function Drivers whenever the SD card signals an interrupt to the host. 
 *        The Palm device enables the SDIO interrupt whenever 1 or more "InterruptSDCard" non-zero callback is set. 
 *        It is up to the SDIO Function Driver (or really each SDIO function) to reset the interrupt source or else the interrupt 
 *        callback will be called again (up to forever!)
 *
 *    "sdioCallbackSelectSleep" and
 *    "sdioCallbackSelectAwake" calls the Function Drivers when the Palm will be put to sleep or wake up. 
 *      Note, The Sleep is always called with interrupts disabled, and it should be as fast as possible
 *      Note, The Awake is always called with interrupts disabled
 *
 *      "sdioCallbackSelectPowerOn" calls the function drivers when the SDIO card power is turned on.
 *      "sdioCallbackSelectPowerOff " calls the function drivers when the SDIO card power is turned off.
 * Note: for the power callbacks, never call  SDIOPowerSet() to turn a function on or off!
 *
 *     "sdioCallbackSelectReset" calls the function drivers when SDIOPowerSet() is called with "powerOnCard" set to "sdioCardWaitSDIO". "sdioCardWaitSDIO" is typically used after the SDIO section has been reset by a function setting RES bit in the CCCR.
 *     "sdioCallbackSelectBitMode" calls the function drivers if the bus width has been changed when a SDIOSetBitMode() is called and the bus actually changes. (Note: SDIOAPIVersion()==1 never calls this because the bus is always 1 bit wide). *Again: Interrupt routines should only call interrupt safe routines, and Set/use the userDataP to access your user variables!
 *
 *  RETURNS:    errNone            -- callBackP successfully get/set.
 *              expErrCardNotPresent -- The SDIO card has been removed
 *              expErrUnimplemented -- SDIO not supported in this slot driver
 *              sysErrParamErr - a parameter within callBackP is not allowed or wrong or missing.
 *
 *Notes:
 *    All the callbacks are classified as an interrupt. 
 *    THEY CAN OCCURE AT ANY TIME! The Interrupt can even generate a Palm Wakeup event if the Palm is asleep and power to the card is still on.  
 *    Please be careful of these, as interrupt routines can only call a few system routines and 
 *    they must execute quickly. 
 *    Any interrupt callback can call any routine in the Slot driver SlotCustomControl(). 
 *Warning:
 *    If you use any of these callbacks, you may not have control of the user interface or access to your variables. 
 *    Always Set/Use the userDataP to access your user variables! Also, remember to lock memory for
 *    your callback routines and variables.
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do require a SDIO card in the slot, since removing a card will erase these settings
 *************************************************************/
Err INLINE_FNC SDIOGetCallback( UInt16 slotLibRefNum, SDIOCallbackType *callBackP );
Err INLINE_FNC SDIOGetCallback( UInt16 slotLibRefNum, SDIOCallbackType *callBackP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetCallback, callBackP, NULL ) );
}
Err INLINE_FNC SDIOSetCallback( UInt16 slotLibRefNum, SDIOCallbackType *callBackP );
Err INLINE_FNC SDIOSetCallback( UInt16 slotLibRefNum, SDIOCallbackType *callBackP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioSetCallback, callBackP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOGetAutoRun
 *
 *  DESCRIPTION: This fills in information for a Auto Run  of a RAM based Application. 
 *                Generally this is not for the Function Driver (since it is already executing).
 *
 *  PARAMETERS: slotLibRefNum  -- SlotDriver library reference number
 *              AutoRunP      -- Pointer to AutoRunInfoType struct, which describes what to launch for this function
 *
 *  RETURNS:    errNone        -- AutoRunP successfully get.
 *              expErrCardNotPresent -- The SDIO card has been removed
 *              expErrUnimplemented  -- SDIO not supported in this slot driver
 *              expErrUnsupportedOperation - This function number does not exist
 *              sysErrParamErr - a parameter within autoRunP is not allowed or wrong or missing.
 *
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do require a SDIO card in the slot, since removing a card will erase these settings
 *************************************************************/
Err INLINE_FNC SDIOGetAutoRun( UInt16 slotLibRefNum, SDIOAutoRunInfoType *AutoRunP );
Err INLINE_FNC SDIOGetAutoRun( UInt16 slotLibRefNum, SDIOAutoRunInfoType *AutoRunP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioGetAutoRun, AutoRunP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIORWDirect, SDIORWExtendedByte, & SDIORWExtendedBlock
 *
 *  DESCRIPTION: These are the 3 ways to read or write to an SDIO card. The SDIORWExtendedBlock is 
 *                optional (depending upon the card, as per the SDIO specification). 
 *                This SDIO Slot driver does not support the "forever" mode of SDIORWExtendedBlock. 
 *                See the SDIO specification for the SDIO registers that can be read or written.
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *              directP,extendedByteP,extendedBlockP   -- Pointer to struct which describes how to 
 *                                                            read and write for this function
 *
 *  RETURNS:    errNone            -- transaction successful.
 *              expErrCardNotPresent -- The SDIO card has been removed
 *              expErrCardBadSector  -- The SDIO memory could not be read or written.
 *              expErrUnsupportedOperation - Extended block operations or function does not exist
 *              expErrUnimplemented -- SDIO not supported in this slot driver
 *              sysErrParamErr - a parameter is not allowed or wrong or missing.
 *
 *Note; The write protect tab on the SD card is ignored, these writes will always issue the write command to the card.
 *
 * Note: These routines are safe for interrupts.
 * Note: These routines do require a SDIO card in the slot, and the card will be turned on and accessed
 *************************************************************/
Err INLINE_FNC SDIORWDirect( UInt16 slotLibRefNum, SDIORWDirectType *directP );
Err INLINE_FNC SDIORWDirect( UInt16 slotLibRefNum, SDIORWDirectType *directP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioRWDirect, directP, NULL ) );
}
Err INLINE_FNC SDIORWExtendedByte( UInt16 slotLibRefNum, SDIORWExtendedByteType *extendedByteP );
Err INLINE_FNC SDIORWExtendedByte( UInt16 slotLibRefNum, SDIORWExtendedByteType *extendedByteP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioRWExtendedByte, extendedByteP, NULL ) );
}
Err INLINE_FNC SDIORWExtendedBlock( UInt16 slotLibRefNum, SDIORWExtendedBlockType *extendedBlockP );
Err INLINE_FNC SDIORWExtendedBlock( UInt16 slotLibRefNum, SDIORWExtendedBlockType *extendedBlockP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioRWExtendedBlock, extendedBlockP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIOTupleWalk
 *
 *  DESCRIPTION: This will "walk" a tuple list of a particular function  
 *                               until a tuple is found and return the contents of the tuple
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *               tupleP   -- Pointer to struct which describes how to 
 *                                                            read and write for this function
 *
 *  RETURNS:    errNone            -- tupleP successfully found.
 *              expErrCardNotPresent -- The SDIO card has been removed
 *              expErrUnsupportedOperation - This function number does not exist
 *              expErrCardBadSector  - The SDIO function memory could not be read or  tuple not found
 *              expErrUnimplemented - SDIO not supported in this slot driver
 *              sysErrParamErr - a parameter within tupleP is not allowed or wrong or missing.
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does require a SDIO card in the slot, and the card will be powered and accessed
 *************************************************************/
Err INLINE_FNC SDIOTupleWalk( UInt16 slotLibRefNum, SDIOTupleType *tupleP );
Err INLINE_FNC SDIOTupleWalk( UInt16 slotLibRefNum, SDIOTupleType *tupleP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioTupleWalk, tupleP, NULL ) );
}
/************************************************************
 *
 *  FUNCTION:    SDIOAccessDelay
 *
 *  DESCRIPTION: The default access delay for any SDIO card is 1 second
 *		If a card needs a slower (worst case) delay use this.
 *      Note: basic commands like read CCRCR, FBR's, and tuples MUST 
 *          be readable within 1 second!
 *      If a file system is available, 
 *          it will be mountes (accesssed) with this 1 second limitation too!
 *      Drivers only have access to this after their driver is started!
 *
 *  PARAMETERS: slotLibRefNum    -- SlotDriver library reference number
 *               delayMSP   -- Pointer to delay in Milliseconds, mimimum is 1,000 (1 second)
 *
 *  RETURNS:    errNone            -- delayMSP successfully set.
 *              expErrCardNotPresent -- The SDIO card has been removed, delay not set
 *              expErrUnimplemented - SDIO not supported in this slot driver
 *              sysErrParamErr - a parameter within delayMSP is not allowed or wrong or missing.
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does require a SDIO card in the slot
 *************************************************************/
Err INLINE_FNC SDIOAccessDelay( UInt16 slotLibRefNum, SDIOAccessDelayType *delayMSP );
Err INLINE_FNC SDIOAccessDelay( UInt16 slotLibRefNum, SDIOAccessDelayType *delayMSP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioAccessDelay, delayMSP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIODebugOptions
 *
 *  DESCRIPTION: FOR DEBUG ROMS and DEBUG RAM patches only!
 *			This call activates or deactivates printing debugging messages 
 *			to the serial port (or USB port). If you activate this be sure to be
 *			in a cradle and a debugger is running to get the messages. Code warrior
 *			works too, but it adds unwanted extra <CR><LF>'s in the messages.
 *			to deactivate this, press the reset button (soft reset) or just call 
 *                                                   SDIODebugOptions() with *debugOptionsP=0;
 *   Note: the serial port does slow down the response of the card. This is not a real time trace.
 *             Use a logic analyzer for real time tracing.
 *
 *  PARAMETERS: slotLibRefNum   -- SlotDriver library reference number
 *              debugOptionsP   -- Pointer to SDIODebugOptionType of bits that define what to print
 *
 *  RETURNS:    errNone            -- debugOptionsP successfully set.
 *              expErrUnsupportedOperation - This is NOT a debug ROM or debug RAM patch, no debug features available
 *              expErrUnimplemented - SDIO not supported in this slot driver
 *
 * Note: This routine is safe for interrupts.
 * Warning: If this option is activated, and the device is NOT in a cradle, all debug messages will be routed
 *         to the USB cradle (until a soft reset is generated) by default. However, since you are not connected
 *         to a USB cradle, the software will "lock" forever trying to open a non-existent USB port. 
 *         To recover from this, either press reset or, first start a USB debugger on your PC/MAC 
 *         then connect the Handheld to the cradle. 
 *************************************************************/
Err INLINE_FNC SDIODebugOptions( UInt16 slotLibRefNum, SDIODebugOptionType *debugOptionsP );
Err INLINE_FNC SDIODebugOptions( UInt16 slotLibRefNum, SDIODebugOptionType *debugOptionsP )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioDebugOptions, debugOptionsP, NULL ) );
}

/************************************************************
 *
 *  FUNCTION:    SDIODisableHandheldInterrupt, and SDIOEnableHandheldInterrupt
 *
 *  DESCRIPTION:
 *			These calls disables or enables the interrupt on the handheld side
 *			(This does not turn off any interrupt on the card). The disable interrupt 
 *			is implemented as an incrementing counter (like locking memory), thus 
 *			making it re-entrant. However, for every call of SDIODisableHandheldInterrupt()
 *			there must be an equal number (or more) of SDIOEnableHandheldInterrupt() to 
 *			actually re-enable interrupts. By default, when the card is inserted, 
 *			this interrupt is enabled by this routine, but disabled internally until 
 *			an interrupt callback is set.
 *
 *  PARAMETERS: slotLibRefNum   -- SlotDriver library reference number
 *
 *  RETURNS:    errNone            -- debugOptionsP successfully set.
 *              expErrCardNotPresent -- The SDIO card has been removed, 
 *              expErrUnsupportedOperation - For SDIODisableHandheldInterrupt() = >65,535 disables
 *              expErrUnsupportedOperation - For SDIOEnableHandheldInterrupt() = interrupts alread enabled
 *              expErrUnimplemented - SDIO not supported in this slot driver
 *
 * Note: This routine is safe for interrupts.
 * Note: This routine does require a SDIO card in the slot
 *************************************************************/
Err INLINE_FNC SDIODisableHandheldInterrupt( UInt16 slotLibRefNum );
Err INLINE_FNC SDIODisableHandheldInterrupt( UInt16 slotLibRefNum )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioDisableMasterInterrupt, NULL, NULL ) );
}
Err INLINE_FNC SDIOEnableHandheldInterrupt( UInt16 slotLibRefNum );
Err INLINE_FNC SDIOEnableHandheldInterrupt( UInt16 slotLibRefNum )
{ 
    return( SlotCustomControl( slotLibRefNum, sysFileApiCreatorSDIO, sdioEnableMasterInterrupt, NULL, NULL ) );
}

#endif //__SDIO_h_
