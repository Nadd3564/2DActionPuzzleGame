//
//  StateMachine.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "StateMachine.h"

StateMachine::StateMachine(){}

StateMachine::~StateMachine(){}

void StateMachine::pushState(GameState* pState) {
	//コンテナの最後に新しい状態を追加
    m_gameStates.push_back(pState);
	//追加した状態（コンテナの最後）を取り出す。更に、その状態の初期化
    m_gameStates.back()->onStateEnter();
}

void StateMachine::changeState(GameState* pState) {
	//ステートが存在する場合
    if(!m_gameStates.empty())
    {
		//現在の状態と引数の状態が同一の場合、以降の処理を行なわない
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        
		//現在の状態と引数の状態が違う場合、状態終了の処理を実行し、現在の状態を削除
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
			//現在状態を削除
            m_gameStates.pop_back();
        }
        
		//コンテナの最後に新しい状態を追加
        m_gameStates.push_back(pState);
		//追加した状態（コンテナの最後）を取り出す。更に、その状態の初期化
        m_gameStates.back()->onStateEnter();
    }
}

void StateMachine::popState() {
	//ステートが存在する場合
    if(!m_gameStates.empty())
    {
		//状態終了の処理を実行し、現在の状態を削除
        if(m_gameStates.back()->onStateExit())
        {
			//現在の状態を削除（m_gameStates）
            delete m_gameStates.back();
			//前の状態へ戻る
            m_gameStates.pop_back();
        }
    }
}

void StateMachine::update(float dt)
{
    m_gameStates.back()->stateUpdate(dt);
}

bool StateMachine::onBeganEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	return m_gameStates.back()->onTouchBeganEvent(pTouch, pEvent);
}

void StateMachine::onMovedEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	m_gameStates.back()->onTouchMovedEvent(pTouch, pEvent);
}

void StateMachine::onEndedEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	m_gameStates.back()->onTouchEndedEvent(pTouch, pEvent);
}
