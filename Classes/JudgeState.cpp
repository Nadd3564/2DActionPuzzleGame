/*
* JudgeState.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#include "JudgeState.h"
#include "NormalState.h"
#include "Player.h"
#include "GameLayer.h"
#include "TitleLayer.h"


using namespace cocos2d;

const std::string JudgeState::s_judgeID = "JUDGE";

JudgeState::JudgeState():
m_timer(0),
m_isClear(false)
{}

JudgeState::~JudgeState() {}

//‰Šú‰»
bool JudgeState::onStateEnter()
{
	CCLog("Judge");
	return true;
}

void JudgeState::stateUpdate(float dt)
{
	CCNode *enemy = GAME::getInstance()->getChildByTag(kTag_Enemy);
	if (!enemy && calcTimer(150))
	{
		onResult();
	}
	else if (calcTimer(600))
	{
		failed();
	}
}

bool JudgeState::onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	return true;
}

void JudgeState::onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void JudgeState::onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent)
{
	if (m_isClear)
		return;

	failed();
}

bool JudgeState::onStateExit()
{
	return true;
}

bool JudgeState::calcTimer(float value)
{
	if (++m_timer >= value)
		return true;
	return false;
}

void JudgeState::onResult()
{
	m_isClear = true;
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *clear;
	if (!GAME::getInstance()->getChildByTag(kTag_Clear)){
		clear = CCSprite::create("clear.png");
		clear->setPosition(screenSize / 2);
		clear->setOpacity(0);
		GAME::getInstance()->addChild(clear, kOrder_Result, kTag_Clear);
	}
	

	CCFadeIn *fadein = CCFadeIn::create(0.5);
	CCDelayTime *delay = CCDelayTime::create(1.0);
	CCFadeOut *fadeout = CCFadeOut::create(0.5);
	CCCallFuncN *cb = CCCallFuncN::create(this, callfuncN_selector(JudgeState::next));
	CCSequence *seq = CCSequence::create(fadein, delay, fadeout, cb, NULL);
	clear->runAction(seq);
}

void JudgeState::failed()
{
	ObjectManager *om = OM::getInstance();
	if (om->isFailed()){
		om->destroyWisp();
		om->removeFromParent();
		CCScene *scene = TitleLayer::createScene();
		CCTransitionFade *turn = CCTransitionFade::create(3.0, scene);
		CCDirector::sharedDirector()->replaceScene(turn);
	}
	else if (om->getRemaining() > 0)
		s_JudgeToNormal();
	return;
}

void JudgeState::s_JudgeToNormal()
{
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void JudgeState::next(CCObject *pSender)
{
	ObjectManager *om = ObjectManager::getInstance();
	int nextLevel = om->getLevel();
	if (nextLevel >= 3){
		nextLevel = 1;
	}
	else
	{
		nextLevel += 1;
	}

	om->destroyWisp();
	om->removeRemaining();
	om->removeFromParent();
	CCScene *scene = GameLayer::createScene(3, nextLevel);
	CCDirector::sharedDirector()->replaceScene(scene);
}