#include "Enemigo.h"
#include <cmath> // Para calcular la distancia entre el personaje y el enemigo

Enemigo::Enemigo() {
    _textur.loadFromFile("images/gnomo.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setPosition(862, 806);  // Posición inicial fija
    _velocity = {0, 0};             // El enemigo no se mueve inicialmente
    _persiguiendo = false;          // No está persiguiendo al principio
}

void Enemigo::update(const sf::Vector2f& personajePos) {
    float distancia = std::sqrt(std::pow(personajePos.x - _sprite.getPosition().x, 2) +std::pow(personajePos.y - _sprite.getPosition().y, 2));

    // Si la distancia es menor que 200, el enemigo comienza a perseguir al personaje
    if (distancia < 200) {
        _persiguiendo = true;
    } else {
        _persiguiendo = false;
    }

    if (_persiguiendo) {
        // Calcular la dirección hacia el personaje
        sf::Vector2f direccion = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        direccion /= longitud;  // Normalizar el vector

        // Establecer una velocidad fija hacia el personaje
        _velocity = direccion * 3.0f;  // Velocidad ajustada a 2 unidades por frame
    } else {
        _velocity = {0, 0};  // No se mueve si no está persiguiendo
    }

    // Mover el sprite del enemigo según la velocidad calculada
    _sprite.move(_velocity);
}
sf::FloatRect Enemigo::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}


