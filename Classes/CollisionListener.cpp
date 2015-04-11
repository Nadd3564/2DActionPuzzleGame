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
				//火花が散るアクション
				OM::getInstance()->collisionWisp();
				//敵NPC消滅アクション
				OM::getInstance()->destroyEnemy(spriteB);
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
	if (len > 3.0)
		return true;
	return false;
}