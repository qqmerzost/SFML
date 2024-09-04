#pragma once
#include <SFML/Graphics.hpp>

class Coin
{
public:
    Coin(sf::Vector2f position);

    // Mark render as const because it doesn't modify the coin
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape mCoin;
};
