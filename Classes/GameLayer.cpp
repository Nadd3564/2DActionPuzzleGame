/*
* GameLayer.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#include "GameLayer.h"

USING_NS_CC;

GameLayer* GameLayer::s_pInstance = 0;

GameLayer::GameLayer(){}

GameLayer::~GameLayer()
{
	delete m_pWorld;
	m_pWorld = NULL;

	delete m_pCollisionListener;
	m_pCollisionListener = NULL;
}

//�V�[������
CCScene* GameLayer::createScene(int remaining, int level)
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);

	ObjectManager *gm = OM::getInstance();
	gm->init(remaining, level);
	scene->addChild(gm);
   
	HudLayer *hud = new HudLayer();
	hud->init();
	scene->addChild(hud);
	layer->m_pHud = hud;

	return scene; 
}

GameLayer* GameLayer::create(){
	GameLayer *layer = new GameLayer();
	if (layer && layer->init()){
		layer->autorelease();
		return layer;
	}
	
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	GameLayer::s_pInstance = this;

    this->initPhysics();
	
    //�V���O���^�b�v���[�h
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    this->scheduleUpdate();
	
    return true;
}

void GameLayer::initPhysics(){
	//�d��
	b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
	m_pWorld = new b2World(gravity);
	//�������~�܂������̂ɂ��āA�v�Z���ȗ�
	m_pWorld->SetAllowSleeping(true);
	//�I�u�W�F�N�g�̏Փ˔�������鎞�ɂ��蔲���Ȃ��悤�ɒ������Čv�Z����B
	m_pWorld->SetContinuousPhysics(true);
	//�Փ˃C�x���g�n���h���[
	m_pCollisionListener = new CollisionListener();
	m_pWorld->SetContactListener(m_pCollisionListener);
}

bool GameLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	return OM::getInstance()->handleBeganEvents(pTouch, pEvent);
}

void GameLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	OM::getInstance()->handleMovedEvents(pTouch, pEvent);
}

void GameLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	OM::getInstance()->handleEndedEvents(pTouch, pEvent);
}

void GameLayer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

void GameLayer::removeChain(){
	//�����폜
	removeChildByTag(kTag_Chain1);
	removeChildByTag(kTag_Chain2);
}

void GameLayer::update(float dt)
{}

