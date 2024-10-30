#pragma once
#include <SFML/Graphics.hpp>

class ItemLanzado : public sf::Drawable
{
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    bool _isAlive;

public:
    ItemLanzado(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update();
    sf::FloatRect getBounds() const;
    bool isAlive() const;
};
