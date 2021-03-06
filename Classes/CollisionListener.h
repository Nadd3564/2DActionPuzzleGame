/*
* CollisionListener.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#ifndef _EN_CollisionListener_
#define _EN_CollisionListener_

#include <Box2D\Box2D.h>

class CollisionListener : public b2ContactListener
{
    public :
		//衝突検知関数
		virtual void BeginContact(b2Contact* contact);
		//virtual void EndContact(b2Contact* contact);

	private:

		bool isEqualsTag(int tag, int type);
		bool isOver(b2Body *obstacles);

};


#endif /* defined(_EN_CollisionListener_) */
