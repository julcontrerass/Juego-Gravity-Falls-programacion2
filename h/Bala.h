#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include "Colisionable.h"

class Bala : public sf::Drawable, public Collisionable
{
public:
    Bala(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    bool isAlive() const { return _isAlive; }
    void kill(); // Add this line
private:
    sf::CircleShape _shape;
    sf::Vector2f _velocity;
    bool _isAlive;
};
#endif // BALA_H
