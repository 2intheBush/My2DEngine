#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "framework.h"
#include <algorithm>
#include <stack>
#include <list>

//forward decleration
class Node;

struct Edge
{
	Edge(Node* firstNode, Node* secNode, float f_cost)
	{
		orgNode = firstNode;
		destNode = secNode;
		cost = f_cost;
	};
	~Edge(){};
	Node* getOrgNode(){ return orgNode; };
	Node* getDestNode(){ return destNode; };
	float getCost(){ return cost; };
	float cost;
	Node* destNode;
private:
	Node* orgNode;


};

class Node
{
public:
	
	Node(int a_width, int a_height, int a_colPos, int a_rowPos)
	{ 
		rowPos = a_rowPos; colPos = a_colPos;  
		width = a_width; height = a_height; 
		isVisited = false, isWall = false; 
	};
	~Node(){};
	int ReturnCoord(){ return x , y; };
	bool CheckIfVisited(){ return isVisited; };
	void SetVisited(){ isVisited = true; };
	void SetNotVisited(){ isVisited = false; };
	void AddAdjacentNode(Node* adj, float f_cost);
	unsigned int spriteID;
	int gScore;
	Node* previous;
	int width, height, x, y, rowPos, colPos;
	std::vector<Edge>EdgeList;
	bool isVisited, isWall;
private:

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
	void AddEdgesToNodes();
	//void Dijkstra(Node* start, Node* goal);
	//bool NodeCompare(Node* lhs, Node* rhs);
	//std::list<Node*> BuildPath();
	void DeleteNodesEdges(Node* n);
	std::vector<Node* >NodeList;
	std::list<Node*> result;
	int rowSize, colSize, xPos, yPos, yIncrease;
private:

};

#endif // _GRAPH_H_