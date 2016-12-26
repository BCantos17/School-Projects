/*
 * Created by Bryan Cantos for class CSCI 493.69 2015
 */
#include <iostream>
#include <assert.h>
#include "Image.h"
#include "Pgm.cpp"

using namespace std;

void toBinary( char **argv );

int main( int argc, char **argv ){
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " <INPUT_PGM_IMAGE>	<THRESHOLD> <OUTPUT_PGM_IMAGE> " << endl;
		return 0;
  	}

  	toBinary( argv );

	return 0;
}

void toBinary( char **argv ) {

	Image *edge;
	edge = new Image;
	assert( edge != 0 );

	Image *binary;
	binary = new Image;
	assert( binary != 0 );

	if( readImage( edge, argv[ 1 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 1 ] << endl;
		exit ( 1 );
	}

	int threshold = atoi( argv[2] );

	int rows = edge->getNRows();
	int cols = edge->getNCols();

	binary->setSize( rows, cols );
	binary->setColors( 1 );

	// By using the thersold, sets the input image to a binary image, meaning the picture will only be black and white.
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ )
			if ( edge->getPixel( i, j ) < threshold )
				binary->setPixel( i, j, 0 );
			else
				binary->setPixel( i, j, 1 );

	if ( writeImage( binary , argv[3] ) != 0 ){
		cout << "Can't open file " << argv[ 3 ] << endl;
		exit ( 1 );
	}

}