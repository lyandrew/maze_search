// CS 440 MP1
// @author Will Hempy
// @netid hempy2

#include "GBFsearch.h"

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

int dist(node * lhs, node * rhs) {
	int dist_x = lhs->loc.first - rhs->loc.first;
	int dist_y = lhs->loc.second - rhs->loc.second;
	
	if (dist_x < 0) dist_x = -1*dist_x;
	if (dist_y < 0) dist_y = -1*dist_y;
	return dist_x + dist_y;
}
void GBFsearch::findPathGBF() {
	node * root = new node();
	root->loc = beginning;
	solution.push(beginning);	
	findPathGBF(root);
}

void GBFsearch::findPathGBF(node * root) {
	
	// Copy the maze and initialize
	int tempmaze[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			tempmaze[i][j] = maze[i][j];
		}
		
		
	int j = 0;
	list <node*> gbf;
	
	root->parent = NULL;
	gbf.push_back(root);
	
	node *last = new node();
	node *closest = NULL;
	node *temp = NULL;
	
/**
OPEN = [initial state]
CLOSED = []
while OPEN is not empty
*/

	while (!gbf.empty()){
		maxTreeDepth++;
		int ihateyou = gbf.size();
		maxFrontier = max(maxFrontier, ihateyou);
		
		//  1. Remove the best node from GBF, call it n, add it to CLOSED.
		closest = gbf.front();
		for (list<node*>::iterator it=gbf.begin(); it!=gbf.end(); ++it)
			if (dist(goals[j],closest) > dist(goals[j],*it)) {
				closest = *it;
			}
		
		
		gbf.remove(closest);	
		temp = closest;

		// Set our current position
		int x = temp->loc.first;
		int y = temp->loc.second;
	

		// 2. If n is the goal state, backtrace path to n (through recorded parents) and return path.	
		
		//tempmaze[x][y] = 0;
		// 3. Create n's successors.
		/**
		 * 4. For each successor do:
		 *  a. If it is not in CLOSED: evaluate it, add it to OPEN, and record its parent.
		 *  b. Otherwise: change recorded parent if this new path is better than previous one.
		 */

		// MOVE DOWN
		if (tempmaze[x + 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y] == 3){
				pair<int,int> dot = make_pair(x+1,y);
				last->loc = dot;
				maze[x+1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x + 1][y] = 0;
			gbf.push_back(new node(temp, make_pair(x + 1, y)));
		}
		// MOVE LEFT
		if (tempmaze[x][y - 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y-1] == 3){
				pair<int,int> dot = make_pair(x,y-1);
				last->loc = dot;
				maze[x][y-1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y - 1] = 0;
			gbf.push_back(new node(temp, make_pair(x, y - 1)));
		}
		// MOVE UP
		if (tempmaze[x - 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x-1][y] == 3){
				pair<int,int> dot = make_pair(x-1,y);
				last->loc = dot;
				maze[x-1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x - 1][y] = 0;
			gbf.push_back(new node(temp, make_pair(x - 1, y)));
		}
		
		// MOVE RIGHT
		if (tempmaze[x][y + 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y + 1] == 3){
				pair<int,int> dot = make_pair(x,y + 1);
				last->loc = dot;
				maze[x][y + 1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y + 1] = 0;
			gbf.push_back(new node(temp, make_pair(x, y + 1)));
		}
	}
	
	if (last != NULL) {
		solutionAssemble(last);
		totalDots--;
		if (totalDots > 0)
			findPathGBF(last);
	}
	
	delete temp;
	temp = NULL;
	delete last;
	last = NULL;
	
	while (!gbf.empty()) {
		temp = gbf.back();
		gbf.pop_back();
		delete temp;
		temp = NULL;
	}

}
/**
*  This function is called once a solution is found. 
*  The path taken to the solution is thrown into a stack starting at the end
*  (first out is the root)
*/
void GBFsearch::solutionAssemble(node* at){
	if (at->parent == NULL)
		return;
	solution.push(at->loc);
	solutionAssemble(at->parent);
}
/**
*  @return the solution in the form of a stack.
*  Note: the memory from this function must be freed by the 
*  caller. 
*/
int** GBFsearch::retrieveSolution(){
	
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
/**
*  Blank Constructor
*/
GBFsearch::GBFsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
}
/**int dis(node * lhs, node * rhs) {
	int dist_x = lhs->loc.first - rhs->loc.first;
	int dist_y = lhs->loc.second - rhs->loc.second;
	
	if (dist_x < 0) dist_x = -1*dist_x;
	if (dist_y < 0) dist_y = -1*dist_y;
	return dist_x + dist_y;
}
*  Constructs a BFS searcher from a 2D array (m), total number of dots (dots)
*  and the beginning spot on the maze (beg) in the form of a pair
*/
GBFsearch::GBFsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g) {
	for (int i = 0; i < row ; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = m[i][j];		
		}
	}
	totalDots = dots;
	beginning = beg;
	goals = g;
}
/**
*  Deconstructor
*/
GBFsearch::~GBFsearch() {
	
}

stack<pair<int, int> > GBFsearch::rS() {
	return solution;
}

/**
* Retrieve Solution Cost
* A solution must be found before this is called.
*/
int GBFsearch::rSC() {
	if (solution.size() != 0)
		return solution.size();
	else
		return -1;//If you did not find a solution before you called this or there is no solution
}

/**
* Retrieve Tree Depth
*/
int GBFsearch::rTD() {
	return maxTreeDepth;
}

/**
* Retrieve Size Frontier
*/ 
int GBFsearch::rSF(){
	return maxFrontier;
}

/**
* returns the total number of nodes expanded
*/
int GBFsearch::returnNodesExpand() {
	return totalNodesExpanded;
}

