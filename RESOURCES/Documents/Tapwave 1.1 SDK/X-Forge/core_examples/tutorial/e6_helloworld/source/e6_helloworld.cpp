// this is the 'hello world' printer example from 'getting started'.

#include <xforge.h>
#include <xfutil/XFuPrinter.h>

class MyApp : public XFcApp, public XFcInput, public XFcRenderer
{
  virtual void onPointerUp(INT32 aX, INT32 aY); 
  virtual void render();
  virtual void onAppInit();
  XFcGL *mGL;
  XFuPrinter *mPrinter;
};


void MyApp::onPointerUp(INT32 /*aX*/, INT32 /*aY*/)
{
  XFcCore::quit();
}


void MyApp::render()
{
  XFcGLSurface *fb;
  
  // Clear the framebuffer:
  mGL->clear();
  
  // Ask GL for the secondary buffer:
  fb = mGL->getSecondary();
  
  // Print the classic phrase:
  mPrinter->print(fb, 0, 0, XFCSTR("Hello World"));
}


void MyApp::onAppInit()
{
  mGL = XFcGL::create();
  mPrinter = XFuPrinter::create(XFCSTR("font16.pcx"), 0);
}


void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mResourceMemoryLimit = (INT32)(1024 * 1024 * 0.5);
    aAppPrefs.mMinimumExtraMemory = (INT32)(1024 * 128);
    aAppPrefs.mUID = 0x0F470006;
}


INT32 xfcAppInit() 
{
  xfcUseDefaults();
  MyApp *a = new MyApp();
  XFcCore::setRenderer(a);
  XFcCore::setController(a);
  return 0;
}
