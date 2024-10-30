#include "cofre.h"

#include "cofre.h"

// Inicializaci�n del array est�tico
bool Cofre::cofresAbiertos[MAX_COFRES] = {false};  // Todos los cofres comienzan cerrados

Cofre::Cofre(int numeroCofre) :
    _visible(true),
    _numeroCofre(numeroCofre)
{
    // Verificar que el n�mero de cofre sea v�lido
    if(numeroCofre < 0 || numeroCofre >= MAX_COFRES) {
        throw std::runtime_error("N�mero de cofre inv�lido");
    }

    // Cargar texturas
    if (!_textur.loadFromFile("./Imagenes/Items/cofreCerrado.png")) {
        throw std::runtime_error("No se pudo cargar la textura del cofre cerrado");
    }
    if (!_texturRecogido.loadFromFile("./Imagenes/Items/cofreAbierto.png")) {
        throw std::runtime_error("No se pudo cargar la textura del cofre abierto");
    }

    // Configurar sprite inicial
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);

    // Verificar si este cofre ya fue abierto anteriormente
    _abierto = cofresAbiertos[_numeroCofre];
    if (_abierto) {
        _sprite.setTexture(_texturRecogido);
    }

    // Cargar sonido
    if (!sonidoCofre.openFromFile("./Imagenes/Sonidos/cofreAbriendo.wav")) {
        throw std::runtime_error("No se pudo cargar la m�sica del cofre.");
    }
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
    if (_visible) // Solo dibuja el cofre si est� visible
    {
        target.draw(_sprite, states);
    }
}

void Cofre::cambiarTextura()
{
    if (!_abierto) {
        _sprite.setTexture(_texturRecogido);
        _abierto = true;
        cofresAbiertos[_numeroCofre] = true;  // Actualizar el estado global
    }
}


bool Cofre::estaAbierto() const
{
    return _abierto;
}
void Cofre::resetearTodosLosCofres()
{
    for(int i = 0; i < MAX_COFRES; i++) {
        cofresAbiertos[i] = false;
    }
}

bool Cofre::getEstadoCofre(int numeroCofre)
{
    if(numeroCofre >= 0 && numeroCofre < MAX_COFRES) {
        return cofresAbiertos[numeroCofre];
    }
    return false;
}

void Cofre::setEstadoCofre(int numeroCofre, bool estado)
{
    if(numeroCofre >= 0 && numeroCofre < MAX_COFRES) {
        cofresAbiertos[numeroCofre] = estado;
    }
}

// M�todo para establecer la posici�n del item
void Cofre::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}
