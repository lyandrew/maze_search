// CS 440 project
// @author William Koehler
// @netid wkoehle2


#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;



class BFSDFS_search{
	int * map[];
	int totalDots; //total number of points we have to capture
	pair<int,int> beginning (1, 1);
	stack<pair<int, int> > solution;

public:
	void BFS_solve();
	bool BFS_recur(queue search);
	void DFS_solve();
	bool DFS_recur(stack search);
}
void BFSDFS_search::BFSsolve() {
	std::queue<(pair<int, int>)> bfs;
	bfs.push(beginning);
	while (solution.size() > 0)
		solution.pop();
	solution.push(beginning);

	map[beginning.first][beginning.second] == 0;
	while(bfs.size() > 0) {
		pair<int, int> cn = bfs.front();
		bfs.pop();

		if (map[cn.first][cn.second] == 3) {

		}

		int up = map[cn.first][cn.second - 1];
		int down = map[cn.first][cn.second + 1];
		int left = map[cn.first - 1][cn.second];
		int right = map[cn.first + 1][cn.second];
		
		if (up % 2 == 1) {
			pair<int, int> temp (cn.first, cn.seocnd - 1];
			if (up == 3)
		}
	}
}
bool BFSDFS_search::DFS_recur(


void BFSDFS_search::DFSsolve() {
	//std::stack<pair<int, int> > dfs;
	//dfs.push(beginning);  //initialize the stack
	while (solution.size() > 0) //Makes sure there isn't already a solution in the list
		solution.pop();
	bool temp = BFS_recur(beginning); //if temp is false, there is no solution, do nothing.
	

}
/** This function immitates a stack, adding on to a stack in directions up, left, down, right, in that order
 * @param: takes in a node to be evaluated and 
 * @return: returns a boolean value if a solution is found.
 */
bool BFSDFS_search::BFS_recur(pair<int, int> cn){
	//pair<int, int> cn = search.front(); //Current Node
	//search.pop();
	int thisVal = map[cn.first][cn.second];
	if (thisVal == 0)
		return false;
	if (thisVal == 3) { //if this is the final node
		solution.push(cn);
		return true;
	}
	pair<int, int> up (cn.first, cn.second - 1);
	pair<int, int> down (cn.first, cn.second + 1);
	pair<int, int> left (cn.first - 1, cn.second);
	pair<int, int> right (cn.first + 1, cn.second);

	if (thisVal == 1) { //if this is a open space
		//search.push(up);
		bool temp =  BFS_recur(up);
		if (temp == true) {
			solution.push(cn);
			return true;
		}
		temp = BFS_recur(left);
		if (temp == true) {
			solution.push(cn);
			return true;
		}
		temp = BFS_recur(down);
		if (temp == true) {
			solution.push(cn);
			return true;
		}
		temp = BFS_recur(right);
		if (temp == true) {
			solution.push(cn);
			return true;
		}
	}
	map[cn.first][cn.second] == 0;
	return false;
}

/**
int main(int argc, char **argv) {
	std::stack<(pair<int, int>)> dfs;
	
	std::queue<(pair<int, int>)> bfs;
	
	struct a = dfs or bfs;
	
	while(a.size > 0) {
	pair cn = a.front();
	a.pop();
	
	int up = map[cn.first][cn.second - 1];
	int down = map[cn.first][cn.second + 1];
	int left = map[cn.first - ][cn.second];
	int right = map[cn.first + 1][cn.second];
	if (up % 2 == 1) {
		pair<int, int> temp (cn.first, cn.second - 1);
		if (up == 1) {
			a.add(temp);
			map[cn.first][cn.second - 1] = 5;
		}
		if (up == 3) {
			totaldots--;
			if (totaldots == 0)
				find path;
			else {
				add checkpoint;
				a.add(temp);
			}
		}
	}
	
	if	(down % 2 == 1) {
		pair<int, int> temp (cn.first, cn.second + 1);
		if (down == 1) {
			a.add(temp);
			map[cn.first][cn.second + 1] = 5;
		}
		if (down == 3) {
			map[cn.first][cn.second + 1] = 10;
			totaldots--;
			if (totaldots == 0)
				find path;
			else {
				add checkpoint;
				a.add(temp);
			}
		}
	}
	
	if (left % 2 == 1) {
		pair<int, int> temp (cn.first -1, cn.second);
		if (left == 1) {
			a.add(temp);
			map[cn.first -1][cn.second] = 5;
		}
		if (left == 3) {
			map[cn.first - 1][cn.second] = 10;
			totaldots--;
			if (totaldots == 0)
				find path;
			else {
				add checkpoint;
				a.add(temp);
			}
		}
	}
	
	if (right % 2 == 1) {
		pair<int, int> temp (cn.first, cn.second - 1);
		if (right == 1) {
			a.add(temp);
			map[cn.first + 1][cn.second] = 5;
		}
		if (right == 3) {
			map[cn.first + 1][cn.second] = 10;
			totaldots--;
			if (totaldots == 0)
				find path;
			else {
				add checkpoint;
				a.add(temp);
			}
		}
		}
	}
}
*/