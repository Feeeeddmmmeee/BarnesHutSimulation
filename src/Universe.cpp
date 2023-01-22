#include "Universe.h"

Universe::Universe()
{
	this->root = std::make_shared<Chunk>(0, Vector2d(0, 0), Vector2d(1080, 1080 ));
}

void Universe::render(sf::RenderWindow* window)
{
	std::shared_ptr<Chunk> temp = this->root;
	//temp->render(window);
	sf::CircleShape shape;
	shape.setFillColor(sf::Color::White);

	for (auto& planet : this->planets)
	{
		shape.setPosition(planet->position.x - planet->radius, planet->position.y - planet->radius);
		shape.setRadius(planet->radius);
		window->draw(shape);
	}
}

void Universe::update(double dT)
{
	//this->root->Clear();
	this->root = std::make_shared<Chunk>(0, Vector2d(0, 0), Vector2d(1080, 1080));
	for (auto& planet : this->planets)
	{
		root->insert(planet);
	}

	for (auto& planet : this->planets)
	{
		planet->acceleration = { 0, 0 };

		this->gravityDFS(root, planet, dT);
		this->attractToCenter(planet, dT);

		planet->velocity += planet->acceleration;
	}

	for (auto& planet : this->planets)
	{
		planet->update(dT);
	}
}

void Universe::addPlanet(Planet* planet)
{
	this->planets.push_back(planet);
}

void Universe::gravityDFS(std::shared_ptr<Chunk> chunk, Planet* planet, double dT)
{
	if (chunk->p == planet) return;
	else if (!chunk->hasChildren || (chunk->size.x / (chunk->centerOfMass - planet->position).length()) < MAX_DISTANCE)
	{
		calculateChunkForce(chunk, planet, dT);
	}
	else
	{
		for (int i = 0; i < 4; i++) if(chunk->chunks[i]) gravityDFS(chunk->chunks[i], planet, dT);
	}
}

void Universe::attractToCenter(Planet* planet, double dT)
{
	Vector2d direction = (root->position + root->size/2) - planet->position;
	double distance = direction.length();
		
	if (!distance) return;

	if (distance > planet->radius)
		planet->acceleration += (direction / distance * CENTER_MASS * G_CONSTANT / (distance * distance)) * dT;
}

void Universe::spawnPlanetDisk(int planetCount, double minDistance, double maxDistance, double minMass, double maxMass, double minVelocity, double maxVelocity)
{
	for (int i = 0; i < planetCount; i++)
	{
		double theta = 2 * PI * fRand(0, 1);
		double r = fRand(minDistance, maxDistance);

		double mass = fRand(minMass, maxMass);

		Vector2d center = this->root->position + this->root->size * 0.5;
		Vector2d position = center + Vector2d(r * cos(theta), r * sin(theta));

		Vector2d directionNormal = (center - position).fastNormal();
		Vector2d rotatedNormal = Vector2d(directionNormal.y, directionNormal.x * -1);
		Vector2d velocity = rotatedNormal * fRand(minVelocity, maxVelocity);

		this->addPlanet(new Planet(mass, position, velocity));
	}
}

void Universe::calculateChunkForce(std::shared_ptr<Chunk> chunk, Planet* planet, double dT)
{
	Vector2d direction = chunk->centerOfMass - planet->position;
	double distance = direction.length();
	
	if (!distance) return;

	if (!chunk->p)
	{
		planet->acceleration += (direction / distance * chunk->totalMass * G_CONSTANT / (distance * distance)) * dT;
	}
	else if (distance > chunk->p->radius + planet->radius)
	{
		planet->acceleration += (direction / distance * chunk->totalMass * G_CONSTANT / (distance * distance)) * dT;
	}
}	

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
