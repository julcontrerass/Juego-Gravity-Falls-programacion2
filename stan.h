#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "mochila.h"

class Stan : public sf::Drawable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _frame;
    sf::Vector2f _velocity;
    sf::Vector2f _direccionMirada;
    sf::Text _textoDialogo;
    sf::RectangleShape _burbujaDialogo;
    sf::Font _fuente;
    bool _mostrarDialogo;
    std::vector<std::string> _dialogos;
    std::vector<std::string> _dialogos2;
    std::vector<std::string> _dialogos3;
    int _dialogoActual;
    bool _dialogoCompletado;
    float _tiempoDialogo;
    const float TIEMPO_ENTRE_DIALOGOS = 2.0f;
    bool _dialogoPermanentementeCompletado;
    Mochila mochila;
    bool _moviendoseAutomaticamente;
    std::vector<sf::Vector2f> _puntosDeRuta;
    size_t _puntoActual;
    float _velocidadAutomatica;
    static bool _debeDesaparecer;
    float _fotograma;
    bool _segundoDialogoCompletado;

public:
    Stan();
    void update();
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // DIALOGOS
    void actualizarDialogo(float deltaTime);
    void iniciarDialogo();
    bool dialogoCompletado() const
    {
        return _dialogoCompletado;
    }
    bool dialogoPermanentementeCompletado() const;
    void setPermanentementeCompletado(bool completado)
    {
        _dialogoPermanentementeCompletado = completado;
    }
    void actualizarPosicionDialogo();
    bool segundoDialogoCompletado() const;

    // MOVIMIENTOS
    void iniciarMovimientoAutomatico();
    bool haDesaparecido() const;
    void actualizarMovimientoAutomatico();
};
