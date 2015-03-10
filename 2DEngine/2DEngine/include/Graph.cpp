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
			Node* n = new Node(25, 25, i, j);
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

//void Graph::Dijkstra(Node* start, Node* goal)
//{
//	for (auto node : NodeList)
//	{
//		node->previous = NULL;
//		node->gScore = INFINITY;
//	}
//
//	std::list<Node*> NodeStack;
//	NodeStack.push_front(start);
//
//
//	while (!NodeStack.empty())
//	{
//		NodeStack.sort(NodeCompare);
//		Node* currentNode = NodeStack.front();
//		if (currentNode == goal)
//		{
//			std::cout << "found the End!" << std::endl;
//			//sort nodes
//
//			//for (int i = 0; i < NodeStack.size(); i++)
//			//{
//			//	NodeStack.pop();
//			//}
//			break;
//		}
//		currentNode = NodeStack.front();
//		NodeStack.pop_front();
//		currentNode->previous = currentNode;
//		currentNode->gScore = 0;
//		currentNode->isVisited = true;
//
//		for (auto Edge : currentNode->EdgeList)
//		{
//			Node* end = Edge.destNode;
//			if (end->isVisited == false)
//			{
//				currentNode->gScore += Edge.getCost();
//				if (Edge.cost <= currentNode->gScore)
//				{
//					end->previous = currentNode;
//					end->gScore = currentNode->gScore + Edge.getCost();
//					NodeStack.push_front(end);
//		
//				}
//			}
//		}
//	}
//	std::cout << goal << std::endl;
//}

void Graph::DeleteNodesEdges(Node* n)
{
	n->isWall = true;
}

//bool NodeCompare(Node* lhs, Node* rhs)
//{
//	return lhs->gScore < rhs->gScore;
//}
