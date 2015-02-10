#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <string>
#include "sprite.h"
#include "animation.h"
#include "command.h"

class GLF
{
public:
	InputHandler command;

	std::vector<Sprite> mSpriteList;
	const float* ortho;
	GLFWwindow* window;
	int InitWindow(int screenWidth, int screenHeight, const char* title);
	GLuint uiProgramTextured;
	GLuint MatrixIDTextured;
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	const float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	void SetScreenColor(float a_red, float a_green, float a_blue, float a_alpha);
	void Shutdown();
	bool UpdateFramework();
	void SwapBuffers();
	
	unsigned int CreateSprite(const char* a_fileName, int width, int height);
	void DrawSprite(unsigned int s);
	void MoveSprite(unsigned int s, float x, float y);
	void UpdateVertex(unsigned int s);
};
#endif