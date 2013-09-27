//CS 440 MP1
// @author William Koehler
// @netid wkoehle2


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <queue>
//#include <unistd.h>


//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;
struct node {
	node* parent;
	pair<int, int> loc;
	node::node() {
		parent = NULL;
		loc = make_pair(-1, -1);
	}
	node::node(node* p, pair<int, int> l){
		parent = p;
		loc = l;
	}
};
class BFSsearch {
	int maze[100][100];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	void solutionAssemble(node* at);
public:
	void findPathBFS();
	void findPathBfs(node * root);
	int ** retriveSolution();
	BFSsearch();
	BFSsearch(int m[100][100], int dots, pair<int, int> beg);
	~BFSsearch();
};

void BFSsearch::findPathBFS() {
	node * root = new node();
	root-> parent = NULL;
	root->loc = beginning;
	solution.push(beginning);
	findPathBfs(root);
	delete root;
}

/**
*  This function starts by creating a root pointer, adding it to a queue, and running through the queue, adding and removing,
*  until a dot is found and then stops going through that queue.
*/
void BFSsearch::findPathBfs(node * root) {
	root->parent = NULL;
	//root->loc = beginning;
	std::queue<node*> bfs;
	bfs.push(root);
	node *last = new node();

	while (bfs.size() > 0){
		node *temp = new node();
		temp = bfs.front();
		pair<int, int> ptemp;
		bfs.pop();
		
		int x = temp->loc.first;
		int y = temp->loc.second;
		node * newnode = new node();
		if (maze[x - 1][y] != 0){
			if (maze[x - 1][y] == 3){
				last->loc = make_pair(x - 1, y);
				maze[x - 1][y] = 0;
				last->parent = temp;
				solutionAssemble(last);
				break;
			}
			maze[x - 1][y] = 0;
			bfs.push(new node(temp, make_pair(x - 1, y)));
			
		}
		if (maze[x][y - 1] != 0){
			if (maze[x][y - 1] == 3){
				last->loc = make_pair(x, y - 1);
				maze[x][y - 1] = 0;
				last->parent = temp;
				solutionAssemble(last);
				break;
			}
			maze[x][y - 1] = 0;
			bfs.push(new node(temp, make_pair(x, y - 1)));
		}
		if (maze[x + 1][y] != 0){
			if (maze[x + 1][y] == 3){
				last->loc = make_pair(x + 1, y);
				maze[x + 1][y] = 0;
				last->parent = temp;
				solutionAssemble(last);
				break;
			}
			maze[x + 1][y] = 0;
			bfs.push(new node(temp, make_pair(x + 1, y)));
		}
		if (maze[x][y + 1] != 0){
			if (maze[x][y + 1] == 3){
				last->loc = make_pair(x, y + 1);
				maze[x][y + 1] = 0;
				last->parent = temp;
				solutionAssemble(last);
				break;
			}
			maze[x][y + 1] = 0;
				bfs.push(new node(temp, make_pair(x, y + 1)));
		}
		delete temp;
	}
	if (last != NULL) {
		solutionAssemble(last);
		totalDots--;
		if (totalDots > 0)
			findPathBfs(last);
	}
	delete last;
}
/**
*  This function is called once a solution is found. The path taken to the solution is thrown into a stack starting at the end
*  (first out is the root)
*/
void BFSsearch::solutionAssemble(node* at){
	if (at->parent == NULL)
		return;
	solution.push(at->loc);
	solutionAssemble(at->parent);
	delete at;
}
/**
*  returns the solution in the form of a stack.
*/
int ** BFSsearch::retriveSolution(){
	int[100][100] az;
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
BFSsearch::BFSsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
}
/**
*  Constructs a BFS searcher from a 2D array (m), total number of dots (dots)
*  and the beginning spot on the maze (beg) in the form of a pair
*/
BFSsearch::BFSsearch(int m[100][100], int dots, pair<int, int> beg) {
	for (int i = 0; i <100; i++)
		for (int j = 0; j < 100; j++)
			maze[i][j] = m[i][j];
	totalDots = dots;
	beginning = beg;
}
/**
*  Deconstructor
*/
BFSsearch::~BFSsearch() {
	
}
