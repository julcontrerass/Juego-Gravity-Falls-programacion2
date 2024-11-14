#include "../../libro3.h"

Libro3::Libro3(){
    _textur.loadFromFile("./Imagenes/Items/Libro3.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}


bool Libro3::agarrado = false;

sf::FloatRect Libro3::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Libro3::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
void Libro3::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Libro3::recolectado(){
    agarrado = true;
}

bool Libro3::estadoDelLibro() const{
    return agarrado;
}
