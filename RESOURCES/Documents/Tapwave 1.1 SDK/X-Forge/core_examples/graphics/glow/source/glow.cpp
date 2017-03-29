/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief Glow (render to surface) example.
 * 
 * $Id: glow.cpp,v 1.6 2003/04/16 09:35:49 jari Exp $
 * $Date: 2003/04/16 09:35:49 $
 * $Revision: 1.6 $
 *
 * This example demonstrates a neat, but horribly slow way of
 * using setRenderTarget() to create a crude glow special effect.
 */

#include <xforge.h>
// Common code to many examples: builds cube vertex buffer.
#include "../../common/source/buildcube.h"
// Common code to many examples: sets up viewport & matrices.
#include "../../common/source/cubeorbit.h"


// Application class, also acting as input and renderer.
class MyApp : public XFcApp, public XFcInput, public XFcRenderer
{
public:    
    // Renderer function which will be called in every frame.
    virtual void render();
    // Called by XFcCore when stylus or mouse button is lifted.
    virtual void onPointerUp(INT32 aX, INT32 aY);
    // Called by XFcCore when a key is released.
    virtual void onControlUp(INT32 aKey); 
    // Called when application is started.
    virtual void onAppInit();
    // Called when application is terminated.
    virtual void onAppDeinit();
    
    // Pointer to X-Forge core graphics library.
    XFcGL *mGL;
    // Pointer to vertex buffer.
    XFcGLVertexBuffer *mVB;
    // Vertex buffer where most faces are black.
    XFcGLVertexBuffer *mVBBlack;
    // Effect surfaces (used as render target).
    XFcGLSurface *mEffect;
    XFcGLSurface *mEffect2;
};


// Rendering function of the application
void MyApp::render()
{
    // Make the cube rotate - common code, see common/source/cubeorbit.cpp
    xfCubeOrbit(mGL);
    
    // Cull (do not draw for optimization) every clockwise triangle.
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_CW);
    
    // Set for matte colours (colours are ignored with texture).
    mGL->setStateI(XFCGLRS_SHADING, XFCGLSHADE_MATTE);
    
    
    mGL->setRenderTarget(mEffect);
    
    // Define viewport; objects in X = [0..239], Y = [0..319], Z = [1..1000] will be drawn.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = 1;
    vp.mMaxZ = 1000;
    
    // Set viewport.
    mGL->setViewport(vp);
    
    mEffect->drawFilledRect(0, 0, XFcCore::getDeviceWidth(), XFcCore::getDeviceHeight(), 0xff000000);
    mEffect->drawFilledRect(XFcCore::getDeviceWidth() / 2,
                            XFcCore::getDeviceHeight() / 2,
                            XFcCore::getDeviceWidth() / 8,
                            XFcCore::getDeviceHeight() / 8,
                            0xffffffff);
    
    // Start rendering section.
    mGL->beginRender();
    
    mGL->renderPrimitive(mVBBlack, XFCGLPT_TRIANGLELIST, 0, 36, 0, 36, NULL);
    
    // End render (does actual rendering).
    mGL->endRender();
    
    mEffect2->drawFilledRect(0, 0, XFcCore::getDeviceWidth(), XFcCore::getDeviceHeight(), 0xff000000);

    mEffect2->drawImageBlend(mEffect, -1, -1, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect,  1,  1, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect,  1, -1, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect, -1,  1, XFCBLEND_ADD, 0x3f);
    
    mEffect2->drawImageBlend(mEffect, -2,  0, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect,  2,  0, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect,  0, -2, XFCBLEND_ADD, 0x3f);
    mEffect2->drawImageBlend(mEffect,  0,  2, XFCBLEND_ADD, 0x3f);

    mGL->setRenderTarget(NULL);

    // Define viewport; objects in X = [0..239], Y = [0..319], Z = [1..1000] will be drawn.
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = 1;
    vp.mMaxZ = 1000;
    
    // Set viewport.
    mGL->setViewport(vp);          
    
    // Set render primitive(s).
    
    // - Render list of triangles (GLPT_TRIANGLELIST) by using the
    //   vertices. Each three vertices form a triangle.
    // - Start rendering from offset 0 and render 36 vertices.
    // - No additional information for triangles needed.
    
    // Start rendering section.
    mGL->beginRender();
    
    // Render the normal cube in its elliptic track.
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLELIST, 0, 36, 0, 36, NULL);
    
    // End render (does actual rendering).
    mGL->endRender();
    
    mGL->getSecondary()->drawImageBlend(mEffect2,
                                        -2, -2,
                                        XFcCore::getDeviceWidth(), XFcCore::getDeviceHeight(),
                                        XFCBLEND_ADD_FAST, 0);
}


// Called by XFcCore when stylus or mouse button is lifted.
void  MyApp::onPointerUp(INT32 /*aX*/, INT32 /*aY*/)
{
    // Quit the application.
    XFcCore::quit();
}


