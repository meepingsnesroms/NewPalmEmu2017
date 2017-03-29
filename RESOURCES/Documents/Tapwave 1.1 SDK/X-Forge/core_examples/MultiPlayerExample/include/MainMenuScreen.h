/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MainMenuScreen.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef MAINMENUSCREEN_H_INCLUDED
#define MAINMENUSCREEN_H_INCLUDED


#define MPE_HOST_BUTTON  10000
#define MPE_JOIN_BUTTON  10001
#define MPE_QUIT_BUTTON  10002


class XFuPrinter;
class Screen;


class MainMenuScreen : public Screen
{

public:

    static MainMenuScreen * create(XFcGL *aGL, XFuPrinter *aPrinter);

    MainMenuScreen();
    virtual ~MainMenuScreen();

    virtual void onActivate();
    virtual void onDeactivate();

    virtual void onTick();

    virtual void render();

    virtual void onButtonPressed(INT32 aButton);

protected:

};

#endif // !MAINMENUSCREEN_H_INCLUDED


