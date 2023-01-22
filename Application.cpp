#include "Application.h"

Application::Application(sf::VideoMode mode, const sf::String name, int antialiasingLevel)
{
    //sf::ContextSettings settings;
    //settings.antialiasingLevel = antialiasingLevel;

   //this->window = new sf::RenderWindow(mode, name);
    this->isRunning = 1;

    this->universe.spawnPlanetDisk(10000,100, 300, 250, 400, 15, 15); // 10k
    //this->universe.spawnPlanetDisk(1000, 50, 250, 250, 400, 15, 15); // 1k
}

Application::~Application()
{
    //this->window->close();
    //delete this->window;
}

void Application::update(double dT)
{
    this->universe.update(dT);
}

void Application::render(sf::RenderWindow* window)
{
	window->clear(sf::Color::Black);
    this->universe.render(window);
	window->display();
}

void Application::handleEvents(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->isRunning = 0;
            break;

        case sf::Event::MouseButtonPressed:
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
            sf::Vector2f m = window->mapPixelToCoords(pixelPos);
            this->universe.addPlanet(new Planet(200, Vector2d(m.x, m.y), { 0, 0 }));
            break;
        }
    }
}