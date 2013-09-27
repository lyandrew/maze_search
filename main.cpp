// CS 440 MP1 
// @author Will Hempy
// @netid hempy2 

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "DFSBFS.h"
#include "DFSsearch.h"
#include "BFSsearch.h"

//0 - wall
//1 - blank
//3 - dot
//2 - packman
//bigMaze.lay;
//openMaze.lay;
//mediumMaze.lay;
//smallMaze.lay;

using namespace std;

/** * A function that will print the given maze to  * the terminal window. *  * @arg1 a pointer to the 2D maze array * @arg2 the length of the maze * @arg3 the height of the maze */
void print_maze(int *** maze, int row, int column){	int ** bigMaze = *maze;
	
	// Testing if the array works
	for ( int i = 0; i < row; i++) {
	        for (int j = 0; j < column; j++) {
	                cout << bigMaze[i][j];
	        }
	        printf("\n");
	}}
int main(int argc, char **argv) {

	// Read the input arguments to get the filename:	if (argv[1] == NULL) {		printf("FAILED: Please input maze file as first argument.\n");
		return 0;	}
	ifstream myReadFile(argv[1]);
	string str;
	int bigMaze[100][100];
	int row = 0;
	while (getline(myReadFile, str)) {
	        int strSize = str.size();
	        if (strSize == 0) break;

	        for(int j =0; j < strSize; j++ ) {
	                if (str[j] == '%')
	                        bigMaze[row][j] = 0;
	                else if(str[j] == ' ' )
				bigMaze[row][j] = 1;
			else if( str[j] == '.' )
				bigMaze[row][j] = 3;
			else //Pacman
				bigMaze[row][j] = 2;
	        }       
	        row++;
	        int numDots = 0;
		if(str.find('.') != string::npos) numDots++;
	}
	      
}
