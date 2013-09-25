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


class DFSsearch {
	int **maze;
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	stack<pair<int, int> > solution; //Final trail we will follow from this algorithm

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
	for (int i = 0; i < maze[].size; i++) {
		delete maze[i];
	}
	delete [] maze;
}

void DFSsearch::findPathBFS() {

}