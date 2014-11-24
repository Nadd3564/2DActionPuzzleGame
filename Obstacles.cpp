#include "Obstacles.h"
#include "ObjectManager.h"
#include "GameLayer.h"


Obstacles::Obstacles(GameLayer* game) : GameObject(game){}


Obstacles::~Obstacles(){}

Obstacles* Obstacles::create(int obstacle, cocos2d::CCPoint pos, float angle){
	Obstacles* obs = new Obstacles(GameLayer::s_pInstance);
	if (obs) {
        obs = obs->initObstacles(obstacle, pos, angle);
		obs->autorelease();
		return obs;
	}
	CC_SAFE_DELETE(obs);
	return NULL;
}

Obstacles* Obstacles::initObstacles(int obstacle, cocos2d::CCPoint pos, float angle)
{
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

	//��Q���̐���
	this->initWithFile(fileName.c_str());
	this->setPosition(pos);
	this->setRotation(angle);
	this->setTag(GameLayer::s_pInstance->kTag_Obstacles);

	//�����{�f�B����
	 b2BodyDef bodyDef;

	 switch(obstacle)
	 {
	 case GameLayer::ObstacleType::Obstacle1:
		case GameLayer::ObstacleType::Obstacle2:
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(this->getPositionX() / PTM_RATIO,
                               this->getPositionY() / PTM_RATIO);
			bodyDef.angle = 50 / PTM_RATIO;
			bodyDef.userData = this;
			_body = _game->getWorld()->CreateBody(&bodyDef);

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(this->getContentSize().width * 0.49/ PTM_RATIO, this->getContentSize().height * 0.45/ PTM_RATIO);
			_body->CreateFixture(&spriteShape, 1);
				

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}

		case GameLayer::ObstacleType::Obstacle3:
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(this->getPositionX() / PTM_RATIO,
                               this->getPositionY() / PTM_RATIO);
			bodyDef.userData = this;
			_body = _game->getWorld()->CreateBody(&bodyDef);
			

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(this->getContentSize().width * 0.5 / PTM_RATIO, this->getContentSize().height * 0.3 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 2);

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break; 
		}

		default:
		{
			bodyDef.type = b2_staticBody;
			bodyDef.position.Set(this->getPositionX() / PTM_RATIO,
                               this->getPositionY() / PTM_RATIO);
			bodyDef.userData = this;
			_body = _game->getWorld()->CreateBody(&bodyDef);

			//�����G���W����̕����̌`�Ƒ傫��
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(this->getContentSize().width * 0.5 / PTM_RATIO, this->getContentSize().height * 0.5 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 3);

			//��������
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}
	 }
    
	 this->setRigidBody(_body);
	return this;
}

void Obstacles::stateUpdate(){
    std::cout << "Update for the obstacles.";
}

void Obstacles::update(float dt){}