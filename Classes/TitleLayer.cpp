/*
* TitleLayer.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#include "TitleLayer.h"
#include "GameLayer.h"

USING_NS_CC;

CCScene* TitleLayer::createScene()
{
    CCScene *scene = CCScene::create();
    TitleLayer *layer = TitleLayer::create();
	scene->addChild(layer);

	return scene;
}

TitleLayer::TitleLayer(){}

TitleLayer::~TitleLayer(){}

bool TitleLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	//シングルタップモード
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
   
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite *background = CCSprite::create("background1.png");
	background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(background, 0);

	CCSprite *logo = CCSprite::create("title_text.png");
	logo->setPosition(ccp(screenSize.width / 2, screenSize.height / 1.5));
	this->addChild(logo, 1);

	//終了ボタン
	CCMenuItemImage *exitButton =
		CCMenuItemImage::create(
		"exit.png",
		"exit.png",
		this,
		menu_selector(TitleLayer::exit));
	//ボタンからメニューを作成する
	CCMenu *menu = CCMenu::create(exitButton, NULL);
	//画面の中央へ表示
	menu->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(menu, kOrder_Result);
	

    return true;
}

bool TitleLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	onGame();
	return true;
}

void TitleLayer::onGame()
{
	CCScene *game = GAME::createScene(3, 1);
	CCTransitionSplitCols *splitCols = CCTransitionSplitCols::create(1.0, game);
	CCDirector::sharedDirector()->replaceScene(splitCols);
}

void TitleLayer::exit(CCObject *pSender)
{
	CCDirector::sharedDirector()->end();
}