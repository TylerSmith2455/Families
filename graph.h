#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

// MAX people or families, 101 was used so index is correct
const int MAXP = 101;

// directed bipartite graph class
class graph {
	public:
		graph();
		int familyCheck(int temp);
		int personCheck(int temp, string relation);
		int personIndex(int temp);
		void insertFamily(vector< pair <string,int> > myVector);
		void Union(int left, int right);
		bool Find(int left, int right);
		void BFS(int start, int end);
	private:
		// Decleration of Person vertex
		struct Person;
		
		// Family vertex
		struct Family {
        		int number;
       	 		Person *husband;
        		Person *wife;
        		vector<Person*> children;
		};
		
		// Person vertex
		struct Person {
        		int number;
        		Family *marriage;
        		Family *parentage;
		};
	
		// Create a Family vertex
		struct Family* newFamily() {
        		Family* temp = new Family;
        		temp->number = 0;
        		temp->husband = NULL;
        		temp->wife = NULL;
        		return temp;
		};
		
		// Create a Person vertex
		struct Person* newPerson() {
        		Person* temp = new Person;
        		temp->number = 0;
        		temp->marriage = NULL;
        		temp->parentage = NULL;
        		return temp;
		};
		
		// Set struct for Union Find connectivity
		struct Set {
			int number;
			int depth;
			int representative;
		};
		
		// Create a Set struct
		struct Set* newSet() {
			Set* temp = new Set;
			temp->number = 0;
			temp->depth = 0;
			temp->representative = 0;
			return temp;
		};

		vector<Family*> families;	// Vector of Family vertices
		vector<Person*> people;		// Vector of Person vertices
		Set* sets[MAXP];		// Array of Set struct (Union Find)
};

#endif /* GRAPH_H */
