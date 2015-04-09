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
		float velocitySumA = spriteA->getVelocitySum();
		float velocitySumB = spriteB->getVelocitySum();

		if ((tagB == kTag_Enemy) && (tagA == kTag_Wisp))
		{
			if (velocitySumA > 10 || velocitySumB > 10) {
				//火花が散るアクション
				GAME::getInstance()->collisionWisp();
				//敵NPC消滅アクション
				GAME::getInstance()->destroyEnemy(spriteB);
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
			}
		}
		else if ((tagA == kTag_Enemy) && (tagB == kTag_Enemy)){
				GAME::getInstance()->destroyEnemy(spriteA);
				GAME::getInstance()->destroyEnemy(spriteB);
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
		}
	}
}
