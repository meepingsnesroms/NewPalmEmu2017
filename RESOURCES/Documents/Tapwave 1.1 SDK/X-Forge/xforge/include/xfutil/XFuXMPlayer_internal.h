/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XM player internal structures header file
 * 
 * $Id: XFuXMPlayer_internal.h,v 1.16 2003/10/10 11:34:51 toni Exp $
 * $Date: 2003/10/10 11:34:51 $
 * $Revision: 1.16 $
 */

#ifndef XFUXMPLAYER_INTERNAL_H_INCLUDED
#define XFUXMPLAYER_INTERNAL_H_INCLUDED


const UINT16 XMFORMAT_SIZEOF_ENVELOPE = 325;
const UINT16 XMFORMAT_SIZEOF_WAVEFORM = 64;
const UINT16 XMFORMAT_SIZEOF_KEYBOARD = 96;

const UINT16 XMFORMAT_SAMPLE_16BIT = 16;

//! Fixed point accuracy.
const INT32 FP_BITS = 12;
const INT32 FP_VALUE = (1 << FP_BITS);

const INT32 VOLUME_FP_BITS = 16;

const INT32 VOLUME_RAMP_WIDTH = 32;

enum XMPLAYER_LOOP_TYPE
{
    LOOP_FORWARD = 1,
    LOOP_PINGPONG = 2
};

enum XMPLAYER_ENVELOPE_TYPE
{
    ENVELOPE_ON = 1,
    ENVELOPE_SUSTAIN = 2,
    ENVELOPE_LOOP = 4
};

enum XMPLAYER_WAVEFORM
{
    WAVEFORM_SINEWAVE = 0,
    WAVEFORM_RAMPDOWN = 1,
    WAVEFORM_SQUAREWAVE = 2,
    WAVEFORM_NO_RETRIG = 4
};

enum XMPLAYER_XM_VIBRATO_WAVEFORM
{
    XM_VIBRATO_WAVEFORM_SINEWAVE = 0,
    XM_VIBRATO_WAVEFORM_SQUAREWAVE = 1,
    XM_VIBRATO_WAVEFORM_RAMPDOWN = 2,
    XM_VIBRATO_WAVEFORM_RAMPUP = 3
};


class XFuXMFormatAtom
{
public:
    UINT8 mNote;
    UINT8 mInstrumentNb;
    UINT8 mVolume;
    UINT8 mEffectType;
    UINT8 mEffectValue;
};


class XFuXMFormatHeader
{
public:
    UINT8 mIdString[17 + 1];    //!< ID text: 'Extended module: ' (+ extra byte for \0).
    UINT8 mModuleName[20 + 1];  //!< Module name (+ extra byte for \0).
    UINT8 mH1A;                 //!< $1A.
    UINT8 mTrackerName[20 + 1]; //!< Tracker name  (+ extra byte for \0).
    UINT16 mVersion;            //!< Version number, hi-UINT8 major, lo-UINT8 minor.
                              
    UINT32 mHeaderSize;         //!< Header size.
                              
    UINT16 mSongLength;         //!< Song length in pattern order table.
    UINT16 mRestartPosition;    //!< Song restart position.
    UINT16 mNbChannels;         //!< Number of channels.
    UINT16 mNbPatterns;         //!< Number of patterns.
    UINT16 mNbInstruments;      //!< Number of instruments.

    /*! Bit 0:
     * \li 0 = Amiga frequency table
     * \li 1 = Linear frequency table
     */
    UINT16 mFlags;
                              
    UINT16 mTempo;            //!< Default tempo (0..31).
    UINT16 mBpm;              //!< Default bpm (0..255).
                              
    UINT8 mOrderTable[256];   //!< Pattern order table.
};


class XFuXMFormatPatternHeader
{
public:
    UINT32 mHeaderLength;               //!< Pattern header length.
    UINT8 mPackingType;                 //!< Packing type, always 0.
    UINT16 mNbRows;                     //!< Number of rows in pattern (0..256).
    UINT16 mSize;                       //!< Packed patterndata size.
};


