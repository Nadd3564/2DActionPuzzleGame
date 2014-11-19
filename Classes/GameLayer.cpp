#include "GameLayer.h"

#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#define WISP_INIT_POS ccp(96 ,150)
#define WISP_STRETCH_LENGTH 50

#define CROSS_POS1 ccp(10, 135)
#define CROSS_POS2 ccp(125, 140)

USING_NS_CC;

GameLayer::GameLayer() {
    
}

//�V�[������
CCScene* GameLayer::createScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = GameLayer::create();
	scene->addChild(layer);

	return scene; 
}


bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
 
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
    gravity.Set(0.0f, -98.0f);
    _world = new b2World(gravity);
	//�������~�܂������̂ɂ��āA�v�Z���ȗ�
    _world->SetAllowSleeping(true);
	//�I�u�W�F�N�g�̏Փ˔�������鎞�ɂ��蔲���Ȃ��悤�ɒ������Čv�Z����B
    _world->SetContinuousPhysics(true);
	
}

void GameLayer::onEnter(){
	CCLayer::onEnter();

	instantiateBackground();
	instantiateGround();
	instantiateWisp();
}

//�w�i�̐���
void GameLayer::instantiateBackground(){
	//�w�i�̐ݒ�
	CCSprite* background = CCSprite::create("background1.png");
	background->setAnchorPoint(ccp(0.0, 0.5));
	background->setPosition(ccp(0, WINSIZE.height / 2));
	addChild(background, kOrder_Background, kTag_Background);
}

//�n�ʂ̐���
void GameLayer::instantiateGround(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCNode* background = getChildByTag(kTag_Background);
	

	//�����{�f�B����
    b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    
    // �n�ʂ̌`�Ƒ傫���̒�`
    float groundHeight = size.height * 0.1;
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, groundHeight / PTM_RATIO),
                  b2Vec2(size.width / PTM_RATIO, groundHeight / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);


    

	//��������
	b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.8;
	groundBody->CreateFixture(&groundBox,0);

	//�n�ʃm�[�h�쐬
	CCNode* node = CCNode::create();
	node->setAnchorPoint(ccp(0.5, 0.5));
	node->setPosition(ccp(background->getContentSize().width / 2, 25));
	this->addChild(node);
}

void GameLayer::instantiateEnemy(CCPoint position){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//�G�l�~�[����
	RigidSprite* enemy = new RigidSprite();
	enemy->autorelease();
	enemy->initWithFile("enemy1.png");
	enemy->setPosition(position);
	enemy->setTag(kTag_Enemy);

	//�G�l�~�[�̃A�j���[�V����
	CCAnimation* animation =  CCAnimation::create();
	animation->addSpriteFrameWithFileName("enemy2.png");
	animation->addSpriteFrameWithFileName("enemy1.png");
	animation->setDelayPerUnit(1);

	CCRepeatForever* repeat = CCRepeatForever::create(CCAnimate::create(animation));
	enemy->runAction(repeat);

	//�����{�f�B����
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	_body = _world->CreateBody(&bodyDef);
    
	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
    spriteShape.m_radius = enemy->getContentSize().width * 0.3 / PTM_RATIO;

   //��������
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    _body->SetUserData(enemy);
	
	enemy->setRigidBody(_body);
	this->addChild(enemy, kOrder_Enemy);

}

void GameLayer::instantiateWisp(){
	//�E�B�X�v����
	RigidSprite* wisp = new RigidSprite();
	wisp->autorelease();
	wisp->initWithFile("wisp_1.png");
	wisp->setPosition(WISP_INIT_POS);
	wisp->setTag(kTag_Wisp);
	wisp->setZOrder(kOrder_Wisp);

	//�����{�f�B����
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(wisp->getPositionX() / PTM_RATIO,
                               wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = wisp; 
	_body = _world->CreateBody(&bodyDef);

	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
    spriteShape.m_radius = wisp->getContentSize().width * 0.3 / PTM_RATIO;

	//��������
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    _body->SetUserData(wisp);
	
	wisp->setRigidBody(_body);
	addChild(wisp);


	//���ˑ��ǉ�
	//RigidSprite* Cross1 = new RigidSprite();
	//launcher1->autorelease();
	//launcher1->initWithFile("Cross1.png");
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
		//������BALL_STRETCH_LENGTH�ƂȂ�ʒu��Ԃ�
		return WISP_INIT_POS + (touch - WISP_INIT_POS) * WISP_STRETCH_LENGTH / distance;
	else
		//�^�b�v�ʒu��Ԃ�
		return touch;
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
	//instantiateEnemy(location);
	
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

		chain1->setPosition(CROSS_POS1 - (CROSS_POS1 - pos));
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

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){}

void GameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event){}

void GameLayer::update(float dt)
{
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

		
            //�X�v���C�g����ʂ�1/3�܂ŗ�������A��A�N�e�B�u�ɂ���
            /*CCSize s = CCDirector::sharedDirector()->getWinSize();
            if(myActor->getPositionY()<s.height/1){
                b->SetActive(false);
			}*/
        }
    }
}

