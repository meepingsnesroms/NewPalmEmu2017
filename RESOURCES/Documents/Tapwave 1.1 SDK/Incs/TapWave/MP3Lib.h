/******************************************************************************
 *
 * Copyright (c) 2003-2004 Tapwave Inc. All rights reserved.
 *
 * File: MP3Lib.h
 *
 * Release: 
 *
 * Description:
 *              Public API of MP3 Library used by 68K applications
 *
 * History:
 *      Jun 17, 2003    Created by Liu, Akewart
 *
 *****************************************************************************/

#ifndef _MP3LIB_H_
#define _MP3LIB_H_

#include <PalmTypes.h>
#include <DataMgr.h>
#include <VFSMgr.h>

#if CPU_TYPE != CPU_68K
#include <LibTraps68K.h>
#else
#include <LibTraps.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYS_TRAP
#define SYS_TRAP(num)
#endif

/********************************************************************
 * Constants
 ********************************************************************/

#define kMP3LibType     sysFileTLibrary
#define kMP3LibCreator  'twM3'
#define kMP3LibName     "MP3Lib"

/********************************************************************
 * Error codes
 ********************************************************************/

#define mp3LibErrClass              0x9900

#define mp3LibErrNotEnoughMemory    (mp3LibErrClass|1)
#define mp3LibErrInvalidMP3Format   (mp3LibErrClass|2)
#define mp3LibErrDecodeError        (mp3LibErrClass|3)
#define mp3LibErrInvalidParam       (mp3LibErrClass|4)
#define mp3LibErrPlayingInterrupted (mp3LibErrClass|5)

/********************************************************************
 * Traps
 ********************************************************************/
 
#define trapMP3LibPlayFile          (sysLibTrapCustom + 1)
#define trapMP3LibPlayDb            (sysLibTrapCustom + 2)
#define trapMP3LibPause             (sysLibTrapCustom + 3)
#define trapMP3LibIsPaused          (sysLibTrapCustom + 4)
#define trapMP3LibSeekSeconds       (sysLibTrapCustom + 5)
#define trapMP3LibGetVolume         (sysLibTrapCustom + 6)
#define trapMP3LibSetVolume         (sysLibTrapCustom + 7)
#define trapMP3LibStop              (sysLibTrapCustom + 8)
#define trapMP3LibGetTrackLength    (sysLibTrapCustom + 9)
#define trapMP3LibCustomControl     (sysLibTrapCustom + 10)

/********************************************************************
 * Notification types
 ********************************************************************/

#define sysNotifyMP3Stopped 'MP3s'

#define mp3ReasonFinishedPlaying    0x0
#define mp3ReasonHaltByError        0x1

typedef struct {
    Int32   reason ;    //  reason tells why this notification is broadcasted ..
    Int32   errcode ;   //  errcode if reason is mp3ReasonHaltByError ...may convert this into an Err type
} MP3NotifyType ;

/********************************************************************
 * Prototypes
 ********************************************************************/

Err MP3LibPlayFile(UInt16 refnum, UInt16 volRefNum, const Char *path, Boolean paused, UInt16 duration)
    SYS_TRAP(trapMP3LibPlayFile);
    
Err MP3LibPlayDb(UInt16 refnum, DmOpenRef fileR, UInt16 *samplerate, Int16 *channels, Int16 *bitrate, Int16 *time)
    SYS_TRAP(trapMP3LibPlayDb);
    
Err MP3LibPause(UInt16 refnum, Boolean paused)
    SYS_TRAP(trapMP3LibPause);
    
Boolean MP3LibIsPaused(UInt16 refnum, Int32 *where, Int32 *trackLength)
    SYS_TRAP(trapMP3LibIsPaused);
    
Err MP3LibSeekSeconds(UInt16 refnum, Boolean fromStart, Int32 offsetSeconds)
    SYS_TRAP(trapMP3LibSeekSeconds) ;
    
Err MP3LibGetVolume(UInt16 refnum, Int32 *volumeP)
    SYS_TRAP(trapMP3LibGetVolume) ;
    
Err MP3LibSetVolume(UInt16 refnum, Int32 volume)
    SYS_TRAP(trapMP3LibSetVolume) ;
    
Err MP3LibStop(UInt16 refnum )
    SYS_TRAP(trapMP3LibStop) ;

Err MP3LibGetTrackLength(UInt16 refnum, FileRef filer)
    SYS_TRAP(trapMP3LibGetTrackLength) ;
    
Err MP3LibCustomControl(UInt16 refnum, UInt16 cmd, void *paramP, UInt16 *paramLenP)
    SYS_TRAP(trapMP3LibCustomControl) ;
    
#ifdef __cplusplus 
}
#endif

#endif // _MP3LIB_H_

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
