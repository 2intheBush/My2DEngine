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
		if (Current->g_nEdges.empty() || CheckNodeEdges(Current))
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

		//NodeStack.pop();
	}
	return false;
}

bool Graph::CheckNodeEdges(Node* N)
{
	for (int i = 0; i < N->g_nEdges.size(); i++)
	{
		if (N->g_nEdges[i].g_nEnd->visited == false)
		{
			return false;
		}
	}
}

void Graph::PathFromTo(Node* Start, Node* End)
{
	std::vector<int> result;
	if (SearchDFS(Start, End) == true)
	{
		std::stack<Node*> NodePath;
		CurrentNode = Start;
		CurrentNode->visited = true;
		NodePath.push(CurrentNode);
		while (!NodePath.empty())
		{
			for (int i = 0; i < CurrentNode->g_nEdges.size(); i++)
			{
				NodePath.push(CurrentNode->g_nEdges[i].g_nEnd);
			}
			CurrentNode = NodePath.top();
			CurrentNode->visited = true;
			if (CurrentNode == End)
			{
				continue;
			}
			else
			{
				NodePath.pop();
			}
			CurrentNode = NodePath.top();
			CurrentNode->visited = true;
		}
		/*while (!NodePath.empty())
		{
			if (CurrentNode->visited == false)
			{
				PathOfNodes.emplace_back(CurrentNode->NodeNumber);
			}
			CurrentNode->visited = true;
			for (int i = 0; i < CurrentNode->g_nEdges.size(); i++)
			{
				if (CurrentNode->visited = false)
				{
					NodePath.push(CurrentNode->g_nEdges[i].g_nEnd);
					CurrentNode->visited = true;
					CurrentNode = NodePath.top();
					if (CurrentNode = End)
					{
						PathOfNodes.emplace_back(CurrentNode->NodeNumber);
						continue;
					}
				}
			}
			NodePath.pop();
			CurrentNode = NodePath.top();
		}*/
	}
	else
	{
		std::cout << "No path found." << std::endl;
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