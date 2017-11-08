/*
*	@file Light.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Light.h"

Light::Light()
{

	position = Vctr(0, 0, 1);
	color = Color(1.0, 1.0, 1.0, 1.0);

}

Light::Light(Vctr position, Color color)
{

	this->position = position;
	this->color = color;

}

Vctr Light::getPosition() const
{

	return position;

}

Color Light::getColor() const
{

	return color;

}