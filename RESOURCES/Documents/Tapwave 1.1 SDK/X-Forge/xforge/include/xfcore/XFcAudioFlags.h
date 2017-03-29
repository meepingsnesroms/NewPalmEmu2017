/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio flags.
 * 
 * $Id: XFcAudioFlags.h,v 1.5 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.5 $
 */

#ifndef XFC_CORE_XFCAUDIOFLAGS_H_INCLUDED
#define XFC_CORE_XFCAUDIOFLAGS_H_INCLUDED


//! Audio format flags.
enum XFCAUDIOFLAGS
{
    XFCAUDIO_RINGBUFFER = (1 << 8),
    XFCAUDIO_16BIT = (1 << 9),
    XFCAUDIO_STEREO = (1 << 10),
    XFCAUDIO_SIGNED = (1 << 11)
};

//! Audio interpolation mode flags.
enum XFCAUDIOINTERPOLATION
{
    XFCAUDIO_INTERPOLATION_NONE = 0,
    XFCAUDIO_INTERPOLATION_LINEAR = 1
};


#endif // !XFC_CORE_XFCAUDIOFLAGS_H_INCLUDED

