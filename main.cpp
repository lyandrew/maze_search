// CS 440 MP1 
// @author Will Hempy
// @netid hempy2 

//0 - wall
//1 - blank
//3 - dot
//2 - packman
//bigMaze.lay;
//openMaze.lay;
//mediumMaze.lay;
//smallMaze.lay;
using namespace std;

#include "BFSsearch.h"
#include "DFSsearch.h"
#include "GBFsearch.h"
#include "ASTsearch.h"
#include "UCsearch.h"

int ** solution;

void retrieveSolution(stack<pair<int, int> > s) {
	solution = new int*[100];
	for (int i = 0; i < 100; i++) {
   	   	solution[i] = new int[100];
   	 for (int j = 0; j < 100; j++) {
     	solution[i][j] = 0;	
   	 }
   }
   pair<int, int> temp;
   while (s.size() > 0) {
           temp = s.top();
           s.pop();
           solution[temp.first][temp.second] = 1;
   }
}

int main(int argc, char **argv) {
	
	ifstream myReadFile(argv[2]);
	
	if (myReadFile.is_open()) {
		
		string str;
		int row = 0;
		int col = 0;
		int numDots = 0;
		pair<int, int> Pacman;
		int bigMaze[100][100];
		
		vector<node*> goals;
		
		cout << "Maze file: " << endl;
		while (getline(myReadFile, str)) {
			
	    	col = str.size();
			cout << str << endl;
			
		    for(int j =0; j < col; j++ ) {
		    	switch (str[j]) {
		    		case ' ':
		    			bigMaze[row][j] = 1;
		    		break;
		    		case 'P':
		    			bigMaze[row][j] = 2;
		    			Pacman = make_pair(row,j);
		    		break;
		    		case '.':
		    			bigMaze[row][j] = 3;
		    			numDots++;
		    			goals.push_back(new node(NULL,make_pair(row,j)));
		    		break;
		    		default:
		    			bigMaze[row][j] = 0;
		    		break;
		    	}
		    }       
		    row++;
		}
		
		string blargh(argv[1]);
		
		if (blargh.find("dfs") != string::npos) {
			DFSsearch my_dfs(bigMaze,numDots, Pacman,row,col);
			my_dfs.findPathDfs();
			retrieveSolution(my_dfs.rS());	
			
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (solution[i][j] == 1 && bigMaze[i][j] != 2)
						bigMaze[i][j] = 3;
				}
				delete [] solution[i];
				solution[i] = NULL;
			}
			delete [] solution;
			solution = NULL;

			for ( int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					switch(bigMaze[i][j]) {
						case 1:
							cout << ' ';
						break;
						case 2:
							cout << 'P';
						break;
						case 3:
							cout << '.';
						break;
						case 0:
							cout << '%';
						break;
						default:
						break;
					}
				}
				cout << endl;
			}
			
			cout << "Solution Cost: " << my_dfs.rSC() << endl;
			cout << "Max Tree Depth: " << my_dfs.rTD() << endl;
			cout << "Max Frontier Size: " << my_dfs.rSF() << endl;
			cout << "Nodes Expanded: " << my_dfs.returnNodesExpand() << endl;			
		}
		else if (blargh.find("bfs") != string::npos) {
			BFSsearch my_bfs(bigMaze,numDots, Pacman,row,col);
			my_bfs.findPathBfs();
			retrieveSolution(my_bfs.rS());	

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (solution[i][j] == 1 && bigMaze[i][j] != 2)
						bigMaze[i][j] = 3;
				}
				delete [] solution[i];
				solution[i] = NULL;
			}
			delete [] solution;
			solution = NULL;

			for ( int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					switch(bigMaze[i][j]) {
						case 1:
							cout << ' ';
						break;
						case 2:
							cout << 'P';
						break;
						case 3:
							cout << '.';
						break;
						case 0:
							cout << '%';
						break;
						default:
						break;
					}
				}
				cout << endl;
			}
			
			cout << "Solution Cost: " << my_bfs.rSC() << endl;
			cout << "Max Tree Depth: " << my_bfs.rTD() << endl;
			cout << "Max Frontier Size: " << my_bfs.rSF() << endl;
			cout << "Nodes Expanded: " << my_bfs.returnNodesExpand() << endl;			
		}
		else if (blargh.find("gbf") != string::npos) {
			GBFsearch my_gbf(bigMaze,numDots,Pacman,row,col,goals);
			my_gbf.findPathGBF();
			retrieveSolution(my_gbf.rS());	

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (solution[i][j] == 1 && bigMaze[i][j] != 2)
						bigMaze[i][j] = 3;
				}
				delete [] solution[i];
				solution[i] = NULL;
			}
			delete [] solution;
			solution = NULL;
			
			for ( int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					switch(bigMaze[i][j]) {
						case 1:
							cout << ' ';
						break;
						case 2:
							cout << 'P';
						break;
						case 3:
							cout << '.';
						break;
						case 0:
							cout << '%';
						break;
						default:
						break;
					}
				}
				cout << endl;
			}
			
			cout << "Solution Cost: " << my_gbf.rSC() << endl;
			cout << "Max Tree Depth: " << my_gbf.rTD() << endl;
			cout << "Max Frontier Size: " << my_gbf.rSF() << endl;
			cout << "Nodes Expanded: " << my_gbf.returnNodesExpand() << endl;		
		}
		else if (blargh.find("ucs") != string::npos){
			
			string input = "";

 			// How to get a string/sentence with spaces
			cout << "Please enter a valid cost function (0,1 or 2):\n>>";
			getline(cin, input);
			cout << "You entered: " << input << endl;
			
			int value = atoi(input.c_str());
			
			UniformCost my_ucs(bigMaze,numDots,Pacman,row,col,goals,value);
			my_ucs.findPathUC();
			retrieveSolution(my_ucs.rS());	

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (solution[i][j] == 1 && bigMaze[i][j] != 2)
						bigMaze[i][j] = 3;
				}
				delete [] solution[i];
				solution[i] = NULL;
			}
			delete [] solution;
			solution = NULL;
			
			for ( int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					switch(bigMaze[i][j]) {
						case 1:
							cout << ' ';
						break;
						case 2:
							cout << 'P';
						break;
						case 3:
							cout << '.';
						break;
						case 0:
							cout << '%';
						break;
						default:
						break;
					}
				}
				cout << endl;
			}
			
			cout << "Solution Cost: " << my_ucs.rSC() << endl;
			cout << "Max Tree Depth: " << my_ucs.rTD() << endl;
			cout << "Max Frontier Size: " << my_ucs.rSF() << endl;
			cout << "Nodes Expanded: " << my_ucs.returnNodesExpand() << endl;		
		}
		else if (blargh.find("ast") != string::npos) {
			ASTsearch my_ast(bigMaze,numDots,Pacman,row,col,goals);
			my_ast.findPathAST();
			retrieveSolution(my_ast.rS());	

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (solution[i][j] == 1 && bigMaze[i][j] != 2)
						bigMaze[i][j] = 3;
				}
				delete [] solution[i];
				solution[i] = NULL;
			}
			delete [] solution;
			solution = NULL;
			
			for ( int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					switch(bigMaze[i][j]) {
						case 1:
							cout << ' ';
						break;
						case 2:
							cout << 'P';
						break;
						case 3:
							cout << '.';
						break;
						case 0:
							cout << '%';
						break;
						default:
						break;
					}
				}
				cout << endl;
			}
			
			cout << "Solution Cost: " << my_ast.rSC() << endl;
			cout << "Max Tree Depth: " << my_ast.rTD() << endl;
			cout << "Max Frontier Size: " << my_ast.rSF() << endl;
			cout << "Nodes Expanded: " << my_ast.returnNodesExpand() << endl;
		}
		else {
			printf("Incorrect input. Choose 'bfs','dfs','gbf,'ucs',or 'ast'\n");
			cout << argv[1] << endl;
			return 0;	
		}
	
	myReadFile.close();
	}
	else {
		printf("ERROR:  Failed to open maze file.\n");
		printf("\tPlease input file as first argument:\n");
		printf("\t i.e. './main bigMaze.lay'\n");
	}
}
