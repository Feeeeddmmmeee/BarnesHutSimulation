#include "Planet.h"

Planet::Planet(double mass, Vector2d position, Vector2d velocity)
{
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;

	this->radius = std::cbrt(4 * mass / 3 / 3.1415) / 8;
}

void Planet::update(double dT)
{
	this->position += this->velocity * dT;

	if (this->position.x >= 1080)
	{
		this->position.x = 1079;
		this->velocity.x = -1 * this->velocity.x;
	}

	if (this->position.y >= 1080)
	{
		this->position.y = 1079;
		this->velocity.y = -1 * this->velocity.y;
	}
	if (this->position.x <= 0)
	{
		this->position.x = 1;
		this->velocity.x = -1 * this->velocity.x;
	}
	if (this->position.y <= 0)
	{
		this->position.y = 1;
		this->velocity.y = -1 * this->velocity.y;
	}
}
