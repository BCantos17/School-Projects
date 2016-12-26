/*
 * Created by Bryan Cantos for class CSCI 493.69 2015
 */

#include <iostream>
#include "Image.h"
#include <cmath>
#include "Pgm.cpp"
#include <assert.h>

#define PI 3.1415926

using namespace std;

void makeHoughLine( char** argv );

int main( int argc, char **argv ){
	if(argc != 5){
		cout << "Usage: " << argv[0] << " <INPUT_GREY_IMAGE> <INPUT_HOUGH_IMAGE> <THRESHOLD> <OUTPUT_IMAGE>" << endl;
		return 0;
    }

    makeHoughLine( argv );

    return 0;
}

void makeHoughLine( char** argv ){
    Image *grey;
    grey = new Image;
    assert( grey != 0 );

    Image *hough;
    hough = new Image;
    assert( hough != 0 );

    if(readImage(grey, argv[1]) == -1){
        cout << "Can't open file " << argv[ 1 ] << endl;
        exit ( 1 );
    }

    if(readImage(hough, argv[2]) == -1){
        cout << "Can't open file " << argv[ 1 ] << endl;
        exit ( 1 );
    }

    int threshold = atoi(argv[3]);
    int houghRow = hough->getNRows();
    int houghCol = hough->getNCols();
    int greyRow = grey->getNRows();
    int greyCol = grey->getNCols();

    //Go through Hough Transform image to draw line
    for( int i = 0; i < houghRow; i++ )
        for( int j = 0; j < houghCol; j++ )
            //Draw line if accumulator Pixel is greater than or equal to threshold
            if( hough->getPixel(i, j) >= threshold ){

                double angle = j * PI / 180;
                double yIntercept = ( 2 * ( i - houghRow / 2 ) ) / sin( angle );
                double slope = -cos( angle ) / sin( angle );

                //Starting point coordinates
                int x1 = 0;
                int y1 = round( yIntercept );

                //Recalculate if y coordinate is out of bounds
                while( y1 < 0 || y1 >= greyRow ){
                    if( ++x1 >= greyCol )
                        break;
                    y1 = round( slope * x1 + yIntercept );
                }

                //Skip if coordinate are out of bounds
                if( y1 >= greyRow || y1 < 0 || x1 >= greyCol )
                    continue;

                //End point coordinate
                int x2 = greyCol - 1;
                int y2 = round( slope * x2 + yIntercept );

                //Recalculate if y coordinate is out of bounds
                while( y2 >= greyRow || y2 < 0 ){
                    if( --x2 < 0 )
                        break;  
                    y2 = round( slope * x2 + yIntercept );
                }

                //Skip if coordinates are out of bounds
                if( y2 >= greyRow || y2 < 0 || x2 < 0 )
                    continue;

                //Draw line on Grey Scale image
                line(grey, y1, x1, y2, x2, hough->getPixel(i, j) );
            }

    if ( writeImage( grey , argv[4] ) != 0 ){
        cout << "Can't open file " << argv[4] << endl;
        exit ( 1 );
    }

    return;
}