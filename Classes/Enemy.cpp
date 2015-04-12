//
//  Enemy.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "Enemy.h"
#include "ObjectManager.h"
#include "GameLayer.h"


Enemy::Enemy(){}

Enemy::~Enemy(){}

Enemy* Enemy::create(CCPoint position, const char* fileName)
{
	//�G�l�~�[����
	Enemy* enemy = new Enemy();
	if (enemy)
	{
        enemy->initEnemy(position, fileName);
		enemy->autorelease();
		GAME::getInstance()->addChild(enemy, kTag_Enemy, kOrder_Enemy);
		return enemy;
	}
	//autorelease���g�p���Ă��邽�߁Adelete�̑���Ɏg�p�A���������J��
	//���x���������Ȃ��悤�ɃK�[�h��������
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(CCPoint position, const char* FileName)
{
	this->initWithFile(FileName);
	this->setPosition(position);
	
	//�����{�f�B����
	b2BodyDef bodyDef = enemyBodyDef(this);
	
	this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&bodyDef);
	this->m_pBody->SetSleepingAllowed(true);
	this->m_pBody->SetLinearDamping(0.2);
	this->m_pBody->SetAngularDamping(0.8);
    
	//�����G���W����̕����̌`�Ƒ傫��
    b2CircleShape spriteShape;
	spriteShape.m_radius = this->getContentSize().width * 0.4 / PTM_RATIO;

    //��������
	b2FixtureDef fixtureDef = enemyFixtureDef();
	fixtureDef.shape = &spriteShape;
	
	this->m_pBody->CreateFixture(&fixtureDef);
	this->setRigidBody(this->m_pBody);
	this->scheduleUpdate();
	return this;
}

//�����{�f�B����
b2BodyDef Enemy::enemyBodyDef(Enemy* enemy)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(
		enemy->getPositionX() / PTM_RATIO,
		enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = this;
	return bodyDef;
}

//��������
b2FixtureDef Enemy::enemyFixtureDef()
{
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = 0x0010;
	fixtureDef.density = 0.5;
	fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

void Enemy::addEnemy()
{
	create(ccp(736, 125), "enemy1.png");
	create(ccp(636, 325), "enemy1.png");
}

void Enemy::update (float dt){}
