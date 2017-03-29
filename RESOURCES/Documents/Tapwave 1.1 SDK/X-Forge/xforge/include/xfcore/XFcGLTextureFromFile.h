/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Texture builder from image files
 * 
 * $Id: XFcGLTextureFromFile.h,v 1.12 2003/08/19 11:24:34 peppe Exp $
 * $Date: 2003/08/19 11:24:34 $
 * $Revision: 1.12 $
 */

#ifndef XFCTEXTUREFROMFILE_H_INCLUDED
#define XFCTEXTUREFROMFILE_H_INCLUDED

#include <xfcore/XFcGLTextureBuilder.h>


class XFcGLComplexSurfaceResource;

//! Create XFcTexture object from an image file.
class XFCDLLEXPORT XFcGLTextureFromFile : public XFcGLTextureBuilder
{

public:

    //! Creates a texture object from an image file.
    /*!
     * In order to use the color key, set the aColorKey parameter and
     * use the XFCTC_COLORKEY flag. The color keying sets the texture format
     * to 1555 and sets all the texels that have the color as transparent.
     * \par
     * Internally, the create() function creates a XFcGLTextureFromFile object
     * and passes itself to XFcTexture's create function.
     *
     * \param aFilename filename to load the image from.
     * \param aFlags texture creation flags, see XFCTEXTURECREATE.
     * \param aColorKey color key to use if XFCTC_COLORKEY flag is used.
     * \return new texture object, or NULL if unsuccessful.
     * \sa XFCTEXTURECREATE
     */
    XFCIMPORT static XFcGLTexture * create(const CHAR *aFilename,
                                           INT32 aFlags = XFCTC_MIPMAP_POINTSAMPLE,
                                           UINT32 aColorKey = 0xff000000);

    //! Loads the texture info for the texture builder.
    XFCEXPORT static void loadTextureInfo(XFcGLTextureFromFile *aBuilder);

    //! Inherited from XFcGLTextureBuilder interface.
    /*! \sa XFcGLTextureBuilder::fillSurface
     */
    XFCIMPORT virtual INT fillSurface(INT32 aSurfaceNumber, void *aBuffer,
                                      XFcGLComplexSurfaceResource *aSurface);

    //! Inherited from XFcGLTextureBuilder interface.
    /*! \sa XFcGLTextureBuilder::getSurfaceCount
     */
    XFCIMPORT virtual INT32 getSurfaceCount();
    
    //! Inherited from XFcGLTextureBuilder interface.
    /*! \sa XFcGLTextureBuilder::getSurfaceParams
     */
    XFCIMPORT virtual void getSurfaceParams(INT32 aSurfaceNumber, INT32 &aWidth,
                                            INT32 &aHeight, INT32 &aFormat);
    
    //! Inherited from XFcGLTextureBuilder interface.
    /*! \sa XFcGLTextureBuilder::sameClassEquals
     */
    XFCIMPORT virtual INT sameClassEquals(XFcGLTextureBuilder *aBuilder);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcGLTextureFromFile();

protected:

    //! Protected constructor.
    XFcGLTextureFromFile();

    UINT32 mFormat;             //!< Internal: image format.
    CHAR *mFilename;            //!< Internal: image filename.
    UINT32 mWidth;              //!< Internal: image width.
    UINT32 mHeight;             //!< Internal: image height.
    INT32 mSurfaces;            //!< Internal: total number of surfaces.
    INT32 mTextureFormat;       //!< Internal: texture format (XFCGF_R5G5A1B5 or XFCGF_R5G5X1B5).
    UINT32 mColorKey;           //!< Internal: color key, if any.

};


#endif // !XFCTEXTUREFROMFILE_H_INCLUDED

