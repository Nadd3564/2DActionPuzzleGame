/*
* RigidSprite.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

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