#include "../../libro1.h"

Libro1::Libro1()  {
    _textur.loadFromFile("./Imagenes/Items/Libro1.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}
bool Libro1::agarrado = false;

//void Libro1::update() {
//    // Aquí podrías actualizar el libro si es necesario
//}

sf::FloatRect Libro1::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Libro1::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);

}
// Método para establecer la posición del item
void Libro1::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Libro1::recolectado(){
    agarrado = true;
}

bool Libro1::estadoDelLibro() const{
    return agarrado;
}
