#ifndef _AITANK_H_
#define _AITANK_H_

#include "Tank.h"

class SteeringBehavior;

class AITank : public Tank
{
public:
	SteeringBehavior* steerBehave;
	glm::vec2 velocity;
	float maxVelocity;

	void Update();
};

#endif