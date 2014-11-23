#ifndef __RigidSprite__
#define __RigidSprite__
#define PTM_RATIO 32.0
#define WINSIZE CCDirector::sharedDirector()->getWinSize()

#include <iostream>
#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class RigidSprite : public CCSprite
{
public:
	b2Body* m_pBody;

    RigidSprite();
	~RigidSprite();
    void setRigidBody(b2Body* body);
    
    virtual bool isDirty(void);
};

#endif // defined(__RigidSprite__)