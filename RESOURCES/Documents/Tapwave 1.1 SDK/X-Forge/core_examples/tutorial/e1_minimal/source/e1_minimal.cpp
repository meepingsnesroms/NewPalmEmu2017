// This is the minimal application from 'getting started'.

#include <xforge.h>

void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mResourceMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mMinimumExtraMemory = (INT32)(1024 * 128);
    aAppPrefs.mUID = 0x0F470001;
}

INT32 xfcAppInit() 
{
  xfcUseDefaults();
  return 0;
}
