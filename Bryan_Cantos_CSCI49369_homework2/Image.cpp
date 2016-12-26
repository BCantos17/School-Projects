/* 
** Modified by Bryan Cantos
** Class CSCI 49369
*/

/*
 -- Sample file --
 Source file "Image.C"
*/
#include <cstdio>
#include <cstdlib>
#include <map>
#include "Image.h"
#include <vector>

 using namespace std;

Image::Image(){
    /* initialize image class */
    /* everything is zero...  */
    Ncols=0;
    Nrows=0;
    Ncolors=0;
    image=NULL;
}

Image::Image(const Image &im){
    /* initialize image class */
    /* Copy from im  */
  setSize(im.getNRows(), im.getNCols());
  setColors(im.getColors());
  int i,j;
  for (i=0; i<getNRows(); ++i)
    for (j=0; j<getNCols(); ++j){
      setPixel(i,j, im.getPixel(i,j));
    }
}


Image::~Image(){
    int i;
    if (image) {
  for (i=0; i<Nrows; i++)
      free( image[i] );
  free(image);
    }
}
/*
 allocates space for an rows x columns image.

 returns : -2 if rows or columns <=0
           -1 if cannot allocate space
            rows * columns if success

*/

int
Image::setSize(int rows, int columns)
{
    int i;
    if (rows<=0 || columns <=0){
  printf("setSize: rows, columns must be positive\n");
  return -2;
    }

    if ( (image=(int **)malloc(sizeof (int *) * rows))==NULL ){
  printf("setSize: can't allocate space\n");
  return -1;
     }

    for (i=0; i<rows; i++) {
  if ( (image[i]=(int *)malloc(sizeof(int) * columns))==NULL){
      printf("setSize: can't allocate space\n");
      return -1;
  }
    }

    Nrows=rows;
    Ncols=columns;

    return rows*columns;
}


/*
 Sets the number of gray - levels
*/
int
Image::setColors(int colors){
  Ncolors=colors;
  return Ncolors;
}

/*
 Returns pixel i,j
 If image is "empty" return -1.
*/
int
Image::getPixel(int i, int j)const{
   if ( !image ) {
       printf("getPixel: read pixel from an empty image\n");
       return -1;
     }
  if (i<0 || i>Nrows || j<0 || j>Ncols){
//         error_msg("getPixel: out of image");
        return -1;
       }
       else
          return image[i][j];
}

/*
 set pixel i, j
 return -1 if error.
*/
int
 Image::setPixel(int i, int j, int color){
  if ( !image ) {
       printf("setPixel: write pixel to an empty image");
       return 0;
     }

 if ( i<0 || i>Nrows || j<0 || j>Ncols ){
 //  error_msg("Image::setPixel -> Out of boundaries\n");
   return -1;
 }
 image[i][j]=color;
 return color;
}

/*
 Converts binary image to label image
*/
void 
 Image::toLabel( const Image *binary ) {
  int rows = binary->getNRows(); 
  int cols = binary->getNCols();
  int newLabel = 0; 
  DisjSets table((rows * cols)/2);
  map<int, int> size;
  this->setSize( rows, cols );
  vector<int> ordered;

  // Goes through the image pixel by pixel
  for ( int i = 0; i < rows; i++ )
    for ( int j = 0; j < cols; j++ ){
      this->setPixel( i, j, 0 );
      if( binary->getPixel( i, j ) == 1 ){
        this->checkTopLeft( binary, i, j );
        this->checkTop( binary, i, j, newLabel );
        this->checkLeft( binary, i, j, newLabel );
        this->checkAll( binary, i, j, newLabel );
        this->notEqual(binary, i, j, newLabel, table );
      }
    }

  // Goes through image again to set each pixel to their proper equivalent number
  // Also finds the number of objects in the image
  for ( int i = 0; i < rows; i++ )
    for ( int j = 0; j < cols; j++ ){
      if( this->getPixel(i , j) != 0){
        if( size.find( table.find( this->getPixel( i , j ) ) ) == size.end() ){
          size[table.find( this->getPixel( i , j ) )];
          ordered.push_back( table.find( this->getPixel( i , j ) ) );
        }
        for( int k = 0; k < ordered.size(); k++ ){
          if( ordered[ k ] == table.find( this->getPixel( i, j ) ) )
            this->setPixel( i , j, k + 1 );
        }
      }
    }
  // Set amounts of color base on number of objects
  this->setColors( size.size() );
}

/*
 Checks top left pixel
 If Label, current pixel is set to top left pixel
 If pixel is "empty" return.
*/
void 
 Image::checkTopLeft( const Image *binary, int i, int j ){
  if( binary->getPixel( i - 1, j - 1 ) == -1 )
    return;

  if( binary->getPixel( i - 1, j - 1 ) != 0 )
    this->setPixel( i, j, this->getPixel( i - 1, j - 1 ));
 }

/*
 Checks top pixel
 If Label, current pixel is set to top pixel
 If pixel is "empty" return.
*/
void 
  Image::checkTop( const Image *binary, int i, int j, int & newLabel ){
  if( binary->getPixel( i - 1, j ) == -1 )
    return;

  if( binary->getPixel( i - 1, j ) != 0 )
    this->setPixel( i, j, this->getPixel( i - 1, j ));
  }

/*
 Checks left pixel
 If Label, current pixel is set to left pixel
 If pixel is "empty" return.
*/
void 
 Image::checkLeft( const Image *binary, int i, int j, int & newLabel ){
  if( binary->getPixel( i, j - 1) == -1 )
    return;

  if( binary->getPixel( i, j - 1 ) != 0 )
    this->setPixel( i, j, this->getPixel( i, j - 1 ));
 }

/*
 Checks surrounding pixels
 If all are not label, add new label to current pixel
*/
void 
 Image::checkAll( const Image *binary, int i, int j, int & newLabel ){
  if( binary->getPixel( i, j - 1 )      == 0     &&
      binary->getPixel( i - 1, j - 1 )  == 0     &&
      binary->getPixel( i - 1, j )      == 0     ){

    newLabel++;
    this->setPixel( i, j, newLabel );
  }
}

/*
 Checks top and left
 If they are not equal, merge into union-set for evaluation later
 If either top or left pixel are not label, return
*/
 void 
  Image::notEqual( const Image *binary, int i, int j, int & newLabel, DisjSets & table ){
    if( binary->getPixel( i, j - 1)   == 0                          ||
        binary->getPixel( i - 1, j)   == 0                          ||
        this->getPixel( i, j - 1)     == this->getPixel( i - 1, j) )
      return;

    table.unionSets( this->getPixel(i - 1, j), this->getPixel(i, j - 1) );
    this->setPixel( i, j, this->getPixel( i, j - 1) );
  }
