#include "Cofre.h"

Cofre::Cofre() : _abierto(false), _visible(true) // Inicializamos la bandera _abierto a false
{
    _textur.loadFromFile("images/cofreCerrado.png");
    _texturRecogido.loadFromFile("images/cofreAbierto.png");  // Asegúrate de que la ruta sea correcta
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    // Inicializamos la posición del cofre en el centro de la pantalla
    _sprite.setPosition(1180, 800);
}

void Cofre::update()
{
}

sf::FloatRect Cofre::getBounds() const
{
    return _sprite.getGlobalBounds();
}

void Cofre::setVisible(bool visible)
{
    _visible = visible;
}

bool Cofre::isVisible() const
{
    return _visible;
}

void Cofre::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_visible) // Solo dibuja el cofre si está visible
    {
        target.draw(_sprite, states);
    }
}

void Cofre::cambiarTextura()
{
    if (!_abierto) // Solo cambia la textura si el cofre no está abierto
    {
        _sprite.setTexture(_texturRecogido);  // Cambia la textura del sprite al estado recogido
        _abierto = true; // Marca el cofre como abierto
    }
}

bool Cofre::estaAbierto() const
{
    return _abierto;
}

