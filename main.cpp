#include "Application.h"

Application* app;

void renderingThread(sf::RenderWindow* window)
{
    while(app->running())
        app->render(window);
}

int main()
{
    app = new Application(sf::VideoMode(1080, 1080), "Barnes-Hut Gravity Simulation", 0);
    sf::Clock deltaClock;

    sf::RenderWindow window(sf::VideoMode(1080, 1080), "Barnes-Hut Gravity Simulation");

    window.setActive(0);
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    while (app->running())
    {
        sf::Time dT = deltaClock.restart();

        app->handleEvents(&window);
        app->update(dT.asSeconds());
    }

    delete app;
    return 0;
}