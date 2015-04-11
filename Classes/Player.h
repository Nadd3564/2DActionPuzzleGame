//
//  Player.h
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

	Player();
	virtual ~Player();
	
	static Player* create();
    
	CCSprite* initCrossOne();
	CCSprite* initCrossTwo();
	
	bool wispTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	void wispTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	void wispTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	
private:

	bool initWisp();

	void reloadAction();

	b2BodyDef wispBodyDef(Player* wisp);
	b2FixtureDef wispFixtureDef(b2Shape* shape);
	
	virtual void update(float dt);

	void addForceToWisp(CCNode* wisp);
	bool wispRectTouch(CCNode* wisp, CCTouch* touch);
	bool touchWithProcess(CCNode* wisp, CCTouch* touch);
	void chain(CCNode* wisp, CCTouch* touch);
	float extendAngle(CCNode* wisp);
	CCPoint extendPos(CCNode* wisp);
	void removeAndAdd(CCNode* wisp, CCTouch* touch);
	void setChainOne(CCNode* chain1, CCPoint pos);
	void setChainTwo(CCNode* chain2, CCPoint pos);
	CCNode* initChainOne(CCNode* chain1);
	CCNode* initChainTwo(CCNode* chain2);
	CCPoint calcPos(CCPoint touch);
	bool gThanPos(int dist);
	CCPoint calcRetPos(CCPoint touch, int dist);
	void physicsOnEnable();

};

#endif /* defined(__Player__) */
