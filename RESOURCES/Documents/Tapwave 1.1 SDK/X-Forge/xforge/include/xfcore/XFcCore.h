/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Main header file for X-Forge Core.
 * 
 * $Id: XFcCore.h,v 1.62 2003/10/15 09:32:43 kkallio Exp $
 * $Date: 2003/10/15 09:32:43 $
 * $Revision: 1.62 $
 */

#ifndef XFC_XFCCORE_H_INCLUDED
#define XFC_XFCCORE_H_INCLUDED

#if defined(XFC_PLATFORM_WINCE)
#include <windows.h> // required for asserts.
#include <bldver.h> // used to detect smartphone2002 build
#endif

#if defined(XFC_PLATFORM_EPOC6)
    #ifdef __WINS__
        // disable memory manager for Symbian emulator builds
        #define XFC_MEMMGR_DISABLE
    #endif
#endif
#if defined(XFC_MEMMGR_DISABLE)
#include <stdlib.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#ifndef XFC_CORE_XFCCONFIG_H_INCLUDED
#include <xfcore/XFcConfig.h>
#endif

#ifndef XFC_CORE_COREENUMS_H_INCLUDED
#include <xfcore/XFcCoreEnums.h>
#endif
#ifndef XFC_CORE_XFCAPPPREFS_H_INCLUDED
#include <xfcore/XFcAppPrefs.h>
#endif
#ifndef XFC_CORE_XFCRECTANGLE_H_INCLUDED
#include <xfcore/XFcRectangle.h>
#endif
#ifndef XFC_CORE_XFCGLSURFACE_H_INCLUDED
#include <xfcore/XFcGLSurface.h>
#endif
#ifndef XFC_CORE_XFCRENDERER_H_INCLUDED
#include <xfcore/XFcRenderer.h>
#endif
#ifndef XFC_CORE_XFCAPP_H_INCLUDED
#include <xfcore/XFcApp.h>
#endif
#ifndef XFC_CORE_XFCCL_H_INCLUDED
#include <xfcore/XFcInput.h>
#endif
#ifndef XFC_CORE_XFCFILE_H_INCLUDED
#include <xfcore/XFcFile.h>
#endif
#ifndef XFC_CORE_XFCFILEFIND_H_INCLUDED
#include <xfcore/XFcFileFind.h>
#endif
#ifndef XFC_CORE_FIXED_H_INCLUDED
#include <xfcore/XFcFixed.h>
#endif
#ifndef XFC_CORE_XFCCFL_H_INCLUDED
#include <xfcore/XFcCFL.h>
#endif
#ifndef XFC_CORE_XFCAUDIOBUFFER_H_INCLUDED
#include <xfcore/XFcAudioBuffer.h>
#endif
#ifndef XFC_CORE_XFCAUDIO_H_INCLUDED
#include <xfcore/XFcAudio.h>
#endif
#ifndef XFC_CORE_XFCAUDIOFLAGS_H_INCLUDED
#include <xfcore/XFcAudioFlags.h>
#endif
#ifndef XFC_CORE_XFCPROFILER_H_INCLUDED
#include <xfcore/XFcProfiler.h>
#endif
#ifndef XFC_CORE_XFCMUTEX_H_INCLUDED
#include <xfcore/XFcMutex.h>
#endif
#ifndef XFC_CORE_XFCTHREAD_H_INCLUDED
#include <xfcore/XFcThread.h>
#endif
#ifndef XFC_CORE_XFCTHREADOBJECT_H_INCLUDED
#include <xfcore/XFcThreadObject.h>
#endif
#ifndef XFC_CORE_XFCSTR_H_INCLUDED
#include <xfcore/XFcStringToolkit.h>
#endif
#ifndef XFC_XFCMATH_H_INCLUDED
#include <xfcore/XFcMath.h>
#endif
#ifndef XFC_MATH_VECTOR_H_INCLUDED
#include <xfcore/XFcVector.h>
#endif
#ifndef XFC_MATH_MATRIX_H_INCLUDED
#include <xfcore/XFcMatrix.h>
#endif
#ifndef XFC_MATH_QUATERNION_H_INCLUDED
#include <xfcore/XFcQuaternion.h>
#endif
#ifndef XFC_CORE_XFCGL_H_INCLUDED
#include <xfcore/XFcGL.h> 
#endif
#ifndef XFC_CORE_XFCGLVERTEXBUFFER_H_INCLUDED
#include <xfcore/XFcGLVertexBuffer.h>
#endif
#ifndef XFC_CORE_XFCGLTRIANGLEINFOBUFFER_H_INCLUDED
#include <xfcore/XFcGLTriangleInfoBuffer.h>
#endif
#ifndef XFC_CORE_XFCGLTEXTUREFROMFILE_H_INCLUDED
#include <xfcore/XFcGLTextureFromFile.h>
#endif
#ifndef XFC_CORE_XFCIMAGELOADER_H_INCLUDED
#include <xfcore/XFcImageLoader.h>
#endif
#ifndef XFCLOGGER_H_INCLUDED
#include <xfcore/XFcLogger.h>
#endif
#ifndef XFC_CORE_XFCUSE_H_INCLUDED
#include <xfcore/XFcUse.h>
#endif
#ifndef XFC_XFCGLRESOURCESURFACE_H_INCLUDED
#include <xfcore/XFcGLResourceSurface.h>
#endif
#ifndef XFCCOMMUNICATIONSCHEDULER_H_INCLUDED
#include <xfcore/net/XFcCommunicationScheduler.h>
#endif
#ifndef XFCRLESPRITE_H_INCLUDED
#include <xfcore/XFcRLESprite.h>
#endif
#ifndef XFC_CORE_XFCDATETIME_H_INCLUDED
#include <xfcore/XFcDateTime.h>
#endif
#ifndef XFC_CORE_XFCHARDWAREID_H_INCLUDED
#include <xfcore/XFcHardwareId.h>
#endif
#ifndef XFC_CORE_XFCGLSURFACETOOLKIT_H_INCLUDED
#include <xfcore/XFcGLSurfaceToolkit.h>
#endif

