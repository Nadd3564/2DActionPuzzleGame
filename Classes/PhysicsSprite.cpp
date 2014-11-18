#include "PhysicsSprite.h"

PhysicsSprite::PhysicsSprite()
:m_pBody(NULL)
{
}

void PhysicsSprite::setPhysicsBody(b2Body* body)
{
    m_pBody = body;
}

// CCSpriteクラスの関数をオーバーロード

bool PhysicsSprite::isDirty(void)
{
    return true;
}

// CCNodeクラスの関数をオーバーロード
// 表示されている画像を m_pBody に追従させるコード
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos = m_pBody->GetPosition();
    
    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;
    
    if (isIgnoreAnchorPointForPosition()) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }
    
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if (!m_obAnchorPointInPoints.equals(CCPointZero)) {
        x += c * -m_obAnchorPointInPoints.x + -s * -m_obAnchorPointInPoints.y;
        y += s * -m_obAnchorPointInPoints.x + c * -m_obAnchorPointInPoints.y;
    }
    
    m_sTransform = CCAffineTransformMake(c, s, -s, c, x, y);
    return m_sTransform;
}