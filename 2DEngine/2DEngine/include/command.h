#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "GL\glew.h"
//#include "GL\wglew.h"
//glew has to go first.
#include "GLFW\glfw3.h"

enum KeyPressed{
	w = GLFW_KEY_W,
	a = GLFW_KEY_A,
	s = GLFW_KEY_S,
	d = GLFW_KEY_D,
	spacebar = GLFW_KEY_SPACE,
	esc = GLFW_KEY_ESCAPE,
	leftbutton = GLFW_MOUSE_BUTTON_LEFT,
	rightbutton = GLFW_MOUSE_BUTTON_RIGHT,
};

class Command
{
public:
	~Command(){};
	virtual void excecute() = 0;
};


class MoveUpCommand : public Command
{
public:
	virtual void excecute(){ MoveUp(); };
private:
	void MoveUp();
};

class MoveDownCommand : public Command
{
public:
	virtual void excecute(){ MoveDown(); };
private:
	void MoveDown();
};

class MoveLeftCommand : public Command
{
public:
	virtual void excecute(){ MoveLeft(); };
private:
	void MoveLeft();
};

class MoveRightCommand : public Command
{
public:
	virtual void excecute(){ MoveRight(); };
private:
	void MoveRight();
};

static class InputHandler
{
public:
	void HandleInput(GLFWwindow* a_window)
	{
		window = a_window;
		vertMovement = horzMovement = 0;
		if (IsKeyPressed(w)) ButtonW_->excecute();
		if (IsKeyPressed(a)) ButtonA_->excecute();
		if (IsKeyPressed(s)) ButtonS_->excecute();
		if (IsKeyPressed(d)) ButtonD_->excecute();
	}

	Command* ButtonW_;
	Command* ButtonA_;
	Command* ButtonS_;
	Command* ButtonD_;

	static float vertMovement;
	static float horzMovement;
private:
	GLFWwindow* window;

	bool IsKeyPressed(KeyPressed key){ return glfwGetKey(window, key); };
};
#endif