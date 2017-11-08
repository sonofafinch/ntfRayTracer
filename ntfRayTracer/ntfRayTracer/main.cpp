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
#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Vctr.h"

Vctr IDENT_X(1, 0, 0);	//
Vctr IDENT_Y(0, 1, 0);	//Used to get right direction
Vctr IDENT_Z(0, 0, 1);	//Used to set camera origin

double MARGIN = 0.000001;

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

/*
*	findClosestObject
*
*	Takes all of the intersections of a ray and determines which is closest to the camera.
*
*	@param			intersections			The detected points where objects and the ray meet
*
*	@return									The index of the closest intersection
*/
int findClosestObject(std::vector<double> intersections)
{

	if (intersections.size() == 0)
	{

		return -1; //nothing hit

	}
	else if (intersections.size() == 1)
	{

		if (intersections.at(0) > 0)
		{

			return 0; //Index of intersection

		}
		else
		{

			return -1; //Behind

		}

	}
	else
	{

		int index = 0; //One must be valid, so track which
		double maxValue = 0;

		for (int i = 0; i < intersections.size(); ++i)
		{

			if (maxValue < intersections.at(i))
			{

				maxValue = intersections.at(i);

			}

		}

		if (maxValue > 0)
		{

			for (int j = 0; j < intersections.size(); ++j)
			{

				if (intersections.at(j) > 0 && intersections.at(j) <= maxValue)
				{

					maxValue = intersections.at(j);
					index = j;

				}

			}

		return index;

		}
		else
		{

			return -1; //behind

		}

	}

}

