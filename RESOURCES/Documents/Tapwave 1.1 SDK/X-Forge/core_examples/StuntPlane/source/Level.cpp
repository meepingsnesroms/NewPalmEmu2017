/*! \file
 * Level.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Level.cpp,v 1.6 2003/08/07 07:50:42 lars Exp $
 * $Date: 2003/08/07 07:50:42 $
 * $Revision: 1.6 $
 */

#include <xforge.h>

#include <xfutil/XFuRandom.h>
#include <xfutil/XFuTokenizer.h>
#include <xfutil/XFuDynamicArray.h>

#include "Sprite.h"
#include "Screen.h"
#include "Objects.h"
#include "Level.h"
#include "GameScreen.h"
#include "StuntPlane.h"


// Define this for 50/50 transparent clouds. Might be too slow on some devices.
#define TRANSPARENT_CLOUDS


//! Static creation.
Level * Level::create()
{
    Level *l = new Level();
    XFCASSERT(l);

    l->mSprites = XFuDynamicArray<Sprite *>::create();
    l->mClouds = XFuDynamicArray<Sprite *>::create();
    l->mWinds = XFuDynamicArray<WindParameter *>::create();
    l->mTextures = XFuDynamicArray<TextureInfo *>::create();

    XFCASSERT(l->mSprites && l->mClouds && l->mWinds && l->mTextures);

    return l;
}


Level::Level()
{
    mText = NULL;
    mBackSurf = NULL;
    mCloudTexture = NULL;

    mPlaneSpeed = 128;

    mPlaneRed   = REALf(1.0f);
    mPlaneGreen = REALf(0.0f);
    mPlaneBlue  = REALf(0.0f);
}


Level::~Level()
{
    UINT i;

    // deallocate sprites
    if (mSprites) 
    {
        for (i = 0; i < mSprites->size(); i++)
        {        
            delete mSprites->get(i);
        }
        delete mSprites;
    }

    // deallocate clouds
    if (mClouds) 
    {
        for (i = 0; i < mClouds->size(); i++)
        {        
            delete mClouds->get(i);
        }
        delete mClouds;
    }

    // deallocate wind parameters
    if (mWinds) 
    {
        for (i = 0; i < mWinds->size(); i++)
        {        
            delete mWinds->get(i);
        }
        delete mWinds;
    }
    

    // deallocate textures
    if (mTextures) 
    {
        for (i = 0; i < mTextures->size(); i++)
        {        
            delete mTextures->get(i);
        }
        delete mTextures;
        mTextures = NULL;
    }

    // deallocate remaing stuff.
    delete mText;
    delete mBackSurf;
    delete mCloudTexture;
}


