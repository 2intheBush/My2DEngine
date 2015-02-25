#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "framework.h"
#include <stack>


struct Edge;

class Node
{
	typedef std::vector<Edge> EdgeList;
public:
	Node();
	Node(int a_iNum);
	int NodeNumber;
	bool visited;
	EdgeList g_nEdges;
};

struct Edge
{
	Node* g_nStart;
	Node* g_nEnd;
	float g_nCost;
};

class Graph
{
	typedef std::vector<Node*> NodeList;
public:
	Graph();
	~Graph();
	Graph(unsigned int a_uiNodeCount);
	void AddNode(Node* g_nNode);
	void RemoveNode(Node* g_nNode);
	void AddEdge(Node Start, Node End);
	void FollowNodePath(Node* N);
	void PrintNodes();
	void PrintNeighbors(Node N);

	bool SearchDFS(Node* Start, Node* End);
	void PathFromTo(Node* Start, Node* End);
	std::vector<int> PathOfNodes;
	void ResetVisited();
	Node* CurrentNode;
	NodeList g_nNodes;

};

#endif // _GRAPH_H_