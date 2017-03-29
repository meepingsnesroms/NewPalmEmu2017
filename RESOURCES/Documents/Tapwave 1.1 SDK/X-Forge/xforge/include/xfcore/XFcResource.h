/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Resource base class.
 * 
 * $Id: XFcResource.h,v 1.10 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.10 $
 */

#ifndef XFC_CORE_XFCRESOURCE_H_INCLUDED
#define XFC_CORE_XFCRESOURCE_H_INCLUDED


//! Resource base class.
/*!
 * Defines the resource interface. Resources can be managed by the resource
 * manager in a way so that if the memory manager runs out of memory, the
 * resource manager can destroy resources as it sees fit, and will re-create
 * the resources when they are needed next. Textures, for example, are
 * resources.
 * \sa XFcResourceManager
 * \sa XFcGLTexture
 */
class XFCDLLEXPORT XFcResource
{

public:

    //! Called whenever the resource needs to be generated.
    /*!
     * aBuffer points to a buffer which is as large as the resource
     * requires (as defined in the createResource() call). The 
     * resource manager expects the callback to fill the buffer with
     * the resource data. 
     * \return 1 if success, 0 if failure.
     */
    XFCIMPORT virtual INT callback(void *aBuffer);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcResource();

protected:

    //! Protected constructor.
    /*! Makes XFcResource an abstract class as there is no public
     *  static constructor.
     */
    XFcResource();

    //! Creates a resource, size in bytes, with user given flags.
    void createResource(const UINT32 aSize, const UINT32 aFlags);

    //! Creates a resource, size in bytes, with default flags.
    void createResource(const UINT32 aSize);

    //! Removes a resource.
    INT removeResource();

    //! Locks resource.
    void * lockResource();

    //! Unlocks resource.
    INT unlockResource();

private:

    //! Unique id.
    INT32 mId;

};


#endif // !XFC_CORE_XFCRESOURCE_H_INCLUDED

