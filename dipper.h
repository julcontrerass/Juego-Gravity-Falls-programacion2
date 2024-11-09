#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "colisiones.h"
#include "pocionDeVelocidad.h"
#include "bebidaDeVida.h"
#include "disparo.h"
#include "cuchillo.h"
#include "gancho.h"
#include "linterna.h"
#include "estadoDelJuego.h"


class Dipper: public sf::Drawable, public Colisiones
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    sf::Music sonidoBebida;
    float _frame;
    sf::Vector2f _direccionMirada;
//    static int vidas;
    int timer;
    PocionDeVelocidad pocion;
    bool incremento;
    BebidaDeVida bebida;
    //disparo
    TipoDisparo _tipoDisparoActual;
    std::vector<Disparo> _disparos;
    sf::Clock _disparoCooldown;
    const sf::Time _tiempoEntreDisparos = sf::seconds(0.5f);
    Gancho gancho;
    Cuchillo cuchillo;
    Linterna linterna;

    estadoDelJuego estadoDelJuego;

public:
    Dipper();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const  override;
    sf::Vector2f getPosition() const ;
    void setPosition(const sf::Vector2f& position);
    void setInitialTextureRect(int row);
//    int getVidas() const;
//    void recuperarVidas();
//    void perderVida();
    void disparar();
    void cambiarTipoDisparo();
    std::vector<Disparo>& getDisparos() { return _disparos; }
};
