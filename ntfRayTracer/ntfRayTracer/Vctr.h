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

	double getX() const;
	double getY() const;
	double getZ() const;

	/**
	*	add
	*
	*	Sums to vectors' values.
	*
	*	@param		toAdd				The vector to add to this one
	*
	*	@return							The sum of the two vectors
	*/
	Vctr add(Vctr toAdd) const;

	/**
	*	cross
	*
	*	Performs a cross product operation between this vector and a parameter one.
	*
	*	@param		toCross				The vector to cross with this one
	*
	*	@return							The cross product of two vectors
	*/
	Vctr cross(Vctr toCross) const;

	/**
	*	dot
	*
	*	Peforms a dot product operation between this vector and a parameter one.
	*
	*	@param		toProduct			The vector to dot with this one
	*
	*	@return							The dot product of the two vectors
	*/
	double dot(Vctr toDot) const;

	/**
	*	magnitude
	*
	*	Computes the magnitude, based on x, y, and z vector values.
	*
	*	@preturn						The magnitude of this vector
	*/
	double magnitude() const;

	/**
	*	multiply
	*
	*	Multiplies this vector's values by a scalar value.
	*
	*	@param		toMultiply			The scalar to multiply by
	*
	*	@return							The scaled vector
	*/
	Vctr multiply(double toMultiply) const;

	/*
	*	negate
	*
	*	Inverts this vector's x, y, and z values.
	*
	*	@return							The inverted vector
	*/
	Vctr negate() const;

	/*
	*	normalize
	*
	*	Computes the magnitude of the vector and returns the normalized vector.
	*
	*	@return							The normalized vector
	*/
	Vctr normalize() const;

private:

	double x, y, z;

};

#endif