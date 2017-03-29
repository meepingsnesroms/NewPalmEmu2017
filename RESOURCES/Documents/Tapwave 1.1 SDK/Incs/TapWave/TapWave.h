/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TAPWAVE_H__
#define __TAPWAVE_H__

#include <PalmOS.h>
#include <VFSMgr.h>
#include <PceNativeCall.h>

#include <TwDefs.h>
#include <TwTraps.h>
#include <TwChars.h>
#include <TwDevice.h>
#include <TwHighScore.h>
#include <TwInput.h>
#include <TwKeys.h>
#include <TwOSAdditions.h>
#include <TwScreen.h>
#include <TwSecurity.h>
#include <TwSound.h>
#include <TwSemaphore.h>
#include <TwVdAudioAmp.h>
#include <TwVdRumbler.h>
#include <TwGfx.h>
#include <TwGfxUtils.h>
#include <TwApp.h>
#include <PenInputMgr.h>
#include <BtLib.h>
#include <TwJpg.h>
#include <TwMp.h>
#include <TwMidi.h>

#if CPU_TYPE != CPU_68K
#include <TwRuntime.h>
#include <TwSemaphore.h>
#include <TwUtils.h>
#include <zlib.h>
#include <TwGlue.h>
#include <TwNew.h>
#endif /* CPU_TYPE != CPU_68K */

#endif /* __TAPWAVE_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
