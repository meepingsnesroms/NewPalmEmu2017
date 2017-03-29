/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWAPP_H__
#define __TWAPP_H__

#include <PalmOS.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initialize Tapwave Native Application framework.
 *
 * The function creates an empty form to cover entire display window
 * area and setup form event handler for it, so that this app can
 * receive all palmos events through its event handler.
 */
Err TwAppStart(Boolean (*AppHandleEvent)(EventType* event));

/*
 * Finalize Tapwave Native Application framework.
 *
 * Application should avoid calling any API functions after this
 * point, especially any UI functions.
 */
Err TwAppStop(void);

/*
 * Run Tapwave Native Application using standard PalmOS event loop.
 * This function will handle different PalmOS version properly.
 *
 *  Err TwAppRun(Int32* timeout)
 *  {
 *      EventType event;
 *      Err err = errNone;
 *
 *      for (;;) {
 *          EvtGetEvent(&event, *timeout);
 *
 *          if (!SysHandleEvent(&event)) {
 *              if (!MenuHandleEvent(NULL, &event, &err)) {
 *                  if (!FrmDispatchEvent(&event)) {
 *                      if (event.eType == appStopEvent) {
 *                          return err;
 *                      }
 *                  }
 *              }
 *          }
 *      }
 *  }
 *
 * Application can change event loop speed by modifying the timeout
 * value at any point. NOTE: timeout is specificed in milli seconds.
 *
 * The event loop stops at appStopEvent. If application does not want
 * to stop, it should change appStopEvent to nilEvent inside it event
 * handler. However, it should prompt user before doing this.
 */
Err TwAppRun(Int32* timeout);

/*
 * Get next event from system.
 *
 * Let system process next event. Return the event if it is not
 * handled by standard event loop, otherwise return nilEvent.
 *
 * This function is obsolete, because PalmOS requires application to
 * use event handler model. Application should use TwAppRun() instead.
 */
Err TwNextEvent(EventType * event, Int32 timeout);

#ifdef __cplusplus
}
#endif

#endif /* __TWAPP_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
