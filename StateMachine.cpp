//
//  StateMachine.cpp
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

void StateMachine::update(float dt) {
    m_gameStates.back()->stateUpdate(dt);
}

bool StateMachine::onBeganEvent(){
	return m_gameStates.back()->onTouchBeganEvent();
}

void StateMachine::onMovedEvent(){
	m_gameStates.back()->onTouchMovedEvent();
}

void StateMachine::onEndedEvent(){
	m_gameStates.back()->onTouchEndedEvent();
}
