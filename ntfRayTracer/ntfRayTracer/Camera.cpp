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

}

Camera::Camera(Vctr position, Vctr direction, Vctr right, Vctr down)
{

	this->position = position;
	this->direction = direction;
	this->right = right;
	this->down = down;

}