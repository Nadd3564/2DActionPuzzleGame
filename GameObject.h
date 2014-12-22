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
    //virtual void setStrategy();
	virtual void stateUpdate(float dt) = 0;
	GameObject(GameLayer* game);
	~GameObject();
	CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(GameLayer *, _gameL, gGame);
	virtual void update(float dt);

private:
    //std::string strategy;
    
};


#endif /* defined(__GameObject__) */
