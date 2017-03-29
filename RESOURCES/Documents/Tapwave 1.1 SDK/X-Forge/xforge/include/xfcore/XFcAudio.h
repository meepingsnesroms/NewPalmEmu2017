/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio library.
 * 
 * $Id: XFcAudio.h,v 1.13 2003/10/06 11:26:47 toni Exp $
 * $Date: 2003/10/06 11:26:47 $
 * $Revision: 1.13 $
 */

#ifndef XFC_CORE_XFCAUDIO_H_INCLUDED
#define XFC_CORE_XFCAUDIO_H_INCLUDED

#include <xfcore/XFcAudioFormat.h>


class XFcAudioProducer;

//! Static audio interface.
class XFCDLLEXPORT XFcAudio
{

public:

    //! Locks an audio producer.
    /*!
     * While an audio producer is locked, the audio system can not play it.
     *
     * \param aProducer Audio producer to be locked.
     *
     * \return Pointer to sample data.
     */
    XFCIMPORT static void * lock(XFcAudioProducer *aProducer);

    //! Unlocks an audio producer.
    /*!
     * If called without a prior lock(), method does nothing.
     *
     * \param aProducer Audio producer to be unlocked.
     */
    XFCIMPORT static void unlock(XFcAudioProducer *aProducer);


    //! Starts to play an audio producer.
    /*!
     * An unique id is returned so that individual playing instances can be referenced.
     *
     * \param aProducer Audio producer to be played.
     *
     * \return An unique id for the playing instance of the producer.
     */
    XFCIMPORT static UINT32 play(XFcAudioProducer *aProducer);
    
    //! Starts to play an audio producer with given sampling rate.
    /*!
     * An unique id is returned so that individual playing instances can be referenced.
     *
     * \param aProducer Audio producer to be played.
     * \param aSamplingRate Sample rate, from 0 to any value.
     *
     * \return An unique id for the playing instance of the producer.
     */
    XFCIMPORT static UINT32 play(XFcAudioProducer *aProducer,
                                 FLOAT32 aSamplingRate);
    
    //! Starts to play an audio producer with given sampling rate and volume.
    /*!
     * An unique id is returned so that individual playing instances can be referenced.
     *
     * \param aProducer Audio producer to be played.
     * \param aSamplingRate Sample rate, from 0 to any value.
     * \param aVolume Volume, from 0 to any value. 1 is the original volume of the sample data.
     *
     * \return An unique id for the playing instance of the producer.
     */
    XFCIMPORT static UINT32 play(XFcAudioProducer *aProducer,
                                 FLOAT32 aSamplingRate, REAL aVolume);
    
    //! Starts to play an audio producer with given sampling rate, volume and panning.
    /*!
     * An unique id is returned so that individual playing instances can be referenced.
     *
     * \param aProducer Audio producer to be played.
     * \param aSamplingRate Sample rate, from 0 to any value.
     * \param aVolume Volume, from 0 to any value. 1 is the original volume of the sample data.
     * \param aPanning Panning, from 0 to 1. 0 is left, 1 is right, 0.5 is center.
     *
     * \return An unique id for the playing instance of the producer.
     */
    XFCIMPORT static UINT32 play(XFcAudioProducer *aProducer,
                                 FLOAT32 aSamplingRate, REAL aVolume, REAL aPanning);
    
    //! Starts to play an audio producer with given sampling rate, volume, panning and priority.
    /*!
     * An unique id is returned so that individual playing instances can be referenced.
     *
     * \param aProducer Audio producer to be played.
     * \param aSamplingRate Sample rate, from 0 to any value.
     * \param aVolume Volume, from 0 to any value. 1 is the original volume of the sample data.
     * \param aPanning Panning, from 0 to 1. 0 is left, 1 is right, 0.5 is center.
     * \param aPriority Priority, from 0 to 65535. Smaller number is higher priority.
     *
     * \return An unique id for the playing instance of the producer.
     */
    XFCIMPORT static UINT32 play(XFcAudioProducer *aProducer,
                                 FLOAT32 aSamplingRate, REAL aVolume, REAL aPanning,
                                 UINT16 aPriority);

    
    //! Stops an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT stop(UINT32 aUid);
    
    //! Stops each instance of a certain audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT stopEach(XFcAudioProducer *aProducer);
    
    //! Stops all playing audio producer instances.
    XFCIMPORT static void stopAll();

    //! Pauses an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT pause(UINT32 aUid);
    
    //! Pauses each instance of a certain audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT pauseEach(XFcAudioProducer *aProducer);
    
    //! Pauses all audio producers.
    XFCIMPORT static void pauseAll();

    //! Resumes an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT resume(UINT32 aUid);
    
    //! Resumes each instance of a certain audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return 1 is operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT resumeEach(XFcAudioProducer *aProducer);
    
