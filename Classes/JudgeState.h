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

	void stateUpdate(float dt) override;
	bool onStateEnter() override;
	bool onStateExit() override;
	bool onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent) override;
	void onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent) override;
	void onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent) override;

	std::string getStateID() override { return s_judgeID; }

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