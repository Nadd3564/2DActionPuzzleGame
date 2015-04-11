#include "GameLayer.h"

USING_NS_CC;

GameLayer* GameLayer::s_pInstance = 0;

GameLayer::GameLayer():
m_pWisp(NULL)
{

}

GameLayer::~GameLayer()
{
	delete m_pWorld;
	m_pWorld = NULL;

	delete m_pCollisionListener;
	m_pCollisionListener = NULL;
}

//�V�[������
CCScene* GameLayer::createScene(int zanki, int level)
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create(zanki, level);
	scene->addChild(layer);

	ObjectManager *gm = OM::getInstance();
	gm->init();
    scene->addChild(gm);
   
	HudLayer *hud = new HudLayer();
	hud->init();
	scene->addChild(hud);
	layer->m_pHud = hud;

	return scene; 
}

GameLayer* GameLayer::create(int zanki, int level){
	GameLayer *layer = new GameLayer();
	layer->init(zanki, level);
	layer->autorelease();

	return layer;
}

bool GameLayer::init(int zanki, int level)
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	m_zanki = zanki;
	m_level = level;

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

void GameLayer::onEnter(){
	CCLayer::onEnter();
	this->m_pWisp = dynamic_cast<Player *>(this->getChildByTag(kTag_Wisp));
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

