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

	virtual void stateUpdate(float dt);
	virtual bool onStateEnter();
	virtual bool onStateExit();
	virtual bool onTouchBeganEvent(CCTouch* pTouch, CCEvent* pEvent);
	virtual void onTouchMovedEvent(CCTouch* pTouch, CCEvent* pEvent);
	virtual void onTouchEndedEvent(CCTouch* pTouch, CCEvent* pEvent);
    
	virtual std::string getStateID(){ return s_normalID; }
    
    NormalState();
    virtual ~NormalState();
    
private:

	Player* m_pWisp;
	Enemy* m_pEnemy;
	Obstacles* m_pObs;
	static const std::string s_normalID;

	void s_normalToJudge();

};


#endif /* defined(__NormalState__) */
