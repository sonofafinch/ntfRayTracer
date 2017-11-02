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
#include "Color.h"
#include "Light.h"
#include "Ray.h"
#include "Vctr.h"

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
void saveImage(std::string fileName, int width, int height, Color *values)
{

	FILE *toSave;
	std::stringstream imageData;
	imageData << "P3\n" << width << " " << height << "\n255\n"; //Save header

	int pixCount = width * height;
	int rgbSpace = 255;

	for (int i = 0; i < pixCount; ++i)
	{

		Color curColor = values[i];

		imageData << "\n" << (curColor.getRed() * rgbSpace) << "\n" <<
			(curColor.getGreen() * rgbSpace) << "\n" << (curColor.getBlue() * rgbSpace);

	} //Output pixel colors as string values

	std::ofstream imageFile(fileName); //Create a new file

	imageFile << imageData.str(); //Save the image data to the file

	imageFile.close(); //Finalize

}

Color* processImage(Camera sceneCam, Light *sceneLights, Color background, int *dimensions)
{

	int pixCount = dimensions[0] * dimensions[1];
	Color *pixels = new Color[pixCount];
	int curPixel = 0;

		for (int i = 0; i < dimensions[1]; ++i)	//width
		{

			for (int j = 0; j < dimensions[2]; ++j)	//height
			{

				curPixel = j * dimensions[1] + i; //set single dimension array position based on two dimensions

				pixels[curPixel].setRed(background.getRed());
				pixels[curPixel].setGreen(background.getGreen());
				pixels[curPixel].setBlue(background.getBlue());

			}

		}

		return pixels;

}

void outputProcessing(std::string sceneName)
{

	std::cout << "Processing " + sceneName + ". Please wait.\n";

}

void outputComplete(std::string fileName)
{

	std::cout << "Ray tracing complete. Image saved as " + fileName + ".\n";

}

int main(int argc, char*argv[])
{

	std::cout << "Ray tracing has started...\n";

	int *picDimen = new int[2]; 	//square image for each scene
	picDimen[0] = 516;
	picDimen[1] = 516;

	//Identity Vectors
	Vctr identX(1, 0, 0);
	Vctr identY(0, 1, 0);
	Vctr identZ(0, 0, 1);

	//Set up Scene 1

	outputProcessing("Scene 1");

	Vctr oneLookAt(0, 0, 0);
	Vctr oneLookFrom(0, 0, 1);
	Vctr oneDirection = oneLookFrom.add(oneLookAt.negate()).negate().normalize();
	Vctr oneRight = identY.cross(oneDirection).normalize();
	Vctr oneDown = oneRight.cross(oneDirection);
	double oneFOV = 56;
	Camera oneCam(oneLookFrom, oneDirection, oneRight, oneDown, oneFOV);

	Vctr oneLightPos(1, 0, 0);
	Vctr oneLightColor(1, 1, 1);
	Light oneDirectional(oneLightPos, oneLightColor);

	Vctr oneAmbientColor(.2, .2, .2);
	Light oneAmbient(Vctr(), oneAmbientColor);

	Color oneBG(.2, .2, .2, 1.0);

	Light *lights = new Light[2];
	lights[0] = oneDirectional;
	lights[1] = oneAmbient;

	objColor *imageData = processImage(oneCam, lights, oneBG, picDimen);
	std::string sceneOne = "scene1.ppm";
	saveImage(sceneOne, picDimen[1], picDimen[0], imageData);
	outputComplete(sceneOne);

	/*

	//Set up Scene 2

	outputProcessing("Scene 2");

	std::string sceneTwo = "scene2.ppm";

	saveImage(sceneOne, picDimen[1], picDimen[0], imageData);

	outputComplete(sceneTwo);

	//Set up Scene 3

	outputProcessing("Scene 3");

	std::string sceneThree = "scene3.ppm";

	saveImage(sceneOne, picDimen[1], picDimen[0], imageData);

	outputComplete(sceneThree);

	*/

	system("pause");

	return 0;

}