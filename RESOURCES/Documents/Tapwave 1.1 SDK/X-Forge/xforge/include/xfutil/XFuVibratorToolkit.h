/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Toolkit for vibrator effects
 *
 * $Id: XFuVibratorToolkit.h,v 1.4 2003/09/26 10:41:08 jani Exp $
 * $Date: 2003/09/26 10:41:08 $
 * $Revision: 1.4 $
 */

#ifndef XFUVIBRATORTOOLKIT_H_INCLUDED
#define XFUVIBRATORTOOLKIT_H_INCLUDED


//! Pseudo random number generator class.
class XFuVibratorToolkit
{
public:

    //! Play dithered note on 1-bit vibrator hardware.
    /*! Uses random dither pattern to simulate magnitudes on 1-bit 
     *  vibrator hardware, such as the Tapwave Zodiac.
     *
     * \param aDuration duration of vibration in 10ms units
     * \param aMagnitude strength of vibration, 0..255
     */
    static void playDitheredNote(UINT8 aDuration, UINT8 aMagnitude);
};


#endif // !XFUVIBRATORTOOLKIT_H_INCLUDED

