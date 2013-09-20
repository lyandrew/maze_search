// CS 440 MP1
// @author Will Hempy
// @netid hempy2 

#include <iostream>
#include <fstream>

using namespace std;

int main(){

	ifstream myReadFile;
	myReadFile.open("text.txt");
	char output[100];
	if (myReadFile.is_open()) {
	while (!myReadFile.eof()) {


	myReadFile >> output;
	cout<<output;


	}
}
myReadFile.close();
