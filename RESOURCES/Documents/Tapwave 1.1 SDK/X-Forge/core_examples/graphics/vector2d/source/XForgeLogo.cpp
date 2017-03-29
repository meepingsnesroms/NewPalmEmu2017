#include <xforge.h>
#include <xfcore/XFcPrimitiveTranslator.h>
#include <xfcore/XFcPrimitiveShapes.h>
#include <xfcore/XFcPixelBlender.h>
#include "XForgeLogo.h"

XForgeLogo::XForgeLogo()
{
    // This transformation translates and scales the logo to 256 unit size and
    // centers to origin.
    XFcMath::matrixScaling2D(mTransformation,REALf(0.75));
    XFcVector2 offset = XFcVector2(REALi(-148),REALi(-160));
    XFcMath::matrixTranslate2D(mTransformation,offset);

    mZoom = REALi(1);

    mFade = 255;
    mFadeColor = 0;
}

XForgeLogo::~XForgeLogo()
{

}

void XForgeLogo::setZoom(REAL aZoom)
{
    mZoom = aZoom;
}

void XForgeLogo::setFade(UINT32 aFadeColor, INT32 aFade)
{
    if (aFade < 0)
        mFade = 0;
    else if (aFade > 255)
        mFade = 255;
    else
        mFade = aFade;

    mFadeColor = (aFadeColor & 0xffffff) | 0xff000000;
}

UINT32 XForgeLogo::calculateFade(UINT32 aColor)
{
    return XFcPixelBlender::blendAlphaX888(aColor | 0xff000000,mFadeColor,mFade);
}

