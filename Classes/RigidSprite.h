#ifndef __RigidSprite__
#define __RigidSprite__
#define PTM_RATIO 32.0

#include <iostream>
#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

class RigidSprite : public CCSprite
{
protected:
    b2Body* m_pBody;
    
public:
    RigidSprite();
    void setRigidBody(b2Body* body);
    
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
};

#endif // defined(__RigidSprite__)