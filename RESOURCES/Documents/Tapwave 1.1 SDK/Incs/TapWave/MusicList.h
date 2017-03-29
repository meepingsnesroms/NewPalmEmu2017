/*
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * MusicList.h
 *
 * public header for shared library
 *
 * This wizard-generated code is based on code adapted from the
 * SampleLib project distributed as part of the Palm OS SDK 4.0.
 */

#ifndef __MUSICLIST_H__
#define __MUSICLIST_H__

/* Palm OS common definitions */
#include <SystemMgr.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYS_TRAP
#define SYS_TRAP(num)
#endif

/* If we're actually compiling the library code, then we need to
 * eliminate the trap glue that would otherwise be generated from
 * this header file in order to prevent compiler errors in CW Pro 2. */
#ifdef BUILDING_MUSICLIST
    #define MUSICLIST_LIB_TRAP(trapNum)
#else
    #define MUSICLIST_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif

/*********************************************************************
 * Type and creator of Sample Library database
 *********************************************************************/

#define     MusicListCreatorID  'twML'
#define     MusicListTypeID     sysFileTLibrary

/*********************************************************************
 * Internal library name which can be passed to SysLibFind()
 *********************************************************************/

#define     MusicListName       "MusicListMgr"

/*********************************************************************
 * MusicListMgr result codes
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *********************************************************************/

/* invalid parameter */
#define MusicListErrParam       (appErrorClass | 1)     

/* library is not open */
#define MusicListErrNotOpen     (appErrorClass | 2)     

/* returned from MusicListClose() if the library is still open */
#define MusicListErrStillOpen   (appErrorClass | 3)     

// custom Errors
#define MusicListErrInvalidPath     (appErrorClass | 4)
#define MusicListErrIndexOutOfRange (appErrorClass | 5)
#define MusicListErrItemNotExsit    (appErrorClass | 6)
#define MusicListErrUnknown         (appErrorClass | 7)
#define MusicListErrReadOnly        (appErrorClass | 8)
#define MusicListErrEmptyEntry      (appErrorClass | 9)
#define MusicListErrInvalidParam    (appErrorClass | 10)


typedef struct MusicListType MusicListType; // private


// "sort" definitions, used in MusicListOpen()
typedef enum {
    sortAlphabetical = 0x1,
    sortUserdefined, 
    sortShuffled
} SortFlags;


// "filter" definitions, used in MusicListOpen()
#define searchMemory    0x0001
#define searchCard1     0x0002
#define searchCard2     0x0004
#define searchCards     (searchCard1|searchCard2)
#define searchAll       (searchMemory|searchCards)
#define searchRemoved   0x0010
#define searchExisted	0x0100


/*********************************************************************
 * API Prototypes
 *********************************************************************/


/* Standard library open, close, sleep and wake functions */
extern Err MusicListLibOpen(UInt16 refNum, UInt32 * clientContextP)
    MUSICLIST_LIB_TRAP(sysLibTrapOpen);
                
extern Err MusicListLibClose(UInt16 refNum, UInt32 clientContext)
    MUSICLIST_LIB_TRAP(sysLibTrapClose);

extern Err MusicListLibSleep(UInt16 refNum)
    MUSICLIST_LIB_TRAP(sysLibTrapSleep);

extern Err MusicListLibWake(UInt16 refNum)
    MUSICLIST_LIB_TRAP(sysLibTrapWake);


/* Custom library API functions */
extern MusicListType*  MusicListOpen(UInt16 refNum, UInt16 filter, SortFlags sort, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 5);

extern UInt16 MusicListCountSongs(UInt16 refNum, MusicListType* musicListP, UInt16 filter, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 6);

extern void MusicListClose(UInt16 refNum, MusicListType* musicListP, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 7);

extern void MusicListUpdate(UInt16 refNum, MusicListType* musicListP, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 8);

extern void MusicListShuffle(UInt16 refNum, MusicListType* musicListP, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 9);

extern void MusicListMoveSong(UInt16 refNum, MusicListType* musicListP, UInt16 fromIndex, UInt16 toIndex, Boolean realmove, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 10);// this one is different from the doc..

