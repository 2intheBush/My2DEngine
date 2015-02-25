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
	Node* CurrentNode;
	CurrentNode = N;
	std::cout << "Current node: " << CurrentNode->NodeNumber << std::endl;
	std::cout << "The neighbors are:" << std::endl;
	PrintNeighbors(*g_nNodes[CurrentNode->NodeNumber]);
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

void Graph::ResetVisited()
{
	for (int i = 0; i < g_nNodes.size(); i++)
	{
		g_nNodes[i]->visited = false;
	}
}

bool Graph::SearchDFS(Node* Start, Node* End)
{
	std::stack <Node*> NodeStack;
	NodeStack.push(Start);
	while (!NodeStack.empty())
	{
		Node* Current = NodeStack.top();
		if (Current->visited == true)
		{
			NodeStack.pop();
			continue;
		}
		Current->visited = true;
		std::cout << Current->NodeNumber << "-> ";
		if (Current == End)
		{
			std::cout << "End!";
			return true;
		}
		if (Current->g_nEdges.empty() || CheckVisitedEdges(Current))
		{
			NodeStack.pop();
			continue;
		}
		else
		{
			for (int i = 0; i < Current->g_nEdges.size(); i++)
			{
				NodeStack.push(Current->g_nEdges[i].g_nEnd);
			}
		}
	}
	return false;
}

bool Graph::CheckVisitedEdges(Node* N)
{
	for (int i = 0; i < N->g_nEdges.size(); i++)
	{
		if (N->g_nEdges[i].g_nEnd->visited == false)
		{
			return false;
		}
	}
}

bool Graph::GScoreCompare(Node* left, Node* right)
{
	return(left->gScore < right->gScore);
}

void Graph::ShortestPathDijkstra(Node* Start, Node* End)
{
	
	Node* CurrentNode;
	for (int i = 0; i < g_nNodes.size(); i++)
	{
		g_nNodes[i]->nScore = NULL;
		g_nNodes[i]->gScore = INFINITY;
	}

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