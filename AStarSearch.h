#ifndef ASTARSEARCH_H__
#define ASTARSEARCH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include <list>
using namespace std;

#include "node.h"
class CompareTime {
public:
    bool operator()(node& t1, node& t2)
    {
       if (t1.f > t2.f) return true;
       return false;
    }
};
class AStarSearch {
	int **maze;
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning; //Where we begin
	pair<int,int> goals;
	int row;
	int col;
	stack<pair<int, int> > solution;

public:
	list<node> findPathAStar();
	void findPathAStar(node * root);
	list<node> test();

	AStarSearch(int **m, int dots, pair<int, int> beginningCoords, pair<int, int> goals, int row, int col);

};
#endif
