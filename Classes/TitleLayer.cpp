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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *button = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(TitleLayer::onGame));
    
	button->setPosition(ccp(origin.x + visibleSize.width - button->getContentSize().width / 2,
		origin.y + button->getContentSize().height / 2));

    CCMenu* pMenu = CCMenu::create(button, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(pSprite, 0);
    
    return true;
}


void TitleLayer::onGame(CCObject* pSender)
{
	CCScene *game = GAME::createScene(3, 1);
	CCTransitionFade *fade = CCTransitionFade::create(0.5, game);
	CCDirector::sharedDirector()->replaceScene(fade);
}