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
    void setVisible(bool visible);  // Nueva funci�n para cambiar la visibilidad
    bool isVisible() const;  // Funci�n para consultar si est� visible
    void setPosition(const sf::Vector2f& position);  // Nueva funci�n para cambiar la posici�n
    bool isPickedUp() const;  // Funci�n para saber si el libro fue recogido
};
