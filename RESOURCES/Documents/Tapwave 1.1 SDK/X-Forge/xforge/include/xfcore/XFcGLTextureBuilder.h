/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Texture builder class
 * 
 * $Id: XFcGLTextureBuilder.h,v 1.10 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.10 $
 */

#ifndef XFCGLTEXTUREBUILDER_H_INCLUDED
#define XFCGLTEXTUREBUILDER_H_INCLUDED



class XFcGLComplexSurfaceResource;

//! Interface for a texture builder which creates texture surfaces as needed.
/*!
 * A texture builder object contains all information required to create
 * the surfaces for the texture as needed. Since the resource manager may
 * decide to discard the surface data whenever free memory is required, the
 * texture builder will need to recreate the surface data when needed. 
 * \sa XFcGLTexture
 */
class XFCDLLEXPORT XFcGLTextureBuilder 
{

public:

    //! Used by equals() function to see if the classes are the same.
    /*! \sa sameClassEquals
     */
    UINT32 mBuilderUniqueId;

    //! Used by equals() function to see if flags are the same.
    /*! \sa sameClassEquals
     */
    UINT32 mFlags;

    //! Returns the number of surfaces required for this texture.
    /*! \sa sameClassEquals
     */
    XFCIMPORT virtual INT32 getSurfaceCount() = 0;

    //! Called for each surface to return the parameters for the surface.
    /*!
     * \param aSurfaceNumber number of the surface to get the parameters for.
     * \param aWidth returned width of the surface.
     * \param aHeight returned height of the surface.
     * \param aFormat returned format of the surface, see XFCGFXFORMAT.
     * \sa XFCGFXFORMAT
     */
    XFCIMPORT virtual void getSurfaceParams(INT32 aSurfaceNumber, INT32 &aWidth,
                                            INT32 &aHeight, INT32 &aFormat) = 0;

    //! Called in order to fill the surfaces as needed.
    /*!
     * \param aSurfaceNumber surface number to fill in.
     * \param aBuffer destination pointer to fill the data in.
     * \param aComplexSurfaceResource pointer to the complex surface resource for surface.
     * \return 1 if successful, or 0 if unsuccessful.
     */
    XFCIMPORT virtual INT fillSurface(INT32 aSurfaceNumber, void *aBuffer,
                                      XFcGLComplexSurfaceResource *aComplexSurfaceResource) = 0;

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcGLTextureBuilder();

    //! Compares two XFcGLTextureBuilder classes.
    /*! \sa sameClassEquals
     * \param aBuilder texture builder to compare this builder against.
     * \return non-zero if the builders are considered equal, or 0 if they are not equal.
     */
    XFCIMPORT INT equals(XFcGLTextureBuilder *aBuilder);

    //! Compares two XFcGLTextureBuilder-extended objects of the same class.
    /*!
     * The texture loading mechanism attempts to share resources between 
     * objects as much as possible, so that, for example, if an application 
     * loads a single texture from file several times, it is only allocated 
     * once (except if XFCTC_UNIQUE flag is used while creating the texture).
     * \param aBuilder texture builder to compare this builder against.
     * \return non-zero if the builders are considered equal, or 0 if they are not equal.
     */
    XFCIMPORT virtual INT sameClassEquals(XFcGLTextureBuilder *aBuilder) = 0;
};  


#endif // !XFCGLTEXTUREBUILDER_H_INCLUDED

