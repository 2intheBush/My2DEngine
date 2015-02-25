#include "framework.h"
#include "Graph.h"
GLF TwoDEngine;
Graph g(6);

float keyPressTimer = .25f;
float keyPressCounter = 0;

void InitGraph();
void CheckGraphNodeNeighbors();


int main()
{
	TwoDEngine.InitWindow(1024, 720, "Hell YA!!");

	InitGraph();

	g.PrintNodes();
	std::cout << "Select a node to see its neighbors." << std::endl;
	
	g.SearchDFS(g.g_nNodes[0], g.g_nNodes[1]);

	while (TwoDEngine.UpdateFramework())
	{
		TwoDEngine.SetScreenColor(0.1f, 0.4f, 0.7f, 0.0f);
		TwoDEngine.currentFrame = glfwGetTime();
		TwoDEngine.deltaTime = TwoDEngine.currentFrame - TwoDEngine.lastFrame;
		TwoDEngine.lastFrame = TwoDEngine.currentFrame;

		keyPressCounter += TwoDEngine.deltaTime;

		//CheckGraphNodeNeighbors();
		g.ResetVisited();


		//g.PathFromTo(g.g_nNodes[0], g.g_nNodes[4]);
		for (int i = 0; i < g.PathOfNodes.size(); i++)
		{
			std::cout << g.g_nNodes[i] << "->";
		}
		TwoDEngine.SwapBuffers();
	}

	TwoDEngine.Shutdown();
}

void InitGraph()
{
	//Edge from 0 to 1
	Edge e1;
	e1.g_nStart = g.g_nNodes[0];
	e1.g_nEnd = g.g_nNodes[1];
	g.g_nNodes[0]->g_nEdges.push_back(e1);

	//Edge from 1 to 2
	Edge e2;
	e2.g_nStart = g.g_nNodes[1];
	e2.g_nEnd = g.g_nNodes[2];
	g.g_nNodes[1]->g_nEdges.emplace_back(e2);

	//Edge from 2 to 0
	Edge e3;
	e3.g_nStart = g.g_nNodes[2];
	e3.g_nEnd = g.g_nNodes[0];
	g.g_nNodes[2]->g_nEdges.push_back(e3);

	//Edge from 2 to 3
	Edge e4;
	e4.g_nStart = g.g_nNodes[2];
	e4.g_nEnd = g.g_nNodes[3];
	g.g_nNodes[2]->g_nEdges.push_back(e4);

	//Edge from 3 to 4
	Edge e5;
	e5.g_nStart = g.g_nNodes[3];
	e5.g_nEnd = g.g_nNodes[4];
	g.g_nNodes[3]->g_nEdges.push_back(e5);

	//Edge from 0 to 5
	Edge e6;
	e6.g_nStart = g.g_nNodes[0];
	e6.g_nEnd = g.g_nNodes[5];
	g.g_nNodes[0]->g_nEdges.push_back(e6);

	//Edge from 5 to 3
	Edge e8;
	e8.g_nStart = g.g_nNodes[5];
	e8.g_nEnd = g.g_nNodes[3];
	g.g_nNodes[5]->g_nEdges.push_back(e8);

	//Edge from 5 to 4
	Edge e7;
	e7.g_nStart = g.g_nNodes[5];
	e7.g_nEnd = g.g_nNodes[4];
	g.g_nNodes[5]->g_nEdges.push_back(e7);


}

void CheckGraphNodeNeighbors()
{
	if (keyPressTimer < keyPressCounter)
	{
		if (TwoDEngine.command.IsKeyPressed(Zero))
		{
			g.FollowNodePath(g.g_nNodes[0]);
			keyPressCounter = 0;
		}
		if (TwoDEngine.command.IsKeyPressed(One))
		{
			g.FollowNodePath(g.g_nNodes[1]);
			keyPressCounter = 0;
		}
		if (TwoDEngine.command.IsKeyPressed(Two))
		{
			g.FollowNodePath(g.g_nNodes[2]);
			keyPressCounter = 0;
		}
		if (TwoDEngine.command.IsKeyPressed(Three))
		{
			g.FollowNodePath(g.g_nNodes[3]);
			keyPressCounter = 0;
		}
		if (TwoDEngine.command.IsKeyPressed(Four))
		{
			g.FollowNodePath(g.g_nNodes[4]);
			keyPressCounter = 0;
		}
		if (TwoDEngine.command.IsKeyPressed(Five))
		{
			g.FollowNodePath(g.g_nNodes[5]);
			keyPressCounter = 0;
		}

	}
}