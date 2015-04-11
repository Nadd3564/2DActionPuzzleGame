#ifndef _EN_CollisionListener_
#define _EN_CollisionListener_

#include <Box2D\Box2D.h>

class CollisionListener : public b2ContactListener
{
    public :
		virtual void BeginContact(b2Contact* contact);
		//virtual void EndContact(b2Contact* contact);
	private:
		bool IsEqualsTag(int tag, int type);
		bool IsOver(b2Body *obstacles);
};


#endif /* defined(_EN_CollisionListener_) */
