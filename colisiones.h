#pragma once
#include <SFML/Graphics.hpp>


class Colisiones
{
public:
    virtual sf::FloatRect getBounds() const = 0;
    bool isCollision(Colisiones &col) const;
};
