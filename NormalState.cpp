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

using namespace cocos2d;

const std::string NormalState::s_normalID = "NORMAL";

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState() {
	CC_SAFE_RELEASE(_enemy);
}

	//初期化
bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	//ウィスプ生成
	_wisp = Player::create();
	//エネミー生成
	Enemy::create(ccp(436, 125), "enemy2.png")->addEnemy();
	//背景生成
	OM::getInstance()->initBackground();
	//地面生成
	OM::getInstance()->initGround();
	//発射台生成
	_wisp->initCrossOne();
	_wisp->initCrossTwo();
	//障害物生成
	Obstacles::create(Obstacle4, ccp(536, 75), 0)->addObstacles();
	
	
	//コンテナにゲームオブジェクトを代入
	m_gObjects = OM::getInstance()->getGameObjects();
	
	return true;
}

void NormalState::stateUpdate(float dt) {
	//_gObjectsに追加されたゲームオブジェクトから関数を呼び出す
	/*for (std::vector<GameObject*>::iterator it = m_gObjects.begin(); it != m_gObjects.end(); it++){
		// Game::Instance()->getStateMachine()->changeState(new AlarmState());
		if (!(*it)){
			return;
		}
		(*it)->stateUpdate(dt);
	}*/
	
}

bool NormalState::onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent){
	return _wisp->wispTouchBegan(pTouch, pEvent);
}

void NormalState::onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent){
	_wisp->wispTouchMoved(pTouch, pEvent);
}

void NormalState::onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent){
	_wisp->wispTouchEnded(pTouch, pEvent);
}


	//状態遷移時の処理
bool NormalState::onStateExit() {
    return true;
}

