#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Bala.h"
#include <vector>

class Enemigo : public sf::Drawable, public Collisionable
{
private:
    sf::Sprite _sprite;
    sf::Texture _textur;
    sf::Vector2f _velocity;
    bool _persiguiendo;
    std::vector<Bala> _balas;
    sf::Clock _disparoCooldown;
    sf::Time _tiempoEntreDisparos;
    int _vidas;

public:
    Enemigo();
    void update(const sf::Vector2f& personajePos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void disparar(const sf::Vector2f& personajePos);
    void recibirDanio();
    int getVidas() const;
    bool estaVivo() const;
    std::vector<Bala>& getBullets();
};
#endif // ENEMIGO_H
