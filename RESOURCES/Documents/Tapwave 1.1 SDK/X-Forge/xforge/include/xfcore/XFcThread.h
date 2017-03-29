/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Common thread handling.
 * 
 * $Id: XFcThread.h,v 1.8 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.8 $
 */

#ifndef XFC_CORE_XFCTHREAD_H_INCLUDED
#define XFC_CORE_XFCTHREAD_H_INCLUDED


//! Common thread handling.
/*!
 * This class encapsulates thread handling routines in a 
 * platform-independent way.
 * \sa XFcThreadObject
 * \sa XFcMutex
 * \note It is possible that some platforms do not have thread support.
 * \note Using threads generally slow down some systems.
 */
class XFCDLLEXPORT XFcThread
{

public:

    //! Creates a new thread and starts running it.
    /*!
     * \param aFunc thread function pointer.
     * \param aArg argument passed to the thread function.
     * \return pointer to the new thread object or NULL if operation failed.
     * \note You should always use waitDeath() exactly once for each thread
     *       before deleting the thread object.
     */
    XFCIMPORT static XFcThread * create(INT32 (*aFunc)(void *), void *aArg);

    //! Exits the caller thread.
    /*!
     * \param aExitCode Exit code for the thread.
     */
    XFCIMPORT static void exit(INT32 aExitCode);

    //! Returns identifier of the caller thread.
    /*!
     * \return Unique thread identifier for this thread.
     */
    XFCIMPORT static UINT32 getId();

    //! Blocks until the thread ends and returns exit code.
    /*!
     * \note This must be called only once per existing thread.
     */
    XFCIMPORT INT32 waitDeath();
    
    //! Virtual destructor.
    /*!
     * \sa create
     */
    XFCIMPORT virtual ~XFcThread();

protected:

    //! Protected constructor.
    XFcThread();

    //! Initializes a thread and starts running it.
    /*!
     * \param aFunc thread function pointer
     * \param aArg argument passed to the thread function
     * \return 1 if operation was successful, 0 otherwise
     */
    INT init(INT32 (*aFunc)(void *), void *aArg);

private:

    //! Thread handle.
    void *mThread;

};


#endif // !XFC_CORE_XFCTHREAD_H_INCLUDED

