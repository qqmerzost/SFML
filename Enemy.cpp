#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position)
    : mVelocity(100.f, 0.f), speed(100.f)
{
    mBody.setSize(sf::Vector2f(50, 50));  // Goomba size
    mBody.setPosition(position);
    mBody.setFillColor(sf::Color::Yellow);  // Goomba color
}

void Enemy::update(float deltaTime)
{
    // Move the enemy left and right
    mBody.move(mVelocity * deltaTime);

    // Simple movement logic (reverses when hitting screen edge)
    if (mBody.getPosition().x <= 0 || mBody.getPosition().x + mBody.getSize().x >= 800)
    {
        mVelocity.x = -mVelocity.x;  // Reverse direction
    }
}

// Add const here to ensure it matches the const-correctness in Enemy.h
void Enemy::render(sf::RenderWindow& window) const
{
    window.draw(mBody);
}

sf::FloatRect Enemy::getBounds() const
{
    return mBody.getGlobalBounds();
}
