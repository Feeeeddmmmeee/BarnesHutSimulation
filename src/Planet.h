#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>

#include "Vector.h"
//#include "Universe.h"

struct Planet
{
	double radius, mass;
	Vector2d position, velocity, acceleration;

	Planet(double mass, Vector2d position, Vector2d velocity);

	void update(double dT);
};

#endif