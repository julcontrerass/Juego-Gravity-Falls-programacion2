#include "../h/Personaje.h"

Personaje::Personaje()
{
    _frame = 0;
    _velocity = {4, 4};
    _textur.loadFromFile("images/dipper.png");
    _sprite.setTexture(_textur);
    _sprite.setTextureRect({0, 0, 50, 55});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    // Inicializamos la posición del personaje en el centro de la pantalla
    _sprite.setPosition(1185, 100);
}

void Personaje::update()
{
    _velocity = {0, 0};

    if (_frame >= 2)
    {
        _frame = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _velocity.y = -4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 169, 50, 55});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity.y = 4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 0, 50, 55});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity.x = -4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 57, 50, 55});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity.x = 4;
        _frame += 0.2;
        _sprite.setTextureRect({0 + int(_frame) * 50, 113, 50, 55});
    }

    // Movemos el personaje según la velocidad
    _sprite.move(_velocity);
}

sf::Vector2f Personaje::getPosition() const
{
    return _sprite.getPosition();
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Personaje::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}



