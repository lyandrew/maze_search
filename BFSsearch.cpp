//CS 440 MP1
// @author William Koehler
// @netid wkoehle2

#include "BFSsearch.h"

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

void BFSsearch::findPathBfs() {
	node * root = new node();
	root->loc = beginning;
	solution.push(beginning);
	findPathBfs(root);
	delete root;
}

/**
*  This function starts by creating a root pointer, adding it to a queue, 
*  and running through the queue, adding and removing, until a dot is 
*  found and then stops going through that queue.
* 
*  At each step:
*  Case 1: 
*  If the next square is a dot (3), save it as the "last" node,
*  then make that square a wall (0), so we can't revisit it.
*  Also, change the dot to a space (1) in the original maze so we don't
*  eat it again.
* 
*  Case 2:
*  The next square is not a dot. Push the next square onto the queue, and
*  set the square to a wall (0) so we don't go over it again.
*/
void BFSsearch::findPathBfs(node * root) {

	// Copy the maze and initialize
	int tempmaze[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			tempmaze[i][j] = maze[i][j];
		}

	// Data structure and root node added.
	std::queue<node*> bfs;
	bfs.push(root);
	root->parent = NULL;
	// is this used?
	node *last = new node();
	node *temp = NULL;
	node *newnode = NULL;

	while (!bfs.empty()){
		maxTreeDepth++;
		int ihateyou = bfs.size();
		maxFrontier = max(maxFrontier, ihateyou);
		// Take the first element from the queue
		temp = bfs.front();
		bfs.pop();
		
		// Set our current position
		int x = temp->loc.first;
		int y = temp->loc.second;
		
		
		// MOVE UP
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
			bfs.push(new node(temp, make_pair(x, y - 1)));
		}
		// MOVE LEFT
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
			bfs.push(new node(temp, make_pair(x - 1, y)));
		}
		
		// MOVE DOWN
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
			bfs.push(new node(temp, make_pair(x, y + 1)));
		}
		
		// MOVE RIGHT
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
			bfs.push(new node(temp, make_pair(x + 1, y)));
		}
	}
	if (last != NULL) {
		solutionAssemble(last);
		totalDots--;
		if (totalDots > 0)
			findPathBfs(last);
	}
	
	delete temp;
	temp = NULL;
	delete last;
	last = NULL;
	while (!bfs.empty()) {
		temp = bfs.front();
		bfs.pop();
		delete temp;
		temp = NULL;
	}
}
/**
*  This function is called once a solution is found. 
*  The path taken to the solution is thrown into a stack starting at the end
*  (first out is the root)
*/
void BFSsearch::solutionAssemble(node* at){
	if (at->parent == NULL)
		return;
	solution.push(at->loc);
	solutionAssemble(at->parent);
}

stack<pair<int, int> > BFSsearch::rS() {
	return solution;
}

/**
*  @return the solution in the form of a stack.
*  Note: the memory from this function must be freed by the 
*  caller. 
*/
/*
int** BFSsearch::retrieveSolution(){
	
   int** az = new int*[100];
   for (int i = 0; i < 100; i++) {
   	   	az[i] = new int[100];
   	 for (int j = 0; j < 100; j++) {
     	az[i][j] = 0;	
   	 }
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
*  Blank Constructor
*/
BFSsearch::BFSsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
	totalNodesExpanded = -1;
	maxTreeDepth = -1;
	solutionCost = -1;
	maxFrontier = -1;
}
/**
*  Constructs a BFS searcher from a 2D array (m), total number of dots (dots)
*  and the beginning spot on the maze (beg) in the form of a pair
*/
BFSsearch::BFSsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col) {
	for (int i = 0; i < row ; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = m[i][j];		
		}
	}
	totalDots = dots;
	beginning = beg;
	totalNodesExpanded = 0;
	maxTreeDepth = 0;
	solutionCost = 0;
	maxFrontier = 0;
	extraHeads = dots - 1;
}
/**
*  Deconstructor
*/
BFSsearch::~BFSsearch() {}

/**
* Retrieve Solution Cost
* A solution must be found before this is called.
*/
int BFSsearch::rSC() {
	if (solution.size() != 0)
		return solution.size();
	else
		return -1;//If you did not find a solution before you called this or there is no solution
}

/**
* Retrieve Tree Depth
*/
int BFSsearch::rTD() {
	return maxTreeDepth;
}

/**
* Retrieve Size Frontier
*/ 
int BFSsearch::rSF(){
	return maxFrontier;
}

/**
* returns the total number of nodes expanded
*/
int BFSsearch::returnNodesExpand() {
	return totalNodesExpanded;
}
