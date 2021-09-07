#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include"graph.h"

using namespace std;

// graph constructor
graph::graph() {
	for (int i = 0; i < MAXP + 1; i++)
		sets[i] = newSet();
}

// Find the index of the given person
int graph::personIndex(int temp) {
	int index = -1;
	for (unsigned long i = 0; i < people.size(); i++) {
                if (people[i]->number == temp) {
                        index = i;
                }
        }
	return index;
}

// Check if a Family has already been created
int graph::familyCheck(int temp) {
	for (unsigned long i = 0; i < families.size(); i++) {
		if (families[i]->number == temp)
			return 1;
	}
	return 0;
}

// Check if a Person has been used, and if either the marriage or parentiage has been used
int graph::personCheck(int temp, string relation) {
	// If person index does not find the person, it hasn't been created
	int index = personIndex(temp);
	if (index == -1) 
		return 1;
	
	// Check if the person's marriage is NULL
	if (relation == "Husband") {
		if (people[index]->marriage == NULL)
			return 1;
		else {
			cout << "\t" << relation << " " << temp << " is already married.\n";
			return 0;
		}
	}
	// Check if the person's marriage is NULL
	else if (relation == "Wife") {
		if (people[index]->marriage == NULL)
                        return 1;
                else {
                        cout << "\t" << relation << " " << temp << " is already married.\n";
                        return 0;
                }
        }
	// Check if the person's parentage is NULL
	else {
		if (people[index]->parentage == NULL)
                        return 1;
                else {
                        cout << "\t" << relation << " " << temp << " is already parented.\n";
                        return 0;
                }
	}
	return 0;
}

// Union to sets together, shorter pathn is connected to longer path
void graph::Union(int left, int right) {
	// Each Set starts with depth 1
	int leftCount = 1, rightCount = 1;
	// Temporary ints
	int tempLeft = left, tempRight = right;

	while (sets[tempLeft]->representative != 0) {
		leftCount++;
		tempLeft = sets[tempLeft]->representative;
	}
	while (sets[tempRight]->representative != 0) {
		rightCount++;
                tempRight = sets[tempRight]->representative;
	}

	// If the depth of the left Set is shorter, connect it to the right Set
	if (sets[tempLeft]->depth < sets[tempRight]->depth) {
		sets[tempLeft]->representative = tempRight;
		if (sets[tempRight]->depth == 0)
			++sets[tempRight]->depth; // Keep track of depth
	} // If the depth of the left Set is equal, connect it to the right Set
	else if (sets[tempLeft]->depth == sets[tempRight]->depth) {
		if (sets[tempLeft]->representative != tempRight) {
			sets[tempLeft]->representative = tempRight;
			++sets[tempRight]->depth; // Keep track of depth
		}
	}
	else { // Else connect the right Set ot the left Set
		sets[tempRight]->representative = tempLeft;
		++sets[tempLeft]->depth; // Keep track of depth
	}
}

// Find function to see if two People are connected
bool graph::Find(int left, int right) {
	bool val;
	int leftTemp = left, rightTemp = right;

	// If either number is 0, they are not real people
	if ((sets[left]->number == 0) || (sets[right]->number == 0))
		return val = 0;
	// If the right side is its own representative
	if (sets[right]->representative == 0) { 
		// Continue until the root is found, or the right number is found
		while ((sets[leftTemp]->representative != 0) && (sets[leftTemp]->number != right))
			leftTemp = sets[leftTemp]->representative;
		if (sets[leftTemp]->number == right)
			return val = 1;
		else
			return val = 0;
	}
	else {
		// Continue until the root is found
		while (sets[leftTemp]->representative != 0)
			leftTemp = sets[leftTemp]->representative;
		// Continue until the root is found
		while (sets[rightTemp]->representative != 0)
			rightTemp = sets[rightTemp]->representative;
		if (sets[leftTemp]->number == sets[rightTemp]->number)
			return val = 1;
		else
			return val = 0;
	}
}

