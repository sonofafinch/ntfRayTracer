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
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
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
*	getRay
*
*	Returns a subsequent ray based on a previous one
*
*	@param			direction			The previous ray direction
*	@param			normal				The intersected object normal
*	@param			intersection		The point of intersection with the ray/object
*
*	@return								The resulting ray
*/
Ray getRay(Vctr direction, Vctr normal, Vctr intersection)
{

	double refl1 = normal.dot(direction.negate());
	Vctr refl2 = normal.multiply(refl1);
	Vctr refl3 = refl2.add(direction);
	Vctr refl4 = refl3.multiply(2);
	Vctr refl5 = direction.negate().add(refl4);
	Vctr reflectionDirection = refl5.normalize();

	return Ray(intersection, direction);

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

	Color finalColor = frontColor.multiplyHue(lights.at(0).getColor()); //Ambient color

	Ray reflectionRay = getRay(rayPos, frontNormal, intPos);

	std::vector<double> reflectionIntersections;

	for (int i = 0; i < obj.size(); ++i)
	{

		reflectionIntersections.push_back(obj.at(i)->detectIntersection(reflectionRay));

	}

	int reflectedObjectIndex = findClosestObject(reflectionIntersections);

	if (reflectedObjectIndex != -1) //There's an object and potential reflection
	{

		double curIntersection = reflectionIntersections.at(reflectedObjectIndex);

		if (curIntersection > MARGIN)
		{

			Vctr reflectionPosition = intPos.add(reflectionRay.getDirection().multiply(curIntersection));

			Color reflectionColor = getIntersectedColor(reflectionPosition, reflectionRay.getDirection(), obj, reflectedObjectIndex, lights);

			finalColor = finalColor.addHue(reflectionColor);

		}

	}

	for (int i = 1; i < lights.size(); ++i) //First light is always ambient source
	{

		Vctr lightDirection = lights.at(i).getPosition().add(intPos.negate()).normalize();

		float cos = frontNormal.dot(lightDirection); //Lambertian surface proportion

		bool inShadow = false; //Track which points are in shadow and don't need specular highlights

		if (cos > 0)
		{
			Vctr curLightPos = lights.at(i).getPosition(); //Get the light source
			Vctr lightDistance = curLightPos.add(intPos.negate()).normalize(); //Add the distance to the intersection

			Ray shadowRay(intPos, lightDistance); //Ray toward light

			std::vector<double> shadowIntersections;

			for (int j = 0; j < obj.size() && !inShadow; ++j)
			{

				shadowIntersections.push_back(obj.at(j)->detectIntersection(shadowRay)); //Intersection if not in shadow

			}

			for (int k = 0; k < shadowIntersections.size(); ++k)
			{

				if (shadowIntersections.at(k) > MARGIN) //Potential shadow
				{

					if (shadowIntersections.at(k) <= lightDistance.magnitude()) //Too far from source
					{

						inShadow = true;

						break;

					}

				}

				if (!inShadow)
				{
					
					finalColor = finalColor.addHue(frontColor.multiplyHue(lights.at(i).getColor()).scaleHue(cos)); //Directional light with ambient

					//Phong illumination
					double nDotL = frontNormal.dot(lightDirection); //(n * l)
					Vctr nScaleNDotL = frontNormal.multiply(nDotL); //n(n * l)
					Vctr twoN = nScaleNDotL.multiply(2); //2n(n * l)
					Vctr rTerm = twoN.add(lightDirection.negate()); //2n(n * l) - l

					Vctr reflectionVector = rTerm.normalize();

					double specularTerm = reflectionVector.dot(lightDirection);

					if (specularTerm > 0)
					{

						Color curPhong = obj.at(index)->getPhong();

						specularTerm = pow(specularTerm, curPhong.getCharacter());

						Color curLightColor = lights.at(i).getColor();

						// Amb + Diff + ClCp(e * r) ^ p
						finalColor = finalColor.addHue(curLightColor.scaleHue(specularTerm).multiplyHue(curPhong));

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

Color* processScene(int* picDimen, Vctr right, Vctr down, Camera sceneCam, std::vector<Shape*> sceneObjects, std::vector<Light> sceneLights, Color sceneBackground)
{

	int pixCount = picDimen[0] * picDimen[1];
	Color *pixels = new Color[pixCount];
	int curPixel = 0;

	for (int i = 0; i < picDimen[0]; ++i)	//width
	{

		for (int j = 0; j < picDimen[1]; ++j)	//height
		{

			curPixel = j * picDimen[0] + i; //set single dimension array position based on two dimensions

											//create ray

			double xRay = (i + 0.5) / picDimen[0];
			double yRay = ((picDimen[1] - j) + 0.5) / picDimen[1];

			Vctr xComponent = right.multiply(xRay - 0.5);
			Vctr yComponent = down.multiply(yRay - 0.5);

			Vctr rayOrigin = sceneCam.getPosition();
			Vctr rayDirection = sceneCam.getDirection().add(xComponent.add(yComponent)).normalize();

			Ray fromCamera(rayOrigin, rayDirection);

			//send rays out to scene

			std::vector<double> intersections;

			for (int k = 0; k < sceneObjects.size(); ++k)
			{

				intersections.push_back(sceneObjects.at(k)->detectIntersection(fromCamera));

			}

			int frontObject = findClosestObject(intersections);

			if (frontObject == -1)
			{

				pixels[curPixel].setRed(sceneBackground.getRed());
				pixels[curPixel].setGreen(sceneBackground.getGreen());
				pixels[curPixel].setBlue(sceneBackground.getBlue());

			}
			else
			{

				if (intersections.at(frontObject) > MARGIN)
				{

					Vctr intersectionPosition = rayOrigin.add(rayDirection.multiply(intersections.at(frontObject)));

					Color intersectedColor = getIntersectedColor(intersectionPosition, rayDirection, sceneObjects, frontObject, sceneLights);

					pixels[curPixel].setRed(intersectedColor.getRed());
					pixels[curPixel].setGreen(intersectedColor.getGreen());
					pixels[curPixel].setBlue(intersectedColor.getBlue());

				}
			}

		}

	}

	return pixels;

}

int main(int argc, char*argv[])
{

	std::cout << "Ray tracing has started...\n";

	int *picDimen = new int[2]; 	//square image for each scene
	picDimen[0] = 720;
	picDimen[1] = 720;

	//Process Scene 1

	outputProcessing("Scene 1");
	
	const Vctr oneLookAt(0, 0, 0);
	const Vctr oneLookFrom(IDENT_Z.getX(), IDENT_Z.getY(), IDENT_Z.getZ());
	const Vctr oneDirection(IDENT_Z.getX(), IDENT_Z.getY(), -IDENT_Z.getZ());
	const Vctr oneRight = IDENT_Y.cross(oneDirection).negate();
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

	Sphere sphereOne(Vctr(.35, 0, -.1), .05, Color(1, 1, 1, 1), Color(1, 1, 1, 4));
	Sphere sphereTwo(Vctr(.2, 0, -.1), .075, Color(1, 0, 0, 1), Color(.5, 1, .5, 32));
	Sphere sphereThree(Vctr(-.6, 0, 0), .3, Color(0, 1, 0, 1), Color(.5, 1, .5, 32));

	std::vector<Shape*> oneObj;
	oneObj.push_back(dynamic_cast<Shape*>(&sphereOne));
	oneObj.push_back(dynamic_cast<Shape*>(&sphereTwo));
	oneObj.push_back(dynamic_cast<Shape*>(&sphereThree));

	Triangle triangleOne(Vctr(.3, -.3, -.4), Vctr(0, .3, -.1), Vctr(-.3, -.3, .2), Color(0, 0, 1, 1), Color(1, 1, 1, 32));
	Triangle triangleTwo(Vctr(-.2, .1, .1), Vctr(-.2, -.5, .2), Vctr(-.2, .1, -.3), Color(1, 1, 0, 1), Color(1, 1, 1, 4));

	oneObj.push_back(dynamic_cast<Shape*>(&triangleOne));
	oneObj.push_back(dynamic_cast<Shape*>(&triangleTwo));

	Color* sceneOneImage = processScene(picDimen, oneRight, oneDown, oneCam, oneObj, oneLights, oneBG);

	std::string sceneOneFile = "scene1.ppm";
	saveImage(sceneOneFile, picDimen[1], picDimen[0], sceneOneImage);

	delete sceneOneImage;

	outputComplete(sceneOneFile);

	//Set up Scene 2

	outputProcessing("Scene 2");

	std::string sceneTwo = "scene2.ppm";

	const Vctr twoLookAt(0, 0, 0);
	const Vctr twoLookFrom(0, 0, 1.2);
	const Vctr twoDirection = twoLookFrom.negate();
	const Vctr twoRight = IDENT_Y.cross(twoDirection).negate();
	const Vctr twoDown = twoRight.cross(twoDirection);
	const double twoFOV = 55;
	const Camera twoCam(twoLookFrom, twoDirection, twoRight, twoDown, twoFOV);

	const Vctr twoLightPos(IDENT_Y.getX(), IDENT_Y.getY(), IDENT_Y.getZ());
	const Color twoLightColor(1.0, 1.0, 1.0, 1.0);
	const Light twoDirectional(twoLightPos, twoLightColor);

	const Color twoAmbientColor(0.0, 0.0, 0.0, 0.0);
	const Light twoAmbient(Vctr(), twoAmbientColor);

	const Color twoBG(.2, .2, .2, 1);

	const std::vector<Light> twoLights = { twoAmbient, twoDirectional };

	Sphere sphere1(Vctr(0, 0.3, 0), .2, Color(0, 0, 0, 1), Color(.75, .75, .75, .75));

	std::vector<Shape*> twoObj;
	twoObj.push_back(dynamic_cast<Shape*>(&sphere1));

	Triangle triangle1(Vctr(0, -.5, .5), Vctr(1, .5, 0), Vctr(0, -.5, -.5), Color(0, 0, 1, 1), Color(1, 1, 1, 4));
	Triangle triangle2(Vctr(0, -.5, .5), Vctr(0, -.5, -.5), Vctr(-1, .5, 0), Color(1, 1, 0, 1), Color(1, 1, 1, 4));

	twoObj.push_back(dynamic_cast<Shape*>(&triangle1));
	twoObj.push_back(dynamic_cast<Shape*>(&triangle2));

	Color* sceneTwoImage = processScene(picDimen, twoRight, twoDown, twoCam, twoObj, twoLights, twoBG);

	std::string sceneTwoFile = "scene2.ppm";
	saveImage(sceneTwoFile, picDimen[1], picDimen[0], sceneTwoImage);

	outputComplete(sceneTwo);

	//Set up Scene 3

	outputProcessing("Scene 3");

	std::string sceneThree = "scene3.ppm";

	const Vctr threeLookAt(0, 0, 0);
	const Vctr threeLookFrom(1, 1, 1);
	const Vctr threeDirection = threeLookFrom.negate();
	const Vctr threeRight = IDENT_Y.cross(threeDirection).negate();
	const Vctr threeDown = threeRight.cross(threeDirection);
	const double threeFOV = 45;
	const Camera threeCam(threeLookFrom, threeDirection, threeRight, threeDown, threeFOV);

	const Vctr threeLightPos(0, -1, 1);
	const Color threeLightColor(1.0, 1.0, 1.0, 0);
	const Light threeDirectional(threeLightPos, threeLightColor);

	const Color threeAmbientColor(.1, .1, .1, 0);
	const Light threeAmbient(Vctr(), threeAmbientColor);

	const Color threeBG(.2, .2, .2, 0);

	const std::vector<Light> threeLights = { threeAmbient, threeDirectional };

	Sphere sphereA(Vctr(.5, -.5, -2), .1, Color(1, 1, 1, 1), Color(.2, 1, .3, 4));
	Sphere sphereB(Vctr(.2, 0, -.5), .2, Color(1, 0, 0, 1), Color(.1, 1, .5, 32));
	Sphere sphereC(Vctr(-.5, 0, -4), .2, Color(1, 0, .3, 1), Color(.1, 1, .5, 32));
	
	std::vector<Shape*> threeObj;
	threeObj.push_back(dynamic_cast<Shape*>(&sphereA));
	threeObj.push_back(dynamic_cast<Shape*>(&sphereB));
	threeObj.push_back(dynamic_cast<Shape*>(&sphereC));

	Triangle triangleA(Vctr(-.3, -.3, -.4), Vctr(0, .3, -.1), Vctr(-.3, -.3, .2), Color(.5, 0, 1, 1), Color(1, 1, 1, 4));
	Triangle triangleB(Vctr(-.2, .1, .1), Vctr(.2, -.5, .2), Vctr(-.2, .1, -.3), Color(1, .5, 0, 1), Color(1, 1, 1, 32));

	threeObj.push_back(dynamic_cast<Shape*>(&triangleA));
	threeObj.push_back(dynamic_cast<Shape*>(&triangleB));

	Color* sceneThreeImage = processScene(picDimen, threeRight, threeDown, threeCam, threeObj, threeLights, threeBG);

	std::string sceneThreeFile = "scene3.ppm";
	saveImage(sceneThreeFile, picDimen[1], picDimen[0], sceneThreeImage);

	saveImage(sceneThree, picDimen[1], picDimen[0], sceneThreeImage);

	outputComplete(sceneThree);

	system("pause");

	return 0;

}