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
bool IsStraightLine(Node* begin, Node* end);
glm::vec2 RayDirection(glm::vec2& startPos, glm::vec2& endPos)
{
	return glm::normalize(startPos - endPos);
}
std::vector<Node*> GetNodesInLine(Ray ray, Node* end);
bool AABBRayCollision(Ray ray, Box b);
Box AABB(Node* n);

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

	grid.startNode = grid.NodeList[13];
	grid.goalNode = grid.NodeList[140];

	// grid.Dijkstra(startNode, goalNode);
	
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
			int x = ((cursX - 75) / 50);
			int y = ((cursY - 75) / 50);
			Node* n = grid.GetNode(x, y);
			grid.DeleteNodesEdges(n);
			n->spriteID = wallSprite;
		}

		if (TwoDEngine.command.IsKeyPressed(spacebar))
		{
 			Dijkstra(grid.startNode, grid.goalNode);
			SetSprites();
		}

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
	for (auto node : grid.resultSmoothed)
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
		NodeStack.sort(HeuristicCompare);
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
	grid.result.insert(grid.result.begin(), cNode);
	Node* parent = cNode->previous;
	grid.result.insert(grid.result.begin(), parent);
	while (parent != start)
	{
		parent = parent->previous;
		grid.result.insert(grid.result.begin(), parent);
	}

	int i = 3;
	Node* begin = grid.result.front();
	Node* end = grid.result[i];

	while (!grid.result.empty())
	{
		while (std::find(grid.result.begin(), grid.result.end(), begin) + 1 != grid.result.end())
		{
			i += 2;
			begin = grid.result.front();
			end = grid.result[i];
			
			grid.result.erase(grid.result.begin());
			if (IsStraightLine(begin, end))

			{
				grid.result.erase(grid.result.begin());
			}
			else
			{
				grid.resultSmoothed.push_back(begin);
				grid.resultSmoothed.push_back(end);
			}
		}
		break;
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
 	return glm::distance(glm::vec2(n->x, n->y), glm::vec2(grid.goalNode->x, grid.goalNode->y));
}

bool IsStraightLine(Node* begin, Node* end)
{
	glm::vec2 rDirection = RayDirection(glm::vec2(begin->x, begin->y),glm::vec2(end->x, end->y));
	Ray ray(glm::vec2(begin->x, begin->y), rDirection);
	std::vector<Node* > NodesInLine = GetNodesInLine(ray, end);
	for (auto Node : NodesInLine)
	{
		if (Node->isWall)
		{
			//check collision
			Box box = AABB(Node);
			if (AABBRayCollision(ray, box))
			{
				return false;
			}
		}
	}
	return true;
}

std::vector<Node*> GetNodesInLine(Ray ray, Node* end)
{
	std::vector<Node*> result;
	glm::vec2 currentPos = ray.origin;
	glm::vec2 size(end->width, end->height);
	Node* currentNode = NULL;
	while (currentNode != end)
	{
		currentPos += size * ray.direction;
		currentNode = grid.GetNode(((currentPos.x - 75) / 50), ((currentPos.y - 75) / 50));
		if (std::find(result.begin(), result.end(), currentNode) == result.end())
		{
			result.push_back(currentNode);
		}
	}
	return result;
}

bool AABBRayCollision(Ray ray, Box b)
{
	glm::vec2 min = (b.minPoint - ray.origin) / ray.direction;
	glm::vec2 max = (b.maxPoint - ray.origin) / ray.direction;

	glm::vec2 near = glm::min(min, max); 
	glm::vec2 far = glm::max(min, max);

	float enter = glm::max(glm::max(near.x, near.y), 0.0f);
	float exit = glm::min(far.x, far.y);
	return (exit > 0.0f && enter < exit);
}

Box AABB(Node* n)
{
	glm::vec2 min(n->x - n->width, n->y - n->height);
	glm::vec2 max(n->x + n->width, n->y + n->height);
	return Box(min, max);
}