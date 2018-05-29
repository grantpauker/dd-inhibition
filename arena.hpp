#ifndef H_ARENA
#define H_ARENA
#include <SFML/Graphics.hpp>
#include "cell.hpp"
class Arena
{
  public:
    Arena(sf::RenderWindow &window) ;
   
    std::vector<Cell> cells;
    sf::RenderWindow &window;
    void update();
};
#endif