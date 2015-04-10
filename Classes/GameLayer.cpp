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

//シーン生成
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
	
    //シングルタップモード
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    this->scheduleUpdate();
	
    return true;
}

void GameLayer::initPhysics(){
	//重力
	b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
	m_pWorld = new b2World(gravity);
	//動きが止まった物体について、計算を省略
	m_pWorld->SetAllowSleeping(true);
	//オブジェクトの衝突判定をする時にすり抜けないように調整して計算する。
	m_pWorld->SetContinuousPhysics(true);
	//衝突イベントハンドラー
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
	//鎖を削除
	removeChildByTag(kTag_Chain1);
	removeChildByTag(kTag_Chain2);
}

void GameLayer::collisionWisp(){
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

void GameLayer::destroyEnemy(CCNode *enemy){
	if (!enemy){
		return;
	}
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

void GameLayer::update(float dt)
{}

