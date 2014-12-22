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
	//�R���e�i�̍Ō�ɐV������Ԃ�ǉ�
    m_gameStates.push_back(pState);
	//�ǉ�������ԁi�R���e�i�̍Ō�j�����o���B�X�ɁA���̏�Ԃ̏�����
    m_gameStates.back()->onStateEnter();
}

void StateMachine::changeState(GameState* pState) {
	//�X�e�[�g�����݂���ꍇ
    if(!m_gameStates.empty())
    {
		//���݂̏�Ԃƈ����̏�Ԃ�����̏ꍇ�A������
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        
		//���݂̏�Ԃƈ����̏�Ԃ��Ⴄ�ꍇ�A��ԏI���̏��������s���A���݂̏�Ԃ��폜
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
			//���ݏ�Ԃ��폜�im_gameStates�j
            m_gameStates.pop_back();
        }
        
		////�R���e�i�̍Ō�ɐV������Ԃ�ǉ�
        m_gameStates.push_back(pState);
		//�ǉ�������ԁi�R���e�i�̍Ō�j�����o���B�X�ɁA���̏�Ԃ̏�����
        m_gameStates.back()->onStateEnter();
    }
}

void StateMachine::popState() {
	//�X�e�[�g�����݂���ꍇ
    if(!m_gameStates.empty())
    {
		//��ԏI���̏��������s���A���݂̏�Ԃ��폜
        if(m_gameStates.back()->onStateExit())
        {
            delete m_gameStates.back();
			//���݂̏�Ԃ��폜�im_gameStates�j
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
