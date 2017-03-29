/*
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * PhotoList.h
 *
 * public header for shared library
 *
 * This wizard-generated code is based on code adapted from the
 * SampleLib project distributed as part of the Palm OS SDK 4.0.
 */

#ifndef PHOTOLIST_H_
#define PHOTOLIST_H_

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
#ifdef BUILDING_PHOTOLIST
    #define PHOTOLIST_LIB_TRAP(trapNum)
#else
    #define PHOTOLIST_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif

/*********************************************************************
 * Type and creator of Sample Library database
 *********************************************************************/

#define     PhotoListCreatorID  'twPL'
#define     PhotoListTypeID     sysFileTLibrary

/*********************************************************************
 * Internal library name which can be passed to SysLibFind()
 *********************************************************************/

#define     PhotoListName       "PhotoListMgr"

/*********************************************************************
 * PhotoListMgr result codes
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *********************************************************************/

/* invalid parameter */
#define PhotoListErrParam           (appErrorClass | 1)     

/* library is not open */
#define PhotoListErrNotOpen         (appErrorClass | 2)     

/* returned from PhotoListClose() if the library is still open */
#define PhotoListErrStillOpen       (appErrorClass | 3)     

// custom Errors
#define PhotoListErrInvalidPath     (appErrorClass | 4)
#define PhotoListErrIndexOutOfRange (appErrorClass | 5)
#define PhotoListErrItemNotExsit    (appErrorClass | 6)
#define PhotoListErrUnknown         (appErrorClass | 7)
#define PhotoListErrReadOnly        (appErrorClass | 8)
#define PhotoListErrEmpty           (appErrorClass | 9)
#define PhotoListErrEmptyEntry      (appErrorClass | 10)


typedef struct PhotoListType PhotoListType; // private


// "sort" definitions, used in PhotoListOpen()
typedef enum {
    sortAlphabetical = 0x1,
    sortUserdefined, 
    sortShuffled
} SortFlags;


// "filter" definitions, used in PhotoListOpen()
#define searchMemory    0x0001
#define searchCard1     0x0002
#define searchCard2     0x0004
#define searchCards     (searchCard1|searchCard2)
#define searchAll       (searchMemory|searchCards)
#define searchRemoved   0x0010

// Rotations
#define photoRotation0      0x00
#define photoRotation90     0x01
#define photoRotation180    0x03
#define photoRotation270    0x02

/*********************************************************************
 * API Prototypes
 *********************************************************************/

/* Standard library open, close, sleep and wake functions */
extern Err PhotoListLibOpen(UInt16 refNum, UInt32 * clientContextP)
    PHOTOLIST_LIB_TRAP(sysLibTrapOpen);
                
extern Err PhotoListLibClose(UInt16 refNum, UInt32 clientContext)
    PHOTOLIST_LIB_TRAP(sysLibTrapClose);

extern Err PhotoListLibSleep(UInt16 refNum)
    PHOTOLIST_LIB_TRAP(sysLibTrapSleep);

extern Err PhotoListLibWake(UInt16 refNum)
    PHOTOLIST_LIB_TRAP(sysLibTrapWake);


/* Custom library API functions */
extern PhotoListType*  PhotoListOpen(UInt16 refNum, UInt16 filter, SortFlags sort, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 5);

extern UInt16 PhotoListCountImages(UInt16 refNum, PhotoListType* photoListP, UInt16 filter, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 6);

extern void PhotoListClose(UInt16 refNum, PhotoListType* photoListP, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 7);

extern void PhotoListUpdate(UInt16 refNum, PhotoListType* photoListP, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 8);

extern void PhotoListShuffle(UInt16 refNum, PhotoListType* photoListP, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 9);

extern void PhotoListMoveImage(UInt16 refNum, PhotoListType* photoListP,UInt16 fromIndex,UInt16 toIndex, Boolean realmove, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 10);// different from the doc.
    
extern void PhotoListDeleteImage(UInt16 refNum, PhotoListType* photoListP,UInt16 index, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 11);

extern Boolean PhotoListFindInImage(UInt16 refNum, PhotoListType* photoListP,UInt16 index,const Char *searchString, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 12);

extern Int8 PhotoListGetImageSlot(UInt16 refNum, PhotoListType* photoListP,UInt16 index,Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 13);

extern Char * PhotoListGetImagePath(UInt16 refNum, PhotoListType* photoListP,UInt16 index, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 14);

