/*
*	@file Shape.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _SHAPE_H
#define _SHAPE_H

#include "Color.h"
#include "Ray.h"
#include "Vctr.h"

/**
*	Shape Class
*
*	Super class that allows ray interaction for all sub-class objects.
*/
class Shape
{

public:

	Shape() {};

	virtual Color getColor() const { return Color(); }

	/**
	*	detectIntersection
	*
	*	Computes whether a given ray intersects with the shape in question; dependant upon the sub-class type/method.
	*
	*	@param		curRay			The ray that's seeking intersection
	*
	*	@return						The value of intersection
	*/
	virtual double detectIntersection(Ray curRay)  const { return 0; }

	virtual Vctr getNormal(Vctr position) const { return Vctr(); }

};

#endif