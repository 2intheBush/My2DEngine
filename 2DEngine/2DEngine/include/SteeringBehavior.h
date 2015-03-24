#ifndef _STEERINGBEHAVIOR_H_
#define _STEERINGBEHAVIOR_H_

#include "AITank.h"

enum STEERING_TYPE
{
	SEEK,
};

class SteeringBehavior
{
public:
	SteeringBehavior(){};
	~SteeringBehavior(){};
	virtual glm::vec2 GetForce() = 0;
	AITank* owner;
};


class Seek : public SteeringBehavior
{
public:
	Seek(){};
	~Seek(){};
	glm::vec2 GetForce();
	AITank* Target;
};

class Flee : public SteeringBehavior
{
public:
	Flee(){};
	~Flee(){};
	glm::vec2 GetForce();
	AITank* Target;
};

class Wander : public SteeringBehavior
{
public:
	Wander(){};
	~Wander(){};
	glm::vec2 GetForce();
	AITank* Target;
};
#endif