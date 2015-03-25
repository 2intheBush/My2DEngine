#include "AITank.h"
#include "SteeringBehavior.h"

void AITank::Update()
{
	force = steerBehave->GetForce();
	CheckWallCollision();
}

void AITank::CheckWallCollision()
{
	//is x less than 0
	if (position[0] - size[0] * 5.f < 0)
	{
		velocity[0] *= -1;
	}
	// is x greater than 1024
	if (position[0] + size[0] * 5.f > 1024)
	{
		velocity[0] *= -1;
	}
	// is y less than 0
	if (position[1] - size[1] * 5.f < 0)
	{
		velocity[1] *= -1;
	}
	// is y greater than 720
	if (position[1] + size[1] * 5.f > 720)
	{
		velocity[1] *= -1;
	}
}