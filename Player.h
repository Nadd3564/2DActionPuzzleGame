//
//  Player.h
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __Player__
#define __Player__

#define WISP_SET_POS ccp(100 ,150)
#define WISP_EXTEND 50

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

class Player : public GameObject
{
public:
	Player(GameLayer* game);
	~Player();
	virtual void stateUpdate(float dt);
	static Player* create();
    b2BodyDef wispBodyDef(Player* wisp);
	b2FixtureDef wispFixtureDef(b2Shape* shape);
	CCSprite* initCrossOne();
	CCSprite* initCrossTwo();
	virtual void update (float dt);

	void addForceToWisp(CCNode* wisp);
	bool wispTouchBegan();
	void wispTouchMoved();
	void wispTouchEnded();
	void setChainOne(CCNode* chain1, CCPoint pos);
	void setChainTwo(CCNode* chain2, CCPoint pos);
	CCNode* visibleChainOne();
	CCNode* visibleChainTwo();
	CCPoint processingPosition(CCPoint touch);

private:
	Player* initWisp();
};

#endif /* defined(__Player__) */
