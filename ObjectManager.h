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
#include <map>
#include <cocos2d.h>
#include "GameObject.h"

USING_NS_CC;

class ObjectManager : public cocos2d::CCLayer
{
public:
    
    static ObjectManager* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new ObjectManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
    bool init();
    void update(float dt);
    void clean();
    bool handleBeganEvents();
	void handleMovedEvents();
	void handleEndedEvents();

    void setGameObjectPosition(const cocos2d::CCPoint &pts);
    void setTileMap(cocos2d::CCTMXTiledMap* tileMap);
    void setGameObjectStrategy();
    
    void addGameObjectMap(std::string id, GameObject* sprite);
    void addGameObject(GameObject* sprite);
    
    std::vector<GameObject*> getGameObjects();
    std::map<std::string, GameObject*> getGameObjectMap();
    GameObject* findGameObject(std::string id);
    cocos2d::CCTMXTiledMap* getTileMap();
    
    StateMachine* getStateMachine() { return m_pStateMachine; }
    
    CC_SYNTHESIZE(int, m_playerLives, PlayerLives);
    CC_SYNTHESIZE(int, m_nextLevel, NextLevel);
    CC_SYNTHESIZE(bool, m_bLevelComplete, LevelComplete);
    
    void setCurrentLevel(int currentLevel);
    int getCurrentLevel() { return m_currentLevel;}
    
    std::vector<std::string> getLevelFiles() { return m_levelFiles; }
    
	CCSprite* initBackground();
	CCNode* initGround(b2Body* _body, b2World* _world, CCNode* kTag);
	b2BodyDef groundBodyDef();
	b2EdgeShape groundShape();

private:
    
    StateMachine* m_pStateMachine;
    static ObjectManager* s_pInstance;
    
    std::vector<GameObject*> m_gameObjects;
    std::map<std::string, GameObject*> m_gameObjectMap;
    
    cocos2d::CCTMXTiledMap *_tileMap;
    
    int m_currentLevel;

    std::vector<std::string> m_levelFiles;
    
    ObjectManager();
    ~ObjectManager();
    
    ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
    
    ObjectManager(const cocos2d::CCSprite*);
};

typedef ObjectManager Game;

#endif /* defined(__ObjectManager__) */
