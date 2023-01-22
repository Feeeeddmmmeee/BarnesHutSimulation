#ifndef CHUNK_H
#define CHUNK_H

#include "Vector.h"
#include "Planet.h"

class Chunk
{
public:
	friend class Universe;

	Planet* p = nullptr;
	bool hasChildren = 0;
	int depth;

	Vector2d centerOfMass = { 0, 0 };
	double totalMass = 0;

	Vector2d position;
	Vector2d size;

	Chunk(int depth, Vector2d position, Vector2d size);

	void render(sf::RenderWindow* window);
	void insert(Planet* planet);
	void Clear();

private:
	std::shared_ptr<Chunk> chunks[4] = { nullptr, nullptr, nullptr, nullptr };
	/*
	
	 1 | 0
	___|___
	 2 | 3
	
	*/

	void insertIntoAppropriateQuadrant(Planet* planet);

};

#endif