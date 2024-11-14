#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
#include "estadoDelJuego.h"

class Disparo : public sf::Drawable, public Colisiones
{

private:
    sf::CircleShape _shape;
    sf::Vector2f _velocity;
    bool _isAlive;
    int _tipo;
    sf::Sprite _sprite;
    static sf::Texture _texturaGancho;
    static sf::Texture _texturaCuchillo;
    static bool _texturasLoaded;
    void loadTexturas();
    estadoDelJuego estadoDelJuego;



public:
    Disparo(const sf::Vector2f& position, const sf::Vector2f& direction, int tipo);
    void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const;
    bool isAlive() const { return _isAlive; }
    void kill() { _isAlive = false; }
    sf::Vector2f getPosition() const;

};

