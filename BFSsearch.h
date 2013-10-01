//CS 440 MP1
// @author William Koehler
// @netid wkoehle2

#ifndef BFSSEARCH_H__
#define BFSSEARCH_H__

#include "globe.h"

using namespace std;

class BFSsearch {
	int maze[100][100];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	void solutionAssemble(node* at);
	void findPathBfs(node * root);
	int totalNodesExpanded;
	int maxTreeDepth;
	int solutionCost;
	int maxFrontier;
	int extraHeads;
public:
	void findPathBfs();
	//int** retrieveSolution();
	stack<pair<int, int> > rS();
	int rSC();//Retrieve Solution Cost
	int rTD();//Retrieve Tree Depth
	int rSF();//Retrieve Size Frontier
	int returnNodesExpand();
	BFSsearch();
	BFSsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col);
	~BFSsearch();
};

#endif