class XFuXMFormatInstrumentHeader
{
public:
    UINT32 mSize;                       //!< Instrument size.
    UINT8 mInstrumentName[22 + 1];      //!< Instrument name (+ extra byte for \0).
    UINT8 mType;                        //!< Instrument type, always 0.
    UINT16 mNbSamples;                  //!< Number of samples in instrument.
};


class XFuXMFormatInstrument
{
public:
    UINT32 mSampleHeaderSize;       //!< Sample header size.
                                    
    UINT8 mKeyboard[96];            //!< Sample number for all notes.
                                    
    UINT16 mVolumeEnvelope[24];     //!< Points for volume envelope.
    UINT16 mPanningEnvelope[24];    //!< Points for panning envelope.
    UINT8 mNbVolEnvPoints;          //!< Number of volume envelope points.
    UINT8 mNbPanEnvPoints;          //!< Number of panning envelope points.
    UINT8 mVolEnvSustain;           //!< Volume envelope sustain point.
    UINT8 mVolEnvLoopStart;         //!< Volume envelope loop start point.
    UINT8 mVolEnvLoopEnd;           //!< Volume envelope loop end point.
    UINT8 mPanEnvSustain;           //!< Panning envelope sustain point.
    UINT8 mPanEnvLoopStart;         //!< Panning envelope loop start point.
    UINT8 mPanEnvLoopEnd;           //!< Panning envelope loop end point.
    //! Volume envelope type.
    /*! \li Bit 0: On
     *  \li Bit 1: Sustain
     *  \li Bit 2: Loop
     */
    UINT8 mVolEnvType;
    //! Panning envelope type.
    /*! \li Bit 0: On
     *  \li Bit 1: Sustain
     *  \li Bit 2: Loop
     */
    UINT8 mPanEnvType;
                                    
    UINT8 mVibratoType;             //!< Vibrato type.
    UINT8 mVibratoSweep;            //!< Vibrato sweep.
    UINT8 mVibratoDepth;            //!< Vibrato depth.
    UINT8 mVibratoRate;             //!< Vibrato rate.
                                    
    UINT16 mVolumeFadeout;          //!< Volume fadeout speed.
                                    
    UINT16 mReserved;               //!< Reserved.
};


class XFuXMFormatSample
{
public:
    UINT32 mSampleLength;       //!< Sample length.
    UINT32 mLoopStart;          //!< Sample loop start.
    UINT32 mLoopLength;         //!< Sample loop length.
    UINT8 mVolume;              //!< Volume.
    INT8 mFinetune;             //!< Finetune (signed byte -128..+127).
    //! Sample type.
    /*! Bit 0-1:
     * \li 0 = No loop
     * \li 1 = Forward loop
     * \li 2 = Ping-pong loop
     * \par Bit 4: 16-bit sample data
     */
    UINT8 mType;                
                                
    UINT8 mPan;                 //!< Panning (0..255).
    INT8 mRelativeNote;         //!< Relative note number (signed byte).
                                
    UINT8 mReserved;            //!< Reserved.
                                
    UINT8 mSampleName[22 + 1];  //!< Sample name (+ extra byte for \0).
};


class XFuXMSong
{
public:
    UINT8 *mOrderTable;                 //!< Pattern order table, MAX_ORDERS.
    UINT16 mSongLength;                 //!< Song length in pattern order table.
    UINT16 mRestartPosition;            //!< Song restart position.

    UINT16 mNbPatterns;                 //!< Number of patterns.
    UINT16 mNbChannels;                 //!< Number of channels.
    UINT16 mNbInstruments;              //!< Number of instruments.

    UINT16 mTempo;                      //!< Tempo (0..31), tick count.
    UINT16 mBpm;                        //!< Bpm (0..255), tick speed.

    INT8 mGlobalVolume;                 //!< Global volume.
};


class XFuXMSample
{
public:
    UINT8 mVolume;                      //!< Volume (0..63).
    UINT8 mPan;                         //!< Panning (-128..+127).
    INT8 mFinetune;                     //!< Finetune (signed byte -128..+127).
    INT8 mRelativeNote;                 //!< Relative note number (signed byte).

