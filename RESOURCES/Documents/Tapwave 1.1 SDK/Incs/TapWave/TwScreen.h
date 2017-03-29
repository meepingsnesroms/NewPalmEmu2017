/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWSCREEN_H__
#define __TWSCREEN_H__

#include <PalmOS.h>

#define twHoldReasonUnknown 0   // sent when holding or unholding for some other reason
#define twHoldReasonIdle    1   // future use, sent when holding due to autoOff expiration
#define twHoldReasonUser    2   // future use, sent when holding due to user request
#define twHoldReasonSleep   3   // in use, sent when unholding as part of going to sleep

typedef struct TwHoldEventParamTag {
	Int32 reason;		// contains the reason we are going/exiting hold mode. See above list for possible values.
	Int32 deferHold;	// Only used for the twNotifyHoldRequestEvent, this should be incremented by 
						// clients that want to defer the sleep.  To restart a suspended hold request,
                        // the easiest thing to do is enqueue an autoOffChr.
} TwHoldEventParamType;

// these notifications are broadcast when the device is entering
// or exiting hold mode.  The notifyParamsP is 
#define twNotifyHoldRequestEvent 'twh+'
#define twNotifyHoldExitEvent    'twh-'
    
#define twHoldNone     0x00000000   // Normal mode, device running, will sleep if asked 
#define twHoldRequest  0x00000001   // Hold mode requested, device running, will not sleep but display will turn off
#define twHoldInvoke   0x00000002   // Hold mode invoked, display is off 
#define twHoldLock     0x00000004   // don't let EvtResetAutoOffTimer exit hold mode,
                                    // to unlock do TwSetHoldState with twHoldRequest, twHoldNone, or twHoldWake 
#define twHoldWake     0x00000008   // force device to wake up, exits both 'invoke' and 'lock' and leaves state in 'request'
#define twHoldSleeping 0x00000010   // internal flag used when switching from hold to sleep


#ifdef __cplusplus
extern "C" {
#endif

/*
 *  API's to get/set Display State.
 */

Int32 TwGetHoldState (void)
    TAL_TRAP(trapTwGetHoldState);
 
Err  TwSetHoldState (Int32 state)
    TAL_TRAP(trapTwSetHoldState);


#ifdef __cplusplus
}
#endif

#endif /* __TWSCREEN_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
