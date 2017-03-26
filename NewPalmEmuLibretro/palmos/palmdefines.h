#ifndef PALMDEFINES
#define PALMDEFINES

#include "trapapilist.h"
#include "errorcodes.h"

//keys
#define	keyBitPower			0x01			// Power key
#define	keyBitPageUp		0x02			// Page-up
#define	keyBitPageDown		0x04			// Page-down
#define	keyBitHard1			0x08			// App #1
#define	keyBitHard2			0x10			// App #2
#define	keyBitHard3			0x20			// App #3
#define	keyBitHard4			0x40			// App #4

//dpad keys
#define keyBitNavLeft			0x01000000
#define keyBitNavRight			0x02000000
#define keyBitNavSelect			0x04000000
#define keyBitNavLRS			0x07000000	/*Key state mask to check the five way navigation LEFT, RIGHT and SELECT buttons.*/


#define	keyBitsAll			0xFFFFFFFF	// all keys

//dpad on new palms
#define vchrRockerUp				0x0132		// 5-way rocker up
#define vchrRockerDown				0x0133		// 5-way rocker down
#define vchrRockerLeft				0x0134		// 5-way rocker left
#define vchrRockerRight				0x0135		// 5-way rocker right
#define vchrRockerCenter			0x0136		// 5-way rocker center/press

#define navFtrCreator           	'fway'		/*Creator ID for 5-Way navigator.*/
#define navFtrVersion           	0		/*Feature id for 5-Way.*/
#define navVersion              	0x00010000	/*Version for 5-Way.*/

#if 0
#define keyBitNavLeft			0x01000000	/**< Key state mask to check the five way navigation LEFT button. */
#define keyBitNavRight			0x02000000	/**< Key state mask to check the five way navigation RIGHT button. */
#define keyBitNavSelect			0x04000000	/**< Key state mask to check the five way navigation SELECT button. */
#define keyBitNavLRS			0x07000000	/**< Key state mask to check the five way navigation LEFT, RIGHT and SELECT buttons. */
#endif

#define navBitUp				0x0001		/**< Key mask for the five way navigation UP button. */
#define navBitDown				0x0002		/**< Key mask for the five way navigation DOWN button. */
#define navBitLeft				0x0004		/**< Key mask for the five way navigation LEFT button. */
#define navBitRight				0x0008		/**< Key mask for the five way navigation RIGHT button. */
#define navBitSelect			0x0010		/**< Key mask for the five way navigation SELECT button. */
#define navBitsAll				0x001F		/**< Key mask for all five way navigation buttons. */

#define navChangeUp				0x0100		/**< Key mask for the five way navigation UP button state change. */
#define navChangeDown			0x0200		/**< Key mask for the five way navigation DOWN button state change. */
#define navChangeLeft			0x0400		/**< Key mask for the five way navigation LEFT button state change. */
#define navChangeRight			0x0800		/**< Key mask for the five way navigation RIGHT button state change. */
#define navChangeSelect			0x1000		/**< Key mask for the five way navigation SELECT button state change. */
#define navChangeBitsAll		0x1F00		/**< Key mask for all five way navigation buttons state change. */



//68k
#define m68kTrapInstr			0x4E40
#define m68kTrapVectorMask		0x000F

#define sysDbgBreakpointTrapNum			0		// For soft breakpoints
#define sysDbgTrapNum					8		// For compiled breakpoints
#define sysDispatchTrapNum				15		// Trap dispatcher



#define	sysAppLaunchCmdNormalLaunch			0
#define	sysAppLaunchCmdFind					1
#define	sysAppLaunchCmdGoTo					2
#define	sysAppLaunchCmdSyncNotify			3
#define	sysAppLaunchCmdTimeChange			4
#define	sysAppLaunchCmdSystemReset			5
#define	sysAppLaunchCmdAlarmTriggered		6
#define	sysAppLaunchCmdDisplayAlarm			7
#define	sysAppLaunchCmdCountryChange		8
#define	sysAppLaunchCmdSyncRequestLocal		9
#define	sysAppLaunchCmdSyncRequest			sysAppLaunchCmdSyncRequestLocal
#define	sysAppLaunchCmdSaveData						10
#define	sysAppLaunchCmdInitDatabase					11
#define	sysAppLaunchCmdSyncCallApplicationV10		12
#define	sysAppLaunchCmdPanelCalledFromApp			13
#define	sysAppLaunchCmdReturnFromPanel				14
#define	sysAppLaunchCmdLookup					 	15
#define	sysAppLaunchCmdSystemLock					16
#define	sysAppLaunchCmdSyncRequestRemote			17
#define	sysAppLaunchCmdHandleSyncCallApp			18
#define sysAppLaunchCmdAddRecord					19

//------------------------------------------------------------------------
// New launch codes defined for PalmOS 3.x where x >= 1
//------------------------------------------------------------------------

#define sysAppLaunchCmdURLParams					50
#define sysAppLaunchCmdNotify						51
#define sysAppLaunchCmdOpenDB						52
#define sysAppLaunchCmdAntennaUp					53
#define sysAppLaunchCmdGoToURL						54

//------------------------------------------------------------------------
// Custom action code base (custom action codes begin at this value)
//------------------------------------------------------------------------
#define	sysAppLaunchCmdCustomBase	0x8000

// Your custom launch codes can be defined like this:
//
//	typedef enum {
//		myAppCmdDoSomething = sysAppLaunchCmdCustomBase,
//		myAppCmdDoSomethingElse,
//		myAppCmdEtcetera
//
//		} MyAppCustomActionCodes;



//------------------------------------------------------------------------
// SysAppLaunch flags (passed to PilotMain)
//------------------------------------------------------------------------

#define	sysAppLaunchFlagNewThread		0x01	// create a new thread for application
															//  - implies sysAppLaunchFlagNewStack
#define	sysAppLaunchFlagNewStack		0x02	// create separate stack for application
#define	sysAppLaunchFlagNewGlobals		0x04	// create new globals world for application
															//  - implies new owner ID for Memory chunks
#define	sysAppLaunchFlagUIApp			0x08	// notifies launch routine that this is a UI app being
															//  launched.
#define	sysAppLaunchFlagSubCall			0x10
#define sysAppLaunchFlagDataRelocated	0x80








#define	sysFileCSystem					'psys'

/************************************************************
 * System Features
 *************************************************************/
#define	sysFtrCreator			sysFileCSystem		// Feature Creator

#define	sysFtrNumROMVersion	1						// ROM Version
			// 0xMMmfsbbb, where MM is major version, m is minor version
			// f is bug fix, s is stage: 3-release,2-beta,1-alpha,0-development,
			// bbb is build number for non-releases
			// V1.12b3   would be: 0x01122003
			// V2.00a2   would be: 0x02001002
			// V1.01     would be: 0x01013000

#define	sysFtrNumProcessorID	2						// Product id
			// 0xMMMMRRRR, where MMMM is the processor model and RRRR is the revision.
