/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio library sound format class.
 * 
 * $Id: XFcAudioFormat.h,v 1.11 2003/10/06 11:26:47 toni Exp $
 * $Date: 2003/10/06 11:26:47 $
 * $Revision: 1.11 $
 */

#ifndef XFC_CORE_XFCAUDIOFORMAT_H_INCLUDED
#define XFC_CORE_XFCAUDIOFORMAT_H_INCLUDED


//! Audio library sound format class.
class XFcAudioFormat
{

public:

    //! Sampling rate.
    FLOAT32 mSamplingRate;

    //! Flags.
    UINT32 mFlags;

    //! Number of samples.
    INT32 mSamples;

    //! Bytes per sample.
    INT32 mBytesPerSample;

    //! Channels (mono/stereo).
    INT32 mChannels;

    XFcAudioFormat();
    XFcAudioFormat(FLOAT32 aSamplingRate, UINT32 aFlags, INT32 aSamples);

};


#endif // !XFC_CORE_XFCAUDIOFORMAT_H_INCLUDED

