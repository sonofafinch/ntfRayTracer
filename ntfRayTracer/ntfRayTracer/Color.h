/*
*	@file Color.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once

#ifndef _COLOR_H
#define _COLOR_H

/**
*	Color Class
*
*	Stores RGB color values.
*/
class Color
{

public:

	Color();
	Color(double, double, double, double);

	double getRed() const;
	double getGreen() const;
	double getBlue() const;
	double getCharacter() const;

	void setRed(double);
	void setGreen(double);
	void setBlue(double);
	void setCharacter(double);

	double value() const;
	Color scaleHue(double scale) const;
	Color addHue(Color toAdd) const;
	Color multiplyHue(Color toMultiply) const;
	Color average(Color toAvg) const;
	Color limit() const;

private:

	double red, green, blue, character;

};

#endif