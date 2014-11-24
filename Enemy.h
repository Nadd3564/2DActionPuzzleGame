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
	Enemy(GameLayer * game);
	~Enemy();
    static Enemy* create(GameLayer* game, CCPoint position, const char* fileName, int kTag);
    b2BodyDef enemyBodyDef(Enemy* enemy);
	b2FixtureDef enemyFixtureDef(b2Shape* shape);
	virtual void update (float dt);

private:
	Enemy* initEnemy(GameLayer* game, CCPoint position, const char* fileName, int kTag);
};


#endif /* defined(__TileGame__Enemy__) */
