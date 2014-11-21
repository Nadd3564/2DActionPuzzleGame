#pragma once

#ifndef _EN_GameLayer_
#define _EN_GameLayer_
//#define PTM_RATIO 32.0
#define BALL_RADIUS 8.0

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "RigidSprite.h"


class GameLayer : public cocos2d::CCLayer
{
protected:

	enum kTag
	{
		kTag_Background = 1,
		kTag_Enemy,
		kTag_Wisp,
		kTag_Chain1,
		kTag_Chain2,
		kTag_Obstacles,
	};

	enum kOrder
	{
		kOrder_Background = 1,
		kOrder_Enemy,
		kOrder_Cross2,
		kOrder_Chain2,
		kOrder_Wisp,
		kOrder_Chain1,
		kOrder_Cross1,
		kOrder_Obstacles,
	};

	enum ObstacleType
	{
		Obstacle1,
		Obstacle2,
		Obstacle3,
		Obstacle4,
	};

	void instantiateBackground(); 
	void instantiateGround(); 
	void instantiateEnemy(cocos2d::CCPoint position);
	void instantiateWisp();
	cocos2d::CCPoint processingPosition(cocos2d::CCPoint touch);
	void addForceToWisp(cocos2d::CCNode* wisp);
	void instantiateObstacleWithEnemy();
	void instantiateObstacle(ObstacleType obstacle, cocos2d::CCPoint pos, float angle);
	void instantiateObs(cocos2d::CCPoint pos, float angle);
	
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

#endif // defined(_EN_GameLayer_)