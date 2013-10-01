// CS 440 MP1
// @author Will Hempy
// @netid hempy2

#ifndef GBFSEARCH_H__
#define GBFSEARCH_H__

#include "globe.h"

using namespace std;

class GBFsearch {
	int maze[100][100];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	void solutionAssemble(node* at);
	vector<node*> goals;
	int totalNodesExpanded;
	int maxTreeDepth;
	int solutionCost;
	int maxFrontier;
public:
	void findPathGBF();
	void findPathGBF(node * root);
	int** retrieveSolution();
	stack<pair<int, int> > rS();
	int rSC();//Retrieve Solution Cost
	int rTD();//Retrieve Tree Depth
	int rSF();//Retrieve Size Frontier
	int returnNodesExpand();
	GBFsearch();
	GBFsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g);
	~GBFsearch();
};

#endif
