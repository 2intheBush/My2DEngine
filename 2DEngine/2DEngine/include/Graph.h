#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "framework.h"
#include "Node.h"
#include <algorithm>
#include <stack>
#include <list>

struct Ray
{
	Ray(glm::vec2 a_origin, glm::vec2 a_direction) {origin = a_origin; direction = a_direction;};
	~Ray(){};
	glm::vec2 origin;
	glm::vec2 direction;
};

struct Box
{
	Box(glm::vec2 min, glm::vec2 max){ minPoint = min; maxPoint = max; };
	~Box(){};
	glm::vec2 minPoint;
	glm::vec2 maxPoint;
};

class Graph
{
public:
	Graph(){};
	~Graph(){
		for (int i = 0; i < NodeList.size(); i++)
		{
			delete NodeList[i];
		}
	};
	Node* startNode,* goalNode;
	void CreateGrid(int numOfNodes, int xStart, int yStart);
	void SetRow();
	void AddEdge(Node* n, int a_rowPos, int a_colPos);
	Node* GetNode(int a_rowPos, int a_colPos)
	{ 
		for (auto node : NodeList)
		{
			if (node->rowPos == a_rowPos && node->colPos == a_colPos)
			{
				return node;
			}
		}
	};
	Node* FindNodeLine(float xCord, float yCord);
	Box AABB(Node* n);
	void AddEdgesToNodes();
	//void Dijkstra(Node* start, Node* goal);
	//bool NodeCompare(Node* lhs, Node* rhs);
	//std::list<Node*> BuildPath();
	void DeleteNodesEdges(Node* n);
	std::vector<Node* >NodeList;
	std::vector<Node*> result;
	//std::list<Node*> resultSmoothed;
	int rowSize, colSize, xPos, yPos, yIncrease;
private:

};

#endif // _GRAPH_H_