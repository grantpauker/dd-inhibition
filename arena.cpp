#include <iostream>
#include "arena.hpp"

Arena::Arena(sf::RenderWindow &window) : window(window)
{
    cells.push_back(Cell(25));
}

void Arena::update()
{
    std::vector<Cell>::size_type size = cells.size();
    std::cout << size << std::endl;
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
            std::array<Cell, 2> daughters = cells[i].reproduce();
            cells.push_back(daughters[0]);
            cells.push_back(daughters[1]);
            cells.erase(cells.begin() + i);
            i++;
        }

        window.draw(cells[i]);
    }
}
