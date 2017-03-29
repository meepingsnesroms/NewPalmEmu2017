/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XFcGL resource surface class. 
 * 
 * $Id: XFcGLResourceSurface.h,v 1.12 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.12 $
 */

#ifndef XFC_XFCGLRESOURCESURFACE_H_INCLUDED
#define XFC_XFCGLRESOURCESURFACE_H_INCLUDED


class XFcGLCoreSurface;
class XFcGLSingleSurfaceResource;


//! Graphics surface class which stores surface as a resource.
/*!
 * Extends XFcGLSurface so that the surface data itself is a resource, and
 * may be deallocated by the resource manager whenever free memory is required.
 * The surface data is re-created from file when needed. Please note that
 * whatever changes done to the surface may be lost when the resource is
 * removed from memory.
 */
class XFCDLLEXPORT XFcGLResourceSurface : public XFcGLSurface
{
    friend class XFcGLCoreSurface;

public:

    //! Creates a surface with dimensions and format.
    /*! \param aPictureFilename filename of the picture file.
     *  \param aFormat enumerated surface format. \sa XFCGFXFORMAT
     *  \param aFlags resource type flags. \sa XFCRESOURCEFLAGS
     */
    XFCIMPORT static XFcGLResourceSurface * create(const CHAR *aPictureFilename,
                                                   INT32 aFormat = XFCGF_DEFAULT,
                                                   INT32 aFlags = XFCRESOURCE_DEFAULT);

    //! Destructor.
    XFCIMPORT virtual ~XFcGLResourceSurface();
    
    //! Locks the surface with specific mode.
    /*!
     * Non-preferred modes will be converted on the fly, which is slow.
     * \par
     * If you wish to fill the whole surface you may get some speed gains
     * by using the XFCGFX_DISCARDCONTENTS flag. Not using this flag may cause
     * the system to convert between graphics formats on lock and unlock.
     * \par
     * If you only wish to read from the surface, use the XFCGFX_DISCARDCHANGES
     * flag. Not doing so may cause loss of data (if locked format has less
     * data than the native format).
     * \note While the framebuffer is locked, you should not call any graphics
     *       library functions.
     * \param aBuffer returned pointer to the surface.
     * \param aFlags surface lock flags, see XFCGFXFLAGS.
     * \param aMode graphics format, see XFCGFXFORMAT. Use XFCGF_DEFAULT to
     *              lock surface in its own native format.
     * \return Surface pitch in bytes.
     * \sa XFCGFXFORMAT
     * \sa XFCGFXFLAGS
     */
    XFCIMPORT virtual INT32 lock(void **aBuffer, INT32 aMode = XFCGF_DEFAULT,
                                 INT32 aFlags = XFCGFX_DISCARDCONTENTS);

    //! Unlocks the framebuffer.
    /*! If the surface was locked in a non-native format and the locking did
     *  not specify the GFX_DISCARDCHANGES flag, the unlock will convert the
     *  temporary buffer into the surface's native format.
     *  \sa lock
     */
    XFCIMPORT virtual void unlock();   

protected:

    //! Protected constructor.
    XFcGLResourceSurface(); 

    //! Surface resource.
    XFcGLSingleSurfaceResource *mResource;

};


#endif // !XFC_XFCGLRESOURCESURFACE_H_INCLUDED

