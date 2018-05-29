
#include <SFML/Graphics.hpp>
#include "cell.hpp"
#include "constants.hpp"

Cell::Cell( float radius, float max_size) : sf::CircleShape(radius)
{
    alive = true;
    split = false;
    growth_rate = float((rand() % 70 + 30)) / 100;
    direction_bias = sf::Vector2f(0, 0);
    setOrigin(radius / 2, radius / 2);
    setFillColor(sf::Color(255, 0, 0, 50));
    setOutlineColor(sf::Color(255, 0, 0));
    setOutlineThickness(5);
    setPosition(arena_width / 2, arena_height / 2);


}
void Cell::jiggle(int n)
{
    sf::Vector2f to_move(rand() % (2 * n + 1) - n, rand() % (2 * n + 1) - n);
    to_move += (direction_bias);
    if (!exceedBounds())
    {
        move(to_move);
    }
    if (abs(direction_bias.x) > 0.1)
    {
        direction_bias.x *= 0.9;
    }
    else
    {
        direction_bias.x = 0;
    }
    if (abs(direction_bias.y) > 0.1)
    {
        direction_bias.y *= 0.9;
    }
    else
    {
        direction_bias.y = 0;
    }
}
void Cell::update()
{
    // std::cout << "x: " << getPosition().x << ", y: " << getPosition().y << ", exceed: " << exceedBounds() << std::endl;
    if (getRadius() < 100)
    {
        setRadius(getRadius() + growth_rate);
    }
    else
    {
        split = true;
    }
    if (rand() % 100 == 3)
    {
        alive = false;
    }
    jiggle(1);
}
std::array<Cell, 2> Cell::reproduce()
{
    std::array<Cell, 2> daughters{Cell(25), Cell(25)};
    float angle = radians(rand() % 360 + 1);
    sf::Vector2f pos1(getPosition().x + getRadius() * sin(angle), getPosition().y + getRadius() * cos(angle));
    float angle2 = radians(degrees(angle) + 90 + (rand() % 180));
    sf::Vector2f pos2(getPosition().x + getRadius() * sin(angle2), getPosition().y + getRadius() * cos(angle2));
    daughters.at(0).setPosition(pos1);
    daughters.at(0).direction_bias = sf::Vector2f(sin(angle), cos(angle)) * 10.f;
    daughters.at(1).setPosition(pos2);
    // float angle2 = angle -180;
    // std::cout << "x: " << degrees(angle) << ", y: " << degrees(angle2) << ", exceed: " << exceedBounds() << std::endl;

    daughters.at(1).direction_bias = sf::Vector2f(sin(angle2), cos(angle2)) * 10.f;
    return daughters;
}
bool Cell::isAlive()
{
    return alive;
}
bool Cell::isSplit()
{
    return split;
}
bool Cell::isIntersecting(Cell to_check)
{
    float distance = pow((to_check.getPosition().x - getPosition().x), 2) + pow((to_check.getPosition().y - getPosition().y), 2);
    return distance > pow(getRadius() + to_check.getRadius(), 2);
}
bool Cell::exceedBounds()
{
    bool exceeds = getPosition().x < 0;
    exceeds = exceeds || getPosition().x > arena_width;
    exceeds = exceeds || getPosition().y < 0;
    exceeds = exceeds || getPosition().y > arena_height;
    return exceeds;
}
