//
//  Enemy.h
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __TileGame__Enemy__
#define __TileGame__Enemy__

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	
	static Enemy* create(CCPoint position, const char* fileName);
	void addEnemy();
    b2BodyDef enemyBodyDef(Enemy* enemy);
	b2FixtureDef enemyFixtureDef(b2Shape* shape);
	virtual void update (float dt);

private:
	Enemy* initEnemy(CCPoint position, const char* fileName);
};


#endif /* defined(__Enemy__) */
