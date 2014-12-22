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
	_gameL = GameLayer::Instance();
	_gm = Game::Instance();
}

NormalState::~NormalState() {
    
}

	//初期化
bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	//ウィスプ生成
	_wisp = Player::create();
	//エネミー生成
	Enemy::create(ccp(636, 125), "enemy2.png")->addEnemy();
	//背景生成
	_gm->initBackground();
	//地面生成
	_gm->initGround();
	//発射台生成
	_wisp->initCrossOne();
	_wisp->initCrossTwo();
	//障害物生成
	Obstacles::create(_gameL->Obstacle4, ccp(536, 75), 0)->addObstacles();
	
	//コンテナにゲームオブジェクトを代入
	_gObjects = _gm->getGameObjects();

    return true;
}

void NormalState::stateUpdate(float dt) {
	//_gObjectsに追加されたゲームオブジェクトから関数を呼び出す
    for (std::vector<GameObject*>::iterator it = _gObjects.begin() ; it != _gObjects.end(); ++it){
        // Game::Instance()->getStateMachine()->changeState(new AlarmState());
		(*it)->stateUpdate(dt);
	}
}

bool NormalState::onTouchBeganEvent(){
	return _wisp->wispTouchBegan();
}

void NormalState::onTouchMovedEvent(){
	_wisp->wispTouchMoved();
}

void NormalState::onTouchEndedEvent(){
	_wisp->wispTouchEnded();
}


	//状態遷移時の処理
bool NormalState::onStateExit() {
    return true;
}

