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
	_gl->setWisp(Player::create());
	//エネミー生成
	_gl->setEnemy(Enemy::create(ccp(636, 125), "enemy2.png"));
	//背景生成
	_gl->setStaticSprite(_gm->initBackground());
	//地面生成
	_gl->setGround(_gm->initGround());
	//発射台生成
	_gl->setStaticSprite(_gl->getWisp()->initCrossOne());
	_gl->setStaticSprite(_gl->getWisp()->initCrossTwo());
    return true;
}

void NormalState::stateUpdate(float dt) {
    std::vector<GameObject*> gameObjects = Game::Instance()->getGameObjects();
	for (std::vector<GameObject*>::iterator it = gameObjects.begin() ; it != gameObjects.end(); ++it){
        // Game::Instance()->getStateMachine()->changeState(new AlarmState());
		(*it)->stateUpdate(dt);
	}
}

bool NormalState::onTouchBeganEvent(){
	return _gl->getWisp()->wispTouchBegan();
}

void NormalState::onTouchMovedEvent(){
	_gl->getWisp()->wispTouchMoved();
}

void NormalState::onTouchEndedEvent(){
	_gl->getWisp()->wispTouchEnded();
}



bool NormalState::onStateExit() {
    return true;
}

