#pragma once

#ifndef _SmileyDog_GameLayer_
#define _SmileyDog_GameLayer_
//#define PTM_RATIO 32.0
#define BALL_RADIUS 8.0

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "PhysicsSprite.h"


class GameLayer : public cocos2d::CCLayer
{
protected:

	enum kTag
	{
		kTag_Background = 1,
		kTag_Enemy,
		kTag_Ball,
		kTag_Gum1,
		kTag_Gum2,
	};

	enum kOrder
	{
		kOrder_Background = 1,
		kOrder_Enemy,
		kOrder_Launcher2,
		kOrder_Gum2,
		kOrder_Ball,
		kOrder_Gum1,
		kOrder_Launcher1,
	};

	void instantiateBackground(); 
	void instantiateGround(); 
	void instantiateEnemy(cocos2d::CCPoint position);
	void instantiateBall();
	cocos2d::CCPoint processingPosition(cocos2d::CCPoint touch);
	
public:
	static cocos2d::CCScene* createScene(); 
	void initPhysics();
	virtual bool init();
	CREATE_FUNC(GameLayer); 
	CC_SYNTHESIZE(b2World *, _world, World);
	CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(GameLayer *, _game, Game);
	virtual void onEnter(); //ÉåÉCÉÑÅ[ï\é¶éûèàóù
	GameLayer();
	void update(float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

#endif // defined(_SmileyDog_GameLayer_)