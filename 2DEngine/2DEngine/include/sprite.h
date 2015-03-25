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
	glm::vec2 position;
	glm::vec4 color;
	glm::vec2 UV;
};

class Sprite
{
public:
	Sprite(){};
	~Sprite(){};

	GLuint uiVAO;
	GLuint uiVBO;
	GLuint uiIBO;
	GLuint uiProgramTextured;
	GLuint MatrixIDText;
	glm::mat4 ortho;
	glm::mat4 MVPMatrix, viewMatrix;
	glm::mat4 transform;
	glm::vec3 translate, scale;
	Vertex vertex[4];
	int bpp;
	float x, y, sWidth, sHeight;
	glm::mat4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);


	void UpdateMatrix();
	void Translation(glm::vec2 x_y);

	unsigned int spriteID;
	unsigned int loadTexture(const char* o_fileName, int & a_iWidth, int & a_iHeight, int & a_iBPP);
	void UpdateUV(glm::vec2 vOne, glm::vec2 vTwo, glm::vec2 Vec3, glm::vec2 vFour);
	Sprite(const char* a_fileName, int width, int height, GLuint frameProgram);
	void Draw();
};

#endif