#include "CollisionListener.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void CollisionListener::BeginContact(b2Contact* contact) {
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

	GameLayer* gameL = GameLayer::Instance();

    RigidSprite *spriteA = static_cast<RigidSprite *>(bodyA->GetUserData());
	RigidSprite *spriteB = static_cast<RigidSprite *>(bodyB->GetUserData());

	if (spriteA && spriteB) {

		if (spriteA->getTag() == gameL->kTag_Obstacles &&
			spriteB->getTag() == gameL->kTag_Obstacles) {
			if (spriteA->getPow() > 10 || spriteB->getPow() > 10) {
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
			}
		}
		else if ((spriteA->getTag() == gameL->kTag_Enemy &&
			spriteB->getTag() == gameL->kTag_Wisp) ||
			(spriteB->getTag() == gameL->kTag_Enemy &&
			spriteA->getTag() == gameL->kTag_Wisp)) {
			if (spriteA->getPow() > 10 || spriteB->getPow() > 10) {
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
				static_cast<Player *>(gameL->getWispTag())->setCanFire(false);
			}
		}
		else if ((spriteA->getTag() == gameL->kTag_Obstacles &&
			spriteB->getTag() == gameL->kTag_Wisp) || 
			(spriteB->getTag() == gameL->kTag_Obstacles &&
			spriteA->getTag() == gameL->kTag_Wisp)){
			if (spriteA->getPow() > 10 || spriteB->getPow() > 10) {
				SimpleAudioEngine::sharedEngine()->playEffect("hit.mp3");
				static_cast<Player *>(gameL->getWispTag())->setCanFire(false);
			}
		}
	}
}
