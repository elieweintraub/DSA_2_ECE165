/********************************************************************************/
/*  Elie Weintraub                                                              */
/*  DSAII - Programming Project #3                                              */
/*                                                                              */ 
/*  usegraph.cpp                                                                */
/*                                                                              */
/*  This sourcefile uses the Graph class defined in graph.h and implemented in  */
/*  graph.cpp as part of a simple program that takes a txt file representing a  */
/*  graph as input, reads it into a Graph, and performs Dijkstra's algorithm to */
/*  compute the shortest path lengths from a source vertex given by the user    */
/*  to every other vertex in the graph. The output is then sent to a txt file.  */
/*                                                                              */
/********************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "graph.h"
#include "heap.h"
#include "hash.h"

using namespace std;

// Prompt user to supply source id. If not a valid source id the user is re-prompted.
void promptUser(Graph &myGraph, string &src_id){
	bool inputGood = false;	
	while (!inputGood) {
		inputGood = true;
		cout <<"Enter a valid vertex id for the staring vertex: ";
		cin >> src_id;
		if (!myGraph.contains(src_id)){ //Input is not valid
			cout<<"The vertex you entered was not valid!"<<endl;
			inputGood = false;
		}	
	}
}	


int main(){
	string inputFileName, outputFileName;
	string src_id, dest_id;
	unsigned long weight;
	int size=0;
	
	//Prompt user for input file and verify that opens properly
	cout<<"Enter name of graph file: ";
	cin>>inputFileName;
	
	ifstream input(inputFileName.c_str());
	if (!input.is_open()){ // Error opening input file
		cerr << "Unable to open input file: "<<inputFileName<<endl;
		exit(1);
	}
	
	//Create Graph from input file
	Graph myGraph(size);
	while (input.good()){
		input>>src_id>>dest_id>>weight; 
		myGraph.insertEdge(src_id,dest_id,weight);
	}
	
	input.close();
		
	//Prompt user to supply id of starting vertex
	promptUser(myGraph,src_id);
	
	//Apply Dijkstra's Algorithm and record CPU time
	clock_t t1,t2;
	double timeDiff;
	
	t1 = clock();
	myGraph.dijkstra(src_id);
	t2 = clock();
	timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff<< endl;
	
	//Prompt user to supply output file and verify that opens properly
	cout<<"Enter name of output file: ";
	cin>>outputFileName;
	
	ofstream output(outputFileName.c_str());
	if (!output.is_open()){ // Error opening output file
		cerr << "Unable to open output file: "<<outputFileName<<endl;
		exit(1);
	}

	//Produce output file
	if(myGraph.printPaths(src_id,output)){
		cerr<<"Can't print paths because Dijkstra's Algorithm hasn't been performed"<<endl;
		exit(1);
	}
	
	output.close();
	
	return 0;
}	