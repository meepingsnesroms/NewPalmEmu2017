#include <xforge.h>
#include <xfcore/XFcPrimitiveTranslator.h>
#include <xfcore/XFcPrimitiveShapes.h>
#include <xfcore/XFcPrimitiveDrawFiller.h>
#include <xfcore/XFcPrimitiveDrawGradientFiller.h>
#include <xfcore/XFcPixelBlender.h>
#include "button.h"

/*
 * This example demonstrates the use of gradients. Note that gradients are fairly slow,
 * so in real-life application it is better to pre-render graphics that use gradients
 * to bitmaps (and convert them to RLE-sprites for even faster rendering). The example
 * also demonstrates how to use XFcPrimitiveShapes class for rendering simple 2D primitives.
 */

button::button(REAL aXPos, REAL aYPos, REAL aRadius)
{
    // The graphic is defined in 60x60 pixel size.
    REAL scale = aRadius / REALf(60);
    XFcMath::matrixScaling2D(mTransformation,scale);

    // Offset by the position
    XFcVector2 offset = XFcVector2(aXPos, aYPos);
    XFcMath::matrixTranslate2D(mTransformation,offset);

    XFcVector2 center = XFcVector2(REALf(32.5),REALf(32.5));
    XFcVector2 focal = XFcVector2(REALf(32.5),REALf(32.5));
    mRadialFillerA = XFcPrimitiveDrawRadialGradientFiller::create(center, focal, REALf(32.5));
    mRadialFillerA->addGradientStop(REALf(0.8), 0xBF000000);    // 75% black
    mRadialFillerA->addGradientStop(REALf(1), 0x00000000);      // transparent black

    center = XFcVector2(REALf(30),REALf(30));
    focal = XFcVector2(REALf(30),REALf(50));
    mRadialFillerB = XFcPrimitiveDrawRadialGradientFiller::create(center, focal, REALf(30));

    XFcVector2 start = XFcVector2(REALf(30),REALf(0));
    XFcVector2 end = XFcVector2(REALf(30),REALf(60));
    mLinearFiller = XFcPrimitiveDrawLinearGradientFiller::create(start, end);
    mLinearFiller->addGradientStop(REALf(0), 0xCCFFFFFF);       // 80% white
    mLinearFiller->addGradientStop(REALf(0.25), 0x00FFFFFF);    // transparent white
    mLinearFiller->addGradientStop(REALf(0.6), 0x00FFFFFF);     // transparent white
    mLinearFiller->addGradientStop(REALf(1), 0xCCFFFFFF);       // 80% white

    mBrightness = 255;
    mPressed = 0;
}

button::~button()
{
    delete mRadialFillerA;
    delete mRadialFillerB;
    delete mLinearFiller;
}

void button::setPressed(INT aState)
{
    if (aState)
        mPressed = 1;
    else
        mPressed = 0;
}

UINT32 button::calculateBrightness(UINT32 aColor)
{
    return XFcPixelBlender::blendAlphaX888(aColor,0,mBrightness);
}

void button::render(XFcGLSurface *aSurface)
{
    XFcPrimitiveTranslator *translator = XFcCore::getPrimitiveTranslator();
    if (translator == NULL)
        return;

    // Reset the states of the translator
    translator->setStrokeOff();
    translator->setFillRule(XFC_PRIMITIVETRANSLATOR_NONZERO_FILL);
    translator->setFillOpacity(0xff);
    translator->setRenderTarget(aSurface);
    INT32 w = aSurface->getWidth();
    INT32 h = aSurface->getHeight();
    XFcRectangle rect = XFcRectangle(0,0,w,h);
    translator->setClipRect(&rect);

    translator->setTransformation(mTransformation);

    translator->setFillGradient(mRadialFillerA);
    XFcPrimitiveShapes::circle(translator,REALf(35),REALf(35),REALf(32.5));

    if (mPressed)
    {
        XFcVector2 offset = XFcVector2(REALf(2.5),REALf(2.5));
        XFcMatrix3 transformation = mTransformation;
        XFcMath::matrixTranslate2D(transformation,offset);
        translator->setTransformation(transformation);
        mBrightness = 255;
    }
    else
    {
        INT32 tick = XFcCore::getTick();
        REAL brightness = (XFcMath::sin(REALf(0.005) * tick) + REALi(3)) / 4;
        mBrightness = (INT32)(brightness * 255);
    }

    mRadialFillerB->resetGradient();
    mRadialFillerB->addGradientStop(REALf(0), calculateBrightness(0xFFFF3F1F));
    mRadialFillerB->addGradientStop(REALf(0.5), calculateBrightness(0xFFDD1F00));
    mRadialFillerB->addGradientStop(REALf(0.95), calculateBrightness(0xFF770D00));
    mRadialFillerB->addGradientStop(REALf(1), calculateBrightness(0xFF220F00));

    translator->setFillGradient(mRadialFillerB);
    XFcPrimitiveShapes::circle(translator,REALf(30),REALf(30),REALf(30));

    translator->setFillGradient(mLinearFiller);
    XFcPrimitiveShapes::circle(translator,REALf(30),REALf(30),REALf(28));   
}