#define	sysFtrNumProcessorMask		0xFFFF0000		// Mask to obtain processor model
#define	sysFtrNumProcessor328		0x00010000		// Motorola 68328		(Dragonball)
#define	sysFtrNumProcessorEZ		0x00020000		// Motorola 68EZ328	(Dragonball EZ)
#define	sysFtrNumProcessorVZ		0x00030000		// Motorola 68VZ328	(Dragonball VZ)
#define	sysFtrNumProcessorSuperVZ	0x00040000		// Motorola 68SZ328	(Dragonball SuperVZ)
#define	sysFtrNumProcessorARM720T	0x00100000		// ARM 720T
#define sysFtrNumProcessorARM7TDMI	0x00110000		// ARM7TDMI
#define sysFtrNumProcessorARM920T	0x00120000		// ARM920T
#define sysFtrNumProcessorARM922T	0x00130000		// ARM922T
#define sysFtrNumProcessorARM925	0x00140000		// ARM925
#define sysFtrNumProcessorStrongARM	0x00150000		// StrongARM
#define sysFtrNumProcessorXscale	0x00160000		// Xscale
#define sysFtrNumProcessorARM710A	0x00170000		// ARM710A
#define sysFtrNumProcessorARM925T	0x00180000		// ARM925T
#define sysFtrNumProcessorARM926EJS	0x00190000		// ARM926EJ-S
#define	sysFtrNumProcessorx86		0x01000000		// Intel CPU		(Palm Simulator)

// The following sysFtrNumProcessorIs68K(x) and sysFtrNumProcessorIsARM(x)
// macros are intended to be used to test the value returned from a call to
//    FtrGet(sysFtrCreator, sysFtrNumProcessorID, &value);
// in order to determine if the code being executed is running on a 68K or ARM processor.

#define sysFtrNumProcessor68KIfZero    0xFFF00000   // 68K if zero; not 68K if non-zero
#define sysFtrNumProcessorIs68K(x)     (((x&sysFtrNumProcessor68KIfZero)==0)? true : false)

#define sysFtrNumProcessorARMIfNotZero 0x00F00000   // ARM if non-zero
#define sysFtrNumProcessorIsARM(x)     (((x&sysFtrNumProcessorARMIfNotZero)!=0)? true : false)

#define	sysFtrNumProductID	sysFtrNumProcessorID	// old (obsolete) define

#define	sysFtrNumBacklight	3						// Backlight
			// bit 0:	1 if present. 0 if Feature does not exist or backlight is not present

#define	sysFtrNumEncryption	4						// Which encryption schemes are present
#define	sysFtrNumEncryptionMaskDES		0x00000001 // bit 0:	1 if DES is present

#define	sysFtrNumCountry		5						// International ROM identifier
			// Result is of type CountryType as defined in Preferences.h.
			// Result is essentially the "default" country for this ROM.
			// Assume cUnitedStates if sysFtrNumROMVersion >= 02000000
			// and feature does not exist. Result is in low sixteen bits.

#define	sysFtrNumLanguage		6						// Language identifier
			// Result is of untyped; values are defined in Incs:BuildRules.h
			// Result is essentially the "default" language for this ROM.
			// This is new for the WorkPad (v2.0.2) and did NOT exist for any of the
			// following: GermanPersonal, GermanPro, FrenchPersonal, FrenchPro
			// Thus we can't really assume anything if the feature doesn't exist,
			// though the actual language MAY be determined from sysFtrNumCountry,
			// above. Result is in low sixteen bits.

#define	sysFtrNumDisplayDepth	7					// Display depth
			// Result is the "default" display depth for the screen.					(PalmOS 3.0)
			// This value is used by ScrDisplayMode when setting the default display depth.

#define	sysFtrNumHwrMiscFlags		8				// GHwrMiscFlags value			(PalmOS 3.1)
#define	sysFtrNumHwrMiscFlagsExt	9				// GHwrMiscFlagsExt value		(PalmOS 3.1)

#define	sysFtrNumIntlMgr				10
			// Result is a set of flags that define functionality supported
			// by the Int'l Manager.															(PalmOS 3.1)

#define	sysFtrNumEncoding				11
			// Result is the character encoding (defined in PalmLocale.h) supported
			// by this ROM. If this feature doesn't exist then the assumed encoding
			// is PalmLatin (superset of Windows code page 1252)						(PalmOS 3.1)

#define	sysFtrDefaultFont				12
			// Default font ID used for displaying text.									(PalmOS 3.1)

#define	sysFtrDefaultBoldFont		13
			// Default font ID used for displaying bold text.							(PalmOS 3.1)

#define	sysFtrNumGremlinsSupportGlobals	14		// Globals for supporting gremlins.
			// This value is a pointer to a memory location that stores global variables needed
			// for intelligently supporting gremlins.  Currently, it is only used in Progress.c.
			// It is only initialized on first use (gremlins and progress bar in combination)
			// when ERROR_CHECK_LEVEL == ERROR_CHECK_FULL.								(PalmOS 3.2)

#define	sysFtrNumVendor				15
			// Result is the vendor id, in the low sixteen bits.						(PalmOS 3.3)

#define	sysFtrNumCharEncodingFlags	16
			// Flags for a given character encoding, specified in TextMgr.h		(PalmOS 3.5)

#define	sysFtrNumNotifyMgrVersion	17 // version of the NotifyMgr, if any		(PalmOS 3.5)

#define	sysFtrNumOEMROMVersion		18	// Supplemental ROM version, provided by OEM
			// This value may be present in OEM devices, and is in the same format
			// as sysFtrNumROMVersion.															(PalmOS 3.5)

#define	sysFtrNumErrorCheckLevel	19 // ROM build setting of ERROR_CHECK_LEVEL
			// May be set to ERROR_CHECK_NONE, ERROR_CHECK_PARTIAL, or ERROR_CHECK_FULL
			// as defined in <BuildDefines.h>.												(PalmOS 3.5)

#define	sysFtrNumOEMCompanyID			20			// GHwrOEMCompanyID value		(PalmOS 3.5)
#define	sysFtrNumOEMDeviceID			21			// GHwrOEMDeviceID value		(PalmOS 3.5)
#define	sysFtrNumOEMHALID				22			// GHwrOEMHALID value			(PalmOS 3.5)
#define	sysFtrNumDefaultCompression		23			// Default Clipper's compression (Palmos 3.5)

#define sysFtrNumWinVersion				24			// Window version				(PalmOS 4.0)

#define	sysFtrNumAccessorTrapPresent	25			// If accessor trap exists		(PalmOS 4.0)

#define	sysFtrNumInputAreaFlags		26			// Active silkscreen flags (PalmOS 4.2SC)
			// Flags for active silkscreen, specified in Graffiti.h

#define sysFtrBtSupportsScheduledWakeup 27			// If Bluetooth hardware supports wakeup scheduling
#define sysFtrNumDmAutoBackup           31          // Is Data Manager Auto Backup supported?
#define sysFtrNumFiveWayNavVersion		32			// version of the 5-way nav if any



