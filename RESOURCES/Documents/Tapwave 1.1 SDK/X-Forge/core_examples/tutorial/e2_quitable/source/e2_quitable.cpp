// This is the minimal, but quitable, application from 'getting started'.

#include <xforge.h>

class MyApp : public XFcApp, public XFcInput, public XFcRenderer
{
  virtual void onPointerUp(INT32 aX, INT32 aY); 
  virtual void render();
};

void MyApp::onPointerUp(INT32 /*aX*/, INT32 /*aY*/)
{
  XFcCore::quit();
}

void MyApp::render()
{
}

void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mResourceMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mMinimumExtraMemory = (INT32)(1024 * 128);
    aAppPrefs.mUID = 0x0F470002;
}

INT32 xfcAppInit() 
{
  xfcUseDefaults();
  MyApp *a = new MyApp();
  XFcCore::setRenderer(a);
  XFcCore::setController(a);
  return 0;
}
