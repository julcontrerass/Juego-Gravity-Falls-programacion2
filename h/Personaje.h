#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include "Colisionable.h"

class Personaje : public sf::Drawable, public Collisionable
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    sf::Vector2f _velocity;
    float _frame;

public:
    Personaje();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
};

#endif  // PERSONAJE_H
