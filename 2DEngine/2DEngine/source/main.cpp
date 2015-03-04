#include "framework.h"
#include "Graph.h"
GLF TwoDEngine;

Graph grid;

float keyPressTimer = .25f;
float keyPressCounter = 0;

void InitSprites();
void SetSprites();

float a_x, a_y;
unsigned int trueSprite, falseSprite, currentSprite, goalSprite, wallSprite;
double cursX, cursY;
int main() 
{
	TwoDEngine.InitWindow(1024, 720, "Hell YA!!");
	
	a_x = a_y = 0;
	grid.CreateGrid(144, 100, 100);
	grid.AddEdgesToNodes();
	InitSprites();

	Node* startNode,* goalNode;
	startNode = grid.NodeList[3];
	goalNode = grid.NodeList[143];

	// grid.Dijkstra(startNode, goalNode);
	
	
	startNode->spriteID = currentSprite;
	goalNode->spriteID = goalSprite;

	SetSprites();

	while (TwoDEngine.UpdateFramework())
	{
		TwoDEngine.SetScreenColor(0.1f, 0.4f, 0.7f, 0.0f);
		TwoDEngine.GetCursPos(cursX, cursY);
		cursY = 720 - cursY;
		TwoDEngine.currentFrame = glfwGetTime();
		TwoDEngine.deltaTime = TwoDEngine.currentFrame - TwoDEngine.lastFrame;
		TwoDEngine.lastFrame = TwoDEngine.currentFrame;
		keyPressCounter += TwoDEngine.deltaTime;
		

		if (TwoDEngine.command.IsKeyPressed(s))
		{

			int x = ((cursX - 75) / 50);
			int y = ((cursY - 75) / 50);
			Node* n = grid.GetNode(y,x);
			n->isVisited = true;
			n->spriteID = wallSprite;
		}

		if (TwoDEngine.command.IsKeyPressed(spacebar))
		{
			grid.Dijkstra(startNode, goalNode);
		}

		//for (auto node : grid.NodePath)
		//{
		//	node->spriteID = 3;
		//}
		for (auto node : grid.NodeList)
		{
			TwoDEngine.MoveSprite(node->spriteID, node->x, node->y);
			TwoDEngine.DrawSprites(node->spriteID);
		}

		TwoDEngine.SwapBuffers();

	}
	grid.~Graph();
	TwoDEngine.Shutdown();
}


void InitSprites()
{
	falseSprite = TwoDEngine.CreateSprite("resources\\images\\greenbox.png", 25, 25);

	trueSprite = TwoDEngine.CreateSprite("resources\\images\\redbox.png", 25, 25);

	wallSprite = TwoDEngine.CreateSprite("resources\\images\\wallbox.png", 25, 25);

	currentSprite = TwoDEngine.CreateSprite("resources\\images\\currentbox.png", 25, 25);

	goalSprite = TwoDEngine.CreateSprite("resources\\images\\goalbox.png", 25, 25);

}

void SetSprites()
{
	for (auto node : grid.NodeList)
	{
		if (node->isVisited == true)
		{
			node->spriteID = trueSprite;
		}
	}
}



	