    void *mOffset;                      //!< Sample address in memory.
    UINT32 mSize;                       //!< Sample size.

    UINT8 mLoopForward;                 //!< Forward loop.
    UINT8 mLoopPingpong;                //!< Pingpong loop.
    UINT32 mLoopStart;                  //!< Sample loop start.
    UINT32 mLoopEnd;                    //!< Sample loop end.

    UINT8 m16Bit;                       //!< 16-bit sample flag.
};


class XFuXMInstrument
{
public:
    UINT16 mNbSamples;                  //!< Number of samples in instrument.
    XFuXMSample *mSamples;              //!< MAX_SAMPLES.

    UINT8 mKeyboard[XMFORMAT_SIZEOF_KEYBOARD];   //!< Sample number for all notes.

    REAL mVolumeEnvelope[XMFORMAT_SIZEOF_ENVELOPE];
    UINT16 mVolEnvEnd;                  //!< Volume envelope end point.
    UINT8 mVolEnvType;                  //!< Volume envelope flag.
    UINT16 mVolEnvLoopStart;            //!< Volume envelope loop start.
    UINT16 mVolEnvLoopEnd;              //!< Volume envelope loop end.
    UINT16 mVolEnvSustain;              //!< Volume envelope sustain point.

    REAL mVolumeFadeout;                //!< Volume fadeout speed.

    UINT8 mPanningEnvelope[XMFORMAT_SIZEOF_ENVELOPE];
    UINT16 mPanEnvEnd;                  //!< Panning envelope end point.
    UINT8 mPanEnvType;                  //!< Panning envelope flag.
    UINT16 mPanEnvLoopStart;            //!< Panning envelope loop start.
    UINT16 mPanEnvLoopEnd;              //!< Panning envelope loop end.
    UINT16 mPanEnvSustain;              //!< Panning envelope sustain point.

    UINT8 mIsVibrato;                   //!< Vibrato flag.
    UINT8 mVibratoType;                 //!< Vibrato type.
    UINT8 mVibratoSweep;                //!< Vibrato sweep.
    UINT8 mVibratoDepth;                //!< Vibrato depth.
    UINT8 mVibratoRate;                 //!< Vibrate rate.
};


class XFuXMPattern
{
public:
    UINT8 *mData;               //!< Pattern data.
    UINT32 *mRows;              //!< Pointer to row in pattern, MAX_PATTERN_ROWS.
};


class XFuXMChannel
{
public:
    XFuXMFormatAtom mTa;

    INT mIsValid;                       //! Data validity flag.
    INT mInitSample;                    //! Sample initialization flag.
    
    INT32 mPointer;                     //! Pointer to current position in sample data.

    XFuXMInstrument mCurrentInstrument;  //!< Current instrument.
    XFuXMSample mCurrentSample;          //!< Current sample.

    void * mOffset;                     //!< Sample address in memory.
    INT32 mLength;                      //!< Sample size.
    INT16 mInstrumentNb;                //!< Instrument number.
    UINT32 mSpeed;                      //!< Speed.
    //! Sample loop type.
    /*! \li 0 = Off
     *  \li 1 = Forward
     *  \li 2 = Pingpong
     */
    UINT8 mLoop;
    INT32 mLoopStart;                   //!< Sample loop start.
    INT32 mLoopEnd;                     //!< Sample loop end.

    UINT8 mIsSample;                    //!< Sample availability flag.

    INT8 mNote;                         //!< Current note.
    INT8 mFinetune;                     //!< Current finetune.

    INT8 mDirection;                    //!< Sample direction: +1 = Forwards, -1 = Backwards.

