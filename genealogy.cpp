#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<ctype.h>
#include<sstream>
#include"graph.h"

using namespace std;

// Parse the tokens and insert them into a string vector
vector< pair <string,int>> parse(string str) {
        istringstream iss(str);
        vector< pair <string,int>> input; // Vector pair to hold the input
        string s;
	string temp;
	int i = 0;
	int num;
	// While loop if Family is first: add string, then int for each loop
	// While loop if Relate is first: add string, then two ints
        while (iss >> quoted(s)) {
		if (i == 0) {
			temp = s;
			i = 1;
		}
		else {
			stringstream degree(s);
			degree >> num;
                	input.push_back(make_pair(temp,num));
			if (temp != "Relate") 
				i = 0;
		}
        }
        return input; // Return the input
}

// main function
int main() {
	graph myGraph; // Graph object
	vector< pair <string,int> > temp; // temp vector pair for input
	string input;
	for (;;) { // continuous for loop
		getline(cin,input); // get one line at time
	        if (feof(stdin)) { // if the end of file is found, exit
			exit(0);
		}
		temp = parse(input); // parse the input
		// If the first word is Family
		if (temp[0].first == "Family")
			myGraph.insertFamily(temp); // Insert the family
		// If the first word if Relate
		if (temp[0].first == "Relate") {
			// If Find returns true
			if (myGraph.Find(temp[0].second,temp[1].second) == 1) 
				myGraph.BFS(temp[0].second,temp[1].second); // Search for the path between to vertices
			
			else { // Else they are not connected
				cout << "Persons " << temp[0].second << " and " << temp[1].second;
				cout << " are not related.\n";
			}
		}
	}
	return 0;
}
