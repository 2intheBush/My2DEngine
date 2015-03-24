#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <fstream>
#include "animation.h"
#include "command.h"

class GLF
{
public:
	Command command;
	int hDirection, vDirection;
	double currentFrame, deltaTime, lastFrame = 0;
	std::vector<Sprite> mSpriteList;
	animate Animation;
	glm::mat4 m_MVP;
	const float* ortho;
	GLFWwindow* window;
	int InitWindow(int screenWidth, int screenHeight, const char* title);
	GLuint uiProgramTextured;
	GLuint MatrixIDTextured;
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	glm::mat4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
	void SetScreenColor(float a_red, float a_green, float a_blue, float a_alpha);
	void Shutdown();
	bool UpdateFramework();
	void SwapBuffers();
	void GetCursPos(double &xPos, double &yPos);

	void CreateAnimation(const char * a_fileName, AnimationType currentState, float width, float height);
	void LoadAnimationSprite(const char * a_fileName, AnimationType currentState);
	void DrawAnimatedSprite(AnimationType currentState);


	unsigned int CreateSprite(const char* a_fileName, int width, int height);
	void DrawSprites(unsigned int s);
	void MoveSprite(unsigned int s, float x, float y);
	void UpdateVertex(unsigned int s);
};
#endif