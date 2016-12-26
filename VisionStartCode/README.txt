
Sample code that reads/writes pgm images and that draws lines on the images is provided.

Image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

Pgm.cpp   : Functions to read/write a pgm image file.

Line.cpp :  Functions to draw a line on an image.

ImageDemo.cpp : Sample main() function for testing.

----------------------
To compile in Linux:
----------
 
   make all

To run:
---------

./ImageDemo objects.pgm output.pgm

This will open image objects.pgm, will draw a line on the image, and will save resulting image to file output.pgm

-----------
