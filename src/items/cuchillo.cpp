#include "../../cuchillo.h"

Cuchillo::Cuchillo() {
    _textur.loadFromFile("./Imagenes/Items/Cuchillo.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool Cuchillo::agarrado = false;
void Cuchillo::update() {
}

sf::FloatRect Cuchillo::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Cuchillo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
void Cuchillo::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Cuchillo::recolectado(){
    agarrado = true;
}

bool Cuchillo::estadoDelCuchillo() const{
    return agarrado;
}




