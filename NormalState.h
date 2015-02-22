//
//  NormalState.h
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __NormalState__
#define __NormalState__

#include "GameState.h"
#include <cocos2d.h>
#include "ObjectManager.h"
#include "Player.h"
#include "Obstacles.h"
#include "Enemy.h"

using namespace cocos2d;

class NormalState : public GameState
{
public:

	void stateUpdate(float dt) override;
	bool onStateEnter() override;
    bool onStateExit() override;
    bool onTouchBeganEvent() override;
	void onTouchMovedEvent() override;
	void onTouchEndedEvent() override;
    
    std::string getStateID() override { return s_normalID; }
    
    NormalState();
    ~NormalState();
    
private:

	Player* _wisp;
	Enemy* _enemy;
	Obstacles* _obs;
	static const std::string s_normalID;

    float _tileWidth;
    float _tileHeight;
    float _mapWidth;
    float _mapHeight;
	  
};


#endif /* defined(__NormalState__) */
