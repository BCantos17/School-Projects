/*
 * Created by Bryan Cantos for class CSCI 493.69 2015
 */

#include <iostream>
#include <assert.h>
#include "Image.h"
#include "Pgm.cpp"

using namespace std;

void toEdge( char **argv );

int main( int argc, char **argv ){
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <INPUT_PGM_IMAGE>	<OUTPUT_PGM_IMAGE>" << endl;
		return 0;
  	}

  	toEdge( argv );

	return 0;
}

void toEdge( char **argv ) {

	Image *grey;
	grey = new Image;
	assert( grey != 0 );

	Image *edge;
	edge = new Image;
	assert( edge != 0 );

	if( readImage( grey, argv[ 1 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 1 ] << endl;
		exit ( 1 );
	}

	int rows = grey->getNRows();
	int cols = grey->getNCols();

	edge->setSize( rows, cols );
	edge->setColors( 255 );

	//Uses the Laplacian method to generate an edge image by getting the dx^2/dy^2 of a pixel
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ ){
			int dx;
			int dy;
			int dXdY;

			if( i + 1 != rows )
				dx = grey->getPixel( i - 1, j ) - 2*grey->getPixel( i, j ) + grey->getPixel( i + 1, j );

			dy = grey->getPixel( i, j - 1 ) - 2*grey->getPixel( i, j ) + grey->getPixel( i, j +1 );
			dx = dx*dx;
			dy = dy*dy;
			dXdY = dx + dy;
			edge->setPixel( i, j, dXdY );

		}

	if( writeImage( edge, argv[ 2 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 2 ] << endl;
		exit ( 1 );
	}

	return;
}