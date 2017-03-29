/******************************************************************************
 *
 * Copyright (c) 2003-2004 Tapwave Inc. All rights reserved.
 *
 * File: JPGLib.h
 *
 * Release: 
 *
 * Description:
 *              Public API of a simple library used by 68K applications
 *
 * History:
 *      June 17, 2003   Created by Liu, Akewart
 *      July 29, 2003   Added V20 APIs by Hong Zhang
 *
 *****************************************************************************/

#ifndef __JPGLIB_H__
#define __JPGLIB_H__

#include <PalmTypes.h>

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

#define kJPGLibType     sysFileTLibrary
#define kJPGLibCreator  'twJ6'
#define kJPGLibName     "IJG JPEG Library"

/********************************************************************
 * Traps
 ********************************************************************/

#define sysLibTrapGetPhotoInfo      sysLibTrapCustom + 1
#define sysLibTrapDecodePhoto       sysLibTrapCustom + 2

#define sysLibTrapGetPhotoInfoV20   sysLibTrapCustom + 3
#define sysLibTrapDecodePhotoV20    sysLibTrapCustom + 4

#define SimpleLibAPIVersion         (sysMakeROMVersion(5, 0, 0, sysROMStageRelease, 0))

/********************************************************************
 * Prototypes
 ********************************************************************/

typedef struct
{
    Int32   ScaleX;                 //[Input Para] width of preview area
    Int32   ScaleY;                 //[Input Para] height of preview area
    Int32   PosiX;                  //[Input Para] actural position X of image 
    Int32   PosiY;                  //[Input Para] actural position Y of image
    Int32   ImageWidth;             //[Output Para]
    Int32   ImageHeight;            //[Output Para]
    Int32   Preview_mode;           //[Input Para] 0 - fullscale mode ( default )
                                    // 1 - preview mode 
                                    
    Int32   Grayscale_output;       // 0 - color ( default )[Input]
                                    // 1 - grayscale
                              
    Int32   Fit_mode;               //[Input Para]
                                    //0---Fit Actual size
                                    //1---Fit Height
                                    //2---Fit Width
                                    
    Int32   rotate;                 //[Input Para]
                                    //0---not rotate
                                    //1---rotate right
                                    //2---rotate left
                                    //3---rotate twice left/right
                                    
    UInt16  *outBMP;                // Buffer for holding the RGB data
    
    Int32   ActualImageWidth;       //[Output Para]
    Int32   ActualImageHeight;      //[Output Para]
    
} JPEGDEC_CTL ;

#if CPU_TYPE == CPU_68K
    #define LIBREF UInt16 libRef,
#else
    #define LIBREF
#endif

/*
 * These functions decode a JPEG image using standard PalmOS VFS manager.
 */
Err JPGLibGetPhotoInfoV10(LIBREF UInt16 volRefNum, const Char *path, JPEGDEC_CTL *pCtrl)
    SYS_TRAP(sysLibTrapGetPhotoInfo);

Err JPGLibDecodePhotoV10(LIBREF UInt16 volRefNum, const Char *path, JPEGDEC_CTL *pCtrl)
    SYS_TRAP(sysLibTrapDecodePhoto);

/*
 * These functions decode a JPEG image using callback mechanism. The
 * callback function carries UNIX read(2) syntax. If the callcack
 * function is not provided, it is assumed to be VFSFileRead, and
 * the handle is FileRef. NOTE: refnum is not used on ARM side.
 */
Err JPGLibGetPhotoInfoV20(LIBREF Int32 (*reader)(void* handle, void* buf, Int32 len), void* handle, JPEGDEC_CTL *pCtrl)
    SYS_TRAP(sysLibTrapGetPhotoInfoV20);

Err JPGLibDecodePhotoV20(LIBREF Int32 (*reader)(void* handle, void* buf, Int32 len), void* handle, JPEGDEC_CTL *pCtrl)
    SYS_TRAP(sysLibTrapDecodePhotoV20);

#ifdef __cplusplus 
}
#endif

#endif // __JPGLIB_H__

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
