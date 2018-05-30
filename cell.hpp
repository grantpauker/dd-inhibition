#ifndef H_CELL
#define H_CELL
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "constants.hpp"
class Cell : public sf::CircleShape
{
public:
  Cell(b2World &,b2Vec2 , float);
  void kill();
  void jiggle(int);
  void update();
  std::array<Cell, 2> reproduce(b2World &world);
  bool isAlive();
  bool isSplit();
  bool isIntersecting(Cell);
  bool exceedBounds();
  b2Vec2 velocity_override;

private:
  Cell(b2World &, b2Vec2,b2Vec2, float);
  bool alive;
  bool split;
  float growth_rate;
  float death_time;
  sf::Clock clock;
  b2Body *body;
};
#endif