class XFcCommunication;
class XFcCPUInfo;
class XFcPrimitiveDraw;
class XFcPrimitiveTranslator;

//! When application is set to non-exclusive mode, this structure is used to report the visible area of the framebuffer.
struct XFcExclusiveModeSettings
{
    INT32 mVisibleWidth;        //!< Width of the visible area.
    INT32 mVisibleHeight;       //!< Height of the visible area.
};

//! Static core class, contains global functions.
class XFCDLLEXPORT XFcCore 
{
public:
    //! Returns platform as a printable CHAR * string.
    /*! \return Printable CHAR * string describing the platform.
     */
    XFCIMPORT static const CHAR * getPlatformString();

    //! Returns platform as a generic id (see XFCPLATFORM enum).
    /*! \return Platform type as an enumerated value.
     *  \sa XFCPLATFORM
     */
    XFCIMPORT static INT32 getPlatformId();

    //! Returns command line as a CHAR string, if applicable to the platform.
    XFCIMPORT static const CHAR * getCommandlineString();

    //! Sets (or changes) the renderer object.
    /*! Causes the old renderer to get a deinitialization call, and the new
     *  one to receive an initialization call.
     */
    XFCIMPORT static void setRenderer(XFcRenderer *aNewRenderer);
    
    //! Sets (or changes) the input receiver object.
    XFCIMPORT static void setController(XFcInput *aNewController);

    //! Returns the system tick (in milliseconds).
    /*! \return Current tick, in milliseconds.
     *  \note The tick counts milliseconds from the application start-up.
     *  \note The granularity of ticks depends on the used platform. 
     *  Pocketpc has 1ms granularity while symbian platforms have 16-17ms granularity.
     *  \note If getTick() is not called for 5 minutes (300000ms) or more, the tick is only advanced by 1ms.
     *  This is to avoid any system freezes due to physics running forever or something similar.
     *  \sa getTick64()
     */
    XFCIMPORT static INT32 getTick();
    
    //! Returns the system tick (in milliseconds) as an INT64 value.
    /*! Implemeted for situations where INT32 overflow is a problem.
     * \sa getTick()
     */
    XFCIMPORT static INT64 getTick64();
    
