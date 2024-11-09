#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
#include "estadoDelJuego.h"
class BebidaDeVida: public sf::Drawable, public Colisiones
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    static bool estadoBebidas[3];
    static int cantBebidas;
    static int decremento;

    estadoDelJuego estadoDelJuego;

public:
    BebidaDeVida();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(const sf::Vector2f& position);  // Nueva función para cambiar la posición
    void recolectado(int numBebida);
    bool bebidasRecolectadas(int numBebida) const;
    int cantidadDeBebidas() const;
    void restaBebidas();
};


