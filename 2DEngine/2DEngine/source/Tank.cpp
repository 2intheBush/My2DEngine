#include "Tank.h"

void Tank::Dijkstra(Node* start, Node* goal, Graph grid)
{
	TankNodeList = grid.NodeList;
	goalNode = goal;
	for (auto node : grid.NodeList)
	{
		node->previous = NULL;
		node->gScore = INT_MAX;
	}

	std::list<Node*> NodeStack;
	NodeStack.push_front(start);

	while (!NodeStack.empty())
	{
		NodeStack.sort();
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
	Node* begin = *grid.result.begin();
	Node* end = *(grid.result.begin() + 2);

	while (std::find(grid.result.begin(), grid.result.end(), end) + 1 != grid.result.end())
	{
		if (IsStraightLine(begin, end))
		{

			grid.result.erase(std::find(grid.result.begin(), grid.result.end(), begin) + 1);
			if (std::find(grid.result.begin(), grid.result.end(), end) + 1 != grid.result.end())
			{
				end = *(std::find(grid.result.begin(), grid.result.end(), end) + 1);
			}
		}
		else
		{
			begin = *(std::find(grid.result.begin(), grid.result.end(), begin) + 1);
			if (std::find(grid.result.begin(), grid.result.end(), end) + 1 != grid.result.end())
			{
				end = *(std::find(grid.result.begin(), grid.result.end(), end) + 1);
			}
		}
	}

	for (auto node : grid.result)
	{
		std::cout << node->rowPos + 1 << ", " << node->colPos + 1 << std::endl;
	}
}

bool Tank::HeuristicCompare(Node* lhs, Node* rhs)
{
	return lhs->gScore + GetHeuristic(lhs) < rhs->gScore + GetHeuristic(rhs);
}

float Tank::GetHeuristic(const Node* n)
{
	return glm::distance(glm::vec2(n->x, n->y), glm::vec2(goalNode->x, goalNode->y));
}

bool Tank::IsStraightLine(Node* begin, Node* end)
{
	glm::vec2 rDirection = RayDirection(glm::vec2(begin->x, begin->y), glm::vec2(end->x, end->y));
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

std::vector<Node*> Tank::GetNodesInLine(Ray ray, Node* end)
{
	std::vector<Node*> result;
	glm::vec2 currentPos = ray.origin;
	glm::vec2 size(end->width, end->height);
	Node* currentNode = NULL;
	while (currentNode != end)
	{
		currentPos += (size * 2.f) * ray.direction;
		currentNode = FindNodeLine(currentPos.x, currentPos.y);
		//if (std::find())
		if (std::find(result.begin(), result.end(), currentNode) == result.end())
		{
			result.push_back(currentNode);
		}
	}
	return result;
}

bool Tank::AABBRayCollision(Ray ray, Box b)
{
	glm::vec2 min = (b.minPoint - ray.origin) / ray.direction;
	glm::vec2 max = (b.maxPoint - ray.origin) / ray.direction;

	glm::vec2 near = glm::min(min, max);
	glm::vec2 far = glm::max(min, max);

	float enter = glm::max(glm::max(near.x, near.y), 0.0f);
	float exit = glm::min(far.x, far.y);
	return (exit > 0.0f && enter < exit);
}

Box Tank::AABB(Node* n)
{
	glm::vec2 min(n->x - n->width, n->y - n->height);
	glm::vec2 max(n->x + n->width, n->y + n->height);
	return Box(min, max);
}


Node* Tank::FindNodeLine(float xCord, float yCord)
{
	for (auto node : TankNodeList)
	{
		Box b = AABB(node);
		if (b.minPoint.x < xCord &&b.minPoint.y < yCord && b.maxPoint.x > xCord && b.maxPoint.y > yCord)
		{
			return node;
		}
	}
}