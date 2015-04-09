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
    
    static ObjectManager* getInstance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new ObjectManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    bool init();
    virtual void update(float dt);
	
	bool handleBeganEvents(CCTouch* pTouch, CCEvent* pEvent);
	void handleMovedEvents(CCTouch* pTouch, CCEvent* pEvent);
	void handleEndedEvents(CCTouch* pTouch, CCEvent* pEvent);

    void addGameObject(GameObject* sprite);
    std::vector<GameObject*> getGameObjects();
	StateMachine* getStateMachine() { return m_pStateMachine; }
    
	CCSprite* initBackground();
	CCNode* initGround();
	b2BodyDef groundBodyDef();
	b2EdgeShape groundShape();

private:
    
	ObjectManager();
	virtual ~ObjectManager();

    StateMachine* m_pStateMachine;
    static ObjectManager* s_pInstance;
	
    std::vector<GameObject*> m_gameObjects;
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
    ObjectManager(const cocos2d::CCSprite*);
};

typedef ObjectManager OM;

#endif /* defined(__ObjectManager__) */
