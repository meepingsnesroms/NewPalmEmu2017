/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XM player header file
 * 
 * $Id: XFuXMPlayer.h,v 1.20 2003/10/06 11:26:47 toni Exp $
 * $Date: 2003/10/06 11:26:47 $
 * $Revision: 1.20 $
 */

#ifndef XFUXMPLAYER_H_INCLUDED
#define XFUXMPLAYER_H_INCLUDED

#include <xfcore/XFcAudioStream.h>
#include <xfutil/XFuXMPlayer_internal.h>
#include <xfutil/XFuXMPlayerEventHandler.h>


template<class T> class XFcLinkedList;


class XFuXMPlayerEventHandlerSlot
{
public:
    XFuXMPlayerEvent mEvent;
    XFuXMPlayerEventHandler *mHandler;

    INT operator != (const XFuXMPlayerEventHandlerSlot &aRef) const
    {
        return !(mHandler == aRef.mHandler);
    }

    INT operator == (const XFuXMPlayerEventHandlerSlot &aRef) const
    {
        return (mHandler == aRef.mHandler);
    }
};


//! Plays XM music files.
class XFuXMPlayer : public XFcAudioStream
{
protected:
    FLOAT32 mSamplingRate;              //!< Sampling rate.
    UINT32 mFlags;                      //!< Format flags.
    INT32 mTgtXor;                      //!< Signed/unsigned xor value.

    XFuXMFormatHeader mXMHeader;        //!< XM file header.
    XFuXMSong mSong;                    //!< Module.

    XFuXMFormatPatternHeader *mXMPatternHeaders;    //!< XM pattern headers.
    XFuXMPattern *mPatternData;                     //!< Pattern data.

    XFuXMInstrument *mInstruments;      //!< Instruments.

    XFuXMChannel *mChannels;            //!< Channels.

    INT16 mSineWaveTable[XMFORMAT_SIZEOF_WAVEFORM];
    INT16 mSquareWaveTable[XMFORMAT_SIZEOF_WAVEFORM];
    INT16 mRampUpTable[XMFORMAT_SIZEOF_WAVEFORM];
    INT16 mRampDownTable[XMFORMAT_SIZEOF_WAVEFORM];

    UINT32 mPpoint;                     //!< Pattern data index.
    INT16 mCurrentOrder;                //!< Order index.
    INT16 mPatternNb;                   //!< Pattern index.
    INT16 mCurrentRow;                  //!< Row index.
    INT32 mSamplesPerTick;              //!< Amount of samples in one tick.
    INT32 mSamplePointer;               //!< Counter.
    FLOAT32 mTickRate;                  //!< Tick speed in Hz.
    INT32 mRamp;

    UINT8 mPatternDelayCounter;         //!< Pattern delay counter.
    UINT8 mPatternDelayCounterTemp;     //!< Temporary pattern delay counter.
    UINT8 mPatternDelaySkip;            //!< Flag for skipping pattern delay commands.

    UINT8 mIsRead;                      //!< Flag indicating whether pattern data should be read.
    UINT8 mJumpFlag;                    //!< Flag for pattern jump and pattern break commands.

    UINT8 mCurrentTick;                 //!< Tick index (0..tempo-1).
    UINT32 mTotalTicks;                 //!< Test tick counter.

    REAL mVolumeRampDivOpt;             //!< For volume ramping.

    //! List of event handlers interested in events of this player.
    XFcLinkedList<XFuXMPlayerEventHandlerSlot> *mEventHandlers;

    
    INT loadXM(const CHAR *aFilename, XFcFile *aTextout);

    
    XFuXMFormatAtom getAtom();
    
    void dumpSongParameters(XFcFile *aTextout);


    UINT32 getPeriod(INT8 aNote, INT8 aFinetune);
    
    UINT32 getSpeed(UINT32 aPeriod, FLOAT32 aSamplingRate);
    
    void initChannel(XFuXMChannel &aCh);

    void initSound(XFuXMChannel &aCh);


    //! Notify handlers of events.
    void notifyHandlers(XFuXMChannel &aCh);

    void debugPrint(XFcFile *aTextout, char *aFmt, ...);


    XFuXMPlayer(FLOAT32 aSamplingRate, UINT32 aFlags);
 
public:
    //! Initializes the playhead to the beginning of a certain pattern.
    void initSong(INT16 aStartOrder);

    //! Returns the player's internal tick.
    INT32 getTick();

    //! Returns the current order being played.
    INT16 getCurrentOrder();


    //! Adds a new event handler to this player.
    void addHandler(XFuXMPlayerEvent aEvent, XFuXMPlayerEventHandler *aHandler);

    //! Removes a specific event handler from this player.
    INT removeHandler(XFuXMPlayerEventHandler *aHandler);

    //! Removes all event handlers from this player.
    void removeHandlers();


    virtual void stop();

    virtual UINT32 stream(void *aBuffer, INT32 aTargetSamples, INT32 aOffset, 
                          INT32 aSamples);

    //! Creates an XM-Player.
    /*! 
     * Creates an XM-Player with the given module name, sampling rate and audio format.
     */
    static XFuXMPlayer * create(const CHAR *aFilename, FLOAT32 aSamplingRate, 
                                UINT32 aFlags);

    virtual ~XFuXMPlayer();
};


#endif // !XFUXMPLAYER_H_INCLUDED

