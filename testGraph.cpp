#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "AdjacencyList.h"

using namespace std;

void makeGraph	( AdjacencyList & graph, string & text );
void findVertex	( AdjacencyList & graph );

int main( int argc, char **argv ) {
	if (argc != 3) {
    	cout << "Usage: " << argv[0] << " <GRAPH_FILE>	<STARTING_VERTEX>" << endl;
    	return 0;
  	}
  	string fileName( argv[ 1 ] );
  	int start = atoi( argv[ 2 ] );
	AdjacencyList graph;
	makeGraph( graph, fileName );
	graph.dijkstra( start );
	findVertex( graph );

	return 0;
}

void makeGraph( AdjacencyList & graph, string & name ) {
	ifstream file( name );
	if(file.fail()) {
		cout << "Could not open file." << endl;
		exit(1);
	}

	int vertices;
	string text;

	// Get the number of vertices from the text file
	getline( file, text );
	stringstream number(text);
	number >> vertices;
	graph.setVertices( vertices );

	// Inserts the edges into the graph
	while( getline( file, text ) ){
		stringstream edges( text );
		int firstVertex, secondVertex;
		float weight;
		edges >> firstVertex;
		while( edges >> secondVertex ) {
			if( secondVertex == -1 )
				break;
			edges >> weight;
			graph.addEdge( firstVertex, secondVertex, weight );
		}
	}
}

// Prompts the user to find a Vertex
void findVertex	( AdjacencyList & graph ) {
	cout << "Please enter a Vertex that you want to find" << endl;
	int goal;
	cin >> goal;
	graph.shortestPath( goal );
	cout << "Do you want to continue? Enter 'y' for yes" << endl;
	char cont;
	cin >> cont;
	while( cont == 'y') {
		cout << "Please enter a Vertex that you want to find" << endl;
		cin >> goal;
		graph.shortestPath( goal );
		cout << "Do you want to continue? Enter 'y' for yes" << endl;
		cin >> cont;
	}
}