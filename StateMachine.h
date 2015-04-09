//
//  StateMachine.h
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
    void update(float dt);
	bool onBeganEvent(CCTouch* pTouch, CCEvent* pEvent);
	void onMovedEvent(CCTouch* pTouch, CCEvent* pEvent);
	void onEndedEvent(CCTouch* pTouch, CCEvent* pEvent);
 
private:

    std::vector<GameState*> m_gameStates;

};

typedef StateMachine theStateMachine;

#endif /* defined(__StateMachine__) */
