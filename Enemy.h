#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(sf::Vector2f position);

    void update(float deltaTime);
    // Mark render as const because it doesn't modify the enemy
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape mBody;
    sf::Vector2f mVelocity;
    float speed;
};
