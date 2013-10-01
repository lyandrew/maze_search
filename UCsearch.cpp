// CS 440 MP1
// @author Will Hempy
// @netid hempy2

#include "UCsearch.h"
#include <cmath>
#include <map>

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

float UniformCost::dist(node * lhs, node * rhs) {
	float x_cost = 0;
	float y_cost = 0;
	float tobe = 0;
	
	
	y_cost = lhs->loc.first - rhs->loc.first;
	
	if (costFunct == 1) {
		tobe = 1/2;
		x_cost = pow(tobe,lhs->loc.second) - pow(tobe, rhs->loc.second);
		y_cost = pow(tobe, max(lhs->loc.second, rhs->loc.second)) * (y_cost);
	}
	else if (costFunct == 2) {
			tobe = 2;
		x_cost = pow(tobe, lhs->loc.first) - pow(tobe, rhs->loc.first);
		y_cost = pow(tobe, min(lhs->loc.second, rhs->loc.second)) * (y_cost);
	}
	else {		x_cost = lhs->loc.second - rhs->loc.second;
	}
	
	if (x_cost < 0) x_cost = -1*x_cost;
	if (y_cost < 0) y_cost = -1*y_cost;
	return x_cost + y_cost;}
void UniformCost::findPathUC() {
	node happy = node();
	node* sad = &happy;
	map<node*, node*> came_from;
	came_from.insert(make_pair(sad, new node()));
	node * root = new node();
	root->loc = beginning;
	solution.push(beginning);	
	findPathUC(root);
}

void UniformCost::findPathUC(node * root) {
	
	// Copy the maze and initialize
	int tempmaze[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			tempmaze[i][j] = maze[i][j];
		}
		
		
	int j = 0;
	list <node*> UC;
	
	root->parent = NULL;
	UC.push_back(root);
	
	node *last = new node();
	node *closest = NULL;
	node *temp = NULL;
	
/**
OPEN = [initial state]
CLOSED = []
while OPEN is not empty
*/

	while (!UC.empty()){
		maxTreeDepth++;
		int ihateyou = UC.size();
		maxFrontier = max(maxFrontier, ihateyou);
		
		//  1. Remove the best node from UC, call it n, add it to CLOSED.
		closest = UC.front();
		for (list<node*>::iterator it=UC.begin(); it!=UC.end(); ++it)
			if (dist(goals[j],closest) > dist(goals[j],*it)) {				closest = *it;			}
		
		
		UC.remove(closest);	
		temp = closest;

		// Set our current position
		int x = temp->loc.first;
		int y = temp->loc.second;
	

		// 2. If n is the goal state, backtrace path to n (through recorded parents) and return path.	
		
		//tempmaze[x][y] = 0;
		// 3. Create n's successors.
		/**		 * 4. For each successor do:		 *  a. If it is not in CLOSED: evaluate it, add it to OPEN, and record its parent.		 *  b. Otherwise: change recorded parent if this new path is better than previous one.		 */

		// MOVE DOWN
		if (tempmaze[x + 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y] == 3){				pair<int,int> dot = make_pair(x+1,y);
				last->loc = dot;
				maze[x+1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x + 1][y] = 0;
			UC.push_back(new node(temp, make_pair(x + 1, y)));
		}
		// MOVE LEFT
		if (tempmaze[x][y - 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y-1] == 3){				pair<int,int> dot = make_pair(x,y-1);
				last->loc = dot;
				maze[x][y-1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y - 1] = 0;
			UC.push_back(new node(temp, make_pair(x, y - 1)));
		}
		// MOVE UP
		if (tempmaze[x - 1][y] != 0){
			totalNodesExpanded++;
			if (tempmaze[x-1][y] == 3){				pair<int,int> dot = make_pair(x-1,y);
				last->loc = dot;
				maze[x-1][y] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x - 1][y] = 0;
			UC.push_back(new node(temp, make_pair(x - 1, y)));
		}
		
		// MOVE RIGHT
		if (tempmaze[x][y + 1] != 0){
			totalNodesExpanded++;
			if (tempmaze[x][y + 1] == 3){				pair<int,int> dot = make_pair(x,y + 1);
				last->loc = dot;
				maze[x][y + 1] = 1;
				last->parent = temp;
				break;
			}
			tempmaze[x][y + 1] = 0;
			UC.push_back(new node(temp, make_pair(x, y + 1)));
		}
	}
	
	if (last != NULL) {
		solutionAssemble(last);
		totalDots--;
		if (totalDots > 0)
			findPathUC(last);
	}
	
	delete temp;
	temp = NULL;
	delete last;
	last = NULL;
	
	while (!UC.empty()) {		temp = UC.back();
		UC.pop_back();
		delete temp;
		temp = NULL;	}

}
/**
*  This function is called once a solution is found. *  The path taken to the solution is thrown into a stack starting at the end
*  (first out is the root)
*/
void UniformCost::solutionAssemble(node* at){
	if (at->parent == NULL)
		return;
	solution.push(at->loc);
	solutionAssemble(at->parent);
}
/**
*  @return the solution in the form of a stack.*  Note: the memory from this function must be freed by the *  caller. 
*/
int** UniformCost::retrieveSolution(){	
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
/**
*  Blank Constructor
*/
UniformCost::UniformCost() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
	costFunct = 0;
}
/**int dis(node * lhs, node * rhs) {	int x_cost = lhs->loc.first - rhs->loc.first;
	int y_cost = lhs->loc.second - rhs->loc.second;
	
	if (x_cost < 0) x_cost = -1*x_cost;
	if (y_cost < 0) y_cost = -1*y_cost;
	return x_cost + y_cost;}
*  Constructs a BFS searcher from a 2D array (m), total number of dots (dots)
*  and the beginning spot on the maze (beg) in the form of a pair
*/
UniformCost::UniformCost(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g, int cF) {
	for (int i = 0; i < row ; i++) {		for (int j = 0; j < col; j++) {			maze[i][j] = m[i][j];				}	}
	totalDots = dots;
	beginning = beg;
	goals = g;
	costFunct = cF;
}
/**
*  Deconstructor
*/
UniformCost::~UniformCost() {
	
}

stack<pair<int, int> > UniformCost::rS() {
	return solution;
}

/**
* Retrieve Solution Cost
* A solution must be found before this is called.
*/
int UniformCost::rSC() {
	if (solution.size() != 0)
		return solution.size();
	else
		return -1;//If you did not find a solution before you called this or there is no solution
}

/**
* Retrieve Tree Depth
*/
int UniformCost::rTD() {
	return maxTreeDepth;
}

/**
* Retrieve Size Frontier
*/ 
int UniformCost::rSF(){
	return maxFrontier;
}

/**
* returns the total number of nodes expanded
*/
int UniformCost::returnNodesExpand() {
	return totalNodesExpanded;
}

