#include "Chunk.h"

Chunk::Chunk(int depth, Vector2d position, Vector2d size)
{
	this->depth = depth;
	this->position = position;
	this->size = size;
}

void Chunk::render(sf::RenderWindow* window)
{
	if (this->depth == 8) return;
	sf::RectangleShape shape;

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor({0, 255, 0, 16});
	shape.setOutlineThickness(-1);
	if(this)
		shape.setPosition(this->position.x, this->position.y);
	if(this)
		shape.setSize(sf::Vector2f(this->size.x, this->size.y));

	window->draw(shape);

	if (this->hasChildren)
	{
		for (int i = 0; i < 4; i++)
			if (chunks[i]) chunks[i]->render(window);
	}
}

void Chunk::insert(Planet* planet)
{
	if (this->hasChildren)
	{
		this->insertIntoAppropriateQuadrant(planet);
	}
	else if (this->p)
	{
		Vector2d half = this->size * 0.5;
		this->chunks[0] = std::make_shared<Chunk>(this->depth + 1, this->position + Vector2d(half.x, 0), half);
		this->chunks[1] = std::make_shared<Chunk>(this->depth + 1, this->position, half);
		this->chunks[2] = std::make_shared<Chunk>(this->depth + 1, this->position + Vector2d(0, half.y), half);
		this->chunks[3] = std::make_shared<Chunk>(this->depth + 1, this->position + half, half);

		this->insertIntoAppropriateQuadrant(planet);
		this->insertIntoAppropriateQuadrant(this->p);

		this->hasChildren = 1;
		this->p = nullptr;
	}
	else this->p = planet;
	this->centerOfMass = (this->centerOfMass * this->totalMass + planet->position * planet->mass) / (this->totalMass + planet->mass);
	this->totalMass += planet->mass;
}

void Chunk::insertIntoAppropriateQuadrant(Planet* planet)
{
	if (planet->position.x > this->position.x + 0.5 * this->size.x)
	{
		if (planet->position.y > this->position.y + 0.5 * this->size.y)
		{
			this->chunks[3]->insert(planet);
		}
		else
		{
			this->chunks[0]->insert(planet);
		}
	}
	else
	{
		if (planet->position.y > this->position.y + 0.5 * this->size.y)
		{
			this->chunks[2]->insert(planet);
		}
		else
		{
			this->chunks[1]->insert(planet);
		}
	}
}

void Chunk::Clear()
{
	if (this->hasChildren)
	{
		for (auto& chunk : this->chunks)
		{
			if (chunk)
			{
				chunk->Clear();
				//chunk = nullptr;
			}
		}
	}


}
