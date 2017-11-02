/*
*	@file Ray.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Ray.h"

Ray::Ray()
{

	origin = Vctr(0, 0, 0);
	direction = Vctr(0, 0, -1);

}

Ray::Ray(Vctr origin, Vctr direction)
{

	this->origin = origin;
	this->direction = direction;

}

Vctr Ray::getOrigin()
{

	return origin;

}

Vctr Ray::getDirection()
{

	return direction;

}