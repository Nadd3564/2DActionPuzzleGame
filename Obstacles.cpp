#include "Obstacles.h"
#include "ObjectManager.h"
#include "GameLayer.h"

USING_NS_CC;

Obstacles::Obstacles(GameLayer* game) : GameObject(game){}


Obstacles::~Obstacles(){}

Obstacles* Obstacles::create(int obstacle, CCPoint pos, float angle){
	Obstacles* obs = new Obstacles(GameLayer::Instance());
	if (obs) {
        obs->initObstacles(obstacle, pos, angle);
		obs->autorelease();
		GameLayer::Instance()->setObstacles(obs);
		return obs;
	}
	//何度も生成しないようガードをかける
	CC_SAFE_DELETE(obs);
	return NULL;
}

std::string Obstacles::fileNameInit(int obstacle){
	std::string fileName;

	switch (obstacle)
	{
	case GameLayer::Obstacle1:
		fileName = "stone1.png";
		break;
	case GameLayer::Obstacle2:
		fileName = "isi.png";
		break;
	case GameLayer::Obstacle3:
		fileName = "pumpkin.png";
		break;
	case GameLayer::Obstacle4:
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
	this->setTag(GameLayer::Instance()->kTag_Obstacles);

	//物理ボディ生成
	 b2BodyDef bodyDef;

	 switch(obstacle)
	 {
	    case GameLayer::ObstacleType::Obstacle1:
	    case GameLayer::ObstacleType::Obstacle2:
		{
			bodyDef = ObsBodyDef(bodyDef, b2_dynamicBody);
			bodyDef.angle = 50 / PTM_RATIO;
			_body = _gameL->getWorld()->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.49, 0.45);
			_body->CreateFixture(&spriteShape, 1);
				

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			_body->CreateFixture(&fixtureDef);
			break;
		}

		case GameLayer::ObstacleType::Obstacle3:
		{
			_body = _gameL->getWorld()->CreateBody(&ObsBodyDef(bodyDef, b2_dynamicBody));
			

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.5, 0.3);
			_body->CreateFixture(&spriteShape, 2);

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			_body->CreateFixture(&fixtureDef);
			break; 
		}

		default:
		{
			_body = _gameL->getWorld()->CreateBody(&ObsBodyDef(bodyDef, b2_staticBody));

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape = ObsShape(0.5, 0.5);
			_body->CreateFixture(&spriteShape, 3);

			//物理性質
			b2FixtureDef fixtureDef = ObsFixtureDef(0.5, 0.5, 0.3);
			fixtureDef.shape = &spriteShape;
			_body->CreateFixture(&fixtureDef);
			break;
		}
	 }
    
	 this->setRigidBody(_body);
	return this;
}

void Obstacles::addObstacles(){
	create(_gameL->Obstacle4, ccp(636, 75), 0);
	create(_gameL->Obstacle4, ccp(736, 75), 0);
	create(_gameL->Obstacle1, ccp(586, 150), 90);
	create(_gameL->Obstacle1, ccp(586, 250), 90);
	create(_gameL->Obstacle1, ccp(686, 150), 90);
	create(_gameL->Obstacle1, ccp(686, 250), 90);
	create(_gameL->Obstacle3, ccp(636, 325), 0);
}

void Obstacles::stateUpdate(float dt){
    std::cout << "Update for the obstacles.";
}

void Obstacles::update(float dt){}