// This refNum signals an invalid refNum
#define	sysInvalidRefNum				0xFFFF

enum{
	sysEventNilEvent = 0,
	sysEventPenDownEvent,
	sysEventPenUpEvent,
	sysEventPenMoveEvent,
	sysEventKeyDownEvent,
	sysEventWinEnterEvent,
	sysEventWinExitEvent,
	sysEventAppStopEvent = 22,
	sysEventTsmConfirmEvent = 35,
	sysEventTsmFepButtonEvent,
	sysEventTsmFepModeEvent,

	// add future UI level events in this numeric space
	// to save room for new system level events
	sysEventNextUIEvent = 0x0800,

	// <chg 2-25-98 RM> Equates added for library events
	sysEventFirstINetLibEvent = 0x1000,
	sysEventFirstWebLibEvent = 0x1100,

	// <chg 10/9/98 SCL> Changed firstUserEvent from 32767 (0x7FFF) to 0x6000
	// Enums are signed ints, so 32767 technically only allowed for ONE event.
	sysEventFirstUserEvent = 0x6000
};

enum{
	prefVersion,
	prefCountry,
	prefDateFormat,
	prefLongDateFormat,
	prefWeekStartDay,
	prefTimeFormat,
	prefNumberFormat,
	prefAutoOffDuration,					// prefAutoOffDurationSecs is now preferred (prefAutoOffDuration is in minutes)
	prefSysSoundLevelV20,				// slOn or slOff - error beeps and other non-alarm/game sounds
	prefGameSoundLevelV20,				// slOn or slOff - game sound effects
	prefAlarmSoundLevelV20,				// slOn or slOff - alarm sound effects
	prefHidePrivateRecordsV33,
	prefDeviceLocked,
	prefLocalSyncRequiresPassword,
	prefRemoteSyncRequiresPassword,
	prefSysBatteryKind,
	prefAllowEasterEggs,
	prefMinutesWestOfGMT,				// deprecated old unsigned minutes EAST of GMT
	prefDaylightSavings,					// deprecated old daylight saving time rule
	prefRonamaticChar,
	prefHard1CharAppCreator,			// App creator for hard key #1
	prefHard2CharAppCreator,			// App creator for hard key #2
	prefHard3CharAppCreator,			// App creator for hard key #3
	prefHard4CharAppCreator,			// App creator for hard key #4
	prefCalcCharAppCreator,				// App creator for calculator soft key
	prefHardCradleCharAppCreator,		// App creator for hard cradle key
	prefLauncherAppCreator,				// App creator for launcher soft key
	prefSysPrefFlags,
	prefHardCradle2CharAppCreator,	// App creator for 2nd hard cradle key
	prefAnimationLevel,

	// Additions for PalmOS 3.0:
	prefSysSoundVolume,					// actual amplitude - error beeps and other non-alarm/game sounds
	prefGameSoundVolume,					// actual amplitude - game sound effects
	prefAlarmSoundVolume,				// actual amplitude - alarm sound effects
	prefBeamReceive,						// not used - use ExgLibControl with ir(Get/Set)ScanningMode instead
	prefCalibrateDigitizerAtReset,	// True makes the user calibrate at soft reset time
	prefSystemKeyboardID,				// ID of the preferred keyboard resource
	prefDefSerialPlugIn,					// creator ID of the default serial plug-in

	// Additions for PalmOS 3.1:
	prefStayOnWhenPluggedIn,			// don't sleep after timeout when using line current
	prefStayLitWhenPluggedIn,			// keep backlight on when not sleeping on line current

	// Additions for PalmOS 3.2:
	prefAntennaCharAppCreator,			// App creator for antenna key

	// Additions for PalmOS 3.3:
	prefMeasurementSystem,				// English, Metric, etc.

	// Additions for PalmOS 3.5:
	prefShowPrivateRecords,				// returns privateRecordViewEnum
	prefAutoOffDurationSecs,			// auto-off duration in seconds

	// Additions for PalmOS 4.0:
	prefTimeZone,							// GMT offset in minutes, + for east of GMT, - for west
	prefDaylightSavingAdjustment,		// current DST adjustment in minutes (typically 0 or 60)

	prefAutoLockType,						// Never, on poweroff, after preset delay or at preset time.
	prefAutoLockTime,						// Auto lock preset time or delay.
	prefAutoLockTimeFlag,    			// For Minutes or Hours.

	prefLanguage,							// Language spoken in country selected via Setup app/Formats panel
	prefLocale,								// Locale for country selected via Setup app/Formats panel

	prefTimeZoneCountry,					// Country used to specify time zone.

	prefAttentionFlags,					// User prefs for getting user's attention

	prefDefaultAppCreator				// Default application launched on reset.

};

//forms

// Gadget support:
#define formGadgetDrawCmd			0	// paramP is unspecified
#define formGadgetEraseCmd			1	// paramP is unspecified
#define formGadgetHandleEventCmd	2	// paramP is an EventType *for the relevant event.
#define formGadgetDeleteCmd		3	// paramP is unspecified.

#define noFocus 0xffff

#define frmInvalidObjectId		0xffff
#define frmNoSelectedControl	0xff

// Magic button IDs used by FrmCustomResponseAlert callbacks
#define frmResponseCreate		1974
#define frmResponseQuit			((WORD) 0xBEEF)



//syncing
enum{
	dlkSyncStateNeverSynced = 0,		// never synced
	dlkSyncStateInProgress,				// sync is in progress
	dlkSyncStateLostConnection,		// connection lost during sync
	dlkSyncStateLocalCan,				// cancelled by local user on handheld
	dlkSyncStateRemoteCan,				// cancelled by user from desktop
	dlkSyncStateLowMemoryOnTD,			// sync ended due to low memory on handheld
	dlkSyncStateAborted,					// sync was aborted for some other reason
	dlkSyncStateCompleted,				// sync completed normally

	// Added in PalmOS v3.0:
	dlkSyncStateIncompatibleProducts	// sync ended because desktop HotSync product
												// is incompatible with this version
												// of the handheld HotSync
};

#define noPreferenceFound			-1

// Preference version constants
#define preferenceDataVer2			2 // Palm OS 2.0
#define preferenceDataVer3			3 // Palm OS 3.0
#define preferenceDataVer4			4 // Palm OS 3.1
#define preferenceDataVer5			5 // Palm OS 3.2a
#define preferenceDataVer6			6 // Palm OS 3.2b/3.3
#define preferenceDataVer8			8 // Palm OS 3.5
#define preferenceDataVer9			9 // Palm OS 4.0

// Operations for the WinPalette function
#define winPaletteGet 				0
#define winPaletteSet 				1
#define winPaletteSetToDefault	2

#define WinUseTableIndexes -1


#define winDefaultDepthFlag		0xFF


