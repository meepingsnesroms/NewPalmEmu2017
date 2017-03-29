// this is the audio example from 'getting started'.

#include <xforge.h>
#include <xfutil/XFuXMPlayer.h>

class MyApp : public XFcApp, public XFcInput, public XFcRenderer
{
  virtual void onPointerUp(INT32 aX, INT32 aY); 
  virtual void render();
  virtual void onAppInit();
  virtual void onAppDeinit();
  XFcGLSurface *mSurf;
  XFcGL *mGL;
  XFuXMPlayer *mPlayer;
  UINT32 mPlayerId;
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

  // Draw a stretched sprite:
  INT32 tick = XFcMath::abs(250 - (XFcCore::getTick() % 500)) + 1;
  INT32 xcenter = XFcCore::getDeviceWidth() / 2;
  INT32 ycenter = XFcCore::getDeviceHeight() / 2;
  fb->drawImage(mSurf, xcenter - tick, ycenter - tick, tick * 2, tick * 2);
}

void MyApp::onAppInit()
{
  mGL = XFcGL::create();
  // Create a 32x32 surface:
  mSurf = XFcGLSurface::create(32, 32);
  // Lock the surface:
  INT16 *map;
  INT32 pitch = mSurf->lock((void **)&map);  
  // Pitch is divided by 2 because we're using a 16-bit pointer
  // and pitch is in bytes.
  pitch /= 2;

  // Fill the surface:
  INT32 ofs = 0;
  for (INT32 y = 0; y < mSurf->getHeight(); y++, ofs = y * pitch)
  {
    for (INT32 x = 0; x < mSurf->getWidth(); x++, ofs++)
    {
      map[ofs] = (INT16)((x << 11) + (y << 6));
    }
  }

  // and remember to unlock:
  mSurf->unlock();

  XFcAudio::setAudioFormat(NULL, 16, 0);

  // create XM player:
  mPlayer = XFuXMPlayer::create("jenkka17.xm", 8000, 0);

  // start playing
  mPlayerId = XFcAudio::play(mPlayer);
}

void MyApp::onAppDeinit()
{
  // stop playing music (one could also just call "XFcAudio::stopAll()")
  XFcAudio::stop(mPlayerId);
}

void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = (INT32)(1024 * 1024 * 1);
    aAppPrefs.mResourceMemoryLimit = (INT32)(1024 * 1024 * 1);
    aAppPrefs.mMinimumExtraMemory = (INT32)(1024 * 128);
    aAppPrefs.mUID = 0x0F470004;
}

INT32 xfcAppInit() 
{
  xfcUseDefaults();
  MyApp *a = new MyApp();
  XFcCore::setRenderer(a);
  XFcCore::setController(a);
  return 0;
}
