#pragma once

#ifndef _EN_GameLayer_
#define _EN_GameLayer_
#define BALL_RADIUS 8.0

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "RigidSprite.h"
#include "HudLayer.h"
#include "ObjectManager.h"
#include "NormalState.h"
#include "ApproachState.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacles.h"

USING_NS_CC;

class GameLayer : public CCLayer
{
private:
    static GameLayer* s_pInstance;

    CCTMXTiledMap *_tileMap;
    
    CCTMXLayer *_background;

    Player * _wisp;
    Enemy * _enemy;
	
    NormalState *_normalState;
    ApproachState *_approachState;

    CCTMXLayer *_meta;
    
    CCTMXLayer *_foreground;
    
    HudLayer *_hud;
    
    ObjectManager* _gm;
    
    int _numCollected;

	CCTouch* _beganTouch;

	CCTouch* _movedTouch;

	CCTouch* _endedTouch;

public:
    static GameLayer* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new GameLayer();
            return s_pInstance;
        }
        
		return s_pInstance;
    }

	
	enum Status {
        kNormal = 0,
        kAlarm,
        kEnegyDrink,
    };

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

	static cocos2d::CCScene* createScene(); 
	void initPhysics();
	virtual bool init();
	CREATE_FUNC(GameLayer); 
	CC_SYNTHESIZE(b2World *, _world, World);
	CC_SYNTHESIZE(b2Body *, _body, Body);
    virtual void onEnter();
	GameLayer();
	~GameLayer();
	void update(float dt);
	void removeChain();

	void setWisp(Player* wisp);
	void setEnemy(Enemy* enemy);
	void setSprite(CCSprite* sprite);
	void setNode(CCNode* node);
	void setObstacles(Obstacles* obs);
	CCTouch* getBeganTouch();
	CCTouch* getMovedTouch();
	CCTouch* getEndedTouch();
	CCNode* getWispTag();
	CCNode* getBgTag();
	CCNode* getChainOneTag();
	CCNode* getChainTwoTag();
	Player* getWisp();
	
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
};

#endif /* defined(_EN_GameLayer_) */