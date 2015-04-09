#include "CollisionListener.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void CollisionListener::BeginContact(b2Contact* contact) {
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

	RigidSprite *spriteA = static_cast<RigidSprite *>(bodyA->GetUserData());
	RigidSprite *spriteB = static_cast<RigidSprite *>(bodyB->GetUserData());

	if (spriteA && spriteB) {
			
		if ((spriteB->getTag() == kTag_Enemy &&
			spriteA->getTag() == kTag_Wisp)) {
			if (spriteA->getPow() > 10 || spriteB->getPow() > 10) {
				//火花が散るアクション
				GAME::getInstance()->collisionWisp();
				//敵NPC消滅アクション
				GAME::getInstance()->destroyEnemy(spriteB);
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
			}
		}
		else if ((spriteA->getTag() == kTag_Obstacles &&
			spriteB->getTag() == kTag_Wisp) ||
			(spriteB->getTag() == kTag_Obstacles &&
			spriteA->getTag() == kTag_Wisp)){
			if (spriteA->getPow() > 10 || spriteB->getPow() > 10) {
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
			}
		}

		
	}
}
