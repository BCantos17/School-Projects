#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Vertex{
public:
	Vertex () { 
	}

	Vertex( const int & number ): thisVertex{ number }, adjList{ 0 } {
	adjList.resize( 0 ); 
	}

	int getNumber( ) const {
		return thisVertex;
	}

	void displayEdges( ) const {
		cout << "Vertex " << thisVertex << " has edge:" << endl;
		if( adjList.size() == 0 ){
			cout << "no edges." << endl;
			return;
		}
		for( int i = 0; i < adjList.size(); ++i ){
			cout << adjList[ i ].thatVertex << " with a weight of " << adjList[ i ].weight << endl;
		}
	}

	void makeEdge( Vertex * & v, const int & n, const float & f ) {
		adjList.resize( adjList.size() + 1);
		adjList.back().node = v;
		adjList.back().thatVertex = n;
		adjList.back().weight = f;
	}

	void reset() {
		dist = INT_MAX;
		known = false;
	}

	void setDistant( const float & f ) {
		dist = f;
	}

	bool knownIsFalse() {
		if ( !known )
			return true;
		else return false;
	}

	void setPQ() {
		for( int i = 0; i < adjList.size(); ++i) {
			pq.push( adjList[i] );
		}
	}

	void setKnown( ) {
		known = true;
	}

	Vertex * smallestWeight( ) const {
		return pq.top().node;
	}

	void deleteMin( ) {
		pq.pop();
	}
private:
	struct Edge {
		Vertex* node;
		int thatVertex;
		float weight;

		Egde( ) {
			thatVertex = 0;
			weight = 0;
		}
		bool operator<( const Edge & rhs) const {
  			return weight < rhs.weight;
		}
	};

	vector< Edge > adjList;
	int thisVertex;
	Vertex *path;
	float dist = INT_MAX;
	bool known = false;
	priority_queue< Edge > pq;

};

#endif