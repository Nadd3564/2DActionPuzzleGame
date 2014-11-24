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
	static Player* create(GameLayer* game, CCPoint position, const char* fileName, int kTag, int kOrder);
    b2BodyDef wispBodyDef(Player* wisp);
	b2FixtureDef wispFixtureDef(b2Shape* shape);
	CCSprite* initCrossOne();
	CCSprite* initCrossTwo();
	virtual void update (float dt);
    void setPlayerPosition(cocos2d::CCPoint* diff, cocos2d::CCPoint playerPos,
                           float tileWidth, float tileHeight, float mapWidth, float mapHeight);

	void addForceToWisp(cocos2d::CCNode* wisp);

private:
	Player* initWisp(GameLayer* game, CCPoint position, const char* fileName, int kTag, int kOrder);
};

#endif /* defined(__TileGame__Player__) */
