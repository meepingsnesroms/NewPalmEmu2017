/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Video recorder class (for desktop use)
 * 
 * $Id: XFuVideoRecorder.h,v 1.3 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.3 $
 */

#ifndef XFUVIDEORECORDER_H_INCLUDED
#define XFUVIDEORECORDER_H_INCLUDED

//! Utility to help creation of video files from running x-forge applications.
class XFuVideoRecorder
{
protected:
    //! Hidden constructor
    XFuVideoRecorder();
    FLOAT32 mLastTick;    //!< Last tick handled
    FLOAT32 mTicksPerFrame; //!< Ticks each frame takes
    INT32 mFrame;       //!< Next frame number
    CHAR *mPrefix;      //!< Filename prefix
    //! Called by tick() to store a single frame. 
    /*! May get several calls with the same frame if framerate is too low.
     *  Defined as virtual so that it is possible to create new video store
     *  methods. The basic implementation stores 24-bit BMP files.
     */
    virtual void storeFrame(XFcGLSurface *aSurface);

public:
    //! Creation function. Framerates such as 24 or 15 are typically good for video.    
    static XFuVideoRecorder * create(const CHAR *aPrefix, INT32 aDesiredFPS);
    //! Ticking function. Should be called once per tick after all rendering is done.
    void tick(XFcGLSurface *aSurface);
    //! Virtual destructor.
    virtual ~XFuVideoRecorder();
};

#endif
