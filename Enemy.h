//
//  Enemy.h
//  TileGame
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
    ~Enemy();
	Enemy();
    static Enemy* create(Enemy* _enemy, b2Body* _body, b2World* _world,
							CCPoint position, const char* FileName, int kTag);
    b2BodyDef enemyBodyDef(Enemy* enemy);
	b2FixtureDef enemyFixtureDef(b2Shape* shape);

private:
    Enemy* initEnemy(Enemy* _enemy, b2Body* _body, b2World* _world,
					CCPoint position, const char* FileName, int kTag);
};


#endif /* defined(__TileGame__Enemy__) */