    //! Quits the application.
    /*! This method never returns. It causes onAppDeinit() to be called, as well as
     *  closing any current renderers and so on.
     */
    XFCIMPORT static void quit();
    
    //! Performs system panic; shows dialog for user, tries to shut down cleanly.
    /*! This method is to be used when an error situation is so severe
     *  that it is uncertain whether the application is able to continue.
     */
    XFCIMPORT static void systemPanic(const CHAR *aPanicMessage);
    
    //! Returns a pointer to the application class.
    /*! \return Pointer to the application class.
     * \note The application class is a good place to store any application global
     *       data that would normally be stored as global static data. 
     */
    XFCIMPORT static XFcApp * getApp();

    //! Returns graphics device logical width in pixels.
    /*!
     * \note Since different graphics devices may have different logical sizes
     *       compared to physical ones (esp. the FSAA devices), the values returned
     *       by these functions are only valid after the creation of a XFcGL object.
     * \return device width, in pixels.
     */
    XFCIMPORT static INT32 getDeviceWidth();
    
    //! Returns graphics device logical height in pixels.
    /*!
     * \note Since different graphics devices may have different logical sizes
     *       compared to physical ones (esp. the FSAA devices), the values returned
     *       by these functions are only valid after the creation of a XFcGL object.
     * \return device height, in pixels.
     */
    XFCIMPORT static INT32 getDeviceHeight();

    //! Opens a compressed file library from filename.
    /*!
     * You can open multiple files. If several resource names overlap, only the
     * last opened one is used.
     * \param aFileName filename of the resource file.
     * \return 1 if success.
     * \return 0 if failure (out of memory, file not found, or corrupted file).
     */
    XFCIMPORT static INT openCFL(const CHAR * aFileName);
    
    //! Resets the CFL directory.
    /*!
     * In order to change levels or other data, you may want to flush the
     * current CFL directory entries and re-open the CFL files.
     * \note It's not required to call this method before quitting the application.
     */
    XFCIMPORT static void resetCFLDirectory();

    //! Changes the default file open strategy
    /*!
     * See XFCFILEOPENSTRATEGY enum. The default strategy is XFCFO_DISKFIRST.
     */
    XFCIMPORT static void setFileOpenStrategy(INT32 aStrategy);

    //! Attempts to compact memory pool.
    /*! Tells the memory manager that now would be a good time to do any 
     *  house-keeping tasks that may take some time. 
     * \param aFlags reserved; set to 0
     */
    XFCIMPORT static void compactMemory(UINT32 aFlags);

    //! Returns size of an allocated memory block.
    /*! \return Bytes of memory in the block.
     *  \note If the given pointer is not valid, the operation is undefined.
     */
    XFCIMPORT static UINT32 getMemoryBlockSize(void *aPtr);

    //! Returns free memory.
    /*! \return Bytes of free memory in the pool.
     */
    XFCIMPORT static UINT32 getFreePoolMemory();
    
    //! Performs platform independent memory allocation.
    /*! \note Allocates memory outside the memory pool. The memory must be freed with freeSystemMemory().
     */
    XFCIMPORT static void * allocateSystemMemory(const INT32 aSize);
    
    //! Performs platform independent memory deallocation.
    /*! \note Use this only to free any memory allocated with allocateSystemMemory call.
     */
    XFCIMPORT static void freeSystemMemory(void *aPtr);

    //! Returns percentage of battery left (0..1).
    /*! It is advisable to show the battery state inside games; however, the
     *  value returned by this call is not reliable enough to warrant any action
     *  on low battery situations.
     * \return Percentage of battery left, as a REAL number (0..1).
     */
    XFCIMPORT static REAL getBatteryState();

    //! Adds a virtual button on screen.
    /*!
     * Please note that this is not a widget, and there is no visual feedback.
     * If stylus touched the defined rectangle, a keydown event is dispatched;
     * when the stylus exits the region, keyup event is dispatched.
     * You can map the scancode to a control code using the mapControlCode call.
     * \sa resetScreenButtons()
     */
    XFCIMPORT static void addScreenButton(const XFcRectangle &aRect, INT32 aScanCode);