// Create a new family
void graph::insertFamily(vector< pair <string,int> > myVector) {
	// Check if the family has already been created
	if (familyCheck(myVector[0].second) == 1) {
		cout << "\tFamily " << myVector[0].second << " has already been entered\n";
		return;
	}
	else {
		// Keep count of how many people are created or modified
		int count = 0;
		vector<Set*> tempSets; // temp vector of Set* to hold new Sets
		Family* temp = newFamily(); // temp Family* to add to the Family vector
		temp->number = myVector[0].second; // put the Family number into the vertex
		int index;

		// Before creating any new people or modifying, make sure they are valid
		for (unsigned long i = 1; i < myVector.size(); i++) {
			if (myVector[i].second > 0) 
				if (personCheck(myVector[i].second,myVector[i].first) == 0)
					return;

		}

		// If husband is known, either make a new person or modify existing one
		if (myVector[1].second > 0) { 
			count++;
			index = personIndex(myVector[1].second);
			if (index == -1) { // New person
				Person* hus = newPerson();
				hus->number = myVector[1].second;
				hus->marriage = temp;
				temp->husband = hus;
				people.push_back(hus);
				sets[myVector[1].second]->number = myVector[1].second;
			}
			else { // Modify existing person
				people[index]->marriage = temp;
				temp->husband = people[index];
			}
		}
		// If wife is known, either make a new person or modify existing one
		if (myVector[2].second > 0) {
			count++;
			index = personIndex(myVector[2].second);
                        if (index == -1) { // New person
				Person* wife = newPerson();
                        	wife->number = myVector[2].second;
                        	wife->marriage = temp;
                        	temp->wife = wife;
				people.push_back(wife);
				sets[myVector[2].second]->number = myVector[2].second;
			}
			else { // Modify existing person
				people[index]->marriage = temp;
                                temp->wife = people[index];
                        }

		}

		cout << "Family " << myVector[0].second << " has husband " << myVector[1].second;
		cout << ", wife " << myVector[2].second << ", and children";
		
		// If children are entered, either create new people or modify existing ones
		for (unsigned long i = 3; i < myVector.size(); i++) {
			if (myVector[i].second > 0) {
				count++;
                        	index = personIndex(myVector[i].second);
                        	if (index == -1) { // New person
                                	Person* child = newPerson();
                                	child->number = myVector[i].second;
                                	child->parentage = temp;
                                	temp->children.push_back(child);
                                	people.push_back(child);
					sets[myVector[i].second]->number = myVector[i].second;
                        	}
                        	else { // Modify existing person
                                	people[index]->parentage = temp;
                                	temp->children.push_back(people[index]);
                        	}
				cout << " " << myVector[i].second;
			}
                }
		cout << ".\n";
		families.push_back(temp); // Add the temp Family vertex to the vector
		int myCount = myVector.size() - 1;
		// Hold the index for connecting sets
		int UnionIndex;
		// If the husband was know
		if (myVector[1].second > 0) {
			UnionIndex = 2;
			// Use the count of people and the Union Index to do Unions on the Sets
			for (int i = 0; i < myCount-1; i++)
                        	if (myVector[i+UnionIndex].second > 0)
                                	Union(myVector[i+UnionIndex].second,myVector[UnionIndex-1].second);
		}
		// If the wife was known
		else if (myVector[2].second > 0) {
			UnionIndex = 3;
			// Use the count of people and the Union Index to do Unions on the Sets
			for (int i = 0; i < myCount-2; i++)
                        	if (myVector[i+UnionIndex].second > 0)
                                	Union(myVector[i+UnionIndex].second,myVector[UnionIndex-1].second);
		}
		else { // Else use the first child
			UnionIndex = 4;
			// Use the count of people and the Union Index to do Unions on the Sets
			for (int i = 0; i < myCount-3; i++)
                        	if (myVector[i+UnionIndex].second > 0)
                                Union(myVector[i+UnionIndex].second,myVector[UnionIndex-1].second);
		}
		return;
	}	
}

