#include "linterna.h"
Linterna::Linterna() {
    _textur.loadFromFile("./Imagenes/Items/Linterna.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool Linterna::agarrado = false;

void Linterna::update() {
    // Aquí podrías actualizar el libro si es necesario
}

sf::FloatRect Linterna::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Linterna::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
// Método para establecer la posición del item
void Linterna::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Linterna::recolectado(){
    agarrado = true;
}

bool Linterna::estadoDeLaLinterna() const{
    return agarrado;
}
