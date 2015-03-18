#ifndef _TANK_H_
#define _TANK_H_
#include "glm\glm.hpp"

class Tank
{
public:
	Tank(){};
	~Tank(){};
	glm::vec2 position;
	glm::vec2 size;
	glm::mat3 transform;
	float speed;
	virtual void Update() = 0;
};

#endif