//
//  ObjectManager.h
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __ObjectManager__
#define __ObjectManager__

#include "StateMachine.h"
#include <vector>
#include <cocos2d.h>
#include "GameObject.h"

USING_NS_CC;

class ObjectManager : public cocos2d::CCLayer
{
public:
    
	CC_SYNTHESIZE(int, m_remaining, Remaining);
	CC_SYNTHESIZE(int, m_level, Level);

    static ObjectManager* getInstance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new ObjectManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    bool init(int remining, int level);
    virtual void update(float dt);
	
	bool handleBeganEvents(CCTouch* pTouch, CCEvent* pEvent);
	void handleMovedEvents(CCTouch* pTouch, CCEvent* pEvent);
	void handleEndedEvents(CCTouch* pTouch, CCEvent* pEvent);

   StateMachine* getStateMachine() { return m_pStateMachine; }
    
	CCSprite* initBackground();
	CCNode* initGround();
	b2EdgeShape groundShape();

	void collisionWisp();
	void destroyEnemy(CCNode *enemy);
	void destroyWisp();

	void shotSE();

	void reloadSE();

	bool isFailed();

	void onTitle(CCObject *pSender);

	void remainingCount();

	void removeRemaining();

private:
    
	ObjectManager();
	virtual ~ObjectManager();

    StateMachine* m_pStateMachine;
    static ObjectManager* s_pInstance;
    std::vector<GameObject*> m_gameObjects;

	
    
};

typedef ObjectManager OM;

#endif /* defined(__ObjectManager__) */
