//
//  GameObject.h
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <cocos2d.h>
#include "RigidSprite.h"

class GameLayer;

class GameObject : public RigidSprite
{
public:

	CC_SYNTHESIZE(b2Body *, _body, Body);
	CC_SYNTHESIZE(GameLayer *, _gameL, gGame);

	GameObject(GameLayer* game);
	~GameObject();

    virtual void stateUpdate(float dt) = 0;
	virtual void update(float dt);
    
};


#endif /* defined(__GameObject__) */
