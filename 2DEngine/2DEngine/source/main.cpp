#include "Path.h"
#include "SteeringBehavior.h"

GLF TwoDEngine;

Graph grid;
Path path;
AITank seekTank;
AITank FleeTank;
Seek* seek;
Flee* flee;
float keyPressTimer = .25f;
float keyPressCounter = 0;

void InitSprites();
void SetSprites();
bool NodeCompare(Node* lhs, Node* rhs);

void Destroy()
{
	delete seek;
	delete flee;
}

float a_x, a_y;
unsigned int trueSprite, falseSprite, currentSprite, goalSprite, wallSprite, seekTankID;
double cursX, cursY;

void InitTank()
{
	seekTank.steerBehave = seek;
	seekTank.steerBehave->owner = &seekTank;
	seekTank.spriteID = seekTankID;
	seek->Target = &FleeTank;
	seekTank.maxVelocity = 10;
	seekTank.position = glm::vec2(600, 350);

	FleeTank.steerBehave = flee;
	FleeTank.steerBehave->owner = &FleeTank;
	FleeTank.maxVelocity = 10.0f;
	FleeTank.position = glm::vec2(60, 35);
}

int main() 
{
	TwoDEngine.InitWindow(1024, 720, "Hell YA!!");
	
	seek = new Seek;
	flee = new Flee;

	InitTank();

	a_x = a_y = 0;
	grid.CreateGrid(196, 25, 25);
	grid.AddEdgesToNodes();
	InitSprites();



	grid.startNode = grid.NodeList[0];
	grid.goalNode = grid.NodeList[180];
	
	grid.startNode->spriteID = currentSprite;
	grid.goalNode->spriteID = goalSprite;

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
			int x = (cursX / 50);
			int y = (cursY / 50);
			Node* n = grid.GetNode(y, x);
			grid.DeleteNodesEdges(n);
			n->spriteID = wallSprite;
		}

		if (TwoDEngine.command.IsKeyPressed(spacebar))
		{
			path.Dijkstra(grid.startNode, grid.goalNode, grid);
			SetSprites();
		}

		for (auto node : grid.NodeList)
		{
			TwoDEngine.MoveSprite(node->spriteID, node->x, node->y);
			TwoDEngine.DrawSprites(node->spriteID);
		}

		TwoDEngine.MoveSprite(seekTank.spriteID, seekTank.position[0], seekTank.position[1]);
		TwoDEngine.DrawSprites(seekTank.spriteID);

		//seekTank->Update();

		TwoDEngine.SwapBuffers();

	}
	Destroy();
	TwoDEngine.Shutdown();
}

void InitSprites()
{
	falseSprite = TwoDEngine.CreateSprite("resources\\images\\greenbox.png", 25, 25);

	trueSprite = TwoDEngine.CreateSprite("resources\\images\\redbox.png", 25, 25);

	wallSprite = TwoDEngine.CreateSprite("resources\\images\\wallbox.png", 25, 25);

	currentSprite = TwoDEngine.CreateSprite("resources\\images\\currentbox.png", 25, 25);

	goalSprite = TwoDEngine.CreateSprite("resources\\images\\goalbox.png", 25, 25);

	seekTankID = TwoDEngine.CreateSprite("resources\\images\\seekTank.png", 25, 25);

}

void SetSprites()
{
	for (auto node : grid.result)
	{
		if (node->isVisited == true)
		{
			node->spriteID = trueSprite;
		}
	}
}

bool NodeCompare(Node* lhs, Node* rhs)
{
	return lhs->gScore < rhs->gScore;
}

