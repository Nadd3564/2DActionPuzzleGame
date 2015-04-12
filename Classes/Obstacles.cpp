/*
* Obstacles.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#include "Obstacles.h"
#include "ObjectManager.h"
#include "GameLayer.h"

USING_NS_CC;

Obstacles::Obstacles(){}


Obstacles::~Obstacles(){}

Obstacles* Obstacles::create(int obstacle, CCPoint pos, float angle){
	Obstacles* obs = new Obstacles();
	if (obs) {
        obs->initObstacles(obstacle, pos, angle);
		obs->autorelease();
		GameLayer::getInstance()->addChild(obs, (int)kOrder_Obstacles, kTag_Obstacles);
		return obs;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(obs);
	return NULL;
}

std::string Obstacles::fileNameInit(int obstacle){
	std::string fileName;

	switch (obstacle)
	{
	case Obstacle1:
		fileName = "stone1.png";
		break;
	case Obstacle2:
		fileName = "headStone.png";
		break;
	case Obstacle3:
		fileName = "pumpkin.png";
		break;
	case Obstacle4:
		fileName = "baseStone1.png";
		break;
	case length:
		fileName = "baseStone1.png";
		break;
	default:
		break;
	}

	return fileName;
}

b2BodyDef Obstacles::ObsBodyDef(b2BodyDef bodyDef, b2BodyType BodyType){
	bodyDef.type = BodyType;
	bodyDef.position.Set(this->getPositionX() / PTM_RATIO,
                               this->getPositionY() / PTM_RATIO);
	bodyDef.userData = this;
	return bodyDef;
}

b2PolygonShape Obstacles::ObsShape(float32 width, float32 height){
	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(this->getContentSize().width * width/ PTM_RATIO, 
							this->getContentSize().height * height/ PTM_RATIO);
	return spriteShape;
}

b2FixtureDef Obstacles::ObsFixtureDef(float32 density, float32 restitution, float32 friction){
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = 0x0010;
	fixtureDef.density = density;
	fixtureDef.restitution = restitution;
	fixtureDef.friction = friction;
	return fixtureDef;
}

Obstacles* Obstacles::initObstacles(int obstacle, CCPoint pos, float angle)
{

	//障害物の生成
	this->initWithFile(fileNameInit(obstacle).c_str());
	this->setPosition(pos);
	this->setRotation(angle);
	//物理ボディ生成
	 b2BodyDef bodyDef;

	 switch(obstacle)
	 {
	    case Obstacle1:
	    case Obstacle2:
		{
			bodyDef = ObsBodyDef(bodyDef, b2_dynamicBody);
			bodyDef.angle = 50 / PTM_RATIO;
			this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.49, 0.45);
			this->m_pBody->CreateFixture(&spriteShape, 1);
				

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			this->m_pBody->CreateFixture(&fixtureDef);
			break;
		}

		case Obstacle3:
		{
			bodyDef = ObsBodyDef(bodyDef, b2_dynamicBody);
			this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&bodyDef);
			
			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.5, 0.3);
			m_pBody->CreateFixture(&spriteShape, 2);

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.1, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			m_pBody->CreateFixture(&fixtureDef);
			break; 
		}

		case length:
		{
			bodyDef = ObsBodyDef(bodyDef, b2_kinematicBody);
			this->m_pBody = GAME::getInstance()->getWorld()->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.5, 0.3);
			m_pBody->CreateFixture(&spriteShape, 2);

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			m_pBody->CreateFixture(&fixtureDef);
			break;
		}
			
		default:
		{
			bodyDef = ObsBodyDef(bodyDef, b2_staticBody);
			m_pBody = GAME::getInstance()->getWorld()->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.5, 0.5);
			m_pBody->CreateFixture(&spriteShape, 3);

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			m_pBody->CreateFixture(&fixtureDef);
			break;
		}
	 }
    
	 this->setRigidBody(m_pBody);
	 return this;
}

void Obstacles::addObstacles(int level){
	switch (level)
	{
		case 1:
		{
			create(Obstacle4, ccp(636, 75), 0);
			create(Obstacle4, ccp(736, 75), 0);
			create(Obstacle4, ccp(836, 75), 0);
			create(Obstacle1, ccp(686, 150), 90);
			create(Obstacle1, ccp(686, 250), 90);
			create(Obstacle1, ccp(786, 150), 90);
			create(Obstacle1, ccp(786, 250), 90);
			create(Obstacle3, ccp(736, 325), 0);
			break;
		}
		case 2:
		{
			create(Obstacle4, ccp(536, 75), 0);
			create(Obstacle4, ccp(636, 75), 0);
			create(Obstacle4, ccp(736, 75), 0);
			create(Obstacle4, ccp(836, 75), 0);
			create(Obstacle4, ccp(936, 75), 0);
			create(Obstacle1, ccp(586, 150), 90);
			create(Obstacle1, ccp(686, 150), 90);
			create(Obstacle1, ccp(786, 150), 90);
			create(Obstacle1, ccp(886, 150), 90);
			create(Obstacle3, ccp(636, 225), 0);
			create(Obstacle3, ccp(736, 225), 0);
			create(Obstacle3, ccp(836, 225), 0);
			break;
		}
		default:
		{
			create(Obstacle4, ccp(536, 75), 0);
			create(Obstacle4, ccp(636, 75), 0);
			create(Obstacle4, ccp(736, 75), 0);
			create(Obstacle4, ccp(836, 75), 0);
			create(Obstacle4, ccp(936, 75), 0);
			create(Obstacle1, ccp(586, 150), 90);
			create(Obstacle1, ccp(686, 150), 90);
			create(Obstacle1, ccp(786, 150), 90);
			create(Obstacle1, ccp(686, 300), 90);
			create(Obstacle1, ccp(786, 300), 90);
			create(Obstacle1, ccp(886, 150), 90);
			create(Obstacle3, ccp(636, 225), 0);
			create(Obstacle3, ccp(736, 225), 0);
			create(Obstacle3, ccp(736, 375), 0);
			create(Obstacle2, ccp(736, 450), 0);
			create(Obstacle3, ccp(836, 225), 0);
			break;
		}
		
	}

	
}


void Obstacles::update(float dt){}