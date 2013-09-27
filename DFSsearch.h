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
#include <unistd.h>


//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;


class DFSsearch {
	int **maze;
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm
	bool findPathRecur(pair<int, int> at);

public:
	void findPathDfs();
	DFSsearch();
	DFSsearch(int **maz, int dots, pair<int, int> beg);
	~DFSsearch();
};

DFSsearch::DFSsearch() {
	totalDots = -1;
	beginning = make_pair(-1, -1);
}
DFSsearch::DFSsearch(int **maz, int dots, pair<int, int> beg) {
	maze = maz;
	totalDots = dots;
	beginning = beg;
}
DFSsearch::~DFSsearch() {
	int i = 0;
	while (maze[i] != NULL) {
		delete maze[i];
		i++;
	}
	delete [] maze;
}

<<<<<<< HEAD:DFSsearch.cpp
void DFSsearch::findPathDfs() {
	
}

bool DFSsearch::findPathRecur(pair<int, int> at) {
	int info = maze[at.first][at.second];
	if (info == 0)
		return false;
	else if (info ==

	return false;
}
=======
void DFSsearch::findPathDFS() {

}
>>>>>>> d6c49f496d83a54a7b2a83032e2d4d3066dfa20e:DFSsearch.h
