#include "../../gancho.h"

Gancho::Gancho() {
    _textur.loadFromFile("./Imagenes/Items/Gancho.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool Gancho::agarrado = false;



sf::FloatRect Gancho::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Gancho::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
void Gancho::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Gancho::recolectado(){
    agarrado = true;
}

bool Gancho::estadoDelGancho() const{
    return agarrado;
}
