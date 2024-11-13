#include "../../bill.h"
#include "../../disparo.h"
#include <cmath>

Bill::Bill()
    : _persiguiendo(false),
      _tiempoEntreDisparos(sf::seconds(2.0f)),
      _vidas(5),
      _frame(0),
      _direccionMirada(0, 1),
      _velocity(0, 0),
      _muriendo(false),
      _frameMuerte(0),
      _animacionMuerteCompleta(false)
{
    if (!_textur.loadFromFile("./Imagenes/Personajes/bill.png"))
    {
        throw std::runtime_error("Error al cargar la imagen de bill");
    }

    if (!_texturMuerte.loadFromFile("./Imagenes/Personajes/billMuriendo.png"))
    {
        throw std::runtime_error("Error al cargar la imagen de muerte de bill");
    }

    _sprite.setTexture(_textur);
    _sprite.setTextureRect({53, 0, 50, 70}); // Ajusta estos valores seg·n el tama±o de tu sprite
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}

void Bill::update(const sf::Vector2f& personajePos)
{
    if (_muriendo)
    {
        actualizarAnimacionMuerte();
        return;
    }

    float distancia = std::sqrt(std::pow(personajePos.x - _sprite.getPosition().x, 2) +
                                std::pow(personajePos.y - _sprite.getPosition().y, 2));

    // Reinicia la velocidad
    _velocity = {0, 0};

    // Reinicia el frame si se completa un ciclo
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

        // Actualiza la animaci≤n seg·n la direcci≤n
        _frame += 0.2f;

        // Actualiza el rectßngulo de textura seg·n la direcci≤n del movimiento
        if (std::abs(_direccionMirada.x) > std::abs(_direccionMirada.y))
        {
            if (_direccionMirada.x > 0)
            {
                // Movimiento hacia la derecha
                _sprite.setTextureRect({int(_frame) * 53, 132, 50, 70});
            }
            else
            {
                // Movimiento hacia la izquierda
                _sprite.setTextureRect({int(_frame) * 53, 70, 50, 70});
            }
        }
        else
        {
            if (_direccionMirada.y > 0)
            {
                // Movimiento hacia abajo
                _sprite.setTextureRect({int(_frame) * 53, 0, 50, 70});
            }
            else
            {
                // Movimiento hacia arriba
                _sprite.setTextureRect({int(_frame) * 53, 212, 50, 70});
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

void Bill::setInitialTextureRect(int row)
{
    _sprite.setTextureRect({50, row * 0, 50, 55});
}


void Bill::disparar(const sf::Vector2f& personajePos)
{
    if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos)
    {
        sf::Vector2f direccionDisparo = personajePos - _sprite.getPosition();
        float longitud = std::sqrt(direccionDisparo.x * direccionDisparo.x + direccionDisparo.y * direccionDisparo.y);
        direccionDisparo /= longitud;
        sf::Vector2f origenBala = _sprite.getPosition();
        origenBala.y -= _sprite.getGlobalBounds().height / 2;
        _balas.emplace_back(origenBala, direccionDisparo);
        _disparoCooldown.restart();
    }
}

void Bill::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    for (const auto& bala : _balas)
    {
        target.draw(bala, states);
    }
}

sf::FloatRect Bill::getBounds() const
{
    return _sprite.getGlobalBounds();
}

std::vector<Disparo>& Bill::getDisparos()
{
    return _balas;
}

void Bill::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

sf::Vector2f Bill::getPosition() const
{
    return _sprite.getPosition();
}

void Bill::iniciarAnimacionMuerte()
{
    if (!_muriendo)  // Solo verificamos que no estΘ ya muriendo
    {
        _muriendo = true;
        _frameMuerte = 0;
        _animacionMuerteCompleta = false;
        _posicionMuerte = _sprite.getPosition();

        _sprite.setTexture(_texturMuerte);
        _sprite.setTextureRect({134, 147, 67, 79});
    }
}
void Bill::actualizarAnimacionMuerte()
{
    if (_muriendo && !_animacionMuerteCompleta)
    {
        _frameMuerte += 0.1f; // Velocidad de la animaci≤n

        if (_frameMuerte >= FRAMES_MUERTE)
        {
            _animacionMuerteCompleta = true;
            return;
        }

        // Actualiza el frame de la animaci≤n de muerte
        _sprite.setTextureRect({int(_frameMuerte) / 134, 147, 67, 79});
        _sprite.setPosition(_posicionMuerte);
    }
    if (_animacionMuerteCompleta){
        _sprite.setTextureRect({0, 0, 67, 79});
    }
}

bool Bill::getEstadoAnimacion(){
    return _animacionMuerteCompleta;
}

bool Bill::estaAnimacionMuerteCompleta() const
{
    return _animacionMuerteCompleta;
}
