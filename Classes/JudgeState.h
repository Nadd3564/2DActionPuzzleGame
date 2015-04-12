/*
* JudgeState.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/


#ifndef _EN_JudgeState_
#define _EN_JudgeState_

#include "GameState.h"

class JudgeState : public GameState
{
public:

	JudgeState();
	virtual ~JudgeState();

	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent);
	virtual void onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent);
	virtual void onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent);

	virtual std::string getStateID(){ return s_judgeID; }

	void calcRemaining(int &remaining);
	void next(CCObject *pSender);

private:

	bool m_isClear;
	float m_timer;
	static const std::string s_judgeID;

	void s_JudgeToNormal();
	void onResult();
	void failed();
	bool calcTimer(float value);

};

#endif /* defined(_EN_JudgeState_) */