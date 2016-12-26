/* 
** Created by Bryan Cantos
** Class CSCI 49369
*/

#include <iostream>
#include <assert.h>
#include "Image.h"
#include <vector>
#include <math.h>
#include <fstream>
#include "Pgm.cpp"

#define PI 3.14159265

using namespace std;

struct Database{
	Datebase();
	int rowSum = 0;
	int colSum = 0;
	long long aPrime = 0;
	long long bPrime = 0;
	long long cPrime = 0;
	long long a = 0;
	long long b = 0;
	long long c = 0;
	int totalPixel = 0;
	double centerRow = 0;
	double centerCol = 0;
	long double thetaMin = 0;
	long double thetaMax = 0;
	long double PMin = 0;
	long double angle = 0;
	long long EMin = 0;
	long long EMax = 0;
};

void objectData( Image * label, vector<Database> & objects );
void insertDatabase( vector<Database> & objects, string dataName );
void drawLine( Image * imageLine, vector<Database> & objects );

int main( int argc, char *argv[] ) {

	if( argc != 4 ) {
		printf( "Usage: %s file1 file2 file3\n", argv[0] );
		exit( 1 );
	}

	vector<Database> objects;
	vector<int> numOfLabels;
	string dataName( argv[2] );

	Image *label;
	label = new Image;
	assert( label != 0 );

	Image *imageLine;
	imageLine = new Image;
	assert( imageLine != 0 );

	if( readImage( label, argv[1] ) != 0 ) {
		cout << "Can't open file" << endl;
		exit( 1 );
	}

	objectData( label, objects );
	insertDatabase( objects, dataName );

	imageLine->setSize( label->getNRows(), label->getNCols() );
	imageLine->setColors( 1 ); 

	drawLine( imageLine, objects );

	if ( writeImage( imageLine , argv[3] ) != 0 ){
		printf( "Can't write to file %s\n", argv[3] );
		exit ( 1 );
	}

	return 0;
}

void objectData( Image * label, vector<Database> & objects ) {
	int rows = label->getNRows();
	int cols = label->getNCols();
	map<int, int> numbers;

	objects.resize(label->getColors());

	// Commutes the sum of the rows, sum of the columns, the primes of A, B and C and the area of the object
	for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ ){
			if( label->getPixel( i, j ) != 0){
				objects[ label->getPixel( i, j ) - 1 ].rowSum += i;
				objects[ label->getPixel( i, j ) - 1 ].colSum += j;
				objects[ label->getPixel( i, j ) - 1 ].aPrime += (j * j);
				objects[ label->getPixel( i, j ) - 1 ].bPrime += (2 * (i * j) );
				objects[ label->getPixel( i, j ) - 1 ].cPrime += (i * i);
				objects[ label->getPixel( i, j ) - 1 ].totalPixel ++;
			}
		}

	//Computes the Center Col, Center Row, a, b , c, a', b', c', theta min and max, PMin, E min and max
	for( int i = 0; i < objects.size(); i++ ){
		objects[i].centerCol = objects[i].colSum / objects[i].totalPixel;
		objects[i].centerRow = objects[i].rowSum / objects[i].totalPixel;
		objects[i].a = objects[i].aPrime - ( objects[i].centerCol * objects[i].centerCol * objects[i].totalPixel );
		objects[i].b = objects[i].bPrime - ( 2 * objects[i].centerCol * objects[i].centerRow * objects[i].totalPixel );
		objects[i].c = objects[i].cPrime - ( objects[i].centerRow * objects[i].centerRow * objects[i].totalPixel );
		objects[i].angle = atan2(objects[i].b, objects[i].a - objects[i].c);
		objects[i].thetaMin = objects[i].angle / 2;
		objects[i].thetaMax = (PI/2) + objects[i].thetaMin;
		objects[i].PMin = ( -1 * objects[i].centerCol * cos( objects[i].thetaMin ) ) + ( objects[i].centerRow * objects[i].thetaMin );
		objects[i].EMin = ( objects[i].a * pow( sin( objects[i].thetaMin ), 2) ) - ( objects[i].b * cos( objects[i].thetaMin ) * sin( objects[i].thetaMin  ) ) + ( objects[i].c * pow( cos( objects[i].thetaMin ), 2) );
		objects[i].EMax = ( objects[i].a * pow( sin( objects[i].thetaMax ), 2) ) - ( objects[i].b * cos( objects[i].thetaMax ) * sin( objects[i].thetaMax  ) ) + ( objects[i].c * pow( cos( objects[i].thetaMax ), 2) );
	}
}

void insertDatabase( vector<Database> & objects, string dataName ){

	ofstream file( dataName );

	// inserts data from the Database to Database.txt
	for( int i = 0; i < objects.size(); i++ ){
		file << i + 1 << " ";
		file << objects[i].rowSum << " ";
		file << objects[i].colSum << " ";
		file << objects[i].EMin << " ";
		file << objects[i].thetaMin * 180 / PI << endl;
	}

	file.close();
}

void drawLine( Image * imageLine, vector<Database> & objects ){

	for( int i = 0; i < imageLine->getNRows(); i++ )
		for( int j = 0; j < imageLine->getNCols(); j++ )
			imageLine->setPixel( i, j, 0 );

	for(int i = 0; i < objects.size(); ++i){
		// Sets up path for the line
		pair <double, double> path( cos( objects[i].thetaMin * 2 ), sin( objects[i].thetaMin * 2 ) );
		// Draw the line
		line( imageLine, (int)objects[i].rowSum, (int)objects[i].colSum, (int)( objects[i].rowSum + ( path.second * 50)), (int)( objects[i].colSum + ( path.first * 50 ) ), 1);
	}
}