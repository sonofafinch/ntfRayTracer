/*
*	@file Scene.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Shape.h"

/**
*	Scene Class
*
*	Stores shapes and a background color.
*/
class Scene
{

public:

	Scene();
	Scene(Camera, std::vector<Shape*>, std::vector<Light>, Color);

	Camera getCamera() const;
	std::vector<Shape*> getShapes() const;
	std::vector<Light> getLights() const;
	Color getBackground() const;
	Color* processScene(int* dimensions) const;

private:

	int Scene::findClosestObject(std::vector<double> intersections) const
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

			int index = 0;
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

	Camera camera;
	std::vector<Shape*> shapes;
	std::vector<Light> lights;
	Color background;

};

#endif