    //! Removes all virtual buttons from screen.
    /*! \sa addScreenButton()
     */
    XFCIMPORT static void resetScreenButtons();

    //! Returns the number of allocated control mappings.
    /*! \sa getControlMapping()
     */
    XFCIMPORT static UINT32 getControlMappingCount();
    
    //! Returns one control mapping for an index.
    /*! Returned values aControlCode and aHardwareScanCode are either valid control and 
     *  hardware scan codes, or both are -1 if the allocated link is not currently in use.
     * \param aControlIndex index in range [0..n-1], where n is the return value of getControlMappingCount().
     * \param aControlCode reference to an INT32 where the control code will be written.
     * \param aHardwareScanCode reference to an INT32 where the hardware scan code will be written.
     */
    XFCIMPORT static void getControlMapping(UINT32 aControlIndex, INT32 &aControlCode, INT32 &aHardwareScanCode);
    
    //! Maps a hardware scan code to a control code.
    /*! When a certain scan code is received from physical buttons, the
     *  core can map it to some control code, and calls onControlDown()
     *  with the control code. All controls can be re-mapped with this method.
     * \param aControlCode control code to map to.
     * \param aHardwareScanCode hardware scan code to map from.
     * \sa unmapControlCode
     */
    XFCIMPORT static void mapControlCode(INT32 aControlCode, INT32 aHardwareScanCode);

    //! Unmaps the link from a hardware scan code to a control code.
    /*!
     * \param aControlCode control code to remove mapping for.
     * \param aHardwareScanCode hardware scan code to remove mapping for.
     * \sa mapControlCode
     */
    XFCIMPORT static void unmapControlCode(INT32 aControlCode, INT32 aHardwareScanCode);
    
    //! Resets control mappings to default.
    /*! Discards any changes done with mapControlCode, and returns to
     *  startup defaults (which are platform specific).
     */
    XFCIMPORT static void resetControlMappings();

    //! Returns network communication scheduler.
    XFCIMPORT static XFcCommunication * getCommunicationScheduler();

    //! Allocates and returns CPU information class.
    /*! \return XFcCPUInfo object if successful.
     *  \return NULL if failed or unsupported.
     *  \note the application must delete the returned object.
     */
    XFCIMPORT static XFcCPUInfo * getCPUInfo();
    
    //! Sleeps the current thread for at least specified amount of milliseconds.
    /*! It is highly recommended to sleep() as much as possible during
     *  idle moments, as this saves device batteries.
     * \param aMilliseconds amount of milliseconds to sleep at least.
     */
    XFCIMPORT static void sleep(INT32 aMilliseconds);

    //! Sets exclusive mode.
    /*! In exclusive mode application takes over the whole screen and may capture
     *  control events that would otherwise be handled by the device. Applications
     *  start in exclusive mode.
     * \param aMode 0 for non exclusive mode, or 1 for exclusive mode.
     * \param aSettings a reference to a struct that upon successful return describes the 
     *                  part of the framebuffer that is visible on screen.
     * \return 1 on success.
     * \return 0 on failure.
     */
    XFCIMPORT static INT32 setExclusiveMode(INT32 aMode, XFcExclusiveModeSettings &aSettings);
    
    //! Sets the action which should be taken when memory allocation fails.
    /*! This function sets the global action which should be taken whenever
     *  memory allocation fails. The normal mode of action is to do nothing
     *  and return NULL from the memory allocation. It may be desirable to
     *  set the out of memory action to XFCOMA_PANIC to detect out of memory 
     *  situations in unexpected situations. XFCOMA_ASSERT can be used to 
     *  break into debugger in debug builds; finally, XFCOMA_NONE can be used
     *  to return to normal operation.
     * \sa XFCOUTOFMEMORYACTION enumeration
     */
    XFCIMPORT static void setOutOfMemoryAction(INT32 aMode);

    //! Tells X-Forge whether to let the device go into idle state or not.
    /*! Normally a game would not want the device to go idle while the
     *  game is being played. There can be situations, such as cutscenes,
     *  which last long enough for the device to turn off backlight.
     *  In some situations, such as game menus or pause mode it is, however,
     *  desirable to let the device time out in order to save batteries.
     *  \sa XFCIDLEMODE enumeration
     */
    XFCIMPORT static void setIdleMode(INT32 aMode);