// Bits in the low memory global GHwrMiscFlags (UInt16)
#define	hwrMiscFlagHasBacklight		0x0001			// set if backlight is present
#define	hwrMiscFlagHasMbdIrDA		0x0002			// set if IrDA is present (on main board)
#define	hwrMiscFlagHasCardIrDA		0x0004			// set if IrDA is present (on memory card)
#define	hwrMiscFlagHasBurrBrown		0x0008			// set if BurrBrown A/D is present
#define	hwrMiscFlagHasJerryHW		0x0010			// set if Jerry Hardware is present
#define	hwrMiscFlagNoRTCBug			0x0020			// set if using rev of DragonBall (3G or later)
																	//  that doesn't require the RealTimeClock
																	//  bug work-around (see TimeMgr68328.c).
																	//  <chg 3-27-98 RM>
#define	hwrMiscFlagHas3vRef			0x0040			// set if switchable 3v reference is present
#define	hwrMiscFlagHasAntennaSw		0x0080			// set if viewer has an antenna raised switch
#define	hwrMiscFlagHasCradleDetect	0x0100			// set if we have an A/D converter on hotsync port used for ID'ing the attached device
#define	hwrMiscFlagHasSWContrast	0x0200			// set if UI should support software contrast
#define	hwrMiscFlagInvertLCDForBL	0x0400			// set if we need to invert LCD w/Backlight
#define	hwrMiscFlagHasMiscFlagExt	0x0800			// set if we have new hwrMiscFlagsExt

			// The following bit flags are set by HwrIdentifyFeatures.
			// They allow software to read the hardware ID without poking at hardware.
			// They also provide some isolation from different ID detection schemes
			// such as if the ID detection mechanism should change with EZ...
#define	hwrMiscFlagID1				0x1000				// set if ID bit keyBitHard1 was set
#define	hwrMiscFlagID2				0x2000				// set if ID bit keyBitHard2 was set
#define	hwrMiscFlagID3				0x4000				// set if ID bit keyBitHard3 was set
#define	hwrMiscFlagID4				0x8000				// set if ID bit keyBitHard4 was set
#define	hwrMiscFlagIDMask			0xF000
#define	hwrMiscFlagIDOffset		12						// Bits to shift to get a numeric ID

enum{
	UIObjectFrame = 0,
	UIObjectFill,
	UIObjectForeground,
	UIObjectSelectedFill,
	UIObjectSelectedForeground,
	UIMenuFrame,
	UIMenuFill,
	UIMenuForeground,
	UIMenuSelectedFill,
	UIMenuSelectedForeground,
	UIFieldBackground,
	UIFieldText,
	UIFieldTextLines,
	UIFieldCaret,
	UIFieldTextHighlightBackground,
	UIFieldTextHighlightForeground,
	UIFieldFepRawText,
	UIFieldFepRawBackground,
	UIFieldFepConvertedText,
	UIFieldFepConvertedBackground,
	UIFieldFepUnderline,
	UIFormFrame,
	UIFormFill,
	UIDialogFrame,
	UIDialogFill,
	UIAlertFrame,
	UIAlertFill,
	UIOK,
	UICaution,
	UIWarning,
	UILastColorTableEntry
};

/************************************************************
 * Memory Manager Types
 *************************************************************/
enum{
	memIDPtr,
	memIDHandle
};


/************************************************************
 * Flags accepted as parameter for MemNewChunk.
 *************************************************************/
#define memNewChunkFlagPreLock				0x0100
#define memNewChunkFlagNonMovable			0x0200
#define memNewChunkFlagAtStart				0x0400	// force allocation at front of heap
#define memNewChunkFlagAtEnd				0x0800	// force allocation at end of heap

#define memNewChunkFlagAllowLarge			0x1000  // this is not in the sdk


/************************************************************
 * Memory Manager Debug settings for the MemSetDebugMode function
 *************************************************************/
#define		memDebugModeCheckOnChange			0x0001
#define		memDebugModeCheckOnAll				0x0002
#define		memDebugModeScrambleOnChange		0x0004
#define		memDebugModeScrambleOnAll			0x0008
#define		memDebugModeFillFree				0x0010
#define		memDebugModeAllHeaps				0x0020
#define		memDebugModeRecordMinDynHeapFree	0x0040

// Pixel width of tab stops in fields
#define  fntTabChrWidth      20

// Width of character missing from font.
#define	fntMissingChar		  -1


// Sound Manager max and default volume levels
#define sndMaxAmp				64
//#define sndVolumeMask		0x0ff
#define sndDefaultAmp		sndMaxAmp

#define sndMidiNameLength	32			// MIDI track name length *including* NULL terminator

//
// Command numbers for SndCommandType's cmd field
//
enum{

	sndCmdFreqDurationAmp = 1,		// play a sound, blocking for the entire duration (except for zero amplitude)
											// param1 = frequency in Hz
											// param2 = duration in milliseconds
											// param3 = amplitude (0 - sndMaxAmp); if 0, will return immediately

	// Commands added in PilotOS v3.0
	// ***IMPORTANT***
	// Please note that SndDoCmd() in PilotOS before v3.0 will Fatal Error on unknown
	// commands (anything other than sndCmdFreqDurationAmp).  For this reason,
	// applications wishing to take advantage of these new commands while staying
	// compatible with the earlier version of the OS, _must_ avoid using these commands
	// when running on OS versions less thatn v3.0 (see sysFtrNumROMVersion in SystemMgr.h).
	// Beginning with v3.0, SndDoCmd has been fixed to return sndErrBadParam when an
	// unknown command is passed.
	//
	sndCmdNoteOn,						// start a sound given its MIDI key index, max duration and velocity;
											// the call will not wait for the sound to complete, returning imeediately;
											// any other sound play request made before this one completes will interrupt it.
											// param1 = MIDI key index (0-127)
											// param2 = maximum duration in milliseconds
											// param3 = velocity (0 - 127) (will be interpolated as amplitude)

	sndCmdFrqOn,						// start a sound given its frequency in Hz, max duration and amplitude;
											// the call will not wait for the sound to complete, returning imeediately;
											// any other sound play request made before this one completes will interrupt it.
											// param1 = frequency in Hz
											// param2 = maximum duration in milliseconds
											// param3 = amplitude (0 - sndMaxAmp)

	sndCmdQuiet							// stop current sound
											// param1 = 0
											// param2 = 0
											// param3 = 0

};



// Bits in the low memory global GHwrMiscFlags (UInt16)
#define	hwrMiscFlagHasBacklight		0x0001			// set if backlight is present
#define	hwrMiscFlagHasMbdIrDA		0x0002			// set if IrDA is present (on main board)
#define	hwrMiscFlagHasCardIrDA		0x0004			// set if IrDA is present (on memory card)
#define	hwrMiscFlagHasBurrBrown		0x0008			// set if BurrBrown A/D is present
#define	hwrMiscFlagHasJerryHW		0x0010			// set if Jerry Hardware is present
#define	hwrMiscFlagNoRTCBug			0x0020			// set if using rev of DragonBall (3G or later)
																	//  that doesn't require the RealTimeClock
																	//  bug work-around (see TimeMgr68328.c).
																	//  <chg 3-27-98 RM>
