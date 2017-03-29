/*
    File:       Startup.cpp  

    Summary:    Tapwave Native Application entrypoint. It also defines
                hooks for relocation support, floating point, and
                global constructors.

    Author:     Hong Zhang

    Copyright:  Copyright © 2003 by Tapwave, Inc.

    Disclaimer: IMPORTANT: This Tapwave software is provided by
                Tapwave, Inc. ("Tapwave").  Your use is subject to and
                governed by terms and conditions of the Software
                Development Kit Agreement ("SDK Agreement") between
                you and Tapwave.  If you have not entered into
                Tapwave’s standard SDK Agreement with Tapwave, you
                have no right or license to use, reproduce, modify,
                distribute or otherwise exploit this Tapwave software.
                You may obtain a copy of Tapwave’s standard SDK
                Agreement by calling 650-960-1817 or visiting Tapwave
                at http://www.tapwave.com/developers/.

    Change History (most recent first):
        030702  Update comment regarding Tapwave Native Application.
        030805  Update to provide basic time support for MSL.
        031107  Update to support open/close/read/write/lseek/mkdir
*/

#include <TapWave.h>

#ifndef __PALMOS_ARMLET__
#error "__PALMOS_ARMLET__ is not defined!!!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This variable holds the Tapwave Native Application interface
 * dispatch table. General ARM API calls will go through this table.
 */
struct TwGlue*   twGlue;
const void*      twEmulState;
Call68KFuncType* twCall68KFunc;

#ifdef __MWERKS__

#if __PALMOS_ARMLET__ < 0x120
#error "You must use CodeWarrior for Palm OS 9.3 or later!!!"
#endif

#include <string.h>
#include <ctype.h>
#include <float.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <file_struc.h>
#include <console_io.h>
#include <dirent.h>

using namespace std;

UInt32 __ARMlet_Startup__(const void*, void*, Call68KFuncType*);

/*
 * These symbols aren't real, but are linker-generated symbols that
 * mark the start and end of the various data sections.
 */
extern long __DataStart__[];
extern long __RODataStart__[];
extern long __BSSStart__[];
extern long __BSSEnd__[];
extern long __CodeRelocStart__[];
extern long __CodeRelocEnd__[];
extern long __DataRelocStart__[];
extern long __DataRelocEnd__[];

/*
 * This function performs relocation for Tapwave Native Application.
 */
static void relocate(void)
{
    // this symbol points to the very beginning of current application
    long base = (long) __ARMlet_Startup__;
    long *cur, *end;

    // handle code-to-data relocation
    cur = __CodeRelocStart__;
    end = __CodeRelocEnd__;
    for (; cur < end; cur++) {
        *(long*)(base + *cur) += base;
    }

    // handle data-to-data relocation
    cur = __DataRelocStart__;
    end = __DataRelocEnd__;
    for (; cur < end; cur++) {
        *(long*)(base + *cur) += base;
    }
}

/*
 * The following functions provide malloc/free support to Metrowerks
 * Standard Library (MSL). This feature requires the MSL library be
 * built with _MSL_OS_DIRECT_MALLOC enabled.
 */
void*
__sys_alloc(size_t size)
{
    void * ptr = MemPtrNew(size);
    ErrFatalDisplayIf(ptr == NULL, "out of memory");
    return ptr;
}

void
__sys_free(void* ptr)
{
    (void) MemPtrFree(ptr);
}

size_t
__sys_pointer_size(void* ptr)
{
    return (size_t) MemPtrSize(ptr);
}

/*
 * This function converts stanard windows path into palmos path.
 */
