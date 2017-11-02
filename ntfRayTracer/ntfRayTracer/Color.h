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

	double getRed();
	double getGreen();
	double getBlue();
	double getAlpha();

	void setRed(double);
	void setGreen(double);
	void setBlue(double);
	void setAlpha(double);

private:

	double red, green, blue, alpha;

};

#endif