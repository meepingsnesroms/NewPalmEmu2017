/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief RIFF Wave loader
 * 
 * $Id: XFuWavLoad.h,v 1.8 2003/10/07 06:35:28 toni Exp $
 * $Date: 2003/10/07 06:35:28 $
 * $Revision: 1.8 $
 */

#ifndef XFUWAVLOAD_H_INCLUDED
#define XFUWAVLOAD_H_INCLUDED



class XFcAudioBuffer;


//! Loads RIFF .Wav file as XFcAudioBuffer.
/*! Currently only supports 8/16-bit mono/stereo PCM samples.
 */
XFcAudioBuffer * xfuLoadWav(const CHAR *aFilename, UINT32 aFlags);

//! Loads RIFF .Wav file as XFcAudioBuffer.
/*! Currently only supports 8/16-bit mono/stereo PCM samples.
 */
XFcAudioBuffer * xfuLoadWav(const CHAR *aFilename);


#endif // !XFUWAVLOAD_H_INCLUDED