int
__sys_path(const char* path, char* buffer, size_t length)
{
    UInt16 volume;

    if (path[1] == ':') {
        // absolute path
        // convert drive letter to slot number, ref ascii table.
        int slot = (path[0] & 0x1F);
        if (slot == 3) {
            slot = twSlotInternal;
        }
        // iterate all volumes
        UInt32 it = vfsIteratorStart;
        while (!VFSVolumeEnumerate(&volume, &it)) {
            if (slot == TwGetSlotNumberForVolume(volume)) {
                if (strlen(path) < length) {
                    strcpy(buffer, path + 2);
                    goto done;
                }
                break;
            }
        }
    } else {
        // relative path
        // find application data volume and directory
        if (!TwGetDBDataDirectory(NULL, &volume, buffer, length)) {
            if (path[0] == '/' || path[0] == '\\') {
                buffer[0] = 0;
            }
            if (strlen(buffer) + 1 + strlen(path) < length) {
                strcat(buffer, "/");
                strcat(buffer, path);
                goto done;
            }
        }
    }
    return -1;
 done:
    for (int i = 0; buffer[i] != 0; i++) {
        if (buffer[i] == '\\') {
            buffer[i] = '/';
        }
    }
    return volume;
}

/*
 * The following functions provide hooks for stdin/stdout/stderr.
 * Applications may override them to do whatever they want. The
 * default implementation redirects console IO through ARM semihosting
 * interface.
 */
int
__close_console(__file_handle file)
{
    return __no_io_error;
}

int
__read_console(__file_handle file, unsigned char * buff, size_t * count, __ref_con ref_con)
{
    return __io_EOF;
}

int
__write_console(__file_handle file, unsigned char * buff, size_t * count, __ref_con ref_con)
{
    return __no_io_error;
}

/*
 * The following functions provide basic support for non-console stdio.
 */
int
__open_file(const char * path, __file_modes mode, __file_handle * handle)
{
    char buffer[256];
    int volume = __sys_path(path, buffer, sizeof(buffer));
    UInt16 vfsmode = 0;
    Err err;
    
    if (mode.open_mode == __create_if_necessary) {
        vfsmode |= vfsModeCreate;
    } else if (mode.open_mode == __create_or_truncate) {
        vfsmode |= vfsModeCreate | vfsModeTruncate;
    }
    if (mode.io_mode & __read) {
        vfsmode |= vfsModeRead;
    } else if (mode.io_mode & __write) {
        vfsmode |= vfsModeWrite;
    }
    err = VFSFileOpen(volume, buffer, vfsmode, handle);
    return (err ? __io_error : __no_io_error);
}

int
__close_file(__file_handle file)
{
    Err err = VFSFileClose((FileRef) file);
    return (err ? __io_error : __no_io_error);
}

int
__read_file(__file_handle file, unsigned char * buff, size_t * count, __ref_con ref_con)
{
    Err err = VFSFileRead((FileRef) file, *count, buff, count);
    return (*count ? __no_io_error : (err == vfsErrFileEOF ? __io_EOF : __io_error));
}

int
__write_file(__file_handle file, unsigned char * buff, size_t * count, __ref_con ref_con)
{
    Err err = VFSFileWrite((FileRef) file, *count, buff, count);
    return (err ? __io_error : __no_io_error);
}

int
__position_file(__file_handle file, fpos_t * position, int mode, __ref_con ref_con)
{
    Err err = VFSFileSeek((FileRef) file, (FileOrigin) mode, (Int32) *position);
    if (err == errNone) {
        err = VFSFileTell((FileRef) file, position);
    }
    return (err ? __io_error : __no_io_error);
}

int
__delete_file(const char * name)
{
    char buffer[256];
    int volume = __sys_path(name, buffer, sizeof(buffer));
    return (VFSFileDelete(volume, buffer) ? __io_error : __no_io_error);
}

int
__rename_file(const char * src, const char * dst)
{
    char srcbuf[256];
    int srcvol = __sys_path(src, srcbuf, sizeof(srcbuf));
    char dstbuf[256];
    int dstvol = __sys_path(dst, dstbuf, sizeof(dstbuf));
    if (srcvol == dstvol && !VFSFileRename(srcvol, srcbuf, dstbuf)) {
        return __no_io_error;
    }
    return __io_error;
}

/*
 * The following function provide common unix system call interface.
 */
