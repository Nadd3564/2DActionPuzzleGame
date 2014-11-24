//
//  Enemy.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "Enemy.h"
#include "ObjectManager.h"
#include "GameLayer.h"


Enemy::Enemy(GameLayer * game) : GameObject(game){}

Enemy::~Enemy(){}

Enemy* Enemy::create(GameLayer* game, CCPoint position, const char* FileName, int kTag)
{
	//�G�l�~�[����
	Enemy* _enemy = new Enemy(game);
	
	if (_enemy) {
        _enemy = _enemy->initEnemy(game, position, FileName, kTag);
		_enemy->autorelease();
		return _enemy;
	}
	CC_SAFE_DELETE(_enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(GameLayer* game, CCPoint position, const char* FileName, int kTag)
{
	this->initWithFile(FileName);
	this->setPosition(position);
	this->setTag(kTag);

	//�G�l�~�[�̃A�j���[�V����
	/*CCAnimation* animation =  CCAnimation::create();
	animation->addSpriteFrameWithFileName("enemy2.png");
	animation->addSpriteFrameWithFileName("enemy1.png");
	animation->setDelayPerUnit(1);

	CCRepeatForever* repeat = CCRepeatForever::create(CCAnimate::create(animation));
	enemy->runAction(repeat);*/

	//�����{�f�B����
	_body = _game->getWorld()->CreateBody(&enemyBodyDef(this));
    
	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
   spriteShape.m_radius = this->getContentSize().width * 0.4 / PTM_RATIO;

    //��������
	_body->CreateFixture(&enemyFixtureDef(&spriteShape));
	
	this->setRigidBody(_body);
	Game::Instance()->addGameObjectMap("enemy", this);
	Game::Instance()->addGameObject(this);
	return this;
}

//�����{�f�B����
b2BodyDef Enemy::enemyBodyDef(Enemy* enemy){
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	return bodyDef;
}

//��������
b2FixtureDef Enemy::enemyFixtureDef(b2Shape* shape){
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}
