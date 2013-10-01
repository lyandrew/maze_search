// CS 440 MP1
// @author Will Hempy
// @netid hempy2

#ifndef UCSEARCH_H__
#define UCSEARCH_H__

#include "globe.h"

using namespace std;

class UniformCost {
	int maze[100][100];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	void solutionAssemble(node* at);
	float dist(node * lhs, node * rhs);
	vector<node*> goals;
	int totalNodesExpanded;
	int maxTreeDepth;
	int solutionCost;
	int maxFrontier;
	int costFunct;
public:
	void findPathUC();
	void findPathUC(node * root);
	int** retrieveSolution();
	stack<pair<int, int> > rS();
	int rSC();//Retrieve Solution Cost
	int rTD();//Retrieve Tree Depth
	int rSF();//Retrieve Size Frontier
	int returnNodesExpand();
	UniformCost();
	UniformCost(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g, int cF);
	~UniformCost();
};

#endif
