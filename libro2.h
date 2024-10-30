#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
class Libro2: public sf::Drawable, public Colisiones
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    static bool agarrado;

public:
    Libro2();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(const sf::Vector2f& position);
    void recolectado();
    bool estadoDelLibro() const;
};
