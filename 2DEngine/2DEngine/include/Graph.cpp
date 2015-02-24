#include "Graph.h"

Node::Node()
{

}

Node::Node(int a_iNum)
{
	NodeNumber = a_iNum;

}

Graph::Graph()
{

}

Graph::Graph(unsigned int a_uiNodeCount)
{

	for (int i = 0; i < a_uiNodeCount; i++)
	{
		Node *n = new Node(i);
		g_nNodes.push_back(n);
	}
}

void Graph::FollowNodePath(Node* N)
{
	CurrentNode = N;
}

void Graph::PrintNodes()
{
	std::cout << "Nodes: ";
	for (int i = 0; i < g_nNodes.size(); i++)
	{
		std::cout << g_nNodes[i]->NodeNumber;
	}
	std::cout << std::endl;
}

void Graph::PrintNeighbors(Node N)
{
	for (int i = 0; i < g_nNodes[N.NodeNumber]->g_nEdges.size(); i++)
	{
		std::cout << g_nNodes[N.NodeNumber]->g_nEdges[i].g_nEnd->NodeNumber;
		if (g_nNodes[N.NodeNumber]->g_nEdges.size() > 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

Graph::~Graph()
{
	for (int i = 0; i < g_nNodes.size(); i++)
	{

		delete g_nNodes[i];
	}
}

void Graph::AddNode(Node* g_nNode)
{
	g_nNodes.push_back(g_nNode);
}

//void Graph::RemoveNode(Node* g_nNode)
//{
//	for (int i = 0; i < g_nNodes.size(); i++)
//	{
//		if (g_nNode == g_nNodes[i])
//		{
//			// get rid of edges
//			//g_nNodes.pop_back;
//		}
//
//	}
//}