#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gnomo.h"
#include "estadoDelJuego.h"

class Wendy: public sf::Drawable
{
private:
    sf::Sprite _sprite;
    sf::Texture _textura;
    sf::Vector2f _velocidad;
    sf::Vector2f _direccionMirada;
    Gnomo gnomo;
    //DIALOGOS
    sf::Text _textoDialogo;
    sf::RectangleShape _burbujaDialogo;
    sf::Font _fuente;
    bool _mostrarDialogo;
    std::vector<std::string> _dialogos;
    std::vector<std::string> _dialogos2;
    int _dialogoActual;
    bool _dialogoCompletado;
    float _tiempoDialogo;
    const float TIEMPO_ENTRE_DIALOGOS = 2.0f;
    bool _dialogoPermanentementeCompletado;

    // MOVIMIENTOS
    bool _moviendoseAutomaticamente;
    std::vector<sf::Vector2f> _puntosDeRuta;
    size_t _puntoActual;
    float _velocidadAutomatica;
//    static bool _debeDesaparecer;
    float _fotograma;

    estadoDelJuego estadoDelJuego;


public:
    Wendy();
    void update();
    void draw(sf::RenderTarget& objetivo, sf::RenderStates estados) const override;
    sf::FloatRect obtenerLimites() const;
    sf::Vector2f obtenerPosicion() const;
    void establecerPosicion(const sf::Vector2f& posicion);
    //DIALOGOS
    void actualizarDialogo(float deltaTime);
    void iniciarDialogo();
    bool dialogoCompletado() const { return _dialogoCompletado; }
    bool dialogoPermanentementeCompletado() const { return _dialogoPermanentementeCompletado; }
    void setPermanentementeCompletado(bool completado) { _dialogoPermanentementeCompletado = completado; }
    void actualizarPosicionDialogo();

    // MOVIMIENTOS
    void iniciarMovimientoAutomatico();
    void actualizarMovimientoAutomatico();
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

};
