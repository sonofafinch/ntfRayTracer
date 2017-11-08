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
	character = 0.0;

}
Color::Color(double red, double green, double blue, double character)
{

	setRed(red);
	setGreen(green);
	setBlue(blue);
	setCharacter(character);

}

double Color::getRed() const
{

	return red;

}

double Color::getGreen() const
{

	return green;

}

double Color::getBlue() const
{

	return blue;

}

double Color::getCharacter() const
{

	return character;

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

void Color::setCharacter(double character)
{

	this->character = character;

}

double Color::value() const
{

	return (red + green + blue) / 3;

}

Color Color::scaleHue(double scale) const
{

	return Color(red * scale, green * scale, blue * scale, character);

}

Color Color::addHue(Color toAdd) const
{

	return Color(red + toAdd.getRed(), green + toAdd.getGreen(), blue + toAdd.getBlue(), character);

}

Color Color::multiplyHue(Color toMultiply) const
{

	return Color(red * toMultiply.getRed(), green * toMultiply.getGreen(), blue * toMultiply.getBlue(), character);

}

Color Color::average(Color toAvg) const
{

	return Color((red + toAvg.getRed()) / 2, (green + toAvg.getGreen()) / 2, (blue + toAvg.getBlue()) / 2, character);

}

Color Color::limit() const
{

	double max = red;
	if (max < green)
	{

		max = green;

	}
	if (max < blue)
	{

		max = blue;

	}

	double newRed = red;
	double newGreen = green;
	double newBlue = blue;

	if (max > 1)
	{

		newRed = newRed / max;
		newGreen = newGreen / max;
		newBlue = newBlue / max;

	}

	if (newRed < 0)
	{

		newRed = 0;

	}
	if (newGreen < 0)
	{

		newGreen = 0;

	}
	if (newBlue < 0)
	{

		newBlue = 0;

	}

	return Color(newRed, newGreen, newBlue, character);

}