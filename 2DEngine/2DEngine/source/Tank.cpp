#include "Tank.h"

void Tank::Dijkstra(Node* start, Node* goal, Graph &grid)
{
	for (auto node : grid.NodeList)
	{
		node->previous = NULL;
		node->gScore = INT_MAX;
	}

	for (auto node : grid.NodeList)
	{
		node->hDistance = glm::distance(glm::vec2(node->x, node->y), glm::vec2(goal->x, goal->y));
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
	Node* begin = *grid.result.begin();
	Node* end = *(grid.result.begin() + 2);

	while (std::find(grid.result.begin(), grid.result.end(), end) + 1 != grid.result.end())
	{
		if (IsStraightLine(begin, end, grid))
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



bool Tank::IsStraightLine(Node* begin, Node* end, Graph &grid)
{
	glm::vec2 rDirection = RayDirection(glm::vec2(begin->x, begin->y), glm::vec2(end->x, end->y));
	Ray ray(glm::vec2(begin->x, begin->y), rDirection);
	std::vector<Node* > NodesInLine;
	GetNodesInLine(NodesInLine, ray, end, grid);
	for (auto Node : NodesInLine)
	{
		if (Node->isWall)
		{
			//check collision
			Box box = grid.AABB(Node);
			if (AABBRayCollision(ray, box))
			{
				return false;
			}
		}
	}
	return true;
}

glm::vec2 Tank::RayDirection(glm::vec2& startPos, glm::vec2& endPos)
{
	return glm::normalize(endPos - startPos);
}

void Tank::GetNodesInLine(std::vector<Node*> &v, Ray ray, Node* end, Graph &grid)
{
	glm::vec2 currentPos = ray.origin;
	glm::vec2 size(end->width, end->height);
	Node* currentNode = NULL;
	while (currentNode != end)
	{
		currentPos += (size * 2.f) * ray.direction;
		currentNode = grid.FindNodeLine(currentPos.x, currentPos.y);
		//if (std::find())
		if (std::find(v.begin(), v.end(), currentNode) == v.end())
		{
			v.push_back(currentNode);
		}
	}
}

bool Tank::AABBRayCollision(Ray& ray, Box b)
{
	float tmin = INT_MIN, tmax = INT_MAX;
	if (ray.direction.x != 0.0f)
	{
		float tx1 = (b.minPoint.x - ray.origin.x) * (1 / ray.direction.x);
		float tx2 = (b.maxPoint.x - ray.origin.x) * (1 / ray.direction.x);

		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}

	if (ray.direction.y != 0.0f)
	{
		float ty1 = (b.minPoint.y - ray.origin.y) * (1 / ray.direction.y);
		float ty2 = (b.maxPoint.y - ray.origin.y) * (1 / ray.direction.y);

		tmin = std::max(tmin, std::min(ty1, ty2));
		tmax = std::min(tmax, std::max(ty1, ty2));

	}
	return tmax >= tmin;
}