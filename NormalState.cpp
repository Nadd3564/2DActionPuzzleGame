//
//  NormalState.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "NormalState.h"
#include "cocos2d.h"
#include "Player.h"
#include "GameLayer.h"
#include "TitleLayer.h"


using namespace cocos2d;

const std::string NormalState::s_normalID = "NORMAL";

NormalState::NormalState() {
    std::cout << "NormalState::NormalState() normal state constructor\n";
}

NormalState::~NormalState() {
	CC_SAFE_RELEASE(_enemy);
}

	//初期化
bool NormalState::onStateEnter() {
    std::cout << "NormalState::onStateEnter()\n";
	//ウィスプ生成
	_wisp = Player::create();
	//エネミー生成
	Enemy::create(ccp(636, 125), "enemy2.png")->addEnemy();
	//背景生成
	OM::getInstance()->initBackground();
	//地面生成
	OM::getInstance()->initGround();
	//発射台生成
	_wisp->initCrossOne();
	_wisp->initCrossTwo();
	//障害物生成
	Obstacles::create(Obstacle4, ccp(536, 75), 0)->addObstacles();
	
	
	//コンテナにゲームオブジェクトを代入
	m_gObjects = OM::getInstance()->getGameObjects();
	
	return true;
}

void NormalState::stateUpdate(float dt)
{
	//ワールドを更新
	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	b2World *world = GAME::getInstance()->getWorld();
	world->Step(dt, velocityIterations, positionIterations);
	
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			RigidSprite* myActor = (RigidSprite *)b->GetUserData();
			if ((myActor->getTag() == kTag_Enemy) && (myActor->getIsDead())){
					world->DestroyBody(b);
					myActor->removeFromParent();
					continue;
			}
			myActor->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

bool NormalState::onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent){
	return _wisp->wispTouchBegan(pTouch, pEvent);
}

void NormalState::onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent){
	_wisp->wispTouchMoved(pTouch, pEvent);
}

void NormalState::onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent){
	_wisp->wispTouchEnded(pTouch, pEvent);
}


	//状態遷移時の処理
bool NormalState::onStateExit() {
    return true;
}

