/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio buffer base class.
 * 
 * $Id: XFcAudioBuffer.h,v 1.9 2003/10/06 11:26:47 toni Exp $
 * $Date: 2003/10/06 11:26:47 $
 * $Revision: 1.9 $
 */

#ifndef XFC_CORE_XFCAUDIOBUFFER_H_INCLUDED
#define XFC_CORE_XFCAUDIOBUFFER_H_INCLUDED

#include <xfcore/XFcAudioProducer.h>


//! Audio buffer base class.
class XFCDLLEXPORT XFcAudioBuffer : public XFcAudioProducer
{

public:

    //! Creates a new audio buffer object with given audio format and volume.
    XFCIMPORT static XFcAudioBuffer * create(XFcAudioFormat aFormat,
                                             REAL aVolume);

    //! Creates a new audio buffer object with given audio format, volume and panning.
    XFCIMPORT static XFcAudioBuffer * create(XFcAudioFormat aFormat, REAL aVolume,
                                             REAL aPanning);
    
    //! Creates a new audio buffer object with the given audio format, volume, panning and priority.
    XFCIMPORT static XFcAudioBuffer * create(XFcAudioFormat aFormat, REAL aVolume,
                                             REAL aPanning, UINT16 aPriority);

    //! Creates a new audio buffer object with the given audio format and volume.
    XFCIMPORT static XFcAudioBuffer * create(FLOAT32 aSamplingRate, UINT32 aFlags,
                                             INT32 aSamples, REAL aVolume);
    
    //! Creates a new audio buffer object with the given audio format, volume and panning.
    XFCIMPORT static XFcAudioBuffer * create(FLOAT32 aSamplingRate, UINT32 aFlags,
                                             INT32 aSamples, REAL aVolume,
                                             REAL aPanning);
    
    //! Creates a new audio buffer object with the given audio format, volume, panning and priority.
    XFCIMPORT static XFcAudioBuffer * create(FLOAT32 aSamplingRate, UINT32 aFlags,
                                             INT32 aSamples, REAL aVolume,
                                             REAL aPanning, UINT16 aPriority);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcAudioBuffer();

protected:

    //! Protected constructor.
    XFCIMPORT XFcAudioBuffer();

    //! Initialization method.
    /*! This should be called by all extending classes in their creation method.
     */
    XFCIMPORT INT initialize(FLOAT32 aSamplingRate, UINT32 aFlags, INT32 aSamples,
                             REAL aVolume, REAL aPanning, UINT16 aPriority);

    //! Initialization method.
    /*! This should be called by all extending classes in their creation method.
     */
    XFCIMPORT INT initialize(XFcAudioFormat aFormat, REAL aVolume, REAL aPanning,
                             UINT16 aPriority);

};


#endif // !XFCCORE_XFCAUDIOBUFFER_H_INCLUDED

