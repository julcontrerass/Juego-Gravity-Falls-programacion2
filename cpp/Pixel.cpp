#include "Pixel.h"

Pixel::Pixel(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    shape.setRadius(5.0f); // Tama�o del pixel
    shape.setFillColor(sf::Color::Red); // Color (puedes hacer un ciclo de colores del arco�ris)
    shape.setPosition(position);
    velocity = direction * 300.0f; // Velocidad y direcci�n del proyectil
}

void Pixel::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Pixel::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Pixel::getBounds() const
{
    return shape.getGlobalBounds();
}
