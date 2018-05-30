#ifndef H_ARENA
#define H_ARENA
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "cell.hpp"
class Arena
{
public:
  Arena(sf::RenderWindow &window);
  b2World *world;

  std::vector<Cell> cells;
  sf::RenderWindow &window;
  void update();
};
#endif