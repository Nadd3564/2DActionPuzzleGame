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
#include "CollisionListener.h"

USING_NS_CC;

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
	kOrder_Smoke,
	kOrder_Star,
	kOrder_Result
};

class GameLayer : public CCLayer
{
private:
   
	static GameLayer* s_pInstance;

    Player * m_pWisp;

    Enemy * m_pEnemy;
	
	HudLayer *m_pHud;
     
    int m_numCollected;

	b2ContactListener *m_pCollisionListener;

public:

	enum Status {
		kNormal = 0,
		kAlarm,
		kEnegyDrink,
	};

	int m_zanki;
	int m_level;

	CC_SYNTHESIZE(b2World *, m_pWorld, World);
	CC_SYNTHESIZE(b2Body *, m_pBody, Body);

	GameLayer();
	virtual ~GameLayer();

    static GameLayer* getInstance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new GameLayer();
            return s_pInstance;
        }
        
		assert(s_pInstance != NULL);
		return s_pInstance;
    }

	static cocos2d::CCScene* createScene(int zanki, int level);
	void initPhysics();
	virtual bool init(int zanki, int level);
	static GameLayer* create(int zanki, int level);
	virtual void update(float dt);
	
    virtual void onEnter();
	void removeChain();

	void collisionWisp();
	void destroyEnemy(CCNode *enemy);
	void level(int level);
	void StageClear();
	void StageFailed();
	
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);

};

typedef GameLayer GAME;

#endif /* defined(_EN_GameLayer_) */