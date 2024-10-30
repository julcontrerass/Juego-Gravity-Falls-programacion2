#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
class Gancho: public sf::Drawable, public Colisiones
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    static bool agarrado;

public:
    Gancho();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(const sf::Vector2f& position);  // Nueva funci�n para cambiar la posici�n
    void recolectado();
    bool estadoDelGancho() const;
};
