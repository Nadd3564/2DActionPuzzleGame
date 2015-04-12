/*
* TitleLayer.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#ifndef __TITLE_LAYER_H__
#define __TITLE_LAYER_H__

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayer
{
public:
    
	virtual bool init();  
	
	static cocos2d::CCScene* createScene();
    
	CREATE_FUNC(TitleLayer);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

private:

	TitleLayer();
	virtual ~TitleLayer();

	void onGame();
	void exit(cocos2d::CCObject *pSender);

};

#endif /* defined(__TITLE_LAYER_H__) */
