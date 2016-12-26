#include "Image.h"
#include <stdio.h>
#include <assert.h>
int
main(int argc, char **argv){

	if (argc!=3) {
		printf("Usage: %s file1 file2\n", argv[0]);
		return 0;
	}
	Image *im;
	im=new Image;
	assert(im!=0);
	if (readImage(im, argv[1])!=0) {
		printf("Can't open file %s\n", argv[1]);
		return 0;
	}
	line(im, 0,0, 100,100,0); //color 0

	if (writeImage(im, argv[2])!=0){
		printf("Can't write to file %s\n", argv[2]);
		return 0;
	}
}
