/*
 * Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved.
 *
 * File:        TwVdAudio.h
 *
 * Author:      DFC
 *
 * Contains:	Virtual Device Driver Interface for RoadDawg Audio control.
 *
 * Exported File:  Yes
 *
 * REVISION HISTORY:
 *      Name    Date        Description
 *      ----    ----        -----------
 *      dfc	    03/21/03    initial Revision
 *      dfc     04/02/03    changed to use properties instead of control cmd
 */

#ifndef __TWVDAUDIOAMP_H__
#define __TWVDAUDIOAMP_H__

#define TW_VD_AUDIOAMP "audioAmp0"      /* Name of the Audio Amplifier control */


/* NOTE:  Only valid TwDevice APIs for the Audio Amplifier are:
 *    err = TwDeviceOpen(&handle, TW_VD_AUDIOAMP, "rw");
 *    err = TwDeviceClose(handle);
 *    err = TwDeviceGetProperty(handle, property, buf, len); // see below for properties
 *    err = TwDeviceSetProperty(handle, property, buf, len); // see below for properties
 */

/*
 * Properties of the Audio Amplifier device
 */

/*General read-only property for getting the state of all the features of the AMP at once */
#define TW_VD_AUDIOAMP_ALL_PROPERTIES  'aprp'   /* Returns all properties of the Audio Amplfier system */
                                                /*  GET only. Returns a UInt8 bitmap with the following values: */
#define TW_VD_AUDIOAMP_PROP_POWRD      0x01     /* Set if Amp is ON, zero if Amp is OFF */
#define TW_VD_AUDIOAMP_PROP_MUTED      0x02     /* Set if Amp is MUTED, zero if Amp is PLAYING */
                                                /* This mutes the power to both speakers and headphones */
#define TW_VD_AUDIOAMP_PROP_SPKR_MUTED 0x04     /* Set if Speaker is MUTED, zero if Speaker is PLAYING */
                                                /* This does not effect the headphones */
#define TW_VD_AUDIOAMP_PROP_BASS_BOOST 0x10     /* Set if Bass Boost is ON, zero if Bass Boost is OFF */

/* The following properties can be both Get and Set.
 *   When the property is SET, it causes the associated action to occur in the Amplifier,
 *   i.e., setting TW_VD_AUDIOAMP_PROP_BBOOST to 1 turns on Bass Boost, setting it to 0 turns it off
 *   When GETting the property, it returns the current state of the amplifier relative to that feature
 * NOTE: All Set's take as argument a UInt8, and Get's return as argument a UInt8. 
 */
#define TW_VD_AUDIOAMP_POWER_UP      'apwr' /* Set to 1 to turn the audio amplifier, 0 to turn off */
#define TW_VD_AUDIOAMP_MUTE_ALL      'apmu' /* Set to 1 to mute the speakers and headphones, to 0 to unmute */
#define TW_VD_AUDIOAMP_MUTE_SPKRS    'spmu' /* Set to 1 to mute the speakers only, to 0 to unmute speakers */
#define TW_VD_AUDIOAMP_BBOOST        'bboo' /* Set to 1 to to turn on Bass Boost, to 0 to turn it off */

#endif /* __TWVDAUDIOAMP_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
