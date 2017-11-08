/*
*	@file Sphere.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Sphere.h"

Sphere::Sphere()
{

	center = Vctr();
	radius = 1.0;
	color = Color();

}
Sphere::Sphere(Vctr center, double radius, Color color)
{

	this->center = center;
	this->radius = radius;
	this->color = color;

}

Vctr Sphere::getPosition() const
{

	return center;

}

double Sphere::getRadius() const
{

	return radius;

}

Color Sphere::getColor() const
{

	return color;

}

Vctr Sphere::getNormal(Vctr position) const
{

	Vctr normal = position.add(center.negate()).normalize();
	return normal;

}

double Sphere::detectIntersection(Ray curRay) const
{

	Vctr rayOrigin = curRay.getOrigin();
	double rayOriginX = rayOrigin.getX();
	double rayOriginY = rayOrigin.getY();
	double rayOriginZ = rayOrigin.getZ();

	Vctr rayDirection = curRay.getDirection();
	double rayDirectionX = rayDirection.getX();
	double rayDirectionY = rayDirection.getY();
	double rayDirectionZ = rayDirection.getZ();

	double sphereLocationX = center.getX();
	double sphereLocationY = center.getY();
	double sphereLocationZ = center.getZ();

	double varA = 1;
	double varB = (2 * (((rayOriginX - sphereLocationX) * rayDirectionX) +
						((rayOriginY - sphereLocationY) * rayDirectionY) +
						((rayOriginZ - sphereLocationZ) * rayDirectionZ)));
	double varC = pow(rayOriginX - sphereLocationX, 2) +
					pow(rayOriginY - sphereLocationY, 2) +
					pow(rayOriginZ - sphereLocationZ, 2) -
					(radius * radius);

	double discriminant = varB * varB - 4 * varC;

	if (discriminant > 0)
	{

		double firstRoot = ((-varB - sqrt(discriminant)) / 2) - 0.00001;
		
		if (firstRoot > 0)
		{

			return firstRoot;

		}
		else
		{

			return ((-varB + sqrt(discriminant)) / 2) - .00001;

		}

	}
	else
	{

		return -1;

	}

}