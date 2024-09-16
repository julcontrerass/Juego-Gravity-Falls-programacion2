#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics.hpp>

class Pixel
{
private:
    sf::CircleShape shape; // Representa el pixel como un pequeño círculo
    sf::Vector2f velocity; // Velocidad y dirección del pixel

public:
    Pixel(const sf::Vector2f& position, const sf::Vector2f& direction);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const; // Obtener los límites del píxel para la colisión
};

#endif
