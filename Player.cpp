//
//  Player.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//
#include "Player.h"
#include "ObjectManager.h"
#include "GameLayer.h"

Player::Player(GameLayer* game) : GameObject(game){}

Player::~Player(){}

Player* Player::create(GameLayer* game, CCPoint position, const char* fileName, int kTag, int kOrder){
	//ウィスプ生成
	Player* wisp = new Player(game);
	if (wisp) {
        wisp = wisp->initWisp(game, position, fileName, kTag, kOrder);
		wisp->autorelease();
		return wisp;
	}
	CC_SAFE_DELETE(wisp);
	return NULL;
}

Player* Player::initWisp(GameLayer* game, CCPoint position, const char* FileName, int kTag, int kOrder)
{
	this->initWithFile(FileName);
	this->setPosition(position);
	this->setTag(kTag);
	this->setZOrder(kOrder);


	//物理ボディ生成
	_body = _game->getWorld()->CreateBody(&wispBodyDef(this));
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = this->getContentSize().width * 0.3 / PTM_RATIO;

    //物理性質
	_body->CreateFixture(&wispFixtureDef(&spriteShape));
	
	this->setRigidBody(_body);
	Game::Instance()->addGameObjectMap("wisp", this);
	Game::Instance()->addGameObject(this);
	return this;
}

//物理ボディ生成
b2BodyDef Player::wispBodyDef(Player* wisp){
	b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(wisp->getPositionX() / PTM_RATIO,
                               wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = wisp; 
	return bodyDef;
}

//物理性質
b2FixtureDef Player::wispFixtureDef(b2Shape* shape){
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

CCSprite* Player::initCrossOne(){
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	return cross1;
}

CCSprite* Player::initCrossTwo(){
	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(initCrossOne()->getPosition());
	return cross2;
}

void Player::setPlayerPosition(cocos2d::CCPoint* diff, cocos2d::CCPoint playerPos,
                       float tileWidth, float tileHeight, float mapWidth, float mapHeight)
{
	if(diff){
        if ( abs(diff->x) > abs(diff->y) ) {
            if (diff->x > 0) {
                
                playerPos.x += tileWidth;
            } else {
                playerPos.x -= tileWidth;
            }
        } else {
            if (diff->y > 0) {
                playerPos.y += tileHeight;
            } else {
                playerPos.y -= tileHeight;
            }
        }
        
        // safety check on the bounds of the map
        if (playerPos.x <= (mapWidth * tileWidth) &&
            playerPos.y <= (mapHeight * tileHeight) &&
            playerPos.y >= 0 &&
            playerPos.x >= 0 )
        {
            this->setPosition(playerPos);
		}
    }
}

void Player::addForceToWisp(CCNode* wisp){
	//ウィスプを可動出来るようにする
	RigidSprite* will = dynamic_cast<RigidSprite*>(wisp);
	will->m_pBody->SetType(b2_dynamicBody);
	//ウィスプに力を加える
	will->m_pBody->ResetMassData();
	will->m_pBody->ApplyLinearImpulse(b2Vec2(8.0f, 3.0f), will->m_pBody->GetWorldCenter());
}

void Player::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
}