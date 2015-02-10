#include "framework.h"

GLF TwoDEngine;

int main()
{
	TwoDEngine.InitWindow(1024, 720, "Hell YA!!");

	unsigned int s = TwoDEngine.CreateSprite("resources\\images\\Astroid.png", 32, 32);

	while (TwoDEngine.UpdateFramework())
	{
		TwoDEngine.SetScreenColor(0.1f, 0.4f, 0.7f, 0.0f);
		float x, y;
		x = y = 400;
		TwoDEngine.MoveSprite(s, x, y);
		TwoDEngine.DrawSprite(s);

		TwoDEngine.SwapBuffers();
	}

	TwoDEngine.Shutdown();
}