int open(const char *path, int flags, ...)
{
    __file_handle fd = -1;
    __file_modes mod = {0};
    if (flags & O_RDONLY) mod.io_mode = __read;
    if (flags & O_WRONLY) mod.io_mode = __write;
    if (flags & O_RDWR  ) mod.io_mode = __read_write;
    if (flags & O_APPEND) mod.io_mode = __append;
    __open_file(path, mod, &fd);
    return (int) fd;
}

int close(int fd)
{
    Err err = VFSFileClose((FileRef) fd);
    return (err ? -1 : 0);
}

int read(int fd, void* buf, size_t len)
{
    Err err = VFSFileRead((FileRef) fd, len, buf, &len);
    return (len > 0) ? len : (err ? -1 : 0);
}

int write(int fd, void* buf, size_t len)
{
    Err err = VFSFileWrite((FileRef) fd, len, buf, &len);
    return (len > 0) ? len : (err ? -1 : 0);
}

long lseek(int fd, long offset, int whence)
{
    VFSFileSeek((FileRef) fd, (FileOrigin) whence, offset);
    return VFSFileTell((FileRef) fd, (UInt32*)&offset) ? -1 : offset;
}

int chsize(int fd, long size)
{
    return VFSFileResize((FileRef) fd, size) ? -1 : 0;
}

int fstat(int fd, struct stat * buf)
{
    memset(buf, 0, sizeof(*buf));
    VFSFileGetDate((FileRef) fd, vfsFileDateModified, (UInt32*)&buf->st_mtime);
    buf->st_mtime -= 2082844800;
    return VFSFileSize((FileRef) fd, (UInt32*)&buf->st_size) ? -1 : 0;
}

int access(const char *path, int mode)
{
    char buffer[256];
    int volume = __sys_path(path, buffer, sizeof(buffer));
    FileRef f;

    if (!VFSFileOpen(volume, buffer, (mode == W_OK ? vfsModeWrite : vfsModeRead), &f)) {
        VFSFileClose(f);
        return 0;
    }

    return -1;
}

int mkdir(const char *path, ...)
{
    char buffer[256];
    int volume = __sys_path(path, buffer, sizeof(buffer));
    return VFSDirCreate(volume, buffer) ? -1 : 0;
}

int rmdir(const char* path)
{
    char buffer[256];
    int volume = __sys_path(path, buffer, sizeof(buffer));
    return VFSFileDelete(volume, buffer) ? -1 : 0;
}

void abort(void)
{
    ErrDisplayFileLineMsg(__FILE__, 0, "abort");
}

void exit(int status)
{
    ErrDisplayFileLineMsg(__FILE__, status, "exit");
}

/*
 * The following functions provide simple time support to MSL.
 */
time_t
__get_time(void)
{
    // Convert epoch 1904-01-01 to 1970-01-01
    return TimGetSeconds() - 2082844800;
}

int
__to_gm_time(time_t* time)
{
    // Convert local time to utc time
    *time -= (PrefGetPreference(prefTimeZone) + PrefGetPreference(prefDaylightSavingAdjustment)) * 60;
    return 1;
}

int
__isdst(void)
{
    // Check if we in day light saving time currently.
    return PrefGetPreference(prefDaylightSavingAdjustment) != 0;
}

struct DIR
{
    struct dirent   _d__dirent;
    UInt32          _d__ref;        /* new style FSRef of directory to iterate */
    UInt32          _d__iterator;   /* new style directory iterator reference */
    FileInfoType    _d__f_info;
};

DIR* opendir (const char * path)
{
    char buf[256];
    int volume = __sys_path(path, buf, sizeof(buf));
    DIR * dir = NULL;
    FileRef dirRef;

    if (errNone == VFSFileOpen(volume, buf, vfsModeRead, &dirRef)) {
        dir = (DIR*) malloc(sizeof(DIR));
        if (NULL != dir) {
            dir->_d__ref = dirRef;
            dir->_d__iterator = vfsIteratorStart;
            dir->_d__f_info.nameBufLen = sizeof(dir->_d__dirent.d_name);
            dir->_d__f_info.nameP = dir->_d__dirent.d_name;
        }
    }
    
    return dir;
}

