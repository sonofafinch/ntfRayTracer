/*
*	@file Vctr.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once

#ifndef _VCTR_H
#define _VCTR_H

#include "math.h"

/**
*	Vctr Class
*
*	Stores 3D vectors, while making dimension values easy to access.
*/
class Vctr
{

public:

	Vctr();
	Vctr(double, double, double);

	double getX();
	double getY();
	double getZ();

	/**
	*
	*/
	Vctr cross(Vctr);
	double dot(Vctr);
	double magnitude();
	Vctr negate();
	Vctr normalize();

private:

	double x, y, z;

};

#endif