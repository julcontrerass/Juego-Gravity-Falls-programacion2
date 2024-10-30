#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
enum class TipoDisparo {
    BOLA_AZUL,
    CUCHILLO,
    GANCHO
};

class Disparo : public sf::Drawable, public Colisiones
{


private:
    sf::CircleShape _shape;
    sf::Vector2f _velocity;
    bool _isAlive;
    TipoDisparo _tipo;
    // Para cuchillo y gancho
    sf::Sprite _sprite;
    static sf::Texture _texturaGancho;
    static sf::Texture _texturaCuchillo;
    static bool _texturasLoaded;
    void loadTexturas();


public:
    Disparo(const sf::Vector2f& position, const sf::Vector2f& direction, TipoDisparo tipo = TipoDisparo::BOLA_AZUL);
    void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const;
    bool isAlive() const { return _isAlive; }
    void kill() { _isAlive = false; }
    sf::Vector2f getPosition() const;

};

