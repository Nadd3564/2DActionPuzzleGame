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

	void instantiateEnemy(cocos2d::CCPoint position);
	void instantiateWisp();
	cocos2d::CCPoint processingPosition(cocos2d::CCPoint touch);
	void instantiateObstacleWithEnemy();
	void instantiateObstacle(ObstacleType obstacle, cocos2d::CCPoint pos, float angle);
	

private:
    
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

public:
	static GameLayer* s_pInstance;
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

	static cocos2d::CCScene* createScene(); 
	void initPhysics();
	virtual bool init();
	CREATE_FUNC(GameLayer); 
	CC_SYNTHESIZE(b2World *, _world, World);
	CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(GameLayer *, _game, Game);
	virtual void onEnter();
	GameLayer();
	~GameLayer();
	void update(float dt);
	

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

#endif /* defined(_EN_GameLayer_) */