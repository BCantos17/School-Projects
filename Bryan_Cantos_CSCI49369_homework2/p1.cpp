/* 
** Created by Bryan Cantos
** Class CSCI 49369
*/

#include <stdio.h>
#include <assert.h>
#include "Image.h"
#include "Pgm.cpp"

using namespace std;

/* Converts a grey scale image to a binary image */
Image *GreyToBinary( Image *grey, int thershold );

int main( int argc, char **argv ) {

	if( argc != 4 ) {
		printf( "Usage: %s file1 thershold file3\n", argv[0] );
		exit( 1 );
	}

	int thershold = atoi( argv[2] );
	Image *grey;
	grey = new Image;	
	assert( grey != 0 );
	Image *binary;
	binary = new Image;
	assert( binary != 0 );

	if( readImage( grey, argv[1] ) != 0 ) {
		printf( "Can't open file %s\n", argv[1] );
		exit ( 1 );
	}

	binary = GreyToBinary( grey, thershold );

	if ( writeImage( binary , argv[3] ) != 0 ){
		printf( "Can't write to file %s\n", argv[3] );
		exit ( 1 );
	}

	return 0;
}

Image *GreyToBinary( Image *grey, int thershold ){


	Image *im;
	im = new Image;
	assert( im != 0 );

	im->setSize( grey->getNRows(), grey->getNCols() );
	im->setColors( 1 ); 								/*Sets the image to a binary image, 
														  as in it only has 2 colors, 0 and 1
														*/
	int rows = grey->getNRows();
	int cols = grey->getNCols();

	/*Goes through every single pixel by rows and columns
	  and if the pixel is below the thersold, this sets the 
	  pixel to 0, else to 1 
	*/
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ )
			if ( grey->getPixel( i, j ) < thershold )
				im->setPixel( i, j, 0 );
			else
				im->setPixel( i, j, 1 );

	return im;
}