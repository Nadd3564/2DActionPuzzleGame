#include "GameLayer.h"

#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#define BALL_INIT_POS ccp(96 ,150)
#define BALL_STRETCH_LENGTH 50

#define LAUNCHER_POS1 ccp(10, 135)
#define LAUNCHER_POS2 ccp(125, 140)

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
 
    this->initPhysics();
    //マルチタップモード
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    scheduleUpdate();
 
    return true;
}

void GameLayer::initPhysics(){
	//重力
	b2Vec2 gravity;
    gravity.Set(0.0f, -98.0f);
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
	instantiateBall();
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
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCNode* background = getChildByTag(kTag_Background);
	

	//create table sides
    b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    
    // 地面の形と大きさの定義
    float groundHeight = size.height * 0.1;
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, groundHeight / PTM_RATIO),
                  b2Vec2(size.width / PTM_RATIO, groundHeight / PTM_RATIO));
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
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//エネミー生成
	PhysicsSprite* enemy = new PhysicsSprite();
	enemy->autorelease();
	enemy->initWithFile("enemy1.png");
	enemy->setPosition(position);
	enemy->setTag(kTag_Enemy);

	//エネミーのアニメーション
	CCAnimation* animation =  CCAnimation::create();
	animation->addSpriteFrameWithFileName("enemy2.png");
	animation->addSpriteFrameWithFileName("enemy1.png");
	animation->setDelayPerUnit(1);

	CCRepeatForever* repeat = CCRepeatForever::create(CCAnimate::create(animation));
	enemy->runAction(repeat);

	//物理ボディ生成
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	_body = _world->CreateBody(&bodyDef);
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = enemy->getContentSize().width * 0.3 / PTM_RATIO;

   //物理特性
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    _body->SetUserData(enemy);
	
	enemy->setPhysicsBody(_body);
	this->addChild(enemy, kOrder_Enemy);

}

void GameLayer::instantiateBall(){
	//ボール生成
	PhysicsSprite* ball = new PhysicsSprite();
	ball->autorelease();
	ball->initWithFile("ball_1.png");
	ball->setPosition(BALL_INIT_POS);
	ball->setTag(kTag_Ball);
	ball->setZOrder(kOrder_Ball);

	//物理ボディ生成
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(ball->getPositionX() / PTM_RATIO,
                               ball->getPositionY() / PTM_RATIO);
	bodyDef.userData = ball; 
	_body = _world->CreateBody(&bodyDef);

	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
    spriteShape.m_radius = ball->getContentSize().width * 0.3 / PTM_RATIO;

	//物理特性
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spriteShape;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	_body->CreateFixture(&fixtureDef);
    _body->SetUserData(ball);
	
	ball->setPhysicsBody(_body);
	addChild(ball);


	//発射台を追加
	//PhysicsSprite* launcher1 = new PhysicsSprite();
	//launcher1->autorelease();
	//launcher1->initWithFile("launcher1.png");
	CCSprite* launcher1 = CCSprite::create("Cross1.png");
	launcher1->setScale(0.5);
	launcher1->setPosition(ccp(100, 100));
	addChild(launcher1, kOrder_Launcher1);

	CCSprite* launcher2 = CCSprite::create("Cross2.png");
	launcher2->setScale(0.5);
	launcher2->setPosition(launcher1->getPosition());
	addChild(launcher2, kOrder_Launcher2);
}

CCPoint GameLayer::processingPosition(CCPoint touch){
	//ボールの初期位置とタップ位置の距離
	int distance = touch.getDistance(BALL_INIT_POS);

	if(distance > BALL_STRETCH_LENGTH)
		//距離がBALL_STRETCH_LENGTHとなる位置を返す
		return BALL_INIT_POS + (touch - BALL_INIT_POS) * BALL_STRETCH_LENGTH / distance;
	else
		//タップ位置を返す
		return touch;
}


bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event){
	bool flg = false;
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCNode* ball = getChildByTag(kTag_Ball);
	if(ball && ball->boundingBox().containsPoint(touch->getLocation()))
	{
		//ボールの位置を計算
		ball->setPosition(processingPosition(touch->getLocation()));
		flg = true;
	}
	//instantiateEnemy(location);
	
	return flg;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCNode* ball = getChildByTag(kTag_Ball);
	if(ball)
	{
		ball->setPosition(processingPosition(touch->getLocation()));

		//ゴムを引くポイント
		float angle = ((BALL_INIT_POS - ball->getPosition()).getAngle());
		CCPoint pos = ball->getPosition() + ccp(-25, 0).rotate(CCPoint::forAngle(angle));

		//ゴムを表示
		CCNode* gum1 = getChildByTag(kTag_Gum1);
		if(!gum1)
		{
			gum1 = CCSprite::create("iron.png");
			addChild(gum1, kOrder_Gum1, kTag_Gum1);
		}

		gum1->setPosition(LAUNCHER_POS1 - (LAUNCHER_POS1 - pos));
		gum1->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS1 - pos).getAngle() * -1));
		gum1->setScaleX(LAUNCHER_POS1.getDistance(pos));
		gum1->setScaleY(10);

		CCNode* gum2 = getChildByTag(kTag_Gum2);
		if(!gum2)
		{
			gum2 = CCSprite::create("iron.png");
			addChild(gum2, kOrder_Gum2, kTag_Gum2);
		}

		gum2->setPosition(LAUNCHER_POS2 - (LAUNCHER_POS2 - pos) / 2);
		gum2->setRotation(CC_RADIANS_TO_DEGREES((LAUNCHER_POS2 - pos).getAngle() * -1));
		gum2->setScaleX(LAUNCHER_POS2.getDistance(pos));
		gum2->setScaleY(10);
	}
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event){}

void GameLayer::ccTouchCancelled(CCTouch* touch, CCEvent* event){}

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