#define	hwrMiscFlagHas3vRef			0x0040			// set if switchable 3v reference is present
#define	hwrMiscFlagHasAntennaSw		0x0080			// set if viewer has an antenna raised switch
#define	hwrMiscFlagHasCradleDetect	0x0100			// set if we have an A/D converter on hotsync port used for ID'ing the attached device
#define	hwrMiscFlagHasSWContrast	0x0200			// set if UI should support software contrast
#define	hwrMiscFlagInvertLCDForBL	0x0400			// set if we need to invert LCD w/Backlight
#define	hwrMiscFlagHasMiscFlagExt	0x0800			// set if we have new hwrMiscFlagsExt

// The following bit flags are set by HwrIdentifyFeatures.
// They allow software to read the hardware ID without poking at hardware.
#define	hwrMiscFlagID1				0x1000				// set if ID bit keyBitHard1 was set
#define	hwrMiscFlagID2				0x2000				// set if ID bit keyBitHard2 was set
#define	hwrMiscFlagID3				0x4000				// set if ID bit keyBitHard3 was set
#define	hwrMiscFlagID4				0x8000				// set if ID bit keyBitHard4 was set
#define	hwrMiscFlagIDMask			0xF000
#define	hwrMiscFlagIDOffset		12						// Bits to shift to get a numeric ID


#define	hwrMiscFlagIDCheckROMToken	(0)						// used to be hwrMiscFlagIDOther
#define	hwrMiscFlagIDPalmPilot		(0)						// since it was never explicitly set

// hwrMiscFlagIDUndetermined is what the OS initializes the ID to when booting.
// The HAL is responsible for setting the ID to something valid (and meaningful).
#define	hwrMiscFlagIDUndetermined	(hwrMiscFlagID1)		// used to be hwrMiscFlagIDUnused1

#define	hwrMiscFlagIDCheckOEMFtrs	(hwrMiscFlagID2)		// used to be hwrMiscFlagIDUnused2

// Old-style Hardware IDs for DragonBall '328 based products
#define	hwrMiscFlagIDThumper		(hwrMiscFlagID4 | hwrMiscFlagID2)
#define	hwrMiscFlagIDJerry			(hwrMiscFlagID4 | hwrMiscFlagID3)
#define	hwrMiscFlagIDRocky			(hwrMiscFlagID4 | hwrMiscFlagID3 | hwrMiscFlagID2)
#define	hwrMiscFlagIDTouchdown		(hwrMiscFlagID4 | hwrMiscFlagID3 | hwrMiscFlagID2 | hwrMiscFlagID1)

// Old-style Hardware IDs for DragonBall 'EZ based products
#define	hwrMiscFlagIDJerryEZ		(hwrMiscFlagID3 | hwrMiscFlagID2)
#define	hwrMiscFlagIDSumo			(hwrMiscFlagID4 | hwrMiscFlagID2 | hwrMiscFlagID1)
#define	hwrMiscFlagIDBrad			(hwrMiscFlagID4 | hwrMiscFlagID3 | hwrMiscFlagID1)
#define	hwrMiscFlagIDAustin			(hwrMiscFlagID4 | hwrMiscFlagID1)
#define	hwrMiscFlagIDCobra2			(hwrMiscFlagID2 | hwrMiscFlagID1)
#define	hwrMiscFlagIDCalvin			(hwrMiscFlagID3 | hwrMiscFlagID1)


// Hardware SubIDs used to detect hardware type early in boot process
#define	hwrMiscFlagExtSubIDBrad				0x0
#define	hwrMiscFlagExtSubIDSumo				0x2
#define	hwrMiscFlagExtSubIDCobra			0x4
#define	hwrMiscFlagExtSubIDCobra2_16		0x6
#define	hwrMiscFlagExtSubIDCobra2_20		0x7



// Old-style Hardware IDs still unused
#define	hwrMiscFlagIDUnused4			(hwrMiscFlagID3)
#define	hwrMiscFlagIDUnused5			(hwrMiscFlagID3 | hwrMiscFlagID1)
#define	hwrMiscFlagIDUnused7			(hwrMiscFlagID3 | hwrMiscFlagID2 | hwrMiscFlagID1)
#define	hwrMiscFlagIDUnused8			(hwrMiscFlagID4)


// Bits in the low memory global GHwrMiscFlagsExt (UInt32)
#define	hwrMiscFlagExtSubID1		0x00000001		// subtype ID (for feature select in device)
#define	hwrMiscFlagExtSubID2		0x00000002		// subtype ID (for feature select in device)
#define	hwrMiscFlagExtSubID3		0x00000004		// subtype ID (for feature select in device)
#define	hwrMiscFlagExtSubIDMask		0x00000007		// sybtype ID Mask

#define	hwrMiscFlagExtHasLiIon		0x00000010		// set if we have Lithium Ion battery rechargable in the cradle
#define	hwrMiscFlagExtHasRailIO		0x00000020		// set if we have Rail I/O hardware
#define	hwrMiscFlagExtHasFlash		0x00000040		// set (by OS or HAL) if we have Flash ROM
#define	hwrMiscFlagExtHasFParms		0x00000080		// set (by OS or HAL) if we have Flash parms area

#define	hwrMiscFlagExt115KIrOK		0x00000100		// device supports 115K IR transfers
#define	hwrMiscFlagExtHasExtLCD		0x00000200		// device has external LCD controller
#define	hwrMiscFlagExtHasSWBright	0x00000400		// device has software controlled brightness

// Added by BGT, 08/01/2000
#define hwrMiscFlagExtNeedsLpr		0x00000800		// DRAM needs special LP Refresh

// Assigned values for hwrOEMCompanyID (aka sysFtrNumOEMCompanyID):
// Values are assigned by the PalmSource Platform Engineering group.
//
// Note: These values are different from the values that may be found in some
// OEM devices which used HwrROMTokens on versions of Palm OS prior to 3.5.

#define hwrOEMCompanyIDUnspecified	0x00000000		// hwrOEMCompanyID not specified by HAL
#define hwrOEMHALIDUnspecified		0x00000000		// hwrOEMHALID not specified by HAL
#define hwrOEMDeviceIDUnspecified	0x00000000		// hwrOEMDeviceID not specified by HAL

#define hwrOEMCompanyIDPalmPlatform	'psys'			// Reference Platforms made by Palm Computing
#define hwrOEMCompanyIDPalmDevices	'palm'			// Devices made by Palm Computing

#define hwrOEMCompanyIDSymbol		'smbl'			// Devices made by Symbol Technologies
#define hwrOEMCompanyIDQualcomm		'qcom'			// Devices made by Qualcomm
#define hwrOEMCompanyIDTRG			'trgp'			// Devices made by TRG Products
#define hwrOEMCompanyIDHandspring	'hspr'			// Devices made by Handspring
#define hwrOEMCompanyIDSony			'sony'			// Devices made by Sony

