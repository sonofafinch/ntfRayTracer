/*
*	@file main.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include <cmath>
#include <limits>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Camera.h"
#include "Ray.h"
#include "Vctr.h"

/**
*	pixColor
*
*	Structure for storing the color values of a pixel.
*/
struct pixColor
{

	double red;
	double green;
	double blue;

};

/**
*	saveImage
*
*	Takes in a user-specified file name, image width and height, as well as the
*	color data for the image's pixels, in order to create a PPM image.
*
*	@param		fileName			The name of the file to create
*	@param		width				The image width
*	@param		height				The image height
*	@param		values				The color values for all of the image's pixels
*/
void saveImage(std::string fileName, int width, int height, pixColor *values)
{

	FILE *toSave;
	std::stringstream imageData;
	imageData << "P3\n" << width << " " << height << "\n255\n"; //Save header

	int pixCount = width * height;
	int rgbSpace = 255;

	for (int i = 0; i < pixCount; ++i)
	{

		pixColor curColor = values[i];

		imageData << "\n" << (curColor.red * rgbSpace) << "\n" <<
			(curColor.green * rgbSpace) << "\n" << (curColor.blue * rgbSpace);

	} //Output pixel colors as string values

	std::ofstream imageFile(fileName); //Create a new file

	imageFile << imageData.str(); //Save the image data to the file

	imageFile.close(); //Finalize

}


int main(int argc, char*argv[])
{

	std::cout << "Render started...\n";

	int picDimen = 516; 	//square image
	int pixCount = picDimen * picDimen;
	pixColor *pixels = new pixColor[pixCount];
	int curPixel = 0;

	//Identity Vectors
	Vctr identX(1, 0, 0);
	Vctr identY(0, 1, 0);
	Vctr identZ(0, 0, 1);



	for (int i = 0; i < picDimen; ++i)	//width
	{

		for (int j = 0; j < picDimen; ++j)	//height
		{

			curPixel = j * picDimen + i; //set single dimension array position based on two dimensions

			pixels[curPixel].red = .182;
			pixels[curPixel].green = .23;
			pixels[curPixel].blue = .95;

		}

	}

	saveImage("raytrace.ppm", picDimen, picDimen, pixels);

	return 0;

}