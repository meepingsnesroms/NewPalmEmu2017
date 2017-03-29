/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief GL Profiler interface
 * 
 * $Id: XFcGLProfiler.h,v 1.4 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.4 $
 */

#ifndef XFC_GLPROFILER_H_INCLUDED
#define XFC_GLPROFILER_H_INCLUDED


enum XFC_GLPROFILER_EVENTFLAGS
{
    XFCGLP_LOG_FRAME = 0,
    XFCGLP_LOG_TRIFLAT,
    XFCGLP_LOG_TRIGOURAUD,
    XFCGLP_LOG_TRITEXTURE,
    XFCGLP_LOG_TRITEXTURE1555,
    XFCGLP_LOG_TRITEXTUREFLAT,
    XFCGLP_LOG_TRITEXTUREGOURAUD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVE,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVE1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLAT,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUD,
    XFCGLP_LOG_TRIFLATADD,
    XFCGLP_LOG_TRIGOURAUDADD,
    XFCGLP_LOG_TRITEXTUREADD,
    XFCGLP_LOG_TRITEXTUREADD1555,
    XFCGLP_LOG_TRITEXTUREFLATADD,
    XFCGLP_LOG_TRITEXTUREGOURAUDADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEADD1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDADD,
    XFCGLP_LOG_TRIFLATALPHA,
    XFCGLP_LOG_TRIGOURAUDALPHA,
    XFCGLP_LOG_TRITEXTUREALPHA,
    XFCGLP_LOG_TRITEXTUREALPHA1555,
    XFCGLP_LOG_TRITEXTUREFLATALPHA,
    XFCGLP_LOG_TRITEXTUREGOURAUDALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEALPHA1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDALPHA,
    XFCGLP_LOG_TRIFLATINVMUL,
    XFCGLP_LOG_TRIGOURAUDINVMUL,
    XFCGLP_LOG_TRITEXTUREINVMUL,
    XFCGLP_LOG_TRITEXTUREINVMUL1555,
    XFCGLP_LOG_TRITEXTUREFLATINVMUL,
    XFCGLP_LOG_TRITEXTUREGOURAUDINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEINVMUL1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDINVMUL
};


//! Adds an event into the GL profiler binary log.
/*!
 * This method is meant to be used with the GLDefaultProfiler graphics device.
 * It can be used to store user-defined events into the profiler log. Doing so
 * may require some changes in the profiler log analyzer util. 
 * \note Calling this function while the GLDefaultProfiler graphics device is not
 *       in use may cause undefined behavior.
 * \param aEvent event type; 0..63. Events in use are defined in the XFC_GLPROFILER_EVENTFLAGS enum.
 * \param aValue event value; 0..1023. Typically time or pixel count.
 */
XFCIMPORT void xfcGLProfilerLog(UINT32 aEvent, UINT32 aValue);


#endif // !XFC_GLPROFILER_H_INCLUDED