// Note that values for hwrOEMDeviceID (aka sysFtrNumOEMDeviceID) and
// hwrOEMHALID (aka sysFtrNumOEMHALID) are OEM vendor-specific, and not
// necessarily tracked by this Palm OS header file, though it may be
// worthwhile to include "known" values here for third party developers.
//
// It is recommended that OEM vendors choose values for these globals that
// are four-digit human-readable ASCII values, rather than numeric codes,
// though this is not a requirement.

// HALs that belong to hwrOEMCompanyIDPalmPlatform

#define hwrOEMHALIDEZRef			'eref'			// (Mono 160x160) EZ Reference Platform (PalmSource)
#define hwrOEMHALIDEZRefColor		'cref'			// (Color 160x160) EZ Reference Platform (PalmSource)

#define hwrOEMHALIDVZRefMono1X		'vref'			// (Mono 160x160) VZ Reference Platform (PalmSource)
#define hwrOEMHALIDVZRefMonoQX		'vrfq'			// (Mono QVGA) VZ Reference Platform (PalmSource)
#define hwrOEMHALIDVZRefMono2X		'vrfd'			// (Mono 320x320) VZ Reference Platform (PalmSource)
#define	hwrOEMHALIDVZRef			hwrOEMHALIDVZRefMono1X	// Old name for mono VZRef ROM.

#define hwrOEMHALIDVZRefColor1X		'cvrf'			// (Color 160x160) VZ Reference Platform (PalmSource)
#define hwrOEMHALIDVZRefColorQX		'cvrq'			// (Color QVGA) VZ Reference Platform (PalmSource)
#define hwrOEMHALIDVZRefColor2X		'cvrd'			// (Color 320x320) VZ Reference Platform (PalmSource)
#define	hwrOEMHALIDVZRefColor		hwrOEMHALIDVZRefColor1X	// Old name for color VZRef ROM.

#define hwrOEMHALIDSZRefMono1X		'sref'			// (Mono 160x220) SZ Reference Platform (PalmSource)
#define hwrOEMHALIDSZRefMonoQX		'srfq'			// (Mono QVGA) SZ Reference Platform (PalmSource)
#define hwrOEMHALIDSZRefMono2X		'srfd'			// (Mono 320x440) SZ Reference Platform (PalmSource)

#define hwrOEMHALIDSZRefColor1X		'csrf'			// (Color 160x220) SZ Reference Platform (PalmSource)
#define hwrOEMHALIDSZRefColorQX		'csrq'			// (Color QVGA) SZ Reference Platform (PalmSource)
#define hwrOEMHALIDSZRefColor2X		'csrd'			// (Color 320x440) SZ Reference Platform (PalmSource)

// HALs that belong to hwrOEMCompanyIDPalmDevices
#define hwrOEMHALID328Jerry			'jery'			// Palm VII HAL (Palm Computing)
#define hwrOEMHALID328Rocky			'rcky'			// Pilot, PalmPilot, Palm III HAL (Palm Computing)
#define hwrOEMHALIDEZSumo			'sumo'			// Palm IIIx/V/Vx HAL (Palm Computing)
#define hwrOEMHALIDEZAustin			'astn'			// Palm IIIc (Palm Computing)
#define hwrOEMHALIDEZCalvin			'clvn'			// Palm m100 (Palm Computing)




// Pen Input Manager Features
#define pinCreator					'pins'
#define pinFtrAPIVersion			1

// preliminary 1.0 release from Garmin
#define pinAPIVersion1_0			0x01000000
// PINS API version number (1.1 for OS 5.3)
#define pinAPIVersion1_1			0x01103000
// PINS API version number (2.0 for OS 6.0)
#define pinAPIVersion2_0			0x02003000


// Pen Input Manager errors
#define pinErrNoSoftInputArea		(pinsErrorClass | 0x00)
#define pinErrInvalidParam			(pinsErrorClass | 0x01)

// control bar errors
#define statErrInvalidLocation		(statErrorClass | 0x01)
#define statErrInvalidName			(statErrorClass | 0x02)
#define statErrInputWindowOpen		(statErrorClass | 0x03)


// Input area states
enum{
	pinInputAreaOpen,
	pinInputAreaClosed,
	pinInputAreaNone,				// do not use
	reserved1,						// do not use
	reserved2,						// do not use
	pinInputAreaUser,				// restore the last user selection of input area state

	pinInputAreaReset = 0xFFFF		// for internal use only
};


// Input trigger states
enum{
	pinInputTriggerEnabled,
	pinInputTriggerDisabled,
	pinInputTriggerNone// do not use
};


// selectors for StatGetAttribute
#define	statAttrBarVisible	0
#define statAttrDimension	1


#define	maxStrIToALen	12


enum{
	 clipboardText,
	 clipboardInk,
	 clipboardBitmap
};

//ARM <=> 68k exchange
/************************************************************
 * Constants
 *************************************************************/
/* These are little-endian! Use from ARM code only. */
#define pceTrapCallARMCodeNoArg		0xfe07
#define pceTrapCallARMCode		0xff07

#define pceOpcodeTRAP			0x4f4e
#define pceOpcodeJSR			0xb94e
#define pceOpcodeRTS			0x754e


#define kPceNativeWantA0		(0x10000000)
#define kPceNativeTrapNoMask		(0x00000FFF)


/************************************************************
 * Handy macro
 *************************************************************/
#define pceMakeTrap(x)			((x) - sysTrapBase)
#define PceNativeTrapNo(sysTrapNo)	(sysTrapNo & kPceNativeTrapNoMask)


#define pceFtrCreator			'a68k'
#define pceFtrNumTrapHandlersP		1

#define CALL68KFUNC 0xFFFFFF68
//#define CALL68KFUNC 0xFFF68000//FFFF68



/*
 * This is the generic creator for Tapwave products, assigned by PalmSource
 */
#define twCreatorID             'Tpwv'
#define twFtrCreator            twCreatorID

/*
 * This is the PalmOS feature number for TapWave API version.
 */
#define twFtrAPIVersion         0x0000

/*
 * This is the PalmOS feature number for TapWave Native API Glue.
 */
#define twFtrAPIGlue            0x0001

/*
 * This feature can be used to discover the current background music state.
 * See TwSndSetMusicControlState in TwSound.h
 */
#define twFtrMusicControlState  0x0002

/*
 * This feature contains the source change number for Tapwave
 * Application Library. NOTE: this feature may not exist for
 * engineering builds. --hz 2004-01-07
 */
#define twFtrChangeNumber       0x0003

/*
 * This is the compile-time version for TapWave API.
 */
#ifndef TAPWAVE_API_VERSION
#define TAPWAVE_API_VERSION     0x0205
#endif





//notifications
#define DBChangedFieldSetName             0x1
#define DBChangedFieldSetCreator          0x2
#define DBChangedFieldSetType             0x4
#define DBChangedFieldSetCrDate           0x8
#define DBChangedFieldSetModDate         0x10
#define DBChangedFieldSetBckUpDate       0x20
#define DBChangedFieldSetModNum          0x40
#define DBChangedFieldSetAppInfo         0x80
#define DBChangedFieldSetSortInfo       0x100
#define DBChangedFieldSetAttributes     0x200
#define DBChangedFieldSetVersion        0x400


