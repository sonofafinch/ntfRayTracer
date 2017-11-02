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

double Vctr::getX()
{

	return x;

}

double Vctr::getY()
{

	return y;

}

double Vctr::getZ()
{

	return z;

}

Vctr Vctr::add(Vctr toAdd)
{

	double sumX = this->x + toAdd.getX();
	double sumY = this->y + toAdd.getY();
	double sumZ = this->z + toAdd.getZ();

	return Vctr(sumX, sumY, sumZ);

}

Vctr Vctr::cross(Vctr toCross)
{

	double crossX = this->y * toCross.getZ() - this->z * toCross.getY();
	double crossY = this->z * toCross.getX() - this->x * toCross.getZ();
	double crossZ = this->x * toCross.getY() - this->y * toCross.getX();

	return Vctr(crossX, crossY, crossZ);

}

double Vctr::dot(Vctr toProduct)
{

	double xProduct = this->x * toProduct.getX();
	double yProduct = this->y * toProduct.getY();
	double zProduct = this->z * toProduct.getZ();

	return xProduct + yProduct + zProduct;

}

double Vctr::magnitude()
{

	return sqrt((x * x) + (y * y) + (z * z));

}

Vctr Vctr::multiply(double toMultiply)
{

	double scaledX = this->x * toMultiply;
	double scaledY = this->y * toMultiply;
	double scaledZ = this->z * toMultiply;

	return Vctr(scaledX, scaledY, scaledZ);

}

Vctr Vctr::negate()
{

	return Vctr(-(this->x), -(this->y), -(this->z));

}

Vctr Vctr::normalize()
{

	double vctrMgntd = this->magnitude();

	double normX = this->x / vctrMgntd;
	double normY = this->y / vctrMgntd;
	double normZ = this->z / vctrMgntd;

	return Vctr(normX, normY, normZ);

}