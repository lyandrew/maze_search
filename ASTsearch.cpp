// CS 440 MP1
// @author --your name here
// @netid --your netid here

#include "ASTsearch.h"

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;
list<node*> getNeighbors(int maze[100][100], node * current, node ** nodeList) {

	list<node*> neighbor_list;
        int x = current->loc.first;
        int y = current->loc.second;

	// ADD UP
        if( maze[x][y+1] != 0){
        	neighbor_list.push_front(&nodeList[x][y+1]);
        }
	// ADD LEFT
	if( maze[x-1][y] != 0){
		neighbor_list.push_front(&nodeList[x-1][y]);
        }
	// ADD DOWN
        if( maze[x][y-1] != 0){
        	neighbor_list.push_front(&nodeList[x][y-1]);
        }
	// ADD RIGHT
	if( maze[x+1][y] != 0){
        	neighbor_list.push_front(&nodeList[x+1][y]);     
        }

	
	return neighbor_list;
}
int distance(node * lhs, node * rhs) {
	int dist_x = lhs->loc.first - rhs->loc.first;
	int dist_y = lhs->loc.second - rhs->loc.second;
	
	if (dist_x < 0) dist_x = -1*dist_x;
	if (dist_y < 0) dist_y = -1*dist_y;
	return dist_x + dist_y;
}
float heuristic_cost_estimate(node * lhs, node * rhs) {
	return abs(rhs->loc.first - lhs->loc.first) + abs(rhs->loc.second - lhs->loc.second);
}
void ASTsearch::findPathAST() {
	node * root = new node();
	root->loc = beginning;
	solution.push(beginning);
	findPathAST(root);
}

void ASTsearch::findPathAST(node * root) {
	
	// Copy the maze and initialize
	node ** nodeList = new node*[100];
	int tempmaze[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			tempmaze[i][j] = maze[i][j];
		}
	
	
	for(int i =0; i < 100; ++i)
	        nodeList[i] = new node[100];

	for ( int i = 0; i < 100; i++) {
	        for (int j = 0; j < 100; j++) {
                        nodeList[i][j] = node(NULL, make_pair(i,j));
                }
        }
	list <node*> openList;
	list <node*> closedList;
	root->parent = NULL;
	openList.push_front(root);
	node * lowestFNode = NULL;
	node * current = NULL;

	
	while(!openList.empty()){
		maxTreeDepth++;
		int openListSize = openList.size();
		maxFrontier = max(maxFrontier, openListSize);
		float lowestF = 99999.0;
		// find the lowest f node
		for( list<node*>::iterator it = openList.begin(); it != openList.end(); it++){
			lowestFNode = *it;
			if (lowestFNode->f < lowestF) {
				lowestF = lowestFNode->f;
				current = lowestFNode;
			}
		}
		
		//if result has been found.... return the path
		//cout << current->loc.first <<  "   " << current->loc.second << endl;
		if( current->loc == goals[t]->loc ) {
			
			int i = 0;
			node * temp = current;
			while(temp != NULL) {
				i++;
				temp = temp->parent;	
			}

			solutionAssemble(current);
			t++;
			totalDots--;
			if (totalDots > 0)
				findPathAST(current);
			
			totalNodesExpanded = closedList.size();
			return;
		}
		
		openList.remove(current);
		closedList.push_back(current);
		
		list<node *> neighbors = getNeighbors(tempmaze, current, nodeList);

		for( list<node*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
			node * neighbor = *it;
			
			list<node*>::iterator findNeighIter = find(closedList.begin(), closedList.end(), neighbor);
			node * found = *findNeighIter;
			// already searched this node, skip this
			if( neighbor->loc == found->loc )
				continue;
			
			float gval = current->g + 1;
			bool gvalIsBest = false;
			list<node*>::iterator findNeighIter2 = find(openList.begin(), openList.end(), neighbor);
			node * foundOpen = *findNeighIter2;
			
			// first time we arrive at this node
			if( neighbor->loc != foundOpen->loc) {
				gvalIsBest = true;
				neighbor->h = heuristic_cost_estimate(neighbor, goals[t]);
				openList.push_back(neighbor);
			}
			else if(gval < neighbor->g) {
				//we have already seen the node, but last time it had a worse g val
				gvalIsBest = true;
			}
			
			if(gvalIsBest) {
				neighbor->parent = current;
				neighbor->g = gval;
				neighbor->f = neighbor->g + neighbor->h;
			
			}
		}
	}
}
/**
*  This function is called once a solution is found. 
*  The path taken to the solution is thrown into a stack starting at the end
*  (first out is the root)
*/
void ASTsearch::solutionAssemble(node* at){
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
int** ASTsearch::retrieveSolution(){
	
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

stack<pair<int, int> > ASTsearch::rS() {
	return solution;
}
/**
* Retrieve Solution Cost
* A solution must be found before this is called.
*/
int ASTsearch::rSC() {
	if (solution.size() != 0)
		return solution.size();
	else
		return -1;//If you did not find a solution before you called this or there is no solution
}

/**
* Retrieve Tree Depth
*/
int ASTsearch::rTD() {
	return maxTreeDepth;
}

/**
* Retrieve Size Frontier
*/ 
int ASTsearch::rSF(){
	return maxFrontier;
}

/**
* returns the total number of nodes expanded
*/
int ASTsearch::returnNodesExpand() {
	return totalNodesExpanded;
}

/**
*  Blank Constructor
*/
ASTsearch::ASTsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
}
/**
*  Constructs a BFS searcher from a 2D array (m), total number of dots (dots)
*  and the beginning spot on the maze (beg) in the form of a pair
*/
ASTsearch::ASTsearch(int m[100][100], int dots, pair<int, int> beg, int row, int col, vector<node*> g) {
	for (int i = 0; i < row ; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = m[i][j];		
		}
	}
	totalDots = dots;
	beginning = beg;
	goals = g;
	t=0;
}
/**
*  Deconstructor
*/
ASTsearch::~ASTsearch() {
	
}