/*
*	getIntersectedColor
*
*	Takes an intersecton point and object, along with light sources, to compute the final point object
*
*	@param			intPos			The point of intersection
*	@param			rayPos			The ray's direction
*	@param			obj				The scene objects
*	@param			index			The index of the closest object
*	@param			lights			The lights in the scene
*
*	@return							The final color at the intersection point
*/
Color getIntersectedColor(Vctr intPos, Vctr rayPos, std::vector<Shape*> obj, int index, std::vector<Light> lights)
{

	Color frontColor = obj.at(index)->getColor();
	Vctr frontNormal = obj.at(index)->getNormal(intPos);

	//Ambient color
	Color finalColor = frontColor.multiplyHue(lights.at(0).getColor());

	//First light is always ambient source
	for (int i = 1; i < lights.size(); ++i)
	{

		Vctr lightDirection = lights.at(i).getPosition().add(intPos.negate()).normalize();

		float cos = frontNormal.dot(lightDirection);

		bool inShadow = false;

		if (cos > 0)
		{

			Vctr lightDistance = lights.at(i).getPosition().add(intPos.negate()).normalize();

			//Ray toward light
			Ray shadowRay(intPos, lights.at(i).getPosition().add(intPos.negate()).normalize());

			std::vector<double> tier2Intersections;

			for (int j = 0; j < obj.size() && !inShadow; ++j)
			{

				tier2Intersections.push_back(obj.at(j)->detectIntersection(shadowRay));

			}

			for (int k = 0; k < tier2Intersections.size(); ++k)
			{

				if (tier2Intersections.at(k) > MARGIN)
				{

					if (tier2Intersections.at(k) <= lightDistance.magnitude())
					{

						inShadow = true;

					}

					break; //

				}

				if (!inShadow)
				{
					//Directional light with ambient
					finalColor = finalColor.addHue(frontColor.multiplyHue(lights.at(i).getColor()).scaleHue(cos));

					if (frontColor.getCharacter() > 0 && frontColor.getCharacter() <= 1)
					{

						double normalDotIntersection = frontNormal.dot(rayPos.negate());
						Vctr normalMult = frontNormal.multiply(normalDotIntersection);
						Vctr normalAdd = normalMult.add(rayPos);
						Vctr normalAddMult = normalAdd.multiply(2); //
						Vctr normalAMA = rayPos.negate().add(normalAddMult);

						Vctr reflectionVector = normalAMA.normalize();

						double specular = reflectionVector.dot(lightDirection);

						if (specular > 0)
						{

							specular = pow(specular, 10);

							Color curLightColor = lights.at(i).getColor();

							finalColor = finalColor.addHue(curLightColor.scaleHue(specular * frontColor.getCharacter()));

						}


					}

				}

			}

		}

	}

	return finalColor.limit();

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

	//Process Scene 1

	outputProcessing("Scene 1");
	
	const Vctr oneLookAt(0, 0, 0);
	const Vctr oneLookFrom(IDENT_Z.getX(), IDENT_Z.getY(), IDENT_Z.getZ());
	const Vctr oneDirection(IDENT_Z.getX(), IDENT_Z.getY(), -IDENT_Z.getZ());
	const Vctr oneRight = IDENT_Y.cross(oneDirection);
	const Vctr oneDown = oneRight.cross(oneDirection);
	const double oneFOV = 56;
	const Camera oneCam(oneLookFrom, oneDirection, oneRight, oneDown, oneFOV);

	const Vctr oneLightPos(IDENT_X.getX(), IDENT_X.getY(), IDENT_X.getZ());
	const Color oneLightColor(1.0, 1.0, 1.0, 0);
	const Light oneDirectional(oneLightPos, oneLightColor);

	const Color oneAmbientColor(.2, .2, .2, 0);
	const Light oneAmbient(Vctr(), oneAmbientColor);

	const Color oneBG(.2, .2, .2, 0);

	const std::vector<Light> oneLights = { oneAmbient, oneDirectional };

	Sphere sphereOne(Vctr(.35, 0, -.1), .05, Color(1, 1, 1, 0));
	Sphere sphereTwo(Vctr(.2, 0, -.1), .075, Color(1, 0, 0, 0));
	Sphere sphereThree(Vctr(-.6, 0, 0), .3, Color(0, 1, 0, 0));

	std::vector<Shape*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<Shape*>(&sphereOne));
	sceneObjects.push_back(dynamic_cast<Shape*>(&sphereTwo));
	sceneObjects.push_back(dynamic_cast<Shape*>(&sphereThree));

	//const Scene one = Scene(oneCam, sceneObjects, oneLights, oneBG);

	int pixCount = picDimen[0] * picDimen[1];
	Color *pixels = new Color[pixCount];
	int curPixel = 0;

	//Camera cam = one.getCamera();

	for (int i = 0; i < picDimen[0]; ++i)	//width
	{

		for (int j = 0; j < picDimen[1]; ++j)	//height
		{

			curPixel = j * picDimen[0] + i; //set single dimension array position based on two dimensions

											  //create ray

			double xRay = (i + 0.5) / picDimen[0];
			double yRay = ((picDimen[1] - j) + 0.5) / picDimen[1];

			Vctr xComponent = oneRight.multiply(xRay - 0.5);
			Vctr yComponent = oneDown.multiply(yRay - 0.5);

			Vctr rayOrigin = oneCam.getPosition();
			Vctr rayDirection = oneCam.getDirection().add(xComponent.add(yComponent)).normalize();

			Ray fromCamera(rayOrigin, rayDirection);

			//send rays out to scene

			std::vector<double> intersections;

			//std::vector<Shape> objects = one.getShapes();

			for (int k = 0; k < sceneObjects.size(); ++k)
			{

				intersections.push_back(sceneObjects.at(k)->detectIntersection(fromCamera));

			}

			int frontObject = findClosestObject(intersections);

			if (frontObject == -1)
			{

				//Color BG = one.getBackground();

				pixels[curPixel].setRed(oneBG.getRed());
				pixels[curPixel].setGreen(oneBG.getGreen());
				pixels[curPixel].setBlue(oneBG.getBlue());

			}
			else
			{

				if (intersections.at(frontObject) > MARGIN)
				{

					Vctr intersectionPosition = rayOrigin.add(rayDirection.multiply(intersections.at(frontObject)));

					Color intersectedColor = getIntersectedColor(intersectionPosition, rayDirection, sceneObjects, frontObject, oneLights);

					pixels[curPixel].setRed(intersectedColor.getRed());
					pixels[curPixel].setGreen(intersectedColor.getGreen());
					pixels[curPixel].setBlue(intersectedColor.getBlue());

				}
			}

		}

	}

	std::string sceneOneFile = "scene1.ppm";
	saveImage(sceneOneFile, picDimen[1], picDimen[0], pixels);
	outputComplete(sceneOneFile);

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