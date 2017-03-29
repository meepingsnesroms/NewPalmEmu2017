/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Common mutex interface.
 * 
 * $Id: XFcMutex.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFC_CORE_XFCMUTEX_H_INCLUDED
#define XFC_CORE_XFCMUTEX_H_INCLUDED



//! Mutual exclusion (mutex) class.
/*! In order to synchronize code running in several threads, you may 
 *  want to use a mutex. All threads will pause on mutex lock if some
 *  thread has already locked it, and will resume once the locking thread
 *  calls unlock.
 */
class XFCDLLEXPORT XFcMutex
{

public:
    //! Creates a mutex object.
    /*!
     * \return pointer to a new mutex object or NULL if unsuccessful
     */
    XFCIMPORT static XFcMutex * create();

    //! Locks the mutex.
    /*!
     * \note Blocks until the mutex is available for locking.
     *       Returns immediately if the caller thread already has the lock.
     */
    XFCIMPORT void lock();

    //! Unlocks the mutex.
    XFCIMPORT void unlock();

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcMutex();

protected:

    //! The id of the thread that has locked the mutex.
    UINT32 mLockingThreadId;
    //! The number of times the locking thread has called lock().
    INT32 mLockCount;

    //! Constructor.
    XFcMutex();

    //! Initializes mutex.
    /*!
     * \return 1 if successful, 0 if unsuccessful.
     */
    INT init();

    //! Does the real lock operation.
    void doLock();

    //! Does the real unlock operation.
    void doUnlock();

private:

    //! Mutex handle.
    void *mMutex;

};


#endif // !XFC_CORE_XFCMUTEX_H_INCLUDED

