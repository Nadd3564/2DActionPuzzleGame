//
//  GameState.h
//  TileGame
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __TileGame__GameState__
#define __TileGame__GameState__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameState : public CCNode
{
public:
    virtual void stateUpdate() = 0;
    
    virtual bool onStateEnter() = 0;
    virtual bool onStateExit() = 0;
    
    virtual void onInputEvent(CCPoint* pts) = 0;
    
    virtual std::string getStateID() = 0;
    
    GameState();
    ~GameState();
    
private:
    
    bool m_loadingComplete;
    bool m_exiting;
    
};

#endif /* defined(__TileGame__GameState__) */
