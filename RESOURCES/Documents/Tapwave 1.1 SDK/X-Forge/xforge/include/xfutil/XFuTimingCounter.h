/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFuConfiguration.h is the header file for the XFuConfiguration class.
 *
 * $Id: XFuTimingCounter.h,v 1.4 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.4 $
 */

#ifndef XFUTIMINGCOUNTER_H_INCLUDED
#define XFUTIMINGCOUNTER_H_INCLUDED

#define XFU_TIMINGCOUNTER_STARTED 1
#define XFU_TIMINGCOUNTER_RUNNING 2

//! Timing counter that takes average of a definable amount of samples.
/*!
 *  This counter can be used for evaluating time spend within functions even in the
 *  case the time is less than the resolution of the clock. The timer takes sliding
 *  average of large amount of samples, and thus gives results that are statistically
 *  more accurate than the clock itself.
 */
class XFuTimingCounter
{
public:
    //! Constructs the timing counter with aSampleCount amount of samples
    static XFuTimingCounter *create(INT32 aSampleCount)
    {
        if (aSampleCount <= 0)
            return NULL;

        XFuTimingCounter *counter = new XFuTimingCounter();

        if (counter)
        {
            counter->mSamples = new INT32[aSampleCount];
            if (counter->mSamples == NULL)
            {
                delete counter;
                return NULL;
            }

            counter->mMaxSampleCount = aSampleCount;
        }

        return counter;
    }

    //! Starts counting of one timing iteration
    virtual void start()
    {
        mTickDiff = 0;
        mState = XFU_TIMINGCOUNTER_STARTED;
        resume();
    }

    //! Stops counting of one timing iteration
    virtual void stop()
    {
        if (mState & XFU_TIMINGCOUNTER_STARTED)
        {
            pause();
            INT32 lastTick = mSamples[mCurrentSample];
            mSampleCount++;
            if (mSampleCount > mMaxSampleCount)
            {
                mSampleCount = mMaxSampleCount;
                mFirstSample = (mFirstSample + 1) % mSampleCount;
            }
            mCurrentSample = (mCurrentSample + 1) % mSampleCount;
            mSamples[mCurrentSample] = lastTick + mTickDiff;
            mState = 0;
        }
    }


    //! Pauses the counting
    virtual void pause()
    {
        if ((mState & (XFU_TIMINGCOUNTER_STARTED | XFU_TIMINGCOUNTER_RUNNING)) == 
            (XFU_TIMINGCOUNTER_STARTED | XFU_TIMINGCOUNTER_RUNNING))
        {
            INT32 tick = XFcCore::getTick();
            mTickDiff = mTickDiff + (tick - mCurrentTick);
            mState &= ~XFU_TIMINGCOUNTER_RUNNING;
        }
    }

    //! Resumes the counting
    virtual void resume()
    {
        if ((mState & (XFU_TIMINGCOUNTER_STARTED | XFU_TIMINGCOUNTER_RUNNING)) == 
            XFU_TIMINGCOUNTER_STARTED)
        {
            mCurrentTick = XFcCore::getTick();
            mState |= XFU_TIMINGCOUNTER_RUNNING;
        }
    }

    //! Resets the counter
    virtual void reset()
    {
        mSampleCount = 0;
        mCurrentSample = 0;
        mFirstSample = 0;
        mState = 0;
    }

    //! Returns the average time spent between start() and stop() calls
    virtual REAL getTime()
    {
        if (mSampleCount > 1)
            return (REAL)(mSamples[mCurrentSample] - mSamples[mFirstSample]) / (mSampleCount - 1);
        else
            return REALi(0);
    }

    //! Virtual destructor
    virtual ~XFuTimingCounter()
    {
        delete[] mSamples;
    }

protected:
    XFuTimingCounter()
    {
        mSamples = NULL;
        mSampleCount = 0;
        mMaxSampleCount = 0;
        mCurrentSample = 0;
        mFirstSample = 0;
    }

    INT32 *mSamples;
    INT32 mSampleCount;
    INT32 mMaxSampleCount;
    INT32 mFirstSample;
    INT32 mCurrentSample;
    INT32 mCurrentTick;
    INT32 mTickDiff;
    INT32 mState;
};

#endif //XFUTIMINGCOUNTER_H_INCLUDED

