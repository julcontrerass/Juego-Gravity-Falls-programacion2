#include "../../libro2.h"

Libro2::Libro2(){
    _textur.loadFromFile("./Imagenes/Items/Libro2.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool Libro2::agarrado = false;

void Libro2::update() {
}

sf::FloatRect Libro2::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Libro2::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
void Libro2::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Libro2::recolectado(){
    agarrado = true;
}

bool Libro2::estadoDelLibro() const{
    return agarrado;
}

