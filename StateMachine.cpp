//
//  StateMachine.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "StateMachine.h"

StateMachine::StateMachine() {
    
}

StateMachine::~StateMachine() {
    
}

void StateMachine::pushState(GameState* pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->onStateEnter();
}

void StateMachine::changeState(GameState* pState) {
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
        
        m_gameStates.push_back(pState);
        m_gameStates.back()->onStateEnter();
    }
}

void StateMachine::popState() {
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void StateMachine::update() {
    m_gameStates.back()->stateUpdate();
}

void StateMachine::onEvent(CCPoint* pts) {
    m_gameStates.back()->onInputEvent(pts);
}

