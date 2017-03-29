// this is the profiler example from 'getting started'.

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

  // Mark the beginning of 'clear' event 
  XFcProfiler::addEvent("clear");
  
  // Clear the framebuffer:
  mGL->clear();
  
  // Mark the beginning of 'waste' event (we'll waste some time here)
  XFcProfiler::addEvent("waste");
  INT k;
  for (INT i = 0; i < 256; i++)
    for (INT j = 0; j < 256; j++)
      k = i * i / (j + 1);
  
  // Ask GL for the secondary buffer:
  fb = mGL->getSecondary();
  
  // Make the frame event
  XFcProfiler::frameEvent();  
  
  // Print the debug info:
  mPrinter->print(fb, 0, 0, XFcProfiler::getEventLog());
  
  // Reset event log; last event was called 'print', next one is 'core '
  XFcProfiler::resetEvent("print", "core ");
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
    aAppPrefs.mUID = 0x0F470007;
}


INT32 xfcAppInit() 
{
  xfcUseDefaults();
  XFcProfiler::initEventLog();
  MyApp *a = new MyApp();
  XFcCore::setRenderer(a);
  XFcCore::setController(a);
  return 0;
}
