Project Name: Families
Author: Tyler Smith
Class: CS 315

Purpose: This program implements a directed bipartite graph with FAmily and Person vertexes.
	 A Family vertex only points to People vertices and a Person vertex on points to Family vertices.
	 Correctly formatted commands are read line by line from standard input.
	 If the input begins with "Family", a new family is created given that all input is valid.
	 If the input begins with "Relate", the program first sees if the two vertices are connected.
	 These two vertices are then put into a Breadth First Search algorithm tof ind the shortest path.

How it Works: When the "Family" command is entered, the program checks for various things.
	      First the prgram checks that the Family has not been created yet.
	      Next each person is checked that they are not already part of a marriage or already a child.
	      When the "Relate" command is enterd, the program first checks for connectivity.
	      Connectivity is found by first Unioning each person with those that they are related to.
	      Next a Find algorithm is used to see if the two people are related.
	      If they are related, Breadth First Search is used to find the shortest path between them.

How to Compile:
		
		(should work): make run
		
		(if that doesn't work): g++ -g -Wall -o genealogy genealogy.cpp graph.cpp
