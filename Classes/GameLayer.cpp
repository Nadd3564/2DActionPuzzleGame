#include "GameLayer.h"
#include "SimpleAudioEngine.h"


#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#define WISP_INIT_POS ccp(100 ,150)
#define WISP_STRETCH_LENGTH 50

#define CROSS_POS1 ccp(80, 135)
#define CROSS_POS2 ccp(125, 140)

USING_NS_CC;

GameLayer::GameLayer() {
    
}

//シーン生成
CCScene* GameLayer::createScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = GameLayer::create();
	scene->addChild(layer);

	return scene; 
}


bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Resources/BGM1.mp3", true);

    this->initPhysics();
    //シングルタップモード
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    scheduleUpdate();
 
    return true;
}

void GameLayer::initPhysics(){
	//重力
	b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    _world = new b2World(gravity);
	//動きが止まった物体について、計算を省略
    _world->SetAllowSleeping(true);
	//オブジェクトの衝突判定をする時にすり抜けないように調整して計算する。
    _world->SetContinuousPhysics(true);
	
}

void GameLayer::onEnter(){
	CCLayer::onEnter();

	instantiateBackground();
	instantiateGround();
	instantiateWisp();
	instantiateObstacleWithEnemy();
}

//背景の生成
void GameLayer::instantiateBackground(){
	//背景の設定
	CCSprite* background = CCSprite::create("background1.png");
	background->setAnchorPoint(ccp(0.0, 0.5));
	background->setPosition(ccp(0, WINSIZE.height / 2));
	addChild(background, kOrder_Background, kTag_Background);
}

//地面の生成
void GameLayer::instantiateGround(){
	CCNode* background = getChildByTag(kTag_Background);
	

	//物理ボディ生成
    b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    
    // 地面の形と大きさの定義
    float groundHeight = WINSIZE.height * 0.1;
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, groundHeight / PTM_RATIO),
                  b2Vec2(WINSIZE.width / PTM_RATIO, groundHeight / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);


    

	//物理特性
	b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.8;
	groundBody->CreateFixture(&groundBox,0);

	//地面ノード作成
	CCNode* node = CCNode::create();
	node->setAnchorPoint(ccp(0.5, 0.5));
	node->setPosition(ccp(background->getContentSize().width / 2, 25));
	this->addChild(node);
}

void GameLayer::instantiateEnemy(CCPoint position){
	//エネミー生成
	RigidSprite* enemy = new RigidSprite();
	enemy->autorelease();
	enemy->initWithFile("enemy2.png");
	enemy->setPosition(position);
	enemy->setTag(kTag_Enemy);

	//エネミーのアニメーション
	/*CCAnimation* animation =  CCAnimation::create();
	animation->addSpriteFrameWithFileName("Resources/enemy2.png");
	animation->addSpriteFrameWithFileName("Resources/enemy1.png");
	animation->setDelayPerUnit(1);

	CCRepeatForever* repeat = CCRepeatForever::create(CCAnimate::create(animation));
	enemy->runAction(repeat);*/

	//物理ボディ生成
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	_body = _world->CreateBody(&bodyDef);
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = enemy->getContentSize().width * 0.4 / PTM_RATIO;

   //物理特性
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
	
	enemy->setRigidBody(_body);
	this->addChild(enemy, kOrder_Enemy);

}

void GameLayer::instantiateWisp(){
	//ウィスプ生成
	RigidSprite* wisp = new RigidSprite();
	wisp->autorelease();
	wisp->initWithFile("wisp_1.png");
	wisp->setPosition(WISP_INIT_POS);
	wisp->setTag(kTag_Wisp);
	wisp->setZOrder(kOrder_Wisp);

	//物理ボディ生成
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
	bodyDef.position.Set(wisp->getPositionX() / PTM_RATIO,
                               wisp->getPositionY() / PTM_RATIO);
	bodyDef.userData = wisp; 
	_body = _world->CreateBody(&bodyDef);

	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = wisp->getContentSize().width * 0.3 / PTM_RATIO;

	//物理特性
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    
	wisp->setRigidBody(_body);
	addChild(wisp);


	//発射台を追加
	CCSprite* cross1 = CCSprite::create("Cross1.png");
	cross1->setScale(0.5);
	cross1->setPosition(ccp(100, 100));
	addChild(cross1, kOrder_Cross1);

	CCSprite* cross2 = CCSprite::create("Cross2.png");
	cross2->setScale(0.5);
	cross2->setPosition(cross1->getPosition());
	addChild(cross2, kOrder_Cross2);
}

CCPoint GameLayer::processingPosition(CCPoint touch){
	//ウィスプの初期位置とタップ位置の距離
	int distance = touch.getDistance(WISP_INIT_POS);

	if(distance > WISP_STRETCH_LENGTH)
		//距離がWISP_STRETCH_LENGTHとなる位置を返す
		return WISP_INIT_POS + (touch - WISP_INIT_POS) * WISP_STRETCH_LENGTH / distance;
	else
		//タップ位置を返す
		return touch;
}

void GameLayer::addForceToWisp(CCNode* wisp){
	//ウィスプを可動出来るようにする
	RigidSprite* will = dynamic_cast<RigidSprite*>(wisp);
	will->m_pBody->SetType(b2_dynamicBody);
	//ウィスプに力を加える
	will->m_pBody->ResetMassData();
	will->m_pBody->ApplyLinearImpulse(b2Vec2(10.0f, 3.0f), will->m_pBody->GetWorldCenter());
}

