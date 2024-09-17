#include "Bala.h"

Bala::Bala(const sf::Vector2f& position, const sf::Vector2f& direction)
    : _isAlive(true)
{
    _shape.setRadius(10.f);
    _shape.setFillColor(sf::Color::Blue);
    _shape.setPosition(position);
    _velocity = direction * 10.f;
}

void Bala::update()
{
    _shape.move(_velocity);
    // Comprueba si la bala está fuera de la pantalla
    if (_shape.getPosition().x < 0 || _shape.getPosition().x > 1920 ||
        _shape.getPosition().y < 0 || _shape.getPosition().y > 1080) {
        _isAlive = false;
    }
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shape, states);
}

sf::FloatRect Bala::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Bala::kill()
{
    _isAlive = false;
}
