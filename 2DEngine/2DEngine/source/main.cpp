#include "framework.h"
#include "Graph.h"
GLF TwoDEngine;

Graph grid;

float keyPressTimer = .25f;
float keyPressCounter = 0;

void InitNodes();
float a_x, a_y;
int main() 
{
	TwoDEngine.InitWindow(1024, 720, "Hell YA!!");
	
	a_x = a_y = 0;
	grid.AddNodes(5, 5);
	grid.AddEdgesToNodes();
	InitNodes();

	while (TwoDEngine.UpdateFramework())
	{
		TwoDEngine.SetScreenColor(0.1f, 0.4f, 0.7f, 0.0f);
		TwoDEngine.currentFrame = glfwGetTime();
		TwoDEngine.deltaTime = TwoDEngine.currentFrame - TwoDEngine.lastFrame;
		TwoDEngine.lastFrame = TwoDEngine.currentFrame;

		keyPressCounter += TwoDEngine.deltaTime;
		
		for (int i = 0; i < grid.NodeList.size(); i++)
		{
			TwoDEngine.DrawSprite(grid.NodeList[i]->spriteID);
		}


		TwoDEngine.SwapBuffers();

	}
	grid.~Graph();
	TwoDEngine.Shutdown();
}


void InitNodes()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			grid.NodeList[i]->spriteID = TwoDEngine.CreateSprite("resources\\images\\greenbox.png",
																 grid.NodeList[i]->width, 
																 grid.NodeList[i]->height, 
																 grid.NodeList[i]->x,
																 grid.NodeList[i]->y);
			grid.NodeList[i]->x += grid.NodeList[i]->width;
		}
		grid.NodeList[i]->y += grid.NodeList[i]->height;
	}
}