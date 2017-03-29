/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief Hexagon example.
 * 
 * $Id: hexagon.cpp,v 1.7 2003/04/16 09:35:49 jari Exp $
 * $Date: 2003/04/16 09:35:49 $
 * $Revision: 1.7 $
 */

#include <xforge.h>


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
};    


// Rendering function of the application.
void MyApp::render()
{ 
    REAL centerX, centerY, dx, dy;
    
    // Simple animation variable.
    INT32 t = XFcCore::getTick() / 10;
    
    // Define viewport.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = 1;
    vp.mMaxZ = 1000;
    
    INT32 halfWidth = XFcCore::getDeviceWidth() / 2;
    INT32 halfHeight = XFcCore::getDeviceHeight() / 2;
    
    // Set viewport.
    mGL->setViewport(vp);
    
    // Clear framebuffer to black.
    mGL->clear();
    
    XFcGLTLVertex *v;

    // Lock vertex buffer, if fails, quit.
    v = (XFcGLTLVertex *)mVB->lock(0);
    
    XFCASSERT(v && "Vertex buffer locking failed.");
    if (!v)
        XFcCore::quit();
    
    centerX = halfWidth;
    centerY = halfHeight;
    dx = (halfWidth / 2) * sin(t / 25.0f);
    dy = (halfWidth / 2) * cos(t / 27.0f);
    
    /*
     * 6 sided polygon is formed of 8 verteces by triangle list
     * 
     *   
     *         6-------7
     *        . .     . .
     *       .   .   .   .
     *      .     . .     .
     *     5-------1-------2,8
     *      .     . .     . 
     *       .   .   .   .
     *        . .     . . 
     *         4-------3              
     */
    
    
    v[0].mX = centerX + dx;                     // 1.
    v[0].mY = centerY + dy;
    v[0].mZ = 100;      // Z-coordinates dont count, we'll just set them to 100.
    v[0].mDiffuseColor = 0xff0000ff;
    
    v[1].mX = v[7].mX = centerX + 50;           // 2,8
    v[1].mY = v[7].mY = centerY;
    v[1].mZ = v[7].mZ = 100;
    v[1].mDiffuseColor = 0xff0000ff;
    v[7].mDiffuseColor = 0xff00ffff;
    
    v[2].mX = centerX + 25;                     // 3.
    v[2].mY = centerY + 43;
    v[2].mZ = 100;
    v[2].mDiffuseColor = 0xffffffff;
    
    v[3].mX = centerX - 25;                     // 4.
    v[3].mY = centerY + 43;
    v[3].mZ = 100;
    v[3].mDiffuseColor = 0x00ffffff;
    
    v[4].mX = centerX - 50;                     // 5.
    v[4].mY = centerY;
    v[4].mZ = 100;
    v[4].mDiffuseColor = 0x0000ffff;
    
    v[5].mX = centerX - 25;                     // 6.
    v[5].mY = centerY - 43;
    v[5].mZ = 100;
    v[5].mDiffuseColor = 0xff8888ff;
    
    v[6].mX = centerX + 25;                     // 7.
    v[6].mY = centerY - 43;
    v[6].mZ = 100;
    v[6].mDiffuseColor = 0x88ff88ff;
    
    // Start rendering section.
    mGL->beginRender();
    
    // Disable culling.
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_NONE);
    
    // Set for gouraud colors (colors are ignored with texture).
    mGL->setStateI(XFCGLRS_SHADING, XFCGLSHADE_GOURAUD);
    
    // Set render primitive(s).
    
    // - Render verteces. First three verteces form the first triangle
    //   and every new vertex in buffer forms a new triangle which is
    //   connected to the first vertex. (GLPT_TRIANGLEFAN)
    // - Start rendering from offset 0 and render 8 vertices.
    // - No additional information for triangles needed.    
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLEFAN, 0, 8, 0, 8, NULL);
    
    // End render (does actual rendering).
    mGL->endRender();
    
    // Unlock vertex buffer.
    mVB->unlock();  
}


// Called by XFcCore when stylus or mouse button is lifted.
void  MyApp::onPointerUp(INT32 /*X*/, INT32 /*Y*/)
{
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
// Creates the object.
void MyApp::onAppInit()
{
    // For every input action XFcCore calls control.
    XFcCore::setController(this);
    
    // In every frame XFcCore calls cuberender to draw the image.
    XFcCore::setRenderer(this);
    
    // Create renderer.
    mGL = XFcGL::create();
    XFCASSERT(mGL && "Failed to create GL.");
    
    // Create a 6 sided fan of 8 TLVERTEX vertices.
    mVB = XFcGLVertexBuffer::create(XFCGL_TLVERTEX, sizeof(XFcGLTLVertex), 8);   
    XFCASSERT(mVB && "Failed to create VB.");
}


// Called when application is terminated.
// Frees the allocated memory.
void MyApp::onAppDeinit()
{
    delete mVB;
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
    aAppPrefs.mUID = 0x101F4F88;
    aAppPrefs.mMinimumExtraMemory = 128 * 1024; // Minimum extra free memory on the system
}


// Initializes the application.
INT xfcAppInit() 
{
    //  We could use xfcUseDefaults() here to link with all typically used
    //  core features, which would lead to an executable size of about
    //  343k on arm release on wince..
    //xfcUseDefaults();
    //  but we'll use only the bits that are actually used, resulting in
    //  exe size of about 335k. Note that since zlib is not used, the dll is
    //  also not needed.
    xfcUseGLDefault(); 
    //  Compiling without GLDefault would result in executable size of 
    //  about 235k.
    //  One could, of course, use xfcUseGLDefaultFSAA() instead, (336k)
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
    //  Note that the FSAA version looks different since the TLVertices work in
    //  screen coordinates.
    
    new MyApp;
        
    return 0;
}
