#ifndef __HUDLAYER__
#define __HUDLAYER__

#include "cocos2d.h"

using namespace cocos2d;

class HudLayer : public cocos2d::CCLayer
{
public:
   
	virtual bool init();
    
    static CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(HudLayer);
    
    void numCollectedChanged (int numCollected);

private:

	CCLabelTTF *_label;

};

#endif /* defined(__HUDLAYER__) */