int closedir(DIR * dir)
{
    int res = -1;

    if (dir) {
        res = VFSFileClose(dir->_d__ref) ? -1 : 0;
        free(dir);
    }
    
    return res;
}

struct dirent* readdir(DIR * dir)
{
    if (VFSDirEntryEnumerate(dir->_d__ref, &dir->_d__iterator, &dir->_d__f_info)) {
        return (struct dirent*) NULL;
    }

    return &dir->_d__dirent;
}

/*
 * This is the real entrypoint for Tapwave Native Application. It
 * depends on various CodeWarrior 9.2 compiler/linker/runtime features.
 */
static SYSTEM_CALLBACK UInt32
Startup(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
    if (emulStateP) {
        twEmulState = emulStateP;
        twCall68KFunc = call68KFuncP;
        // COMMENT: normal pace native object launch
        return PilotMain(sysAppLaunchCmdNormalLaunch, userData68KP, 0);
    } else {
        // Setup TNA interface dispatch table
        twGlue = (struct TwGlue*) userData68KP;

        // OPTIONAL: relocate data segment
        relocate();

        // OPTIONAL: initialize the floating-point library
        _fp_init();

        return 0;
    }
}

#pragma PIC off
asm UInt32
__ARMlet_Startup__(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
    b        Startup             //   0 forwarding call
    nop                          //   4
    nop                          //   8
    nop                          //  12
    nop                          //  16
    nop                          //  20
    nop                          //  24
    dcd      'TWNA'              //  28 Tapwave Native Application
    dcd      1                   //  32 version 1
    dcd      'cdwr'              //  36 make this section the same as the __ARMlet_Startup__
    dcd      __DataStart__       //  40 used by CodeWarrior 9.2
    dcd      __RODataStart__     //  44
    dcd      __BSSStart__        //  48
    dcd      __BSSEnd__          //  52
    dcd      __CodeRelocStart__  //  56
    dcd      __CodeRelocEnd__    //  60
    dcd      __DataRelocStart__  //  64
    dcd      __DataRelocEnd__    //  68
}
#pragma PIC reset

#endif // __MWERKS__

#ifdef __ARMCC_VERSION

static void relocate(struct TwGlue* twGlue)
{
    Int8* base = (Int8*) __ARMlet_Startup__;
    Int32 size = MemPtrSize(base);
    Int32* end = (Int32*)(base + size - 4);
    Int32* cur = end - (*end);

    for (; cur < end; cur++) {
        *(long*)(base + *cur) += (Int32)base;
    }
}

#pragma arm section code = "startup_code_header_area"
UInt32
__ARMlet_Startup__(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
    if (emulStateP) {
        twEmulState = emulStateP;
        twCall68KFunc = call68KFuncP;
        // COMMENT: normal pace native object launch
        return PilotMain(sysAppLaunchCmdNormalLaunch, userData68KP, 0);
    } else {
        // NOTE: perform self relocation first
        reloc((struct TwGlue*) userData68KP);

        // Setup global variable
        ::twGlue = (struct TwGlue*) userData68KP;

        return 0;
    }
}
#pragma arm section code

#endif // __ARMCC_VERSION

#ifdef _WIN32
/*
 * This is the real entrypoint for Tapwave Native Application.
 * It is a DLL export function, whose name is referred by Application.rcp
 */
__declspec(dllexport) UInt32
__ARMlet_Startup__(const void *emulStateP, void *userData68KP, Call68KFuncType *call68KFuncP)
{
    // Special call for initialization
    if (!emulStateP) {
        /* Setup TNA interface dispatch table */
        twGlue = (struct TwGlue*) userData68KP;

        return 0;
    }

    twEmulState = emulStateP;
    twCall68KFunc = call68KFuncP;
    return PilotMain(sysAppLaunchCmdNormalLaunch, NULL, 0);
}
#endif // _WIN32

#ifdef __cplusplus
} // extern "C"
#endif
