#ifndef _TANK_H_
#define _TANK_H_
#include "Graph.h"

class Tank
{
public:
	Tank(){};
	~Tank(){};
	void Dijkstra(Node* start, Node* goal, Graph grid);
	bool NodeCompare(Node* lhs, Node* rhs);
	bool HeuristicCompare(Node* lhs, Node* rhs);
	float GetHeuristic(const Node* n);
	bool IsStraightLine(Node* begin, Node* end);
	bool operator()(const Node* lhs, const Node* rhs)
	{
		return  lhs->gScore + GetHeuristic(lhs) < rhs->gScore + GetHeuristic(rhs);
	}
	glm::vec2 RayDirection(glm::vec2& startPos, glm::vec2& endPos)
	{
		return glm::normalize(endPos - startPos);
	}
	std::vector<Node*> GetNodesInLine(Ray ray, Node* end);
	bool AABBRayCollision(Ray ray, Box b);
	Box AABB(Node* n);
	Node* FindNodeLine(float xCord, float yCord);
	Node* goalNode;
	std::vector<Node* >TankNodeList;

};

#endif