    //! Resumes all playing audio producer instances.
    XFCIMPORT static void resumeAll();


    //! Returns the number of samples in an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return Number of samples or 0 if audio producer is a stream.
     */
    XFCIMPORT static INT32 getSamples(XFcAudioProducer *aProducer);

    //! Sets the number of samples in an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aSamples Number of samples.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setSamples(XFcAudioProducer *aProducer,
                                     INT32 aSamples);


    //! Returns looping information of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return 1 if looping is enabled, 0 otherwise.
     */
    XFCIMPORT static INT getLooping(UINT32 aUid);

    //! Returns looping information of an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return 1 if looping is enabled, 0 otherwise.
     */
    XFCIMPORT static INT getLooping(XFcAudioProducer *aProducer);

    //! Enables/disables looping of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aLooping 0 for looping disabled, otherwise looping enabled.
     *
     * \return 1 if operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT setLooping(UINT32 aUid, INT aLooping);
    
    //! Enables/disables looping of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aLooping 0 for looping disabled, otherwise looping enabled.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setLooping(XFcAudioProducer *aProducer, INT aLooping);

    //! Returns loop offsets of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aStartOffset Start offset is saved to this variable reference.
     * \param aEndOffset End offset is saved to this variable reference.
     */
    XFCIMPORT static void getLoopOffsets(UINT32 aUid, INT32 &aStartOffset, 
                                         INT32 &aEndOffset);

    //! Returns loop offsets of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aStartOffset Start offset is saved to this variable reference.
     * \param aEndOffset End offset is saved to this variable reference.
     */
    XFCIMPORT static void getLoopOffsets(XFcAudioProducer *aProducer, 
                                         INT32 &aStartOffset, INT32 &aEndOffset);

    //! Sets start and end loop offsets to an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aStartOffset Start offset.
     * \param aEndOffset End offset.
     *
     * \return 1 if operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT setLoopOffsets(UINT32 aUid, INT32 aStartOffset, INT32 aEndOffset);

    //! Sets start and end loop offsets to an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aStartOffset Start offset.
     * \param aEndOffset End offset.
     *
     * \return 1 if operation succeeded, 0 otherwise.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static INT setLoopOffsets(XFcAudioProducer *aProducer, 
                                        INT32 aStartOffset, INT32 aEndOffset);


    //! Returns the sampling rate of an audio producer instance with given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Sample rate.
     */
    XFCIMPORT static FLOAT32 getSamplingRate(UINT32 aUid);
    
    //! Returns the sampling rate of an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return Sample rate.
     */
    XFCIMPORT static FLOAT32 getSamplingRate(XFcAudioProducer *aProducer);

    
    //! Sets the sampling rate of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aSamplingRate Sample rate.
     *
     * \return 1 if operation succeeded, 0 otherwise.
     */
    XFCIMPORT static INT setSamplingRate(UINT32 aUid, FLOAT32 aSamplingRate);
    
    //! Sets the sampling rate of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aSamplingRate Sample rate.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setSamplingRate(XFcAudioProducer *aProducer,
                                        FLOAT32 aSamplingRate);

    
    //! Returns the volume of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Volume.
     */
    XFCIMPORT static REAL getVolume(UINT32 aUid);
    
    //! Returns the volume of an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return Volume.
     */
    XFCIMPORT static REAL getVolume(XFcAudioProducer *aProducer);
    
    //! Sets the volume of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aVolume Volume, from 0 to any value. 1 is the original volume of the sample data.
     *
     * \return 1 if operation succeeds, 0 otherwise.
     */
    XFCIMPORT static INT setVolume(UINT32 aUid, REAL aVolume);
    
    //! Sets the volume of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aVolume Volume, from 0 to any value. 1 is the original volume of the sample data.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setVolume(XFcAudioProducer *aProducer, REAL aVolume);
    
    //! Returns the master volume.
    /*!
     * \return Master volume.
     *
     * \note Not implemented yet.
     */
    XFCIMPORT static REAL getMasterVolume();
    
    //! Sets the master volume.
    /*!
     * \param aVolume Master volume.
     *
     * \note Not implemented yet.    
     */
    XFCIMPORT static void setMasterVolume(REAL aVolume);


    //! Returns the panning of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Panning.
     */
    XFCIMPORT static REAL getPanning(UINT32 aUid);
    
    //! Returns the panning of an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return Panning.
     */
    XFCIMPORT static REAL getPanning(XFcAudioProducer *aProducer);
    
    //! Sets the panning of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aPanning Panning, from 0 to 1. 0 is left, 1 is right, 0.5 is center.
     *
     * \return 1 if operation succeeds, 0 otherwise.
     */
    XFCIMPORT static INT setPanning(UINT32 aUid, REAL aPanning);
    
    //! Sets the panning of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aPanning Panning, from 0 to 1. 0 is left, 1 is right, 0.5 is center.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setPanning(XFcAudioProducer *aProducer, REAL aPanning);
    

    //! Returns the priority of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Priority.
     */
    XFCIMPORT static UINT16 getPriority(UINT32 aUid);
    
    //! Returns the priority of an audio producer.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Priority.
     */
    XFCIMPORT static UINT16 getPriority(XFcAudioProducer *aProducer);
    
    //! Sets the priority of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     * \param aPriority Priority, from 0 to 65535. Smaller number is higher priority.
     *
     * \return 1 if operation succeeds, 0 otherwise.
     */
    XFCIMPORT static INT setPriority(UINT32 aUid, UINT16 aPriority);
    
    //! Sets the priority of an audio producer.
    /*!
     * \param aProducer Audio producer.
     * \param aPriority Priority, from 0 to 65535. Smaller number is higher priority.
     *
     * \note Does not affect any playing instances.
     */
    XFCIMPORT static void setPriority(XFcAudioProducer *aProducer,
                                      UINT16 aPriority);

    
    //! Returns the number of channels.
    /*!
     * \return Number of channels.
     */
    XFCIMPORT static INT32 getChannelCount();
    
    //! Sets the number of channels.
    /*!
     * \param aChannelCount Number of channels.
     *
     * \return 1 if operation succeeds, 0 otherwise.
     */
    XFCIMPORT static INT setChannelCount(INT32 aChannelCount);
    

    //! Returns the interpolation method.
    /*!
     * \return Interpolation method.
     *
     * \sa XFCAUDIOINTERPOLATION
     */
    XFCIMPORT static UINT32 getInterpolation();

    //! Sets the interpolation method.
    /*!
     * \param aMethod Interpolation method, one of XFCAUDIOINTERPOLATION.
     *
     * \return 1 if operation succeeds, 0 otherwise.
     *
     * \sa XFCAUDIOINTERPOLATION
     */
    XFCIMPORT static INT setInterpolation(UINT32 aMethod);


    //! Returns information whether an audio producer instance with the given id is playing.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return 1 if instance is playing, 0 otherwise.
     */
    XFCIMPORT static INT isPlaying(UINT32 aUid);
    
    //! Returns the playhead of an audio producer instance with the given id.
    /*!
     * \param aUid Id of an audio producer instance.
     *
     * \return Playhead.
     */
    XFCIMPORT static INT32 getPlayhead(UINT32 aUid);

    
    //! Returns the audio format of an audio producer.
    /*!
     * \param aProducer Audio producer.
     *
     * \return Audio format.
     */
    XFCIMPORT static XFcAudioFormat getFormat(XFcAudioProducer *aProducer);

    
    //! Returns the internal audio format of the audio system.
    /*!
     * \return Internal audio format.
     */
    XFCIMPORT static XFcAudioFormat getAudioFormat();
    
    //! Returns the hardware audio format.
    /*!
     * \return Hardware audio format.
     */
    XFCIMPORT static XFcAudioFormat getHardwareAudioFormat();

    //! Sets the hardware and internal audio formats.
    /*!
     * Adjusts the hardware and internal audio formats by the given
     * audio format, channel count and interpolation method.
     *
     * \note Calling this function initializes the audio system.
     *
     * \param aFormat Requested audio format. Use NULL for default
     * \param aChannelCount Number of channels.
     * \param aInterpolation Interpolation method, one of XFCAUDIOINTERPOLATION.
     *
     * \return Closest possible hardware format which could be achieved.
     *
     * \sa XFCAUDIOINTERPOLATION
     */
    XFCIMPORT static XFcAudioFormat setAudioFormat(XFcAudioFormat *aFormat,
                                                   INT32 aChannelCount,
                                                   UINT32 aInterpolation);
    
    //! Gets the recommended audio format for hardware and internal audio.
    /*!
     * Returns the audio format recommended for the currently running platform.
     * The format may vary from platform to platform. The recommended values
     * are what have been found to work on most cases with reasonably small
     * audio latency.
     *
     * \return Recommended audio format.
     */
    XFCIMPORT static XFcAudioFormat getRecommendedAudioFormat();

    //! Re-initializes the hardware audio processing.
    XFCIMPORT static void openAudio();

    //! Shuts down audio processing.
    /*!
     * \note To play audio again, you must call either openAudio() or setAudioFormat() again.
     */
    XFCIMPORT static void closeAudio();
    
    //! Gets a copy of primary audio data for audio feedback effect purposes.
    /*!
     * \note No guarantees about the resulting audio data is made.
     */
    XFCIMPORT static void getPrimaryData(XFcAudioBuffer *aTarget, INT32 aOffset, INT32 aRequestSamples);

};


#endif // !XFC_CORE_XFCAUDIO_H_INCLUDED

