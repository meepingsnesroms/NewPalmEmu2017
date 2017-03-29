/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Built-in profiler helper functionality.
 * 
 * $Id: XFcProfiler.h,v 1.11 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.11 $
 * 
 */

#ifndef XFC_CORE_XFCPROFILER_H_INCLUDED
#define XFC_CORE_XFCPROFILER_H_INCLUDED




//! Flags used in frame event of the event log profiler.
enum XFCPROFILERFLAGS
{
    XFCPROF_ONLYFPSFRAMEEVENT = 1       //!< Only report FPS in frame event.
};


//! Profiler static class.
/*!
 * X-Forge Core supports two kinds of profiling: event log profiling and
 * sampling. The event log system works on all platforms; the sampling system
 * currently only works on WinCE.
 * \par
 * The event log profiling scheme works like this:
 * \code
 * initEventLog(); // run this first in some initialization function.
 * ..
 * addEvent("somefx1"); // call AddEvent before each event
 * ..
 * addEvent("somefx2");
 * ..
 * addEvent("somefx3");
 * ..
 * frameEvent(); // call frameEvent before printing out
 * printOut(GetEventLog());
 * resetEvent("print ","somefx0"); // reset log
 * ..
 * addEvent("core.."); // call this before ending the render function, or the
 *                     // last logged event will get the core time as well.
 * \endcode
 * The sampling profiler stores samples of the instruction pointer
 * which can be used to make a map of function timings using .map
 * file generated with the compiler.
 */
class XFCDLLEXPORT XFcProfiler
{
public:

    //! Initializes profiling log.
    /*! \note Call this only once.
     */
    XFCIMPORT static void initEventLog();

    //! Gets pointer to the profiling log.
    XFCIMPORT static CHAR * getEventLog();

    //! Adds an event to the log (name should preferably be 6 characters).
    /*! \note Keep the descriptions short, as the allocated space for the
     *        whole log is approximately only 1 KB or so.
     * \note Do not delete[] the buffer; it is owned by the core.
     */
    XFCIMPORT static void addEvent(const CHAR *aName);

    //! Marks end of an event, calculates framerate and adds it to the list.
    /*! The log is printable after this call.
     * \note Next call after this should be resetEvent.
     * \sa resetEvent
     */
    XFCIMPORT static void frameEvent(INT32 aFlags = 0);

    //! Resets the event log.
    /*!
     * \param aLastname name of the event preceding this call.
     * \param aNextname name of the event following this call.
     */
    XFCIMPORT static void resetEvent(const CHAR *aLastname,
                                     const CHAR *aNextname);

    //! Starts the sampling profiler.
    /*!
     * \note Sampling profiler requires about 64KB of memory.
     * \note Not supported on all platforms.
     * \note Core must be compiled with XFC_USE_SAMPLINGPROFILER to enable it.
     * \note Under WinCE, you must link toolhelp.lib to the application when
     *       sampling profiler is used.
     */
    XFCIMPORT static void startSampler(const CHAR *aFilename = XFCSTR("sampler_dump.dat"),
                                       INT aStartPaused = 0);
    //! Pauses sampler.
    XFCIMPORT static void pauseSampler();
    //! Resumes sampler.
    XFCIMPORT static void resumeSampler();
    //! Ends sampler.
    /*! \note Calling this is important, as it closes the file and shuts
     *        down worker threads etc.
     */
    XFCIMPORT static void endSampler();
};


#endif // !XFC_CORE_XFCPROFILER_H_INCLUDED

