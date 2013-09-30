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


//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;


void AStarSearch::findPathAStar() {

}

void AStarSearch::findPathAStar(node * root) {

}

list<node> AStarSearch::test() {
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
        
        open_list.push_front(nodeList[beginning.first][beginning.second]);
        node currNode = nodeList[beginning.first][beginning.second];
        
        //set the begining's parent and f to 0.0
        currNode.parent = NULL;
        currNode.f = 0.0;
        pair<int, int> currentCoord = beginning; 

        while(open_list.size() != 0) {
                // find the node with the least f
                node q;
                float lowestf = 999.9;
                for( list<node>::iterator it = open_list.begin(); it != open_list.end(); it++){
                        node node_item = *it;
                        if (node_item.f < lowestf) {
                                lowestf = node_item.f;
                                q = node_item;
                        }

                }
                //pop q off the open list
                open_list.remove(q);
                cout << "x" << q.loc.first << " y" << q.loc.second << endl;
                //generate q's 4 successors and set their parents to q
                list<node> temp_list;
                int x = q.loc.first;
                int y = q.loc.second;
                //add successor to a temp list (only if it is in boundry)
                if( x-1 > -1 ) //check boundry
                        if( maze[x-1][y] != 0){
                                temp_list.push_front(nodeList[x-1][y]);
                                *nodeList[x-1][y].parent = q;
                        }
                if( x+1 < row )
                        if( maze[x+1][y] != 0){
                                temp_list.push_front(nodeList[x+1][y]);
                                *nodeList[x+1][y].parent = q;       
                         }
                if( y-1 > -1 )
                        if( maze[x][y-1] != 0){
                                 temp_list.push_front(nodeList[x][y-1]);
                                 *nodeList[x][y-1].parent = q;
                        }
                if( y+1 < col )
                        if( maze[x][y+1] != 0){
                                temp_list.push_front(nodeList[x][y+1]);
                                *nodeList[x][y+1].parent = q;
                        }
                
                // for each successor...
                for( list<node>::iterator it = temp_list.begin(); it != temp_list.end(); it++){
                        node successor_node = *it;
                        
                        //if coord is in goal
                        if(successor_node.loc == goals) { 
                        
                                for( list<node>::iterator it = closed_list.begin(); it != closed_list.end(); it++){
                                        node node_item = *it;
                                         //cout << "x: " << node_item.loc.first << "  y: "<< node_item.loc.second << endl;
                                }
                                 node temp = successor_node;  
              

                                closed_list.push_front(q);
                                return closed_list;
                        }
                        
                        //update g h f value
                        successor_node.g = q.g + abs(successor_node.loc.first-q.loc.first) + abs(successor_node.loc.second-q.loc.second);
                        successor_node.h = abs(goals.first-successor_node.loc.first) + abs(goals.second-successor_node.loc.second);
                        successor_node.f = successor_node.g + successor_node.h;
                        
                        bool canSkip = false;
                        // if a node with the same position as successor is in the open list which has a lower f than successor, skip succ
                        for( list<node>::iterator it = open_list.begin(); it != open_list.end(); it++){
                                node node_item = *it;
                                
                                if(node_item.loc == successor_node.loc)
                                        if (node_item.f < successor_node.f) {
                                                canSkip = true;
                                        }
                        }                        
                        // if a node with the same posistion as successor is in the closed list which has a lower f than successor, skip successor
                        for( list<node>::iterator it = closed_list.begin(); it != closed_list.end(); it++){
                                node node_item = *it;
                                
                                if(node_item.loc == successor_node.loc)
                                        if (node_item.f < successor_node.f) {
                                                canSkip = true;
                                        }
                        }                         
                        // otherwise add node to the open list
                        if( canSkip == false )
                                open_list.push_front(successor_node);
                }

                closed_list.push_front(q);
        }

}
AStarSearch::AStarSearch(int **m, int dots, pair<int, int> beginningCoords, pair<int, int> goals, int row, int col) {
	this->maze = m;
	this->totalDots = dots;
	this->beginning = beginningCoords;
	this->goals = goals;
	this->row = row;
	this->col = col;
}
