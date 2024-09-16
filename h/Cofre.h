#include <SFML/Graphics.hpp>
#include "Colisionable.h"

class Cofre : public sf::Drawable, public Collisionable
{
    sf::Sprite _sprite;
    sf::Texture _textur;
    bool _visible;  // Nueva bandera para controlar la visibilidad del cofre
    sf::Texture _texturRecogido;  // Nueva textura para cuando el cofre es recogido
    bool _abierto; // Nueva bandera para controlar si el cofre ya ha sido abierto

public:
    Cofre();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setVisible(bool visible);  // Nueva función para cambiar la visibilidad
    bool isVisible() const;  // Función para consultar si está visible
    void cambiarTextura();  // Nueva función para cambiar la textura
    bool estaAbierto() const; // Nueva función para consultar si el cofre está abierto
};
