#pragma once
#include <SFML/Graphics.hpp>
#include "colisiones.h"
#include "estadoDelJuego.h"
class PocionDeVelocidad: public sf::Drawable, public Colisiones
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    static bool estadoPociones[3];
    static int cantidadPociones;
    static int cantPociones;
    static int decremento;
    estadoDelJuego estadoDelJuego;


public:
    PocionDeVelocidad();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(const sf::Vector2f& position);  // Nueva función para cambiar la posición
    void recolectado(int numPocion);
    bool pocionesRecolectadas(int numPocion) const;
    int cantidadDePociones() const;
    void restaPociones();
};
