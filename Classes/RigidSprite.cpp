#include "RigidSprite.h"

RigidSprite::RigidSprite() :
m_pBody(NULL),
m_isDead(false)
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
float RigidSprite::getVelocitySum()
{
	if (!m_pBody)
		return NULL;

	return pow(m_pBody->GetLinearVelocity().x, 2) +
		pow(m_pBody->GetLinearVelocity().y, 2);
}