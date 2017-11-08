/*
*	@file Scene.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Scene.h"

Scene::Scene()
{
	
	camera = Camera();
	shapes = {};
	lights = {};
	background = Color(0, 0, 0, 1);

}
Scene::Scene(Camera camera, std::vector<Shape*> shapes, std::vector<Light> lights, Color background)
{

	this->camera = camera;
	this->shapes = shapes;
	this->lights = lights;
	this->background = background;

}

Camera Scene::getCamera() const
{

	return camera;

}

std::vector<Shape*> Scene::getShapes() const
{

	return shapes;

}

std::vector<Light> Scene::getLights() const
{

	return lights;

}

Color Scene::getBackground() const
{

	return background;

}

Color* Scene::processScene(int* dimensions) const
{

	int pixCount = dimensions[0] * dimensions[1];
	Color *pixels = new Color[pixCount];
	int curPixel = 0;

	for (int i = 0; i < dimensions[0]; ++i)	//width
	{

		for (int j = 0; j < dimensions[1]; ++j)	//height
		{

			curPixel = j * dimensions[0] + i; //set single dimension array position based on two dimensions

			//create ray

			double xRay = (i + 0.5) / dimensions[0];
			double yRay = ((dimensions[1] - j) + 0.5) / dimensions[1];

			Vctr xComponent = camera.getRight().multiply(xRay - 0.5);
			Vctr yComponent = camera.getDown().multiply(yRay - 0.5);

			Vctr rayOrigin = camera.getPosition();
			Vctr rayDirection = camera.getDirection().add(xComponent.add(yComponent)).normalize();

			Ray fromCamera(rayOrigin, rayDirection);

			//send rays out to scene

			std::vector<double> intersections;

			for (int k = 0; k < shapes.size(); ++k)
			{

				Shape *curShape = shapes.at(k);

				intersections.push_back(curShape->detectIntersection(fromCamera));

			}

			int frontObject = findClosestObject(intersections);

			if (frontObject == -1)
			{

				pixels[curPixel].setRed(background.getRed());
				pixels[curPixel].setGreen(background.getGreen());
				pixels[curPixel].setBlue(background.getBlue());

			}
			else
			{

				Shape frontShape = *shapes.at(frontObject);

				Color found = frontShape.getColor();

				pixels[curPixel].setRed(found.getRed());
				pixels[curPixel].setGreen(found.getGreen());
				pixels[curPixel].setBlue(found.getBlue());

			}

		}

	}

	return pixels;

}