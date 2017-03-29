/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWVDMIXER_H__
#define __TWVDMIXER_H__

/*
 * Virtual device driver interface for the audio mixer.
 *
 * The audio mixer mixes N channel digital audio data to produce a single audio output stream
 * to the speakers or headphones. This interface does everything you can do with the PalmOS
 * "SndStream" API, except that it uses a "push" model for data delivery instead of a callback
 * "pull" model.
 *
 * If there are no more streams available then the TwDeviceOpen call will return the "sndErrOpen"
 * error code.
 *
 * To open the mixer device use the TW_VD_MIXER name and a mode of "w".
 */

/*
 * Name of the mixer device.
 */
#define TW_VD_MIXER "mixer"

/*
 * Properties of the mixer that can be set/get using the TwDevice setter/getter api's.
 */

/*
 * Set/get the mixer stream configuration: sample size, sample rate, # of channels, format. The
 * property buffer must be a TwVdMixerConfigProperty.
 */
#define TW_VD_MIXER_CONFIG              0x1
typedef struct TwVdMixerConfigProperty {
    UInt32 sampleRate;          // e.g. 44100
    UInt32 format;              // See SoundMgr.h SndFormatType
    UInt32 type;                // See SoundMgr.h SndSampleType
    UInt32 width;               // See SoundMgr.h SndStreamWidth
} TwVdMixerConfigProperty;

/*
 * Set/get the channel volume. Volume values are the same as SndStream volume values where
 * unity gain is 1024. In addition, the special values of sndSystemVolume, sndGameVolume and
 * sndAlarmVolume are supported. The property buffer must be an Int32.
 */
#define TW_VD_MIXER_VOLUME              0x2

/*
 * Set/get the pan position. The property buffer must be an Int32.
 */
#define TW_VD_MIXER_PAN                 0x3

/*
 * Get the mixer buffer size. This will return the number of bytes of buffering per stream.
 */
#define TW_VD_MIXER_BUFFER_BYTES        0x4

/*
 * Get the mixer buffer size, but in samples per buffer instead of bytes per buffer.
 */
#define TW_VD_MIXER_BUFFER_SAMPLES      0x5

#endif /* __TWVDMIXER_h__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
