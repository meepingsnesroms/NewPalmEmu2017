/*
	File:			Zing.cpp	

	Description:	Zing demo source file. This is where all the magic happens.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/
#include <TapWave.h>

#ifdef EOF
#undef EOF
#endif
#ifdef WIN32
#define snprintf _snprintf
#endif

#include <stdio.h>
#include <string.h>

#include "ZingRsc.h"
#include "JpegLoader.h"

// Assertion Support
static void
assert_check(int error, const char* message)
{
    if (error) {
        ErrDisplayFileLineMsg("PalmOS", (UInt16) error, message);
    }
}

#define xassert(error) assert_check(error, #error);

static void showError(const char* aWhat, Err aError) {
    ErrDisplayFileLineMsg("oink", (UInt16) aError, aWhat);
}

static void showError(const char* aWhat, UInt32 aValue) {
    char chbuf[50];
    StrPrintF(chbuf, "%lx", aValue);
    ErrDisplayFileLineMsg(aWhat, (UInt16)0, chbuf);
}

//----------------------------------------------------------------------

// lame lame lame random number generator
UInt32 gRandomSeed;
static Int32 random() 
{
    UInt32 result;

    // Generate the new seed
    gRandomSeed *= 2147001325;
    gRandomSeed += 715136305;

    // Return the random number
    result = gRandomSeed >> 16;

    return Int32(result);
}

//----------------------------------------------------------------------

// Utility function to load a resource palm bitmap into a new TwGfx surface
static TwGfxSurfaceType*
LoadBitmap(TwGfxType* aGfxLib, Int16 aResID)
{
    TwGfxSurfaceType* surf = NULL;

#ifdef __PALMOS_ARMLET__
    MemHandle resH = DmGetResource('Tbmp', aResID);
#else
    MemHandle resH = DmGetResource('abmp', aResID);
#endif
    if (resH != NULL) {
        BitmapType* resBmp = (BitmapType*) MemHandleLock(resH);
        if (resBmp) {
            UInt16 prevcs = WinSetCoordinateSystem(kCoordinatesNative);

            // Get information about bitmap
            Coord w, h;
            WinGetBitmapDimensions(resBmp, &w, &h);

            // Allocate a surface to hold the image
            TwGfxSurfaceInfoType surfInfo;
            surfInfo.size = sizeof(surfInfo);
            surfInfo.width = w;
            surfInfo.height = h;
            surfInfo.location = twGfxLocationAcceleratorMemory;
            surfInfo.pixelFormat = twGfxPixelFormatRGB565;
            xassert(TwGfxAllocSurface(aGfxLib, &surf, &surfInfo));

            TwGfxPointType dp = {0, 0};
            xassert(TwGfxDrawPalmBitmap(surf, &dp, resBmp));
            xassert(MemHandleUnlock(resH));

            WinSetCoordinateSystem(prevcs);
        } else {
            assert_check(aResID, "MemHandleUnlock failed");
        }
        xassert(DmReleaseResource(resH));
    } else {
        assert_check(aResID, "DmGetResource failed");
    }

    return surf;
}

//----------------------------------------------------------------------

// Simple base class that zeros memory

class ZeroBase {
public:
    // Override operator new and delete for this class so that operator new can zero out the
    // instance data.
    void* operator new(size_t aSize) {
        void* p = MemPtrNew(aSize);
        if (p) {
            MemSet(p, aSize, 0);
        }
        return p;
    }

    void operator delete(void* aPtr) {
        MemPtrFree(aPtr);
    }
};

//----------------------------------------------------------------------

// Simple sample application class that wraps up the various Tapwave Native Application calls
// to create a well formed application. In theory this could be implemented in a library, or a
// template.

static class GenericApp* gApp;

static SYSTEM_CALLBACK Boolean ClassAppHandleEvent(EventType* aEvent);

class GenericApp : public ZeroBase {
public:
    // Note: set the default delay between event loops to 10ms
    GenericApp(Int32 aDelay) : mDelay(aDelay) {
    }

    virtual ~GenericApp() {
    }

    virtual void Launch() {
        AppStart();
        AppEventLoop();
        AppStop();
    }

    virtual void AppStart() {
        TwAppStart(&ClassAppHandleEvent);
        AppBegin();
    }

    // Install your application specific initialization code in the AppBegin method
    virtual void AppBegin() {
    }

    virtual void AppEventLoop() {
        TwAppRun(&mDelay);
    }

    virtual void AppStop() {
        AppEnd();
        TwAppStop();
    }

    // Install your application specific cleanup code in the AppEnd method
    virtual void AppEnd() {
    }

    virtual Boolean AppHandleEvent(EventType* aEvent) {
        RectangleType bounds;
        Boolean handled = false;

        switch (aEvent->eType) {
          case winDisplayChangedEvent:
            // This logic responds to the user changing the orientation or the size of the
            // display area by hiding or showing the grafitti area.
            WinGetBounds(WinGetDisplayWindow(), &bounds);
            WinSetBounds(WinGetActiveWindow(), &bounds);
            HandleResizeEvent();
            handled = true;
            break;

          case keyDownEvent:
            // This logic responds to the user pressing the function button which we use to
            // make the application become fullscreen or revert to non-fullscreen (as a
            // toggle).
            if (aEvent->data.keyDown.chr == vchrFunction) {
                UInt32 visible;
                StatGetAttribute(statAttrBarVisible, &visible);
                if (visible) {
                    PINSetInputAreaState(pinInputAreaClosed);
                    StatHide();
                } else {
                    StatShow();
                    PINSetInputAreaState(pinInputAreaUser);
                }
                handled = true;
            }
            break;

          default:
            break;
        }
        return handled;
    }

    // This method is called when the display area changes size
    virtual void HandleResizeEvent() {
    }

protected:
    // Delay between event loops
    Int32 mDelay;
};

// Note: this cannot be a static class method because the SYSTEM_CALLBACK attribute doesn't
// work there.
static SYSTEM_CALLBACK Boolean ClassAppHandleEvent(EventType* aEvent) {
    return gApp->AppHandleEvent(aEvent);
}

//----------------------------------------------------------------------

    // What a lovely bunch of magic numbers:
    //  450 => display width
    //  344x84 => tapwave image dimensions
    //  44x34 => go, do image dimensions
    //  52x34 => do image dimensions
    //  64x34 => play image dimensions

#define DISPLAY_WIDTH 450
#define DISPLAY_HEIGHT 320
#define GO_WIDTH 52
#define GO_HEIGHT 34
#define GOING_WIDTH 52
#define GOING_HEIGHT 34
#define DO_WIDTH 52
#define DO_HEIGHT 34
#define PLAY_WIDTH 78
#define PLAY_HEIGHT 36
#define TAPWAVE_WIDTH 344
#define TAPWAVE_HEIGHT 84

#define FRAMES_PER_SECOND       60

// When the "game" begins - 5 seconds after starting
#define START_TIMEOUT           5 * FRAMES_PER_SECOND

//----------------------------------------------------------------------

// Simple base class for animated surfaces - surfaces that move or change in some fashion. This
// code is not meant to be a good object model for an animation system; its purpose is to
// demonstrate some of the TwGfx rendering methods and what they can be used for.

class AnimatedSurface : public ZeroBase {
public:
    AnimatedSurface(Int32 aX, Int32 aY, Int32 aDX, Int32 aDY)
        : mXPos(aX), mYPos(aY), mDX(aDX), mDY(aDY)
    {
    }

    virtual ~AnimatedSurface() {
    }

    virtual void Init(TwGfxType* aGfxLib, Int16 aID) {
        mSurface = LoadBitmap(aGfxLib, aID);
        if (mSurface) {
            TwGfxSurfaceInfoType info;
            info.size = sizeof(info);
            TwGfxGetSurfaceInfo(mSurface, &info);
            mWidth = info.width;
            mHeight = info.height;
        }
    }

    // This Compose method just does a TwGfxBitBlt
    virtual void Compose(TwGfxSurfaceType* aDestSurface) {
        if (mSurface) {
            TwGfxPointType dp;
            TwGfxMakePoint(dp, mXPos, mYPos);

            TwGfxRectType r;
            TwGfxMakeRect(r, 0, 0, mWidth, mHeight);

            TwGfxBitBlt(aDestSurface, &dp, mSurface, &r);
        }
    }

    Int32 x() const { return mXPos; }
    Int32 y() const { return mYPos; }
    Int32 x1() const { return mXPos + mWidth; }
    Int32 y1() const { return mYPos + mHeight; }
    Int32 w() const { return mWidth; }
    Int32 h() const { return mHeight; }

    void GetBounds(TwGfxRectType* aBounds) {
        aBounds->x = mXPos;
        aBounds->y = mYPos;
        aBounds->w = mWidth;
        aBounds->h = mHeight;
    }

    bool Intersects(AnimatedSurface* aSurface) {
        if (aSurface == this) {
            // Sanity check: we don't intersect ourselves
            return false;
        }

        TwGfxRectType ours, theirs;
        GetBounds(&ours);
        aSurface->GetBounds(&theirs);
        return Intersects(&ours, &theirs);
    }

    static bool Intersects(const TwGfxRectType* aR1, const TwGfxRectType* aR2) {
        Int32 r2right = aR2->x + aR2->w;
        if (r2right <= aR1->x) return false;

        Int32 r2bottom = aR2->y + aR2->h;
        if (r2bottom <= aR1->y) return false;

        Int32 r1right = aR1->x + aR1->w;
        if (aR2->x >= r1right) return false;

        Int32 r1bottom = aR1->y + aR1->h;
        if (aR2->y >= r1bottom) return false;

        return true;
    }

    // Moving animation routine. Move by a constant velocity and bounce of the rectangular
    // boundary.
    void MovingAnimation(const TwGfxRectType* aBounds) {
        Int32 x0 = aBounds->x;
        Int32 y0 = aBounds->y;
        Int32 x1 = x0 + aBounds->w;
        Int32 y1 = y0 + aBounds->h;

        Int32 x = mXPos + mDX;
        if (x < x0) {
            x = x0;
            mDX = -mDX;
        }
        if (x + mWidth > x1) {
            x = x1 - mWidth;
            mDX = -mDX;
        }

        Int32 y = mYPos + mDY;
        if (y < y0) {
            y = y0;
            mDY = -mDY;
        }
        if (y + mHeight > y1) {
            y = y1 - mHeight;
            mDY = -mDY;
        }
        mXPos = x;
        mYPos = y;
    }

    virtual void Animate(UInt32 aFrame, const TwGfxRectType* aBounds) {
        MovingAnimation(aBounds);
    }

    // Create a mask usable with TwGfxMaskBlendBlt: find all of the non-transparent pixels and
    // assign them the alpha value from aAlpha (aAlpha is a value between zero and 15,
    // inclusive). For transparent pixels, the alpha value is set to zero. aBitmapResult is
    // filled in with a full description of the resulting mask, includ the "data" field which
    // has mask memory allocated.
    static Err MakeMask(TwGfxSurfaceType* aSurface, TwGfxPackedRGBType aTransparentColor, UInt8 aAlpha,
                        TwGfxBitmapType* aBitmapResult) {
        TwGfxSurfaceInfoType info;
        info.size = sizeof(info);
        Err err = TwGfxGetSurfaceInfo(aSurface, &info);
        if (!err) {
            void* addr;
            err = TwGfxLockSurface(aSurface, &addr);
            if (!err) {
                UInt16 transparentPixel = (UInt16) TwGfxPackedRGBToDisplayRGB(aTransparentColor);

                // Initialize bitmap object and allocate memory for the mask data
                aBitmapResult->size = sizeof(TwGfxBitmapType);
                aBitmapResult->width = info.width;
                aBitmapResult->height = info.height;
                aBitmapResult->rowBytes = (info.width + 1) / 2;       // 2 pixels per byte
                aBitmapResult->pixelFormat = twGfxPixelFormat4bpp;
                aBitmapResult->data = MemPtrNew(aBitmapResult->rowBytes * aBitmapResult->height);
                if (!aBitmapResult->data) {
                    err = sysErrNoFreeRAM;
                }
                else {
                    memset(aBitmapResult->data, 0, aBitmapResult->rowBytes * aBitmapResult->height);

                    // Using surface data construct the mask: where we find the
                    // transparentPixel, put a zero in the mask, otherwise put i+1 in the mask.
                    const UInt16* pixp = (const UInt16*) addr;
                    const UInt16* end = (const UInt16*) ((char*)pixp + info.rowBytes * info.height);
                    UInt8* maskp = (UInt8*) aBitmapResult->data;
                    while (pixp < end) {
                        const UInt16* nextPixp = (const UInt16*) ((char*)pixp + info.rowBytes);
                        const UInt16* lineEnd = pixp + info.width;

                        // Note: lazy code
                        for (Int32 x = 0; x < info.width; x++) {
                            if (*pixp++ != transparentPixel) {
                                UInt8 byte = maskp[x/2];
                                if (x & 1) {
                                    byte |= aAlpha;
                                }
                                else {
                                    byte |= aAlpha << 4;
                                }
                                maskp[x/2] = byte;
                            }
                        }
                        pixp = nextPixp;
                        maskp = maskp + aBitmapResult->rowBytes;
                    }
                }
                TwGfxUnlockSurface(aSurface, false);
            }
        }
        return err;
    }

protected:
    TwGfxSurfaceType* mSurface;
    Int32 mXPos, mYPos;
    Int32 mDX, mDY;
    Int32 mWidth, mHeight;
};

// 8 bits of fraction fixed point
#define MAKE_FIXED_POINT(_num,_denom) (((_num) << 8) / (_denom))
#define FIXED_TO_INT(_fp) ((_fp) >> 8)

// A surface that doesn't move, but whose alpha blending animates

class StationaryBlendedSurface : public AnimatedSurface {
public:
    StationaryBlendedSurface(Int32 aX, Int32 aY, Int32 aAlpha, Int32 aDA)
        : AnimatedSurface(aX, aY, 0, 0),
          mAlpha(aAlpha),
          mDA(aDA)
        {
        }

    virtual ~StationaryBlendedSurface() {
    }

    virtual void Init(TwGfxType* aGfxLib, Int16 aID) {
        AnimatedSurface::Init(aGfxLib, aID);
    }

    virtual void Compose(TwGfxSurfaceType* aDestSurface) {
        if (mSurface) {
            // Center in destination surfaces area
            TwGfxSurfaceInfoType info;
            info.size = sizeof(info);
            TwGfxGetSurfaceInfo(aDestSurface, &info);
            TwGfxPointType dp;
            TwGfxMakePoint(dp, (info.width - mWidth) / 2, (info.height - mHeight) / 2);

            TwGfxRectType r;
            TwGfxMakeRect(r, 0, 0, mWidth, mHeight);

            // Use the mask so that we can blend and have transparency
            Int32 a = FIXED_TO_INT(mAlpha);
            TwGfxBlendBlt(aDestSurface, &dp, mSurface, &r, TwGfxComponentsToPackedRGB(a, a, a));
        }
    }

    virtual void Animate(UInt32 aFrame, const TwGfxRectType* aBounds) {
        // we don't move, but our alpha value cycles
        Int32 a = mAlpha + mDA;
        if (a < 0) {
            a = 0;
            mDA = -mDA;
        }
        else if (a > MAKE_FIXED_POINT(255,1)) {
            a = MAKE_FIXED_POINT(255,1);
            mDA = -mDA;
        }
        mAlpha = a;
    }

protected:
    Int32 mAlpha;
    Int32 mDA;
};

// A simple variant on AnimatedSurface that uses transparency

class TransparentAnimatedSurface : public AnimatedSurface {
public:
    TransparentAnimatedSurface(Int32 aX, Int32 aY, Int32 aDX, Int32 aDY, UInt32 aTransparentColor)
        : AnimatedSurface(aX, aY, aDX, aDY),
          mTransparentColor(aTransparentColor)
        {
            mXPos = aX;
            mYPos = aY;
        }

    virtual ~TransparentAnimatedSurface() {
    }

    // This Compose method does a TwGfxTransparentBlt
    virtual void Compose(TwGfxSurfaceType* aDestSurface) {
        if (mSurface) {
            TwGfxPointType dp;
            TwGfxMakePoint(dp, mXPos, mYPos);

            TwGfxRectType r;
            TwGfxMakeRect(r, 0, 0, mWidth, mHeight);

            TwGfxTransparentBlt(aDestSurface, &dp, mSurface, &r, mTransparentColor);
        }
    }

protected:
    UInt32 mTransparentColor;
};

//----------------------------------------------------------------------

class GoSurface : public TransparentAnimatedSurface {
public:
    GoSurface(Int32 aX, Int32 aY, Int32 aDX, Int32 aDY, TwGfxPackedRGBType aTransparentColor)
        : TransparentAnimatedSurface(aX, aY, aDY, aDY, aTransparentColor)
    {
    }

    virtual void Init(TwGfxType* aGfxLib, Int16 aID1, Int16 aID2, Int16 aID3) {
        TransparentAnimatedSurface::Init(aGfxLib, aID1);
        mMovingSurface = LoadBitmap(aGfxLib, aID2);
        mGlowingSurface = LoadBitmap(aGfxLib, aID3);
    }

    virtual void Compose(TwGfxSurfaceType* aDestSurface) {
        if (mSurface && mMovingSurface) {
            TwGfxPointType dp;
            TwGfxMakePoint(dp, mXPos, mYPos);

            TwGfxRectType r;
            TwGfxMakeRect(r, 0, 0, mWidth, mHeight);

            if (mFrame < START_TIMEOUT) {
                TwGfxTransparentBlt(aDestSurface, &dp, mSurface, &r, mTransparentColor);
            }
            else {
                TwGfxTransparentBlt(aDestSurface, &dp, mGlowing ? mGlowingSurface : mMovingSurface,
                                    &r, mTransparentColor);
            }
        }
    }

    void Animate(UInt32 aFrame, const TwGfxRectType* aBounds, bool aBounce, Int32 aBounceAmount) {
        if (aBounce) {
            if (!mGlowing) {
                mGlowing = true;
                mGlowingCounter = 0;
                mDY = -mDY;

                // adjust dx by amount away from center we are
                if (aBounceAmount < 0) {
                    // left side of "paddle"
                }
                else {
                    // right side of "paddle"
                }
            }
        }
        else {
            if (mGlowing) {
                mGlowingCounter++;
                if (mGlowingCounter > (FRAMES_PER_SECOND * 3 / 4)) {
                    mGlowing = false;
                }
            }
        }

        Animate(aFrame, aBounds);
    }

    virtual void Animate(UInt32 aFrame, const TwGfxRectType* aBounds) {
        mFrame = aFrame;
        if (aFrame < START_TIMEOUT) {
            // Until 5 seconds have elapsed, we don't start moving
            return;
        }
        TransparentAnimatedSurface::Animate(aFrame, aBounds);
    }

protected:
    TwGfxSurfaceType* mMovingSurface;
    TwGfxSurfaceType* mGlowingSurface;
    UInt32 mFrame;
    bool mGlowing;
    Int32 mGlowingCounter;
};

class DoSurface : public TransparentAnimatedSurface {
public:
    DoSurface(Int32 aX, Int32 aY, TwGfxPackedRGBType aTransparentColor)
        : TransparentAnimatedSurface(aX, aY, 0, 0, aTransparentColor),
          mState(sittingDuck)
    {
    }

    virtual ~DoSurface() {
        for (Int32 i = 0; i < 15; i++) {
            if (mMasks[i].data) {
                MemPtrFree(mMasks[i].data);
            }
        }
    }

    virtual void Init(TwGfxType* aGfxLib, Int16 aID) {
        // Load our image
        TransparentAnimatedSurface::Init(aGfxLib, aID);

        // Using our image memory, construct 15 4bpp masks so that we can do
        // TwGfxMaskBlendBlt's to fade in/out the image.
        for (Int32 i = 0; i < 15; i++) {
            // Initialize bitmap object and allocate memory for the mask data
            Err err = MakeMask(mSurface, mTransparentColor, i+1, &mMasks[i]);
            if (err) {
                ErrDisplayFileLineMsg("DoSurface::Init", err, "MakeMask failed");
            }
        }
    }

    virtual void Compose(TwGfxSurfaceType* aDestSurface) {
        if (mSurface) {
            Int32 maskNum;

            TwGfxPointType dp;
            TwGfxMakePoint(dp, mXPos, mYPos);
            TwGfxRectType r;
            TwGfxMakeRect(r, 0, 0, mWidth, mHeight);

            switch (mState) {
              case sittingDuck:
                TwGfxTransparentBlt(aDestSurface, &dp, mSurface, &r, mTransparentColor);
                break;

              case smacked:
                TwGfxBitBlt(aDestSurface, &dp, mSurface, &r);
                break;

              case fadingOut:
                maskNum = (mCurrentFrame - mStartFrame) / 15;
                if (maskNum > 14) maskNum = 14;
                TwGfxMaskBlendBlt(aDestSurface, &dp, mSurface, &r, &mMasks[14-maskNum]);
                break;

              case fadingIn:
                maskNum = (mCurrentFrame - mStartFrame) / 15;
                if (maskNum > 14) maskNum = 14;
                TwGfxMaskBlendBlt(aDestSurface, &dp, mSurface, &r, &mMasks[maskNum]);
                break;
            }

            // Some disabled debugging code used to verify that the masks were created properly.
            if (false) {
                UInt16 fakePalette[16];
                for (Int32 p = 0; p < 16; p++) {
                    UInt16 comp = (UInt16) ((p<<4) | p);
                    fakePalette[p] = TwGfxMakeDisplayRGB(comp, comp, comp);
                }

                for (Int32 i = 0; i < 15; i++) {
                    TwGfxMakePoint(dp, 2 + (i % 8) * (mWidth + 2), 2 + (i / 8) * (mHeight + 2));
                    mMasks[i].palette = fakePalette;
                    TwGfxDrawBitmap(aDestSurface, &dp, &mMasks[i]);
                    mMasks[i].palette = NULL;
                }
            }
        }
    }

    void Animate(UInt32 aFrame, const TwGfxRectType* aBounds, bool aAction) {
        mCurrentFrame = aFrame;
        if (aAction && (mState == sittingDuck)) {
            mState = smacked;
            mStartFrame = aFrame;
        }

        switch (mState) {
          case sittingDuck:
            break;

          case smacked:
            if (aFrame - mStartFrame >= 2*FRAMES_PER_SECOND) {
                mState = fadingOut;
                mStartFrame = aFrame;
            }
            break;

          case fadingOut:
            if (aFrame - mStartFrame >= 2*FRAMES_PER_SECOND) {
                mState = fadingIn;
                mStartFrame = aFrame;

                // Warp to a new location
                mXPos = random() % DISPLAY_WIDTH;
                if (mXPos + mWidth > DISPLAY_WIDTH) {
                    mXPos = DISPLAY_WIDTH - mWidth;
                }
                mYPos = random() % DISPLAY_HEIGHT;
                if (mYPos + mHeight > DISPLAY_HEIGHT) {
                    mYPos = DISPLAY_HEIGHT - mHeight;
                }
            }
            break;

          case fadingIn:
            if (aFrame - mStartFrame >= 2*FRAMES_PER_SECOND) {
                mState = sittingDuck;
            }
            break;
        }

        TransparentAnimatedSurface::Animate(aFrame, aBounds);
    }

protected:
    enum {
        sittingDuck,
        smacked,
        fadingOut,
        fadingIn,
    } mState;
    UInt32 mStartFrame;
    UInt32 mCurrentFrame;
    TwGfxBitmapType mMasks[15];
};

class PlaySurface : public TransparentAnimatedSurface {
public:
    PlaySurface(Int32 aX, Int32 aY, TwGfxPackedRGBType aTransparentColor)
        : TransparentAnimatedSurface(aX, aY, 0, 0, aTransparentColor)
    {
    }

    virtual void Animate(UInt32 aFrame, const TwGfxRectType* aBounds) {
        mFrame = aFrame;

        if (aFrame < START_TIMEOUT / 2) {
            // Until half the start time has elapsed, we do nothing
            return;
        }

        if (aFrame < START_TIMEOUT) {
            // For the second half of the start time, we animate by dropping to the bottom of
            // the screen.

            // (xc,yb) is where we are trying to animate to, approximately
            const Int32 xc = (DISPLAY_WIDTH - mWidth) / 2;
            const Int32 yb = DISPLAY_HEIGHT - mHeight;

            Int32 framesLeft = START_TIMEOUT - aFrame;
            Int32 xDist = xc - mXPos;           // note: negative value
            Int32 yDist = yb - mYPos;           // note: positive value

            mDX = xDist / framesLeft;
            mDY = yDist / framesLeft;
            if (xDist && (mDX <= 0)) mDX = -1;
            if (yDist && (mDY <= 0)) mDY = 1;

            TransparentAnimatedSurface::Animate(aFrame, aBounds);
            return;
        }

        // After the time elapses we don't move unless the joystick moves us
        mDX = mDY = 0;
    }

    void MoveBy(Int32 aDX, Int32 aDY, const TwGfxRectType* aBounds) {
        if (mFrame >= START_TIMEOUT) {
            mDX = aDX;
            MovingAnimation(aBounds);
            mDX = 0;
        }
    }

protected:
    UInt32 mFrame;
};

class TapwaveSurface : public StationaryBlendedSurface {
public:
    TapwaveSurface(Int32 aX, Int32 aY)
        : StationaryBlendedSurface(aX, aY, MAKE_FIXED_POINT(14,1), MAKE_FIXED_POINT(-1,8))
    {
    }
};

//----------------------------------------------------------------------

class Zing : public GenericApp {
public:
    Zing() : GenericApp(0) {
    }

    virtual ~Zing() {
    }

    virtual void AppStart() {
        SysSetOrientation(sysOrientationLandscape);
        PINSetInputAreaState(pinInputAreaHide);
        GenericApp::AppStart();
    }

    typedef struct {
        Int32 mJoystickX;
        Int32 mJoystickY;
    } JoystickEvent;

    virtual void AppBegin() {
        Int32 inputFormats[] = { twInputNavX, twInputNavY };

        xassert(TwGfxOpen(&mGfxLib, NULL));

        CreateComposeSurface();

        buildTapwaveSurface();
        buildGoSurface();
        buildDoSurface();
        buildPlaySurface();

        JpegLoader::LoadJpeg(mGfxLib, 1, &mBgImageSurface, &mBgImageInfo);

// List of key bindings
#define rotateLeftKey   keyBitHard1 // polled every game period
#define rotateRightKey  keyBitHard2 // polled every game period
#define shootKey        keyBitHard3 // polled every game period
#define thrustKey       keyBitHard4 // polled every game period
#define keysAllowedMask (rotateLeftKey | rotateRightKey | shootKey | thrustKey )

        // Set the keys we poll to not generate events.  This saves cpu cycles
        // by avoiding the events flowing through the event loop which we will 
        // ignore anyways.
        KeySetMask(~keysAllowedMask);

        TwInputOpen(&mInputQueue, "twinput", "r");

        mInputFormat = new Int32[sizeof(inputFormats)/sizeof(inputFormats[0])];
        MemMove(mInputFormat, inputFormats, sizeof(inputFormats));
        TwInputSetFormat(mInputQueue, mInputFormat, sizeof(inputFormats));
            
        // Activating the queue stops the joystick from generating
        // keyDownEvents.  If this is not done, then every direction
        // visited while polling will cause a corresponding keyDownEvent
        // in that direction, and if the polling duration exceeds 
        // the keyDown repeat duration, then a repeating keyDownEvent 
        // will be generated too.
        TwInputActivate(mInputQueue);
    }

    void buildGoSurface() {
        const Int32 xr = (DISPLAY_WIDTH - TAPWAVE_WIDTH) / 2 + TAPWAVE_WIDTH;
        const Int32 yb = (DISPLAY_HEIGHT - TAPWAVE_HEIGHT) / 2 + TAPWAVE_HEIGHT;
        const Int32 x = xr - 10 - PLAY_WIDTH - 10 - DO_WIDTH - 10 - GO_WIDTH;
        const Int32 y = yb + 10;

        Int32 dx = 1 + random() % 4;
        if (random() & 1) dx = -dx;
        Int32 dy = 1 + random() % 4;
        if (random() & 1) dy = -dy;

        GoSurface* s = new GoSurface(x, y, dx, dy, TwGfxComponentsToPackedRGB(255, 0, 0));
        s->Init(mGfxLib, GoBitmapFamily, GoingBitmapFamily, GoneBitmapFamily);
        mGoSurface = s;
    }

    void buildDoSurface() {
        const Int32 xr = (DISPLAY_WIDTH - TAPWAVE_WIDTH) / 2 + TAPWAVE_WIDTH;
        const Int32 yb = (DISPLAY_HEIGHT - TAPWAVE_HEIGHT) / 2 + TAPWAVE_HEIGHT;
        const Int32 x = xr - 10 - PLAY_WIDTH - 10 - DO_WIDTH;
        const Int32 y = yb + 10;

        DoSurface* s = new DoSurface(x, y, TwGfxComponentsToPackedRGB(255, 0, 0));
        s->Init(mGfxLib, DoBitmapFamily);
        mDoSurface = s;
    }

    void buildPlaySurface() {
        const Int32 xr = (DISPLAY_WIDTH - TAPWAVE_WIDTH) / 2 + TAPWAVE_WIDTH;
        const Int32 yb = (DISPLAY_HEIGHT - TAPWAVE_HEIGHT) / 2 + TAPWAVE_HEIGHT;
        const Int32 x = xr - 10 - PLAY_WIDTH;
        const Int32 y = yb + 10;

        PlaySurface* s = new PlaySurface(x, y, TwGfxComponentsToPackedRGB(255, 0, 0));
        s->Init(mGfxLib, PlayBitmapFamily);
        mPlaySurface = s;
    }

    void buildTapwaveSurface() {
        const Int32 xc = (DISPLAY_WIDTH - TAPWAVE_WIDTH) / 2;
        const Int32 yt = (DISPLAY_HEIGHT - TAPWAVE_HEIGHT) / 2;

        TapwaveSurface* s = new TapwaveSurface(xc, yt);
        s->Init(mGfxLib, TapwaveBitmapFamily);
        mTapwaveSurface = s;
    }

    virtual void AppEnd() {
        delete mGoSurface;
        delete mDoSurface;
        delete mPlaySurface;
        delete mTapwaveSurface;

        TwInputClose(mInputQueue);
        delete mInputFormat;
        TwGfxClose(mGfxLib);
    }

    virtual Boolean AppHandleEvent(EventType* aEvent) {
        Boolean handled = false;

        switch (aEvent->eType) {
          case nilEvent:
            TwInputPoll(mInputQueue, (Int32 *) &mJoystickEvent, sizeof(mJoystickEvent));
            ProcessJoystickChange();
            // fall through

          case frmUpdateEvent:
            {
                TwGfxPointType destLocation = {0, 0};
                TwGfxSurfaceType* displaySurface;

                // Get palmos display surface:
                xassert(TwGfxGetPalmDisplaySurface(mGfxLib, &displaySurface));

                // compose scene
                ComposeScene();

                // Wait for vertical blank
                xassert(TwGfxWaitForVBlank(mGfxLib));

                // Blit display buffer to screen:
                xassert(TwGfxBitBlt(displaySurface, &destLocation, mComposeSurf, &mDisplayArea));
                handled = true;
            }
            break;

          case winExitEvent:
            if (mInputQueue) {
                TwInputDeactivate(mInputQueue);
            }

            // Make sure handled is false, for documentation reasons: we need the system to do
            // some work too.
            handled = false;
            break;

          case winEnterEvent:
            if (mInputQueue) {
                TwInputActivate(mInputQueue);
            }

            // Make sure handled is false, for documentation reasons: we need the system to do
            // some work too.
            handled = false;
            break;

          default:
            break;
        }

        if (!handled) {
            // If we don't handle the event, maybe the GenericApp class will handle it for us
            return GenericApp::AppHandleEvent(aEvent);
        }
        return handled;
    }

    virtual void HandleResizeEvent() {
        FreeComposeSurface();
        CreateComposeSurface();
    }

    static Int32 MapJoystickValue(Int32 aValue) {
        Boolean negative = false;
        if (aValue < 0) {
            aValue = -aValue;
            negative = true;
        }

        // compute log2 of the raw value
        Int32 result = 0;
        if (aValue >> 16) {
            result += 16;
            aValue >>= 16;
        }
        if (aValue >> 8) {
            result += 8;
            aValue >>= 8;
        }
        if (aValue >> 4) {
            result += 4;
            aValue >>= 4;
        }
        if (aValue >> 2) {
            result += 2;
            aValue >>= 2;
        }
        if (aValue >> 1) {
            result += 1;
        }

        // reduce range to keep joystick speed "sensible"
        result = result * 2 / 3;                // => multiply by 2/3

        return negative ? -result : result;
    }

    void ProcessJoystickChange() {
        Int32 dx = MapJoystickValue(mJoystickEvent.mJoystickX);
        Int32 dy = MapJoystickValue(mJoystickEvent.mJoystickY);
        mPlaySurface->MoveBy(dx, dy, &mDisplayArea);

        // Some disabled debugging code to see if the MapJoystickValue produces sensible
        // results. This is an example of how to do on-screen debugging.
        if (false) {
            char chbuf[50];
            snprintf(chbuf, sizeof(chbuf), "%ld,%ld => %ld,%ld",
                     mJoystickEvent.mJoystickX, mJoystickEvent.mJoystickY,
                     dx, dy);
            WinPaintChars(chbuf, strlen(chbuf), 5, 5);
        }
    }

    // If this were more general code, the background animator would probably be just another
    // subclass of the AnimatedSurface class...but it's not...
    void ComposeScene() {
        TwGfxRectType r;
        TwGfxPointType dp = { 0, 0 };

        Int32 cx = mBgImageInfo.width / 2;
        Int32 x0 = cx - mDisplayArea.w / 2;

        xassert(TwGfxFillRect(mComposeSurf, &mDisplayArea, TwGfxComponentsToPackedRGB(0, 255, 0)));

        // Turn the background image into an "infinite" looping image with no seams. I do this by
        // drawing subsets of the image at most twice with one drawn mirrored using
        // TwGfxTransformBlt. This logic assumes that the background image height is >= viewport
        // height.
        Int32 y0 = mDY;
        Int32 y1 = mDY + mDisplayArea.h;
        Int32 bgImageHeight = mBgImageInfo.height;
        Int32 bgImageHeight2 = 2 * bgImageHeight;

        // coordinates from 0 to bgImageHeight-1 draw the bg image normally
        // coordinates from bgImageHeight to bgImageHeight*2-1 draw the bg image mirrored vertically
        // coordinates from bgImageHeight*2 to bgImageHeight*3-1 draw the bg image normally
        // etc.
        //
        // Once mDY reaches >= bgImageHeight*2 we reset it back to approximately zero by
        // subtracting off bgImageHeight*2
        if (y1 <= bgImageHeight) {
            // viewport overlaps just the normal image
            TwGfxMakeRect(r, x0, y0, mDisplayArea.w, mDisplayArea.h);
            TwGfxBitBlt(mComposeSurf, &dp, mBgImageSurface, &r);
        }
        else if (y0 < bgImageHeight) {
            // viewport is straddling both the normal image and the mirrored area
            Int32 h1 = bgImageHeight - y0;  // height of part inside the normal area
            Int32 h2 = mDisplayArea.h - h1;  // height of part inside the mirrored area
            TwGfxPointType p;

            TwGfxMakeRect(r, x0, y0, mDisplayArea.w, h1);
            TwGfxBitBlt(mComposeSurf, &dp, mBgImageSurface, &r);

            TwGfxMakePoint(p, 0, h1);
            TwGfxMakeRect(r, x0, bgImageHeight - h2, mDisplayArea.w, h2);
            TwGfxTransformBlt(mComposeSurf, &p, mBgImageSurface, &r,
                              twGfxRotateNone, twGfxMirrorVertical);
        }
        else if (y1 <= bgImageHeight2) {
            // viewport overlaps just the mirrored area
            TwGfxMakeRect(r, x0, bgImageHeight2 - y0 - mDisplayArea.h, mDisplayArea.w, mDisplayArea.h);
            TwGfxTransformBlt(mComposeSurf, &dp, mBgImageSurface, &r,
                              twGfxRotateNone, twGfxMirrorVertical);
        }
        else {
            // viewport is straddling both the mirrored area and the normal area
            Int32 h1 = bgImageHeight2 - y0; // height of part inside the mirrored area
            Int32 h2 = mDisplayArea.h - h1;  // height of part inside the normal area
            TwGfxPointType p;

            TwGfxMakeRect(r, x0, 0, mDisplayArea.w, h1);
            TwGfxTransformBlt(mComposeSurf, &dp, mBgImageSurface, &r,
                              twGfxRotateNone, twGfxMirrorVertical);

            TwGfxMakePoint(p, 0, h1);
            TwGfxMakeRect(r, x0, 0, mDisplayArea.w, h2);
            TwGfxBitBlt(mComposeSurf, &p, mBgImageSurface, &r);
        }

        mDY += 5;
        if (mDY >= bgImageHeight2) {
            // we've wrapped so reduce mDY back to a matching location in the normal area
            mDY -= bgImageHeight2;
        }

        // render surfaces, in the correct order
        mTapwaveSurface->Compose(mComposeSurf);
        mDoSurface->Compose(mComposeSurf);
        mGoSurface->Compose(mComposeSurf);
        mPlaySurface->Compose(mComposeSurf);

        // See if go & play intersect
        Int32 bounceAmount = 0;
        bool bouncey = mGoSurface->Intersects(mPlaySurface);
        if (bouncey) {
            Int32 goCX = mGoSurface->x() + mGoSurface->w() / 2;
            Int32 playCX = mPlaySurface->x() + mPlaySurface->w() / 2;
            bounceAmount = goCX - playCX;
        }
        bool action = mGoSurface->Intersects(mDoSurface);

        // call the animation logic for each surface
        mTapwaveSurface->Animate(mFrame, &mDisplayArea);
        mGoSurface->Animate(mFrame, &mDisplayArea, bouncey, bounceAmount);
        mDoSurface->Animate(mFrame, &mDisplayArea, action);
        mPlaySurface->Animate(mFrame, &mDisplayArea);

        mFrame++;
    }

    void CreateComposeSurface() {
        if (mGfxLib != NULL) {
            UInt32 width, height;
            WinSetCoordinateSystem(kCoordinatesNative);
            xassert(WinScreenMode(winScreenModeGet, &width, &height, NULL, NULL));
            WinSetCoordinateSystem(kCoordinatesStandard);

            TwGfxSurfaceInfoType surfInfo;
            surfInfo.size = sizeof(surfInfo);
            surfInfo.width = width;
            surfInfo.height = height;
            surfInfo.location = twGfxLocationAcceleratorMemory;
            surfInfo.pixelFormat = twGfxPixelFormatRGB565;
            xassert(TwGfxAllocSurface(mGfxLib, &mComposeSurf, &surfInfo));

            mDisplayArea.w = width;
            mDisplayArea.h = height;
        }
    }

    void FreeComposeSurface() {
        if (mComposeSurf != NULL) {
            TwGfxFreeSurface(mComposeSurf);
            mComposeSurf = NULL;
        }
    }

protected:
    TwGfxType* mGfxLib;

    TwGfxSurfaceType* mBgImageSurface;
    TwJpgImageInfoType mBgImageInfo;

    GoSurface* mGoSurface;
    DoSurface* mDoSurface;
    PlaySurface* mPlaySurface;
    TapwaveSurface* mTapwaveSurface;

    TwGfxSurfaceType* mComposeSurf;

    TwGfxRectType mDisplayArea;

    Int32 mDY;
    UInt32 mFrame;

    TwInputHandle mInputQueue;
    Int32* mInputFormat;
    JoystickEvent mJoystickEvent;
};

//----------------------------------------------------------------------

// Palm entry point

extern "C" UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
    if (cmd == sysAppLaunchCmdNormalLaunch) {
        gApp = new Zing();
        gApp->Launch();
        delete gApp;
    }

    return 0;
}
