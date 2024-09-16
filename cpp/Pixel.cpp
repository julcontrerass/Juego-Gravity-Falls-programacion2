#include "Pixel.h"

Pixel::Pixel(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    shape.setRadius(5.0f); // Tamaño del pixel
    shape.setFillColor(sf::Color::Red); // Color (puedes hacer un ciclo de colores del arcoíris)
    shape.setPosition(position);
    velocity = direction * 300.0f; // Velocidad y dirección del proyectil
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
