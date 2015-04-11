/*
* GameLayer.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#ifndef _EN_GameLayer_
#define _EN_GameLayer_
#define BALL_RADIUS 8.0

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "HudLayer.h"
#include "ObjectManager.h"
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
	kTag_ObstaclesB,
	kTag_Clear,
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
	kOrder_dying,
	kOrder_Star,
	kOrder_Result,
	kOrder_Remaining,
};

class GameLayer : public CCLayer
{
public:

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

	static cocos2d::CCScene* createScene(int remaining, int level);
	static GameLayer* create();
	virtual bool init();
	void initPhysics();
	
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	virtual void update(float dt);
    void removeChain();
	
private:

	static GameLayer* s_pInstance;

	HudLayer *m_pHud;

	int m_numCollected;

	b2ContactListener *m_pCollisionListener;

};

typedef GameLayer GAME;

#endif /* defined(_EN_GameLayer_) */