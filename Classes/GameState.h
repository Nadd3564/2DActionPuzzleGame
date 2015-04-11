//
//  GameState.h
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __GameState__
#define __GameState__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

class GameLayer;
class ObjectManager;

class GameState : public CCNode
{
public:

	GameState();
	virtual ~GameState();

    virtual void stateUpdate(float dt) = 0;
    virtual bool onStateEnter() = 0;
    virtual bool onStateExit() = 0;
	virtual bool onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent) = 0;
	virtual void onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent) = 0;
	virtual void onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent) = 0;

    virtual std::string getStateID() = 0;
    
protected:

	std::vector<GameObject*> m_gObjects;

};

#endif /* defined(__GameState__) */
