/*
*	@file Light.h
*	@author Nate Finch
*	@date 11-2-17
*/

#pragma once
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vctr.h"
#include "Color.h"

/**
*	Light Class
*
*	Stores a light's position, or direction to it, along with its color (stored as a Vctr object,
*	with rgb corresponding to xyz).
*/
class Light
{

public:

	Light();
	Light(Vctr, Color);

	Vctr getPosition() const;
	Color getColor() const;

private:

	Vctr position;
	Color color;

};

#endif