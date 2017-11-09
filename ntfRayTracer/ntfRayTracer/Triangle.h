/*
*	@file Triangle.h
*	@author Nate Finch
*	@date 11-8-17
*/

#pragma once
#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Color.h"
#include "math.h"
#include "Shape.h"
#include "Vctr.h"

/**
*	Triangle Class
*
*	Stores the position, size, and color of a triangle object.
*/
class Triangle : public Shape
{

public:

	Triangle();
	Triangle(Vctr, Vctr, Vctr, Color, Color);

	double getDistance() const;
	virtual Color getColor() const;
	virtual Color getPhong() const;

	virtual Vctr getNormal() const;
	virtual double detectIntersection(Ray curRay) const;

private:

	Vctr vertex1;
	Vctr vertex2;
	Vctr vertex3;
	Color color;
	Color phong;

};

#endif