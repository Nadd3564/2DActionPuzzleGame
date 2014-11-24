//
//  GameObject.h
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#ifndef __TileGame__GameObject__
#define __TileGame__GameObject__

#include <iostream>
#include <cocos2d.h>
#include "RigidSprite.h"


class GameLayer;

class GameObject : public RigidSprite
{
public:
    //virtual void setStrategy();
	GameObject(GameLayer* game);
	~GameObject();
	CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(GameLayer *, _game, gGame);
private:
    //std::string strategy;
    
};


#endif /* defined(__TileGame__GameObject__) */
