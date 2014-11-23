#include "RigidSprite.h"

RigidSprite::RigidSprite()
:m_pBody(NULL)
{
}

RigidSprite::~RigidSprite()
{
}

void RigidSprite::setRigidBody(b2Body* body)
{
    m_pBody = body;
}

// CCSpriteクラスの関数をオーバーロード

bool RigidSprite::isDirty(void)
{
    return true;
}
