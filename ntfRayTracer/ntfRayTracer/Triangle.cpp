/*
*	@file Triangle.cpp
*	@author Nate Finch
*	@date 11-8-17
*/

#include "Triangle.h"

Triangle::Triangle()
{

	vertex1 = Vctr();
	vertex2 = Vctr();
	vertex3 = Vctr();
	color = Color();
	phong = Color();

}
Triangle::Triangle(Vctr vertex1, Vctr vertex2, Vctr vertex3, Color color, Color phong)
{

	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	this->vertex3 = vertex3;
	this->color = color;
	this->phong = phong;

}

double Triangle::getDistance() const
{
	
	return getNormal().dot(vertex1);

}

Color Triangle::getColor() const
{

	return color;

}

Vctr Triangle::getNormal() const
{

	Vctr threeOne(vertex3.getX() - vertex1.getX(), vertex3.getY() - vertex1.getY(), vertex3.getZ() - vertex1.getZ());
	Vctr twoOne(vertex2.getX() - vertex1.getX(), vertex2.getY() - vertex1.getY(), vertex2.getZ() - vertex1.getZ());
	return threeOne.cross(twoOne).normalize();

}

double Triangle::detectIntersection(Ray curRay) const
{

	Vctr rayDirection = curRay.getDirection();
	double angleToTriangle = rayDirection.dot(getNormal());

	if (angleToTriangle == 0) //Parallel
	{

		return -1;

	}
	else
	{

		double angleFromTriangle = getNormal().dot(curRay.getOrigin().add(getNormal().multiply(getDistance()).negate()));

		double toPlane = -(angleFromTriangle / angleToTriangle);

		Vctr planarVector = curRay.getDirection().multiply(toPlane);
		double qX = planarVector.getX() + curRay.getOrigin().getX();
		double qY = planarVector.getY() + curRay.getOrigin().getY();
		double qZ = planarVector.getZ() + curRay.getOrigin().getZ();

		Vctr threeOne(vertex3.getX() - vertex1.getX(), vertex3.getY() - vertex1.getY(), vertex3.getZ() - vertex1.getZ());
		Vctr qOne(qX - vertex1.getX(), qY - vertex1.getY(), qZ - vertex1.getZ());
		double edge1 = threeOne.cross(qOne).dot(getNormal());

		Vctr twoThree(vertex2.getX() - vertex3.getX(), vertex2.getY() - vertex3.getY(), vertex2.getZ() - vertex3.getZ());
		Vctr qThree(qX - vertex3.getX(), qY - vertex3.getY(), qZ - vertex3.getZ());
		double edge2 = twoThree.cross(qThree).dot(getNormal());

		Vctr oneTwo(vertex1.getX() - vertex2.getX(), vertex1.getY() - vertex2.getY(), vertex1.getZ() - vertex2.getZ());
		Vctr qTwo(qX - vertex2.getX(), qY - vertex2.getY(), qZ - vertex2.getZ());
		double edge3 = oneTwo.cross(qTwo).dot(getNormal());

		if (edge1 >= 0 && edge2 >=0 && edge3 >= 0)
		{

			return toPlane;

		}
		else
		{

			return -1; //Outside triangle

		}

		return -(angleFromTriangle / angleToTriangle);

	}
	
}

Color Triangle::getPhong() const
{

	return phong;

}