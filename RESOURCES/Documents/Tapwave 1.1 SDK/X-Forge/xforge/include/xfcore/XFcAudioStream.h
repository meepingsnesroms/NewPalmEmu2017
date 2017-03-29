/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio stream base class.
 * 
 * $Id: XFcAudioStream.h,v 1.13 2003/10/06 11:26:47 toni Exp $
 * $Date: 2003/10/06 11:26:47 $
 * $Revision: 1.13 $
 */

#ifndef XFC_CORE_XFCAUDIOSTREAM_H_INCLUDED
#define XFC_CORE_XFCAUDIOSTREAM_H_INCLUDED

#include <xfcore/XFcAudioProducer.h>


//! Audio stream base class.
class XFCDLLEXPORT XFcAudioStream : public XFcAudioProducer
{

public:
    //! Called when a play() call is made to XFcAudio with this producer (callback).
    XFCIMPORT virtual void play();
    
    //! Called when a stop() call is made to XFcAudio with this producer (callback).
    XFCIMPORT virtual void stop();
    
    //! Called when a pause() call is made to XFcAudio with this producer (callback).
    XFCIMPORT virtual void pause();
    
    //! Called when a resume() call is made to XFcAudio with this producer (callback).
    XFCIMPORT virtual void resume();


    //! Called when new data is required by the system (callback).
    /*! \param aBuffer Pointer to target sound buffer data.
     *  \param aTargetSamples Size of target sound buffer data in samples.
     *  \param aOffset Start offset to target sound buffer data.
     *  \param aSamples Required number of samples.
     *  \return 1 if successful, 0 if unsuccessful (currently ignored).
     */
    XFCIMPORT virtual UINT32 stream(void *aBuffer, INT32 aTargetSamples, INT32 aOffset, 
                                    INT32 aSamples) = 0;


    //! Destructor.
    XFCIMPORT virtual ~XFcAudioStream();

protected:
    //! Constructor.
    XFCIMPORT XFcAudioStream();

    //! Initialization method.
    /*! This should be called by all extending classes in their creation method.
     */
    XFCIMPORT INT initialize(FLOAT32 aSamplingRate, UINT32 aFlags, REAL aVolume,
                             REAL aPanning, UINT16 aPriority);

    //! Initialization method.
    /*! This should be called by all extending classes in their creation method.
     */
    XFCIMPORT INT initialize(XFcAudioFormat aFormat, REAL aVolume, REAL aPanning,
                             UINT16 aPriority);

};


#endif // !XFCCORE_XFCAUDIOSTREAM_H_INCLUDED

