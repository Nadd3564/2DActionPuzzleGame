//
//  NormalState.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "NormalState.h"
#include "cocos2d.h"

using namespace cocos2d;

const std::string NormalState::s_normalID = "NORMAL";

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState() {
    
}

void NormalState::stateUpdate() {
    std::vector<GameObject*> gameObjects = Game::Instance()->getGameObjects();
    for (std::vector<GameObject*>::iterator it = gameObjects.begin() ; it != gameObjects.end(); ++it){
        // ここで各ゲームオブジェクト＝NPCのアップデートを行います。
        // 人工知能的な動作については
        // Game::Instance()->getStateMachine()->changeState(new AlarmState());
        // をお使いください。
		}
}

void NormalState::onInputEvent(CCPoint* diff) {
	_tileWidth = Game::Instance()->getTileMap()->getTileSize().width;
    _tileHeight = Game::Instance()->getTileMap()->getTileSize().height;
    _mapWidth = Game::Instance()->getTileMap()->getMapSize().width;
    _mapHeight = Game::Instance()->getTileMap()->getMapSize().height;
    
    Player* player = dynamic_cast<Player*>( Game::Instance()->findGameObject("player"));
	Player* wisp = dynamic_cast<Player*>(Game::Instance()->findGameObject("wisp"));
    CCPoint playerPos = player->getPosition();
    
    player->setPlayerPosition(diff, playerPos, _tileWidth,_tileHeight, _mapWidth, _mapHeight);
}

bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
    return true;
}

bool NormalState::onStateExit() {
    return true;
}

