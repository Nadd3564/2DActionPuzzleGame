//
//  StateMachine.h
//  TileGame
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __StateMachine__
#define __StateMachine__

#include <vector>
#include "GameState.h"

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();
    
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    void update();
    void onEvent(CCPoint * pts);
    
protected:
private:
    std::vector<GameState*> m_gameStates;
};

typedef StateMachine theStateMachine;

#endif /* defined(__StateMachine__) */