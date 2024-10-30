#include "disparo.h"
#include <cmath>
#include <stdexcept>

// Inicialización de las variables estáticas
sf::Texture Disparo::_texturaGancho;
sf::Texture Disparo::_texturaCuchillo;
bool Disparo::_texturasLoaded = false;

void Disparo::loadTexturas() {
    if (!_texturasLoaded) {
        try {
            if (!_texturaCuchillo.loadFromFile("./Imagenes/Items/CuchilloLanzado.png")) {
                throw std::runtime_error("No se pudo cargar la textura del cuchillo");
            }
            if (!_texturaGancho.loadFromFile("./Imagenes/Items/ganchoLanzado.png")) {
                throw std::runtime_error("No se pudo cargar la textura del gancho");
            }

            // Configurar repetición de texturas si es necesario
            _texturaCuchillo.setSmooth(true);
            _texturaGancho.setSmooth(true);

            _texturasLoaded = true;
        } catch (const std::exception& e) {
            throw std::runtime_error("Error al cargar texturas: " + std::string(e.what()));
        }
    }
}

Disparo::Disparo(const sf::Vector2f& position, const sf::Vector2f& direction, TipoDisparo tipo)
    : _isAlive(true), _tipo(tipo)
{
    // Normalizar el vector de dirección
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = length != 0.f ? direction / length : direction;

    // Configurar velocidad base según el tipo
    float velocidadBase;
    switch(tipo) {
        case TipoDisparo::BOLA_AZUL:
            velocidadBase = 10.0f;
            break;
        case TipoDisparo::CUCHILLO:
            velocidadBase = 15.0f;
            break;
        case TipoDisparo::GANCHO:
            velocidadBase = 8.0f;
            break;
        default:
            velocidadBase = 10.0f;
            break;
    }

    _velocity = normalizedDirection * velocidadBase;

    if (tipo == TipoDisparo::BOLA_AZUL) {
        // Configuración para bola azul
        _shape.setRadius(10.f);
        _shape.setFillColor(sf::Color::Blue);
        _shape.setOrigin(10.f, 10.f); // Centrar el origen
        _shape.setPosition(position);
    } else {
        // Cargar texturas si no están cargadas
        loadTexturas();

        // Configurar sprite según el tipo
        if (tipo == TipoDisparo::CUCHILLO) {
            _sprite.setTexture(_texturaCuchillo);
        } else { // TipoDisparo::GANCHO
            _sprite.setTexture(_texturaGancho);
        }

        // Configurar el sprite
        sf::FloatRect bounds = _sprite.getLocalBounds();
        _sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        _sprite.setPosition(position);

        // Calcular y establecer la rotación
        float angulo = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
        _sprite.setRotation(angulo);

        // Escalar el sprite si es necesario
        if (tipo == TipoDisparo::CUCHILLO) {
            _sprite.setScale(1.5,1.5); // Ajustar según el tamaño de tu textura
        } else {
            _sprite.setScale(1.5, 1.5); // Ajustar según el tamaño de tu textura
        }
    }
}

void Disparo::update() {
    // Actualizar posición según el tipo
    if (_tipo == TipoDisparo::BOLA_AZUL) {
        _shape.move(_velocity);
    } else {
        _sprite.move(_velocity);
    }

    // Verificar si el proyectil está fuera de la pantalla
    sf::FloatRect bounds = getBounds();
    if (bounds.left < -50.f || bounds.left > 1920.f + 50.f ||
        bounds.top < -50.f || bounds.top > 1080.f + 50.f) {
        _isAlive = false;
    }
}

void Disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_tipo == TipoDisparo::BOLA_AZUL) {
        target.draw(_shape, states);
    } else {
        target.draw(_sprite, states);
    }
}

sf::FloatRect Disparo::getBounds() const {
    if (_tipo == TipoDisparo::BOLA_AZUL) {
        return _shape.getGlobalBounds();
    } else {
        return _sprite.getGlobalBounds();
    }
}


sf::Vector2f Disparo::getPosition() const {
    if (_tipo == TipoDisparo::BOLA_AZUL) {
        return _shape.getPosition();
    } else {
        return _sprite.getPosition();
    }
}


