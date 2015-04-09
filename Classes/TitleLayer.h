#ifndef __TITLE_LAYER_H__
#define __TITLE_LAYER_H__

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayer
{
public:
    
	virtual bool init();  
	
	static cocos2d::CCScene* createScene();
    
	void onGame(CCObject* pSender);
    
	CREATE_FUNC(TitleLayer);

private:

	TitleLayer();
	virtual ~TitleLayer();

};

#endif /* defined(__TITLE_LAYER_H__) */
