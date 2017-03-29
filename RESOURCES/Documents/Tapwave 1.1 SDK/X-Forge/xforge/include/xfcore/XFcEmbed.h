/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Used to access the desktop windows embedding interface
 * 
 * $Id: XFcEmbed.h,v 1.5 2003/09/26 11:54:43 mikko Exp $
 * $Date: 2003/09/26 11:54:43 $
 * $Revision: 1.5 $
 */

#ifndef XFC_XFCEMBED_H_INCLUDED
#define XFC_XFCEMBED_H_INCLUDED


#if defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE)
#include <windows.h>
#else
#error Embedding only supported in Desktop Windows builds.
#endif

#if defined(XFC_PLATFORM_DESKTOPWINDOWS)
extern void XFCDLLEXPORT embeddedControlDown(int code);
extern void XFCDLLEXPORT embeddedControlUp(int code);
extern void XFCDLLEXPORT embeddedKeyDown(int code);
extern void XFCDLLEXPORT embeddedKeyUp(int code);
extern void XFCDLLEXPORT embeddedPointerDown(int x, int y);
extern void XFCDLLEXPORT embeddedPointerMove(int x, int y);
extern void XFCDLLEXPORT embeddedPointerUp(int x, int y);
extern void XFCDLLEXPORT embeddedInit(int aWidth, int aHeight,
                                      INT (__cdecl *xfcAppInit)(void),
                                      void (__cdecl *xfcAppPref)(XFcAppPrefs &), HINSTANCE hInst);
extern void XFCDLLEXPORT embeddedSoundInit();
extern short XFCDLLEXPORT * embeddedFrame();
extern void XFCDLLEXPORT embeddedDeinit();
extern int XFCDLLEXPORT realWinMain(int aWidth, int aHeight,
                                    HINSTANCE hInst, int nCmdShow,
                                    INT (__cdecl *xfcAppInit)(void),
                                    void (__cdecl *xfcAppPref)(XFcAppPrefs &),
                                    CHAR8 *aCommandline);
#endif

#if defined(XFC_PLATFORM_WINCE)
extern int XFCDLLEXPORT realWinMain(HINSTANCE hInst, int nCmdShow,
                                    INT (*xfcAppInit)(void),
                                    void (*xfcAppPref)(XFcAppPrefs &),
                                    CHAR16 *aCommandline);
#endif


#endif // XFC_XFCEMBED_H_INCLUDED
