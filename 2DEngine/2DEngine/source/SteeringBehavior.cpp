#include "SteeringBehavior.h"
#include "AITank.h"

glm::vec2 Seek::GetForce()
{
	if (Target->position - owner->position == glm::vec2(0, 0))
	{
		return glm::vec2(0, 0);
	}
	glm::vec2 force = glm::normalize(Target->position - owner->position);
	force *= owner->maxVelocity;
	return force - owner->velocity;
}

glm::vec2 Flee::GetForce()
{
	//if (Target->position - owner->position == glm::vec2(0, 0))
	//{
	//	return glm::vec2(0, 0);
	//}
	//glm::vec2 force = glm::normalize(Target->position - (Target->position - owner->position));
	//force *= owner->maxVelocity;
	//return force - owner->velocity;
	return  owner->velocity;
}

glm::vec2 Wander::GetForce()
{
	if (Target->position - owner->position == glm::vec2(0, 0))
	{
		return glm::vec2(0, 0);
	}

	return  glm::vec2(0,0);
}