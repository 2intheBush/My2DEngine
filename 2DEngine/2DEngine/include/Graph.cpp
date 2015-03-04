#include "Graph.h"

void Node::AddAdjacentNode(Node* adj, float f_cost)
{
	
	Edge newEdge(this, adj, f_cost);
	EdgeList.push_back(newEdge);
}

void Graph::CreateGrid(int numOfNodes, int xStart, int yStart)
{
	xPos = xStart;
	yPos = yStart;
	for (int i = 0; i < sqrt(numOfNodes); i++)
	{
		for (int j = 0; j < sqrt(numOfNodes); j++)
		{
			Node* n = new Node(25, 25, j, i);
			NodeList.push_back(n);
			yIncrease = n->height * 2;
			n->x = xPos;
			n->y = yPos;
			if (j == sqrt(numOfNodes) - 1)
			{
				xPos = xStart;
			}
			else
			{
				xPos += n->width * 2;
			}
		}
		yPos += yIncrease;
		colSize = rowSize += 1;
	}
}

void Graph::AddEdge(Node* n, int a_rowPos, int a_colPos)
{
	Node* second = GetNode(a_rowPos, a_colPos);
	Edge e(n, second, 1);
	n->EdgeList.push_back(e);
}

void Graph::AddEdgesToNodes()
{
	for (auto node : NodeList)
	{
		//North edge
		if (node->rowPos + 1 < rowSize)
		{
			AddEdge(node, node->rowPos + 1, node->colPos);
		}
		//south edge
		if (node->rowPos - 1 >= 0)
		{
			AddEdge(node, node->rowPos - 1, node->colPos);
		}
		//east edge
		if (node->colPos + 1 < colSize)
		{
			AddEdge(node, node->rowPos, node->colPos + 1);
		}
		//west edge
		if (node->colPos - 1 >= 0)
		{
			AddEdge(node, node->rowPos, node->colPos - 1);
		}
	}
}

void Graph::Dijkstra(Node* start, Node* goal)
{
	for (auto node : NodeList)
	{
		node->nScore = NULL;
		node->gScore = INFINITY;
	}

	std::stack<Node*> NodeStack;
	NodeStack.push(start);


	while (!NodeStack.empty())
	{
		Node* currentNode = NodeStack.top();
		if (currentNode == goal)
		{
			for (int i = 0; i < NodeStack.size(); i++)
			{
				NodeStack.pop();
				std::cout << "found the End!" << std::endl;
			}
			continue;
		}
		currentNode = NodeStack.top();
		NodeStack.pop();
		currentNode->nScore = currentNode;
		currentNode->gScore = 0;
		currentNode->isVisited = true;

		for (auto Edge : currentNode->EdgeList)
		{
			Node* end = Edge.destNode;
			if (end->isVisited == false)
			{
				currentNode->gScore += Edge.getCost();
				if (Edge.cost <= currentNode->gScore)
				{
					end->nScore = currentNode;
					end->gScore = currentNode->gScore + Edge.getCost();
					NodeStack.push(end);
		
				}
			}
		}
	}

}

