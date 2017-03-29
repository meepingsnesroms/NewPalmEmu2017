/*! \file
* Level.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: Level.h,v 1.3 2003/07/22 13:33:35 lars Exp $
* $Date: 2003/07/22 13:33:35 $
* $Revision: 1.3 $
*/

#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

class Sprite;
class Plane;
class StuntPlane;
class GameScreen;
class WindParameter;

// Bitmasks for indicating keypresses.
#define SP_LEFT     1
#define SP_RIGHT    2
#define SP_UP       4
#define SP_DOWN     8

#define SP_ROTATE_LEFT       16
#define SP_ROTATE_RIGHT      32


//! Class used to keep track of loaded textures.
class TextureInfo
{

public:
    //! Static constructor.
    static TextureInfo * create(const CHAR *aFileName) 
    { 
        TextureInfo *ti = new TextureInfo();
        XFCASSERT(ti);

        ti->mFileName = XFcStringToolkit::copy(aFileName);
        XFCASSERT(ti->mFileName);

        ti->mTexture = XFcGLTextureFromFile::create(aFileName,
            XFCTC_MIPMAP_LINEAR | XFCTC_COLORKEY, 
            0xff00ff00);

        XFCASSERT(ti->mTexture);
        return ti;
    }

    //! Virtual destructor.
    virtual ~TextureInfo()
    {
        if (mFileName) delete mFileName;
        if (mTexture) delete mTexture;
    }

    //! Get pointer to XFcGLTexture.
    XFcGLTexture *getGLTexture() { return mTexture; }

    //! Get filename of this texture.
    CHAR *getName() { return mFileName; }

protected:
    //! Protected constructor.
    TextureInfo() : mFileName(NULL), mTexture(NULL) { }

    //! Name of the texture file.
    CHAR *mFileName;

    //! Pointer to XFcGLTexture.
    XFcGLTexture *mTexture;            
};


//! Class that takes care of loading, initiating and to some degree rendering levels.
class Level
{

public:
    //! Static constructor.
    static Level * create();

    ~Level();

    //! Load, parse and initialize level from a text file description.
    INT load(INT aLevel);
  
    //! Returns the length of the currently loaded level.
    INT length() { return mLength; }

    //! Returns the number of sprites (hoops and bonus items) in current level.
    UINT nrSprites() { return mSprites->size(); }

    //! Returns a pointer to a sprite.
    Sprite * getSprite(INT aIndex) { return mSprites->get(aIndex); }

    //! Returns a pointer to the level description text.
    CHAR * getText() { return mText; };

    //! Remove a sprite from the sprite list.
    void removeSprite(Sprite *aSprite) { mSprites->remove(aSprite); }

    //! Draw backdrop image.
    void drawBackdrop(XFcGL *aGL, REAL mX, REAL mY, INT aNoStatusBar);

    //! Draw randomly generated clouds.
    void renderClouds(XFcGL *aGL, REAL mX, REAL mY, REAL mZ);

    //! Interpolate between wind parameters specified at certain locations.
    void updateWindParameters(REAL aZ);

    //! Forward speed on this level.
    REAL getPlaneSpeed() { return mPlaneSpeed; }

    //! Wind parameters.
    REAL getWindMagnitude() { return mWindMagnitude; }
    REAL getWindDirection() { return mWindDirection; }
    REAL getWindGustFactor() { return mWindGustFactor; }

    //! Get start coordinates for the plane.
    void getStartXY(REAL &aX, REAL &aY) { aX = mStartX; aY = mStartY; }

    void getPlaneColor(REAL &aR, REAL &aG, REAL &aB) 
    {
        aR = mPlaneRed;   
        aG = mPlaneGreen;   
        aB = mPlaneBlue;
    }

private:
    // Private constructor.
    Level();

    //! Check if texture has already been loaded. Load it if not.
    XFcGLTexture * findTexture(const CHAR *aFileName);

    //! Generate a number of clouds at random positions.
    void generateClouds(const CHAR *aTextureFile, INT aNumber);

    //! Initialize wind interpolation.
    void initWinds();
    
    //! Level background surface.
    XFcGLSurface *mBackSurf;        

    //! Texture for all clouds on current level.
    XFcGLTexture *mCloudTexture;
    
    //! List of hoop and bonus item sprites.
    XFuDynamicArray<Sprite *> *mSprites;

    //! List of cloud sprites.
    XFuDynamicArray<Sprite *> *mClouds;        

    //! List of wind parameters.
    XFuDynamicArray<WindParameter *> *mWinds;        

    //! List of textures.
    XFuDynamicArray<TextureInfo *> *mTextures;
    
    //! Length of currently loaded level.
    REAL mLength;

    //! Forward speed on this level.
    REAL mPlaneSpeed;

    //! Color of the plane.
    REAL mPlaneRed, mPlaneGreen, mPlaneBlue;

    //! Plane starting coordinates.
    REAL mStartX, mStartY;

    //! Short description of the level.
    CHAR  *mText;

    //! First of two wind parameters to interpolate between.
    INT mFirstWind;

    //! Current strength of the wind.
    REAL mWindMagnitude;
    
    //! Wind direction in radians.
    REAL mWindDirection;
    
    //! Frequency and strength of sudden wind gusts.
    REAL mWindGustFactor;    
};


#endif // !LEVEL_H_INCLUDED
