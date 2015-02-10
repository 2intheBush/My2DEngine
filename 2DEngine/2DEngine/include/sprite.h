#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "GL\glew.h"
//#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "SOIL.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec2 UV;
};

class Sprite
{
public:
	Sprite(){};
	~Sprite(){};

	
	GLuint uiVBO;
	GLuint uiIBO;
	Vertex vertex[4];
	int bpp;
	float x, y, sWidth, sHeight;
	const float* ortho;

	unsigned int spriteID;
	unsigned int loadTexture(const char* o_fileName, int & a_iWidth, int & a_iHeight, int & a_iBPP);
	
	Sprite(const char* a_fileName, int width, int height);
	void Draw();
};

#endif