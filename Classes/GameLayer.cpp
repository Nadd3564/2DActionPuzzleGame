#include "GameLayer.h"
#include "SimpleAudioEngine.h"

#define WISP_INIT_POS ccp(100 ,150)
#define WISP_STRETCH_LENGTH 50

#define CROSS_POS1 ccp(80, 135)
#define CROSS_POS2 ccp(125, 140)

USING_NS_CC;
using namespace CocosDenshion;
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

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Resources/BGM1.mp3", true);

    this->initPhysics();

	Game::Instance()->getStateMachine()->pushState(new NormalState());

    //�V���O���^�b�v���[�h
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::update));
 
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
	addChild(Game::Instance()->instantiateBackground(), kOrder_Background, kTag_Background);
	//�n�ʂ̐���
	addChild(Game::Instance()->instantiateGround(_body, _world, getChildByTag(kTag_Background)));
	instantiateWisp();
	instantiateObstacleWithEnemy();
}

void GameLayer::instantiateWisp(){
	//�E�B�X�v����
	_wisp = new Player(this);
	_wisp->autorelease();
	_wisp->initWithFile("wisp_1.png");
	_wisp->setPosition(WISP_INIT_POS);
	_wisp->setTag(kTag_Wisp);
	_wisp->setZOrder(kOrder_Wisp);

	//�����{�f�B����
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_wisp->getPositionX() / PTM_RATIO,
                               _wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = _wisp; 
	_body = _world->CreateBody(&bodyDef);

	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
    spriteShape.m_radius = _wisp->getContentSize().width * 0.3 / PTM_RATIO;

	//��������
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    
	_wisp->setRigidBody(_body);
	addChild(_wisp);
	Game::Instance()->addGameObjectMap("wisp", _wisp);
	Game::Instance()->addGameObject(_wisp);


	//���ˑ��ǉ�
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	addChild(cross1, kOrder_Cross1);

	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(cross1->getPosition());
	addChild(cross2, kOrder_Cross2);
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


void GameLayer::instantiateObstacleWithEnemy(){
	//�G�l�~�[����
	this->addChild(Enemy::create(this, ccp(636, 125), 
					"enemy2.png", kTag_Enemy), kOrder_Enemy);
	
	//��Q������
	instantiateObstacle(ObstacleType::Obstacle4, ccp(536, 75), 0);
	instantiateObstacle(ObstacleType::Obstacle4, ccp(636, 75), 0);
	instantiateObstacle(ObstacleType::Obstacle4, ccp(736, 75), 0);

	instantiateObstacle(ObstacleType::Obstacle1, ccp(586, 150), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(586, 250), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(686, 150), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(686, 250), 90);
	instantiateObstacle(ObstacleType::Obstacle3, ccp(636, 325), 0);
}

void GameLayer::instantiateObstacle(int obstacle, cocos2d::CCPoint pos, float angle){
	std::string fileName;

	switch (obstacle)
	{
	case GameLayer::Obstacle1:
		fileName = "stone1.png";
		break;
	case GameLayer::Obstacle2:
		fileName = "isi.png";
		break;
	case GameLayer::Obstacle3:
		fileName = "pumpkin.png";
		break;
	case GameLayer::Obstacle4:
		fileName = "baseStone1.png";
		break;
	default:
		break;
	}

	//��Q���̐���
	RigidSprite* obstacles = new RigidSprite();
	obstacles->autorelease();
	obstacles->initWithFile(fileName.c_str());
	obstacles->setPosition(pos);
	obstacles->setRotation(angle);
	obstacles->setTag(kTag_Obstacles);

	//�����{�f�B����
	 b2BodyDef bodyDef;

	 switch(obstacle)
	 {
		case ObstacleType::Obstacle1:
		case ObstacleType::Obstacle2:
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.angle = 50 / PTM_RATIO;
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 0.49/ PTM_RATIO, obstacles->getContentSize().height * 0.45/ PTM_RATIO);
			_body->CreateFixture(&spriteShape, 1);
				

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}

		case ObstacleType::Obstacle3:
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);
			

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 0.5 / PTM_RATIO, obstacles->getContentSize().height * 0.3 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 2);

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break; 
		}

		default:
		{
			bodyDef.type = b2_staticBody;
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 0.5 / PTM_RATIO, obstacles->getContentSize().height * 0.5 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 3);

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}
	 }
    
	 obstacles->setRigidBody(_body);
	 addChild(obstacles, (int)kOrder::kOrder_Obstacles);
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
	Game::Instance()->getStateMachine()->update();
    //�t���[������World�̏����X�V
	float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 10;
    int32 positionIterations = 10;
    _world->Step(timeStep, velocityIterations, positionIterations);
 
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
			CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

