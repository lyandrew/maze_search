#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include "AStarSearch.h"
//#include <unistd.h>
#include <list>
#include <cmath>
#include <map>
#include <algorithm>

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

float heuristic_cost_estimate(pair<int, int> loc1, pair<int, int> loc2) {
	return abs(loc2.first - loc1.first) + abs(loc2.second - loc1.second);
}

float dist_between(pair<int, int> loc1, pair<int, int> loc2) {
	return sqrt( pow(loc2.first-loc1.first,2) + pow(loc2.second-loc1.second,2));
}
void reconstruct_path(map<node*,node*> came_from, node * current_node) {
        cout << current_node->loc.first <<  "   " << current_node->loc.second << endl;
        int t = 0;
        cout << "SIZE OF MAP: " << came_from.size() << endl;	
	for( map< node*, node* >::iterator it = came_from.begin(); it != came_from.end(); it++) {
        	node * neighbor = it->first;
		t++;
        	if( neighbor->loc == current_node->loc ) {
        		node * value = it->second;
        		cout <<" node2 : " << current_node->loc.first <<  "   " << current_node->loc.second << endl;
        		cout << "node : " << value->loc.first <<  "   " << value->loc.second << endl;
        		//node *p = reconstruct_path(came_from, value);
        		
					
    //    		return (p );
        	}
        	else {
      //  		return current_node;
        	}	
        }
cout << "iterated times: " << t << endl;

}

list<node> getNeighbor(node current, int **maze, node ** nodeList) {

	list<node> neighbor_list;
        int x = current.loc.first;
        int y = current.loc.second;

	// ADD UP
        if( maze[x][y+1] != 0){
        	neighbor_list.push_front(nodeList[x][y+1]);
        	*nodeList[x][y+1].parent = current;
        }
	// ADD LEFT
	if( maze[x-1][y] != 0){
		neighbor_list.push_front(nodeList[x-1][y]);
		*nodeList[x-1][y].parent = current;
        }
	// ADD DOWN
        if( maze[x][y-1] != 0){
        	neighbor_list.push_front(nodeList[x][y-1]);
        	*nodeList[x][y-1].parent = current;
        }
	// ADD RIGHT
	if( maze[x+1][y] != 0){
        	neighbor_list.push_front(nodeList[x+1][y]);
                *nodeList[x+1][y].parent = current;       
        }

	
	//cout << neighbor_list.size() << " SIZE " <<endl;
	return neighbor_list;
}

list<node> AStarSearch::findPathAStar() {
	node ** nodeList = new node*[100];
	for(int i =0; i < 100; ++i)
	        nodeList[i] = new node[100];
	        
	for ( int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	                node obj = node(NULL, make_pair(i,j));
                        obj.parent = new node();
                        nodeList[i][j] = obj;
                }
        }

	list<node> open_list;
	list<node> closed_list;
	map<node*,node*> came_from;
	
	node beginningNode = nodeList[beginning.first][beginning.second];
	beginningNode.g = 0;
	beginningNode.f = beginningNode.g+ heuristic_cost_estimate(goals, beginningNode.loc);
	
	cout << beginningNode.f << endl;
	open_list.push_back(beginningNode);
	while(open_list.size() != 0 ) {
		// find the smallest f score value in the open set
                float lowestf = 999.9;
                node current;
                for( list<node>::iterator it = open_list.begin(); it != open_list.end(); it++){
                        node node_item = *it;
                        if (node_item.f < lowestf) {
                                lowestf = node_item.f;
                                current = node_item;
                        }

                }
                
                if( current.loc == goals ){
                       
                	cout << "FOUND IT" << closed_list.size() << endl;
                	node * last_node = &current;
			reconstruct_path(came_from, last_node);

 
                	return closed_list;
                }
                //remove current from openset
                open_list.remove(current);
                //add current to closedset
                closed_list.push_back(current);
                
                list <node> neighbor_list = getNeighbor(current, maze, nodeList);
		//cout << "GOT TO HERE IT " << neighbor_list.size() <<  endl;
                //for each neighbor in neighbor_node(current)
		for( list<node>::iterator it = neighbor_list.begin(); it != neighbor_list.end(); it++) {
                	node neighbor = *it;
                	
                	float tentative_gscore = current.g + dist_between(current.loc, neighbor.loc);
                	// if neghbor in closedset and tentative gscore >= current.g
                	list<node>::iterator findIter = find(closed_list.begin(), closed_list.end(), neighbor);
                	node found = *findIter;
                	//cout << neighbor.loc.first << "  " << neighbor.loc.second << endl;
                	//cout << found.loc.first << "  " << found.loc.second << endl;
                	if (found.loc == neighbor.loc && tentative_gscore >= current.g)
				continue;
			
			// if neight NOT in openset or tentative score < g_score[current]
			list<node>::iterator findNeighbor = find(open_list.begin(), open_list.end(), neighbor);
			found = *findNeighbor;
			if ( found.loc != neighbor.loc || tentative_gscore < current.g ) {
				node * node1 = &neighbor;
				node * node2 = &current;
				cout << " adding to map " <<  "current " << current.loc.first << " " << current.loc.second << "  neigh " << neighbor.loc.first << "  " << neighbor.loc.second << endl;
				cout << "size of came from : " << came_from.size() << endl;
				came_from.insert( pair<node*, node*>(node1, node2 ) );
				neighbor.g = tentative_gscore;
				neighbor.f = neighbor.g + heuristic_cost_estimate( neighbor.loc, goals);
				if ( found.loc != neighbor.loc )
					open_list.push_back(neighbor);
			}
				
                }	
                
	//cout << "Fasdasdas" << "  "<<open_list.size() <<endl;
	}
	cout << "failure " << endl;
	return closed_list;
}


void AStarSearch::findPathAStar(node * root) {

}

list<node> AStarSearch::test() {


}
AStarSearch::AStarSearch(int **m, int dots, pair<int, int> beginningCoords, pair<int, int> goals, int row, int col) {
	this->maze = m;
	this->totalDots = dots;
	this->beginning = beginningCoords;
	this->goals = goals;
	this->row = row;
	this->col = col;
}
