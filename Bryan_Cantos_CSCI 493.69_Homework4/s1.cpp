/* 
** Created by Bryan Cantos
** Class CSCI 49369
*/

#include <iostream>
#include <assert.h>
#include "Image.h"
#include "Pgm.cpp"
#include <fstream>
#include <cmath>

using namespace std;

struct Database{
	Datebase();
	int rowSum = 0;
	int colSum = 0;
	int totalPixel = 0;
	int leftMost = 0;
	int rightMost = 0;
	int upperMost = 0;
	int bottomMost = 0;
	double radius = 0;
	double centerRow = 0;
	double centerCol = 0;
};

void toBinary( char** argv, Image* grey, Image* binary );
void parameters( char** argv, Image* binary, Database & sphere );
void toFile( char** argv, Database & sphere);

int main( int argc, char **argv ) {

	if( argc != 4 ) {
		 cout << "Usage: " << argv[0] << " <INPUT_PGM_IMAGE> <THERSHOLD> <OUTPUT_PARAMETERS_FILE>" << endl;
		exit( 1 );
	}

	Database sphere;

	//Creates new images
	Image *grey;
	grey = new Image;
	assert( grey != 0 );

	Image *binary;
	binary = new Image;
	assert( binary != 0 );

	if( readImage( grey, argv[ 1 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 1 ] << endl;
		exit ( 1 );
	}


	toBinary	( argv, grey, binary );			// Converts Grey Scale Image to Binary
	parameters 	( argv, binary, sphere );		// Get the center of the binary image in (x, y) format and radius
	toFile		( argv, sphere );				// Input parameters into a text file

	return 0;
}

void toBinary( char** argv, Image* grey, Image* binary ){

	int threshold = atoi( argv[2] );	// Thershold of binary image set by user

	int rows = grey->getNRows();
	int cols = grey->getNCols();

	binary->setSize( rows, cols );
	binary->setColors( 1 );

	// By using the thersold, sets the input image to a binary image, meaning the picture will only be black and white.
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ )
			if ( grey->getPixel( i, j ) < threshold )
				binary->setPixel( i, j, 0 );
			else
				binary->setPixel( i, j, 1 );

	if ( writeImage( binary , "binary_sphere.pgm" ) != 0 ){
		cout << "Can't open file " << "binary_sphere.pgm" << endl;
		exit ( 1 );
	}
}

void parameters( char** argv, Image* binary, Database & sphere ){

	int rows = binary->getNRows();
	int cols = binary->getNCols();

	// Computes the sum of the rows, sum of the columns and the area of the sphere
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ ){

			// If the pixel is not black, continue with calculations 
			if( binary->getPixel( i, j ) != 0){

				sphere.rowSum += i;
				sphere.colSum += j;
				sphere.totalPixel ++;

				// Sets up the all the parameters to start with the location of the very first white pixel
				if( sphere.leftMost == 0){
					sphere.leftMost = j;
					sphere.rightMost = j;
					sphere.upperMost= i;
					sphere.bottomMost= i;
				}

				// Assign the leftMost, rightMost, upperMost and bottomost pixel
				if( j < sphere.leftMost )
					sphere.leftMost = j;

				if( j > sphere.rightMost )
					sphere.rightMost = j;

				if( i < sphere.upperMost )
					sphere.upperMost = i;

				if( i > sphere.upperMost )
					sphere.upperMost = i;
		}
	}

	sphere.centerCol = round( sphere.colSum / sphere.totalPixel );
	sphere.centerRow = round( sphere.rowSum / sphere.totalPixel ) + 1;
	sphere.radius = round( ( ( sphere.upperMost - sphere.bottomMost ) + (sphere.rightMost - sphere.leftMost ) ) /4 );

}

void toFile( char** argv, Database & sphere){

	ofstream file( argv[3] );

	// inserts data from the Database to Database.tx
	file << sphere.centerCol << " ";
	file << sphere.centerRow << " ";
	file << sphere.radius << endl;

	file.close();
}