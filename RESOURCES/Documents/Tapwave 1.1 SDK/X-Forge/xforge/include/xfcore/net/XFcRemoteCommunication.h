/*
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief
 *
 * $Id: XFcRemoteCommunication.h,v 1.2 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.2 $
 */

#ifndef XFCREMOTECOMMUNICATION_H_INCLUDED
#define XFCREMOTECOMMUNICATION_H_INCLUDED

class XFcRemoteCommunicationRecv;

class XFcRemoteCommunication
{
private:

    void *mService;
    
protected:

    XFcRemoteCommunication();
    
    INT init(INT aConnectionType, INT32 aPort, XFcRemoteCommunicationRecv *aListener);

public:

    static XFcRemoteCommunication * create(INT aConnectionType, INT32 aPort, XFcRemoteCommunicationRecv *aListener);

    INT32 send(const char *aBuffer, int aSize);
    
    virtual ~XFcRemoteCommunication();
    
    
};

#endif