//! Load and parse level definition file.
INT Level::load(INT aLevel)
{
    // Create level name. Assume level%d.txt.
    CHAR levelName[32];
    XFcStringToolkit::format(levelName, XFCSTR("level%d.txt"), aLevel);

    // Read in the whole file.
    CHAR8 *data = (CHAR8 *)XFcFile::getFile(levelName);
    XFCASSERT(data);

    INT32 size = XFcFile::getFileSize(levelName);

    // Make this a zero terminated string.
    data[size - 1] = 0;


    XFuTokenizer lines, row, params;

    // Split into rows.
    lines.tokenize(data, XFCSTR("\r\n"));

    INT l;
    for (l = 0; l < lines.getTokenCount(); l++)
    {
        row.tokenize(lines.getToken(l), XFCSTR("="));

        // Just skip this line if not exactly one '=' character.
        if (row.getTokenCount() != 2) continue;

        // Get parameters.
        params.tokenize(row.getToken(1), XFCSTR(","));
        

        if (row.tokenEqualsNocase(0, XFCSTR("LEVEL")))
        {
            // Get general level information.
            if (params.getTokenCount() != 5) return 0;

            // Load level backdrop.
            mBackSurf = XFcImageLoader::load(params.getToken(0));
            XFCASSERT(mBackSurf);

            mLength = REALi(XFcStringToolkit::toINT32(params.getToken(1)));
            mStartX = REALi(XFcStringToolkit::toINT32(params.getToken(2)));
            mStartY = REALi(XFcStringToolkit::toINT32(params.getToken(3)));

            // Copy level description.
            mText = XFcStringToolkit::copy(params.getToken(4));            
            XFCASSERT(mText);
        }
        else 
        if (row.tokenEqualsNocase(0, XFCSTR("PLANESPEED")))
        {
            if (params.getTokenCount() != 1) return 0;

            mPlaneSpeed = XFcStringToolkit::toFLOAT32(params.getToken(0));
        }
        if (row.tokenEqualsNocase(0, XFCSTR("PLANECOLOR")))
        {
            if (params.getTokenCount() != 3) return 0;

            mPlaneRed = XFcStringToolkit::toFLOAT32(params.getToken(0));
            mPlaneGreen = XFcStringToolkit::toFLOAT32(params.getToken(1));
            mPlaneBlue = XFcStringToolkit::toFLOAT32(params.getToken(2));
        }
        else 
        if (row.tokenEqualsNocase(0, XFCSTR("WIND")))
        {
            /*  Get wind parameters. Multiply by small values so that we can have
             *  reasonable values in the level file.
             */
            if (params.getTokenCount() != 4) return 0;

            WindParameter *w = new WindParameter();

            w->setParameters(XFcStringToolkit::toFLOAT32(params.getToken(0)),
                             XFcStringToolkit::toFLOAT32(params.getToken(1)) * 0.00004f,
                             XFcStringToolkit::toFLOAT32(params.getToken(2)) * PI / 180.0f,
                             XFcStringToolkit::toFLOAT32(params.getToken(3)) * 0.004f);


            if (mWinds->size() == 0 && w->getZ() > 0) 
            {
                // Add a dummy as first wind parameter (at z=0). Used for interpolation.
                WindParameter *dummy = new WindParameter();
                dummy->setParameters(0, 0, 0, 0);
                mWinds->put(dummy);
            }
            
            mWinds->put(w);
        }        
        else 
        if (row.tokenEqualsNocase(0, XFCSTR("CLOUDS")))
        {
            // Get cloud parameters and generate clouds.
            if (params.getTokenCount() != 2) return 0;

            generateClouds(params.getToken(0), XFcStringToolkit::toINT32(params.getToken(1)));
        }
        else 
        if (row.tokenEqualsNocase(0, XFCSTR("HOOP")))
        {
            if (params.getTokenCount() != 8) return 0;

            Hoop *h = new Hoop();
            if (h == NULL) return 0;

            XFcGLTexture *tex = findTexture(params.getToken(0)); 
            if (tex == NULL) return 0;

            h->setTexture(tex);

            h->setLocation(XFcStringToolkit::toINT32(params.getToken(1)),
                           XFcStringToolkit::toINT32(params.getToken(2)),
                           XFcStringToolkit::toINT32(params.getToken(3)));

            h->setHoleParameters(XFcStringToolkit::toFLOAT32(params.getToken(4)),
                                 XFcStringToolkit::toFLOAT32(params.getToken(5)),
                                 XFcStringToolkit::toFLOAT32(params.getToken(6)) * 2);
            
            const CHAR *o = params.getToken(7);

            // find first printable valid character.
            while (*o != 0 && *o <= 32) o++;

            switch (*o) 
            {
                case 'o' : h->setOrientation(SP_HOOP_ANY); break;
                case '-' : h->setOrientation(SP_HOOP_MINUS); break;
                case '/' : h->setOrientation(SP_HOOP_SLASH); break;
                case '|' : h->setOrientation(SP_HOOP_BAR); break;
                case '\\': h->setOrientation(SP_HOOP_BACKSLASH); break;
                case '+' : h->setOrientation(SP_HOOP_PLUS); break;
                case 'x' : h->setOrientation(SP_HOOP_CROSS); break;
                default:
                    return 0;
            }

            // Add to sprite list.
            mSprites->put(h);
        }
        else 
        if (row.tokenEqualsNocase(0, XFCSTR("BONUS")))
        {
                if (params.getTokenCount() != 5) return 0;
            
            Bonus *b = new Bonus();
            if (b == NULL) return 0;


            XFcGLTexture *tex = findTexture(params.getToken(0)); 
            if (tex == NULL) return 0;

            b->setTexture(tex);           

            b->setLocation(XFcStringToolkit::toINT32(params.getToken(1)),
                           XFcStringToolkit::toINT32(params.getToken(2)),
                           XFcStringToolkit::toINT32(params.getToken(3)));

            b->setValue(XFcStringToolkit::toINT32(params.getToken(4)));

            // Add to sprite list.
            mSprites->put(b);
        }
    }
    delete data;

    initWinds();

    return 1;
}


//! Initialize wind interpolation.
void Level::initWinds()
{
    mWindMagnitude = 0;
    mWindDirection = 0;
    mWindGustFactor = 0;

    if (mWinds->size() > 0)
    {        
        // Add dummy wind parameter used for interpolation.
        WindParameter *last = mWinds->get(mWinds->size() - 1);
        WindParameter *w = new WindParameter();

        w->setParameters(mLength + 1000, last->getMagnitude(), last->getDirection(), last->getGustFactor());
        mWinds->put(w);
        
        mFirstWind = 0;
    }
}


//! Interpolate between wind parameters specified at certain locations.
void Level::updateWindParameters(REAL aZ)
{

    if (mWinds == NULL || mWinds->size() < 2) return;

    do 
    {
        if (mWinds->get(mFirstWind + 1)->getZ() < aZ) 
        {
            mFirstWind++;
        }
    } while ((mWinds->get(mFirstWind + 1)->getZ() - mWinds->get(mFirstWind)->getZ()) <= 0);

    WindParameter *first = mWinds->get(mFirstWind);
    WindParameter *second = mWinds->get(mFirstWind + 1);

    // Do linear interpolation of wind parameters.
    REAL interp = (aZ - first->getZ()) / (second->getZ() - first->getZ());

    mWindMagnitude = first->getMagnitude() + (second->getMagnitude() - first->getMagnitude()) * interp;
    mWindDirection = first->getDirection() + (second->getDirection() - first->getDirection()) * interp;
    mWindGustFactor = first->getGustFactor() + (second->getGustFactor() - first->getGustFactor()) * interp;
}


