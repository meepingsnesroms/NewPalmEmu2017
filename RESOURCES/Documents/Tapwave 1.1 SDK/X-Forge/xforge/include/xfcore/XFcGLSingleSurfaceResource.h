/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Texture resource.
 * 
 * $Id: XFcGLSingleSurfaceResource.h,v 1.8 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.8 $
 */

#ifndef XFCGLSINGLESURFACERESOURCE_H_INCLUDED
#define XFCGLSINGLESURFACERESOURCE_H_INCLUDED

#include <xfcore/XFcResource.h>

class XFcGLResourceSurface;


//! Resource for the XFcGLResourceSurface.
/*!
 * This class acts as the resource for the XFcGLResourceSurface. It uses the 
 * XFcImageLoader to load the image whenever the resource is created (or re-created).
 */
class XFcGLSingleSurfaceResource : public XFcResource
{
public:

    //! Virtual destructor.
    virtual ~XFcGLSingleSurfaceResource();

    //! Creates the surface resource.
    /*!
     * \param aSurface the target resource surface
     * \param aFilename file name to load image for the surface from
     * \param aFlags resource creation flags
     */
    static XFcGLSingleSurfaceResource * create(XFcGLResourceSurface *aSurface, const CHAR *aFilename,
                                               INT32 aFlags);

    //! Locks the surface.
    INT lock();

    //! Unlocks the surface.
    INT unlock();

protected:

    //! Protected constructor.
    XFcGLSingleSurfaceResource();

    //! Pointer to the resource surface.
    XFcGLResourceSurface *mSurface;

    //! Resource surface file name.
    CHAR *mFilename;

    //! Resource creation callback.
    virtual INT callback(void *aBuffer);

};


#endif // !XFCGLSINGLESURFACERESOURCE_H_INCLUDED

