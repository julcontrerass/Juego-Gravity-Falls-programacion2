#include "Enemigo.h"
#include <cmath>

Enemigo::Enemigo() : _persiguiendo(false), _tiempoEntreDisparos(sf::seconds(1.0f)), _vidas(5) {
    _textur.loadFromFile("images/gnomo.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setPosition(862, 806);
    _velocity = {0, 0};
}

void Enemigo::update(const sf::Vector2f& personajePos) {
    float distancia = std::sqrt(std::pow(personajePos.x - _sprite.getPosition().x, 2) +
                                std::pow(personajePos.y - _sprite.getPosition().y, 2));
    if (distancia < 300) {
        _persiguiendo = true;
    } else if( _vidas == 0){
        _persiguiendo = false;
    }
    else {
        _persiguiendo = false;
    }
    if (_persiguiendo) {
        sf::Vector2f direccion = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        direccion /= longitud;
        _velocity = direccion * 3.0f;
        disparar(personajePos);
    } else {
        _velocity = {0, 0};
    }
    _sprite.move(_velocity);

    for (auto it = _balas.begin(); it != _balas.end();) {
        it->update();
        if (!it->isAlive()) {
            it = _balas.erase(it);
        } else {
            ++it;
        }
    }
}

void Enemigo::disparar(const sf::Vector2f& personajePos) {
    if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos) {
        sf::Vector2f direccionDisparo = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccionDisparo.x * direccionDisparo.x + direccionDisparo.y * direccionDisparo.y);
        direccionDisparo /= longitud;
        sf::Vector2f origenBala = _sprite.getPosition();
        origenBala.y -= _sprite.getGlobalBounds().height / 2;
        _balas.emplace_back(origenBala, direccionDisparo);
        _disparoCooldown.restart();
    }
}

sf::FloatRect Enemigo::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
    for (const auto& bala : _balas) {
        target.draw(bala, states);
    }
}

void Enemigo::recibirDanio()
{
    if (_vidas > 0)
    {
        _vidas--;
    }
}

int Enemigo::getVidas() const
{
    return _vidas;
}

bool Enemigo::estaVivo() const
{
    return _vidas > 0;
}

std::vector<Bala>& Enemigo::getBullets()
{
    return _balas;
}
