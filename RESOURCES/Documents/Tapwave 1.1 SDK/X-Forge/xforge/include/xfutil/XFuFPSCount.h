/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Frame rate counter class
 * 
 * $Id: XFuFPSCount.h,v 1.5 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.5 $
 */

#ifndef XFUFPSCOUNT_H_INCLUDED
#define XFUFPSCOUNT_H_INCLUDED


//! Frames per second counter utility class.
class XFuFPSCount 
{

public:
    
    //! Destructor.
    ~XFuFPSCount();

    //! Creates a new XFuFPSCount object.
    /*! \param aFrameInterval Describes the interval for which the frame rate is calculated.
     *                        Larger numbers give more stable values, but take more memory, and update slower.
     */
    static XFuFPSCount * create(INT32 aFrameInterval = 5);
    
    //! Tick the counter.
    /*! This function should be called once per frame.
     */
    void tick();

    //! Returns the current FPS value.
    REAL getFPS();

protected:
    
    //! Protected constructor.
    XFuFPSCount();
    
    //! Array of tick timestamps.
    INT32 *mTicks;
    //! Total number of tick timestamps.
    INT32 mTickCount;
    //! The current tick timestamp in the array.
    INT32 mCurrentTick;
};


#endif // !XFUFPSCOUNT_H_INCLUDED

