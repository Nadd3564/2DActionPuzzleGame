//
//  ApproachState.cpp
//
//  Created by athenaeum on 2014/11/15.
//
//

#include "ApproachState.h"
#include "ObjectManager.h"
#include "NormalState.h"

const std::string ApproachState::s_approachID = "APPROACH";

void ApproachState::s_approachToNormal() {
	OM::getInstance()->getStateMachine()->changeState(new NormalState());
}

void ApproachState::s_approachToIdle() {
    //Game::Instance()->getStateMachine()->changeState(new IdleState());
}

ApproachState::ApproachState() {
    //CCSprite* player = (CCSprite*) HelloWorld::s_pInstance->getChildByTag(0);
    //ccColor3B playerColor = {arc4random() % 255,arc4random() % 255,arc4random() % 255};
    //shirt->setColor(playerColor);
    //HelloWorld::s_pInstance->addChild(this);
}

ApproachState::~ApproachState() {
    
}

void ApproachState::stateUpdate() {
    
}

void ApproachState::onInputEvent(CCPoint* pts) {
    
}

bool ApproachState::onStateEnter() {
    return true;
}

bool ApproachState::onStateExit() {
    return true;
}