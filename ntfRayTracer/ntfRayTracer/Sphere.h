/*
*	@file Sphere.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _SPHERE_H
#define _SPHERE_H

#include "Color.h"
#include "math.h"
#include "Shape.h"
#include "Vctr.h"

/**
*	Sphere Class
*
*	Stores the position, size, and color of a sphere object.
*/
class Sphere : public Shape
{

public:

	Sphere();
	Sphere(Vctr, double, Color, Color);

	Vctr getPosition() const;
	double getRadius() const;
	virtual Color getColor() const;
	virtual Color getPhong() const;

	virtual Vctr getNormal(Vctr) const;
	virtual double detectIntersection(Ray curRay) const;

private:

	Vctr center;
	double radius;
	Color color;
	Color phong;

};

#endif