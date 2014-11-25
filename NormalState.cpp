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
}

NormalState::~NormalState() {
    
}

void NormalState::stateUpdate(float dt) {
    std::vector<GameObject*> gameObjects = Game::Instance()->getGameObjects();
	for (std::vector<GameObject*>::iterator it = gameObjects.begin() ; it != gameObjects.end(); ++it){
        // Game::Instance()->getStateMachine()->changeState(new AlarmState());
		(*it)->stateUpdate(dt);
	}
}

bool NormalState::onTouchBeganEvent(){
	Player* wisp = GameLayer::Instance()->getWisp();
	return wisp->wispTouchBegan();
}

void NormalState::onTouchMovedEvent(){
	GameLayer::Instance()->getWisp()->wispTouchMoved();
}

void NormalState::onTouchEndedEvent(){
	GameLayer::Instance()->getWisp()->wispTouchEnded();
}

bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
    return true;
}

bool NormalState::onStateExit() {
    return true;
}

