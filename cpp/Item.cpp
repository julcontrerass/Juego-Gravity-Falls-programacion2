#include "Item.h"

Item::Item() {
    _textur.loadFromFile("images/Libro1.png");
    _sprite.setTexture(_textur);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    _visible = false;
    _pickedUp = false; // Inicializamos como no recogido
    _sprite.setPosition(1120, 800); // Posición inicial del libro en el mapa
}

void Item::update() {
    // Aquí podrías actualizar el libro si es necesario
}

sf::FloatRect Item::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Item::setVisible(bool visible) {
    _visible = visible;
}

bool Item::isVisible() const {
    return _visible;
}

void Item::setPosition(const sf::Vector2f& position) {
    _sprite.setPosition(position);  // Cambia la posición del sprite
    _pickedUp = true;  // Marca el libro como recogido
}

bool Item::isPickedUp() const {
    return _pickedUp;
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_visible) {
        target.draw(_sprite, states);
    }
}



