#include <iostream>
#include <vector>
#include <cmath>
#include "arena.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode(arena_width, arena_height), "Density Dependers");
    window.setFramerateLimit(60);
    srand(time(NULL));
    Arena arena(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        arena.update();

        window.display();
    }
    return EXIT_SUCCESS;
}
