//
//  Player.cpp
//  TileGame
//
//  Created by athenaeum on 2014/11/18.
//
//
#include "Player.h"

void Player::setPlayerPosition(cocos2d::CCPoint* diff, cocos2d::CCPoint playerPos,
                       float tileWidth, float tileHeight, float mapWidth, float mapHeight)
{
	if(diff){
        if ( abs(diff->x) > abs(diff->y) ) {
            if (diff->x > 0) {
                
                playerPos.x += tileWidth;
            } else {
                playerPos.x -= tileWidth;
            }
        } else {
            if (diff->y > 0) {
                playerPos.y += tileHeight;
            } else {
                playerPos.y -= tileHeight;
            }
        }
        
        // safety check on the bounds of the map
        if (playerPos.x <= (mapWidth * tileWidth) &&
            playerPos.y <= (mapHeight * tileHeight) &&
            playerPos.y >= 0 &&
            playerPos.x >= 0 )
        {
            this->setPosition(playerPos);
		}
    }
}

void Player::addForceToWisp(CCNode* wisp){
	//ウィスプを可動出来るようにする
	RigidSprite* will = dynamic_cast<RigidSprite*>(wisp);
	will->m_pBody->SetType(b2_dynamicBody);
	//ウィスプに力を加える
	will->m_pBody->ResetMassData();
	will->m_pBody->ApplyLinearImpulse(b2Vec2(8.0f, 3.0f), will->m_pBody->GetWorldCenter());
}

b2BodyDef Player::groundBodyDef(){
	 b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 0.0f);
	return groundBodyDef;
}