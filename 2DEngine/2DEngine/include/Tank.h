#ifndef _TANK_H_
#define _TANK_H_

#include "Graph.h"

class Tank
{
public:
	Tank(){};
	~Tank(){};
	void Dijkstra(Node* start, Node* goal, Graph &grid);
	
	bool IsStraightLine(Node* begin, Node* end, Graph &grid);
	glm::vec2 RayDirection(glm::vec2& startPos, glm::vec2& endPos);
	void GetNodesInLine(std::vector<Node*> &v, Ray ray, Node* end, Graph &grid);
	bool AABBRayCollision(Ray ray, Box b);
};

#endif

static bool HeuristicCompare(Node* lhs, Node* rhs)
{
	return lhs->gScore + lhs->hDistance < rhs->gScore + lhs->hDistance;
}