#define sysNotifyNormalPriority		0	// clients should use this priority

#define sysNotifyBroadcasterCode	sysFileCSystem // broadcaster code for events broadcast by the system

#define sysNotifyNoDatabaseID		0xFFFFFFFF		// for system use only!!!

#define sysNotifyVersionNum			1	// version of the NotifyMgr, obtained from the feature

// The queue is much smaller in debug builds so that we aren't tempted to overflow it
// (and larger for release builds so that when we do, it will work).
#if ERROR_CHECK_LEVEL == ERROR_CHECK_FULL
#define sysNotifyDefaultQueueSize	10
#else
#define sysNotifyDefaultQueueSize	30
#endif

/*
	Notify Manager Events:

	Note that in general, for notifications regarding the creation of information
	(e.g. sysNotifyDBAddedEvent) the broadcast goes out AFTER the fact (e.g.,
	after the database has been created) and that notifications regarding
	the deletion of information are broadcast BEFORE the fact.  A notable and
	unfortunate exception to this rule is the database deleted notification, which
	is sent out after the fact.

	The sleep & wake notifications require a little special attention.  These
	notifications are _not_ guaranteed to always be broadcast, and hence are unsuitable
	for applications where external hardware must be shut off to conserve power when
	we go to sleep.  For example, the sleep notification will not be broadcast when
	we do an emergency  shutdown due to low battery conditions.  Also note that any
	sort of prolonged activity (especially displaying UI sich as a dialog) in response
	to these noticfications can complicate things immensely.  UI is very tricky because
	these notifications are broadcast from SysHandleEvent.  The result is that you may
	receive more than one sleep notification if one of the notification clients puts up
	a dialog or something, and it remains there long enough for another AutoOff event
	to come through.  There are also possible problems with reentrancy and stack space
	usage since the notification is broadcast from SysHandleEvent inside an application's
	event loop.
*/

#define sysNotifySyncStartEvent		'hots'	// Sent at the start of a hotsync.
											// Always sent from UI thread.
											// param: none

#define sysNotifySyncFinishEvent	'sync'	// Sent at the end of a hotsync.
											// Always sent from UI thread.
											// param: none

#define sysNotifyAntennaRaisedEvent	'tena'	// Sent when the antenna is raised on a
											// Palm VII series device.
											// Always sent from UI thread.
											// param: none

#define sysNotifyResetFinishedEvent	'rstf'	// Broadcast after all app launchcodes
											// are sent after a reset.
											// Always sent from UI thread.
											// param: none

#define sysNotifyForgotPasswordEvent 'bozo'	// Broadcast when the user presses the
											// 'Forgotten Password' button in the
											// security app, just before every database's
											// private records are deleted.

#define sysNotifySecuritySettingEvent 'ssch' // Broadcast when the security setting
					  // is changed either by the user in the Security application or
					  // programmatically using SecSvcsSetDeviceSetting.

#define sysNotifyTimeChangeEvent	'time'	// Broadcast when the time is changed by the user.
											// param: Int32*, ptr to time change delta in
											// seconds (e.g., a value of 100 means that the
											// user set the clock ahead 100 seconds).

#define sysNotifySleepRequestEvent	'slpq'	// A "Sleep Request Event" is broadcast when the device
											// is about to go to sleep, and is a chance for clients
											// to do perform an action or even delay going to sleep
											// for a little while.  This may be broadcast multiple
											// times if one or more clients defer the sleep. Parameter
											// is a pointer to a SleepEventParamType.  See below
											// details on this structure. Note that this event is
											// NOT guaranteed to be broadcast.  See the big comment
											// at the top of this list for important detials & warnings.
											// Always sent from UI thread.

#define sysNotifySleepNotifyEvent	'slp!'	// A "Sleep Notify Event" is broadcast when the device is
											// definitely going to sleep as soon as the broadcast
											// is finished.  Parameter is unused.
											// Note that this event is NOT guaranteed to be broadcast.
											// See the big comment at the top of this list for
											// important detials & warnings.
											// Always sent from UI thread.


#define sysNotifyEarlyWakeupEvent	'worm'	// ...the early bird gets the worm...
											// Broadcast just after the device wakes up
											// at the early stage where the screen may
											// still be turned off and we may quickly go
											// back to sleep after handling an alarm or
											// charger event.
											// Always sent from UI thread.


#define sysNotifyLateWakeupEvent	'lazy'	// Broadcast after the device wakes up
											// at the later stage of the wakeup
											// process after we turn the screen on,
											// broadcast from EvtResetAutoOffEvent
											// the first time it is called implying
											// that the device will remain awake
											// for at least a little while.
											// Always sent from UI thread.


#define sysNotifyDisplayChangeEvent	'scrd'	// Sent when the display depth is
											// changed, notifyDetailsP has old/new depth
											// see SysNotifyDisplayChangeDetailsType


#define sysNotifyMenuCmdBarOpenEvent	'cbar'	// Sent by FormHandleEvent when a menuCmdBarOpenEvent
												// passes through. The system will not open the toolbar
												// if the 'handled' field is set in the parameter block,
												// so most clients should not set it.  The notification
												// is provided so that Hack-like entities can catch
												// it and add their own buttons to the bar. These
												// buttons will show up to the left of cut/copy/paste/undo and
												// to the right of everything else.

#define cncNotifyProfileEvent	 'cncp'	// sent by the Connection Panel to inform its clients
													// that the current configuration has change
													//	void * notifyDetailsP : has to be casted as UInt32
													// to get the Broadcasted Profile ID user specified ptr
													// passed back with notification
													//	void * userDataP : has to be casted as UInt16
													// to get the device kind of the Broadcasted Profile ID

#define	sysExternalConnectorAttachEvent	'ecna'		// Broadcast when anything is attached to
													// the external connector.

#define	sysExternalConnectorDetachEvent	'ecnd'		// Broadcast when anything is detached from
													// the external connector.

#define sysNotifyCardInsertedEvent	'crdi'	// Broadcast when an ExpansionMgr card is
											// inserted into a slot, and the slot driver
											// calls ExpCardInserted.  Always broadcast
											// from UI task.
											// ExpansionMgr will play a sound & attempt to
											// mount a volume unless the corresponding
											// bits in the 'handled' field are set by a
											// notification handler (see ExpansionMgr.h).
											// PARAMETER: slot number cast as void*

#define sysNotifyCardRemovedEvent	'crdo'	// Broadcast when an ExpansionMgr card is
											// removed from a slot, and the slot driver
											// calls ExpCardRemoved.  Always broadcast
											// from UI task.
											// ExpansionMgr will play a sound & attempt to
											// unmount a volume unless the corresponding
											// bits in the 'handled' field are set by a
											// notification handler (see ExpansionMgr.h).
											// PARAMETER: slot number cast as void*

