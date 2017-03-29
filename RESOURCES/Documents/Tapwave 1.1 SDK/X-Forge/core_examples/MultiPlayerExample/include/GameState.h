/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: GameState.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

// The GameState represents the state of the game for one player.

class GameState
{

public:

    GameState()
    {
        reset();
    }

    ~GameState() {}

    void reset()
    {
        mLedState = -1;
    }

    INT32 getLedState() { return mLedState; }
    void setLedState(INT32 aState) { mLedState = aState; }

protected:

    INT32 mLedState;

};

#endif //! GAMESTATE_H_INCLUDED