    //! Asks if the device is in silent profile.
    /*! \return -1 if unsupported
     *  \return  0 if device is not in silent profile
     *  \return  1 if device is in silent profile
     */
    XFCIMPORT static INT32 getSilentProfileState();

    //! Asks for the current locale in the device.
    /*! Note that this method is not neccessarily supported
     *  on devices that do support several locale settings,
     *  and even on those, not all supported locales are
     *  returned.
     *
     *  If querying the locale fails or is unsupported, the function
     *  returns zero. 
     *  If the application does not detect a supported locale, it should
     *  default to english.
     *
     *  See XFCLOCALES enum for full list of possible return values.
     */
    XFCIMPORT static UINT32 getDeviceLocale();

    //! Returns the primitive translator class for high level 2D vector graphics drawing.
    XFCIMPORT static XFcPrimitiveTranslator *getPrimitiveTranslator();

    //! Returns the primitive draw class for low level 2D vector graphics drawing.
    XFCIMPORT static XFcPrimitiveDraw *getPrimitiveDraw();
};


// Memory manager definitions.

#if !defined(XFC_MEMMGR_DISABLE)

//! Allocates specified amount of memory in bytes.
/*! \param aSize Bytes to allocate memory.
 * \return pointer to allocated memory, or NULL if unsuccessful.
 */
extern "C" void XFCDLLEXPORT XFCIMPORT * xfcMalloc(size_t aSize);
//! Allocates specified amount of memory in bytes and clears the allocated memory.
/*! \param aNum Number of elements to allocate.
 *  \param aSize Size of one element in bytes.
 * \return pointer to allocated and cleared memory, or NULL if unsuccessful.
 */
extern "C" void XFCDLLEXPORT XFCIMPORT * xfcCalloc(size_t aNum, size_t aSize);
//! Reallocates a memory block.
/*! \param aPtr Existing memory block to reallocate.
 *  \param aSize New requested size for the memory block.
 * \return pointer to the new reallocated block, or NULL if unsuccessful.
 */
extern "C" void XFCDLLEXPORT XFCIMPORT * xfcRealloc(void *aPtr, size_t aSize);
//! Frees a memory block.
/*! \param aPtr Pointer to previously allocated memory.
 */
extern "C" void XFCDLLEXPORT XFCIMPORT xfcFree(void *aPtr);

#if !(defined(XFC_MEMMGR_DEBUG) || defined(XFC_MEMMGR_PROFILE))
#define malloc(x) xfcMalloc((x))
#define calloc(x, y) xfcCalloc((x), (y))
#define realloc(x, y) xfcRealloc((x), (y))
#define free(x) xfcFree((x))
#else // !(defined(XFC_MEMMGR_DEBUG) || defined(XFC_MEMMGR_PROFILE))
#define malloc(x) ((memmgrsetowner(__FILE__, __LINE__), 0) ? NULL : xfcMalloc((x)))
#define calloc(x, y) ((memmgrsetowner(__FILE__, __LINE__), 0) ? NULL : xfcCalloc((x), (y)))
#define realloc(x, y) ((memmgrsetowner(__FILE__, __LINE__), 0) ? NULL : xfcRealloc((x), (y)))
#define free(x) ((memmgrsetowner(__FILE__, __LINE__), 0) ? NULL : xfcFree((x)))
#endif // !!(defined(XFC_MEMMGR_DEBUG) || defined(XFC_MEMMGR_PROFILE))

#if (defined(XFC_PLATFORM_PALM) && defined(XFC_COMPILER_ADS))

void * operator new(size_t aSize);
void * operator new(size_t aSize, const UINT32 aFlags);
void * operator new[](size_t aSize);
void * operator new[](size_t aSize, const UINT32 aFlags);
void operator delete(void *aPtr);
void operator delete(void *aPtr, const UINT32 aFlags);
void operator delete[](void *aPtr);
void operator delete[](void *aPtr, const UINT32 aFlags);

#elif (defined(XFC_PLATFORM_PALM) && defined(XFC_COMPILER_MW))

