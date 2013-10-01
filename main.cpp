// CS 440 MP1 
// @author Will Hempy
// @netid hempy2 

//#include "unistd.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <list>
#include "AStarSearch.h"


//0 - wall
//1 - blank
//3 - dot
//2 - packman
//bigMaze.lay;
//openMaze.lay;
//mediumMaze.lay;
//smallMaze.lay;

using namespace std;

int main(int argc, char **argv) {

	ifstream myReadFile("bigMaze.lay");
	string str;
	//int bigMaze[100][100];
	int ** bigMaze = new int*[100];
	for(int i =0; i < 100; ++i)
	        bigMaze[i] = new int[100];
	int row = 0;
	int col = 0;
	int numDots = 0;
	pair<int, int> Pacman;
        pair<int, int> firstGoal;
	while (getline(myReadFile, str)) {
	        int strSize = str.size();
	        if (strSize == 0) break;
	        int column = 0;
	        for(int j =0; j < strSize; j++ ) {
	                if (str[j] == '%')
	                        bigMaze[row][j] = 0;
	                else if(str[j] == ' ' )
				bigMaze[row][j] = 1;
			else if( str[j] == '.' ) {
				bigMaze[row][j] = 3;
				firstGoal = make_pair(row, j);
		        }
			else {//Pacman
				bigMaze[row][j] = 2;
				Pacman = make_pair(row, j);
			}
			col = j +1;
	        }       
	        row++;
	        numDots =0;
		if(str.find('.') != -1)
		        numDots++;
		        
		cout << str << "  " << numDots << endl;
	}
	
	AStarSearch AStar(bigMaze, 1, Pacman, firstGoal, row, col);
        list<node> solution_path = AStar.findPathAStar();
        

        for(list<node>::iterator it = solution_path.begin(); it != solution_path.end(); it++){
                node node_item = *it;
                int x = node_item.loc.first;
                int y = node_item.loc.second;
                bigMaze[x][y] = 9;
        }   

	char ** charBigMaze = new char*[100];
	for(int i =0; i < 100; ++i)
	        charBigMaze[i] = new char[100];
	        
	for ( int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
                        if (bigMaze[i][j] == 0)
	                        charBigMaze[i][j] = '%';
	                else if(bigMaze[i][j] == 1)
				charBigMaze[i][j] = ' ';
			else if( bigMaze[i][j] == 3 ) {
				charBigMaze[i][j] = '.';
		        }
			else if( bigMaze[i][j] == 9 ) {
				charBigMaze[i][j] = '*';
		        }
			else {//Pacman
				;
				}

	        }
	        printf("\n");

	}
	charBigMaze[Pacman.first][Pacman.second] = 'P';
	for ( int i = 0; i < row; i++) {
	        for (int j = 0; j < col; j++) {
	                cout << charBigMaze[i][j];
	        }
	        printf("\n");

	}
	
}
