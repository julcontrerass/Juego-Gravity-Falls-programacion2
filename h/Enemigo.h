#include <SFML/Graphics.hpp>
#include "Colisionable.h"

class Enemigo : public sf::Drawable, public Collisionable
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    sf::Vector2f _velocity;
    bool _persiguiendo;  // Indica si el enemigo está persiguiendo al personaje

public:
    Enemigo();
    void update(const sf::Vector2f& personajePos);  // Ahora se pasa la posición del personaje
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;

};

