#include "framework.h"

int GLF::InitWindow(int screenWidth, int screenHeight, const char* title)
{
	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//make the window's context current
	glfwMakeContextCurrent(window);

	//Start GLEW
	if (glewInit() != GLEW_OK)
	{
		//OpenGL didn't Start up... Shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	};

	//alpha blend
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	return 0;
}

void GLF::Shutdown()
{
	glfwTerminate();
}
bool GLF::UpdateFramework()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	return !(glfwWindowShouldClose(window));
}
void GLF::SetScreenColor(float a_red, float a_green, float a_blue, float a_alpha)
{
	glClearColor(a_red, a_green, a_blue, a_alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	command.HandleInput(window);
	hDirection = command.horzAxis;
	vDirection = command.vertAxis;
}
void GLF::SwapBuffers()
{
	glfwSwapBuffers(window);
	lastFrame = currentFrame;
	//poll for and process events
	glfwPollEvents();
}

unsigned int GLF::CreateSprite(const char* a_fileName, int width, int height)
{
	Sprite s(a_fileName, width, height);
	mSpriteList.emplace_back(s);
	return mSpriteList.size() - 1;
}

void GLF::DrawSprites(unsigned int s)
{
	mSpriteList[s].Draw();
}

void GLF::MoveSprite(unsigned int s, glm::vec2 x_y)
{
	mSpriteList[s].x = x_y[0];
	mSpriteList[s].y = x_y[1];
	UpdateVertex(s, x_y);
 }

void GLF::UpdateVertex(unsigned int s, glm::vec2 x_y)
{
	//mSpriteList[s].vertex[0].position = glm::vec2(mSpriteList[s].x - mSpriteList[s].sWidth, mSpriteList[s].y - mSpriteList[s].sHeight);
	//mSpriteList[s].vertex[1].position = glm::vec2(mSpriteList[s].x - mSpriteList[s].sWidth, mSpriteList[s].y + mSpriteList[s].sHeight);
	//mSpriteList[s].vertex[2].position = glm::vec2(mSpriteList[s].x + mSpriteList[s].sWidth, mSpriteList[s].y + mSpriteList[s].sHeight);
	//mSpriteList[s].vertex[3].position = glm::vec2(mSpriteList[s].x + mSpriteList[s].sWidth, mSpriteList[s].y - mSpriteList[s].sHeight);
	mSpriteList[s].Translation(x_y);
}

void GLF::CreateAnimation(const char * a_fileName, AnimationType currentState, float width, float height)
{

	Animation.LoadAnimationUV(a_fileName, currentState);
	//Sprite s(a_fileName, width, height);
	//Animation.AnimatedSpriteMap.emplace(std::pair<AnimationType, Sprite>(currentState, s));
}

void LoadAnimationSprite(const char * a_fileName, AnimationType currentState)
{
	
}

void GLF::DrawAnimatedSprite(AnimationType currentState)
{
	Animation.PlayAnimation(currentState);
}

void GLF::GetCursPos(double &xPos, double &yPos)
{
	glfwGetCursorPos(window, &xPos, &yPos);
}

