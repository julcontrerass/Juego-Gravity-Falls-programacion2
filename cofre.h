#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "colisiones.h"
#include "estadoDelJuego.h"

class Cofre : public sf::Drawable, public Colisiones
{
private:
    sf::Sprite _sprite;
    sf::Texture _textur;
    bool _visible;
    sf::Texture _texturRecogido;
    bool _abierto;
    int _numeroCofre;
    static const int MAX_COFRES = 10;
    static bool cofresAbiertos[MAX_COFRES];  // Array estático para todos los cofres

    estadoDelJuego estadoDelJuego;
public:
    Cofre(int numeroCofre = 0);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setVisible(bool visible);
    bool isVisible() const;
    void cambiarTextura();
    bool estaAbierto() const;
    void setPosition(const sf::Vector2f& position);
    sf::Music sonidoCofre;
    static void resetearTodosLosCofres();
    static bool getEstadoCofre(int numeroCofre);
    static void setEstadoCofre(int numeroCofre, bool estado);
};
