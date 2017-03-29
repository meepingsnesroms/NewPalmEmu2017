/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Texture resource
 * 
 * $Id: XFcGLComplexSurfaceResource.h,v 1.7 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.7 $
 */

#ifndef XFCGLCOMPLEXSURFACERESOURCE_H_INCLUDED
#define XFCGLCOMPLEXSURFACERESOURCE_H_INCLUDED

#include <xfcore/XFcResource.h>

class XFcGLTextureBuilder;


//! Resource for XFcGLTexture object.
/*! This class acts as the resource for the XFcGLTexture object.
 *  It stores all of the texture's surface data in a single resource.
 *  The negative side from this is that if the texture resource is lost,
 *  all of the mipmaps will have to be generated whenever the texture is
 *  needed next. Positive side is that this dramatically reduces the fragmentation
 *  of resource memory, and also speeds up texture finding, as the resource manager
 *  does not need to go through N * 8 resources. Swapping between mipmaps inside
 *  a single texture is also faster.
 *  \sa XFcGLTexture
 */
class XFcGLComplexSurfaceResource : public XFcResource
{
    
public:

    //! Virtual destructor.
    virtual ~XFcGLComplexSurfaceResource();

    //! Creates a XFcGLComplexSurfaceResource object. 
    /*! XFcGLTextureBuilder is queried for surface details.
     */
    static XFcGLComplexSurfaceResource * create(XFcGLTextureBuilder *aBuilder,
                                                INT32 aFlags);

    //! Locks a surface.
    XFcGLSurface * lock(INT32 aSurfaceNumber);
    //! Unlocks a surface.
    INT unlock(INT32 aSurfaceNumber);

    //! Returns the surface count.
    INT32 getSurfaceCount();

    //! Returns the surface format (all surfaces must be of the same format).
    INT32 getSurfaceFormat();

protected:

    //! Protected constructor.
    XFcGLComplexSurfaceResource();

    //! Surface count.
    INT32 mSurfaces;
    //! Surface offsets inside the resource.
    INT32 *mSurfaceOffset;
    //! Pointers to surfaces.
    XFcGLSurface **mSurface;
    //! Pointer to parent (used in creation of surface data).
    XFcGLTextureBuilder *mBuilder;
    //! Called whenever resource manager needs to re-create the resource.
    virtual INT callback(void *aBuffer);
    //! Lock count.
    INT32 mLockCount;
    //! Data pointer.
    void *mData;

};


#endif // !XFCGLCOMPLEXSURFACERESOURCE_H_INCLUDED

