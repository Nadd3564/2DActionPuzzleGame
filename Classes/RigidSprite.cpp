#include "RigidSprite.h"

RigidSprite::RigidSprite() :
m_pBody(NULL),
m_isdead(false)
{}

RigidSprite::~RigidSprite(){}

void RigidSprite::setRigidBody(b2Body* body)
{
	assert(body != NULL);
	m_pBody = body;
}

b2Body* RigidSprite::getBody()
{
	return m_pBody;
}

//�X�v���C�g�̏c���ړ��ʂ̂Q��̘a���擾
float RigidSprite::getPow()
{
	if (m_pBody)
	{
		return pow(m_pBody->GetLinearVelocity().x, 2) +
			pow(m_pBody->GetLinearVelocity().y, 2);
	}
	return 0.0;
}