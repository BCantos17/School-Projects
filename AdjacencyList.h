#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

class AdjacencyList {
private:
	struct Edge;
	struct Vertex;

public:
	AdjacencyList ( ) {
		vertices.resize( 0 );
	}
	AdjacencyList ( const int number ) : total ( number ) {
		vertices.resize( 0 );
		setVertices( total );
	}

	~AdjacencyList( ) { 
		makeEmpty( ); 
	}
	/**
     *  Make the vertices empty 
     */
	void makeEmpty( ) {
		for(int i = 0; i < total; ++i)
			makeEmpty( vertices[ i ] );
		total = 0;
	}

	/**
     *  Sets up all the vertices in a given vertices
     */
	bool setVertices( const int & number ) {
		if( number == 0 )
			return false;

		total = number;
		vertices.resize( number );

		for( int i = 0; i < total; ++i) {
			Vertex *newVertex = new Vertex{ i };
			vertices[ i ] = newVertex;
		}
		return true;
	}

	/**
     *  Add an edge to a Vertex
     */
	bool addEdge( const int vertex1, const int vertex2, const float weight ) {
		// Return false if vertex does not exist
		if( vertex1 >= total )
			return false;

		// Finds first Vertex
		int i;
		for( i = 0; i < total; ++i) {

			if( vertices[ i ]->thisVertex == vertex1 ) 
				break;
			else if( i == total )
				return false;
		}
		
		// Finds second Vertex
		int j;
		for( j = 0; j < total; ++j) {
			if( vertices[ j ]->thisVertex == vertex2 ) 
				break;
			else if( i == total )
				return false;
		}

		// Adds the edge
		vertices[ i ]->adjList.resize( vertices[ i ]->adjList.size() + 1);
		vertices[ i ]->adjList.back().node = vertices[ j ];
		vertices[ i ]->adjList.back().thatVertex = vertex2;
		vertices[ i ]->adjList.back().weight = weight;

		//cout << vertices[ i ]->thisVertex << endl;

		return true;
	}

	/**
     *  Displays the Graph, used for debugging purposes 
     */
	void displayGraph() {
		cout << "Total number of Vertices is " << total << "." << endl;

		for( int i = 0; i < total; ++i ) {
			cout << "Vertex " << vertices[ i ]->thisVertex << " has edge:" << endl;
			if( vertices[ i ]->adjList.size() == 0 ){
				cout << "no edges." << endl;
				return;
			}
			for( int j = 0; j < vertices[ i ]->adjList.size(); ++j )
				cout << vertices[ i ]->adjList[ j ].thatVertex << " with a weight of " << vertices[ i ]->adjList[ j ].weight << endl;
		} 
	}

	/**
     *  Uses dijkstra algorithm to find all paths of the start
     */
	void dijkstra( int start ) {
		// Sets all dist to Infinity and known to false
		for (int i = 0; i < total; ++i){
			vertices[ i ]->dist = INT_MAX;
			vertices[ i ]->known = false;
		}

		// Find starting vertex
		int s;
		for( s = 0; s < total; ++s){
			if( vertices[ s ]->thisVertex == start ) {
				vertices[ s ]->dist = 0 ;
				break;
			}
		}

		pq.push( vertices[ s ] );

		// Gets the path of all the Vertices
		for( ; ; ) {
			Vertex* v = new Vertex;
			bool success = false;
			while( !pq.empty() && !success){
				v = pq.top();
				pq.pop();
				if( !v->known )
					success = true;
			}
			if (!success)
				break;
			v->known = true;
			for( int i = 0; i < v->adjList.size(); ++i ){
				Vertex* w = new Vertex;
				w = v->adjList[ i ].node;
				if( (v->dist + v->adjList[ i ].weight ) < w->dist) {
					w->dist = ( v->dist + v->adjList[ i ].weight );
					pq.push( w );
					w->path = v;
				}
			}
		}
	}

	/**
     *  Outputs the shortest path and the total dist to get to the Vertex
     */
	void shortestPath( const int goal ) const{
		// Returns if given a number not in the graph
		if( goal >= total ){
			cout << "Invalid goal, Vertex does not exist" << endl;
			return;
		}
		Vertex* path = new Vertex;
		// Finds the Vertex
		for( int i = 0; i < total; ++i )
			if ( vertices[ i ]->thisVertex == goal )
				path = vertices[ i ];

		// Returns if there is no path to that Vertex
		if( path->dist == INT_MAX ){
			cout << "This goal vertex has no path" << endl;
			return;
		}

		cout << "The total distant from the starting point to goal point is " << path->dist << endl;
		cout << "The path is from ";

		// Displays the path of the Vertex
		while( path != nullptr ){
			if( path->path == nullptr ){
				cout << path->thisVertex << endl;
				break;
			}
			cout << path->thisVertex << "<-";
			path = path->path;
		}
	}

private:
	struct Edge {
		Vertex* node;			// The vertex the edge points to
		int thatVertex;			// The number of the Vertex the edge points to
		float weight;			// The weight of the edge

		Egde( ) {
			thatVertex = 0;
			weight = 0;
		}
		bool operator<( const Edge & rhs) const {
  			return weight < rhs.weight;
		}
	};

	struct Vertex {
		vector< Edge > adjList; 	// The List of all edges that are adjacent to the Vertex
		int thisVertex;				// The number this vertex is assigned to
		Vertex *path;				// The shortest Path given a starting point to this Vertex
		float dist = INT_MAX;		// Infinity 
		bool known = false;

		Vertex () {
			adjList.resize( 0 ); 
		 }

		Vertex( const int & number ): thisVertex{ number }, adjList{ 0 } {
			adjList.resize( 0 ); 
		}

		bool operator<( const Vertex * & rhs) const {
  			return dist < rhs->dist;
		}
	};

	vector<Vertex*> vertices;
	int total;
	priority_queue< Vertex* > pq;

	/**
     *  Inside function to make vertices empty 
     */
	void makeEmpty( Vertex * & v ) {
		delete v;
		v = nullptr;
	}
};


#endif