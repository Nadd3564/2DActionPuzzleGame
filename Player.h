//
//  Player.h
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __Player__
#define __Player__

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

class Player : public GameObject
{
public:
	Player(GameLayer* game);
	~Player();
	virtual void stateUpdate();
	static Player* create();
    b2BodyDef wispBodyDef(Player* wisp);
	b2FixtureDef wispFixtureDef(b2Shape* shape);
	CCSprite* initCrossOne();
	CCSprite* initCrossTwo();
	virtual void update (float dt);
    void setPlayerPosition(cocos2d::CCPoint* diff, cocos2d::CCPoint playerPos,
                           float tileWidth, float tileHeight, float mapWidth, float mapHeight);

	void addForceToWisp(cocos2d::CCNode* wisp);

private:
	Player* initWisp();
};

#endif /* defined(__Player__) */
