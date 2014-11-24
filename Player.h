//
//  Player.h
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __TileGame__Player__
#define __TileGame__Player__

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

class Player : public GameObject
{
public:
	Player(GameLayer* game);
	~Player();
    void setPlayerPosition(cocos2d::CCPoint* diff, cocos2d::CCPoint playerPos,
                           float tileWidth, float tileHeight, float mapWidth, float mapHeight);

	void addForceToWisp(cocos2d::CCNode* wisp);
};

#endif /* defined(__TileGame__Player__) */