extern Char * PhotoListGetImageName(UInt16 refNum, PhotoListType* photoListP,UInt16 index,Boolean flat, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 15);

extern Boolean PhotoListGetImageSlideshow(UInt16 refNum, PhotoListType* photoListP,UInt16 index,Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 16);

extern void PhotoListSetImageSlideshow(UInt16 refNum, PhotoListType* photoListP,UInt16 index,Boolean include, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 17);

extern void PhotoListGetImageDimensions(UInt16 refNum, PhotoListType* photoListP,UInt16 index, Coord *withP, Coord *heightP, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 18);
    
extern Int32 PhotoListGetFileSize(UInt16 refNum, PhotoListType * photoListP,UInt16 index,Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 19) ;

extern UInt32 PhotoListGetDateTime(UInt16 refNum, PhotoListType * photoListP,UInt16 index,Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 20) ;
    
extern UInt16 PhotoListGetPreferredImageRotation(UInt16 refNum, PhotoListType* photoListP,UInt16 index,Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 21);
    
extern void PhotoListSetPreferredImageRotation(UInt16 refNum, PhotoListType* photoListP,UInt16 index, UInt16 include, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 22);

extern void PhotoListGetPreferredImageDimensions(UInt16 refNum, PhotoListType * photoListP,UInt16 index,UInt16 *width, UInt16 *height, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 23) ;
    
extern void PhotoListSetPreferredImageDimensions(UInt16 refNum, PhotoListType * photoListP,UInt16 index,UInt16 width, UInt16 height, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 24) ;
    
extern void PhotoListSetCurrentImage(UInt16 refnum, PhotoListType *photoListP, UInt16 index, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 25) ;
    
extern UInt16 PhotoListGetCurrentImage(UInt16 refnum, PhotoListType *photoListP, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 26) ;
    
extern UInt16 PhotoListUpdateThumbData(UInt16 refnum, PhotoListType *photoListP, UInt16 index, UInt32 size, void *data, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 27) ;
    
extern UInt16 PhotoListGetThumbStatus(UInt16 refnum, PhotoListType *photoListP, UInt16 index, UInt16 *width, UInt16 *height, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 28) ;
    
extern UInt16 PhotoListGetThumbData(UInt16 refnum, PhotoListType *photoListP, UInt16 index, void *data, UInt32 bufsize, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 29) ;   
    
extern void PhotoListSetThumbStatus(UInt16 refnum, PhotoListType *photoListP, UInt16 index, UInt16 width, UInt16 height, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 30) ;

extern void PhotoListClearThumbData(UInt16 refnum, Err *errP)
    PHOTOLIST_LIB_TRAP(sysLibTrapBase + 31) ;

#ifdef __cplusplus
}
#endif

/*
 * FUNCTION: PhotoList_OpenLibrary
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
 
__inline Err PhotoList_OpenLibrary(UInt16 *refNumP, UInt32 * clientContextP)
{
    Err error;
    Boolean loaded = false;
    
    /* first try to find the library */
    error = SysLibFind(PhotoListName, refNumP);
    
    /* If not found, load the library instead */
    if (error == sysErrLibNotFound)
    {
        error = SysLibLoad(PhotoListTypeID, PhotoListCreatorID, refNumP);
        loaded = true;
    }
    
    if (error == errNone)
    {
        error = PhotoListLibOpen(*refNumP, clientContextP);
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
 * FUNCTION: PhotoList_CloseLibrary
 *
 * DESCRIPTION: 
 *
 * User-level call to closes the shared library.  This handles removal
 * of the library from system if there are no users remaining.
 *
 * PARAMETERS:
 *
 * refNum
 *      Library reference number obtained from PhotoList_OpenLibrary().
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

__inline Err PhotoList_CloseLibrary(UInt16 refNum, UInt32 clientContext)
{
    Err error;
    
    if (refNum == sysInvalidRefNum)
    {
        return sysErrParamErr;
    }

    error = PhotoListLibClose(refNum, clientContext);

    if (error == errNone)
    {
        /* no users left, so unload library */
        SysLibRemove(refNum);
    } 
    else if (error == PhotoListErrStillOpen)
    {
        /* don't unload library, but mask "still open" from caller  */
        error = errNone;
    }
    
    return error;
}

#endif /* PHOTOLIST_H_ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
