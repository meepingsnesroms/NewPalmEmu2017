/* -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 */
#ifndef __TWMIDI_H__
#define __TWMIDI_H__

#include "TwError.h"
#include "SoundMgr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* typedef's for opaque types */
typedef struct TwSmfType* TwSmfHandle;
typedef struct TwMidiType* TwMidiHandle;

/* typedef for the callback function in TwSmfPlay's callback type */
typedef void (*TwSmfPlayCallbackType)(UInt32 dwUserData);

/* Error codes */
#define twMidiErrorUnavailable          (0 + twMidiErrorBase)
#define twMidiErrorNullPointer          (1 + twMidiErrorBase)
#define twMidiErrorInvalidHandle        (2 + twMidiErrorBase)
#define twMidiErrorAlreadyPlaying       (3 + twMidiErrorBase)
#define twMidiErrorDriverError          (4 + twMidiErrorBase)
#define twMidiErrorInvalidFormat        (5 + twMidiErrorBase)
#define twMidiErrorBadParam             (6 + twMidiErrorBase)
#define twMidiErrorInvalidVolume        (7 + twMidiErrorBase)
#define twMidiErrorAllocFailed          (8 + twMidiErrorBase)

/* Limit names */
#define twMidiLimitMaxSmfHandles        0
#define twMidiLimitMaxMidiHandles       1

/* Control changes */
#define twMidiControlModulation         0
#define twMidiControlChannelVolume      1
#define twMidiControlPanPot             2
#define twMidiControlAllOff             3

/*
 * Maximum volume for midi/smf. Note that this value is different than sndMaxAmp and from the
 * unity gain value (1024) in the sound manager stream api's. The reason is that midi volumes
 * (e.g. key velocities) have the range zero to 127 and it was felt that the midi api's should
 * be self consistent. To make things easier, two conversion macros are provided.
 */
#define twMidiMaxVolume                 127

/* Convert a sound manager volume (0-sndMaxAmp) into a midi volume (0-twMidiMaxVolume) */
#define TwMidiCvtSndVolume2MidiVolume(_sndvol) ((_sndvol) * twMidiMaxVolume / sndMaxAmp)

/* Convert a midi volume (0-twMidiMaxVolume) into a sound manager volume (0-sndMaxAmp) */
#define TwMidiCvtMidiVolume2SndVolume(_sndvol) ((_sndvol) * sndMaxAmp / twMidiMaxVolume)

/* SMF API's */

/*
 * Query an implementation limit for the midi and smf api's.
 */
Err TwMidiGetLimits(Int32 aLimit,
                    Int32* aLimitResult)
    TAL_TRAP(trapTwMidiGetLimits);

/*
 * Change the midi "master volume". The midi master volume applies to all midi sounds -- smf
 * streams and individual notes. The value is in the range of 0 to twMidiMaxVolume
 * (inclusive). See the comment above that describes twMidiMaxVolume.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiSetMasterVolume(Int32 aVolume)
    TAL_TRAP(trapTwMidiSetMasterVolume);

/*
 * Get the midi "master volume". The value returned will be in the range of 0 to
 * twMidiMaxVolume (inclusive).
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiGetMasterVolume(Int32* aVolumeResult)
    TAL_TRAP(trapTwMidiGetMasterVolume);

/*
 * Play an SMF encoded block of data. This is a handy helper function to open, play and close an SMF
 * encoded block of data. If aAsync is non-zero then the playback is done without the caller waiting
 * for its completion.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidFormat
 *      twMidiErrorAllocFailed
 */
Err TwMidiPlaySmf(UInt8* aSMFData,
                  UInt32* aDurationMillisecResult,
                  Boolean aAsync)
    TAL_TRAP(trapTwMidiPlaySmf);

/************************************************************************/

/*
 * Create a handle to an SMF encoded block of data returning (optionally) the duration in
 * milliseconds of the smf data. As with PalmOS, only SMF format #0 is supported. Up to 16
 * channels may be used, however, allowing for chording of the notes.
 *
 * These midi api's are not supported on the simulator (twMidiErrorUnavailable will be returned).
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidFormat
 *      twMidiErrorAllocFailed
 */
Err TwSmfOpen(TwSmfHandle* aHandleResult,
              UInt8* aSMFData,
              UInt32* aDurationMillisecResult)
    TAL_TRAP(trapTwSmfOpen);

/*
 * Close a handle to an smf stream. If the stream was playing it is stopped first.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwSmfClose(TwSmfHandle aSmfHandle)
    TAL_TRAP(trapTwSmfClose);

/*
 * Start an smf stream playing. If a callback is provided it will be called when the stream
 * finishes playing. It is safe to call TwSmfPlay again from the callback to implement
 * looping. It is not safe to make calls that are not safe to call from interrupt routines,
 * which is just about everything.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwSmfPlay(TwSmfHandle aSmfHandle,
              SndSmfOptionsType* aOptions,
              SndSmfChanRangeType* aRangeInfo,
              SndCallbackInfoType* aCallback)
    TAL_TRAP(trapTwSmfPlay);

/*
 * Test an smf stream and see if its playing.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwSmfIsPlaying(TwSmfHandle aSmfHandle,
                   Boolean* aIsPlayingResult)
    TAL_TRAP(trapTwSmfIsPlaying);

/*
 * Stop an smf stream that is playing.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwSmfStop(TwSmfHandle aSmfHandle)
    TAL_TRAP(trapTwSmfStop);

/************************************************************************/

/* MIDI API's */

/*
 * Open a handle to the low level midi interface.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorAllocFailed
 */
Err TwMidiOpen(TwMidiHandle* aHandleResult)
    TAL_TRAP(trapTwMidiOpen);

/*
 * Close a previously opened handle.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiClose(TwMidiHandle aMidiHandle)
    TAL_TRAP(trapTwMidiClose);

/*
 * Turn one of 16 possible midi note channels on.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiNoteOn(TwMidiHandle aMidiHandle,
                 UInt8 aChannel,
                 UInt8 aKey,
                 UInt8 aVelocity)
    TAL_TRAP(trapTwMidiNoteOn);

/*
 * Turn one of 16 possible midi note channels off.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiNoteOff(TwMidiHandle aMidiHandle,
                  UInt8 aChannel,
                  UInt8 aKey,
                  UInt8 aVelocity)
    TAL_TRAP(trapTwMidiNoteOff);

/*
 * Change the program or voice of the given midi note channel.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiProgramChange(TwMidiHandle aMidiHandle,
                        UInt8 aChannel,
                        UInt8 aProgramChange)
    TAL_TRAP(trapTwMidiProgramChange);

/*
 * Change a control setting for the given midi note channel.
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiControlChange(TwMidiHandle aMidiHandle,
                        UInt8 aChannel,
                        Int32 aControlChange,
                        Int32 aValue)
    TAL_TRAP(trapTwMidiControlChange);

/*
 * ???
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiPitchBend(TwMidiHandle aMidiHandle,
                    UInt8 aChannel,
                    Int32 aBend)
    TAL_TRAP(trapTwMidiPitchBend);

/*
 * ??? 0x7e, 0x7f are supported; 
 *
 * Errors:
 *      twMidiErrorUnavailable
 *      twMidiErrorNullPointer
 *      twMidiErrorInvalidHandle
 */
Err TwMidiSysEx(TwMidiHandle aMidiHandle,
                UInt8 aChannel,
                UInt8* aData,
                UInt16 aSize)
    TAL_TRAP(trapTwMidiSysEx);

#ifdef __cplusplus
}
#endif

#endif /* __TWMIDI_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
