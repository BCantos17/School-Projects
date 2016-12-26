/*
 * Created by Bryan Cantos for class CSCI 493.69 2015
 */
#include <iostream>
#include <assert.h>
#include "Image.h"
#include "Pgm.cpp"
#include <cmath>

#define PI 3.1415926

using namespace std;

void houghTransform( char **argv );

int main( int argc, char **argv ){
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <INPUT_PGM_IMAGE> <OUTPUT_PGM_IMAGE> " << endl;
		return 0;
  	}

  	houghTransform( argv );

	return 0;
}

void houghTransform( char **argv ){

	Image *binary;
	binary = new Image;
	assert( binary != 0 );

	Image *hough;
	hough = new Image;
	assert( hough != 0 );

	if( readImage( binary	, argv[ 1 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 1 ] << endl;
		exit ( 1 );
	}

	int row = binary->getNRows();
	int col = binary->getNCols();

	int theta = 180;
	int maxRho = static_cast<int> ( round( sqrt( (row * row) + (col * col) ) ) );
	int accArray[maxRho][theta];

	// Sets everything in the array to 0
	memset(accArray, 0, sizeof(accArray[0][0]) * maxRho * theta);

	hough->setSize( maxRho, theta );
	hough->setColors( 255 );

	//By only looking at a pixel set to 1, we use hough transformation to generation an image
	for( int i = 0; i < row - 1; i++ )
		for( int j = 0; j < col - 1; j++ )
			if( binary->getPixel( i, j ) == 1 )
				//If the Pixel is 1, calculate the rho from 0 to 180 degree
				for( int k = 0; k < theta; k++ ){
					double angle = k * PI / theta;
					int rho = round( ( i * sin( angle) ) + ( j * cos( angle ) ) );
					//Make the accumulator into 2, upper for postive and bottom for negative 
					int temp = round( maxRho / 2.0 + rho / 2.0 );
					accArray[temp][k]++; 
				}

	 for(int i = 0; i < maxRho; ++i)
		for(int j = 0; j < theta; ++j)
			hough->setPixel(i, j, accArray[i][j]);

	if ( writeImage( hough , argv[2] ) != 0 ){
		cout << "Can't open file " << argv[2] << endl;
		exit ( 1 );
	}

	return;
}