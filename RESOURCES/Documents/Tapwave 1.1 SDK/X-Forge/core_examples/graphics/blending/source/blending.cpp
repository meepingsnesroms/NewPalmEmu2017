/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief Blending example.
 * 
 * $Id: blending.cpp,v 1.7 2003/04/16 09:35:49 jari Exp $
 * $Date: 2003/04/16 09:35:49 $
 * $Revision: 1.7 $
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
    // Pointer to texture used in the cube.
    XFcGLTexture *mTexture;  
};


// Rendering function of the application.
void MyApp::render()
{
    // Make the cube rotate - common code, see common/source/cubeorbit.cpp
    xfCubeOrbit(mGL);

    // Start rendering section.
    mGL->beginRender();
  
    // Do not use culling, because we are dealing with transparent objects.
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_NONE);
  
    // Do not blend the 3D-sprite.
    mGL->setStateI(XFCGLRS_ALPHABLEND, 0);

    mGL->setTexture(mTexture);
  
    // Draw 3D sprite, which moves along z-axis in space.
    // - Sprites height and width will be 128
    // - Draw the whole texture: (U0,V0) = 0,0  and (U1,V1) = 1,1;
    mGL->drawSprite3dBillboard(0, 0, 10 * sin(XFcCore::getTick() * 0.000234f),
                               10, 10, 0, 0, 1, 1, NULL);
  
  
    // Turn on blending (to turn off, use parameter 0).
    mGL->setStateI(XFCGLRS_ALPHABLEND, 1);
  
    // Use alpha-blending.
    // Look for more blending options from the X-Forge Guide.
    mGL->setStateI(XFCGLRS_SRCBLEND, XFCBLEND_SRCALPHA);
    mGL->setStateI(XFCGLRS_TGTBLEND, XFCBLEND_INVSRCALPHA);
  
  
    // Set render primitive(s).
  
    // - Render list of triangles (GLPT_TRIANGLELIST) by using the
    //   vertices. Each three vertices form a triangle.
    // - Start rendering from offset 0 and render 36 vertices.
    // - No additional information for triangles needed.
  
    // Render the normal cube in its elliptic track.
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLELIST, 0, 36, 0, 36, NULL);
  
    // Inverse cube's World-matrix to get coordinates and rotation for another cube.
    XFcMatrix4 matrixWorld;
    mGL->getMatrix(XFCGLMAT_WORLD, matrixWorld);
    XFcMath::matrixInverseFast(matrixWorld);
  
    // Set the new matrix. As the world matrix was just inversed for
    // the use of the second cube, its track will be quite weird.
    mGL->setMatrix(XFCGLMAT_WORLD, matrixWorld);
  
    // Draw the second cube in its weird track.
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLELIST, 0, 36, 0, 36, NULL);
  
    // End render (does actual rendering).
    mGL->endRender();
}


// Called by XFcCore when stylus or mouse button is lifted.
void MyApp::onPointerUp(INT32 /*aX*/, INT32 /*aY*/)
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
// Initializes the texture and creates the cube.
void MyApp::onAppInit()
{   
    // For every input action XFcCore calls control.
    XFcCore::setController(this);
    
    // In every frame XFcCore calls cuberender to draw the image.
    XFcCore::setRenderer(this);

    // Initialize texture. 
    // Texture must have a resolution of 256x256 or less, and the
    // dimensions must be of powers of two. The format must be 
    // one that is supported by the image loader; PCX and TGA plugins
    // are defaultly enabled in the core.
    // Note that if the texture file is not found, mTexture is set to 
    // NULL, which results in rendering of the faces as if no 
    // texturing was wanted in the first place.
    mTexture = XFcGLTextureFromFile::create("dirty.pcx");
    
    // Create renderer.
    mGL = XFcGL::create();
    XFCASSERT(mGL && "Out of memory allocating GL.");

    // Call common code to build the cube vertex buffer.
    // (see common/source/buildcube.cpp)
    mVB = xfBuildCube();
    XFCASSERT(mVB && "Out of memory allocating VB.");
}


// Called when application is terminated.
// Frees the allocated memory.
void MyApp::onAppDeinit()
{   
    delete mVB;
    delete mTexture;
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


// Initializes application's resource allocation:
// Total memory is 1M from which resources will take a maximum of 1M.
void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = 1 * 1024 * 1024;   // Total memory
    aAppPrefs.mResourceMemoryLimit = 1 * 1024 * 1024;// Max. memory resources may take
    aAppPrefs.mUID = 0x101F4F86; // Symbian application unique ID
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
    xfcUseImageFilterPCX();
    //  The ImageFilterPCX is needed to load the textures. If you disable
    //  the above line, the texture loading will fail and the resulting 
    //  application will act as if there wasn't any textures to begin with.
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
