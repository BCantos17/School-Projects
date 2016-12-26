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
#include <climits>

using namespace std;

struct Database{
	Datebase();
	double matrixS[3][3];
	double inverseS[3][3];
};

void inverse( char **argv, Database &data );
void surfaceAlbedo( char **argv, Database & data );

int main( int argc, char **argv ) {

	if( argc != 7 ) {
		cout << "Usage: " << argv[0] << " <INPUT_DIRECTION_FILE> <IMAGE1> <IMAGE2> <IMAGE3> <THERSHOLD> <OUTPUT>" << endl;
		exit( 1 );
	}

	Database data;

	inverse 		( argv, data );		// Get the inverse of the matrix of the text file calculated from the previous program
	surfaceAlbedo	( argv, data );		// Draw the surface albedo of the matrix

	return 0;
}

void inverse( char **argv, Database &data ){
	ifstream directions( argv[ 1 ] );

	double a, b, c, d, e, f, g, h, i;

	// Get the matrix from the text file
	if( directions.is_open() ){
		directions >> data.matrixS[0][0];
		a = data.matrixS[0][0];
		directions >> data.matrixS[0][1];
		b = data.matrixS[0][1];
		directions >> data.matrixS[0][2];
		c = data.matrixS[0][2];
		directions >> data.matrixS[1][0];
		d = data.matrixS[1][0];
		directions >> data.matrixS[1][1];
		e = data.matrixS[1][1];
		directions >> data.matrixS[1][2];
		f = data.matrixS[1][2];
		directions >> data.matrixS[2][0];
		g = data.matrixS[2][0];
		directions >> data.matrixS[2][1];
		h = data.matrixS[2][1];
		directions >> data.matrixS[2][2];
		i = data.matrixS[2][2];
	}
	else{
		cout << "Cannot open " << argv[1] << endl;
		exit( 1 );
	}

	directions.close();

	/* Calculate the inverse of the matrix */

	// Switches the order of the matrix and finds the cooresponding inversion
	int A = ( ( e * i ) - ( f * h ) );
	int D = ( -1 * ( ( b * i ) - ( c * h ) ) );
	int G = ( ( b * f ) - ( c * e ) );
	int B = ( -1 * ( ( d * i ) - ( f * g ) ) );
	int E = ( ( a * i ) - ( c * g ) );
	int H = ( -1* ( ( a * f ) - ( c * d ) ) );
	int C = ( ( d * h ) - ( e * g ) );
	int F = ( -1 * ( ( a * h ) - ( b * g ) ) );
	int I = ( ( a * e ) - ( b * d ) );

	// Determinant of the matrix
	double det = ( a*A ) + ( b*B ) + ( c*C );
	double inverseDet = 1/det;

	// Final step of inversion of a matrix, multiply each location by the inverse determinant
	data.inverseS[0][0] = A * inverseDet;
	data.inverseS[0][1] = D * inverseDet;
	data.inverseS[0][2] = G * inverseDet;
	data.inverseS[1][0] = B * inverseDet;
	data.inverseS[1][1] = E * inverseDet;
	data.inverseS[1][2] = H * inverseDet;
	data.inverseS[2][0] = C * inverseDet;
	data.inverseS[2][1] = F * inverseDet;
	data.inverseS[2][2] = I * inverseDet;
}

void surfaceAlbedo( char **argv, Database & data ){

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
	int thershold = atoi( argv[ 5 ] );		// Thershold set by user

	int albedo[rows][cols];					// The pixel of the surface albedo image
	double minimum = 0;
	double maximum = INT_MAX;

	for( int i = 0; i < rows; i++ ){
		for( int j = 0; j < cols; j++ ){

			//  If all three images have a pixel with a greater value than the thershold, continue woth calculations
			if( sphere1->getPixel( i, j ) >= thershold && sphere2->getPixel( i, j ) >= thershold && sphere3->getPixel( i, j ) >= thershold ){


				vector<double> N(3);	// vector, format in (x, y, z), used for finding the magnitude
				vector<double> n(2);	// vector, format in (x, y) used for setting the location of where to draw the needles
				double magnitudeN;

				/* multiplying a 3 x 3 matrix with a 3 x 1 vector, the inverse of the direction matrix with the current pixels of the images */
				N[0] = ( data.inverseS[0][0] * sphere1->getPixel(i, j) ) + ( data.inverseS[0][1] * sphere2->getPixel(i,j) ) + ( data.inverseS[0][2] * sphere3->getPixel(i,j) );
				N[1] = ( data.inverseS[1][0] * sphere1->getPixel(i, j) ) + ( data.inverseS[1][1] * sphere2->getPixel(i,j) ) + ( data.inverseS[1][2] * sphere3->getPixel(i,j) );
				N[2] = ( data.inverseS[2][0] * sphere1->getPixel(i, j) ) + ( data.inverseS[2][1] * sphere2->getPixel(i,j) ) + ( data.inverseS[2][2] * sphere3->getPixel(i,j) );

				magnitudeN = sqrt( N[0]*N[0] + N[1]*N[1] + N[2]*N[2] );

				albedo[i][j] = (int)round( magnitudeN );

				/* Looking for the highest magnitude */
				if( magnitudeN > minimum )
					minimum = magnitudeN;
				else if( magnitudeN < maximum )
                	maximum = magnitudeN;

                sphere1->setPixel( i, j, round( magnitudeN * thershold ) );
			}
			else
				sphere1->setPixel( i, j, 0 );
		}
	}

	double magnitude = sqrt(  ( minimum * minimum ) - ( maximum * maximum ) );

	for( int i = 0; i < rows; i++ ){
		for( int j = 0; j < cols; j++ ){
			if( albedo[i][j] != 0 )
				sphere1->setPixel( i, j, round( 255 * ( ( albedo[i][j] - magnitude ) / minimum ) ) );
			else
				sphere1->setPixel( i, j, 0 );
		}
	}

	if ( writeImage( sphere1 , argv[6] ) != 0 ){
		cout << "Can't open file " << argv[ 6 ] << endl;
		exit ( 1 );
	}
}