/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Interface for unidentified data sender.
 *            
 * 
 * $Id: XFcUnknownSender.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCUNKNOWNSENDER_H_INCLUDED
#define XFCUNKNOWNSENDER_H_INCLUDED


class XFCDLLEXPORT XFcUnknownSender
{
protected:

    //! Protected constructor.
    XFCIMPORT XFcUnknownSender();

public:

    XFCIMPORT virtual INT handleSender(const void *aAddress, const CHAR8 *aData, INT32 aLen) = 0;

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcUnknownSender();
};


#endif // !XFCUNKNOWNSENDER_H_INCLUDED

