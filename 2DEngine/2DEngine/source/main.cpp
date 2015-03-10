#include "framework.h"
#include "Graph.h"
GLF TwoDEngine;

Graph grid;

float keyPressTimer = .25f;
float keyPressCounter = 0;

void InitSprites();
void SetSprites();
void Dijkstra(Node* start, Node* goal);
bool NodeCompare(Node* lhs, Node* rhs);
bool HeuristicCompare(Node* lhs, Node* rhs);
float GetHeuristic(Node* n);

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
	startNode = grid.NodeList[13];
	goalNode = grid.NodeList[140];

	// grid.Dijkstra(startNode, goalNode);
	
	
	startNode->spriteID = currentSprite;
	goalNode->spriteID = goalSprite;


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
			Node* n = grid.GetNode(x,y);
			grid.DeleteNodesEdges(n);
			n->spriteID = wallSprite;
		}

		if (TwoDEngine.command.IsKeyPressed(spacebar))
		{
			Dijkstra(startNode, goalNode);
			SetSprites();

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
	for (auto node : grid.result)
	{
		if (node->isVisited == true)
		{
			node->spriteID = trueSprite;
		}
	}
}

void Dijkstra(Node* start, Node* goal)
{
	for (auto node : grid.NodeList)
	{
		node->previous = NULL;
		node->gScore = INT_MAX;
	}

	std::list<Node*> NodeStack;
	NodeStack.push_front(start);

	while (!NodeStack.empty())
	{
		NodeStack.sort(NodeCompare);
		Node* currentNode = NodeStack.front();

		if (currentNode == goal)
		{
			std::cout << "found the End!" << std::endl;
			break;
		}
		NodeStack.pop_front();
		currentNode->gScore = 0;
		currentNode->isVisited = true;

		for (auto Edge : currentNode->EdgeList)
		{
			Node* end = Edge.destNode;
			if (!end->isVisited && !end->isWall)
			{
				float calcCost = currentNode->gScore + Edge.cost;
				if (calcCost < end->gScore)
				{
					end->previous = currentNode;
					end->gScore = calcCost;
					if (std::find(NodeStack.begin(), NodeStack.end(), end) == NodeStack.end())
					{
						NodeStack.push_back(end);
					}

				}
			}
		}
	}
	Node* cNode = goal;
	if (cNode->previous == nullptr)
	{
		return;
	}
	grid.result.push_front(cNode);
	Node* parent = cNode->previous;
	grid.result.push_front(parent);
 	while (parent != start)
	{
		parent = parent->previous;
		grid.result.push_front(parent);
	}
	for (auto node : grid.result)
	{
		std::cout << node->rowPos + 1 << ", " << node->colPos + 1 << std::endl;
	}
}

bool NodeCompare(Node* lhs, Node* rhs)
{
	return lhs->gScore < rhs->gScore;
}

bool HeuristicCompare(Node* lhs, Node* rhs)
{
	return lhs->gScore + GetHeuristic(lhs) < rhs->gScore + GetHeuristic(rhs);
}

float GetHeuristic(Node* n)
{
	return 0;
}