#include <iostream>
#include <assert.h>
#include "Image.cpp"
#include "Image.h"
#include "Pgm.cpp"

using namespace std;

int main( int argc, char *argv[] ) {

	if( argc != 3 ) {
		printf( "Usage: %s file1 file2\n", argv[0] );
		exit( 1 );
	}

	Image *binary;
	binary = new Image;
	assert( binary != 0 );

	Image *label;
	label = new Image;
	assert( label != 0 );

	if( readImage( binary, argv[1] ) != 0 ) {
		printf( "Can't open file %s\n", argv[1] );
		exit ( 1 );
	}

	label->toLabel( binary );

	if ( writeImage( label , argv[2] ) != 0 ){
		printf( "Can't write to file %s\n", argv[2] );
		exit ( 1 );
	}

	return 0;
}
