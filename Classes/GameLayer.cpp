#include "GameLayer.h"

USING_NS_CC;

GameLayer* GameLayer::s_pInstance = 0;

GameLayer::GameLayer() {

}

GameLayer::~GameLayer() {
    delete _world;
    _world = NULL;
}

//�V�[������
CCScene* GameLayer::createScene()
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);

	HudLayer *hud = new HudLayer();
    hud->init();
    scene->addChild(hud);
    layer->_hud = hud;

	ObjectManager *gm = ObjectManager::Instance();
	gm->init();
    scene->addChild(gm);
    layer->_gm = gm;
   
	return scene; 
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

    scheduleUpdate();
	
    return true;
}

void GameLayer::initPhysics(){
	//�d��
	b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    _world = new b2World(gravity);
	//�������~�܂������̂ɂ��āA�v�Z���ȗ�
    _world->SetAllowSleeping(true);
	//�I�u�W�F�N�g�̏Փ˔�������鎞�ɂ��蔲���Ȃ��悤�ɒ������Čv�Z����B
    _world->SetContinuousPhysics(true);	
}

void GameLayer::onEnter(){
	CCLayer::onEnter();
}

CCNode* GameLayer::getWispTag(){
	return getChildByTag(kTag_Wisp);
}

CCNode* GameLayer::getBgTag(){
	return getChildByTag(kTag_Background);
}

void GameLayer::setWisp(Player* wisp){
	assert(wisp != NULL);
	_wisp = wisp;
	this->addChild(_wisp);
}

void GameLayer::setEnemy(Enemy* enemy){
	assert(enemy != NULL);
	_enemy = enemy;
	this->addChild(_enemy, kTag_Enemy);
}

void GameLayer::setNode(CCNode* node){
	assert(node != NULL);
	this->addChild(node);
}

void GameLayer::setSprite(CCSprite* sprite){
	assert(sprite != NULL);
	this->addChild(sprite);
}

void GameLayer::setObstacles(Obstacles* obs){
	assert(obs != NULL);
	obs->setZOrder((int)kOrder::kOrder_Obstacles);
	this->addChild(obs);
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
	this->_beganTouch = touch;
	return _gm->handleBeganEvents();
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
	this->_movedTouch = touch;
	_gm->handleMovedEvents();
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){
	this->_endedTouch = touch;
	_gm->handleEndedEvents();
}

void GameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event){
	ccTouchEnded(touch, event);
}

void GameLayer::removeChain(){
	//�����폜
	removeChildByTag(kTag_Chain1);
	removeChildByTag(kTag_Chain2);
}

CCNode* GameLayer::getChainOneTag(){
	return getChildByTag(kTag_Chain1);
}

CCNode* GameLayer::getChainTwoTag(){
	return getChildByTag(kTag_Chain2);
}

void GameLayer::update(float dt)
{
	_gm->update(dt);
	//���[���h���X�V
	int32 velocityIterations = 10;
    int32 positionIterations = 10;
	_world->Step(dt, velocityIterations, positionIterations);
 
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
			CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

