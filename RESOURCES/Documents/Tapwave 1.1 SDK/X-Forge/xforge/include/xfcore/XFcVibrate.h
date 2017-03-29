/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Vibrator interface
 * 
 * $Id: XFcVibrate.h,v 1.10 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.10 $
 */

#ifndef XFC_VIBRATE_H_INCLUDED
#define XFC_VIBRATE_H_INCLUDED


//! Static interface to vibrator hardware.
class XFcVibrate
{
public:

    //! Determines if vibrator hardware is available.
    /*!
     * \return 0 if no vibrator functionality is available
     * \return 1 if basic vibrator support is available.
     * \return 2 if rumbler 'songs' are supported.
     * \return 3 if rumbler can be set to loop the song.
     */
    static INT32 isSupported();

    //! Plays basic rumbler effect
    /*! 
     * Basic vibrator support doesn't define the magnitude of the 
     * vibration at all. Vibration is run in cycles of vibrator on, 
     * vibrator off, and these cycles can be repeated. The vibration
     * time is in units of approximately 100ms.
     */
    static void playBasic(INT32 aVibrateTime, INT32 aPauseTime, INT32 aCycles);

    //! Plays a single vibration note.
    /*!
     * This is a convenience function and only works if rumbler 'songs'
     * are supported.
     *
     * \param aDuration duration of vibration in 10ms units
     * \param aMagnitude strength of vibration, 0..255
     */
    static void playNote(UINT8 aDuration, UINT8 aMagnitude);
        
    //! Plays a vibrator 'song'.
    /*! 
     * Song is an array of 2-byte 'notes', with first byte of the pair noting
     * the 'magniture' of the vibration (0 being silent, 255 being max), and
     * the second byte is the duration, in approximately 10ms intervals.
     * If the hardware supports it, the song can be set to loop until the next
     * play() command. 
     * \note Be sure to keep the 'songs' relatively short - 100 notes is plenty.
     */
    static void playSong(UINT8 *aSong, INT32 aNotes, INT aLoop);
    
    //! Attempts to stop the current vibration effect.
    static void stop();
};


#endif // !XFC_VIBRATE_H_INCLUDED

