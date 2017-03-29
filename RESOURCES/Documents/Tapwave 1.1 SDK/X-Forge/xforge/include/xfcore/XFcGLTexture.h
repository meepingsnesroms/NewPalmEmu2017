/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Texture resource
 *
 * $Id: XFcGLTexture.h,v 1.18 2003/08/19 11:24:34 peppe Exp $
 * $Date: 2003/08/19 11:24:34 $
 * $Revision: 1.18 $
 */

#ifndef XFC_CORE_XFCTEXTURE_H_INCLUDED
#define XFC_CORE_XFCTEXTURE_H_INCLUDED



class XFcGLTextureBuilder;
class XFcGLComplexSurfaceResource;


//! Texture creation flags.
enum XFCTEXTURECREATE
{
    //! Do not create mipmaps.
    XFCTC_MIPMAP_NOMIPMAPS   = 0,
    //! Create mipmaps with point-sampling.
    XFCTC_MIPMAP_POINTSAMPLE = 0x0100,
    //! Create mipmaps with linear interpolation.
    XFCTC_MIPMAP_LINEAR      = 0x0200,
    //! Unique texture (does not share resources with other texture).
    XFCTC_UNIQUE             = 0x0400,
    //! Use color key while creating texture.
    XFCTC_COLORKEY           = 0x0800,
    //! Do not preload texture at creation time.
    XFCTC_NOPRELOAD          = 0x1000,
    //! Try to use paletted textures if possible
    XFCTC_PALETTEDTEXTURE     = 0x2000
};


//! Texture class.
/*!
 * Encapsulates a single texture. The texture may have multiple surfaces,
 * which are used for mip mapping.
 * Most often textures are created using the XFcGLTextureFromFile class.
 * \sa XFcGLTextureFromFile
 */
class XFCDLLEXPORT XFcGLTexture
{

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcGLTexture();
    
    //! Static constructor.
    /*!
     *  In order to create a texture, you have to extend the XFcGLTextureBuilder
     *  class, create an object of said class and pass it as a parameter to this
     *  create-function. The texture builder object knows how to create the texture
     *  surfaces whenever they are needed, and since all texture surfaces are
     *  resources, the memory manager may discard them when the system is running
     *  low on memory. The flags are a combination of resource manager flags and
     *  the texture creation flags.
     * \param aBuilder texture builder to use.
     * \param aFlags combined flags, see XFCRESOURCEFLAGS and XFCTEXTURECREATE.
     * \return new texture, or NULL if unsuccessful.
     * \sa XFCRESOURCEFLAGS
     * \sa XFCTEXTURECREATE
     */
    XFCIMPORT static XFcGLTexture * create(XFcGLTextureBuilder *aBuilder,
                                           INT32 aFlags = 0);

    //! Returns surface count for this texture.
    XFCIMPORT INT32 getSurfaceCount();
    //! Returns surface format for this texture.
    /*! \sa XFCGFXFORMAT
     */
    XFCIMPORT INT32 getSurfaceFormat();

    //! Locks a specific surface in this texture.
    /*!
     * \param aSurfaceIndex index of the surface to lock.
     * \return pointer to the locked surface, or NULL if unsuccessful.
     */
    XFCIMPORT XFcGLSurface * lock(INT32 aSurfaceIndex);
    
    //! Unlocks a specific surface in this texture.
    /*!
     * \param aSurfaceIndex index of the surface to unlock.
     */
    XFCIMPORT INT unlock(INT32 aSurfaceIndex);

    //! Returns the largest surface width.
    XFCIMPORT INT32 getPrimarySurfaceWidth();

    //! Returns the largest surface height.
    XFCIMPORT INT32 getPrimarySurfaceHeight();

    //! Returns the texel format for this texture.
    /*! \sa XFCGFXFORMAT
     */
    XFCIMPORT INT32 getTexelFormat();

    //! Calculates mipmap level data based on one level higher data.
    /*!
     * \note Performs point sample scaling.
     * \param aSrc source surface to calculate mipmap data for.
     * \param aTgt destination memory to write the scaled down image.
     */
    XFCIMPORT static void filterMapPointSample55X5(XFcGLSurface *aSrc,
                                                  void *aTgt);
    
    //! Calculates mipmap level data based on one level higher data.
    /*!
     * \note Performs 2x2 box filtering.
     * \param aSrc source surface to calculate mipmap data for.
     * \param aTgt destination memory to write the scaled down image.
     */
    XFCIMPORT static void filterMapLinear55X5(XFcGLSurface *aSrc, void *aTgt);
    
    //! Calculates mipmap level data based on one level higher data.
    /*!
     * \note  Performs point sample scaling.
     * \param aSrc source surface to calculate mipmap data for.
     * \param aTgt destination memory to write the scaled down image.
     */
    XFCIMPORT static void filterMapPointSample5515(XFcGLSurface *aSrc,
                                                   void *aTgt);
    //! Calculates mipmap level data based on one level higher data.
    /*!
     * \note Performs 2x2 box filtering.
     * \param aSrc source surface to calculate mipmap data for.
     * \param aTgt destination memory to write the scaled down image.
     */
    XFCIMPORT static void filterMapLinear5515(XFcGLSurface *aSrc, void *aTgt);

    //! Calculates mipmap level data based on one level higher data.
    /*!
     * \note Performs point sample scaling.
     * \param aSrc source surface to calculate mipmap data for.
     * \param aTgt destination memory to write the scaled down image.
     */
    XFCIMPORT static void filterMapPointSamplePal55X5(XFcGLSurface *aSrc,
                                                  void *aTgt);

    //! Preloads the texture for rendering.
    /*! This call is completely voluntary; the system
     *  will load the texture when it's needed next.
     */
    XFCIMPORT void preload();


    //! Returns the graphics device data hook. [Internal]
    /*! \internal
     */
    XFCIMPORT INT32 getGLData();

    //! Sets the graphics device data hook. [Internal]
    /*! \internal
     */
    XFCIMPORT void setGLData(INT32 aData);

    //! Returns the next texture in the linked list. [Internal]
    /*! \internal
     */
    XFCIMPORT XFcGLTexture * getNext();

    //! Returns the builder for this texture. [Internal]
    /*! \internal
     */
    XFCIMPORT XFcGLTextureBuilder * getBuilder();

protected:

    //! Protected constructor.
    XFcGLTexture();
    
    //! Texture builder object for this texture.
    XFcGLTextureBuilder *mBuilder;
    //! Resource that contains the surface data for all surfaces for this texture.
    XFcGLComplexSurfaceResource *mSurface;
    //! Internal linked list of all textures.
    XFcGLTexture *mNext;
    //! Largest surface width.
    INT32 mWidth;
    //! Largest surface height.
    INT32 mHeight;
    //! Texture surface format.
    INT32 mFormat;
    //! Intenal: graphics device data hook.
    INT32 mGLData;

};


#endif // !XFC_CORE_XFCTEXTURE_H_INCLUDED

