//
//  GameObject.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject(){}

void GameObject::update(float dt)
{
    if (this->m_pBody && isVisible())
	{
		setPositionX(m_pBody->GetPosition().x * PTM_RATIO);
		setPositionY(m_pBody->GetPosition().y * PTM_RATIO);
		setRotation(CC_RADIANS_TO_DEGREES(-1 * m_pBody->GetAngle()));
    }
}