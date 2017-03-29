/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWRUNTIME_H__
#define __TWRUNTIME_H__

#include <PalmOS.h>
#include <PceNativeCall.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TwModuleInfo
{
    /* public fields */
    MemHandle dbH;
    UInt32    moduleID;
    UInt32    dbType;
    UInt32    dbCreator;
    UInt32    rsrcType;
    UInt32    rsrcID;
    UInt32    flags;
    MemHandle rsrcH;
    MemPtr    rsrcP;
    MemPtr    codeAddr;
    UInt32    codeSize;
    MemPtr    dataAddr;
    UInt32    dataSize;
    UInt32    refCount;
    NativeFuncType*     entrypoint;
    /* private fields */
    struct TwModuleInfo* next;
    struct TwModuleInfo* prev;
} TwModuleInfo;

/*
 * Load Tapwave Native Application. On device, the runtime loads the
 * resource into dynamic heap and applies standard initializations.
 */
#define twLoadFlagTNA           1

/*
 * Load PACE Native Object, Run it, Unload it in one call.
 */
#define twLoadFlagQuickRun      2

/*
 * Query module information about the given virtual address.
 *
 *  Parameters:
 * 
 *      addr    the virtual address (code or data) to query
 *
 *      info    struct TwModuleInfo that holds return info
 *
 *      size    must be sizeof(struct TwModuleInfo)
 *
 *  Returns:
 *      errNone
 *      sysErrLibNotFound
 *
 *  Comments:
 *      This function is designed for debugging, profiling, and DRM.
 *      It is illegal to use it for runtime call, such as find a
 *      module and call its entrypoint. Applications should always use
 *      TwLoadModule() for runtime call. This behavior is different
 *      from PalmOS SysLibFind().
 */
Err TwFindModule(void* addr, TwModuleInfo* info, UInt32 size)
    TAL_TRAP(trapTwFindModule);

/*
 * Load PACE Native Object.
 *
 *  Parameters:
 * 
 *      dbType      PNO database type
 *
 *      dbCreator   PNO database creator
 *
 *      rsrcType    PNO resource type
 *
 *      rsrcID      PNO resource id, must <= 0xFFFF
 *
 *      flags       various flags that controls the loading, see above
 *
 *      entry       [OUT] returns the PNO entrypoint, which can be
 *                  used in subsequent PceNativeCall() calls.
 *
 *  Returns:
 *      errNone
 *      sysErrLibNotFound
 *
 *  Comments:
 *      If both dbType and dbCreator are zero, this function will load
 *      resource through SysCurAppDatabase().
 *
 *      If rsrcType is zero, it is assumes to be 'ARMC' on ARM
 *      devices, and 'SIMC' on Palm OS Simulator. If 'ARMC' code
 *      resource is missing, the runtime will try to load 'ARMZ' code
 *      resource, which is assumed to be the gzipped version of 'ARMC'
 *      resource. The gzipped version can save about 50% of space.
 *
 *      The runtime uses reference counting to manage loaded library.
 *      Multiple load of the same library will end up with the same
 *      entrypoint. Global state of a library is kept between multiple
 *      PceNativeCall() calls. NOTE: PceNativeCall() itself does not
 *      maintain global state on PalmSim, because it loads and unloads
 *      for each call.
 */
Err TwLoadModule(UInt32 dbType, UInt32 dbCreator, UInt32 rsrcType, UInt32 rsrcID, UInt32 flags, NativeFuncType** entry)
    TAL_TRAP(trapTwLoadModule);

/*
 * Unload PACE Native Object.
 *
 *  Parameters:
 *
 *      entry   PNO entrypoint returned by TwLoadModule(), see above.
 *
 *  Returns:
 *      errNone
 *      memErrNotEnoughSpace
 *      sysErrLibNotFound
 *      sysErrParamErr
 */
Err TwUnloadModule(NativeFuncType* entry)
    TAL_TRAP(trapTwUnloadModule);

#ifdef __cplusplus
}
#endif

#endif /* __TWRUNTIME_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