//! Draw backdrop image panned according to current world position.
void Level::drawBackdrop(XFcGL *aGL, REAL mX, REAL mY, INT aNoStatusBar)
{
  
    XFcGLSurface *fb;        

    // Ask GL for the secondary buffer.
    fb = aGL->getSecondary();

    // Draw background image.

    REAL top;
    if (aNoStatusBar) 
    {
        top = 0;
    }
    else 
    {
        top = 24;
    }

    // Some slightly messy calculations...
    fb->drawImage(mBackSurf, 0, top,
                  XFcRectangle((SP_BACKDROP_WIDTH / 4) + mX * REALi(SP_BACKDROP_WIDTH / 8) / REALi(SP_LEVEL_MAX_XY / 2), 
                               (SP_BACKDROP_HEIGHT / 4) - mY * REALi(SP_BACKDROP_HEIGHT / 4) / REALi(SP_LEVEL_MAX_XY), 
                                SP_BACKDROP_WIDTH / 2, (SP_BACKDROP_HEIGHT - top) / 2),
                  XFcCore::getDeviceWidth(),
                  XFcCore::getDeviceHeight() - top);
}


//! Render the clouds.
void Level::renderClouds(XFcGL *aGL, REAL mX, REAL mY, REAL mZ)
{
    UINT i;
    Sprite *spr;

    // Render cloud sprites.

#ifdef TRANSPARENT_CLOUDS
    // Enable alpha blending for transparency.
    aGL->setStateI(XFCGLRS_ALPHABLEND, 1);   
#endif

    aGL->setStateI(XFCGLRS_SRCBLEND, XFCBLEND_SRCALPHA);
    aGL->setStateI(XFCGLRS_TGTBLEND, XFCBLEND_INVSRCALPHA);
    
    for (i = 0; i < mClouds->size(); i++)
    {        
        spr = mClouds->get(i);

        REAL dZ = spr->getZ() - mZ;
        if (dZ < REALi(-40)) 
        {
            // Cloud too close, put it further away again.
            spr->setLocation(spr->getX(), spr->getY(), spr->getZ() + 640);
        }

        aGL->setTexture(spr->getTexture());            
        aGL->drawSprite3dBillboard(spr->getX() - mX, spr->getY() - mY, spr->getZ(), 
                                   REALi(70), REALi(70),        
                                   REALi(0), REALi(0),  
                                   REALi(1), REALi(1),  
                                   NULL, 0x7fffffff);             
    }

#ifdef TRANSPARENT_CLOUDS
    aGL->setStateI(XFCGLRS_ALPHABLEND, 0);   
#endif

}


//! Generate a number of clouds in random positions.
void Level::generateClouds(const CHAR *aTextureFile, INT aNumber)
{
     INT i;
     REAL x, y, z;

     XFuRandom *rand = XFuRandom::create(0xdeadbeaf + aNumber);        

     // Load cloud texture. Make green (0xff00ff00) transparent using colorkeying.
     mCloudTexture = XFcGLTextureFromFile::create(aTextureFile,
                XFCTC_MIPMAP_LINEAR | XFCTC_COLORKEY, 
                0xff00ff00);

     XFCASSERT(mCloudTexture);

     for (i = 0; i < aNumber; i++)
     {
          Sprite *cloud = new Sprite();
          XFCASSERT(cloud);
          
          x = (rand->next() % SP_LEVEL_MAX_XY * 4) - 2 * SP_LEVEL_MAX_XY;
          y = (rand->next() % SP_LEVEL_MAX_XY * 4) - 2 * SP_LEVEL_MAX_XY;

          z = (rand->next()) % 640 - 40;

          cloud->setLocation(x, y, z);
          cloud->setTexture(mCloudTexture);

          // Add to cloud list.
          mClouds->put(cloud);
     }

     delete rand;
}


//! Check if a texture has been loaded before. Load it if not.
XFcGLTexture * Level::findTexture(const CHAR *aFileName)
{

    int textureFound = 0;
    TextureInfo *tex = NULL;

    // Search for texture among already loaded ones.
    UINT t;
    for (t = 0; t < mTextures->size(); t++)
    {
        tex = mTextures->get(t);
        if (0 == XFcStringToolkit::compareIgnoreCase(aFileName, tex->getName())) 
        {
            textureFound = 1;
            break;
        }
    }

    if (!textureFound) 
    {
        // Load new texture and add it to the list.
        tex = TextureInfo::create(aFileName);
        mTextures->put(tex);
    }

    if (tex == NULL) return NULL;

    return tex->getGLTexture();
}            
