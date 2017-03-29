/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Resource manager.
 * 
 * $Id: XFcResourceManager.h,v 1.11 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.11 $
 */

#ifndef XFC_CORE_XFCRESOURCEMANAGER_H_INCLUDED
#define XFC_CORE_XFCRESOURCEMANAGER_H_INCLUDED




class XFcResource;


//! Resource manager.
class XFCDLLEXPORT XFcResourceManager
{
public:

    //! Creates a new resource with the default resource type.
    /*!
     * \param aCallback Pointer to the resource to be used when callback is needed.
     * \param aSize Size of memory which should be allocated to the resource in bytes.
     *
     * \return Resource id, or -1 in case of an error.
     */
    XFCIMPORT static INT32 createResource(XFcResource *aCallback, const UINT32 aSize);

    //! Creates a new resource with the given resource type.
    /*!
     * Creates a new resource whose type is determined by the given flags.
     * \par
     * Different resource types are:
     * \li Default: resource can be moved and removed.
     * \li Non-removable: resource can be moved for defragmentation but can not be removed.
     * \li Non-movable: resource can not be moved nor removed, user might have a direct pointer to data.
     *
     * \param aCallback Pointer to the resource to be used when callback is needed.
     * \param aSize Size of memory which should be allocated to the resource in bytes.
     * \param aFlags Flags for resource type.
     *
     * \return Resource id, or -1 in case of an error.
     */
    XFCIMPORT static INT32 createResource(XFcResource *aCallback, const UINT32 aSize, 
                                          const UINT32 aFlags);

    //! Removes a resource.
    /*!
     * \param aId Resource id.
     *
     * \return 1 if the removal succeeds, 0 otherwise.
     */
    XFCIMPORT static INT removeResource(const INT32 aId);

    //! Removes all resources which are removable.
    XFCIMPORT static void removeResources();

    //! Queries whether a certain resource is available in memory.
    /*!
     * Queries whether the internal data of a resource is present in memory.
     * The resource headers stay in memory until the removeResource()-function is
     * called but the internal data might not be if it has been evicted temporarily to
     * free memory.
     *
     * \param aId Resource id.
     *
     * \return 1 if the internal data of a resource is present in memory, 0 otherwise.
     */
    XFCIMPORT static INT queryResource(const INT32 aId);

    //! Evicts the data of a resource.
    /*!
     * Frees the internal data of a resource, the resource header stays in
     * memory. The internal data will be loaded into memory when the resource
     * is being locked or it can be loaded into memory with the preloadResource()-function.
     *
     * \param aId Resource id.
     *
     * \return 1 if the evict succeeds, 0 otherwise.
     */
    XFCIMPORT static INT evictResource(const INT32 aId);

    //! Evicts all resources from memory which are removable.
    /*!
     * Frees the internal data of all resources, the resource headers stay in
     * memory. The internal data will be loaded into memory when the resource
     * is being locked or it can be loaded into memory with the preloadResource()-function.
     */
    XFCIMPORT static void evictResources();

    //! Preloads the data of a resource to memory.
    /*!
     * Loads the internal data of a resource into memory. The actual implementation
     * is just a lock and unlock of the resource.
     *
     * \param aId Resource id
     *
     * \return 1 if preload succeeds, 0 otherwise
     */
    XFCIMPORT static INT preloadResource(const INT32 aId);

    //! Tries to preload data of all resources to memory.
    /*!
     * Tries to load the internal data of all resources into memory.
     */
    XFCIMPORT static void preloadResources();

    //! Locks a resource for use.
    /*!
     * Locks a resource so that it can not be moved nor removed while the lock 
     * is on. If the internal data of a resource is not present in memory, a 
     * callback is made to the resource so it will be loaded into memory again.
     *
     * \param aId Resource id.
     *
     * \return Pointer to the internal data of a resource, NULL if the resource can not be locked.
     */
    XFCIMPORT static void * lockResource(const INT32 aId);

    //! Unlocks a resource.
    /*!
     * Unlocks a resource so it can be moved or removed again if needed.
     * The call will fail if the resource id is not valid or the resource
     * is not locked in the first place.
     *
     * \param aId Resource id.
     *
     * \return 1 if unlock succeeds, 0 otherwise.
     */
    XFCIMPORT static INT unlockResource(const INT32 aId);
};


#endif  // XFC_CORE_XFCRESOURCEMANAGER_H_INCLUDED

