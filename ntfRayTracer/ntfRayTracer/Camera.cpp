/*
*	@file Camera.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Camera.h"

Camera::Camera()
{

	position = Vctr(0, 0, 1);
	direction = Vctr(0, 0, 0);
	right = Vctr(1, 0, 1);
	down = Vctr(0, -1, 1);
	FOV = 45;

}

Camera::Camera(Vctr position, Vctr direction, Vctr right, Vctr down, double FOV)
{

	this->position = position;
	this->direction = direction;
	this->right = right;
	this->down = down;
	this->FOV = FOV;

}

Vctr Camera::getPosition()
{

	return position;

}

Vctr Camera::getDirection()
{

	return direction;

}

Vctr Camera::getRight()
{


	return right;
}

Vctr Camera::getDown()
{

	return down;

}

double Camera::getFOV()
{

	return FOV;

}