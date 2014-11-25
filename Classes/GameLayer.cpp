#include "GameLayer.h"

#define WISP_INIT_POS ccp(100 ,150)
#define WISP_STRETCH_LENGTH 50

#define CROSS_POS1 ccp(80, 135)
#define CROSS_POS2 ccp(125, 140)

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
	Game::Instance()->init();
	Game::Instance()->getStateMachine()->pushState(new NormalState());

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
	
	//�w�i�̐ݒ�
	this->addChild(Game::Instance()->initBackground());
	//�n�ʂ̐���
	this->addChild(Game::Instance()->initGround(_body, _world, getChildByTag(kTag_Background)));
	//�E�B�X�v�Ɣ��ˑ䐶��
	this->addChild(_wisp);
	this->addChild(_wisp->initCrossOne(), kOrder_Cross1);
	this->addChild(_wisp->initCrossTwo(), kOrder_Cross2);
	//�G�l�~�[����
	this->addChild(_enemy, kTag_Enemy);
	//��Q�I�u�W�F�N�g����
	initObstacles();
}

void GameLayer::setWisp(Player* wisp){
	_wisp = wisp;
}

void GameLayer::setEnemy(Enemy* enemy){
	_enemy = enemy;
}

CCPoint GameLayer::processingPosition(CCPoint touch){
	//�E�B�X�v�̏����ʒu�ƃ^�b�v�ʒu�̋���
	int distance = touch.getDistance(WISP_INIT_POS);

	if(distance > WISP_STRETCH_LENGTH)
		//������WISP_STRETCH_LENGTH�ƂȂ�ʒu��Ԃ�
		return WISP_INIT_POS + (touch - WISP_INIT_POS) * WISP_STRETCH_LENGTH / distance;
	else
		//�^�b�v�ʒu��Ԃ�
		return touch;
}


void GameLayer::initObstacles(){
	
	//��Q������
	addChild(Obstacles::create(ObstacleType::Obstacle4, ccp(536, 75), 0), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle4, ccp(636, 75), 0), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle4, ccp(736, 75), 0), (int)kOrder::kOrder_Obstacles);

	addChild(Obstacles::create(ObstacleType::Obstacle1, ccp(586, 150), 90), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle1, ccp(586, 250), 90), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle1, ccp(686, 150), 90), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle1, ccp(686, 250), 90), (int)kOrder::kOrder_Obstacles);
	addChild(Obstacles::create(ObstacleType::Obstacle3, ccp(636, 325), 0), (int)kOrder::kOrder_Obstacles);
}



bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
	bool flg = false;
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp && wisp->boundingBox().containsPoint(touch->getLocation()))
	{
		//�E�B�X�v�̈ʒu���v�Z
		wisp->setPosition(processingPosition(touch->getLocation()));
		flg = true;
	}

	return flg;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp)
	{
		wisp->setPosition(processingPosition(touch->getLocation()));

		//���������|�C���g
		float angle = ((WISP_INIT_POS - wisp->getPosition()).getAngle());
		CCPoint pos = wisp->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(angle));

		//����\��
		CCNode* chain1 = getChildByTag(kTag_Chain1);
		if(!chain1)
		{
			chain1 = CCSprite::create("iron.png");
			addChild(chain1, kOrder_Chain1, kTag_Chain1);
		}

		chain1->setPosition(CROSS_POS1 - (CROSS_POS1 - pos) / 2);
		chain1->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS1 - pos).getAngle() * -1));
		chain1->setScaleX(CROSS_POS1.getDistance(pos));
		chain1->setScaleY(10);

		CCNode* chain2 = getChildByTag(kTag_Chain2);
		if(!chain2)
		{
			chain2 = CCSprite::create("iron.png");
			addChild(chain2, kOrder_Chain2, kTag_Chain2);
		}

		chain2->setPosition(CROSS_POS2 - (CROSS_POS2 - pos) / 2);
		chain2->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS2 - pos).getAngle() * -1));
		chain2->setScaleX(CROSS_POS2.getDistance(pos));
		chain2->setScaleY(10);
	}
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){
	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp)
	{
		//�����폜
		removeChildByTag(kTag_Chain1);
		removeChildByTag(kTag_Chain2);

		wisp->setPosition(processingPosition(touch->getLocation()));

		//�E�B�X�v�ɗ͂�������
		_wisp->addForceToWisp(wisp);
	}
}

void GameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event){
	ccTouchEnded(touch, event);
}

void GameLayer::update(float dt)
{
	Game::Instance()->update(dt);
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

