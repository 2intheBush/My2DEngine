#ifndef _EDGE_H_
#define _EDGE_H_

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

#endif