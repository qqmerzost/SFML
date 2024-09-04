#include "Coin.h"

Coin::Coin(sf::Vector2f position)
{
    mCoin.setRadius(15.f);  // Coin size
    mCoin.setPosition(position);
    mCoin.setFillColor(sf::Color::Yellow);  // Coin color
}

// Add const here to ensure it matches the const-correctness in Coin.h
void Coin::render(sf::RenderWindow& window) const
{
    window.draw(mCoin);
}

sf::FloatRect Coin::getBounds() const
{
    return mCoin.getGlobalBounds();
}
