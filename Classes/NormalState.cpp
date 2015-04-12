//
//  NormalState.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "NormalState.h"
#include "cocos2d.h"
#include "Player.h"
#include "GameLayer.h"
#include "TitleLayer.h"
#include "JudgeState.h"

USING_NS_CC;

const std::string NormalState::s_normalID = "NORMAL";

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState() {
}

void NormalState::s_normalToJudge() {
	OM::getInstance()->getStateMachine()->changeState(new JudgeState());
}

	//初期化
bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	int level = OM::getInstance()->getLevel();
	//ウィスプ生成
	m_pWisp = Player::create();
	if (OM::getInstance()->getRemaining() != 3)
		return false;
	//エネミー生成
	Enemy::create(ccp(836, 325), "enemy2.png")->addEnemy();
	//背景生成
	OM::getInstance()->initBackground();
	//地面生成
	OM::getInstance()->initGround();
	//発射台生成
	m_pWisp->initCrossOne();
	m_pWisp->initCrossTwo();
	//障害物生成
	Obstacles::create(length, ccp(-100, -100), 0)->addObstacles(level);
	
	return true;
}

void NormalState::stateUpdate(float dt)
{
	CCNode *enemy = GAME::getInstance()->getChildByTag(kTag_Enemy);
	if (!enemy)
	{
		s_normalToJudge();
	}
}

bool NormalState::onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent){
	return m_pWisp->wispTouchBegan(pTouch, pEvent);
}

void NormalState::onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent){
	m_pWisp->wispTouchMoved(pTouch, pEvent);
}

void NormalState::onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent){
	m_pWisp->wispTouchEnded(pTouch, pEvent);
	s_normalToJudge();
}


	//状態遷移時の処理
bool NormalState::onStateExit() {
    return true;
}

