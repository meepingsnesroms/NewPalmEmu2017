/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief  XFcThreadObject class for multitasking.
 *
 * $Id: XFcThreadObject.h,v 1.11 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.11 $
 */

#ifndef XFC_CORE_XFCTHREADOBJECT_H_INCLUDED
#define XFC_CORE_XFCTHREADOBJECT_H_INCLUDED

#include <xfcore/XFcThread.h>

class XFcSystemCore;


//! Object that runs in its own thread.
/*!
 * The implementor of the derived class is supposed to provide the
 * implementation for the pure virtual run method. The public interface
 * of XFcThreadObject is available to external agents so that they can
 * manage the state of XFcThreadObject object.
 * \sa XFcThreadObject::run
 * \note It is possible that some platforms do not have thread support.
 * \note Using threads generally slows down some systems.
 */
class XFCDLLEXPORT XFcThreadObject
{

public:

    //! Waits the thread to end and returns the exit code.
    XFCIMPORT INT32 waitDeath();

    //! Creates thread and starts running it immediately.
    XFCIMPORT INT create();

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcThreadObject();

protected:

    //! Protected constructor.
    XFCIMPORT XFcThreadObject();

    //! Thread function (this is where the thread runs).
    /*! Override this to implement the thread's functionality.
     * \return exit code for this thread.
     */
    virtual INT32 run() = 0;

    //! Thread creation.
    XFCIMPORT static INT32 threadEntry(void *);

    //! Actual thread object.
    XFcThread *mThread; 

private:

    //! Executes the thread.
    void runThread();

    //! Handle to the system core for this thread.
    /*!
     * \note Use and need for this field is platform specific.
     * \internal
     */
    XFcSystemCore *mXfc;

    //! Stores handle to the system core of the current thread.
    /*!
     * \note Implementation and need for this operation is platform specific.
     * \internal
     */
    void getTls();

    //! Sets the handle to the system core on the current thread.
    /*!
     * \note Implementation and need for this operation is platform specific.
     * \internal
     */
    void setTls();

};


#endif // !XFC_CORE_XFCTHREADOBJECT_H_INCLUDED

