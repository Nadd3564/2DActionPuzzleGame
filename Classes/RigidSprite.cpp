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

b2Body* RigidSprite::getBody(){
	return m_pBody;
}

// CCSprite�N���X�̊֐����I�[�o�[���[�h
bool RigidSprite::isDirty(void)
{
    return true;
}
