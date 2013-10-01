//CS 440 MP1
// @author William Koehler
// @netid wkoehle2

#include "DFSsearch.h"

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

DFSsearch::DFSsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
	totalNodesExpanded = 0;
	maxTreeDepth = 0;
	solutionCost = 0;
	maxFrontier = 0;
	extraHeads = 0;
}

DFSsearch::DFSsearch(int maz[100][100], int dots, pair<int, int> beg, int row, int col) {
	for (int i = 0; i <row; i++)
		for (int j = 0; j < col; j++) {
			maze[i][j] = maz[i][j];
			tempmaze[i][j] = maz[i][j];
		}
	totalDots = dots;
	beginning = beg;
	totalNodesExpanded = 0;
	maxTreeDepth = 0;
	solutionCost = 0;
	maxFrontier = 1;
	extraHeads = dots - 1;
}

DFSsearch::~DFSsearch() {
	/*
	int i = 0;
	while (maze[i] != NULL) {
		delete maze[i];
		maze[i]
		i++;
	}
	delete [] maze;
	*/
}

void DFSsearch::findPathDfs() {
	node * root = new node();
	root->loc = beginning;
	solution.push(beginning);
	findPathDfs(root);
	delete root;
}

void DFSsearch::findPathDfs(node* root) {
	copyMaze();
	stack<node*> dfs;
	dfs.push(root);
	root->parent = NULL;
	
	node *last = new node();
	node *temp = NULL;
	
	while (!dfs.empty()){
		maxTreeDepth++;
		int ihateyou = dfs.size();
		maxFrontier = max(maxFrontier, ihateyou);
		// Take the first element from the queue
		temp = dfs.top();
		dfs.pop();
		// Set our current position
		int x = temp->loc.first;
		int y = temp->loc.second;
		
		// MOVE UP
		if (tempmaze[x - 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x - 1][y] == 3){
				last->loc = make_pair(x - 1, y);
				tempmaze[x - 1][y] = 0;
				maze[x - 1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x - 1][y] = 0;
			dfs.push(new node(temp, make_pair(x - 1, y)));
		}
		
		// MOVE LEFT
		if (tempmaze[x][y - 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y - 1] == 3){
				last->loc = make_pair(x, y - 1);
				tempmaze[x][y - 1] = 0;
				maze[x][y - 1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y - 1] = 0;
			dfs.push(new node(temp, make_pair(x, y - 1)));
		}
		
		// MOVE DOWN
		if (tempmaze[x + 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x + 1][y] == 3){
				last->loc = make_pair(x + 1, y);
				tempmaze[x + 1][y] = 0;
				maze[x + 1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x + 1][y] = 0;
			dfs.push(new node(temp, make_pair(x + 1, y)));
		}
		
		// MOVE RIGHT
		if (tempmaze[x][y + 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y + 1] == 3){
				last->loc = make_pair(x, y + 1);
				tempmaze[x][y + 1] = 0;
				maze[x][y + 1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y + 1] = 0;
			dfs.push(new node(temp, make_pair(x, y + 1)));
		}
	}
	if (last != NULL) {
		solutionAssemble(last);
		totalDots--;
		if (totalDots > 0)
			findPathDfs(last);
	}
	delete temp;
	temp = NULL;
	delete last;
	last = NULL;

	/*
	int info = tempmaze[at.first][at.second];
	d--;
	if (info == 0)
		return make_pair(false, d);
	totalNodesExpanded++;
	
	if(tempmaze[at.first][at.second - 1] != 0)
		d++;
	if(tempmaze[at.first - 1][at.second] != 0)
		d++;
	if(tempmaze[at.first][at.second + 1] != 0)
		d++;
	if(tempmaze[at.first + 1][at.second] != 0)
		d++;
	maxFrontier = max(d, maxFrontier);
	if (info == 3) {
		solution.push(at);
		
		maze[at.first][at.second] = 1;
		beginning = at;
		totalDots--;
		return make_pair(true, d);
	}
	
	tempmaze[at.first][at.second] = 0;
	if (findPathRecur(make_pair(at.first, at.second - 1), d).first == true) {
		solution.push(at);
		return make_pair(true, d);
	}
	d--;
	if (findPathRecur(make_pair(at.first - 1, at.second), d).first == true) {
		solution.push(at);
		return make_pair(true, d);
	}
	d--;
	if (findPathRecur(make_pair(at.first, at.second + 1), d).first == true) {
		solution.push(at);
		return make_pair(true, d);
	}
	d--;
	if (findPathRecur(make_pair(at.first + 1, at.second), d).first == true) {
		solution.push(at);
		return make_pair(true, d);
	}
	d--;
	return make_pair(false, d);
	*/
}
void DFSsearch::solutionAssemble(node* at){
	if (at->parent == NULL)
		return;
	solution.push(at->loc);
	solutionAssemble(at->parent);
}

void DFSsearch::copyMaze() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			tempmaze[i][j] = maze[i][j];
}


stack<pair<int, int> > DFSsearch::rS() {
	return solution;
}
/*
int** DFSsearch::retrieveSolution(){	
   int** az = new int*[100];
   for (int i = 0; i < 100; i++) {   	   	az[i] = new int[100];   	 for (int j = 0; j < 100; j++) {
     	az[i][j] = 0;	   	 }
   }
   pair<int, int> temp;
   while (solution.size() > 0) {
           temp = solution.top();
           solution.pop();
           az[temp.first][temp.second] = 1;
   }
   return az;
}
*/

/**
* Retrieve Solution Cost
* A solution must be found before this is called.
*/
int DFSsearch::rSC() {
	if (solution.size() != 0)
		return solution.size();
	else
		return -1;//If you did not find a solution before you called this or there is no solution
}

/**
* Retrieve Tree Depth
*/
int DFSsearch::rTD() {
	return maxTreeDepth;
}

/**
* Retrieve Size Frontier
*/ 
int DFSsearch::rSF(){
	return maxFrontier;
}

/**
* returns the total number of nodes expanded
*/
int DFSsearch::returnNodesExpand() {
	return totalNodesExpanded;
}

