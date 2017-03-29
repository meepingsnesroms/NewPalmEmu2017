/*
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Remote debug server incoming data callback
 *
 * $Id: XFcRemoteCommunicationRecv.h,v 1.5 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.5 $
 */

#ifndef XFCREMOTECOMMUNICATIONRECV_H_INCLUDED
#define XFCREMOTECOMMUNICATIONRECV_H_INCLUDED

class XFcRemoteCommunicationRecv
{
private:
protected:
public:

    virtual void receive(const CHAR8 * aData, INT32 aSize, INT32 aError) = 0;
    
    virtual void event(INT32 aEvent) = 0;

};

#endif

