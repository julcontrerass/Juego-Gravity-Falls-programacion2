#ifndef PIXEL_H
#define PIXEL_H

#include <SFML/Graphics.hpp>

class Pixel
{
private:
    sf::CircleShape shape; // Representa el pixel como un peque�o c�rculo
    sf::Vector2f velocity; // Velocidad y direcci�n del pixel

public:
    Pixel(const sf::Vector2f& position, const sf::Vector2f& direction);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const; // Obtener los l�mites del p�xel para la colisi�n
};

#endif
