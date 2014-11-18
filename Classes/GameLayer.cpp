#include "GameLayer.h"

#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#define BALL_INIT_POS ccp(96 ,150)
#define BALL_STRETCH_LENGTH 50

#define LAUNCHER_POS1 ccp(10, 135)
#define LAUNCHER_POS2 ccp(125, 140)

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
    //�}���`�^�b�v���[�h
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
	instantiateBall();
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
	

	//create table sides
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
	PhysicsSprite* enemy = new PhysicsSprite();
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
	
	enemy->setPhysicsBody(_body);
	this->addChild(enemy, kOrder_Enemy);

}

void GameLayer::instantiateBall(){
	//�{�[������
	PhysicsSprite* ball = new PhysicsSprite();
	ball->autorelease();
	ball->initWithFile("ball_1.png");
	ball->setPosition(BALL_INIT_POS);
	ball->setTag(kTag_Ball);
	ball->setZOrder(kOrder_Ball);

	//�����{�f�B����
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(ball->getPositionX() / PTM_RATIO,
                               ball->getPositionY() / PTM_RATIO);
	bodyDef.userData = ball; 
	_body = _world->CreateBody(&bodyDef);

	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
    spriteShape.m_radius = ball->getContentSize().width * 0.3 / PTM_RATIO;

	//��������
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    _body->SetUserData(ball);
	
	ball->setPhysicsBody(_body);
	addChild(ball);


	//���ˑ��ǉ�
	//PhysicsSprite* launcher1 = new PhysicsSprite();
	//launcher1->autorelease();
	//launcher1->initWithFile("launcher1.png");
	CCSprite* launcher1 = CCSprite::create("Cross1.png");
	launcher1->setScale(0.5);
	launcher1->setPosition(ccp(100, 100));
	addChild(launcher1, kOrder_Launcher1);

	CCSprite* launcher2 = CCSprite::create("Cross2.png");
	launcher2->setScale(0.5);
	launcher2->setPosition(launcher1->getPosition());
	addChild(launcher2, kOrder_Launcher2);
}

CCPoint GameLayer::processingPosition(CCPoint touch){
	//�{�[���̏����ʒu�ƃ^�b�v�ʒu�̋���
	int distance = touch.getDistance(BALL_INIT_POS);

	if(distance > BALL_STRETCH_LENGTH)
		//������BALL_STRETCH_LENGTH�ƂȂ�ʒu��Ԃ�
		return BALL_INIT_POS + (touch - BALL_INIT_POS) * BALL_STRETCH_LENGTH / distance;
	else
		//�^�b�v�ʒu��Ԃ�
		return touch;
}


bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
	bool flg = false;
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCNode* ball = getChildByTag(kTag_Ball);
	if(ball && ball->boundingBox().containsPoint(touch->getLocation()))
	{
		//�{�[���̈ʒu���v�Z
		ball->setPosition(processingPosition(touch->getLocation()));
		flg = true;
	}
	//instantiateEnemy(location);
	
	return flg;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCNode* ball = getChildByTag(kTag_Ball);
	if(ball)
	{
		ball->setPosition(processingPosition(touch->getLocation()));

		//�S���������|�C���g
		float angle = ((BALL_INIT_POS - ball->getPosition()).getAngle());
		CCPoint pos = ball->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(angle));

		//�S����\��
		CCNode* gum1 = getChildByTag(kTag_Gum1);
		if(!gum1)
		{
			gum1 = CCSprite::create("iron.png");
			addChild(gum1, kOrder_Gum1, kTag_Gum1);
		}

		gum1->setPosition(LAUNCHER_POS1 - (LAUNCHER_POS1 - pos));
		gum1->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS1 - pos).getAngle() * -1));
		gum1->setScaleX(LAUNCHER_POS1.getDistance(pos));
		gum1->setScaleY(10);

		CCNode* gum2 = getChildByTag(kTag_Gum2);
		if(!gum2)
		{
			gum2 = CCSprite::create("iron.png");
			addChild(gum2, kOrder_Gum2, kTag_Gum2);
		}

		gum2->setPosition(LAUNCHER_POS2 - (LAUNCHER_POS2 - pos) / 2);
		gum2->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS2 - pos).getAngle() * -1));
		gum2->setScaleX(LAUNCHER_POS2.getDistance(pos));
		gum2->setScaleY(10);
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