extern Boolean MusicListFindInSong(UInt16 refNum, MusicListType* musicListP, UInt16 index, const Char *searchString, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 11);

extern Int8 MusicListGetSongSlot(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 12);

extern Char * MusicListGetSongPath(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 13);

extern Char * MusicListGetSongAlbum(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 14);

extern Char * MusicListGetSongArtist(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 15);

extern Char * MusicListGetSongTitle(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 16);

extern Int32 MusicListGetSongDuration(UInt16 refNum, MusicListType* musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 17);
    
extern  Int32 MusicListGetFileSize(UInt16 refNum, MusicListType * musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase + 18) ;

extern void MusicListSetCurrentSong(UInt16 refnum, MusicListType *musicListP, UInt16 index, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase+19) ;
    
extern  UInt16 MusicListGetCurrentSong(UInt16 refnum, MusicListType *musicListP, Err *errP)
    MUSICLIST_LIB_TRAP(sysLibTrapBase +20) ;

extern	Err MusicListCustomControl( UInt16 refnum , UInt16 cmd , void *argP , UInt32 *argLenP )
	MUSICLIST_LIB_TRAP(sysLibTrapBase + 21 ) ;

#ifdef __cplusplus
}
#endif

/*
 * FUNCTION: MusicList_OpenLibrary
 *
 * DESCRIPTION:
 *
 * User-level call to open the library.  This inline function
 * handles the messy task of finding or loading the library
 * and calling its open function, including handling cleanup
 * if the library could not be opened.
 * 
 * PARAMETERS:
 *
 * refNumP
 *      Pointer to UInt16 variable that will hold the new
 *      library reference number for use in later calls
 *
 * clientContextP
 *      pointer to variable for returning client context.  The client context is
 *      used to maintain client-specific data for multiple client support.  The 
 *      value returned here will be used as a parameter for other library 
 *      functions which require a client context.  
 *
 * CALLED BY: System
 *
 * RETURNS:
 *      errNone
 *      memErrNotEnoughSpace
 *      sysErrLibNotFound
 *      sysErrNoFreeRAM
 *      sysErrNoFreeLibSlots
 *
 * SIDE EFFECTS:
 *      *clientContextP will be set to client context on success, or zero on
 *      error.
 */
 
__inline Err MusicList_OpenLibrary(UInt16 *refNumP, UInt32 * clientContextP)
{
    Err error;
    Boolean loaded = false;
    
    /* first try to find the library */
    error = SysLibFind(MusicListName, refNumP);
    
    /* If not found, load the library instead */
    if (error == sysErrLibNotFound)
    {
        error = SysLibLoad(MusicListTypeID, MusicListCreatorID, refNumP);
        loaded = true;
    }
    
    if (error == errNone)
    {
        error = MusicListLibOpen(*refNumP, clientContextP);
        if (error != errNone)
        {
            if (loaded)
            {
                SysLibRemove(*refNumP);
            }

            *refNumP = sysInvalidRefNum;
        }
    }
    
    return error;
}

/*
 * FUNCTION: MusicList_CloseLibrary
 *
 * DESCRIPTION: 
 *
 * User-level call to closes the shared library.  This handles removal
 * of the library from system if there are no users remaining.
 *
 * PARAMETERS:
 *
 * refNum
 *      Library reference number obtained from MusicList_OpenLibrary().
 *
 * clientContext
 *      client context (as returned by the open call)
 *
 * CALLED BY: Whoever wants to close the library
 *
 * RETURNS:
 *      errNone
 *      sysErrParamErr
 */

__inline Err MusicList_CloseLibrary(UInt16 refNum, UInt32 clientContext)
{
    Err error;
    
    if (refNum == sysInvalidRefNum)
    {
        return sysErrParamErr;
    }

    error = MusicListLibClose(refNum, clientContext);

    if (error == errNone)
    {
        /* no users left, so unload library */
        SysLibRemove(refNum);
    } 
    else if (error == MusicListErrStillOpen)
    {
        /* don't unload library, but mask "still open" from caller  */
        error = errNone;
    }
    
    return error;
}

#endif /* __MUSICLIST_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
