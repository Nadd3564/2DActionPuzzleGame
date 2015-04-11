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
	//エネミー生成
	Enemy* enemy = new Enemy();
	if (enemy)
	{
        enemy->initEnemy(position, fileName);
		enemy->autorelease();
		GAME::getInstance()->addChild(enemy, kTag_Enemy, kOrder_Enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(CCPoint position, const char* FileName)
{
	this->initWithFile(FileName);
	this->setPosition(position);
	
	//物理ボディ生成
	this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&enemyBodyDef(this));
	this->m_pBody->SetSleepingAllowed(true);
	this->m_pBody->SetLinearDamping(0.2);
	this->m_pBody->SetAngularDamping(0.8);
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
	spriteShape.m_radius = this->getContentSize().width * 0.4 / PTM_RATIO;

    //物理性質
	this->m_pBody->CreateFixture(&enemyFixtureDef(&spriteShape));
	this->setRigidBody(this->m_pBody);
	this->scheduleUpdate();
	return this;
}

void Enemy::addEnemy()
{
	create(ccp(636, 125), "enemy1.png");
	create(ccp(536, 325), "enemy1.png");
}

//物理ボディ生成
b2BodyDef Enemy::enemyBodyDef(Enemy* enemy)
{
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = this; 
	return bodyDef;
}

//物理性質
b2FixtureDef Enemy::enemyFixtureDef(b2Shape* shape)
{
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
	fixtureDef.filter.categoryBits = 0x0010;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

void Enemy::update (float dt){}
