//
//  ApproachState.h
//
//  Created by athenaeum on 2014/11/15.
//
//

#ifndef __ApproachState__
#define __ApproachState__

#include "GameState.h"
#include <cocos2d.h>

using namespace cocos2d;

class ApproachState : public GameState
{
public:
    virtual void stateUpdate();
    virtual bool onStateEnter();
    virtual bool onStateExit();
    virtual void onInputEvent(CCPoint* pts);
    
    virtual std::string getStateID() { return s_approachID; }
    
    ApproachState();
    ~ApproachState();
private:
    
    static const std::string s_approachID;
    static void s_approachToNormal();
    static void s_approachToIdle();
};

#endif /* defined(__ApproachState__) */
