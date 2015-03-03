#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "framework.h"
#include <stack>

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
private:
	Node* orgNode;
	Node* destNode;
	float cost;
};

class Node
{
public:
	
	Node(int x_id, int y_id){ width = height = 25; isVisited = false; };
	~Node(){};
	int ReturnCoord(){ return x , y; };
	bool CheckIfVisited(){ return isVisited; };
	void SetVisited(){ isVisited = true; };
	void SetNotVisited(){ isVisited = false; };
	void AddAdjacentNode(Node* adj, float f_cost);
	unsigned int spriteID;
	float width, height, x, y;
private:
	bool isVisited;
	std::vector<Edge>EdgeList;
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
	void AddNodes(int row, int col);
	void SetRow();
	Node* GetNode(int i_Node){ return NodeList[i_Node]; };
	void AddEdgesToNodes();
	std::vector<Node* >NodeList;
private:
	int row, col;

};

#endif // _GRAPH_H_