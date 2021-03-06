/*
* Obstacles.h
* EnterNirvana
*
* All Rights Reserved by Nadd3564
*
* Written by Nadd3564 on 2015/04/10.
*
*/

#ifndef __Obstacles__
#define __Obstacles__

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

enum ObstacleType
{
	Obstacle1,
	Obstacle2,
	Obstacle3,
	Obstacle4,
	length,
};

class Obstacles : public GameObject
{
public:

	Obstacles();
	~Obstacles();
	
	static Obstacles* create(int obstacle, CCPoint pos, float angle);
	void addObstacles(int level);
	std::string fileNameInit(int obstacle);
    b2BodyDef ObsBodyDef(b2BodyDef bodyDef, b2BodyType bodyType);
	b2PolygonShape ObsShape(float32 width, float32 height);
	b2FixtureDef ObsFixtureDef(float32 density, float32 restitution, float32 friction);
	virtual void update (float dt);

private:
	Obstacles* initObstacles(int obstacle, CCPoint pos, float angle);
};

#endif /* defined(__Obstacles__) */

