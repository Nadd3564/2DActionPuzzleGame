//
//  Player.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//


#include "Player.h"
#include "ObjectManager.h"
#include "GameLayer.h"

const CCPoint CROSS_ONE_POS = ccp(80, 135);
const CCPoint CROSS_TWO_POS = ccp(125, 140);

Player::Player(GameLayer* game) : GameObject(game){ assert(game != NULL); }

Player::~Player(){}

Player* Player::create(){
	//�E�B�X�v����
	Player* wisp = new Player(GameLayer::Instance());
	if (wisp) {
        wisp->initWisp();
		wisp->autorelease();
		GameLayer::Instance()->setWisp(wisp);
		return wisp;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(wisp);
	return NULL;
}

Player* Player::initWisp()
{
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	this->initWithFile("wisp_1.png");
	this->setPosition(WISP_SET_POS);
	this->setTag(_gameL->kTag_Wisp);
	this->setZOrder(_gameL->kOrder_Wisp);


	//�����{�f�B����
	_body = _gameL->getWorld()->CreateBody(&wispBodyDef(this));
    
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

	CCTouch* touch = _gameL->getBeganTouch();
	CCNode* wisp = _gameL->getWispTag();

	//�E�B�X�v�̈ʒu���v�Z
	return touchWithProcess(wisp, touch, flg);
}



void Player::wispTouchMoved(){
	CCTouch* touch = _gameL->getMovedTouch();
	CCNode* wisp = _gameL->getWispTag();
	//���������|�C���g�ƍ���\��
	chain(wisp, touch);
}



void Player::wispTouchEnded(){
	CCTouch* touch = _gameL->getEndedTouch();
	CCNode* wisp = _gameL->getWispTag();
	//�����폜���A�E�B�X�v�ɗ͂�������
	removeAndAdd(wisp, touch);
}

bool Player::wispRectTouch(CCNode* wisp, CCTouch* touch){
	//�^�b�`�����ʒu���E�B�X�v��Ȃ�A�ȍ~�̏������s�Ȃ�
	if(wisp && wisp->boundingBox().containsPoint(touch->getLocation()))
		return true;
	return false;
}

bool Player::touchWithProcess(CCNode* wisp, CCTouch* touch, bool flg){
	if(wispRectTouch(wisp, touch))
	{
		//�E�B�X�v�̈ʒu���v�Z
		wisp->setPosition(calcPos(touch->getLocation()));
		flg = true;
	}
	return flg;
}

void Player::chain(CCNode* wisp, CCTouch* touch){
	if(wisp)
	{
		wisp->setPosition(calcPos(touch->getLocation()));

		//���������|�C���g�ƍ���\��
		setChainOne(initChainOne(_gameL->getChainOneTag()), extendPos(wisp));
		setChainTwo(initChainTwo(_gameL->getChainTwoTag()), extendPos(wisp));
	}
}

float Player::extendAngle(CCNode* wisp){
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	//���̊p�x���v�Z
	float angle = ((WISP_SET_POS - wisp->getPosition()).getAngle());
	return angle;
}

CCPoint Player::extendPos(CCNode* wisp){
	assert(extendAngle(wisp) != NULL);
	//���̏I�_���v�Z
	CCPoint pos = wisp->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(extendAngle(wisp)));
	return pos;
}

void Player::removeAndAdd(CCNode* wisp, CCTouch* touch){
	if(wisp)
	{
		//�����폜
		_gameL->removeChain();
		//�E�B�X�v�̈ʒu���v�Z
		wisp->setPosition(calcPos(touch->getLocation()));

		//�E�B�X�v�ɗ͂�������
		addForceToWisp(wisp);
	}
}

CCNode* Player::initChainOne(CCNode* chain1){
	//��1��\��
	if(!chain1)
		{
			chain1 = CCSprite::create("iron.png");
			chain1->setTag(_gameL->kTag_Chain1);
			chain1->setZOrder(_gameL->kOrder_Chain1);
			_gameL->setNode(chain1);
		}
	assert(chain1 != NULL);
	return chain1;
}

CCNode* Player::initChainTwo(CCNode* chain2){
	//��2��\��
	if(!chain2)
		{
			chain2 = CCSprite::create("iron.png");
			chain2->setTag(_gameL->kTag_Chain2);
			chain2->setZOrder(_gameL->kOrder_Chain2);
			_gameL->setNode(chain2);
		}
	assert(chain2 != NULL);
	return chain2;
}

void Player::setChainOne(CCNode* chain1, CCPoint pos){
	assert((float)(0, 0) <= (CROSS_ONE_POS.x, CROSS_ONE_POS.y));
	chain1->setPosition(CROSS_ONE_POS - (CROSS_ONE_POS - pos) / 2);
	chain1->setRotation(CC_RADIANS_TO_DEGREES((CROSS_ONE_POS - pos).getAngle() * -1));
	chain1->setScaleX(CROSS_ONE_POS.getDistance(pos));
	chain1->setScaleY(10);
}

void Player::setChainTwo(CCNode* chain2, CCPoint pos){
	assert((float)(0, 0) <= (CROSS_TWO_POS.x, CROSS_TWO_POS.y));
	chain2->setPosition(CROSS_TWO_POS - (CROSS_TWO_POS - pos) / 2);
	chain2->setRotation(CC_RADIANS_TO_DEGREES((CROSS_TWO_POS - pos).getAngle() * -1));
	chain2->setScaleX(CROSS_TWO_POS.getDistance(pos));
	chain2->setScaleY(10);
}

//���ˑ�
CCSprite* Player::initCrossOne(){
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	cross1->setZOrder(_gameL->kOrder_Cross1);
	_gameL->setSprite(cross1);
	return cross1;
}

CCSprite* Player::initCrossTwo(){
	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(initCrossOne()->getPosition());
	cross2->setZOrder(_gameL->kOrder_Cross2);
	_gameL->setSprite(cross2);
	return cross2;
}

void Player::addForceToWisp(CCNode* wisp){
	//�E�B�X�v�����o����悤�ɂ���
	Player* will = dynamic_cast<Player*>(wisp);
	will->getBody()->SetType(b2_dynamicBody);
	//���ʂ��Z�b�g
	will->getBody()->ResetMassData();
	//�E�B�X�v�ɗ͂�������
	will->getBody()->ApplyLinearImpulse(b2Vec2(8.0f, 3.0f), will->getBody()->GetWorldCenter());
}

//���ˑO�̃E�B�X�v�̈ړ��͈͂𐧌�
CCPoint Player::calcPos(CCPoint touch){
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	//�E�B�X�v�̏����ʒu�ƃ^�b�v�ʒu�̋���
	int dist = touch.getDistance(WISP_SET_POS);

	//dist��WISP_EXTEND�ȏ�ɂȂ�����
	if(gThanPos(dist))
		//������WISP_EXTEND�ƂȂ�ʒu��Ԃ��i�͈͐����j
		return calcRetPos(touch, dist);
	else
		//�^�b�v�ʒu��Ԃ�
		return touch;
}


bool Player::gThanPos(int dist){
	assert(dist != NULL);
	if(dist > WISP_EXTEND)
		return true;
	return false;
}


CCPoint Player::calcRetPos(CCPoint touch, int dist){
	assert(dist != NULL);
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	//�^�b�v�ʒu��WISP_EXTEND�O�ł���΁A���͈͓̔��Ɉʒu����悤�ɏ���
	return WISP_SET_POS + (touch - WISP_SET_POS) * WISP_EXTEND / dist;
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
	assert(shape != NULL);
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

void Player::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
}