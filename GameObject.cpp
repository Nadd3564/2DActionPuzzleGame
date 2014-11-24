//
//  GameObject.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "GameObject.h"

GameObject::GameObject(GameLayer* game){
	_game = game;
}

GameObject::~GameObject(){}

/* void GameObject::setStrategy()
{
    
}
 */

void GameObject::update(float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
        setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
    }
}