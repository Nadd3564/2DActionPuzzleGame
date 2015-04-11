//
//  ObjectManager.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#define SCREENSIZE CCDirector::sharedDirector()->getWinSize()

#include "ObjectManager.h"
#include "NormalState.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

ObjectManager* ObjectManager::s_pInstance = 0;

ObjectManager::ObjectManager():
m_remaining(3),
m_level(1),
m_pStateMachine(0)
{
	//状態マシーンの初期化
    m_pStateMachine = new StateMachine();
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::init(int remaining, int level)
{
	if (!CCLayer::init()){
		return false;
	}
	
	setRemaining(remaining);
	setLevel(level);
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (!engine->isBackgroundMusicPlaying())
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("homura.mp3", true);
	//初期状態を追加し、状態を初期化
	m_pStateMachine->pushState(new NormalState());
	
	remainingCount();

	this->scheduleUpdate();

	return true;
}

void ObjectManager::update(float dt)
{
	//ワールドを更新
	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	b2World *world = GAME::getInstance()->getWorld();
	world->Step(dt, velocityIterations, positionIterations);

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			RigidSprite* myActor = (RigidSprite *)b->GetUserData();
			if ((myActor->getTag() == kTag_Enemy) && (myActor->getIsDead())){
				world->DestroyBody(b);
				myActor->removeFromParent();
				continue;
			}
			myActor->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

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
	CCSprite *star = CCSprite::create("star2.png");
	star->setPosition(GAME::getInstance()->getChildByTag(kTag_Wisp)->getPosition());
	star->setScale(0);
	star->setOpacity(127);
	GAME::getInstance()->addChild(star, kOrder_Star);

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
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_system45.mp3");

	CCSprite *destEnemy = CCSprite::create("enemy1.png");
	destEnemy->setPosition(enemy->getPosition());
	addChild(destEnemy, kOrder_Enemy);

	CCSequence *sequence = CCSequence::create(CCScaleTo::create(0.3, 0), CCRemoveSelf::create(), nullptr);
	destEnemy->runAction(sequence);

	CCSprite *dying = CCSprite::create("dying1.png");
	dying->setPosition(destEnemy->getPosition());
	addChild(dying, kOrder_dying);

	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("dying1.png");
	animation->addSpriteFrameWithFileName("dying2.png");
	animation->addSpriteFrameWithFileName("dying3.png");
	animation->setDelayPerUnit(0.15);

	CCSpawn *spawn = CCSpawn::create(CCAnimate::create(animation), CCFadeOut::create(0.45), nullptr);
	CCSequence *smokeSequence = CCSequence::create(spawn, CCRemoveSelf::create(), nullptr);

	dying->runAction(smokeSequence);

	Enemy *enemys = dynamic_cast<Enemy *>(enemy);
	enemys->setIsDead(true);
}

void ObjectManager::shotSE()
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_wind02.mp3");
}

void ObjectManager::reloadSE()
{
	SimpleAudioEngine::sharedEngine()->playEffect("se_maoudamashii_element_fire07.mp3");
}

bool ObjectManager::isFailed()
{
	bool ret = false;

	if (--m_remaining <= 0){
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *failed = CCSprite::create("failed.png");
		failed->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
		GAME::getInstance()->addChild(failed, kOrder_Result);
		ret = true;
	}
	else
	{
		this->removeChildByTag(m_remaining - 1);
		destroyWisp();
	}
	
	return ret;
}

void ObjectManager::destroyWisp()
{
	b2World *world = GAME::getInstance()->getWorld();
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			RigidSprite* myActor = (RigidSprite *)b->GetUserData();
			if ((myActor->getTag() == kTag_Wisp))
			{
				world->DestroyBody(b);
				myActor->removeFromParent();
				continue;
			}
		}
	}
}

void ObjectManager::onTitle(CCObject *pSender)
{
	this->removeFromParent();
	CCScene *scene = GameLayer::createScene(3, 1);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void ObjectManager::remainingCount()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < m_remaining - 1; i++){
		CCSprite *drawRemaining = CCSprite::create("remaining.png");
		drawRemaining->setPosition(ccp(((screenSize.width - 100) / 25) + (i * 40), (screenSize.height - 100) / 20));
		this->addChild(drawRemaining, kOrder_Remaining, i);
	}
}

void ObjectManager::removeRemaining()
{
	this->removeChildByTag(0);
	this->removeChildByTag(1);
}