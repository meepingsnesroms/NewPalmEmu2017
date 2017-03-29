/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: GameScreen.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

class XFuPrinter;
class MultiPlayerHandler;
class GameState;


#define MPE_LED_BUTTON      10001
#define MPE_LEAVE_BUTTON    10002


class GameScreen : public Screen
{

public:

    static GameScreen * create(XFcGL *aGL,
                               XFuPrinter *aPrinter,
                               MultiPlayerHandler *aMultiPlayerHandler);

    GameScreen();
    virtual ~GameScreen();

    virtual void onActivate();
    virtual void onDeactivate();

    virtual void onTick();

    virtual void render();

    virtual void onButtonPressed(INT32 aButton);

protected:

    INT32 getPlayerCount();
    INT32 getPlayerId();
    GameState * getGameState(INT32 aPlayerId);

    XFcGLSurface *mLedOn;
    XFcGLSurface *mLedOff;

    MultiPlayerHandler *mMultiPlayerHandler;
};

#endif // !GAMESCREEN_H_INCLUDED


