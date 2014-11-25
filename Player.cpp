//
//  Player.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//
#define CROSS_POS1 ccp(80, 135)
#define CROSS_POS2 ccp(125, 140)

#include "Player.h"
#include "ObjectManager.h"
#include "GameLayer.h"

Player::Player(GameLayer* game) : GameObject(game){}

Player::~Player(){}

Player* Player::create(){
	//�E�B�X�v����
	Player* wisp = new Player(GameLayer::Instance());
	if (wisp) {
        wisp->initWisp();
		wisp->autorelease();
		return wisp;
	}
	CC_SAFE_DELETE(wisp);
	return NULL;
}

Player* Player::initWisp()
{
	this->initWithFile("wisp_1.png");
	this->setPosition(WISP_SET_POS);
	this->setTag(_game->kTag_Wisp);
	this->setZOrder(_game->kOrder_Wisp);


	//�����{�f�B����
	_body = _game->getWorld()->CreateBody(&wispBodyDef(this));
    
	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
    spriteShape.m_radius = this->getContentSize().width * 0.3 / PTM_RATIO;

    //��������
	_body->CreateFixture(&wispFixtureDef(&spriteShape));
	
	this->setRigidBody(_body);
	Game::Instance()->addGameObjectMap("wisp", this);
	Game::Instance()->addGameObject(this);
	return this;
}

void Player::stateUpdate(float dt){
    std::cout << "Update for the player.";
	update(dt);
}

bool Player::wispTouchBegan(){
	bool flg = false;

	CCTouch* touch = _game->getBeganTouch();
	CCNode* wisp = _game->getWispTag();

	if(wisp && wisp->boundingBox().containsPoint(touch->getLocation()))
	{
		//�E�B�X�v�̈ʒu���v�Z
		wisp->setPosition(processingPosition(touch->getLocation()));
		flg = true;
	}

	return flg;
}

void Player::wispTouchMoved(){
	CCTouch* touch = _game->getMovedTouch();
	CCNode* wisp = _game->getWispTag();

	if(wisp)
	{
		wisp->setPosition(processingPosition(touch->getLocation()));

		//���������|�C���g
		float angle = ((WISP_SET_POS - wisp->getPosition()).getAngle());
		CCPoint pos = wisp->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(angle));

		//����\��
		setChainOne(GameLayer::Instance()->visibleChainOne(), pos);
		setChainTwo(GameLayer::Instance()->visibleChainTwo(), pos);
	}
}

void Player::wispTouchEnded(){
	CCTouch* touch = _game->getEndedTouch();
	CCNode* wisp = _game->getWispTag();

	if(wisp)
	{
		//�����폜
		GameLayer::Instance()->removeChain();
		wisp->setPosition(processingPosition(touch->getLocation()));

		//�E�B�X�v�ɗ͂�������
		addForceToWisp(wisp);
	}
}

void Player::setChainOne(CCNode* chain1, CCPoint pos){
	chain1->setPosition(CROSS_POS1 - (CROSS_POS1 - pos) / 2);
	chain1->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS1 - pos).getAngle() * -1));
	chain1->setScaleX(CROSS_POS1.getDistance(pos));
	chain1->setScaleY(10);
}

void Player::setChainTwo(CCNode* chain2, CCPoint pos){
	chain2->setPosition(CROSS_POS2 - (CROSS_POS2 - pos) / 2);
	chain2->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS2 - pos).getAngle() * -1));
	chain2->setScaleX(CROSS_POS2.getDistance(pos));
	chain2->setScaleY(10);
}

CCPoint Player::processingPosition(CCPoint touch){
	//�E�B�X�v�̏����ʒu�ƃ^�b�v�ʒu�̋���
	int distance = touch.getDistance(WISP_SET_POS);

	if(distance > WISP_EXTEND)
		//������WISP_EXTEND�ƂȂ�ʒu��Ԃ�
		return WISP_SET_POS + (touch - WISP_SET_POS) * WISP_EXTEND / distance;
	else
		//�^�b�v�ʒu��Ԃ�
		return touch;
}

//�����{�f�B����
b2BodyDef Player::wispBodyDef(Player* wisp){
	b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(wisp->getPositionX() / PTM_RATIO,
                               wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = wisp; 
	return bodyDef;
}

//��������
b2FixtureDef Player::wispFixtureDef(b2Shape* shape){
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

//���ˑ�
CCSprite* Player::initCrossOne(){
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	cross1->setZOrder(GameLayer::Instance()->kOrder_Cross1);
	return cross1;
}

CCSprite* Player::initCrossTwo(){
	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(initCrossOne()->getPosition());
	cross2->setZOrder(GameLayer::Instance()->kOrder_Cross2);
	return cross2;
}

void Player::addForceToWisp(CCNode* wisp){
	//�E�B�X�v�����o����悤�ɂ���
	Player* will = dynamic_cast<Player*>(wisp);
	will->getBody()->SetType(b2_dynamicBody);
	//�E�B�X�v�ɗ͂�������
	will->getBody()->ResetMassData();
	will->getBody()->ApplyLinearImpulse(b2Vec2(8.0f, 3.0f), will->getBody()->GetWorldCenter());
}

void Player::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
}