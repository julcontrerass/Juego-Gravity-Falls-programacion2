// Personaje.h
#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Bala.h"
#include <vector>

class Personaje : public sf::Drawable, public Collisionable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    float _frame;
    std::vector<Bala> _balas;
    sf::Clock _disparoCooldown;
    sf::Time _tiempoEntreDisparos;
    sf::Vector2f _direccionMirada;
    int _vidas;

public:
    Personaje();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void disparar();
    void recibirDanio();
    int getVidas() const;
    bool estaVivo() const;
    std::vector<Bala>& getBullets();
};
#endif  // PERSONAJE_H
