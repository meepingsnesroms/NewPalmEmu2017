/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief
 * 
 * $Id: XFcCommunication.h,v 1.5.10.1 2003/10/17 07:54:51 jetro Exp $
 * $Date: 2003/10/17 07:54:51 $
 * $Revision: 1.5.10.1 $
 */

#ifndef XFCCOMMUNICATION_H_INCLUDED
#define XFCCOMMUNICATION_H_INCLUDED


//! Initializes the network library.
/*! \return non-zero if successful, or 0 if unsuccessful.
 */
INT xfcNetworkStartup();

//! Closes and cleans up the network library.
void xfcNetworkCleanup();


class XFCDLLEXPORT XFcCommunication
{

public:

    //! Virtual destructor.
    virtual ~XFcCommunication();

    //! Runs the communication scheduler.
    XFCIMPORT virtual INT runScheduler();

protected:

    //! Protected constructor.
    XFcCommunication();

};


#endif // !XFCCOMMUNICATION_H_INCLUDED

