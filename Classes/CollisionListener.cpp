#include "CollisionListener.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
	
	RigidSprite *spriteA = static_cast<RigidSprite *>(bodyA->GetUserData());
	RigidSprite *spriteB = static_cast<RigidSprite *>(bodyB->GetUserData());

	if (spriteA && spriteB) {
		
		int tagA = spriteA->getTag();
		int tagB = spriteB->getTag();
		
		if (IsEqualsTag(tagB, kTag_Enemy) && IsEqualsTag(tagA, kTag_Wisp))
		{
				//火花が散るアクション
				GAME::getInstance()->collisionWisp();
				//敵NPC消滅アクション
				GAME::getInstance()->destroyEnemy(spriteB);
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
		}
		
		RigidSprite *enemy = NULL;
		b2Body *obstacles = NULL;

		if (IsEqualsTag(tagA, kTag_Enemy))
		{
			enemy = spriteA;
			obstacles = bodyB;
		}
		else if (IsEqualsTag(tagB, kTag_Enemy))
		{
			enemy = spriteB;
			obstacles = bodyA;
		}

		if (enemy && IsOver(obstacles)){
			GAME::getInstance()->destroyEnemy(enemy);
			SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
		}
	}
}

bool CollisionListener::IsEqualsTag(int tag, int type)
{
	if (tag == type)
		return true;
	return false;
}

bool CollisionListener::IsOver(b2Body *obstacles)
{
	if (obstacles->GetLinearVelocity().Length() > 3.0)
		return true;
	return false;
}