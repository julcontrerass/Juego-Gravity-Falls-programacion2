#include "../../minotauro.h"
#include "../../disparo.h"
#include <cmath>

Minotauro::Minotauro()
    : _persiguiendo(false),
      _tiempoEntreDisparos(sf::seconds(2.0f)),
      _vidas(5),
      _frame(0),
      _direccionMirada(0, 1),
      _velocity(0, 0)
{
    if (!_textur.loadFromFile("./Imagenes/Personajes/minotauro.png"))
    {
        throw std::runtime_error("Error al cargar la imagen del gnomo");
    }

    _sprite.setTexture(_textur);
    _sprite.setTextureRect({62, 156, 60, 78});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}

void Minotauro::update(const sf::Vector2f& personajePos)
{
    float distancia = std::sqrt(std::pow(personajePos.x - _sprite.getPosition().x, 2) +
                                std::pow(personajePos.y - _sprite.getPosition().y, 2));

    _velocity = {0, 0};

    if (_frame >= 2) _frame = 0;

    if (distancia < 500 && _vidas > 0)
    {
        _persiguiendo = true;
    }
    else
    {
        _persiguiendo = false;
    }

    if (_persiguiendo)
    {
        sf::Vector2f direccion = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
        direccion /= longitud;
        _velocity = direccion * 2.0f;
        _direccionMirada = direccion;

        _frame += 0.2f;

        // Actualiza el rectángulo de textura según la dirección del movimiento
        if (std::abs(_direccionMirada.x) > std::abs(_direccionMirada.y))
        {
            if (_direccionMirada.x > 0)
            {
                // Movimiento hacia la derecha
                _sprite.setTextureRect({int(_frame) * 62, 156, 60, 78});
            }
            else
            {
                // Movimiento hacia la izquierda
                _sprite.setTextureRect({int(_frame) * 62, 78, 60, 78});
            }
        }
        else
        {
            if (_direccionMirada.y > 0)
            {
                // Movimiento hacia abajo
                _sprite.setTextureRect({int(_frame) * 62, 0, 60, 78});
            }
            else
            {
                // Movimiento hacia arriba
                _sprite.setTextureRect({int(_frame) * 62, 235, 60, 78});
            }
        }

        disparar(personajePos);
    }

    _sprite.move(_velocity);

    // Actualiza las balas
    for (auto it = _balas.begin(); it != _balas.end();)
    {
        it->update();
        if (!it->isAlive())
        {
            it = _balas.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Minotauro::setInitialTextureRect(int row)
{
    _sprite.setTextureRect({50, row * 0, 50, 55});
}


void Minotauro::disparar(const sf::Vector2f& personajePos)
{
    if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos)
    {
        sf::Vector2f direccionDisparo = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccionDisparo.x * direccionDisparo.x + direccionDisparo.y * direccionDisparo.y);
        direccionDisparo /= longitud;
        sf::Vector2f origenBala = _sprite.getPosition();
        origenBala.y -= _sprite.getGlobalBounds().height / 2;
        _balas.emplace_back(origenBala, direccionDisparo,4);
        _disparoCooldown.restart();
    }
}

void Minotauro::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    for (const auto& bala : _balas)
    {
        target.draw(bala, states);
    }
}

sf::FloatRect Minotauro::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Minotauro::recibirDanio()
{
    if (_vidas > 0)
    {
        _vidas--;
    }
}

int Minotauro::getVidas() const
{
    return _vidas;
}

bool Minotauro::estaVivo() const
{
    return _vidas > 0;
}

std::vector<Disparo>& Minotauro::getDisparos()
{
    return _balas;
}

void Minotauro::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

sf::Vector2f Minotauro::getPosition() const
{
    return _sprite.getPosition();
}
