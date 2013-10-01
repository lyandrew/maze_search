// CS 440 MP1
// @author --your name here
// @netid --your netid here

#ifndef ASTSEARCH_H__
#define ASTSEARCH_H__

#include "globe.h"

using namespace std;

class ASTsearch {
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
	int t;
public:
	void findPathAST();
	void findPathAST(node * root);
	int** retrieveSolution();
	stack<pair<int, int> > rS();
	int rSC();//Retrieve Solution Cost
	int rTD();//Retrieve Tree Depth
	int rSF();//Retrieve Size Frontier
	int returnNodesExpand();
	ASTsearch();
	ASTsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g);
	~ASTsearch();
};

#endif
