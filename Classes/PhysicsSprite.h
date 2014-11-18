#ifndef __b2test__PhysicsSprite__
#define __b2test__PhysicsSprite__
#define PTM_RATIO 32.0

#include <iostream>
#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class PhysicsSprite : public CCSprite
{
protected:
    b2Body* m_pBody;
    
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body* body);
    
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
};

#endif /* defined(__b2test__PhysicsSprite__) */