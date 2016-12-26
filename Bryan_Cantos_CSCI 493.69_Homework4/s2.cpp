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
	double radius = 0;
	double centerRow = 0;
	double centerCol = 0;
	double brightPixel[1][3] = { {0.0, 0.0, 0.0} };
	int brightest = 0;
};

void findPixel		( char** argv, vector<Database> & data );
void getDirection	( char** argv, vector<Database> & data );
void toFile			( char** argv, vector<Database> & data );

int main( int argc, char **argv ) {

	if( argc != 6 ) {
		cout << "Usage: " << argv[0] << " <INPUT_PARAMETER_FILE> <IMAGE1> <IMAGE2> <IMAGE3> <OUTPUT_DIRECTION_FILE>" << endl;
		exit( 1 );
	}

	vector<Database> data(3);

	findPixel		( argv, data );		// Find the location of the brighest pixel for all three images
	getDirection	( argv, data );		// Find the directions of the light source from all thee images
	toFile			( argv, data );		// Input the directions into a text file

	return 0;
}

void findPixel( char** argv, vector<Database> & data ){

	Image *sphere1;
	sphere1 = new Image;
	assert( sphere1 != 0 );

	Image *sphere2;
	sphere2 = new Image;
	assert( sphere2 != 0 );

	Image *sphere3;
	sphere3 = new Image;
	assert( sphere3 != 0 );

	if( readImage( sphere1, argv[ 2 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 2 ] << endl;
		exit ( 1 );
	}
	if( readImage( sphere2, argv[ 3 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 3 ] << endl;
		exit ( 1 );
	}
	if( readImage( sphere3, argv[ 4 ] ) != 0 ) {
		cout << "Can't open file " << argv[ 4 ] << endl;
		exit ( 1 );
	}

	int rows = sphere1->getNRows();
	int cols = sphere1->getNCols();

	// The intensity of the brightest pixel for each of the images
	int spherePixel1 = 0;
	int spherePixel2 = 0;
	int spherePixel3 = 0;

	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ ){

			/* If the Pixel has a greater brightness than previously encountered, assign that pixel to the database */

			if( sphere1->getPixel( i, j) > spherePixel1 ){
				spherePixel1 = sphere1->getPixel(i, j);
				data[0].brightPixel[0][0] = j;
				data[0].brightPixel[0][1] = i;
				data[0].brightest = spherePixel1;
			}
			if( sphere2->getPixel( i, j) > spherePixel2 ){
				spherePixel2 = sphere2->getPixel(i, j);
				data[1].brightPixel[0][0] = j;
				data[1].brightPixel[0][1] = i;
				data[1].brightest = spherePixel2;
			}
			if( sphere3->getPixel( i, j) > spherePixel3 ){
				spherePixel3 = sphere3->getPixel(i, j);
				data[2].brightPixel[0][0] = j;
				data[2].brightPixel[0][1] = i;
				data[2].brightest = spherePixel3;
			}
		}
}

void getDirection( char** argv, vector<Database> & data ){
	ifstream parameters( argv[1] );
	int xCenter = 0;
	int yCenter = 0;
	int radius = 0;

	// Get the parameters from the text file calculated in the previous program
	if( parameters.is_open() ){
		parameters >> xCenter;
		parameters >> yCenter;
		parameters >> radius;
	}
	else{
		cout << "Cannot open " << argv[1] << endl;
		exit( 1 );
	}

	parameters.close();

	for( int i = 0; i < data.size(); i ++ ){
		double xB = data[i].brightPixel[0][0];
		double yB = data[i].brightPixel[0][1];
		double nX = xB - xCenter;
		double nY = yB - yCenter;
		double nZ =  sqrt( ( radius * radius ) - ( nX * nX ) - ( nY * nY ) );	// Formula to get the location of nZ
		double magnitude = sqrt( ( nX * nX) + ( nY * nY) + ( nZ * nZ ) );		// Magnitude of the vector

		/* Direction of each of the pixel in (x, y, z) */
		data[i].brightPixel[0][0] = data[i].brightest * ( nX / magnitude );
		data[i].brightPixel[0][1] = data[i].brightest * ( nY / magnitude );
		data[i].brightPixel[0][2] = data[i].brightest * ( nZ / magnitude );
	}
}

void toFile( char** argv, vector<Database> & data ){

	ofstream file( argv[5]);

	if( file.is_open() ){
		for( int i = 0; i < data.size(); i++ ){
			file << data[i].brightPixel[0][0] << " ";
			file << data[i].brightPixel[0][1] << " ";
			file << data[i].brightPixel[0][2] << endl;
		}
	}
	else{
		cout << "Cannot open " << argv[5] << endl;
		exit( 1 );
	}

	file.close();
}