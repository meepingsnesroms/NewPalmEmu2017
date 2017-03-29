/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Audio producer base class.
 * 
 * $Id: XFcAudioProducer.h,v 1.10 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.10 $
 */

#ifndef XFC_CORE_XFCAUDIOPRODUCER_H_INCLUDED
#define XFC_CORE_XFCAUDIOPRODUCER_H_INCLUDED

#include <xfcore/XFcAudioFormat.h>


//! Audio producer base class.
class XFCDLLEXPORT XFcAudioProducer
{

public:
    //! Handle to internal data.
    /*! \internal
     */
    void *mUnknown;

protected:

    //! Initialization method.
    /*!
     * \note This should be called by all extending classes in their creation method.
     */
    INT initialize(XFcAudioFormat aFormat, REAL aVolume, REAL aPanning,
                   UINT16 aPriority, INT aIsStream);


    //! Protected constructor.
    XFcAudioProducer();

    //! Virtual destructor.
    virtual ~XFcAudioProducer();

};


#endif // !XFCCORE_XFCAUDIOPRODUCER_H_INCLUDED