    UINT8 mVolEnvType;                  //!< Volume envelope type.
    UINT16 mVolEnvPointer;              //!< Volume envelope pointer.
    UINT8 mVolEnvSpeed;                 //!< Volume envelope speed.
    UINT16 mVolEnvLoopStart;            //!< Volume envelope loop start.
    UINT16 mVolEnvLoopEnd;              //!< Volume envelope loop end.
    UINT16 mVolEnvSustain;              //!< Volume envelope sustain point.
    REAL mVolEnvValue;                  //!< Volume envelope value.
    REAL mVolumeFadeout;                //!< Volume envelope fadeout.
    REAL mVolumeFadeoutValue;           //!< Volume envelope fadeout value.

    INT8 mVolume;                       //!< Volume.
    INT8 mBaseVolume;                   //!< Base volume.
    REAL mFinalVolume;                  //!< Final volume, used for ramping.
    REAL mFinalOldVolume;               //!< Final old volume, used for ramping.
    REAL mFinalVolumeSpeed;             //!< Final volume ramp speed.

    UINT8 mPanEnvType;                  //!< Panning envelope type.
    UINT16 mPanEnvPointer;              //!< Panning envelope pointer.
    UINT8 mPanEnvSpeed;                 //!< Panning envelope speed.
    UINT16 mPanEnvLoopStart;            //!< Panning envelope loop start.
    UINT16 mPanEnvLoopEnd;              //!< Panning envelope loop end.
    UINT16 mPanEnvSustain;              //!< Panning envelope sustain point.
    UINT8 mPanEnvValue;                 //!< Panning envelope value.
    UINT8 mPan;                          //!< Pan.
    INT16 mFinalPan;                    //!< Final pan.

    UINT8 mSustainReleased;             //!< Sustain release flag.

    UINT8 mVolumeColumn;                //!< Volume column effect.

    UINT8 mEffectType;                  //!< Effect type.
    UINT8 mEffectValue;                 //!< Effect value.

    UINT8 mPortamentoUpV;               //!< Portamento up value.
    UINT8 mPortamentoDownV;             //!< Portamento down value.
    UINT8 mTonePortamentoV;             //!< Tone portamento value.
    UINT8 mVolumeSlideV;                //!< Volume slide value.
    UINT8 mFinePortamentoUpV;           //!< Fine portamento up value.
    UINT8 mFinePortamentoDownV;         //!< Fine portamento down value.
    UINT8 mFineVolumeSlideUpV;          //!< Fine volume slide up value.
    UINT8 mFineVolumeSlideDownV;        //!< Fine volume slide down value.
    UINT8 mGlobalVolumeSlideV;          //!< Global volume slide value.
    UINT8 mMultiRetrigVolumeV;          //!< Multi retrig note volume change.
    UINT8 mMultiRetrigRateV;            //!< Multi retríg note rate.
    UINT8 mTremorV;                     //!< Tremor value.
    UINT8 mExtraFinePortamentoUpV;      //!< Extra fine portamento up value.
    UINT8 mExtraFinePortamentoDownV;    //!< Extra fine portamento down value.
    UINT8 mPanningSlideV;               //!< Panning slide value.

    UINT32 mMultiRetrigTicker;          //!< Multi retrig ticker.
    UINT32 mTremorTicker;               //!< Tremor ticker.

    UINT32 mPeriod;                     //!< Period.
    UINT32 mOldPeriod;                  //!< Old line period.
    UINT32 mDestPeriod;                 //!< Current line period.
    UINT32 mBasePeriod;                 //!< Base period.

    UINT8 mIsVibrato;                   //!< Vibrato flag.
    UINT8 mVibratoRate;                 //!< Vibrato rate.
    UINT8 mVibratoDepth;                //!< Vibrato depth.
    UINT8 mVibratoPointer;              //!< Vibrato pointer.
    UINT8 mVibratoWaveform;             //!< Vibrato waveform.

    UINT8 mTremoloRate;                 //!< Tremolo rate.
    UINT8 mTremoloDepth;                //!< Tremolo depth.
    UINT8 mTremoloPointer;              //!< Tremolo pointer.
    UINT8 mTremoloWaveform;             //!< Tremolo waveform.
};


#endif // !XFUXMPLAYER_INTERNAL_H_INCLUDED