void XForgeLogo::render(XFcGLSurface *aSurface)
{    
    XFcPrimitiveTranslator *translator = XFcCore::getPrimitiveTranslator();
    if (translator == NULL)
        return;

    INT32 w = aSurface->getWidth();
    INT32 h = aSurface->getHeight();

    REAL minSize;
    if (w < h)
        minSize = w;
    else
        minSize = h;

    REAL scale = (minSize * mZoom) / 256;

    XFcMatrix3 transformation;

    XFcVector2 offset = XFcVector2(w/2,h/2);
    XFcMath::matrixTranslation2D(transformation,offset);
    XFcMath::matrixScale2D(transformation,scale);

    transformation = mTransformation * transformation;

    // Reset the states of the translator
    translator->setStrokeOff();
    translator->setFillRule(XFC_PRIMITIVETRANSLATOR_NONZERO_FILL);
    translator->setFillOpacity(0xff);
    translator->setRenderTarget(aSurface);
    XFcRectangle rect = XFcRectangle(0,0,w,h);
    translator->setClipRect(&rect);
    translator->setTransformation(transformation);

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(0), REALf(327.668));
    translator->horizontalLineToRelative(REALf(6.818));
    translator->lineToRelative(REALf(16.306), REALf( -17.342));
    translator->lineToRelative(REALf(16.544), REALf(17.342));
    translator->horizontalLineToRelative(REALf(6.58));
    translator->lineToAbsolute(REALf(27.225), REALf(307.9));
    translator->lineToRelative(REALf(16.878), REALf( -17.602));
    translator->horizontalLineToRelative(REALf(-6.437));
    translator->lineToAbsolute(REALf(23.124), REALf(305.32));
    translator->lineToRelative(REALf(-14.352), REALf( -15.02));
    translator->horizontalLineToAbsolute(REALf(2.145));
    translator->lineToRelative(REALf(16.878), REALf(17.6));
    translator->lineToAbsolute(REALf(0), REALf(327.668));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(51.156), REALf(316.057));
    translator->horizontalLineToRelative(REALf(13.35));
    translator->verticalLineToRelative(REALf(-4.131));
    translator->horizontalLineToRelative(REALf(-13.35));
    translator->verticalLineToAbsolute(REALf(316.057));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(72.987), REALf(327.668));
    translator->horizontalLineToRelative(REALf(4.672));
    translator->verticalLineToAbsolute(REALf(310.48));
    translator->horizontalLineToRelative(REALf(27.129));
    translator->verticalLineToRelative(REALf(-4.129));
    translator->horizontalLineToAbsolute(REALf(77.659));
    translator->verticalLineToAbsolute(REALf(294.43));
    translator->horizontalLineToRelative(REALf(28.226));
    translator->verticalLineToRelative(REALf(-4.129));
    translator->horizontalLineToAbsolute(REALf(72.987));
    translator->verticalLineToAbsolute(REALf(327.668));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(151.891), REALf(316.004));
    translator->curveToRelative(REALf(0), REALf(6.502), REALf( -3.624), REALf(7.947), REALf( -8.105), REALf(7.947));
    translator->horizontalLineToRelative(REALf(-18.928));
    translator->curveToRelative(REALf(-4.481), REALf(0), REALf( -8.105), REALf( -1.445), REALf( -8.105), REALf( -7.947));
    translator->verticalLineToRelative(REALf(-14.039));
    translator->curveToRelative(REALf(0), REALf( -6.504), REALf(3.624), REALf( -7.949), REALf(8.105), REALf( -7.949));
    translator->horizontalLineToRelative(REALf(18.928));
    translator->curveToRelative(REALf(4.482), REALf(0), REALf(8.105), REALf(1.445), REALf(8.105), REALf(7.949));
    translator->verticalLineToAbsolute(REALf(316.004));
    translator->closePath();
    translator->moveToAbsolute(REALf(112.08), REALf(314.094));
    translator->curveToRelative(REALf(0), REALf(9.445), REALf(2.956), REALf(13.988), REALf(12.301), REALf(13.988));
    translator->horizontalLineToRelative(REALf(19.882));
    translator->curveToRelative(REALf(9.345), REALf(0), REALf(12.302), REALf( -4.543), REALf(12.302), REALf( -13.988));
    translator->verticalLineToRelative(REALf(-10.219));
    translator->curveToRelative(REALf(0), REALf( -9.445), REALf( -2.957), REALf( -13.986), REALf( -12.302), REALf( -13.986));
    translator->horizontalLineToRelative(REALf(-19.882));
    translator->curveToRelative(REALf(-9.345), REALf(0), REALf( -12.301), REALf(4.541), REALf( -12.301), REALf(13.986));
    translator->verticalLineToAbsolute(REALf(314.094));
    translator->closePath();
    translator->endPath();


    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(164.525), REALf(327.668));
    translator->horizontalLineToRelative(REALf(4.672));
    translator->verticalLineToRelative(REALf(-14.762));
    translator->horizontalLineToRelative(REALf(22.789));
    translator->curveToRelative(REALf(4.244), REALf(0), REALf(6.867), REALf(0.723), REALf(6.867), REALf(6.555));
    translator->verticalLineToRelative(REALf(8.207));
    translator->horizontalLineToRelative(REALf(4.385));
    translator->verticalLineToRelative(REALf(-9.547));
    translator->curveToRelative(REALf(0), REALf( -3.406), REALf( -1.144), REALf( -6.09), REALf( -5.912), REALf( -7.021));
    translator->verticalLineToRelative(REALf(-0.104));
    translator->curveToRelative(REALf(3.576), REALf( -0.359), REALf(6.344), REALf( -1.807), REALf(6.344), REALf( -7.072));
    translator->verticalLineToRelative(REALf(-3.045));
    translator->curveToRelative(REALf(0), REALf( -7.02), REALf( -1.573), REALf( -10.58), REALf( -11.538), REALf( -10.58));
    translator->horizontalLineToRelative(REALf(-27.604));
    translator->verticalLineToRelative(REALf(37.369));
    translator->horizontalLineToAbsolute(REALf(164.525));
    translator->closePath();
    translator->moveToAbsolute(REALf(169.197), REALf(308.777));
    translator->verticalLineToAbsolute(REALf(294.43));
    translator->horizontalLineToRelative(REALf(21.265));
    translator->curveToRelative(REALf(6.866), REALf(0), REALf(8.534), REALf(1.342), REALf(8.534), REALf(5.521));
    translator->verticalLineToRelative(REALf(3.404));
    translator->curveToRelative(REALf(0), REALf(3.926), REALf( -2.193), REALf(5.42), REALf( -7.391), REALf(5.42));
    translator->lineToAbsolute(REALf(169.197), REALf(308.777));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(254.201), REALf(309.141));
    translator->horizontalLineToRelative(REALf(-22.36));
    translator->verticalLineToRelative(REALf(4.129));
    translator->horizontalLineToRelative(REALf(17.688));
    translator->verticalLineToRelative(REALf(3.769));
    translator->curveToRelative(REALf(0), REALf(5.162), REALf( -2.86), REALf(6.916), REALf( -7.533), REALf(6.916));
    translator->horizontalLineToRelative(REALf(-18.262));
    translator->curveToRelative(REALf(-4.48), REALf(0), REALf( -8.104), REALf( -1.445), REALf( -8.104), REALf( -7.947));
    translator->verticalLineToRelative(REALf(-14.039));
    translator->curveToRelative(REALf(0), REALf( -6.504), REALf(3.624), REALf( -7.948), REALf(8.104), REALf( -7.948));
    translator->horizontalLineToRelative(REALf(12.108));
    translator->curveToRelative(REALf(11.538), REALf(0), REALf(13.493), REALf(0.518), REALf(13.493), REALf(7.483));
    translator->horizontalLineToRelative(REALf(4.386));
    translator->verticalLineToRelative(REALf(-1.342));
    translator->curveToRelative(REALf(0), REALf( -8.621), REALf( -6.627), REALf( -10.271), REALf( -12.823), REALf( -10.271));
    translator->horizontalLineToRelative(REALf(-17.642));
    translator->curveToRelative(REALf(-9.347), REALf(0), REALf( -12.301), REALf(4.541), REALf( -12.301), REALf(13.984));
    translator->verticalLineToRelative(REALf(10.223));
    translator->curveToRelative(REALf(0), REALf(9.443), REALf(2.954), REALf(13.984), REALf(12.301), REALf(13.984));
    translator->horizontalLineToRelative(REALf(19.265));
    translator->curveToRelative(REALf(8.629), REALf(0), REALf(11.68), REALf( -3.613), REALf(11.68), REALf( -13.781));
    translator->verticalLineToAbsolute(REALf(309.141));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(262.44), REALf(327.668));
    translator->horizontalLineToRelative(REALf(34.093));
    translator->verticalLineToRelative(REALf(-4.129));
    translator->horizontalLineToRelative(REALf(-29.417));
    translator->verticalLineToRelative(REALf(-13.061));
    translator->horizontalLineToRelative(REALf(28.083));
    translator->verticalLineToRelative(REALf(-4.129));
    translator->horizontalLineToRelative(REALf(-28.083));
    translator->verticalLineToRelative(REALf(-11.92));
    translator->horizontalLineToRelative(REALf(29.227));
    translator->verticalLineToRelative(REALf(-4.129));
    translator->horizontalLineToRelative(REALf(-33.897));
    translator->lineToAbsolute(REALf(262.44), REALf(327.668));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(305.289), REALf(291.338));
    translator->horizontalLineToRelative(REALf(2.214));
    translator->verticalLineToRelative(REALf(-1.236));
    translator->horizontalLineToRelative(REALf(-5.877));
    translator->verticalLineToRelative(REALf(1.236));
    translator->horizontalLineToRelative(REALf(2.214));
    translator->verticalLineToRelative(REALf(6.311));
    translator->horizontalLineToRelative(REALf(1.449));
    translator->verticalLineToAbsolute(REALf(291.338));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(315.606), REALf(291.29));
    translator->horizontalLineToRelative(REALf(0.053));
    translator->lineToRelative(REALf(-0.121), REALf(6.358));
    translator->horizontalLineToRelative(REALf(1.446));
    translator->verticalLineToRelative(REALf(-7.547));
    translator->horizontalLineToRelative(REALf(-2.375));
    translator->lineToRelative(REALf(-2.013), REALf(5.605));
    translator->horizontalLineToRelative(REALf(-0.04));
    translator->lineToRelative(REALf(-2.053), REALf( -5.605));
    translator->horizontalLineToRelative(REALf(-2.324));
    translator->verticalLineToRelative(REALf(7.547));
    translator->horizontalLineToRelative(REALf(1.449));
    translator->lineToRelative(REALf(-0.121), REALf( -6.33));
    translator->horizontalLineToRelative(REALf(0.03));
    translator->lineToRelative(REALf(2.395), REALf(6.33));
    translator->horizontalLineToRelative(REALf(1.298));
    translator->lineToAbsolute(REALf(315.606), REALf(291.29));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0xAEC3D6));
    translator->beginPath();
    translator->moveToAbsolute(REALf(61.796), REALf(277.855));
    translator->lineToAbsolute(REALf(9.997), REALf(232.918));
    translator->lineToRelative(REALf(56.901), REALf( -81.446));
    translator->lineToRelative(REALf(67.26), REALf(18.356));
    translator->lineToAbsolute(REALf(61.796), REALf(277.855));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(87.071), REALf(63.046));
    translator->lineToAbsolute(REALf(30.914), REALf(27.135));
    translator->lineToRelative(REALf(27.829), REALf(52.976));
    translator->lineToAbsolute(REALf(87.071), REALf(63.046));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x3C6993));
    translator->beginPath();
    translator->moveToAbsolute(REALf(247.046), REALf(80.658));
    translator->lineToRelative(REALf(31.388), REALf( -51.682));
    translator->lineToRelative(REALf(-61.982), REALf(36.535));
    translator->lineToAbsolute(REALf(247.046), REALf(80.658));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0xAEC3D6));
    translator->beginPath();
    translator->moveToAbsolute(REALf(90.675), REALf(0));
    translator->lineToAbsolute(REALf(30.914), REALf(27.135));
    translator->lineToRelative(REALf(56.101), REALf(35.968));
    translator->lineToAbsolute(REALf(0.119), REALf(106.392));
    translator->lineToRelative(REALf(54.335), REALf(41.825));
    translator->lineToRelative(REALf(94.937), REALf( -45.166));
    translator->lineToRelative(REALf(85.822), REALf(44.904));
    translator->lineToRelative(REALf(61.242), REALf( -39.733));
    translator->lineToRelative(REALf(-77.746), REALf( -43.289));
    translator->lineToRelative(REALf(59.761), REALf( -35.967));
    translator->lineToRelative(REALf(-57.931), REALf( -28.24));
    translator->lineToRelative(REALf(-69.697), REALf(30.07));
    translator->lineToAbsolute(REALf(90.675), REALf(0));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x3C6993));
    translator->beginPath();
    translator->moveToAbsolute(REALf(149.774), REALf(101.227));
    translator->lineToRelative(REALf(-95.392), REALf(46.95));
    translator->lineToRelative(REALf(79.582), REALf(21.638));
    translator->lineToRelative(REALf(-72.382), REALf(108.08));
    translator->lineToRelative(REALf(88.535), REALf( -55.959));
    translator->lineToRelative(REALf(0.307), REALf(0.217));
    translator->lineToRelative(REALf(2),REALf(-2));
    translator->verticalLineToRelative(REALf(-120.57 + 4));
    translator->lineToRelative(REALf(-2),REALf(-2));
    translator->lineToAbsolute(REALf(149.774), REALf(101.227));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0x2D4D73));
    translator->beginPath();
    translator->moveToAbsolute(REALf(229.706), REALf(278.034));
    translator->lineToRelative(REALf(-65.267), REALf( -108.22));
    translator->lineToRelative(REALf(70.834), REALf( -21.956));
    translator->lineToRelative(REALf(-84.847), REALf( -46.275));
    translator->verticalLineToRelative(REALf(120.571));
    translator->lineToAbsolute(REALf(229.706), REALf(278.034));
    translator->closePath();
    translator->endPath();

    translator->setFillColor(calculateFade(0xAEC3D6));
    translator->beginPath();
    translator->moveToAbsolute(REALf(163.335), REALf(169.814));
    translator->lineToRelative(REALf(66.356), REALf(108.224));
    translator->lineToRelative(REALf(55.778), REALf( -41.459));
    translator->lineToRelative(REALf(-50.534), REALf( -88.696));
    translator->lineToAbsolute(REALf(163.335), REALf(169.814));
    translator->closePath();
    translator->endPath();
}
