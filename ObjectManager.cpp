//
//  ObjectManager.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "ObjectManager.h"
#include "NormalState.h"
#include "ApproachState.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

ObjectManager* ObjectManager::s_pInstance = 0;

ObjectManager::ObjectManager():
m_pStateMachine(0),
m_playerLives(3),
m_bLevelComplete(false)
{
    m_pStateMachine = new StateMachine();
    m_currentLevel = 1;
	_gameL = GameLayer::Instance();
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::init()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Resources/BGM1.mp3", true);
	//初期状態を追加し、更に初期化
	m_pStateMachine->pushState(new NormalState());
	//m_pStateMachine->changeState(new NormalState());
	return true;
}

void ObjectManager::setGameObjectPosition(const cocos2d::CCPoint &pts)
{
    for (std::vector<GameObject*>::iterator it = m_gameObjects.begin() ; it != m_gameObjects.end(); ++it)
        (*it)->setPosition(pts);
}

void ObjectManager::setTileMap(cocos2d::CCTMXTiledMap* tileMap)
{
    this->_tileMap = tileMap;
}

cocos2d::CCTMXTiledMap* ObjectManager::getTileMap()
{
    return this->_tileMap;
}

void ObjectManager::setGameObjectStrategy()
{
    //for (std::vector<GameObject*>::iterator it = m_gameObjects.begin() ; it != m_gameObjects.end(); ++it)
       // (*it)->setStrategy();
}

void ObjectManager::addGameObject(GameObject* sprite)
{
    m_gameObjects.push_back(sprite);
}

void ObjectManager::addGameObjectMap(const std::string id, GameObject* sprite)
{
    m_gameObjectMap.insert(pair<std::string, GameObject*>(id, sprite));
}

std::vector<GameObject*> ObjectManager::getGameObjects()
{
    return m_gameObjects;
}

GameObject* ObjectManager::findGameObject(std::string id)
{
    std::map<std::string, GameObject*>::iterator it = m_gameObjectMap.find(id);
    if(it != m_gameObjectMap.end()){
        return it->second;
    } else {
        return 0;
    }
}

void ObjectManager::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_pStateMachine->changeState(new NormalState());
    m_bLevelComplete = false;
}

void ObjectManager::update(float dt)
{
    m_pStateMachine->update(dt);
}

//GameLayerで呼び出しているインプットの処理
bool ObjectManager::handleBeganEvents()
{
    return m_pStateMachine->onBeganEvent();
}

void ObjectManager::handleMovedEvents(){
	m_pStateMachine->onMovedEvent();
}

void ObjectManager::handleEndedEvents(){
	m_pStateMachine->onEndedEvent();
}

void ObjectManager::clean()
{
    cout << "cleaning ObjectManager\n";
    //m_pStateMachine->clean();
    m_pStateMachine = 0;
    delete m_pStateMachine;

}

CCSprite* ObjectManager::initBackground(){
	//背景の設定
	CCSprite* background = CCSprite::create("background1.png");
	background->setAnchorPoint(ccp(0.0, 0.5));
	background->setPosition(ccp(0, WINSIZE.height / 2));
	background->setTag(_gameL->kTag_Background);
	background->setZOrder(_gameL->kOrder_Background);
	_gameL->setSprite(background);
	return background;
}

//地面生成
CCNode* ObjectManager::initGround(){
	//物理ボディ生成
	b2Body* body = _gameL->getWorld()->CreateBody(&groundBodyDef());
	
	// 地面の形と大きさの定義
    b2EdgeShape groundBox = groundShape();

	//物理性質
	b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.8;
	body->CreateFixture(&fixtureDef);
	
	//地面ノード作成
	CCNode* node = CCNode::create();
	node->setAnchorPoint(ccp(0.5, 0.5));
	node->setPosition(ccp(_gameL->getBgTag()->getContentSize().width / 2, 25));
	_gameL->setNode(node);
	return node;
}

//物理ボディ生成
b2BodyDef ObjectManager::groundBodyDef(){
	 b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	return groundBodyDef;
}

// 地面の形と大きさの定義
b2EdgeShape ObjectManager::groundShape(){
	b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, WINSIZE.height * 0.1 / PTM_RATIO),
                  b2Vec2(WINSIZE.width / PTM_RATIO, WINSIZE.height * 0.1 / PTM_RATIO));
	return groundBox;
}
