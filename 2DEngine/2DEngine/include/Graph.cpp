#include "Graph.h"

void Node::AddAdjacentNode(Node* adj, float f_cost)
{
	Edge newEdge(this, adj, f_cost);
	EdgeList.push_back(newEdge);
}

void Graph::AddNodes(int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Node* n = new Node(i, j);
			NodeList.push_back(n);
		}
	}
}

void Graph::AddEdgesToNodes()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//first row
			if (i < 1)
			{
				//first node
				if (j < 1)
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
				//last node in row
				else if (j == col)
				{
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
				//rest of nodes
				else
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
			}
			//last row
			else if (i == row)
			{
				//first node
				if (j < 1)
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
				}
				//last node in row
				else if (j == col)
				{
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
				}
				//rest of nodes
				else
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
				}
			}
			//rest of rows
			else
			{
				//first node
				if (j < 1)
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
				//last node in row
				else if (j == col)
				{
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
				//rest of nodes
				else
				{
					//edge to the right
					NodeList[i][j].AddAdjacentNode(&NodeList[i + 1][j], 1);
					//edge to the left
					NodeList[i][j].AddAdjacentNode(&NodeList[i - 1][j], 1);
					//edge up
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j - 1], 1);
					//edge down
					NodeList[i][j].AddAdjacentNode(&NodeList[i][j + 1], 1);
				}
			}
		}
	}
}