//
//  NormalState.cpp
//  TileGame
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
	_gl = GameLayer::Instance();
	_gm = Game::Instance();
}

NormalState::~NormalState() {
    
}

bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	//ウィスプ生成
	_wisp = Player::create();
	//エネミー生成
	Enemy::create(ccp(636, 125), "enemy2.png");
	Enemy::create(ccp(636, 335), "enemy1.png");
	//背景生成
	_gl->setStaticSprite(_gm->initBackground());
	//地面生成
	_gl->setGround(_gm->initGround());
	//発射台生成
	_gl->setStaticSprite(_gl->getWisp()->initCrossOne());
	_gl->setStaticSprite(_gl->getWisp()->initCrossTwo());

	_gObjects = _gm->getGameObjects();

    return true;
}

void NormalState::stateUpdate(float dt) {
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



bool NormalState::onStateExit() {
    return true;
}

