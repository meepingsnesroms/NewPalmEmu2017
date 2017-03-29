/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: ConnectingScreen.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef CONNECTINGSCREEN_H_INCLUDED
#define CONNECTINGSCREEN_H_INCLUDED

class XFuPrinter;
class MultiPlayerHandler;

#define MAX_LIST_ENTRIES    5
#define MPE_START_BUTTON    10000
#define MPE_CANCEL_BUTTON   10001
#define MPE_FIRST_CHECKBOX  10010


class ConnectingScreen : public Screen
{

public:

    static ConnectingScreen * create(XFcGL *aGL, 
                                     XFuPrinter *aPrinter,
                                     MultiPlayerHandler *aMultiPlayerHandler);

    ConnectingScreen();
    virtual ~ConnectingScreen();

    virtual void onActivate();
    virtual void onDeactivate();

    virtual void onTick();

    virtual void render();

    virtual void onButtonPressed(INT32 aButton);

protected:

    void setStatus(const CHAR *aStatus);

    MultiPlayerHandler *mMultiPlayerHandler;

    //! Client checkboxes.
    Widget *mClientCheckbox[MAX_LIST_ENTRIES];    

    //! Screen buttons.
    Widget *mStartButton, *mCancelButton;

    INT32 mMultiPlayerState;
    INT32 mRole;
    INT32 mListedClientCount;
    
    //! Status message coordinates...
    INT mStatusX, mStatusY;

    INT mShowTruncated;

    //! Status string buffer.
    CHAR mStatusString[64];
};

#endif // !CONNECTINGSCREEN_H_INCLUDED


