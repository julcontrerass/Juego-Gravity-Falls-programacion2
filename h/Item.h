#include <SFML/Graphics.hpp>
#include "Colisionable.h"
class Item: public sf::Drawable, public Collisionable
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    bool _visible;  // Nueva bandera para controlar la visibilidad del libro
    bool _pickedUp; // Nueva bandera para saber si fue recogido

public:
    Item();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setVisible(bool visible);  // Nueva función para cambiar la visibilidad
    bool isVisible() const;  // Función para consultar si está visible
    void setPosition(const sf::Vector2f& position);  // Nueva función para cambiar la posición
    bool isPickedUp() const;  // Función para saber si el libro fue recogido
};
