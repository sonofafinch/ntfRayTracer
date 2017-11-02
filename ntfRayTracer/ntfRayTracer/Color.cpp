/*
*	@file Color.cpp
*	@author Nate Finch
*	@date 11-2-17
*/

#include "Color.h"

Color::Color()
{

	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 0.0;

}
Color::Color(double red, double green, double blue, double alpha)
{

	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);

}

double Color::getRed()
{

	return red;

}

double Color::getGreen()
{

	return green;

}

double Color::getBlue()
{

	return blue;

}

double Color::getAlpha()
{

	return alpha;

}

void Color::setRed(double red)
{

	this->red = red;

}

void Color::setGreen(double green)
{

	this->green = green;

}

void Color::setBlue(double blue)
{


	this->blue = blue;

}

void Color::setAlpha(double alpha)
{

	this->alpha = alpha;

}
