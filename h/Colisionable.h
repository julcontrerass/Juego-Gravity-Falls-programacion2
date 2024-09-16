#ifndef COLLISIONABLE_H
#define COLLISIONABLE_H
#include <SFML/Graphics.hpp>
class Collisionable
{
public:
    virtual sf::FloatRect getBounds() const = 0;
    bool isCollision(Collisionable &col) const;
};

#endif // COLLISIONABLE_H
