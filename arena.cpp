#include <iostream>
#include <Box2D/Box2D.h>
#include "arena.hpp"

Arena::Arena(sf::RenderWindow &window) : window(window)
{
    world = new b2World(b2Vec2(0.f, 9.8f));
    cells.push_back(Cell(*world, b2Vec2(arena_width / 2 / pixel_scale, arena_height / 2 / pixel_scale), 25));
}

void Arena::update()
{
    world->Step(1 / 60.f, 8, 3);

    std::vector<Cell>::size_type size = cells.size();
    for (std::vector<Cell>::size_type i = 0; i < size; ++i)
    {
        cells[i].update();
        if (!cells[i].isAlive())
        {
            // cells.erase(cells.begin() + i);
            // i++;
        }
        if (cells[i].isSplit())
        {
            std::array<Cell, 2> daughters = cells[i].reproduce(*world);
            cells.push_back(daughters[0]);
            cells.push_back(daughters[1]);
            (cells.begin()+i)->kill();
            cells.erase(cells.begin() + i);
            i++;
        }

        window.draw(cells[i]);
    }
}
