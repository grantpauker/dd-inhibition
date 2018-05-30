
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cell.hpp"
#include "constants.hpp"

Cell::Cell(b2World &world, b2Vec2 position, float radius) : Cell(world, position, b2Vec2(0, 0), radius) {}
Cell::Cell(b2World &world, b2Vec2 position, b2Vec2 velocity_override, float radius) : sf::CircleShape(radius), velocity_override(velocity_override)
{
    clock = sf::Clock();
    death_time = (rand() % 500) + 3000;
    alive = true;
    split = false;
    growth_rate = float((rand() % 70 + 30)) / 100;

    b2BodyDef body_def;
    body_def.position = position;
    body_def.type = b2_kinematicBody;
    body = world.CreateBody(&body_def);

    b2CircleShape shape;
    shape.m_p.Set(body_def.position.x, body_def.position.y);
    shape.m_radius = radius * pixel_scale;
    b2FixtureDef fix_def;
    fix_def.density = 1.f;
    fix_def.friction = 0.7f;
    fix_def.restitution = 1.f;

    fix_def.shape = &shape;
    body->CreateFixture(&fix_def);

    setOrigin(radius / 2, radius / 2);
    setFillColor(sf::Color(255, 0, 0, 50));
    setOutlineColor(sf::Color(255, 0, 0));
    setOutlineThickness(5);
    setPosition(body->GetPosition().x * pixel_scale, body->GetPosition().y * pixel_scale);
}
void Cell::kill()
{
    body->GetWorld()->DestroyBody(body);
}
void Cell::jiggle(int n)
{
    body->SetLinearVelocity(b2Vec2(rand() % (2 * n + 1) - n, rand() % (2 * n + 1) - n));
}
void Cell::update()
{
    jiggle(3);
    setPosition(pixel_scale * body->GetPosition().x, pixel_scale * body->GetPosition().y);
    setRotation(body->GetAngle() * 180 / b2_pi);
    if (clock.getElapsedTime().asMilliseconds() > death_time)
    {
        split = true;
    }
    // std::cout << "x: " << getPosition().x << ", y: " << getPosition().y << ", exceed: " << exceedBounds() << std::endl;
    // if (getRadius() < 100)
    // {
    //     setRadius(getRadius() + growth_rate);
    // }
    // else
    // {
    //     split = true;
    // }
    // if (rand() % 100 == 3)
    // {
    //     alive = false;
    // }
    // jiggle(1);
}
std::array<Cell, 2> Cell::reproduce(b2World &world)
{
    float angle = radians(rand() % 360 + 1);
    b2Vec2 vel1(sin(angle), cos(angle));
    b2Vec2 vel2(sin(angle - M_PI), cos(angle - M_PI));
    vel1 *= 10.f;
    vel2 *= 10.f;

    std::array<Cell, 2> daughters{Cell(world, body->GetPosition(), vel1, 25), Cell(world, body->GetPosition(), vel2, 25)};

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