#define sysNotifyVolumeMountedEvent	'volm'	// Broadcast when a VFSMgr volume is
											// mounted, Always broadcast from UI task.
											// VFSMgr will run start.prc (if present),
											// and SysUIAppSwitch  to it or the Launcher
											// unless the appropriate bits in the 'handled'
											// field are set by a notification handler.
											// PARAMETER: VFSAnyMountParamPtr cast as void*

#define sysNotifyVolumeUnmountedEvent	'volu'	// Broadcast AFTER a VFSMgr volume is
												// unmounted, Always broadcast from UI task.
												// VFSMgr will delete start.prc (if it was loaded).
												// The volume ref number for the unmounted volume is
												// NO LONGER VALID, so don't bother trying to use it.
												// PARAMETER: volume refNum cast as void*

#define sysNotifyHelperEvent		'hlpr'	// Sent by Address Book (or any
											// 3rd party application) to
											// communicate with Phone Apps


#define sysNotifyPOSEMountEvent     'pose'  // Sent by HostFS to communicate with itself,
											// saving on stack depth.


#define sysNotifyLocaleChangedEvent	'locc'	// Notify apps/panel that the system locale
												// has changed.
												// This is broadcast by the language picker after it
												// has changed the locale.
												// Always sent from UI thread.
												// param: ptr to SysNotifyLocaleChangedType




#define sysNotifyRetryEnqueueKey	'retk'		// An EvtEnqueueKey failed, so retry.


#define sysNotifyGotUsersAttention	'attn'	// Got users attention.


#define sysNotifyDBDeletedEvent	'dbs-'	// broadcast AFTER a database is removed from the device.
														// Note that the database ID in the parameter block is
														// NO LONGER VALID, and you WILL CRASH the device if you
														// try to pass it to any DataMgr routines.
														// notifyDetailsP: ptr to SysNotifyDBDeletedType.

// Notification CreatorID for notifying Launcher and third-party Launchers of changes
#define sysNotifyDBCreatedEvent 'dbcr'	// broadcast (deferred) after a database is created on the device.

#define sysNotifyDBChangedEvent 'dbmn'  // broadcast (deferred) after database info is set on a database, such
												// as by DmSetDatabaseInfo

#define sysNotifyDBDirtyEvent   'dbdr'  // broadcast (deferred) when an overlay is opened, a database is opened for
												// write, or other events which can "dirty" the database info --
												// the Launcher normally checks over such databases on reset and
												// updates the LaunchDB.

#define sysNotifyDeviceUnlocked	'unlk'	// Broadcasted by the Security app After the device is
										//unlocked.
										//notifyDetailsP: none

#define sysNotifyPhoneEvent			'fone'		// Sent by third-party applications to communicate
												// with built-in or external phones.
												// NOTE THAT THIS EVENT IS FOR FUTURE USE

#define sysNotifyNetLibIFMediaEvent	'neti'		// Broadcasted by NetLib to communicate its interfaces media Up and Down requests
												// to registered Apps.
												// notifyDetailsP: ptr to SysNotifyNetLibIFMediaType.

#define sysNotifyDeleteProtectedEvent			'-pdb'		// Broadcast BEFORE a database is removed from the device when a user
																			// or installer application wants to remove a protected database.  This
																			// will ONLY be issued from the UI task and should be issued before each
																			// user driven deletion that targets a protected database that the app
																			// running does not own (i.e. needs to request be unprotected).
																			// This gives the unlucky client a chance to do any required
																			// cleanup work.  Note that if an application has multiple protected
																			// databases, this notification may be sent out more than once.
																			// notifyDetailsP: ptr to SysNotifyDBInfoType.

#define sysNotifyIrDASniffEvent			'irda'		// Sent by IrDA sniffing code when an incomming IrDA frame is detected

#define sysNotifyProcessPenStrokeEvent      'hpps'      // Sent to enable custom recognition of strokes on the system area of the digitizer (buttons, etc.)
														// Note: future OS releases might not send this notification.

#define sysNotifyVirtualCharHandlingEvent   'hvch'      // Sent to enable custom handling handling of vchars
														// Note: future OS releases might not send this notification.

#define sysNotifyEventDequeuedEvent         'hede'      // Sent for each event being returned by EvtGetEvent. Be very careful
														// about registering for this; you can easily impact performance (in a bad way!)
														// Also note: for speed, notifyDetailsP points to a event structure with
														// system-native endianness, meaning you might need to byte-swap what you
														// read depending on what endianness your code uses.
														// Note: future OS releases might not send this notification.

#define sysNotifyIdleTimeEvent              'hidl'      // Sent when the system is idle and is about to doze.
														// Note: future OS releases might not send this notification.

#define sysNotifyAppLaunchingEvent          'hapl'		// Sent before an app is launched (normalLaunch only)
														// Note: future OS releases might not send this notification.

#define sysNotifyAppQuittingEvent           'hapq'      // Sent right after an app has quit (normalLaunch only)
														// Note: future OS releases might not send this notification.

#define sysNotifyInsPtEnableEvent           'hipe'      // Sent at the start of InsPtEnable(). notifyDetailsP points to a Boolean: the enableIt param.
														// Note: future OS releases might not send this notification.

#define sysNotifyKeyboardDialogEvent        'hkbd'      // Sent to enable replacement of SysKeyboardDialog()'s UI.
														// The notifyDetailsP points to the KeyboardType.
														// Note: future OS releases might not send this notification.

#define sysNotifyDisplayResizedEvent		'scrs'		// Broadcast by PINSetInputAreaState after the input area
														// opens or closes.  NotifyDetailsP is a pointer to a
														// SysNotifyDisplayResizedDetailsType structure.

#define sysNotifyInputAreaDrawingEvent		'iaad'		// Broadcast by HALRedrawInputArea right before the input area bitmap
														// is drawn. If the notification is handled, the bitmap is not drawn.
														// NotifyDetailsP is a pointer to a SysNotifyInputAreaDrawingDetailsType structure.
														// Note: future OS releases might not send this notification.

#define sysNotifyInputAreaPendownEvent		'iapd'		// Broadcast by SysHandleEvent when a pen-down has occurred in the input area.
														// If the notification is handled, further pen-down processing is skipped.
														// NotifyDetailsP is a pointer to a SysNotifyInputAreaPendownDetailType structure.
														// Note: future OS releases might not send this notification.

#define sysNotifySelectDay					'seld'		// Broadcast by SelectDay before displaying any UI.
														// If the notification is handled, further UI is skipped.
														// NotifyDetailsP is a pointer to a SysNotifySelectDayDetailsType structure.
														// Note: future OS releases might not send this notification.

#define sysNotifyGsiDrawIndicator			'gsid'		// Broadcast by GsiDrawIndicator before drawing the GSI.
														// If the notification is handled, further drawing is skipped.
														// Note: future OS releases might not send this notification.

#endif  //PALMDEFINES
