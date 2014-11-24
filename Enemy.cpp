//
//  Enemy.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "Enemy.h"
#include "ObjectManager.h"

Enemy::Enemy(){
	
}

Enemy::~Enemy(){}

Enemy* Enemy::create(Enemy* _enemy, b2Body* _body, b2World* _world,
					 CCPoint position, const char* FileName, int kTag)
{
	//エネミー生成
	_enemy = new Enemy();
	
	if (_enemy) {
        _enemy = _enemy->initEnemy(_enemy, _body, _world,
							position, FileName,kTag);
		_enemy->autorelease();
		return _enemy;
	}
	CC_SAFE_DELETE(_enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(Enemy* _enemy, b2Body* _body, b2World* _world,
					 CCPoint position, const char* FileName, int kTag)
{
	_enemy->initWithFile(FileName);
	_enemy->setPosition(position);
	_enemy->setTag(kTag);

	//エネミーのアニメーション
	/*CCAnimation* animation =  CCAnimation::create();
	animation->addSpriteFrameWithFileName("enemy2.png");
	animation->addSpriteFrameWithFileName("enemy1.png");
	animation->setDelayPerUnit(1);

	CCRepeatForever* repeat = CCRepeatForever::create(CCAnimate::create(animation));
	enemy->runAction(repeat);*/

	//物理ボディ生成
    _body = _world->CreateBody(&enemyBodyDef(_enemy));
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = _enemy->getContentSize().width * 0.4 / PTM_RATIO;

    //物理性質
	_body->CreateFixture(&enemyFixtureDef(&spriteShape));
	
	_enemy->setRigidBody(_body);
	Game::Instance()->addGameObjectMap("enemy", _enemy);
	Game::Instance()->addGameObject(_enemy);
	return _enemy;
}

//物理ボディ生成
b2BodyDef Enemy::enemyBodyDef(Enemy* enemy){
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	return bodyDef;
}

//物理性質
b2FixtureDef Enemy::enemyFixtureDef(b2Shape* shape){
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}
