/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief XM player event handler
 * 
 * $Id: XFuXMPlayerEventHandler.h,v 1.6 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.6 $
 */

#ifndef XFUXMPLAYEREVENTHANDLER_H_INCLUDED
#define XFUXMPLAYEREVENTHANDLER_H_INCLUDED



class XFuXMPlayer;


class XFuXMPlayerEvent
{
public:
    XFuXMPlayerEvent()
    {
        mNote = mInstrumentNb = mVolume = mEffectType = mEffectValue = -1;
        mPlayer = NULL;
    }

    INT16 mNote;
    INT16 mInstrumentNb;
    INT16 mVolume;
    INT16 mEffectType;
    INT16 mEffectValue;

    XFuXMPlayer *mPlayer;
};


class XFuXMPlayerEventHandler
{
public:
    virtual void handleXMPlayerEvent(XFuXMPlayerEvent aEvent) = 0;
};


#endif  // !XFUXMPLAYEREVENTHANDLER_H_INCLUDED

