#ifndef _DFSSEARCH_H
#define _DFSSEARCH_H

#include "globe.h"
 
using namespace std;
class DFSsearch {
	int maze[100][100];
	int tempmaze[100][100];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	void findPathDfs(node* root);
	void solutionAssemble(node* at);
	void copyMaze();
	int totalNodesExpanded;
	int maxTreeDepth;
	int maxFrontier;
	int solutionCost;
	int extraHeads;

public:
	void findPathDfs();
	stack<pair<int, int> > rS();
	int rSC();//Retrieve Solution Cost
	int rTD();//Retrieve Tree Depth
	int rSF();//Retrieve Size Frontier
	int returnNodesExpand();
	DFSsearch();
	DFSsearch(int maze[100][100], int dots, pair<int, int> beg, int row, int col);
	~DFSsearch();
};
#endif 
