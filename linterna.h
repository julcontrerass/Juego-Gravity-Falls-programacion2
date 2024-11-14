#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
#include "estadoDelJuego.h"
class Linterna: public sf::Drawable, public Colisiones
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    static bool agarrado;
    estadoDelJuego estadoDelJuego;

public:
    Linterna();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(const sf::Vector2f& position);
    void recolectado();
    bool estadoDeLaLinterna() const;
};

