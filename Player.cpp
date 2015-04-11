//
//  Player.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//


#include "Player.h"
#include "ObjectManager.h"
#include "GameLayer.h"

const float ACCELERATION = 0.2;
const CCPoint CROSS_ONE_POS = ccp(80, 135);
const CCPoint CROSS_TWO_POS = ccp(125, 140);

Player::Player(){}

Player::~Player(){}

Player* Player::create(){
	//ウィスプ生成
	Player* wisp = new Player();
	if (wisp && wisp->initWisp()) {
        wisp->autorelease();
		GAME::getInstance()->addChild(wisp, kOrder_Wisp, kTag_Wisp);
		wisp->reloadAction();
		return wisp;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(wisp);
	return NULL;
}

bool Player::initWisp()
{
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	if (this->initWithFile("wisp_1.png")){
		this->setPosition(WISP_SET_POS);
		return true;
	}
	
	return false;
}

void Player::reloadAction()
{
	OM::getInstance()->reloadSE();
	CCSprite *reload = CCSprite::create("explode1.png");
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	reload->setPosition(ccp(this->getPositionX(), this->getPositionY() + screenSize.height / 15));
	GAME::getInstance()->addChild(reload, kOrder_Star);
	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("explode1.png");
	animation->addSpriteFrameWithFileName("explode2.png");
	animation->addSpriteFrameWithFileName("explode3.png");
	animation->addSpriteFrameWithFileName("explode4.png");
	animation->setDelayPerUnit(0.1);

	CCAnimate *animate = CCAnimate::create(animation);
	CCFadeOut *fadeout = CCFadeOut::create(0.6);
	CCSpawn *spawn = CCSpawn::create(animate, fadeout, NULL);
	CCSequence *seq = CCSequence::create(spawn, CCRemoveSelf::create(), NULL);
	reload->runAction(seq);
}

bool Player::wispTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	//ウィスプの位置を計算
	return touchWithProcess(this, pTouch);
}



void Player::wispTouchMoved(CCTouch* pTouch, CCEvent* pEvent){
	//鎖を引くポイントと鎖を表示
	chain(this, pTouch);
}

void Player::wispTouchEnded(CCTouch* pTouch, CCEvent* pEvent){
	//鎖を削除し、ウィスプに力を加える
	removeAndAdd(this, pTouch);
}

bool Player::wispRectTouch(CCNode* wisp, CCTouch* touch){
	//タッチした位置がウィスプ上なら、以降の処理を行なう
	if(wisp && wisp->boundingBox().containsPoint(touch->getLocation()))
		return true;
	return false;
}

bool Player::touchWithProcess(CCNode* wisp, CCTouch* touch){
	if(wispRectTouch(wisp, touch))
	{
		//ウィスプの位置を計算
		wisp->setPosition(calcPos(touch->getLocation()));
		return true;
	}
	return false;
}

void Player::chain(CCNode* wisp, CCTouch* touch){
	if(wisp)
	{
		wisp->setPosition(calcPos(touch->getLocation()));

		//鎖を引くポイントと鎖を表示
		setChainOne(initChainOne(GAME::getInstance()->getChildByTag(kTag_Chain1)), extendPos(wisp));
		setChainTwo(initChainTwo(GAME::getInstance()->getChildByTag(kTag_Chain2)), extendPos(wisp));
	}
}

float Player::extendAngle(CCNode* wisp){
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	//鎖の角度を計算
	float angle = ((WISP_SET_POS - wisp->getPosition()).getAngle());
	return angle;
}

CCPoint Player::extendPos(CCNode* wisp){
	assert(extendAngle(wisp) != NULL);
	//鎖の終点を計算
	CCPoint pos = wisp->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(extendAngle(wisp)));
	return pos;
}

void Player::removeAndAdd(CCNode* wisp, CCTouch* touch){
	if(wisp)
	{
		//鎖を削除
		GAME::getInstance()->removeChain();
		//ウィスプの位置を計算
		wisp->setPosition(calcPos(touch->getLocation()));
		//剛体をセット
		physicsOnEnable();
		//ウィスプに力を加える
		addForceToWisp(wisp);
	}
}

void Player::physicsOnEnable()
{
	//物理ボディ生成
	this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&wispBodyDef(this));

	//物理エンジン上の物質の形と大きさ
	b2CircleShape spriteShape;
	spriteShape.m_radius = this->getContentSize().width * 0.3 / PTM_RATIO;

	//物理性質
	this->m_pBody->CreateFixture(&wispFixtureDef(&spriteShape));

	this->setRigidBody(this->m_pBody);
}

CCNode* Player::initChainOne(CCNode* chain1){
	//鎖1を表示
	if(!chain1)
		{
			chain1 = CCSprite::create("iron.png");
			GAME::getInstance()->addChild(chain1, kOrder_Chain1, kTag_Chain1);
		}
	assert(chain1 != NULL);
	return chain1;
}

CCNode* Player::initChainTwo(CCNode* chain2){
	//鎖2を表示
	if(!chain2)
		{
			chain2 = CCSprite::create("iron.png");
			GAME::getInstance()->addChild(chain2, kOrder_Chain2, kTag_Chain2);
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

//発射台
CCSprite* Player::initCrossOne(){
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	GAME::getInstance()->addChild(cross1, kOrder_Cross1);
	return cross1;
}

CCSprite* Player::initCrossTwo(){
	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(initCrossOne()->getPosition());
	GAME::getInstance()->addChild(cross2, kOrder_Cross2);
	return cross2;
}

void Player::addForceToWisp(CCNode* wisp){
	//ウィスプを可動出来るようにする
	Player *will = dynamic_cast<Player*>(wisp);
	b2Body *willBody = will->getBody();
	willBody->SetType(b2_dynamicBody);
	//ウィスプに力を加える
	CCPoint force = (will->getPosition() - WISP_SET_POS) * -ACCELERATION;
	willBody->ApplyLinearImpulse(b2Vec2(force.x, force.y), willBody->GetWorldCenter());
	OM::getInstance()->shotSE();
}

//発射前のウィスプの移動範囲を制御
CCPoint Player::calcPos(CCPoint touch){
	assert( (float)(0, 0) < (WISP_SET_POS.x, WISP_SET_POS.y) );
	//ウィスプの初期位置とタップ位置の距離
	int dist = touch.getDistance(WISP_SET_POS);

	//distがWISP_EXTEND以上になったら
	if(gThanPos(dist))
		//距離がWISP_EXTENDとなる位置を返す（範囲制限）
		return calcRetPos(touch, dist);
	else
		//タップ位置を返す
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
	//タップ位置がWISP_EXTEND外であれば、その範囲内に位置するように処理
	return WISP_SET_POS + (touch - WISP_SET_POS) * WISP_EXTEND / dist;
}

//物理ボディ生成
b2BodyDef Player::wispBodyDef(Player* wisp){
	b2BodyDef bodyDef;
    //bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(wisp->getPositionX() / PTM_RATIO,
                               wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = wisp; 
	return bodyDef;
}

//物理性質
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
    
}