void* operator new(std::size_t size) throw(std::bad_alloc);
void* operator new(std::size_t size, const std::nothrow_t&) throw();

void  operator delete(void* ptr) throw();
void  operator delete(void* ptr, const std::nothrow_t&) throw();

void* operator new[](std::size_t size) throw(std::bad_alloc);
void* operator new[](std::size_t size, const std::nothrow_t&) throw();

void  operator delete[](void* ptr) throw();
void  operator delete[](void* ptr, const std::nothrow_t&) throw();

void* operator new  (std::size_t size, void* ptr) throw();
void* operator new[](std::size_t size, void* ptr) throw();

void  operator delete  (void* ptr, void*) throw();
void  operator delete[](void* ptr, void*) throw();

void* operator new(std::size_t size, const UINT32 aFlags) throw(std::bad_alloc);
void* operator new[](std::size_t size, const UINT32 aFlags) throw(std::bad_alloc);

void  operator delete(void* ptr, const UINT32 aFlags) throw();
void  operator delete[](void* ptr, const UINT32 aFlags) throw();
/*
#elif (defined(XFC_PLATFORM_PALM) && defined(XFC_COMPILER_MSVC))

inline void * __cdecl operator new(size_t aSize);
inline void * __cdecl operator new(size_t aSize, const UINT32 aFlags);
inline void * __cdecl operator new[](size_t aSize);
inline void * __cdecl operator new[](size_t aSize, const UINT32 aFlags);
inline void __cdecl operator delete(void *aPtr);
inline void __cdecl operator delete(void *aPtr, const UINT32 aFlags);
void __cdecl operator delete[](void *aPtr);
void __cdecl operator delete[](void *aPtr, const UINT32 aFlags);
*/
#elif defined(XFC_PLATFORM_WINCE)

inline void * __cdecl operator new(size_t aSize);
inline void * __cdecl operator new(size_t aSize, const UINT32 aFlags);
void * __cdecl operator new[](size_t aSize);
void * __cdecl operator new[](size_t aSize, const UINT32 aFlags);
inline void __cdecl operator delete(void *aPtr);
inline void __cdecl operator delete(void *aPtr, const UINT32 aFlags);
void __cdecl operator delete[](void *aPtr);
void __cdecl operator delete[](void *aPtr, const UINT32 aFlags);

#elif defined(XFC_PLATFORM_LINUX)

void * XFCDLLEXPORT operator new(size_t aSize);
void * XFCDLLEXPORT operator new(size_t aSize, const UINT32 aFlags);
void * XFCDLLEXPORT operator new[](size_t aSize);
void * XFCDLLEXPORT operator new[](size_t aSize, const UINT32 aFlags);
void XFCDLLEXPORT operator delete(void *aPtr);
void XFCDLLEXPORT operator delete(void *aPtr, const UINT32 aFlags);
void XFCDLLEXPORT operator delete[](void *aPtr);
void XFCDLLEXPORT operator delete[](void *aPtr, const UINT32 aFlags);

#elif defined(XFC_PLATFORM_PALM) || defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined (XFC_PLATFORM_EPOC)

void * operator new(size_t aSize);
void * operator new(size_t aSize, const UINT32 aFlags);
void * operator new[](size_t aSize);
void * operator new[](size_t aSize, const UINT32 aFlags);
void operator delete(void *aPtr);
void operator delete(void *aPtr, const UINT32 aFlags);
void operator delete[](void *aPtr);
void operator delete[](void *aPtr, const UINT32 aFlags);

#else

#error No platform defined.

#endif
#endif // !XFC_MEMMGR_DISABLE

#if !defined(XFC_MEMMGR_DISABLE) && (defined(XFC_MEMMGR_DEBUG) || defined(XFC_MEMMGR_PROFILE))
extern void XFCDLLEXPORT memmgrsetowner(const CHAR *aSourceFile,
                                        const UINT32 aSourceLine);
#define new (memmgrsetowner(__FILE__, __LINE__), 0) ? NULL : new
#define delete (memmgrsetowner(__FILE__, __LINE__), 0) ? (void)NULL : delete

#endif  // !XFC_MEMMGR_DEBUG

#endif // !XFC_XFCCORE_H_INCLUDED

