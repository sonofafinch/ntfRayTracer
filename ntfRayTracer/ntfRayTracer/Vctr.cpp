/*
*	@file Vctr.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Vctr.h"

Vctr::Vctr()
{

	x = 0;
	y = 0;
	z = 0;

}

Vctr::Vctr(double x, double y, double z)
{

	this->x = x;
	this->y = y;
	this->z = z;

}

double Vctr::getX() const
{

	return x;

}

double Vctr::getY() const
{

	return y;

}

double Vctr::getZ() const
{

	return z;

}

Vctr Vctr::add(Vctr toAdd) const
{

	return Vctr(x + toAdd.getX(), y + toAdd.getY(), z + toAdd.getZ());

}

Vctr Vctr::cross(Vctr toCross) const
{

	double xCross = y * toCross.getZ() - z * toCross.getY();
	double yCross = z * toCross.getX() - x * toCross.getZ();
	double zCross = x * toCross.getY() - y * toCross.getX();

	return Vctr(xCross, yCross, zCross);

}

double Vctr::dot(Vctr toDot) const
{

	return x * toDot.getX() + y * toDot.getY() + z * toDot.getZ();

}

double Vctr::magnitude() const
{

	return sqrt((x * x) + (y * y) + (z * z));

}

Vctr Vctr::multiply(double toMultiply) const
{

	return Vctr(x * toMultiply, y * toMultiply, z * toMultiply);

}

Vctr Vctr::negate() const
{

	return Vctr(-(this->x), -(this->y), -(this->z));

}

Vctr Vctr::normalize() const
{

	double vctrMgntd = this->magnitude();

	double normX = this->x / vctrMgntd;
	double normY = this->y / vctrMgntd;
	double normZ = this->z / vctrMgntd;

	return Vctr(normX, normY, normZ);

}