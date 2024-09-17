#include "Personaje.h"

Personaje::Personaje()
    : _frame(0), _velocity(4, 4), _tiempoEntreDisparos(sf::seconds(0.5f)), _direccionMirada(0, 1), _vidas(5)
{
    _texture.loadFromFile("images/dipper.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({0, 0, 50, 55});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _sprite.setPosition(1185, 100);
}

void Personaje::update()
{
    _velocity = {0, 0};
    if (_frame >= 2) _frame = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _velocity.y = -4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 169, 50, 55});
        _direccionMirada = {0, -1};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity.y = 4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 0, 50, 55});
        _direccionMirada = {0, 1};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity.x = -4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 57, 50, 55});
        _direccionMirada = {-1, 0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity.x = 4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 113, 50, 55});
        _direccionMirada = {1, 0};
    }
    _sprite.move(_velocity);

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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        disparar();
    }
}

void Personaje::disparar()
{
    if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos)
    {
        sf::Vector2f origenBala = _sprite.getPosition();
        origenBala.y -= _sprite.getGlobalBounds().height / 2;
        _balas.emplace_back(origenBala, _direccionMirada);
        _disparoCooldown.restart();
    }
}

sf::Vector2f Personaje::getPosition() const
{
    return _sprite.getPosition();
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    for (const auto& bala : _balas)
    {
        target.draw(bala, states);
    }
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Personaje::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Personaje::recibirDanio()
{
    if (_vidas > 0)
    {
        _vidas--;
    }
}

int Personaje::getVidas() const
{
    return _vidas;
}

bool Personaje::estaVivo() const
{
    return _vidas > 0;
}

std::vector<Bala>& Personaje::getBullets()
{
    return _balas;
}