void GameLayer::instantiateObstacleWithEnemy(){
	//エネミー生成
	instantiateEnemy(ccp(636, 125));

	//障害物生成
	instantiateObstacle(ObstacleType::Obstacle4, ccp(536, 75), 0);
	instantiateObstacle(ObstacleType::Obstacle4, ccp(636, 75), 0);
	instantiateObstacle(ObstacleType::Obstacle4, ccp(736, 75), 0);

	instantiateObstacle(ObstacleType::Obstacle1, ccp(586, 150), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(586, 250), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(686, 150), 90);
	instantiateObstacle(ObstacleType::Obstacle1, ccp(686, 250), 90);
	instantiateObstacle(ObstacleType::Obstacle3, ccp(636, 325), 0);
}

void GameLayer::instantiateObstacle(ObstacleType obstacle, cocos2d::CCPoint pos, float angle){
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
		fileName = "headStone.png";
		break;
	case GameLayer::Obstacle4:
		fileName = "baseStone1.png";
		break;
	default:
		break;
	}

	//障害物の生成
	RigidSprite* obstacles = new RigidSprite();
	obstacles->autorelease();
	obstacles->initWithFile(fileName.c_str());
	obstacles->setPosition(pos);
	obstacles->setRotation(angle);
	obstacles->setTag(kTag_Obstacles);

	//物理ボディ生成
	 b2BodyDef bodyDef;

	 switch(obstacle)
	 {
		case ObstacleType::Obstacle1:
		case ObstacleType::Obstacle2:
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.angle = 50 / PTM_RATIO;
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 0.49/ PTM_RATIO, obstacles->getContentSize().height * 0.45/ PTM_RATIO);
			_body->CreateFixture(&spriteShape, 1);
				

			//物理特性
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.1;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}

		case ObstacleType::Obstacle3:
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);
			

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 1.0 / PTM_RATIO, obstacles->getContentSize().height * 0.3 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 2);

			//物理特性
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
			bodyDef.position.Set(obstacles->getPositionX() / PTM_RATIO,
                               obstacles->getPositionY() / PTM_RATIO);
			bodyDef.userData = obstacles;
			_body = _world->CreateBody(&bodyDef);

			//物理エンジン上の物質の形と大きさ
			b2PolygonShape spriteShape;
			spriteShape.SetAsBox(obstacles->getContentSize().width * 0.5 / PTM_RATIO, obstacles->getContentSize().height * 0.5 / PTM_RATIO);
			_body->CreateFixture(&spriteShape, 3);

			//物理特性
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &spriteShape;
			fixtureDef.density = 0.5;
			fixtureDef.restitution = 0.5;
			fixtureDef.friction = 0.3;
			_body->CreateFixture(&fixtureDef);
			break;
		}
	 }
    
	 obstacles->setRigidBody(_body);
	 addChild(obstacles, (int)kOrder::kOrder_Obstacles);
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
	bool flg = false;
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp && wisp->boundingBox().containsPoint(touch->getLocation()))
	{
		//ウィスプの位置を計算
		wisp->setPosition(processingPosition(touch->getLocation()));
		flg = true;
	}

	return flg;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp)
	{
		wisp->setPosition(processingPosition(touch->getLocation()));

		//鎖を引くポイント
		float angle = ((WISP_INIT_POS - wisp->getPosition()).getAngle());
		CCPoint pos = wisp->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(angle));

		//鎖を表示
		CCNode* chain1 = getChildByTag(kTag_Chain1);
		if(!chain1)
		{
			chain1 = CCSprite::create("iron.png");
			addChild(chain1, kOrder_Chain1, kTag_Chain1);
		}

		chain1->setPosition(CROSS_POS1 - (CROSS_POS1 - pos) / 2);
		chain1->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS1 - pos).getAngle() * -1));
		chain1->setScaleX(CROSS_POS1.getDistance(pos));
		chain1->setScaleY(10);

		CCNode* chain2 = getChildByTag(kTag_Chain2);
		if(!chain2)
		{
			chain2 = CCSprite::create("iron.png");
			addChild(chain2, kOrder_Chain2, kTag_Chain2);
		}

		chain2->setPosition(CROSS_POS2 - (CROSS_POS2 - pos) / 2);
		chain2->setRotation(CC_RADIANS_TO_DEGREES((CROSS_POS2 - pos).getAngle() * -1));
		chain2->setScaleX(CROSS_POS2.getDistance(pos));
		chain2->setScaleY(10);
	}
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){
	CCNode* wisp = getChildByTag(kTag_Wisp);
	if(wisp)
	{
		//鎖を削除
		removeChildByTag(kTag_Chain1);
		removeChildByTag(kTag_Chain2);

		wisp->setPosition(processingPosition(touch->getLocation()));

		//ウィスプに力を加える
		addForceToWisp(wisp);
	}
}

void GameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event){
	ccTouchEnded(touch, event);
}

void GameLayer::update(float dt)
{
   //フレーム毎にWorldの情報を更新
	float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 10;
    int32 positionIterations = 10;
    _world->Step(timeStep, velocityIterations, positionIterations);
 
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
			CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );

		
            //スプライトが画面の1/3まで落ちたら、非アクティブにする
            /*CCSize s = CCDirector::sharedDirector()->getWinSize();
            if(myActor->getPositionY()<s.height/1){
                b->SetActive(false);
			}*/
        }
    }
}