// Called by XFcCore when a key is released.
void MyApp::onControlUp(INT32 /*aKey*/)
{
    // Don't accept control-up input within the first half a second;
    // this will ignore any accidental key-up messages that may happen
    // if you use the device buttons to launch the application.
    if (XFcCore::getTick() > 500)
        XFcCore::quit();
}


// Called when application is started.
// Creates the cube and sets up the effect surfaces.
void MyApp::onAppInit()
{   
    // For every input action XFcCore calls control.
    XFcCore::setController(this);
    
    // In every frame XFcCore calls cuberender to draw the image.
    XFcCore::setRenderer(this);
    
    // Create renderer.
    mGL = XFcGL::create();
    XFCASSERT(mGL && "Out of memory allocating GL.");
    
    // Call common code to build the cube vertex buffer.
    // (see common/source/buildcube.cpp)
    mVB = xfBuildCube();
    XFCASSERT(mVB && "Out of memory allocating VB.");
    
    mVBBlack = XFcGLVertexBuffer::create(XFCGL_LVERTEX, sizeof(XFcGLLVertex), 36);
    XFCASSERT(mVB && "Out of memory allocating VBBlack.");
    
    // Lock vertex buffers, quit if it fails.
    XFcGLLVertex *v;
    XFcGLLVertex *v2;
    
    v = (XFcGLLVertex *)mVB->lock(0);
    
    XFCASSERT(v && "Failed to lock vertex buffer.");
    if (!v)
        XFcCore::quit();
    
    v2 = (XFcGLLVertex *)mVBBlack->lock(0);
    
    XFCASSERT(v2 && "Failed to lock vertex buffer 2.");
    if (!v2)
        XFcCore::quit();
    
    memcpy(v2, v, sizeof(XFcGLLVertex) * 36);
    
    INT32 i;
    
    for (i = 0; i < 36; i++)
    {
        if (!(v2[i].mDiffuseColor == 0x80ff22ff || v2[i].mDiffuseColor == 0x80ff2222))
            v2[i].mDiffuseColor = 0x80000000;
    }
    
    // Unlock vertex buffers.
    mVB->unlock();
    mVBBlack->unlock();
    
    mEffect = XFcGLSurface::create(XFcCore::getDeviceWidth() / 4, XFcCore::getDeviceHeight() / 4);
    mEffect2 = XFcGLSurface::create(XFcCore::getDeviceWidth() / 4, XFcCore::getDeviceHeight() / 4);
    
    XFCASSERT(mEffect && "Failed to allocate effect buffer.");
    if (!mEffect)
        XFcCore::quit();
    
    XFCASSERT(mEffect2 && "Failed to allocate second effect buffer.");
    if (!mEffect2)
        XFcCore::quit();
}


// Called when application is terminated.
// Frees the allocated memory.
void MyApp::onAppDeinit()
{   
    delete mVB;
    delete mVBBlack;
    delete mEffect2;
    delete mEffect;
    delete mGL;
}



/*
 * Initialization of the application works via two global functions:
 *
 * void xfcAppPref(XFcAppPrefs &xfcAppPrefs)
 * - Specifies the system resources application will use.
 * 
 * INT xfcAppInit()
 * - Initializes the application.
 */


// Initialize application's resource allocation:
// Total memory is 1M from which resources will take a maximum of 1M.
void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = 1 * 1024 * 1024;   // Total memory
    aAppPrefs.mResourceMemoryLimit = 1 * 1024 * 1024;// Max. memory resources may take
    aAppPrefs.mUID = 0x101F9048; // Symbian application unique ID
    aAppPrefs.mMinimumExtraMemory = 128 * 1024; // Minimum extra free memory on the system
}


// Initializes the application.
INT xfcAppInit() 
{
    //  We could use xfcUseDefaults() here to link with all typically used
    //  core features, which would lead to an executable size of about
    //  346k on arm release on wince..
    //xfcUseDefaults();
    //  but we'll use only the bits that are actually used, resulting in
    //  exe size of about 341k. Note that since zlib is not used, the dll is
    //  also not needed.
    xfcUseGLDefault(); 
    //  Compiling without GLDefault would result in executable size of 
    //  about 241k.
    //  One could, of course, use xfcUseGLDefaultFSAA() instead, (343k)
    //xfcUseGLDefaultFSAA();
    //  which links to all the code that xfcUseGLDefault() does plus then some,
    //  but does not initialize the default GL device. The resulting executable
    //  shows just a black screen since the core, by default, prefers even the
    //  stub device over the FSAA device. To make the GL use the FSAA device, 
    //  you'll have to add 101 as a parameter to the XFcGL::create() call, above.
    //  (this will make the GL select the first initialized GL device. To do things
    //  in a correct way, you should first initialize the GL, then ask for the list
    //  of available devices, iterate through them, checking the features that you
    //  want (in this case, FSAA enabled flag), and then use that devices' id to 
    //  recreate the device).
    
    new MyApp;
    
    return 0;
}
