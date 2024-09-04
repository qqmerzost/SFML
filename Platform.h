#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
public:
    Platform(sf::Vector2f position, sf::Vector2f size);

    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape mBody;
};
