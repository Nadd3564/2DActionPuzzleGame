/*
* CollisionListener.cpp
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#include "CollisionListener.h"
#include "GameLayer.h"
#include "ObjectManager.h"


void CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
	
	RigidSprite *spriteA = static_cast<RigidSprite *>(bodyA->GetUserData());
	RigidSprite *spriteB = static_cast<RigidSprite *>(bodyB->GetUserData());

	if (spriteA && spriteB) {
		
		int tagA = spriteA->getTag();
		int tagB = spriteB->getTag();
		
		if (isEqualsTag(tagB, kTag_Enemy) && isEqualsTag(tagA, kTag_Wisp))
		{
				//�ΉԂ��U��A�N�V����
				OM::getInstance()->collisionWisp();
				//�GNPC���ŃA�N�V����
				OM::getInstance()->destroyEnemy(spriteB);
		}
		else if (isEqualsTag(tagB, kTag_Wisp) && isEqualsTag(tagA, kTag_Enemy))
		{
			//�ΉԂ��U��A�N�V����
			OM::getInstance()->collisionWisp();
			//�GNPC���ŃA�N�V����
			OM::getInstance()->destroyEnemy(spriteA);
		}
		
		RigidSprite *enemy = NULL;
		b2Body *obstacles = NULL;

		if (isEqualsTag(tagA, kTag_Enemy))
		{
			enemy = spriteA;
			obstacles = bodyB;
		}
		else if (isEqualsTag(tagB, kTag_Enemy))
		{
			enemy = spriteB;
			obstacles = bodyA;
		}

		if (enemy && isOver(obstacles)){
			OM::getInstance()->destroyEnemy(enemy);
		}
	}
}

bool CollisionListener::isEqualsTag(int tag, int type)
{
	if (tag == type)
		return true;
	return false;
}

bool CollisionListener::isOver(b2Body *obstacles)
{
	float32 len = obstacles->GetLinearVelocity().Length();
	if (len > 1.0)
		return true;
	return false;
}