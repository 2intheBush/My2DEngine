#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include "Edge.h"
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
	int ReturnCoord(){ return x, y; };
	bool CheckIfVisited(){ return isVisited; };
	void SetVisited(){ isVisited = true; };
	void SetNotVisited(){ isVisited = false; };
	void AddAdjacentNode(Node* adj, float f_cost);
	unsigned int spriteID;
	int gScore;
	Node* previous;
	float hDistance;
	int width, height, x, y, rowPos, colPos;
	std::vector<Edge>EdgeList;
	bool isVisited, isWall;
private:

};

#endif