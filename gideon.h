#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "colisiones.h"
#include "disparo.h"
#include "estadoDelJuego.h"

class Gideon: public sf::Drawable, public Colisiones
{
private:
    sf::Sprite _sprite;
    sf::Texture _textur;
    sf::Vector2f _velocity;
    float _frame;
    sf::Vector2f _direccionMirada;
    bool _persiguiendo;
    std::vector<Disparo> _balas;
    sf::Clock _disparoCooldown;
    sf::Time _tiempoEntreDisparos;
    int _vidas;
    estadoDelJuego estadoDelJuego;

public:
    Gideon();
    void update(const sf::Vector2f& personajePos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void disparar(const sf::Vector2f& personajePos);
    void recibirDanio();
    int getVidas() const;
    bool estaVivo() const;
    std::vector<Disparo>& getDisparos();
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setInitialTextureRect(int row);
};
