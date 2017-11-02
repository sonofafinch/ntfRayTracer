/*
*	@file Camera.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Vctr.h"

/**
*	Camera Class
*
*	Stores the camera's position, direction, and orientation vectors
*/
class Camera
{

public:

	Camera();
	Camera(Vctr, Vctr, Vctr, Vctr);

	Vctr getPosition();
	Vctr getDirection();
	Vctr getRight();
	Vctr getDown();

private:

	Vctr position, direction, right, down;

};

#endif