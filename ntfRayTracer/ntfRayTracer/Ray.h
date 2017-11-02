/*
*	@file Ray.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _RAY_H
#define _RAY_H

#include "math.h"
#include "Vctr.h"

/**
*	Ray Class
*
*	Stores an origin and destination to form a ray line.
*/
class Ray
{

public:

	Ray();
	Ray(Vctr, Vctr);

	Vctr getOrigin();
	Vctr getDirection();

private:

	Vctr origin, direction;

};

#endif