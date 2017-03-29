/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: AppStates.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef APP_STATES_H_INCLUDED
#define APP_STATES_H_INCLUDED

enum APP_STATES
{
    APP_STATE_START,                // entry point to the state machine
    APP_STATE_MAIN_MENU,            // main menu
    APP_STATE_GAME_INITIATE,        // start as initiator
    APP_STATE_GAME_PARTICIPATE,     // start as participant
    APP_STATE_CONNECTING,           // connecting menu / status screen
    APP_STATE_GAME,                 // the game
    APP_STATE_SHUTDOWN              // shutdown of the application
};

#endif // !APP_STATES_H_INCLUDED

