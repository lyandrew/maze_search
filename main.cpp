// CS 440 MP1 
// @author Will Hempy
// @netid hempy2 

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

//0 - wall
//1 - blank
//3 - dot
//2 - packman
using namespace std;

int main(int argc, char **argv) {
//	string bigMazeString = "bigMaze.lay";
//	string openMazeString = "openMaze.lay";
//	string mediumMazeString = "mediumMaze.lay";
//	string smallMazeString = "smallMaze.lay";

	ifstream myReadFile("bigMaze.lay");
	string str;
	int bigMaze[10000]; // arbitrary number of character in the maze file
	int row = 0;
	while( getline(myReadFile, str) ) {
		int strSize = str.size();
		if(strSize == 0 )
			break;		
		int j=0;		
		for(j = 0; j < strSize; j++ ) {
			if( str[j] == '%' )
				bigMaze[str.size()*row + j] = 0;
			else if(str[j] == ' ' )
				bigMaze[str.size()*row + j] = 1;
			else if( str[j] == '.' )
				bigMaze[str.size()*row + j] = 3;
			else //P
				bigMaze[str.size()*row + j] = 2;
		}
		row++;
		int numDots = 0;
		if(str.find('.') != -1) numDots++;
	}
	
	//test to see if the array works
	// row is used her as the width
	for( int i=0 ; i < row; i++ ) {
		for( int j = 0; j < row; j++) {
			cout << bigMaze[(row*i)+j];
		}
		printf("\n");
	}

}

