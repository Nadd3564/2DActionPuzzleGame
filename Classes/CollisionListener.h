#ifndef _EN_CollisionListener_
#define _EN_CollisionListener_

#include <Box2D\Box2D.h>

class CollisionListener : public b2ContactListener
{
    public :
		virtual void BeginContact(b2Contact* contact);
};


#endif /* defined(_EN_CollisionListener_) */
