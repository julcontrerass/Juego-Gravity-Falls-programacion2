#include "../disparo.h"
#include <cmath>
#include <stdexcept>

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

sf::Texture Disparo::_texturaGancho;
sf::Texture Disparo::_texturaCuchillo;
bool Disparo::_texturasLoaded = false;

Disparo::Disparo(const sf::Vector2f& position, const sf::Vector2f& direction, int tipo)
    : _isAlive(true), _tipo(tipo)
{

    // Configurar velocidad base según el tipo
    float velocidadBase;

    if(tipo == 1 || tipo == 2)
    {
        loadTexturas();
    }

    switch(tipo)
    {
        case 1:
            _sprite.setTexture(_texturaCuchillo);
            _sprite.setScale(1.5,1.5);

            velocidadBase = 7.0f;
            break;
        case 2:
            _sprite.setTexture(_texturaGancho);

            velocidadBase = 8.0f;
            break;
        case 3:
            // Configuración para bola/linterna
            _shape.setRadius(10.f);
            _shape.setFillColor(sf::Color::Yellow);
            _shape.setOrigin(10.f, 10.f); // Centrar el origen
            _shape.setPosition(position);

            velocidadBase = 9.0f;
            break;
        case 4:
            // Configuración para bola azul
            _shape.setRadius(10.f);
            _shape.setFillColor(sf::Color::Blue);
            _shape.setOrigin(10.f, 10.f); // Centrar el origen
            _shape.setPosition(position);

            velocidadBase = 8.0f;
            break;
    }

    _velocity = direction * velocidadBase;


    // Configurar el sprite
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    _sprite.setPosition(position);

    // Calcular y establecer la rotación
    float angulo = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    _sprite.setRotation(angulo);
}

void Disparo::update() {
    // Actualizar posición según el tipo
    if (_tipo == 1 || _tipo == 2) {
        _sprite.move(_velocity);
    } else {
        _shape.move(_velocity);
    }

    // Verificar si el proyectil está fuera de la pantalla
    sf::FloatRect bounds = getBounds();
    if (bounds.left < -50.f || bounds.left > 1920.f + 50.f ||
        bounds.top < -50.f || bounds.top > 1080.f + 50.f) {
        _isAlive = false;
    }
}

void Disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (_tipo == 1 || _tipo ==2) {
        target.draw(_sprite, states);
    } else {
        target.draw(_shape, states);
    }
}

sf::FloatRect Disparo::getBounds() const {
    if (_tipo == 1 || _tipo == 2) {
        return _sprite.getGlobalBounds();
    } else {
        return _shape.getGlobalBounds();
    }

}


sf::Vector2f Disparo::getPosition() const {
    if (_tipo == 1 || _tipo == 2) {
        return _sprite.getPosition();
    } else {
        return _shape.getPosition();
    }
}

