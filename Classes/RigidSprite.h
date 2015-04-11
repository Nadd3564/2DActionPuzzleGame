/*
* RigidSprite.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#ifndef __RigidSprite__
#define __RigidSprite__

#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

const float PTM_RATIO = 32.0;

class RigidSprite : public CCSprite
{
public:

	CC_SYNTHESIZE(bool, m_isDead, IsDead);
	
    RigidSprite();
	virtual ~RigidSprite();

    void setRigidBody(b2Body* body);
	b2Body* getBody();
	
protected:

	b2Body* m_pBody;
	
};

#endif /* defined(__RigidSprite__) */