// Breadth First Search function
void graph::BFS(int start, int end) {
	vector<Person*> myQueue; // Use a vector for the queue routine
	myQueue.push_back(people[personIndex(start)]); // Add the first vertex to the queue
	int prev[2][MAXP]; // Matrix to hold the pervious vertex number and the family which it was related
	bool visited[MAXP]; // Bool array to tell if a Perosn vertex had been visited
	
	// Initialize the bool array and the matrix
	for (int i = 0; i < MAXP; i++) {
		visited[i] = 0;
		prev[0][i] = 0;
		prev[1][i] = 0;
	}
	
	visited[start] = 1; // First vertex will be visited

	// While the vector isn'y empty
	while (!myQueue.empty()) {
		Person* node = myQueue[0]; // Next inline in the queue
		myQueue.erase(myQueue.begin()); // Erase the first element in the queue
		vector< pair <Person*,int> >  neighbors; // Vector pair to hold the Person vertices and the family that they are connected to

		// If the node's marriage pointer isn't NULL add all the peeple from that family to the neighbors
		if (node->marriage != NULL) {
			// Add the Husband if he is known
			if (node->marriage->husband != NULL) {
				if (node->marriage->husband->number != node->number) // Make sure the same node isn't added
					neighbors.push_back(make_pair(node->marriage->husband,node->marriage->number));
			}
			// Add the wife if she is known
			if (node->marriage->wife != NULL) {
				if (node->marriage->wife->number != node->number) // Make sure the same node isn't added
					neighbors.push_back(make_pair(node->marriage->wife, node->marriage->number));
			}
			// Add all the children to the neighbors
			for (unsigned long i = 0; i < node->marriage->children.size(); i++)
				neighbors.push_back(make_pair(node->marriage->children[i],node->marriage->number));
		}
		
		// If the node's parent pointer isn't NULL add all the peeple from that family to the neighbors
		if (node->parentage != NULL) {
			// Add the Husband if he is known
			if (node->parentage->husband != NULL)
				neighbors.push_back(make_pair(node->parentage->husband,node->parentage->number));
			// Add the wife if she is known
			if (node->parentage->wife != NULL)
				neighbors.push_back(make_pair(node->parentage->wife,node->parentage->number));
			// Add all the children to the neighbors
			for (unsigned long i = 0; i < node->parentage->children.size(); i++) 
				if (node->number != node->parentage->children[i]->number) // Make sure the same node isn't added
                                	neighbors.push_back(make_pair(node->parentage->children[i], node->parentage->number));
		}
		
		// Loop until all the neighbors are visited
		for (unsigned long i = 0; i < neighbors.size(); i++) {
			if (!visited[neighbors[i].first->number]) { // If the neighbor hasn't been visited
				myQueue.push_back(neighbors[i].first); // Add the neighbor to queue
				visited[neighbors[i].first->number] = 1; // Make the bool 1
				prev[0][neighbors[i].first->number] = node->number; // Add the node number to the prev matrix
				prev[1][neighbors[i].first->number] = neighbors[i].second; // Add the family number to the prev matrix
			}
		}
	}
	
	vector < pair <int,int> > myPath; // Vector to hold the path between the two vertices
	// Start at the end, end when the first Vertex is found
	for (int i = end; i != 0; i = prev[0][i]) {
		myPath.push_back(make_pair(i,prev[1][i]));
	}
	cout << "Relation:";
	cout << " person " << myPath[myPath.size()-1].first << " ->";
	for (unsigned long i = myPath.size() - 2; i != 0; i--) {
		cout << " family " << myPath[i].second << " ->";
		cout << " person " << myPath[i].first << " ->";
	}
	cout << " family " << myPath[0].second << " ->";
        cout << " person " << myPath[0].first;
	cout << endl;
}
