#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Chunk.h"

const double G_CONSTANT = 6.67e-3;
const double MAX_DISTANCE = 0.5;
const double DISTANCE_THRESHOLD = 0.1;
const double CENTER_MASS = 5000000;
const double PI = 3.1415;

double fRand(double fMin, double fMax);

class Universe
{
public:
	Universe();
	void render(sf::RenderWindow* window);
	void update(double dT);

	void addPlanet(Planet* planet);
	void gravityDFS(std::shared_ptr<Chunk> chunk, Planet* planet, double dT);

	void attractToCenter(Planet* planet, double dT);
	void spawnPlanetDisk(int planetCount, double minDistance, double maxDistance, double minMass, double maxMass, double minVelocity, double maxVelocity);

private:
	std::vector<Planet*> planets;
	std::shared_ptr<Chunk> root;

	void calculateChunkForce(std::shared_ptr<Chunk> chunk, Planet* planet, double dT);
};

#endif