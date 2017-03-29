/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Data receiver interface
 *
 * $Id: XFcDataReceiver.h,v 1.12 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.12 $
 */

#ifndef XFCDATARECEIVER_H_INCLUDED
#define XFCDATARECEIVER_H_INCLUDED
#include <xfcore/XFcCore.h>

//! Interface for data receiver.
class XFCDLLEXPORT XFcDataReceiver
{
protected:

    //! Protected constructor.
    XFCIMPORT XFcDataReceiver();

public:

    //! Adds data to network receiver.
    /*!
     * \param aData data buffer.
     * \param aLen length of buffer.
     */
    XFCIMPORT virtual void addData(const CHAR8 *aData, INT32 aLen);

    //! Adds data to network receiver.
    /*!
     * \param aClientId is identifier about client where data comes from.
     * \param aData data buffer.
     * \param aLen length of buffer.
     */
    XFCIMPORT virtual void addData(INT32 aClientId, const CHAR8 *aData, INT32 aLen);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcDataReceiver();

};


#endif // !XFCDATARECEIVER_H_INCLUDED

