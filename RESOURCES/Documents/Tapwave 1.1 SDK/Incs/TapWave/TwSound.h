/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWSOUND_H__
#define __TWSOUND_H__

#include <PalmOS.h>
#include <TwTraps.h>

#ifdef __cplusplus
extern "C" {
#endif

#define twNotifyMuteEvent                'Twsm'         // broadcast when the system is muted or unmuted

typedef struct TwNotifyMuteDetailsTag {
    Int32 muted;
    UInt32 unmuteAt;
} TwNotifyMuteDetailsType;


// This notification is sent when a change to the master volume occurs. This is the volume
// controled by the TwSndSetVolume and TwSndGetVolume calls. The reason for the change is
// indicated in the 32 bit value below; the *old* volume setting is the low 16 bits
// (0..sndMaxAmp). The new volume setting can be discovered by calling TwSndGetVolume.
#define twNotifySoundVolumeChangedEvent  'Twsv'

// Type used for the notifyDetailsP. Cast the pointer to get the value.
typedef UInt32 TwNotifySoundVolumeChangedDetailsType;

// Values for TwNotifySoundVolumeChangedDetailsType. Note that the reason code is an enumerated
// value, not a bitmask. Test it like this:
//
// UInt32 details = (UInt32) notifyDetailsP;
// if ((details & twSndVolumeChangedReasonMask) == twSndVolumeChangedHeadphoneInserted) { }
#define twSndVolumeChangedHeadphoneInserted     0x00010000UL    // headphones in
#define twSndVolumeChangedHeadphoneRemoved      0x00020000UL    // headphones out
#define twSndVolumeChangedSetVolume             0x00030000UL    // API call to TwSndSetVolume made
#define twSndVolumeChangedReasonMask            0x00FF0000UL    // mask to get reason code

enum TwSysBeepTag {
    // these match SysBeepTag in SoundMgr.h
    twSndInfo = 1,
    twSndWarning,
    twSndError,
    twSndStartUp,
    twSndAlarm,
    twSndConfirmation,
    twSndClick,

    // these are new TapWave additions
    twSndBumpedEdge = 200,
    twSndFollowedLink,
    twSndCardInserted,
    twSndCardRemoved,
    twSndDocked,
    twSndUndocked,
    twSndNextPage,
    twSndPrevPage,
    twSndSyncBegin,
    twSndSyncEnd,
    twSndEnter,
    twSndLaunch,
    twSndSelection,
    twSndLeave,
    twSndGraffitiOpen,
    twSndGraffitiClose,
    twSndRotate,
    twSndBluetoothOn,
    twSndBluetoothOff,
    twSndVolumeChange,
    twSndConnect,
    twSndGoDoPlay,

    twSndDebugUp,
    twSndDebugDown,
    twSndDebugTrill,
    twSndDebugBling
};

typedef UInt8 TwSysBeepTagType;




// BACKGROUND MUSIC FUNCTIONS

// Use the feature manager to test if music is currently playing:
//   The music state will be set to one of the control values
//   Not all control values reflect a current state
//   Note that for some players, "stop" and "pause" are interchangeable
//   If the feature is not set or musicState is 0, no music is playing.

    /*
    UInt32 musicState;
    FtrGet(twFtrCreator, twFtrMusicControlState, &musicState);
    switch (musicState) {
        case twSndMusicControlDisable:
            // no background music player
        case twSndMusicControlStop:
            // music is stopped
        case twSndMusicControlPlay:
            // music is playing
        case twSndMusicControlPause:
            // music is paused
    }
    */

// When the user taps the music control button in the status
// a notification as below is sent with the command twSndMusicControlOpen

// Applications can also do their own SysNotifyBroadcast to control
// background play, e.g. to pause while playing an important sound
// or to stop in order to free the CPU resources.

    /*
    SysNotifyParamType notify;
    TwNotifySoundMusicControlDetailsType details;

	MemSet(&notify, sizeof(notify), 0);    
    notify.broadcaster = appFileCreator;
    notify.notifyType = twNotifySoundMusicControlEvent;
    notify.notifyDetailsP = &details;
	details.command = twSndMusicControlPause;
	SysNotifyBroadcast(&notify);
    */


// This notification is sent when the user invokes the MusicControls button in
#define twNotifySoundMusicControlEvent  'Twmc'

// Type used for the notifyDetailsP for music controls. Cast the pointer to get the value.
typedef struct TwNotifySoundMusicControlDetailsTag {
    UInt32 command;
    // command details may be here
} TwNotifySoundMusicControlDetailsType;

// Overlay notifyDetailsP for the music "play file" command.
typedef struct TwNotifySoundMusicControlPlayFileDetailsTag {
    UInt32 command;
    const Char *pathNameP;
    UInt16 volRefNum;
} TwNotifySoundMusicControlPlayFileDetailsType;

// Values for the command in the details type
#define twSndMusicControlDisable        0    // no background play at all
#define twSndMusicControlQuery          1    // is there anybody out there?
#define twSndMusicControlOpen           2    // open a detailed control slip
#define twSndMusicControlShowTrackInfo  3    // briefly display current track info

#define twSndMusicControlStop          10    // stop, free all resources
#define twSndMusicControlPlay          11    // play
#define twSndMusicControlPause         12    // pause, may not free all resources
#define twSndMusicControlToggle        13    // toggle play/pause state

#define twSndMusicControlNextTrack     20    // go to next track
#define twSndMusicControlPreviousTrack 21    // previous track or restart current track

#define twSndMusicControlSkipForward   30    // skip forward in current track
#define twSndMusicControlSkipBackward  31    // skip backwards in current track

#define twSndMusicControlPlayFile      40    // play the specified MP3 track (then stop)

#define twSndMusicControlAppSpecific  255    // interpretation and additional details depends on the app 




/*
 * Get the "master" volume.
 */
UInt16 TwSndGetVolume(void)
    TAL_TRAP(trapTwSndGetVolume);

/*
 * Set the "master" volume. The legal range for newVolume is
 * 0-sndMaxAmp. Any other value returns an error.
 */
Err TwSndSetVolume(UInt16 newVolume)
    TAL_TRAP(trapTwSndSetVolume);

/*
 * Set the mute and a time to unmuteAt. A zero value for unmuteAt
 * means mute forever.
 */
void TwSndSetMute(Boolean mute, UInt32 unmuteAt)
    TAL_TRAP(trapTwSndSetMute);

/*
 * Query the current mute setting and the time to unmuteAt. If
 * unmuteAt must be non-NULL to get the value.
 */
Boolean TwSndGetMute(UInt32 *unmuteAt)
    TAL_TRAP(trapTwSndGetMute);

/*
 * Set the bass boost level. The legal range for boostLevel is
 * 0-sndMaxAmp. Any other value returns an error.
 */
Err TwSndSetBassBoost(UInt16 boostLevel)
    TAL_TRAP(trapTwSndSetBassBoost);

/*
 * Query the current bass boost level.
 */
UInt16 TwSndGetBassBoost(void)
    TAL_TRAP(trapTwSndGetBassBoost);

/*
 * Play a system sound. Returns an error for an invalid beepID.
 * volume can be usual 0..sndMaxAmp, or one of the special values
 * sndSystemVolume, sndGameVolume, or sndAlarmVolume to use the
 * system-wide volume setting
 */
Err TwSndPlaySystemSound(TwSysBeepTagType beepID, Int16 volume)
    TAL_TRAP(trapTwSndPlaySystemSound);


/*
 * Sets up the system to play an alarm sound:
 *    all other sound channels are muted
 *    mute state is temporarily disabled
 *    the external speakers are turned on
 *    the final amplifier is set to alarm volume
 * Note: attention manager does this for you!
 */
Err TwSndSetAlarmPlaying(Boolean isAlarm)
    TAL_TRAP(trapTwSndSetAlarmPlaying);


/*
 * Set the music control status button state.  (UI only)
 * this is for use ONLY by the application which implements
 * background music playback.  Other apps should use the
 * NotifyMgr based control API if they need to control
 * background playback state.
 *
 * Apps that want to find out the current state can use
 * FtrGet(twFtrCreator, twFtrMusicControlState, &state)
 * to get the last state that was set.
 *
 */
Err TwSndSetMusicControlState(UInt32 command)
    TAL_TRAP(trapTwSndSetMusicControlState);



#ifdef __cplusplus
}
#endif

#endif /* __TWSOUND_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
