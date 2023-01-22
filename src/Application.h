#ifndef APPLICATION_H
#define APPLICATION_H

#include "Universe.h"

class Application {

public:
    Application(sf::VideoMode mode, const sf::String name, int antialiasingLevel);
    ~Application();

    void update(double dT);
    void render(sf::RenderWindow* window);
    void handleEvents(sf::RenderWindow* window);

    bool running() { return isRunning; };

private:
    bool isRunning = 0;
    Universe universe;

};

#endif