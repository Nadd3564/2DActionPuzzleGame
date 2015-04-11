//
//  ObjectManager.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#define SCREENSIZE CCDirector::sharedDirector()->getWinSize()

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
m_pStateMachine(0)
{
	//状態マシーンの初期化
    m_pStateMachine = new StateMachine();
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::init()
{
	if (!CCLayer::init()){
		return false;
	}
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Resources/BGM1.mp3", true);
	//初期状態を追加し、状態を初期化
	m_pStateMachine->pushState(new NormalState());
	//m_pStateMachine->changeState(new NormalState());

	this->scheduleUpdate();

	return true;
}

void ObjectManager::addGameObject(GameObject* sprite)
{
    m_gameObjects.push_back(sprite);
}

std::vector<GameObject*> ObjectManager::getGameObjects()
{
    return m_gameObjects;
}

void ObjectManager::update(float dt)
{
	m_pStateMachine->update(dt);
}

//GameLayerで呼び出しているインプットの処理
bool ObjectManager::handleBeganEvents(CCTouch* pTouch, CCEvent* pEvent)
{
    return m_pStateMachine->onBeganEvent(pTouch, pEvent);
}

void ObjectManager::handleMovedEvents(CCTouch* pTouch, CCEvent* pEvent){
	m_pStateMachine->onMovedEvent(pTouch, pEvent);
}

void ObjectManager::handleEndedEvents(CCTouch* pTouch, CCEvent* pEvent){
	m_pStateMachine->onEndedEvent(pTouch, pEvent);
}

CCSprite* ObjectManager::initBackground(){
	//背景の設定
	CCSprite* background = CCSprite::create("background1.png");
	background->setAnchorPoint(ccp(0.0, 0.5));
	background->setPosition(ccp(0, SCREENSIZE.height / 2));
	GAME::getInstance()->addChild(background, kOrder_Background, kTag_Background);
	return background;
}

//地面生成
CCNode* ObjectManager::initGround(){
	//物理ボディ生成
	b2Body* body = GAME::getInstance()->getWorld()->CreateBody(&groundBodyDef());
	
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
	CCSprite *background = (CCSprite *)GAME::getInstance()->getChildByTag(kTag_Background);
	node->setAnchorPoint(ccp(0.5, 0.5));
	node->setPosition(ccp(background->getContentSize().width / 2, 25));
	GAME::getInstance()->addChild(node);
	return node;
}

//物理ボディ生成
b2BodyDef ObjectManager::groundBodyDef(){
	 b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	groundBodyDef.userData = this;
	return groundBodyDef;
}

// 地面の形と大きさの定義
b2EdgeShape ObjectManager::groundShape(){
	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(0, SCREENSIZE.height * 0.1 / PTM_RATIO),
                  b2Vec2(SCREENSIZE.width / PTM_RATIO, SCREENSIZE.height * 0.1 / PTM_RATIO));
	return groundBox;
}

void ObjectManager::collisionWisp(){
	CCSprite *star = CCSprite::create("star.png");
	star->setPosition(getChildByTag(kTag_Wisp)->getPosition());
	star->setScale(0);
	star->setOpacity(127);
	addChild(star, kOrder_Star);

	//animation
	CCScaleTo *scale = CCScaleTo::create(0.1, 1);
	CCFadeOut *fadeout = CCFadeOut::create(0.1);
	CCRemoveSelf *remove = CCRemoveSelf::create();
	CCSequence *sequence = CCSequence::create(scale, fadeout, remove, nullptr);
	star->runAction(sequence);
}

void ObjectManager::destroyEnemy(CCNode *enemy){
	if (!enemy){
		return;
	}
	SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");

	CCSprite *destEnemy = CCSprite::create("enemy1.png");
	destEnemy->setPosition(enemy->getPosition());
	addChild(destEnemy, kOrder_Enemy);

	CCSequence *sequence = CCSequence::create(CCScaleTo::create(0.3, 0), CCRemoveSelf::create(), nullptr);
	destEnemy->runAction(sequence);

	CCSprite *smoke = CCSprite::create("fog1.png");
	smoke->setPosition(destEnemy->getPosition());
	addChild(smoke, kOrder_Smoke);

	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("fog1.png");
	animation->addSpriteFrameWithFileName("fog2.png");
	animation->addSpriteFrameWithFileName("fog3.png");
	animation->setDelayPerUnit(0.15);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *smokeSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	smoke->runAction(smokeSequence);

	Enemy *enemys = dynamic_cast<Enemy *>(enemy);
	enemys->setIsDead(true);
}