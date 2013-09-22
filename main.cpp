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
//bigMaze.lay;
//openMaze.lay;
//mediumMaze.lay;
//smallMaze.lay;

using namespace std;

int main(int argc, char **argv) {

	ifstream myReadFile("bigMaze.lay");
	string str;
	int bigMaze[100][100];
	int row = 0;
	while (getline(myReadFile, str)) {
	        int strSize = str.size();
	        if (strSize == 0) break;
	        int column = 0;
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
		if(str.find('.') != -1) numDots++;
		
		cout << str << "  " << numDots << endl;
	}
	
	// Testing if the array works
	for ( int i = 0; i < row; i++) {
	        for (int j = 0; j < row; j++) {
	                cout << bigMaze[i][j];
	        }
	        printf("\n");
	}
	      
}
