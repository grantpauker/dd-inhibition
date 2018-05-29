#ifndef H_CELL
#define H_CELL
#include <SFML/Graphics.hpp>
#include "constants.hpp"
class Cell : public sf::CircleShape
{
public:
  Cell(float, float max_size = 50);
  void jiggle(int);
  void update();
  std::array<Cell, 2> reproduce();
  bool isAlive();
  bool isSplit();
  bool isIntersecting(Cell);
  bool exceedBounds();
  sf::Vector2f direction_bias;

private:
  bool alive;
  bool split;
  float growth_rate;
};
#endif
